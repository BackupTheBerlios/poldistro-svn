using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for CodeViewer.
	/// </summary>
	public class CodeViewer : System.Windows.Forms.Form
	{
		private System.Windows.Forms.RichTextBox rtbText;
		private System.Windows.Forms.ContextMenu cmTextOptions;
		private System.Windows.Forms.MenuItem miSelectAll;
		private System.Windows.Forms.MenuItem miCopy;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public string CVText{
			get{
				return rtbText.Text;
			}
			set{
				rtbText.Text=(string)value;
			}
		}

		public CodeViewer()
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
			this.rtbText = new System.Windows.Forms.RichTextBox();
			this.cmTextOptions = new System.Windows.Forms.ContextMenu();
			this.miSelectAll = new System.Windows.Forms.MenuItem();
			this.miCopy = new System.Windows.Forms.MenuItem();
			this.SuspendLayout();
			// 
			// rtbText
			// 
			this.rtbText.ContextMenu = this.cmTextOptions;
			this.rtbText.Dock = System.Windows.Forms.DockStyle.Fill;
			this.rtbText.Font = new System.Drawing.Font("Courier New", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(161)));
			this.rtbText.Location = new System.Drawing.Point(4, 4);
			this.rtbText.Name = "rtbText";
			this.rtbText.ReadOnly = true;
			this.rtbText.Size = new System.Drawing.Size(360, 358);
			this.rtbText.TabIndex = 1;
			this.rtbText.Text = "";
			// 
			// cmTextOptions
			// 
			this.cmTextOptions.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																						  this.miSelectAll,
																						  this.miCopy});
			// 
			// miSelectAll
			// 
			this.miSelectAll.Index = 0;
			this.miSelectAll.Text = "Select All";
			this.miSelectAll.Click += new System.EventHandler(this.miSelectAll_Click);
			// 
			// miCopy
			// 
			this.miCopy.Index = 1;
			this.miCopy.Text = "Copy";
			this.miCopy.Click += new System.EventHandler(this.miCopy_Click);
			// 
			// CodeViewer
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(368, 366);
			this.Controls.Add(this.rtbText);
			this.DockPadding.All = 4;
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
			this.MinimumSize = new System.Drawing.Size(376, 392);
			this.Name = "CodeViewer";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Code Viewer";
			this.ResumeLayout(false);

		}
		#endregion

		private void miSelectAll_Click(object sender, System.EventArgs e)
		{
			rtbText.SelectAll();
		}

		private void miCopy_Click(object sender, System.EventArgs e)
		{
			rtbText.Copy();
		}
	}
}
