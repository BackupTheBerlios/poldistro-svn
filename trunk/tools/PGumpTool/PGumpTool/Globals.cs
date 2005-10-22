using System;
using Microsoft.Win32;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for Globals.
	/// </summary>
	public class Globals
	{
		public static string fontPath = getUOPath() + "\\fonts.mul";
		public static UOFonts fonts = new UOFonts(fontPath);

		public static string getUOPath()
		{
			try {
				RegistryKey key = Registry.LocalMachine;
				key = key.OpenSubKey("SOFTWARE\\Origin Worlds Online\\Ultima Online\\1.0");
				object val = key.GetValue("InstCDPath");
				if (val != null)
					return val.ToString();
				else
					return null;
			} catch(Exception exc) {
				return null;
			}
		}
	}

}
