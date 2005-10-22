using System;
using System.ComponentModel;
namespace PGumpTool
{
	/// <summary>
	/// Summary description for GumpButton.
	/// </summary>
	public class GumpButton:Gump
	{
		private int	_pressedId;
		private bool	_quit;
		private int	_pageid;
		private int	_return;

		[DescriptionAttribute("Sets the image you want to use for a button that is pressed.")]
		public int PressedID
		{
			get { return _pressedId; }
			set { _pressedId=(int)value; }
		}

		[CategoryAttribute("Special"),  
		DescriptionAttribute("Determines whether you want to exit the gump after clicking the button or not.")]
		public bool Quit
		{
			get { return _quit; }
			set { _quit = (bool)value; }
		}

		[CategoryAttribute("Special"),  
		DescriptionAttribute("Moves you to another page specified by this parameter")]
		public int PageID
		{
			get { return _pageid; }
			set { _pageid=(int)value; }
		}

		[CategoryAttribute("Special"),  
		DescriptionAttribute("The return value is what tells the script which follows the gump what to do. A return-value for a button should never double another button. [except they are only used as \"send\"-buttons for radio- or checkbox values]")]
		public int ReturnValue
		{
			get { return _return; }
			set { _return=(int)value; }
		}

		public GumpButton(){}
		public GumpButton(GumpIdx gidx, string pathToGumpArt):base(gidx,pathToGumpArt)
		{
			_pressedId=gidx.ID+1;
		}

		public override string ToString()
		{
			string rText = "Button "+_x+" "+_y+" 0x"+Convert.ToString(ID,16)+" 0x"+Convert.ToString(_pressedId,16)+" ";
			if(_quit) {
				rText+="1 ";
			} else {
				rText+="1 ";
			}
			rText += ""+_pageid+" "+_return;
			return rText;
		}

	}
}
