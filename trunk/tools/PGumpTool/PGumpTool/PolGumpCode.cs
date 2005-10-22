using System;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for PolGumpCode.
	/// </summary>
	public class PolGumpCode
	{
		private string _gfxlayout;
		private string _datatext;
		private string _othertext;

		public string TextGfx
		{
			get { return _gfxlayout; }
			set { _gfxlayout = value; }
		}

		public string TextData
		{
			get { return _datatext; }
			set { _datatext = value; }
		}

		public string TextOther
		{
			get { return _othertext; }
			set { _othertext = value; }
		}

		public PolGumpCode(string gfx, string data, string other)
		{
			_gfxlayout = gfx;
			_datatext = data;
			_othertext = other;
		}

		public PolGumpCode(string gfx, string data):this(gfx, data, null)
		{
		}

		public PolGumpCode(string gfx):this(gfx, null)
		{
		}

		public PolGumpCode()
		{
		}
	}
}
