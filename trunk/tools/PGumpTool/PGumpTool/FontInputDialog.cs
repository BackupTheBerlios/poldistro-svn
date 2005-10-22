using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for FontInputDialog.
	/// </summary>
	public class FontInputDialog : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox tbText;
		private System.Windows.Forms.Button bOk;
		private System.Windows.Forms.Button bCancel;
		private PGumpTool.GumpPreview gumpPreview1;
		private UOText uotext;
		private string pathToFonts;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public UOText Uotext
		{
			get { return uotext; }
		}

		public FontInputDialog(string pathToFonts)
		{
			//
			// Required for Windows Form Designer support
			//
			this.pathToFonts=pathToFonts;
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
			this.tbText = new System.Windows.Forms.TextBox();
			this.bOk = new System.Windows.Forms.Button();
			this.bCancel = new System.Windows.Forms.Button();
			this.gumpPreview1 = new PGumpTool.GumpPreview();
			this.SuspendLayout();
			// 
			// tbText
			// 
			this.tbText.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.tbText.Location = new System.Drawing.Point(8, 8);
			this.tbText.Name = "tbText";
			this.tbText.Size = new System.Drawing.Size(480, 20);
			this.tbText.TabIndex = 0;
			this.tbText.Text = "";
			this.tbText.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbText_KeyPress);
			this.tbText.TextChanged += new System.EventHandler(this.tbText_TextChanged);
			// 
			// bOk
			// 
			this.bOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.bOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bOk.Location = new System.Drawing.Point(152, 64);
			this.bOk.Name = "bOk";
			this.bOk.TabIndex = 2;
			this.bOk.Text = "Ok";
			// 
			// bCancel
			// 
			this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.bCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bCancel.Location = new System.Drawing.Point(256, 64);
			this.bCancel.Name = "bCancel";
			this.bCancel.TabIndex = 3;
			this.bCancel.Text = "Cancel";
			// 
			// gumpPreview1
			// 
			this.gumpPreview1.Image = null;
			this.gumpPreview1.Location = new System.Drawing.Point(8, 32);
			this.gumpPreview1.Name = "gumpPreview1";
			this.gumpPreview1.Size = new System.Drawing.Size(480, 24);
			this.gumpPreview1.TabIndex = 4;
			// 
			// FontInputDialog
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(498, 96);
			this.Controls.Add(this.gumpPreview1);
			this.Controls.Add(this.bCancel);
			this.Controls.Add(this.bOk);
			this.Controls.Add(this.tbText);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "FontInputDialog";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Font Input";
			this.ResumeLayout(false);

		}
		#endregion

		private void tbText_TextChanged(object sender, System.EventArgs e)
		{
			if (uotext == null && !tbText.Text.Equals(""))
				uotext = new UOText(tbText.Text, pathToFonts);
			else if (!tbText.Text.Equals(""))
				uotext.Text = tbText.Text;
			else
				uotext = null;

			try {
				gumpPreview1.Image = uotext.Image;
			} catch (Exception exc) {
			}
		}

		private void tbText_KeyPress(object sender, System.Windows.Forms.KeyPressEventArgs e)
		{
			if ((e.KeyChar < 32 || e.KeyChar > 255) && e.KeyChar != 8)
				e.Handled=true;
		}

	}
}
