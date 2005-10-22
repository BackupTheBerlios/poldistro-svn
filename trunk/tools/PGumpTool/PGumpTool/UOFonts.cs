using System;
using System.Collections;
using System.IO;
using System.Drawing;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for UOFonts.
	/// </summary>
	public class UOFonts
	{
		private ArrayList fonts; 

		public UOFonts(string pathToFontFile)
		{
			fonts = new ArrayList();
			loadFonts(pathToFontFile);
		}

		private void loadFonts(string pathToFontFile){
			FileStream fs = new FileStream(pathToFontFile,FileMode.Open,FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			int width, height;
			int[] rgb;
			Bitmap font;
			Color c;
			ArrayList fontChars;
			while(br.BaseStream.Position<br.BaseStream.Length)
			{
				br.ReadByte();
				fontChars=new ArrayList();
				for(int i=0;i<224;i++)
				{
					width = (int)br.ReadByte();
					height = (int)br.ReadByte();
					if((width+height)*2+br.BaseStream.Position+1>=br.BaseStream.Length)
						break;
					if(width>0&&height>0)
					{
						br.ReadByte();
						font=new Bitmap(width,height);

						for (int y=0; y<height; y++) {
							for (int x=0; x<width; x++) {
								rgb = Gump.uoColorToRgb(br.ReadUInt16());
								c = Color.FromArgb(rgb[0],rgb[1],rgb[2]);
								if (!(rgb[0] == 0 && rgb[1] == 0 && rgb[2] == 0))
									font.SetPixel(x,y,c);
							}
						}
						fontChars.Add(font);
					}
				}
				fonts.Add(fontChars);
			}
			br.Close();			
		}

		public Bitmap getFont(int fontC,int fontnum)
		{
			return (Bitmap)((ArrayList)fonts[fontnum])[fontC];
		}
	}
}
