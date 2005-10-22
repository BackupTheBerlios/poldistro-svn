using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for GumpPreview.
	/// </summary>
	public class GumpPreview : System.Windows.Forms.UserControl
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		private Bitmap bitmap;

		public Bitmap Image {
			get { return bitmap; }
			set{
				bitmap = (Bitmap)value;
				this.Refresh();
			}
		}
		public GumpPreview()
		{
			// This call is required by the Windows.Forms Form Designer.
			InitializeComponent();

			// TODO: Add any initialization after the InitializeComponent call

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

		#region Component Designer generated code
		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			// 
			// GumpPreview
			// 
			this.Name = "GumpPreview";
			this.Size = new System.Drawing.Size(136, 112);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.GumpPreview_Paint);

		}
		#endregion

		private void GumpPreview_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			if (bitmap == null)
				return;
			int width=bitmap.Width;
			int height=bitmap.Height;
			int delimW = this.Size.Width/14;
			int delimH = this.Size.Height/14;
			double cut=0.0;
			/* Resize the picture */
			/* and maintain aspect ratio */
			if (width>this.Width-delimW)
			{
				cut=width/(this.Width-delimW);
				if(cut>1)
				{
					width=(int)(width-(width/cut));
					height=(int)(height-(height/cut));
				}
			}
			if (height > this.Height - delimH) {
				cut=height/(this.Height-delimH);
				if(cut > 1) {
					width = (int)(width-(width/cut));
					height = (int)(height-(height/cut));
				}
			}
			/* Centers the image */
			int centerPw, centerPh;
			int centerIw, centerIh;

			centerPw = this.Width/2;
			centerPh = this.Height/2;

			centerIw = width/2;
			centerIh = height/2;
			
			e.Graphics.DrawImage(bitmap, centerPw-centerIw,
				centerPh-centerIh, width, height);
		}


	}
}
