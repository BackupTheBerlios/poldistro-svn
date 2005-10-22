using System;
using System.Drawing;
using System.IO;
using System.ComponentModel;
using System.Collections;
using System.Xml;
using System.Xml.Serialization;

namespace PGumpTool
{
	public delegate void sizeChanged(object sender);
	public delegate void priorityChanged(object sender);

	/// <summary>
	/// Summary description for Gump.
	/// </summary>
	[DefaultPropertyAttribute("X")]
	[XmlIncludeAttribute(typeof(ResizableGump))]
	[XmlIncludeAttribute(typeof(UOText))]
	[XmlIncludeAttribute(typeof(GumpButton))]
	public class Gump:IComparable
	{
		protected Bitmap image;
		protected GumpIdx _gidx;
		protected int _x;
		protected int _y;
		private int _priority;

		public event sizeChanged SizeChanged;
		public event priorityChanged PriorityChanged;

		[CategoryAttribute("Location"),
		ReadOnly(true),
		DescriptionAttribute("Gump width")]
		public int Width
		{
			get
			{ return image.Width; }
		}

		[CategoryAttribute("Location"),  
		ReadOnly(true),
		DescriptionAttribute("Gump height")]
		public int Height
		{
			get { return image.Height; }
		}

		[CategoryAttribute("Information"),  
		ReadOnly(true),
		DescriptionAttribute("ID represents one of three possible ids: gump-picture-ids, tile-picture-ids and text-ids.")]
		public int ID
		{
			get { return _gidx.ID; }
		}

		[CategoryAttribute("Information"),  
		ReadOnly(true),
		Browsable(false),
		DescriptionAttribute("Gump Image")]
		[XmlIgnoreAttribute]
		public Bitmap Image
		{
			get {
				if (image == null)
					image = Gump.getBitmap(_gidx,Globals.getUOPath()+"\\gumpart.mul");
				return image;
			}
		}

		[CategoryAttribute("Information"),  
		ReadOnly(true),
		DescriptionAttribute("Gump Indexer")]
		public GumpIdx Gidx
		{
			get { return _gidx; }
			set{
				_gidx=value;
			}
		}

		[CategoryAttribute("Location"),  
		ReadOnly(true),
		DescriptionAttribute("X specifies the x-coordinate of the upper left corner of the object you want to position")]
		public int X
		{
			get { return _x; }
			set {
				_x=(int)value;
				riseOnSizeChangeEvent();
			}
		}

		[CategoryAttribute("Location"),  
		DescriptionAttribute("Y specifies the y-coordinate of the upper left corner of the object you want to position")]
		public int Y
		{
			get { return _y; }
			set{
				_y=(int)value;
				riseOnSizeChangeEvent();
			}
		}

		[CategoryAttribute("Location"),  
		DescriptionAttribute("Priority of drawing the gump")]
		public int Priority
		{
			get { return _priority; }
			set {
				_priority=(int)value;
				riseOnPriorityChangedEvent();
			}
		}
		public Gump()
		{
		}

		public Gump(GumpIdx gidx, string pathToGumpArt){
			image=Gump.getBitmap(gidx,pathToGumpArt);
			this._gidx=gidx;
		}

		public static Bitmap getBitmap(GumpIdx gidx, string pathToGumpArt)
		{
			Bitmap img = new Bitmap(gidx.Width, gidx.Height);

			FileStream fs = new FileStream(pathToGumpArt,FileMode.Open,FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);

			uint width=gidx.Width;
			uint height=gidx.Height;
			uint lookup=gidx.Lookup;
			uint size=gidx.Size;

			int[] lookupTable=new int[height];
			int[] rgb;
			Color c;
			short length; 

			fs.Seek(lookup,SeekOrigin.Begin);

			for(int i=0; i < height; i++) {
				lookupTable[i]=BitConverter.ToInt32(br.ReadBytes(4),0);
			}

			for(int y=0; y<height; y++) {
				fs.Seek(lookupTable[y]*4+lookup,SeekOrigin.Begin);
				for (int x=0; x<width; x++) {
					rgb=uoColorToRgb(BitConverter.ToUInt16(br.ReadBytes(2),0));
					length=BitConverter.ToInt16(br.ReadBytes(2),0);
					c=Color.FromArgb(rgb[0]%255,rgb[1]%255,rgb[2]%255);

					for(int i=0; i<length; i++) {
						if(rgb[0] !=0 || rgb[1] !=0 || rgb[2] != 0)
							img.SetPixel(x+i, y, c);
					}
					x += length - 1;
				}
			}
			
			br.Close();

			return img;
		}

		public static int[] uoColorToRgb(ushort color)
		{
			int[] rgb = new int[3];
			rgb[0] = ((color >> 10) * 8);
			rgb[1] = ((color >> 5) & 0x1F) * 8;
			rgb[2] = (color & 0x1F) * 8;
			return rgb;
		}

		protected void riseOnSizeChangeEvent()
		{
			if (SizeChanged != null)
				SizeChanged(this);
		}

		protected void riseOnPriorityChangedEvent()
		{
			if (PriorityChanged!=null)
				PriorityChanged(this);
		}

		public override string ToString()
		{
			return "GumpPic 0x"+Convert.ToString(ID,16).ToUpper()+" "+_x+" "+_y;
		}

		#region IComparable Members

		public int CompareTo(object obj)
		{
			try {
				Gump gmp = (Gump)obj;
				if (this._priority > gmp.Priority)
					return 1;
				else if(this._priority == gmp.Priority)
					return 0;
				else
					return -1;
			} catch(Exception e) {
				return 0;
			}
		}

		#endregion
	}
}
