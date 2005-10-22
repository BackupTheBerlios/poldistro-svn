using System;
using System.Collections;
using System.IO;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for Groups.
	/// </summary>
	public class Groups
	{
		private Hashtable groups;

		public Groups()
		{
			groups = new Hashtable();
			loadGroups();
		}

		public string[] getGroups()
		{
			string[] strarr = new string[groups.Count];
			groups.Keys.CopyTo(strarr,0);
			Array.Sort(strarr);
			return strarr;
		}

		public string[] getGroupItems(string group)
		{
			if (!groups.ContainsKey(group))
				return null;
			ArrayList al = (ArrayList)groups[group];
			string[] strarr = new string[al.Count];
			al.CopyTo(strarr);
			Array.Sort(strarr);
			return strarr;
		}

		private void loadGroups()
		{
			try {
				TextReader tr = new StreamReader("gump.def");
				string line, regionName="", tmp;
				bool inRegion = false;
				char[] delims = new char[]{' ','\t'};
				ArrayList items = new ArrayList();

				while ((line = tr.ReadLine()) != null) {
					if (line.Length > 0 && !line.StartsWith("//")) {
						tmp = line.Trim();
						if (tmp.Equals("{")) {
							inRegion=true;

							if(!groups.ContainsKey(regionName))
								groups.Add(regionName,null);
							items=new ArrayList();
						} else if (tmp.Equals("}")) {
							groups[regionName] = items;
							inRegion = false;
						} else {
							if (inRegion) {
								items.Add(tmp);
							} else {
								regionName = tmp;
							}
						}
					}
				}
			} catch(Exception exc) {
				System.Windows.Forms.MessageBox.Show(null, "Error accured during reading Gump.def file. Reason:\n"
					+ exc.Message, "Error",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);
			}
		}
	}
}
