using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for GumpViewer.
	/// </summary>
	public delegate void selectedIndexChanged(object sender,int index);
	public delegate void selectedGumpChanged(object sender,Gump gump);
	public delegate void gumpAdded(object sender,ref Gump gump);
	public delegate void gumpRemoved(object sender,ref Gump gump);
	public delegate void gumpChanged(object sender);
	public delegate void gumpsSort(object sender);

	public class GumpViewer : System.Windows.Forms.UserControl
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		private ArrayList items;
		private Gump selectedGump;
		private int selectedIndex=-1;
		private GumpViewer _parent;
		private Gump _gmpMoved;
		private ResizableGump _gmpResized;
		private int _movedX, _movedY;

		public event selectedIndexChanged SelectedIndexChanged;
		public event selectedGumpChanged  SelectedGumpChanged;
		public event gumpRemoved GumpRemoved;
		public event gumpAdded GumpAdded;
		public event gumpChanged GumpChanged;
		public event gumpsSort GumpsSort;

		public Gump[] Gumps{
			get {
				Gump[] gtable = new Gump[items.Count];
				items.CopyTo(gtable);
				return gtable;
			}
			set {
				items.Clear();
				items.AddRange(value);
				this.Refresh();
			}
		}
		

		public int SelectedIndex{
			get {
				return selectedIndex;
			}
			set {
				if (selectedIndex >= 0
					&& selectedIndex< items.Count&&selectedIndex != (int)value) {
					selectedIndex = (int)value;
					selectedGump = (Gump)items[selectedIndex];
					riseOnSelectedIndexChangedEvent();
				}
			}
		}

		public Gump SelectedGump{
			get {
				return selectedGump;
			}
			set {
				IEnumerator ie = items.GetEnumerator();
				Gump cur;
				int ind = 0;
				while (ie.MoveNext()) {
					cur=(Gump)ie.Current;
					if (cur == (Gump)value) {
						selectedGump=cur;
						selectedIndex=ind;
						break;
					}
					ind++;
				}
				riseOnSelectedGumpChangedEvent();
			}
		}

		public GumpViewer()
		{
			items = new ArrayList();
			this.SetStyle(ControlStyles.AllPaintingInWmPaint 
				| ControlStyles.UserPaint 
				| ControlStyles.DoubleBuffer,
				true);
			InitializeComponent();
		}

		public GumpViewer(GumpViewer parent)
		{
			items=new ArrayList();
			this._parent=parent;
			this.SetStyle(ControlStyles.AllPaintingInWmPaint 
				| ControlStyles.UserPaint 
				| ControlStyles.DoubleBuffer,
			true);
			InitializeComponent();
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

		public void addGump(Gump gmp)
		{
			items.Add(gmp);
			gmp.SizeChanged+=new sizeChanged(gmp_SizeChanged);
			gmp.PriorityChanged+=new priorityChanged(gmp_PriorityChanged);
			riseGumpAddedEvent(ref gmp);
			SelectedIndex=items.Count-1;
			this.Refresh();
		}

		public void removeGump(Gump gmp)
		{
			int cnt=items.Count;
			items.Remove(gmp);
			selectedGump=null;
			selectedIndex=0;
			if (cnt>items.Count)
				riseGumpRemovedEvent(ref gmp);
			this.Refresh();
		}

		public void removeGump(int index)
		{
			if (index<0||index>=items.Count)
				return;
			Gump gmp = (Gump)items[index];
			int cnt=items.Count;
			items.RemoveAt(index);
			selectedGump=null;
			selectedIndex=0;
			if (cnt>items.Count)
				riseGumpRemovedEvent(ref gmp);

			this.Refresh();
		}

		public void removeSelectedGump()
		{
			removeGump(selectedIndex);
		}
		public PolGumpCode generateEscriptCode()
		{
			PolGumpCode pgc = new PolGumpCode();
			if (items.Count>0)
				pgc.TextGfx="";
			int tcount=0;
			for (int i=0; i<items.Count; i++) {
				if (items[i].GetType()==typeof(UOText)) {
					pgc.TextData += (((UOText)items[i]).Text)+"\n";
					pgc.TextGfx += items[i].ToString()+" "+(tcount++)+"\n";
				} else
					pgc.TextGfx+=items[i].ToString()+"\n";
			}
			return pgc;
		}
		#region Component Designer generated code
		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			// 
			// GumpViewer
			// 
			this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.Name = "GumpViewer";
			this.Size = new System.Drawing.Size(280, 208);
			this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GumpViewer_MouseUp);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.GumpViewer_Paint);
			this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.GumpViewer_MouseMove);
			this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GumpViewer_MouseDown);

		}
		#endregion

		private void GumpViewer_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			Gump gmp;
			ResizableGump rg;

			if (_parent != null)
			{
				Gump[] gmps = _parent.Gumps;
				for (int i=0; i < gmps.Length; i++) {
					if (gmps[i].GetType() == typeof(ResizableGump)) {
						rg = (ResizableGump)gmps[i];
						//e.Graphics.DrawImage(rg.Image, rg.X, rg.Y, rg.Width, rg.Height);
						for (int x = 0; x < rg.Width; x += rg.Image.Width) {
							for (int y = 0; y < rg.Height; y += rg.Image.Height) {
								e.Graphics.DrawImage(rg.Image, rg.X+x, rg.Y+y, rg.Width, rg.Height);
							}
						}
					} else
						//e.Graphics.DrawImage(gmps[i].Image, gmps[i].X,gmps[i].Y, gmps[i].Width, gmps[i].Height);
						e.Graphics.DrawImageUnscaled(gmps[i].Image, gmps[i].X, gmps[i].Y);
				}
			}
			IEnumerator ie = items.GetEnumerator();
			
			while (ie.MoveNext()) {
				if (ie.Current.GetType() == typeof(ResizableGump)) {
					rg = (ResizableGump)ie.Current;
					e.Graphics.DrawImage(rg.Image,rg.X,rg.Y,rg.Width,rg.Height);
				} else {
					gmp = (Gump)ie.Current;
					e.Graphics.DrawImage(gmp.Image, gmp.X, gmp.Y, gmp.Width, gmp.Height);
				}
			}
			if (selectedGump != null && _gmpMoved == null && _gmpResized == null) {
				if (selectedGump.GetType() == typeof(ResizableGump)) {
					rg = (ResizableGump)selectedGump;
					Pen p = new Pen(Brushes.Blue, 3);
					e.Graphics.DrawRectangle(p, rg.X, rg.Y, rg.Width, rg.Height);
				} else {
					Pen p = new Pen(Brushes.Blue, 3);
					e.Graphics.DrawRectangle(p, selectedGump.X, selectedGump.Y, selectedGump.Width,
						selectedGump.Height);
				}
			} else if (_gmpMoved != null) {
				if (_gmpMoved.GetType() == typeof(ResizableGump)) {
					rg = (ResizableGump)_gmpMoved;
					Pen p = new Pen(Brushes.Blue, 3);
					e.Graphics.DrawRectangle(p,rg.X,rg.Y,rg.Width,rg.Height);
				} else {
					Pen p = new Pen(Brushes.Blue, 3);
					e.Graphics.DrawRectangle(p,_gmpMoved.X,_gmpMoved.Y,_gmpMoved.Width,_gmpMoved.Height);				
				}
			} else if (_gmpResized != null) {
				Pen p = new Pen(Brushes.Blue, 3);
				e.Graphics.DrawRectangle(p,_gmpResized.X,_gmpResized.Y,_gmpResized.Width,_gmpResized.Height);
			}
		}

		protected void riseOnSelectedIndexChangedEvent()
		{
			if (SelectedIndexChanged!=null)
				SelectedIndexChanged(this,selectedIndex);
			this.Refresh();
		}

		protected void riseOnSelectedGumpChangedEvent()
		{
			if (SelectedGumpChanged!=null)
				SelectedGumpChanged(this,selectedGump);
			this.Refresh();
		}

		protected void riseGumpAddedEvent(ref Gump gump)
		{
			if (GumpAdded != null)
				GumpAdded(this,ref gump);
		}

		protected void riseGumpRemovedEvent(ref Gump gump)
		{
			if (GumpRemoved != null)
				GumpRemoved(this,ref gump);
		}
		protected void riseGumpChangedEvent(){
			if (GumpChanged != null)
				GumpChanged(this);
		}

		protected void riseGumpSortEvent(){
			if(GumpsSort != null)
				GumpsSort(this);
		}
		private void gmp_SizeChanged(object sender)
		{
			riseGumpChangedEvent();
			this.Refresh();
		}

		private void GumpViewer_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			if (e.Button != MouseButtons.Left)
				return;
			int oldIndex = selectedIndex;
			selectedGump = null;
			IEnumerator ie = items.GetEnumerator();
			Gump g;
			ResizableGump rg;
			int index = 0;
			selectedIndex = -1;
			while (ie.MoveNext()) {
				if (ie.Current.GetType() == typeof(ResizableGump)) {
					rg = (ResizableGump)ie.Current;
					if ((e.X >= rg.X + rg.Width - 2
						&& e.X <= rg.X + rg.Width+2)
						&& (e.Y >= rg.Y + rg.Height - 2
						&& e.Y <= rg.Y + rg.Height + 2)){
						_gmpResized=rg;
						selectedGump=rg;
						selectedIndex=index;
					} else if ((e.X >= rg.X && e.X <= rg.X + rg.Width)
						&& (e.Y >= rg.Y && e.Y <= rg.Y + rg.Height)) {
						selectedGump=rg;
						selectedIndex=index;
						_gmpResized=null;
					}
					index++;
				} else {
					g = (Gump)ie.Current;
					if ((e.X>=g.X&&e.X<=g.X+g.Width)&&(e.Y>=g.Y&&e.Y<=g.Y+g.Height)) {
						selectedGump=g;
						selectedIndex=index;
					}
					index++;
				}
			}
			if (selectedIndex != oldIndex) {
				riseOnSelectedIndexChangedEvent();
			} else if (selectedGump != null && _gmpResized == null) {
				_gmpMoved=selectedGump;
				_movedX=e.X-_gmpMoved.X;
				_movedY=e.Y-_gmpMoved.Y;
			}
			
		}

		private void GumpViewer_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			if (_gmpMoved!=null) {
				int x=e.X-_movedX;
				int y=e.Y-_movedY;

				if (x<0)
					x=0;	
				if(y<0)
					y=0;
				
				_gmpMoved.Y=y;
				_gmpMoved.X=x;

			} else if (_gmpResized != null) {
				int width=_gmpResized.Width-(_gmpResized.X+_gmpResized.Width-e.X);
				int height=_gmpResized.Height-(_gmpResized.Y+_gmpResized.Height-e.Y);
				if(width<5)
					width=5;
				if (height<5)
					height=5;

				_gmpResized.Height=height;
				_gmpResized.Width=width;
			} else if (selectedGump != null) {
				if (selectedGump.GetType() == typeof(ResizableGump)) {				
					ResizableGump rg=(ResizableGump)selectedGump;

					if ((e.X > rg.X && e.X <= rg.Width + rg.X)
						&& (e.Y > rg.Y && e.Y <= rg.Y + rg.Height))
						this.Cursor = Cursors.SizeAll;
					else if (rg != null && ((e.X >= rg.X - 2 + rg.Width
						&& e.X < rg.Width + rg.X + 3)
						&& (e.Y >= rg.Y + rg.Height - 2
						&& e.Y < rg.Y + rg.Height + 3)))
						this.Cursor=Cursors.SizeNWSE;
					else
						this.Cursor=Cursors.Default;
				} else {
					 if ((e.X > selectedGump.X && e.X <= selectedGump.Width + selectedGump.X)
						 && (e.Y > selectedGump.Y && e.Y <= selectedGump.Y + selectedGump.Height))
						this.Cursor=Cursors.SizeAll;
					else
						this.Cursor=Cursors.Default;
				}

			}
		}

		private void GumpViewer_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			_gmpMoved=null;
			_gmpResized=null;
			this.Cursor=Cursors.Default;
		}

		private void gmp_PriorityChanged(object sender)
		{
			items.Sort();
			riseGumpSortEvent();
			this.Refresh();
		}
	}
}
