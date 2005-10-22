using System;
using System.ComponentModel;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for ResizableGump.
	/// </summary>
	public class ResizableGump : Gump
	{
		protected int _width;
		protected int _height;

		[CategoryAttribute("Location"),
		ReadOnly(false),
		DescriptionAttribute("This parameter is only used for resizepics and textentries. It sets the width of the picture or [for textentries] the width of the area in which the player may click in order to enable textentry.")]
		new public int Width
		{
			get { return _width; }
			set {
				_width=(int)value;
				riseOnSizeChangeEvent();
			}
		}

		[CategoryAttribute("Location"),  
		ReadOnly(false),
		DescriptionAttribute("This parameter is only used for resizepics and textentries. It sets the height of the picture or [for textentries] the height of the area in which the player may click in order to enable textentry.")]
		new public int Height
		{
			get { return _height; }
			set
			{
				_height = (int)value;
				riseOnSizeChangeEvent();
			}
		}
		
		public ResizableGump(){
		}

		public ResizableGump(GumpIdx gidx, string pathToGumpArt) : base(gidx, pathToGumpArt)
		{
			this._width = gidx.Width;
			this._height = gidx.Height;
		}

		public override string ToString()
		{
			return "ResizePic "+_x+" "+_y+" 0x"+Convert.ToString(ID,16).ToUpper()+" "+_width+" "+_height;
		}

	}
}
