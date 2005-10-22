using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.IO;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for GumpChooser.
	/// </summary>
	public class GumpChooser : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.Splitter splitter1;
		private System.Windows.Forms.Splitter splitter2;
		private PGumpTool.GumpPreview gumpPreview1;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox gbGroups;
		private System.Windows.Forms.Button bAdd;
		private System.Windows.Forms.Button bCancel;
		private System.Windows.Forms.ListBox lbGroups;
		private System.Windows.Forms.ListBox lbGumps;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private Hashtable indexes = new Hashtable();
		private Groups groups = new Groups();
		private string GumpPath;
		private System.Windows.Forms.Panel panel3;
		private Gump _selectedGump;

		public Gump SelectedGump
		{
			get
			{
				return _selectedGump;
			}
		}

		public GumpIdx SelectedIndex
		{
			get{
				return (GumpIdx)indexes[lbGumps.SelectedItem];
			}
		}
		public GumpChooser(string gumpPath)
		{
			//
			// Required for Windows Form Designer support
			//
			GumpPath=gumpPath;
			InitializeComponent();
			loadIndexes();
			lbGroups.Items.Add("All");
			lbGroups.Items.AddRange(groups.getGroups());
			lbGroups.SelectedIndex=0;
			//lbGumps.Items.AddRange(indexes.ToArray());
			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.panel1 = new System.Windows.Forms.Panel();
			this.gbGroups = new System.Windows.Forms.GroupBox();
			this.lbGroups = new System.Windows.Forms.ListBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.lbGumps = new System.Windows.Forms.ListBox();
			this.panel2 = new System.Windows.Forms.Panel();
			this.bCancel = new System.Windows.Forms.Button();
			this.bAdd = new System.Windows.Forms.Button();
			this.splitter1 = new System.Windows.Forms.Splitter();
			this.splitter2 = new System.Windows.Forms.Splitter();
			this.gumpPreview1 = new PGumpTool.GumpPreview();
			this.panel3 = new System.Windows.Forms.Panel();
			this.panel1.SuspendLayout();
			this.gbGroups.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.panel2.SuspendLayout();
			this.panel3.SuspendLayout();
			this.SuspendLayout();
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.gbGroups);
			this.panel1.Controls.Add(this.groupBox1);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel1.DockPadding.All = 4;
			this.panel1.Location = new System.Drawing.Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(152, 406);
			this.panel1.TabIndex = 0;
			// 
			// gbGroups
			// 
			this.gbGroups.Controls.Add(this.lbGroups);
			this.gbGroups.Dock = System.Windows.Forms.DockStyle.Fill;
			this.gbGroups.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.gbGroups.Location = new System.Drawing.Point(4, 260);
			this.gbGroups.Name = "gbGroups";
			this.gbGroups.Size = new System.Drawing.Size(144, 142);
			this.gbGroups.TabIndex = 1;
			this.gbGroups.TabStop = false;
			this.gbGroups.Text = "Groups";
			// 
			// lbGroups
			// 
			this.lbGroups.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lbGroups.Location = new System.Drawing.Point(3, 16);
			this.lbGroups.Name = "lbGroups";
			this.lbGroups.Size = new System.Drawing.Size(138, 121);
			this.lbGroups.TabIndex = 0;
			this.lbGroups.SelectedIndexChanged += new System.EventHandler(this.lbGroups_SelectedIndexChanged);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.lbGumps);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox1.Location = new System.Drawing.Point(4, 4);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(144, 256);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Gumps";
			// 
			// lbGumps
			// 
			this.lbGumps.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lbGumps.Location = new System.Drawing.Point(3, 16);
			this.lbGumps.Name = "lbGumps";
			this.lbGumps.Size = new System.Drawing.Size(138, 225);
			this.lbGumps.TabIndex = 0;
			this.lbGumps.SelectedIndexChanged += new System.EventHandler(this.lbGumps_SelectedIndexChanged);
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.bCancel);
			this.panel2.Controls.Add(this.bAdd);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel2.Location = new System.Drawing.Point(152, 350);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(424, 56);
			this.panel2.TabIndex = 1;
			// 
			// bCancel
			// 
			this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.bCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bCancel.Location = new System.Drawing.Point(288, 16);
			this.bCancel.Name = "bCancel";
			this.bCancel.Size = new System.Drawing.Size(80, 24);
			this.bCancel.TabIndex = 5;
			this.bCancel.Text = "Cancel";
			// 
			// bAdd
			// 
			this.bAdd.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.bAdd.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bAdd.Location = new System.Drawing.Point(56, 16);
			this.bAdd.Name = "bAdd";
			this.bAdd.Size = new System.Drawing.Size(80, 24);
			this.bAdd.TabIndex = 4;
			this.bAdd.Text = "Add";
			// 
			// splitter1
			// 
			this.splitter1.Location = new System.Drawing.Point(152, 0);
			this.splitter1.Name = "splitter1";
			this.splitter1.Size = new System.Drawing.Size(3, 350);
			this.splitter1.TabIndex = 2;
			this.splitter1.TabStop = false;
			// 
			// splitter2
			// 
			this.splitter2.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.splitter2.Location = new System.Drawing.Point(155, 347);
			this.splitter2.Name = "splitter2";
			this.splitter2.Size = new System.Drawing.Size(421, 3);
			this.splitter2.TabIndex = 3;
			this.splitter2.TabStop = false;
			// 
			// gumpPreview1
			// 
			this.gumpPreview1.BackColor = System.Drawing.SystemColors.AppWorkspace;
			this.gumpPreview1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.gumpPreview1.Image = null;
			this.gumpPreview1.Location = new System.Drawing.Point(0, 0);
			this.gumpPreview1.Name = "gumpPreview1";
			this.gumpPreview1.Size = new System.Drawing.Size(417, 343);
			this.gumpPreview1.TabIndex = 4;
			// 
			// panel3
			// 
			this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.panel3.Controls.Add(this.gumpPreview1);
			this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel3.Location = new System.Drawing.Point(155, 0);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(421, 347);
			this.panel3.TabIndex = 5;
			// 
			// GumpChooser
			// 
			this.AcceptButton = this.bAdd;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.bCancel;
			this.ClientSize = new System.Drawing.Size(576, 406);
			this.Controls.Add(this.panel3);
			this.Controls.Add(this.splitter2);
			this.Controls.Add(this.splitter1);
			this.Controls.Add(this.panel2);
			this.Controls.Add(this.panel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
			this.MinimumSize = new System.Drawing.Size(528, 392);
			this.Name = "GumpChooser";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "GumpChooser";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.GumpChooser_Closing);
			this.panel1.ResumeLayout(false);
			this.gbGroups.ResumeLayout(false);
			this.groupBox1.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			this.panel3.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		void loadIndexes()
		{
			
			FileStream fs = new FileStream(getFileDirectory(GumpPath)+"\\GumpIdx.mul",FileMode.Open,FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			byte[] barr = new byte[12];
			GumpIdx gidx;
			int id=0;

			while(true) {
				barr = br.ReadBytes(12);
				if (barr.Length < 12)
					break;
				gidx = new GumpIdx(id, barr);

				if (gidx.Lookup != 0xFFFFFFFF) {
					indexes.Add("0x"+Convert.ToString(id,16), gidx);
				}
				id++;
			}
			br.Close();
		}

		private void lbGumps_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			if (lbGumps.SelectedItem == null || !indexes.ContainsKey(lbGumps.SelectedItem))
				return;
			_selectedGump = new Gump((GumpIdx)indexes[lbGumps.SelectedItem], GumpPath);
			gumpPreview1.Image = _selectedGump.Image;
		}

		private void GumpChooser_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			//e.Cancel=true;
			//this.Hide();
		}

		private void lbGroups_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			string se = (string)lbGroups.SelectedItem;
			lbGumps.Items.Clear();
			if (se.Equals("All")) {
				string[] arr = new string[indexes.Count];
				indexes.Keys.CopyTo(arr, 0);
				Array.Sort(arr);
				lbGumps.Items.AddRange(arr);
			} else
				lbGumps.Items.AddRange(groups.getGroupItems(se));
		}

		private string getFileDirectory(string filepath)
		{
			int lasti = 0;
			for (int i=0; i<filepath.Length; i++) {
				if (filepath[i] == '\\')
					lasti = i;
			}
			return filepath.Substring(0, lasti);
		}

	}
}
