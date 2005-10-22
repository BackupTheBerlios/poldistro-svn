using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for AboutForm.
	/// </summary>
	public class AboutForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox tbAbout;
		private System.Windows.Forms.Label lLatoch;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.LinkLabel llPOLWebsite;
		private System.Windows.Forms.Label label2;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public AboutForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

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
			this.tbAbout = new System.Windows.Forms.TextBox();
			this.lLatoch = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.llPOLWebsite = new System.Windows.Forms.LinkLabel();
			this.label2 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// tbAbout
			// 
			this.tbAbout.Location = new System.Drawing.Point(8, 8);
			this.tbAbout.Multiline = true;
			this.tbAbout.Name = "tbAbout";
			this.tbAbout.ReadOnly = true;
			this.tbAbout.Size = new System.Drawing.Size(384, 112);
			this.tbAbout.TabIndex = 3;
			this.tbAbout.Text = "POL Gump Designer, allows you to create GUMPs that can be used in POL emulator, w" +
				"ith certain ease.";
			// 
			// lLatoch
			// 
			this.lLatoch.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.lLatoch.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(161)));
			this.lLatoch.Location = new System.Drawing.Point(144, 128);
			this.lLatoch.Name = "lLatoch";
			this.lLatoch.Size = new System.Drawing.Size(128, 23);
			this.lLatoch.TabIndex = 1;
			this.lLatoch.Text = "Created by: Latoch";
			// 
			// label1
			// 
			this.label1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(161)));
			this.label1.Location = new System.Drawing.Point(132, 156);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(152, 23);
			this.label1.TabIndex = 1;
			this.label1.Text = "Maintained by: Melanius";
			// 
			// llPOLWebsite
			// 
			this.llPOLWebsite.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.llPOLWebsite.Location = new System.Drawing.Point(300, 180);
			this.llPOLWebsite.Name = "llPOLWebsite";
			this.llPOLWebsite.Size = new System.Drawing.Size(112, 23);
			this.llPOLWebsite.TabIndex = 2;
			this.llPOLWebsite.TabStop = true;
			this.llPOLWebsite.Text = "www.polserver.com";
			this.llPOLWebsite.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.llPOLWebsite_LinkClicked);
			// 
			// label2
			// 
			this.label2.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label2.Location = new System.Drawing.Point(364, 124);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(28, 23);
			this.label2.TabIndex = 4;
			this.label2.Text = "v0.2";
			// 
			// AboutForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(402, 200);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.llPOLWebsite);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.lLatoch);
			this.Controls.Add(this.tbAbout);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "AboutForm";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "About POL Gump Designer";
			this.Click += new System.EventHandler(this.AboutForm_Click);
			this.ResumeLayout(false);

		}
		#endregion

		private void AboutForm_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}

		private void llPOLWebsite_LinkClicked(object sender, System.Windows.Forms.LinkLabelLinkClickedEventArgs e)
		{
			llPOLWebsite.LinkVisited = true;
			System.Diagnostics.Process.Start("http://www.polserver.com");
		}

	}
}
