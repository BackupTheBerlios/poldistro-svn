using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Configuration;
using System.Xml.Serialization;
using Microsoft.Win32;

namespace PGumpTool
{
	/// <summary>
	/// Summary description for MainForm.
	/// </summary>
	public class MainForm : System.Windows.Forms.Form
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private System.Windows.Forms.MenuItem miFile;
		private System.Windows.Forms.MenuItem miOpen;
		private System.Windows.Forms.MenuItem miSave;
		private System.Windows.Forms.MenuItem miSaveAs;
		private System.Windows.Forms.MenuItem miExport;
		private System.Windows.Forms.MenuItem muExportBmp;
		private System.Windows.Forms.MenuItem miExportJpg;
		private System.Windows.Forms.MenuItem menuItem8;
		private System.Windows.Forms.MenuItem miExit;
		private System.Windows.Forms.MenuItem miEscript;
		private System.Windows.Forms.MenuItem miGenerateCode;
		private System.Windows.Forms.StatusBar sbMain;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Splitter splitter1;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.Splitter splitter2;
		private System.Windows.Forms.ComboBox cbItems;
		private System.Windows.Forms.MainMenu mmFrame;
		private System.Windows.Forms.ContextMenu cmTabMenu;
		private System.Windows.Forms.MenuItem menuItem3;
		private PGumpTool.GumpViewer gumpViewer1;
		private System.Windows.Forms.MenuItem menuItem6;
		private System.Windows.Forms.MenuItem miAddGump;
		private System.Windows.Forms.MenuItem miRemoveGump;
		private System.Windows.Forms.MenuItem miGenerateCodeC;
		private System.Windows.Forms.MenuItem miAddPage;
		private System.Windows.Forms.PropertyGrid pgProperties;
		private System.Windows.Forms.Panel panel4;
		private System.Windows.Forms.Button bAddButton;
		private System.Windows.Forms.Button bAddGump;
		private System.Windows.Forms.Panel panel3;
		private System.Windows.Forms.Button bAddText;
		private System.Windows.Forms.Button bAddResize;

		private GumpChooser gumpChooser;

		private string pathToGumps;
		private System.Windows.Forms.MenuItem miCopy;
		private System.Windows.Forms.MenuItem miCut;
		private System.Windows.Forms.MenuItem miDelete;
		private System.Windows.Forms.MenuItem miPaste;
		private string pathToFonts;
		private System.Windows.Forms.MenuItem miHelp;
		private System.Windows.Forms.MenuItem miUndo;
		private System.Windows.Forms.MenuItem miRedo;
		private System.Windows.Forms.MenuItem menuItem7;
		private System.Windows.Forms.MenuItem miAbout;
		private System.Windows.Forms.MenuItem miEdit;
		private System.Windows.Forms.MenuItem miSupportForum;
		private string saveFileName;

		public MainForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			InitializePaths();

			gumpViewer1.SelectedGumpChanged+=new selectedGumpChanged(gumpViewer1_SelectedGumpChanged);
			gumpViewer1.SelectedIndexChanged+=new selectedIndexChanged(gumpViewer1_SelectedIndexChanged);
			gumpViewer1.GumpAdded+=new gumpAdded(gumpViewer1_GumpAdded);
			gumpViewer1.GumpRemoved+=new gumpRemoved(gumpViewer1_GumpRemoved);
			gumpViewer1.GumpChanged+=new gumpChanged(gumpViewer1_GumpChanged);
			gumpViewer1.GumpsSort+=new gumpsSort(gumpViewer1_GumpsSort);
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
				if (components != null) 
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
			this.mmFrame = new System.Windows.Forms.MainMenu();
			this.miFile = new System.Windows.Forms.MenuItem();
			this.miOpen = new System.Windows.Forms.MenuItem();
			this.miSave = new System.Windows.Forms.MenuItem();
			this.miSaveAs = new System.Windows.Forms.MenuItem();
			this.miExport = new System.Windows.Forms.MenuItem();
			this.muExportBmp = new System.Windows.Forms.MenuItem();
			this.miExportJpg = new System.Windows.Forms.MenuItem();
			this.menuItem8 = new System.Windows.Forms.MenuItem();
			this.miExit = new System.Windows.Forms.MenuItem();
			this.miEdit = new System.Windows.Forms.MenuItem();
			this.miUndo = new System.Windows.Forms.MenuItem();
			this.miRedo = new System.Windows.Forms.MenuItem();
			this.menuItem7 = new System.Windows.Forms.MenuItem();
			this.miCut = new System.Windows.Forms.MenuItem();
			this.miCopy = new System.Windows.Forms.MenuItem();
			this.miPaste = new System.Windows.Forms.MenuItem();
			this.miDelete = new System.Windows.Forms.MenuItem();
			this.miEscript = new System.Windows.Forms.MenuItem();
			this.miGenerateCode = new System.Windows.Forms.MenuItem();
			this.miHelp = new System.Windows.Forms.MenuItem();
			this.miAbout = new System.Windows.Forms.MenuItem();
			this.sbMain = new System.Windows.Forms.StatusBar();
			this.panel1 = new System.Windows.Forms.Panel();
			this.panel3 = new System.Windows.Forms.Panel();
			this.panel4 = new System.Windows.Forms.Panel();
			this.bAddText = new System.Windows.Forms.Button();
			this.bAddButton = new System.Windows.Forms.Button();
			this.bAddResize = new System.Windows.Forms.Button();
			this.bAddGump = new System.Windows.Forms.Button();
			this.splitter2 = new System.Windows.Forms.Splitter();
			this.panel2 = new System.Windows.Forms.Panel();
			this.pgProperties = new System.Windows.Forms.PropertyGrid();
			this.cbItems = new System.Windows.Forms.ComboBox();
			this.splitter1 = new System.Windows.Forms.Splitter();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.gumpViewer1 = new PGumpTool.GumpViewer();
			this.cmTabMenu = new System.Windows.Forms.ContextMenu();
			this.miAddPage = new System.Windows.Forms.MenuItem();
			this.menuItem6 = new System.Windows.Forms.MenuItem();
			this.miAddGump = new System.Windows.Forms.MenuItem();
			this.miRemoveGump = new System.Windows.Forms.MenuItem();
			this.menuItem3 = new System.Windows.Forms.MenuItem();
			this.miGenerateCodeC = new System.Windows.Forms.MenuItem();
			this.miSupportForum = new System.Windows.Forms.MenuItem();
			this.panel1.SuspendLayout();
			this.panel3.SuspendLayout();
			this.panel4.SuspendLayout();
			this.panel2.SuspendLayout();
			this.tabControl1.SuspendLayout();
			this.tabPage1.SuspendLayout();
			this.SuspendLayout();
			// 
			// mmFrame
			// 
			this.mmFrame.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					this.miFile,
																					this.miEdit,
																					this.miEscript,
																					this.miHelp});
			// 
			// miFile
			// 
			this.miFile.Index = 0;
			this.miFile.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				   this.miOpen,
																				   this.miSave,
																				   this.miSaveAs,
																				   this.miExport,
																				   this.menuItem8,
																				   this.miExit});
			this.miFile.Text = "&File";
			// 
			// miOpen
			// 
			this.miOpen.Index = 0;
			this.miOpen.Shortcut = System.Windows.Forms.Shortcut.CtrlO;
			this.miOpen.Text = "Open";
			this.miOpen.Click += new System.EventHandler(this.miOpen_Click);
			// 
			// miSave
			// 
			this.miSave.Index = 1;
			this.miSave.Shortcut = System.Windows.Forms.Shortcut.CtrlS;
			this.miSave.Text = "Save";
			this.miSave.Click += new System.EventHandler(this.miSave_Click);
			// 
			// miSaveAs
			// 
			this.miSaveAs.Index = 2;
			this.miSaveAs.Text = "Save As";
			this.miSaveAs.Click += new System.EventHandler(this.miSaveAs_Click);
			// 
			// miExport
			// 
			this.miExport.Index = 3;
			this.miExport.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.muExportBmp,
																					 this.miExportJpg});
			this.miExport.Text = "Export to";
			// 
			// muExportBmp
			// 
			this.muExportBmp.Index = 0;
			this.muExportBmp.Text = "BMP";
			// 
			// miExportJpg
			// 
			this.miExportJpg.Index = 1;
			this.miExportJpg.Text = "JPG";
			// 
			// menuItem8
			// 
			this.menuItem8.Index = 4;
			this.menuItem8.Text = "-";
			// 
			// miExit
			// 
			this.miExit.Index = 5;
			this.miExit.Text = "Exit";
			this.miExit.Click += new System.EventHandler(this.miExit_Click);
			// 
			// miEdit
			// 
			this.miEdit.Index = 1;
			this.miEdit.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				   this.miUndo,
																				   this.miRedo,
																				   this.menuItem7,
																				   this.miCut,
																				   this.miCopy,
																				   this.miPaste,
																				   this.miDelete});
			this.miEdit.Text = "&Edit";
			// 
			// miUndo
			// 
			this.miUndo.Enabled = false;
			this.miUndo.Index = 0;
			this.miUndo.Shortcut = System.Windows.Forms.Shortcut.CtrlZ;
			this.miUndo.Text = "&Undo";
			// 
			// miRedo
			// 
			this.miRedo.Enabled = false;
			this.miRedo.Index = 1;
			this.miRedo.Shortcut = System.Windows.Forms.Shortcut.CtrlY;
			this.miRedo.Text = "&Redo";
			// 
			// menuItem7
			// 
			this.menuItem7.Enabled = false;
			this.menuItem7.Index = 2;
			this.menuItem7.Text = "-";
			// 
			// miCut
			// 
			this.miCut.Enabled = false;
			this.miCut.Index = 3;
			this.miCut.Shortcut = System.Windows.Forms.Shortcut.CtrlX;
			this.miCut.Text = "Cu&t";
			// 
			// miCopy
			// 
			this.miCopy.Enabled = false;
			this.miCopy.Index = 4;
			this.miCopy.Shortcut = System.Windows.Forms.Shortcut.CtrlX;
			this.miCopy.Text = "&Copy";
			// 
			// miPaste
			// 
			this.miPaste.Enabled = false;
			this.miPaste.Index = 5;
			this.miPaste.Shortcut = System.Windows.Forms.Shortcut.CtrlV;
			this.miPaste.Text = "&Paste";
			// 
			// miDelete
			// 
			this.miDelete.Enabled = false;
			this.miDelete.Index = 6;
			this.miDelete.Shortcut = System.Windows.Forms.Shortcut.Del;
			this.miDelete.Text = "&Delete";
			// 
			// miEscript
			// 
			this.miEscript.Index = 2;
			this.miEscript.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					  this.miGenerateCode});
			this.miEscript.Text = "E&Script";
			// 
			// miGenerateCode
			// 
			this.miGenerateCode.Index = 0;
			this.miGenerateCode.Text = "Generate Code";
			this.miGenerateCode.Click += new System.EventHandler(this.miGenerateCode_Click);
			// 
			// miHelp
			// 
			this.miHelp.Index = 3;
			this.miHelp.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				   this.miSupportForum,
																				   this.miAbout});
			this.miHelp.Text = "&Help";
			// 
			// miAbout
			// 
			this.miAbout.Index = 1;
			this.miAbout.Text = "&About...";
			this.miAbout.Click += new System.EventHandler(this.miAbout_Click);
			// 
			// sbMain
			// 
			this.sbMain.Location = new System.Drawing.Point(0, 489);
			this.sbMain.Name = "sbMain";
			this.sbMain.Size = new System.Drawing.Size(656, 16);
			this.sbMain.TabIndex = 0;
			// 
			// panel1
			// 
			this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.panel1.Controls.Add(this.panel3);
			this.panel1.Controls.Add(this.splitter2);
			this.panel1.Controls.Add(this.panel2);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Right;
			this.panel1.Location = new System.Drawing.Point(480, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(176, 489);
			this.panel1.TabIndex = 1;
			// 
			// panel3
			// 
			this.panel3.Controls.Add(this.panel4);
			this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel3.Location = new System.Drawing.Point(0, 328);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(174, 159);
			this.panel3.TabIndex = 2;
			// 
			// panel4
			// 
			this.panel4.Controls.Add(this.bAddText);
			this.panel4.Controls.Add(this.bAddButton);
			this.panel4.Controls.Add(this.bAddResize);
			this.panel4.Controls.Add(this.bAddGump);
			this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel4.Location = new System.Drawing.Point(0, 0);
			this.panel4.Name = "panel4";
			this.panel4.Size = new System.Drawing.Size(174, 159);
			this.panel4.TabIndex = 2;
			// 
			// bAddText
			// 
			this.bAddText.Dock = System.Windows.Forms.DockStyle.Top;
			this.bAddText.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bAddText.Location = new System.Drawing.Point(0, 72);
			this.bAddText.Name = "bAddText";
			this.bAddText.Size = new System.Drawing.Size(174, 24);
			this.bAddText.TabIndex = 2;
			this.bAddText.Text = "Add Text";
			this.bAddText.Click += new System.EventHandler(this.bAddText_Click);
			// 
			// bAddButton
			// 
			this.bAddButton.Dock = System.Windows.Forms.DockStyle.Top;
			this.bAddButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bAddButton.Location = new System.Drawing.Point(0, 48);
			this.bAddButton.Name = "bAddButton";
			this.bAddButton.Size = new System.Drawing.Size(174, 24);
			this.bAddButton.TabIndex = 1;
			this.bAddButton.Text = "Add Button";
			this.bAddButton.Click += new System.EventHandler(this.bAddButton_Click);
			// 
			// bAddResize
			// 
			this.bAddResize.Dock = System.Windows.Forms.DockStyle.Top;
			this.bAddResize.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bAddResize.Location = new System.Drawing.Point(0, 24);
			this.bAddResize.Name = "bAddResize";
			this.bAddResize.Size = new System.Drawing.Size(174, 24);
			this.bAddResize.TabIndex = 3;
			this.bAddResize.Text = "Add Resize Pic";
			this.bAddResize.Click += new System.EventHandler(this.bAddResize_Click);
			// 
			// bAddGump
			// 
			this.bAddGump.Dock = System.Windows.Forms.DockStyle.Top;
			this.bAddGump.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bAddGump.Location = new System.Drawing.Point(0, 0);
			this.bAddGump.Name = "bAddGump";
			this.bAddGump.Size = new System.Drawing.Size(174, 24);
			this.bAddGump.TabIndex = 0;
			this.bAddGump.Text = "Add Gump";
			this.bAddGump.Click += new System.EventHandler(this.bAddGump_Click);
			// 
			// splitter2
			// 
			this.splitter2.Dock = System.Windows.Forms.DockStyle.Top;
			this.splitter2.Location = new System.Drawing.Point(0, 320);
			this.splitter2.Name = "splitter2";
			this.splitter2.Size = new System.Drawing.Size(174, 8);
			this.splitter2.TabIndex = 1;
			this.splitter2.TabStop = false;
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.pgProperties);
			this.panel2.Controls.Add(this.cbItems);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel2.Location = new System.Drawing.Point(0, 0);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(174, 320);
			this.panel2.TabIndex = 0;
			// 
			// pgProperties
			// 
			this.pgProperties.CommandsVisibleIfAvailable = true;
			this.pgProperties.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pgProperties.LargeButtons = false;
			this.pgProperties.LineColor = System.Drawing.SystemColors.ScrollBar;
			this.pgProperties.Location = new System.Drawing.Point(0, 21);
			this.pgProperties.Name = "pgProperties";
			this.pgProperties.Size = new System.Drawing.Size(174, 299);
			this.pgProperties.TabIndex = 1;
			this.pgProperties.Text = "pgProperties";
			this.pgProperties.ViewBackColor = System.Drawing.SystemColors.Window;
			this.pgProperties.ViewForeColor = System.Drawing.SystemColors.WindowText;
			// 
			// cbItems
			// 
			this.cbItems.Dock = System.Windows.Forms.DockStyle.Top;
			this.cbItems.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbItems.Location = new System.Drawing.Point(0, 0);
			this.cbItems.Name = "cbItems";
			this.cbItems.Size = new System.Drawing.Size(174, 21);
			this.cbItems.TabIndex = 0;
			this.cbItems.SelectedIndexChanged += new System.EventHandler(this.cbItems_SelectedIndexChanged);
			// 
			// splitter1
			// 
			this.splitter1.Dock = System.Windows.Forms.DockStyle.Right;
			this.splitter1.Location = new System.Drawing.Point(477, 0);
			this.splitter1.Name = "splitter1";
			this.splitter1.Size = new System.Drawing.Size(3, 489);
			this.splitter1.TabIndex = 2;
			this.splitter1.TabStop = false;
			// 
			// tabControl1
			// 
			this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
			this.tabControl1.Controls.Add(this.tabPage1);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(477, 489);
			this.tabControl1.TabIndex = 3;
			this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
			// 
			// tabPage1
			// 
			this.tabPage1.AutoScroll = true;
			this.tabPage1.BackColor = System.Drawing.SystemColors.AppWorkspace;
			this.tabPage1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.tabPage1.Controls.Add(this.gumpViewer1);
			this.tabPage1.Location = new System.Drawing.Point(4, 25);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Size = new System.Drawing.Size(469, 460);
			this.tabPage1.TabIndex = 0;
			this.tabPage1.Text = "Page 0";
			// 
			// gumpViewer1
			// 
			this.gumpViewer1.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.gumpViewer1.ContextMenu = this.cmTabMenu;
			this.gumpViewer1.Gumps = new PGumpTool.Gump[0];
			this.gumpViewer1.Location = new System.Drawing.Point(0, 0);
			this.gumpViewer1.Name = "gumpViewer1";
			this.gumpViewer1.SelectedGump = null;
			this.gumpViewer1.SelectedIndex = -1;
			this.gumpViewer1.Size = new System.Drawing.Size(640, 480);
			this.gumpViewer1.TabIndex = 0;
			// 
			// cmTabMenu
			// 
			this.cmTabMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					  this.miAddPage,
																					  this.menuItem6,
																					  this.miAddGump,
																					  this.miRemoveGump,
																					  this.menuItem3,
																					  this.miGenerateCodeC});
			// 
			// miAddPage
			// 
			this.miAddPage.Index = 0;
			this.miAddPage.Text = "Add page";
			this.miAddPage.Click += new System.EventHandler(this.miAddPage_Click);
			// 
			// menuItem6
			// 
			this.menuItem6.Index = 1;
			this.menuItem6.Text = "-";
			// 
			// miAddGump
			// 
			this.miAddGump.Index = 2;
			this.miAddGump.Text = "Add gump";
			this.miAddGump.Click += new System.EventHandler(this.bAddGump_Click);
			// 
			// miRemoveGump
			// 
			this.miRemoveGump.Index = 3;
			this.miRemoveGump.Text = "Remove gump";
			this.miRemoveGump.Click += new System.EventHandler(this.miRemoveGump_Click);
			// 
			// menuItem3
			// 
			this.menuItem3.Index = 4;
			this.menuItem3.Text = "-";
			// 
			// miGenerateCodeC
			// 
			this.miGenerateCodeC.Index = 5;
			this.miGenerateCodeC.Text = "Generate code";
			this.miGenerateCodeC.Click += new System.EventHandler(this.miGenerateCode_Click);
			// 
			// miSupportForum
			// 
			this.miSupportForum.Index = 0;
			this.miSupportForum.Text = "Support Forum";
			this.miSupportForum.Click += new System.EventHandler(this.miSupportForum_Click);
			// 
			// MainForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(656, 505);
			this.ContextMenu = this.cmTabMenu;
			this.Controls.Add(this.tabControl1);
			this.Controls.Add(this.splitter1);
			this.Controls.Add(this.panel1);
			this.Controls.Add(this.sbMain);
			this.Menu = this.mmFrame;
			this.Name = "MainForm";
			this.Text = "POL Gump Designer";
			this.panel1.ResumeLayout(false);
			this.panel3.ResumeLayout(false);
			this.panel4.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			this.tabControl1.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new MainForm());
		}

		private void miExit_Click(object sender, System.EventArgs e)
		{
			System.Environment.Exit(0);
		}

		private void bAddGump_Click(object sender, System.EventArgs e)
		{
			if (gumpChooser==null)
				gumpChooser = new GumpChooser(pathToGumps);
			if (gumpChooser.ShowDialog(this)!=DialogResult.Cancel&&gumpChooser.SelectedIndex!=null) {
				Gump gm = new Gump(gumpChooser.SelectedIndex, pathToGumps);
				((GumpViewer)tabControl1.SelectedTab.Controls[0]).addGump(gm);
			}
		}

		private void bAddResize_Click(object sender, System.EventArgs e)
		{
			if (gumpChooser==null)
				gumpChooser = new GumpChooser(pathToGumps);
			if (gumpChooser.ShowDialog(this)!=DialogResult.Cancel&&gumpChooser.SelectedIndex!=null) {
				ResizableGump rg = new ResizableGump(gumpChooser.SelectedIndex, pathToGumps);
				((GumpViewer)tabControl1.SelectedTab.Controls[0]).addGump(rg);
			}
			
		}

		private void bAddButton_Click(object sender, System.EventArgs e)
		{
			if (gumpChooser==null)
				gumpChooser = new GumpChooser(pathToGumps);
			DialogResult dl = gumpChooser.ShowDialog(this);
			if (dl!=DialogResult.Cancel&&gumpChooser.SelectedIndex!=null) {
				GumpButton gb = new GumpButton(gumpChooser.SelectedIndex, pathToGumps);
				((GumpViewer)tabControl1.SelectedTab.Controls[0]).addGump(gb);
			}
		}

		private void bAddText_Click(object sender, System.EventArgs e)
		{
			
			FontInputDialog fid = new FontInputDialog(pathToFonts);
			if(fid.ShowDialog()==DialogResult.OK&&fid.Uotext!=null)
				((GumpViewer)tabControl1.SelectedTab.Controls[0]).addGump(fid.Uotext);
		}

		private void gumpViewer1_SelectedGumpChanged(object sender, Gump gump)
		{
			if (gump==null)
			{
				this.cbItems.SelectedItem=null;
				pgProperties.SelectedObject=null;
				return;
			}
				
			for(int i=0; i<cbItems.Items.Count; i++)
			{
				if(gump==(Gump)cbItems.Items[i])
					cbItems.SelectedIndex=i;
			}
		}

		private void gumpViewer1_SelectedIndexChanged(object sender, int index)
		{
			if (index==-1)
			{
				cbItems.SelectedItem=null;
				pgProperties.SelectedObject=null;
				return;
			}
			if (index<cbItems.Items.Count)
				cbItems.SelectedIndex=index;
		}

		private void gumpViewer1_GumpAdded(object sender, ref Gump gump)
		{
			cbItems.Items.Add(gump);
		}

		private void gumpViewer1_GumpRemoved(object sender, ref Gump gump)
		{
			pgProperties.SelectedObject=null;
			cbItems.Items.Remove(gump);
		}

		private void miRemoveGump_Click(object sender, System.EventArgs e)
		{
			((GumpViewer)tabControl1.SelectedTab.Controls[0]).removeSelectedGump();
		}

		private void cbItems_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			((GumpViewer)tabControl1.SelectedTab.Controls[0]).SelectedIndex=cbItems.SelectedIndex;
			pgProperties.SelectedObject=cbItems.SelectedItem;
		}

		private void miAddPage_Click(object sender, System.EventArgs e)
		{
			TabPage tp = new TabPage("Page " + tabControl1.TabPages.Count);
			GumpViewer gv = new GumpViewer(((GumpViewer)tabControl1.TabPages[0].Controls[0]));
			gv.Dock = DockStyle.None;
			tp.Controls.Add(gv);
			tp.BorderStyle = tabPage1.BorderStyle;
			tp.BackColor = tabPage1.BackColor;
			tp.AutoScroll = tabPage1.AutoScroll;
			gv.Size = gumpViewer1.Size;
			gv.SelectedGumpChanged += new selectedGumpChanged(gumpViewer1_SelectedGumpChanged);
			gv.SelectedIndexChanged += new selectedIndexChanged(gumpViewer1_SelectedIndexChanged);
			gv.GumpAdded += new gumpAdded(gumpViewer1_GumpAdded);
			gv.GumpRemoved += new gumpRemoved(gumpViewer1_GumpRemoved);
			gv.GumpChanged += new gumpChanged(gumpViewer1_GumpChanged);
			gv.GumpsSort += new gumpsSort(gumpViewer1_GumpsSort);
			gv.ContextMenu = cmTabMenu;
			this.tabControl1.TabPages.Add(tp);
		}

		private void tabControl1_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			pgProperties.SelectedObject=null;
			cbItems.Items.Clear();
			try
			{
				cbItems.Items.AddRange(((GumpViewer)tabControl1.SelectedTab.Controls[0]).Gumps);
				cbItems.SelectedIndex=((GumpViewer)tabControl1.SelectedTab.Controls[0]).SelectedIndex;
			}
			catch
			{
			}
		}
		private void gumpViewer1_GumpChanged(object sender)
		{
			pgProperties.Refresh();
			cbItems.Refresh();
		}

		private void gumpViewer1_GumpsSort(object sender)
		{
			this.cbItems.Items.Clear();
			this.cbItems.Items.AddRange(((GumpViewer)tabControl1.SelectedTab.Controls[0]).Gumps);
		}

		private void miGenerateCode_Click(object sender, System.EventArgs e)
		{
			CodeViewer cv = new CodeViewer();
			//cv.CVText=((GumpViewer)tabControl1.SelectedTab.Controls[0]).generateEscriptCode();
			string gfx = "", data = "", other = "";
			int textid = 0;
			PolGumpCode pgc;
			gfx += "var gfxlayout:={\n";
			data += "var gfxdata:={\n";
			for (int i=0; i<tabControl1.TabCount; i++) {
				pgc = ((GumpViewer)tabControl1.TabPages[i].Controls[0]).generateEscriptCode();
				gfx += "\t\"PAGE "+i+"\",\n";
				if (pgc.TextGfx != null) {
					string[] arr=pgc.TextGfx.Split(new char[]{'\n'});
					for (int j=0; j<arr.Length-1; j++) {
						gfx+="\t\""+arr[j]+"\",\n";	
					}
				}
				if (pgc.TextData!=null) {
					string[] arr=pgc.TextData.Split(new char[]{'\n'});
					for (int j=0; j<arr.Length-1; j++) {
						data+="\t\""+arr[j]+"\",\n";
						textid++;
					}
				}
			}
			if (gfx.EndsWith(",\n"))
				gfx=gfx.Substring(0,gfx.Length-2) + "\n";
			if (data.EndsWith(",\n"))
				data=data.Substring(0,data.Length-2) + "\n";
			gfx += "}\n";
			data += "}";
			cv.CVText=gfx+data;
			//cv.CVText+=data;
			cv.ShowDialog();
		}
		
		private void InitializePaths()
		{
			try {
				pathToGumps = ConfigurationSettings.AppSettings["PathToGumpsMul"];
				pathToFonts = ConfigurationSettings.AppSettings["PathToFontsMul"];
			} catch (Exception exc) {
			}

			if (pathToFonts == null || pathToGumps == null) {
				string pathToUO=Globals.getUOPath();

				if (pathToUO == null) {
					MessageBox.Show(this,"Cannot locate files directory. Please check program configuration.","Error finging paths",MessageBoxButtons.OK,MessageBoxIcon.Error);
					System.Environment.Exit(1);
				}
				if (pathToFonts == null) {
					pathToFonts=pathToUO + "\\fonts.mul";
				}
				if (pathToGumps == null) {
					pathToGumps=pathToUO + "\\gumpart.mul";
				}
			}

			if (!File.Exists(pathToGumps)) {
				MessageBox.Show(this, "File "+pathToGumps+" not found. Please check program configuration.","Path error",MessageBoxButtons.OK,MessageBoxIcon.Error);
				System.Environment.Exit(1);
			}
			if (!File.Exists(pathToFonts)) {
				MessageBox.Show(this, "File "+pathToFonts+" not found. Please check program configuration.","Path error",MessageBoxButtons.OK,MessageBoxIcon.Error);
				System.Environment.Exit(1);
			}
			Globals.fontPath=pathToFonts;
		}

		private void miSaveAs_Click(object sender, System.EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.Filter="Pol Gump Tool Files(*.pgt)|*.pgt|All Files(*.*)|*.*";
			if(DialogResult.Cancel==sfd.ShowDialog(this))
				return;
			saveFileName = sfd.FileName;
			serializeGumps(saveFileName);
		}

		private void miSave_Click(object sender, System.EventArgs e)
		{
			if (saveFileName == null || saveFileName == "") {
				miSaveAs_Click(sender, e);
				return;
			}
			serializeGumps(saveFileName);
		}

		private void miOpen_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter="Pol Gump Tool Files(*.pgt)|*.pgt|All Files(*.*)|*.*";
			if (DialogResult.Cancel == ofd.ShowDialog(this))
				return;

			deserializeGumps(ofd.FileName);
		}

		private void serializeGumps(string saveas)
		{
			Gump[][] gmps = new Gump[tabControl1.TabCount][];
			for (int i=0; i < tabControl1.TabCount; i++)
			{
				gmps[i]=((GumpViewer)tabControl1.TabPages[i].Controls[0]).Gumps;
			}
			try
			{
				TextWriter tw = new StreamWriter(saveas);
				XmlSerializer xs = new XmlSerializer(typeof(Gump[][]));
				xs.Serialize(tw,gmps);
				tw.Close();
			}
			catch(Exception exc)
			{
				MessageBox.Show(this,"Error saving file:\n"+exc,"Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
			}
		}

		private void deserializeGumps(string path)
		{
			try {
				TextReader tr = new StreamReader(path);
				XmlSerializer xs = new XmlSerializer(typeof(Gump[][]));
				Gump[][] gmps=(Gump[][])xs.Deserialize(tr);
				tabControl1.TabPages.Clear();
				TabPage tp;
				GumpViewer gv;
				for (int i=0; i<gmps.Length; i++) {
					tp = new TabPage("Page "+i);
					if(i!=0)			
						gv = new GumpViewer(((GumpViewer)tabControl1.TabPages[0].Controls[0]));
					else
						gv = new GumpViewer();

					gv.Gumps = gmps[i];

					gv.Dock=DockStyle.Fill;
					tp.Controls.Add(gv);
					gv.SelectedGumpChanged+=new selectedGumpChanged(gumpViewer1_SelectedGumpChanged);
					gv.SelectedIndexChanged+=new selectedIndexChanged(gumpViewer1_SelectedIndexChanged);
					gv.GumpAdded+=new gumpAdded(gumpViewer1_GumpAdded);
					gv.GumpRemoved+=new gumpRemoved(gumpViewer1_GumpRemoved);
					gv.GumpChanged+=new gumpChanged(gumpViewer1_GumpChanged);
					gv.GumpsSort+=new gumpsSort(gumpViewer1_GumpsSort);
					gv.ContextMenu=cmTabMenu;
					this.tabControl1.TabPages.Add(tp);
				}
				tr.Close();
			} catch(Exception exc) {
				MessageBox.Show(this, "Error reading file:\n"+exc,"Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
			}
		}

		private void miAbout_Click(object sender, System.EventArgs e)
		{
			AboutForm af = new AboutForm();
			af.ShowDialog();
		}

		private void miSupportForum_Click(object sender, System.EventArgs e)
		{
			System.Diagnostics.Process.Start("http://www.polserver.com/modules.php?name=Forums");
		}
		
	}
}
