using System;
using System.IO;
using System.Drawing;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for UOText.
	/// </summary>
	public class UOText:Gump
	{
		private string _text;
		private int _type;

		public string Text
		{
			get { return _text; }
			set {
				_text=(string)value;
				generateImage();
				riseOnSizeChangeEvent();
			}
		}

		public int FontStyle
		{
			get { return _type; }
			set {
				_type=(int)value;
				generateImage();
				riseOnSizeChangeEvent();
			}
		}

		public UOText(string text,string pathToFontFile)
		{	
			_gidx = new GumpIdx(0, new byte[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
			_text=text;
			generateImage();
		}

		public UOText()
		{
		}

		public override string ToString()
		{
			//Text [x] [y] [color] [text-id]
			return "Text "+X+" "+Y+" 0";
		}

		public void generateImage()
		{
			Bitmap[] fnts = new Bitmap[_text.Length];
			int sumx=0; int maxy=0; int wsum=0;;
			for (int i=0; i<_text.Length; i++)
			{
				fnts[i]=Globals.fonts.getFont((int)_text[i]-32,_type);
				sumx+=fnts[i].Width;
				if(maxy<fnts[i].Height) maxy=fnts[i].Height;
			}
			image = new Bitmap(sumx,maxy);

			for (int i=0; i<_text.Length; i++) {
				for (int x=0; x<fnts[i].Width; x++) {
					for (int y=0; y<fnts[i].Height; y++) {
						image.SetPixel(x+wsum, y, fnts[i].GetPixel(x, y));
					}
				}
				wsum+=fnts[i].Width;
			}
		}
	}
}
