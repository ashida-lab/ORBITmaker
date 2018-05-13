#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "yaCommon.h"
#include "yaString.h"
#include "OpenGLSimpleAdapter.h"
#include "TLEcontents.h"
#include "ANTENNAcontents.h"

// "coreLib.h" includes basic types from the core library,
// such as cSite, cJulian, etc. The header file also contains a
// "using namespace" statement for Zeptomoby::OrbitTools.
#include "coreLib.h"

// "orbitLib.h" includes basic types from the orbit library,
// including cOrbit.
#include "orbitLib.h"

#pragma comment( lib, "freeglut.lib" )
//#pragma comment( lib, "glut32.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )

namespace sample10 {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Drawing::Imaging;
	using namespace System::Collections::Generic;

	using namespace System::Xml::Serialization;
	using namespace System::IO;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		BindingList<TLEcontents^>^ listTLEcontents;
		BindingList<ANTENNAcontents^>^ listANTENNAcontents;
	private: System::Windows::Forms::OpenFileDialog^  antennaOpenFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  antennaSaveFileDialog;
	private: System::Windows::Forms::ComboBox^  txrxComboBox;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::ComboBox^  azelComboBox;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::ComboBox^  antennaComboBox;
	private: System::Windows::Forms::Button^  previewButton;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  antennaChart;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::TextBox^  ElBeamTextBox;
	private: System::Windows::Forms::TextBox^  AzBeamTextBox;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::NumericUpDown^  SecondNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  MinuteNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  HourNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  dayNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  monthNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  yearNumericUpDown;
	private: System::Windows::Forms::CheckBox^  zpCheckBox;

	private: System::Windows::Forms::CheckBox^  udCheckBox;

	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::TextBox^  prfIntervalTextBox;

	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::TextBox^  prfStepTextBox;

	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::TextBox^  prfMaxTextBox;

	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::TextBox^  prfMinTextBox;

	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::ComboBox^  obsPathComboBox;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  tgtHeightTextBox;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::TextBox^  tgtLonTextBox;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  tgtLatTextBox;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  prfChart;
	private: System::Windows::Forms::ComboBox^  obsModeComboBox;

	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ToolStripMenuItem^  loadAntennaToolStripMenuItem;


	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			earthPanel->MouseDown += gcnew MouseEventHandler(this, &sample10::MainForm::myMouseDown);
			earthPanel->MouseWheel += gcnew MouseEventHandler(this, &sample10::MainForm::myMouseWheel);

			listTLEcontents = gcnew BindingList<TLEcontents^>();
			listANTENNAcontents = gcnew BindingList<ANTENNAcontents^>();

			dataGridView1->DataSource = listTLEcontents;
			antennaDataGridView->DataSource = listANTENNAcontents;

			dataGridView1->AutoGenerateColumns = false;
			dataGridView1->Columns["Name"]->DisplayIndex = 0;
			dataGridView1->Columns["L1"]->DisplayIndex = 1;
			dataGridView1->Columns["L2"]->DisplayIndex = 2;

			antennaDataGridView->AutoGenerateColumns = false;
			antennaDataGridView->Columns["Lx"]->DisplayIndex = 0;
			antennaDataGridView->Columns["Ly"]->DisplayIndex = 1;
			antennaDataGridView->Columns["Nx"]->DisplayIndex = 2;
			antennaDataGridView->Columns["Ny"]->DisplayIndex = 3;
			antennaDataGridView->Columns["Px"]->DisplayIndex = 4;
			antennaDataGridView->Columns["Py"]->DisplayIndex = 5;
			antennaDataGridView->Columns["Pz"]->DisplayIndex = 6;
			antennaDataGridView->Columns["TxRx"]->DisplayIndex = 7;

			trans = gcnew cli::array<double, 2>(1800, 3);
			for (int i = 0; i < 1800; i++) {
				trans[i, 0] = 0;
				trans[i, 1] = 0;
				trans[i, 2] = 0;
			}

			//Bitmapクラスの作成
			Bitmap^ bmp;
			bmp = gcnew Bitmap(txPictureBox->Width, txPictureBox->Height);
			txPictureBox->Image = bmp;
			bmp = gcnew Bitmap(rxPictureBox->Width, rxPictureBox->Height);
			rxPictureBox->Image = bmp;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  tleTextBox;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::Panel^  earthPanel;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  removeButton;

	private: System::Windows::Forms::Button^  editButton;
	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::Button^  addButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  loadTLEToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  tleTextBoxL2;

	private: System::Windows::Forms::TextBox^  tleTextBoxL1;
	private: System::Windows::Forms::Button^  removeAntennaButton;
	private: System::Windows::Forms::Button^  editAnttenaButton;
	private: System::Windows::Forms::Button^  saveAntennaButton;
	private: System::Windows::Forms::Button^  addAntennaButton;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  pzTextBox;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  pyTextBox;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  pxTextBox;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  nyTextBox;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  nxTextBox;
	private: System::Windows::Forms::TextBox^  lyTextBox;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  lxTextBox;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::PictureBox^  rxPictureBox;

	private: System::Windows::Forms::PictureBox^  txPictureBox;
	private: System::Windows::Forms::DataGridView^  antennaDataGridView;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea6 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadTLEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadAntennaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->SecondNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->MinuteNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->HourNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->dayNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->monthNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->yearNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tleTextBoxL2 = (gcnew System::Windows::Forms::TextBox());
			this->tleTextBoxL1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->removeButton = (gcnew System::Windows::Forms::Button());
			this->editButton = (gcnew System::Windows::Forms::Button());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->addButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tleTextBox = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->earthPanel = (gcnew System::Windows::Forms::Panel());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->txrxComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->antennaDataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->removeAntennaButton = (gcnew System::Windows::Forms::Button());
			this->editAnttenaButton = (gcnew System::Windows::Forms::Button());
			this->saveAntennaButton = (gcnew System::Windows::Forms::Button());
			this->addAntennaButton = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->pzTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->pyTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->pxTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->nyTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->nxTextBox = (gcnew System::Windows::Forms::TextBox());
			this->lyTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->lxTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->rxPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->txPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->ElBeamTextBox = (gcnew System::Windows::Forms::TextBox());
			this->AzBeamTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->azelComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->antennaComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->previewButton = (gcnew System::Windows::Forms::Button());
			this->antennaChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->antennaOpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->antennaSaveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->prfChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tgtLatTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->tgtLonTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->tgtHeightTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->obsPathComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->prfMinTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->prfMaxTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->prfStepTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->prfIntervalTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->udCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->zpCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->obsModeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SecondNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MinuteNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HourNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dayNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->monthNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->yearNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->antennaDataGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rxPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->txPictureBox))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->antennaChart))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prfChart))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(908, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->loadTLEToolStripMenuItem, this->loadAntennaToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
			// 
			// loadTLEToolStripMenuItem
			// 
			this->loadTLEToolStripMenuItem->Name = L"loadTLEToolStripMenuItem";
			this->loadTLEToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->loadTLEToolStripMenuItem->Text = L"Load TLE";
			this->loadTLEToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadTLEToolStripMenuItem_Click);
			// 
			// loadAntennaToolStripMenuItem
			// 
			this->loadAntennaToolStripMenuItem->Name = L"loadAntennaToolStripMenuItem";
			this->loadAntennaToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->loadAntennaToolStripMenuItem->Text = L"Load Antenna";
			this->loadAntennaToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadAntennaToolStripMenuItem_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Location = System::Drawing::Point(12, 27);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(884, 458);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->SecondNumericUpDown);
			this->tabPage1->Controls->Add(this->MinuteNumericUpDown);
			this->tabPage1->Controls->Add(this->HourNumericUpDown);
			this->tabPage1->Controls->Add(this->dayNumericUpDown);
			this->tabPage1->Controls->Add(this->monthNumericUpDown);
			this->tabPage1->Controls->Add(this->yearNumericUpDown);
			this->tabPage1->Controls->Add(this->tleTextBoxL2);
			this->tabPage1->Controls->Add(this->tleTextBoxL1);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->removeButton);
			this->tabPage1->Controls->Add(this->editButton);
			this->tabPage1->Controls->Add(this->saveButton);
			this->tabPage1->Controls->Add(this->addButton);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->tleTextBox);
			this->tabPage1->Controls->Add(this->dataGridView1);
			this->tabPage1->Controls->Add(this->earthPanel);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(876, 432);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Orbit";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// SecondNumericUpDown
			// 
			this->SecondNumericUpDown->Location = System::Drawing::Point(260, 21);
			this->SecondNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 59, 0, 0, 0 });
			this->SecondNumericUpDown->Name = L"SecondNumericUpDown";
			this->SecondNumericUpDown->Size = System::Drawing::Size(40, 19);
			this->SecondNumericUpDown->TabIndex = 17;
			this->SecondNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->SecondNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::SecondNumericUpDown_ValueChanged);
			// 
			// MinuteNumericUpDown
			// 
			this->MinuteNumericUpDown->Location = System::Drawing::Point(214, 21);
			this->MinuteNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 59, 0, 0, 0 });
			this->MinuteNumericUpDown->Name = L"MinuteNumericUpDown";
			this->MinuteNumericUpDown->Size = System::Drawing::Size(40, 19);
			this->MinuteNumericUpDown->TabIndex = 16;
			this->MinuteNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->MinuteNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::MinuteNumericUpDown_ValueChanged);
			// 
			// HourNumericUpDown
			// 
			this->HourNumericUpDown->Location = System::Drawing::Point(168, 21);
			this->HourNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 23, 0, 0, 0 });
			this->HourNumericUpDown->Name = L"HourNumericUpDown";
			this->HourNumericUpDown->Size = System::Drawing::Size(40, 19);
			this->HourNumericUpDown->TabIndex = 15;
			this->HourNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->HourNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::HourNumericUpDown_ValueChanged);
			// 
			// dayNumericUpDown
			// 
			this->dayNumericUpDown->Location = System::Drawing::Point(122, 21);
			this->dayNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->dayNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->dayNumericUpDown->Name = L"dayNumericUpDown";
			this->dayNumericUpDown->Size = System::Drawing::Size(40, 19);
			this->dayNumericUpDown->TabIndex = 14;
			this->dayNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->dayNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::dayNumericUpDown_ValueChanged);
			// 
			// monthNumericUpDown
			// 
			this->monthNumericUpDown->Location = System::Drawing::Point(76, 21);
			this->monthNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
			this->monthNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->monthNumericUpDown->Name = L"monthNumericUpDown";
			this->monthNumericUpDown->Size = System::Drawing::Size(40, 19);
			this->monthNumericUpDown->TabIndex = 13;
			this->monthNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->monthNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::monthNumericUpDown_ValueChanged);
			// 
			// yearNumericUpDown
			// 
			this->yearNumericUpDown->Location = System::Drawing::Point(7, 21);
			this->yearNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000, 0, 0, 0 });
			this->yearNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->yearNumericUpDown->Name = L"yearNumericUpDown";
			this->yearNumericUpDown->Size = System::Drawing::Size(63, 19);
			this->yearNumericUpDown->TabIndex = 12;
			this->yearNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->yearNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::yearNumericUpDown_ValueChanged);
			// 
			// tleTextBoxL2
			// 
			this->tleTextBoxL2->Location = System::Drawing::Point(6, 153);
			this->tleTextBoxL2->Name = L"tleTextBoxL2";
			this->tleTextBoxL2->Size = System::Drawing::Size(428, 19);
			this->tleTextBoxL2->TabIndex = 11;
			// 
			// tleTextBoxL1
			// 
			this->tleTextBoxL1->Location = System::Drawing::Point(6, 128);
			this->tleTextBoxL1->Name = L"tleTextBoxL1";
			this->tleTextBoxL1->Size = System::Drawing::Size(428, 19);
			this->tleTextBoxL1->TabIndex = 10;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 6);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 12);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Time";
			// 
			// removeButton
			// 
			this->removeButton->Location = System::Drawing::Point(279, 186);
			this->removeButton->Name = L"removeButton";
			this->removeButton->Size = System::Drawing::Size(75, 23);
			this->removeButton->TabIndex = 8;
			this->removeButton->Text = L"Remove";
			this->removeButton->UseVisualStyleBackColor = true;
			this->removeButton->Click += gcnew System::EventHandler(this, &MainForm::removeButton_Click);
			// 
			// editButton
			// 
			this->editButton->Location = System::Drawing::Point(198, 186);
			this->editButton->Name = L"editButton";
			this->editButton->Size = System::Drawing::Size(75, 23);
			this->editButton->TabIndex = 7;
			this->editButton->Text = L"Edit";
			this->editButton->UseVisualStyleBackColor = true;
			this->editButton->Click += gcnew System::EventHandler(this, &MainForm::editButton_Click);
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(360, 186);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(75, 23);
			this->saveButton->TabIndex = 6;
			this->saveButton->Text = L"Save";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &MainForm::saveButton_Click);
			// 
			// addButton
			// 
			this->addButton->Location = System::Drawing::Point(117, 186);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(75, 23);
			this->addButton->TabIndex = 5;
			this->addButton->Text = L"Add";
			this->addButton->UseVisualStyleBackColor = true;
			this->addButton->Click += gcnew System::EventHandler(this, &MainForm::addButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(5, 84);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(25, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"TLE";
			// 
			// tleTextBox
			// 
			this->tleTextBox->Location = System::Drawing::Point(6, 103);
			this->tleTextBox->Name = L"tleTextBox";
			this->tleTextBox->Size = System::Drawing::Size(428, 19);
			this->tleTextBox->TabIndex = 2;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(7, 215);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowTemplate->Height = 21;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(428, 211);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->Click += gcnew System::EventHandler(this, &MainForm::dataGridView1_Click);
			// 
			// earthPanel
			// 
			this->earthPanel->Location = System::Drawing::Point(441, 6);
			this->earthPanel->Name = L"earthPanel";
			this->earthPanel->Size = System::Drawing::Size(429, 420);
			this->earthPanel->TabIndex = 0;
			this->earthPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::earthPanel_Paint);
			this->earthPanel->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::earthPanel_MouseClick);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->txrxComboBox);
			this->tabPage2->Controls->Add(this->antennaDataGridView);
			this->tabPage2->Controls->Add(this->removeAntennaButton);
			this->tabPage2->Controls->Add(this->editAnttenaButton);
			this->tabPage2->Controls->Add(this->saveAntennaButton);
			this->tabPage2->Controls->Add(this->addAntennaButton);
			this->tabPage2->Controls->Add(this->label13);
			this->tabPage2->Controls->Add(this->pzTextBox);
			this->tabPage2->Controls->Add(this->label11);
			this->tabPage2->Controls->Add(this->pyTextBox);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Controls->Add(this->pxTextBox);
			this->tabPage2->Controls->Add(this->label10);
			this->tabPage2->Controls->Add(this->nyTextBox);
			this->tabPage2->Controls->Add(this->label9);
			this->tabPage2->Controls->Add(this->nxTextBox);
			this->tabPage2->Controls->Add(this->lyTextBox);
			this->tabPage2->Controls->Add(this->label8);
			this->tabPage2->Controls->Add(this->label7);
			this->tabPage2->Controls->Add(this->lxTextBox);
			this->tabPage2->Controls->Add(this->label6);
			this->tabPage2->Controls->Add(this->label5);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->rxPictureBox);
			this->tabPage2->Controls->Add(this->txPictureBox);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(876, 432);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Antenna";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// txrxComboBox
			// 
			this->txrxComboBox->FormattingEnabled = true;
			this->txrxComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Tx", L"Rx" });
			this->txrxComboBox->Location = System::Drawing::Point(30, 136);
			this->txrxComboBox->Name = L"txrxComboBox";
			this->txrxComboBox->Size = System::Drawing::Size(121, 20);
			this->txrxComboBox->TabIndex = 25;
			// 
			// antennaDataGridView
			// 
			this->antennaDataGridView->AllowUserToAddRows = false;
			this->antennaDataGridView->AllowUserToDeleteRows = false;
			this->antennaDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->antennaDataGridView->Location = System::Drawing::Point(6, 215);
			this->antennaDataGridView->Name = L"antennaDataGridView";
			this->antennaDataGridView->ReadOnly = true;
			this->antennaDataGridView->RowTemplate->Height = 21;
			this->antennaDataGridView->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->antennaDataGridView->Size = System::Drawing::Size(428, 211);
			this->antennaDataGridView->TabIndex = 24;
			this->antennaDataGridView->Click += gcnew System::EventHandler(this, &MainForm::antennaDataGridView_Click);
			// 
			// removeAntennaButton
			// 
			this->removeAntennaButton->Location = System::Drawing::Point(279, 186);
			this->removeAntennaButton->Name = L"removeAntennaButton";
			this->removeAntennaButton->Size = System::Drawing::Size(75, 23);
			this->removeAntennaButton->TabIndex = 23;
			this->removeAntennaButton->Text = L"Remove";
			this->removeAntennaButton->UseVisualStyleBackColor = true;
			this->removeAntennaButton->Click += gcnew System::EventHandler(this, &MainForm::removeAntennaButton_Click);
			// 
			// editAnttenaButton
			// 
			this->editAnttenaButton->Location = System::Drawing::Point(198, 186);
			this->editAnttenaButton->Name = L"editAnttenaButton";
			this->editAnttenaButton->Size = System::Drawing::Size(75, 23);
			this->editAnttenaButton->TabIndex = 22;
			this->editAnttenaButton->Text = L"Edit";
			this->editAnttenaButton->UseVisualStyleBackColor = true;
			this->editAnttenaButton->Click += gcnew System::EventHandler(this, &MainForm::editAnttenaButton_Click);
			// 
			// saveAntennaButton
			// 
			this->saveAntennaButton->Location = System::Drawing::Point(360, 186);
			this->saveAntennaButton->Name = L"saveAntennaButton";
			this->saveAntennaButton->Size = System::Drawing::Size(75, 23);
			this->saveAntennaButton->TabIndex = 21;
			this->saveAntennaButton->Text = L"Save";
			this->saveAntennaButton->UseVisualStyleBackColor = true;
			this->saveAntennaButton->Click += gcnew System::EventHandler(this, &MainForm::saveAntennaButton_Click);
			// 
			// addAntennaButton
			// 
			this->addAntennaButton->Location = System::Drawing::Point(117, 186);
			this->addAntennaButton->Name = L"addAntennaButton";
			this->addAntennaButton->Size = System::Drawing::Size(75, 23);
			this->addAntennaButton->TabIndex = 20;
			this->addAntennaButton->Text = L"Add";
			this->addAntennaButton->UseVisualStyleBackColor = true;
			this->addAntennaButton->Click += gcnew System::EventHandler(this, &MainForm::addAntennaButton_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(286, 98);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(17, 12);
			this->label13->TabIndex = 19;
			this->label13->Text = L"Pz";
			// 
			// pzTextBox
			// 
			this->pzTextBox->Location = System::Drawing::Point(311, 95);
			this->pzTextBox->Name = L"pzTextBox";
			this->pzTextBox->Size = System::Drawing::Size(100, 19);
			this->pzTextBox->TabIndex = 18;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(155, 98);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(18, 12);
			this->label11->TabIndex = 17;
			this->label11->Text = L"Py";
			// 
			// pyTextBox
			// 
			this->pyTextBox->Location = System::Drawing::Point(180, 95);
			this->pyTextBox->Name = L"pyTextBox";
			this->pyTextBox->Size = System::Drawing::Size(100, 19);
			this->pyTextBox->TabIndex = 16;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(28, 98);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(18, 12);
			this->label12->TabIndex = 15;
			this->label12->Text = L"Px";
			// 
			// pxTextBox
			// 
			this->pxTextBox->Location = System::Drawing::Point(51, 95);
			this->pxTextBox->Name = L"pxTextBox";
			this->pxTextBox->Size = System::Drawing::Size(100, 19);
			this->pxTextBox->TabIndex = 14;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(155, 61);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(19, 12);
			this->label10->TabIndex = 13;
			this->label10->Text = L"Ny";
			// 
			// nyTextBox
			// 
			this->nyTextBox->Location = System::Drawing::Point(180, 58);
			this->nyTextBox->Name = L"nyTextBox";
			this->nyTextBox->Size = System::Drawing::Size(100, 19);
			this->nyTextBox->TabIndex = 12;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(28, 61);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(19, 12);
			this->label9->TabIndex = 11;
			this->label9->Text = L"Nx";
			// 
			// nxTextBox
			// 
			this->nxTextBox->Location = System::Drawing::Point(51, 58);
			this->nxTextBox->Name = L"nxTextBox";
			this->nxTextBox->Size = System::Drawing::Size(100, 19);
			this->nxTextBox->TabIndex = 10;
			// 
			// lyTextBox
			// 
			this->lyTextBox->Location = System::Drawing::Point(180, 21);
			this->lyTextBox->Name = L"lyTextBox";
			this->lyTextBox->Size = System::Drawing::Size(100, 19);
			this->lyTextBox->TabIndex = 9;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(157, 24);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(17, 12);
			this->label8->TabIndex = 8;
			this->label8->Text = L"Ly";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(28, 24);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(17, 12);
			this->label7->TabIndex = 7;
			this->label7->Text = L"Lx";
			// 
			// lxTextBox
			// 
			this->lxTextBox->Location = System::Drawing::Point(51, 21);
			this->lxTextBox->Name = L"lxTextBox";
			this->lxTextBox->Size = System::Drawing::Size(100, 19);
			this->lxTextBox->TabIndex = 6;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 120);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(38, 12);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Tx/Rx";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 80);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(84, 12);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Center Position";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 43);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(89, 12);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Element Number";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(71, 12);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Element Size";
			// 
			// rxPictureBox
			// 
			this->rxPictureBox->BackColor = System::Drawing::Color::Black;
			this->rxPictureBox->Location = System::Drawing::Point(440, 217);
			this->rxPictureBox->Name = L"rxPictureBox";
			this->rxPictureBox->Size = System::Drawing::Size(430, 209);
			this->rxPictureBox->TabIndex = 1;
			this->rxPictureBox->TabStop = false;
			// 
			// txPictureBox
			// 
			this->txPictureBox->BackColor = System::Drawing::Color::Black;
			this->txPictureBox->Location = System::Drawing::Point(440, 6);
			this->txPictureBox->Name = L"txPictureBox";
			this->txPictureBox->Size = System::Drawing::Size(430, 209);
			this->txPictureBox->TabIndex = 0;
			this->txPictureBox->TabStop = false;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->ElBeamTextBox);
			this->tabPage4->Controls->Add(this->AzBeamTextBox);
			this->tabPage4->Controls->Add(this->label17);
			this->tabPage4->Controls->Add(this->label16);
			this->tabPage4->Controls->Add(this->azelComboBox);
			this->tabPage4->Controls->Add(this->label15);
			this->tabPage4->Controls->Add(this->label14);
			this->tabPage4->Controls->Add(this->antennaComboBox);
			this->tabPage4->Controls->Add(this->previewButton);
			this->tabPage4->Controls->Add(this->antennaChart);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(876, 432);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Antenna Pattern";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// ElBeamTextBox
			// 
			this->ElBeamTextBox->Location = System::Drawing::Point(126, 120);
			this->ElBeamTextBox->Name = L"ElBeamTextBox";
			this->ElBeamTextBox->Size = System::Drawing::Size(100, 19);
			this->ElBeamTextBox->TabIndex = 9;
			this->ElBeamTextBox->Text = L"0.1";
			this->ElBeamTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::ElBeamTextBox_TextChanged);
			// 
			// AzBeamTextBox
			// 
			this->AzBeamTextBox->Location = System::Drawing::Point(126, 96);
			this->AzBeamTextBox->Name = L"AzBeamTextBox";
			this->AzBeamTextBox->Size = System::Drawing::Size(100, 19);
			this->AzBeamTextBox->TabIndex = 8;
			this->AzBeamTextBox->Text = L"0.1";
			this->AzBeamTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::AzBeamTextBox_TextChanged);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(9, 123);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(108, 12);
			this->label17->TabIndex = 7;
			this->label17->Text = L"El Beam Width [rad]";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(9, 99);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(111, 12);
			this->label16->TabIndex = 6;
			this->label16->Text = L"Az Beam Width [rad]";
			// 
			// azelComboBox
			// 
			this->azelComboBox->FormattingEnabled = true;
			this->azelComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Az", L"El" });
			this->azelComboBox->Location = System::Drawing::Point(60, 65);
			this->azelComboBox->Name = L"azelComboBox";
			this->azelComboBox->Size = System::Drawing::Size(121, 20);
			this->azelComboBox->TabIndex = 5;
			this->azelComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::azelComboBox_SelectedIndexChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(7, 68);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(34, 12);
			this->label15->TabIndex = 4;
			this->label15->Text = L"Az/El";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(7, 37);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(47, 12);
			this->label14->TabIndex = 3;
			this->label14->Text = L"Antenna";
			// 
			// antennaComboBox
			// 
			this->antennaComboBox->FormattingEnabled = true;
			this->antennaComboBox->Location = System::Drawing::Point(60, 34);
			this->antennaComboBox->Name = L"antennaComboBox";
			this->antennaComboBox->Size = System::Drawing::Size(121, 20);
			this->antennaComboBox->TabIndex = 2;
			this->antennaComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::antennaComboBox_SelectedIndexChanged);
			// 
			// previewButton
			// 
			this->previewButton->Location = System::Drawing::Point(7, 7);
			this->previewButton->Name = L"previewButton";
			this->previewButton->Size = System::Drawing::Size(75, 23);
			this->previewButton->TabIndex = 1;
			this->previewButton->Text = L"Preview";
			this->previewButton->UseVisualStyleBackColor = true;
			this->previewButton->Click += gcnew System::EventHandler(this, &MainForm::previewButton_Click);
			// 
			// antennaChart
			// 
			chartArea6->AxisX->Interval = 0.3141592;
			chartArea6->AxisX->LabelStyle->Format = L"0.00";
			chartArea6->AxisX->Title = L"[rad]";
			chartArea6->AxisY->Title = L"[dB]";
			chartArea6->Name = L"ChartArea1";
			this->antennaChart->ChartAreas->Add(chartArea6);
			legend6->Enabled = false;
			legend6->Name = L"Legend1";
			this->antennaChart->Legends->Add(legend6);
			this->antennaChart->Location = System::Drawing::Point(441, 6);
			this->antennaChart->Name = L"antennaChart";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series6->Legend = L"Legend1";
			series6->Name = L"Series1";
			this->antennaChart->Series->Add(series6);
			this->antennaChart->Size = System::Drawing::Size(429, 420);
			this->antennaChart->TabIndex = 0;
			this->antennaChart->Text = L"antennaChart";
			this->antennaChart->Click += gcnew System::EventHandler(this, &MainForm::antennaChart_Click);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->button1);
			this->tabPage3->Controls->Add(this->obsModeComboBox);
			this->tabPage3->Controls->Add(this->label29);
			this->tabPage3->Controls->Add(this->zpCheckBox);
			this->tabPage3->Controls->Add(this->udCheckBox);
			this->tabPage3->Controls->Add(this->label28);
			this->tabPage3->Controls->Add(this->label27);
			this->tabPage3->Controls->Add(this->prfIntervalTextBox);
			this->tabPage3->Controls->Add(this->label26);
			this->tabPage3->Controls->Add(this->prfStepTextBox);
			this->tabPage3->Controls->Add(this->label25);
			this->tabPage3->Controls->Add(this->prfMaxTextBox);
			this->tabPage3->Controls->Add(this->label24);
			this->tabPage3->Controls->Add(this->prfMinTextBox);
			this->tabPage3->Controls->Add(this->label23);
			this->tabPage3->Controls->Add(this->obsPathComboBox);
			this->tabPage3->Controls->Add(this->label22);
			this->tabPage3->Controls->Add(this->label21);
			this->tabPage3->Controls->Add(this->tgtHeightTextBox);
			this->tabPage3->Controls->Add(this->label20);
			this->tabPage3->Controls->Add(this->tgtLonTextBox);
			this->tabPage3->Controls->Add(this->label19);
			this->tabPage3->Controls->Add(this->tgtLatTextBox);
			this->tabPage3->Controls->Add(this->label18);
			this->tabPage3->Controls->Add(this->prfChart);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(876, 432);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Observation";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// tabPage5
			// 
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(876, 432);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Output";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// prfChart
			// 
			chartArea5->AxisX->Interval = 0.3141592;
			chartArea5->AxisX->LabelStyle->Format = L"0.00";
			chartArea5->AxisX->Title = L"[rad]";
			chartArea5->AxisY->Title = L"[dB]";
			chartArea5->Name = L"ChartArea1";
			this->prfChart->ChartAreas->Add(chartArea5);
			legend5->Enabled = false;
			legend5->Name = L"Legend1";
			this->prfChart->Legends->Add(legend5);
			this->prfChart->Location = System::Drawing::Point(441, 6);
			this->prfChart->Name = L"prfChart";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series5->Legend = L"Legend1";
			series5->Name = L"Series1";
			this->prfChart->Series->Add(series5);
			this->prfChart->Size = System::Drawing::Size(429, 420);
			this->prfChart->TabIndex = 1;
			this->prfChart->Text = L"chart1";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(7, 7);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(83, 12);
			this->label18->TabIndex = 2;
			this->label18->Text = L"Target Position";
			// 
			// tgtLatTextBox
			// 
			this->tgtLatTextBox->Location = System::Drawing::Point(57, 22);
			this->tgtLatTextBox->Name = L"tgtLatTextBox";
			this->tgtLatTextBox->Size = System::Drawing::Size(79, 19);
			this->tgtLatTextBox->TabIndex = 3;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(30, 25);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(21, 12);
			this->label19->TabIndex = 4;
			this->label19->Text = L"Lat";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(142, 25);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(23, 12);
			this->label20->TabIndex = 6;
			this->label20->Text = L"Lon";
			// 
			// tgtLonTextBox
			// 
			this->tgtLonTextBox->Location = System::Drawing::Point(171, 22);
			this->tgtLonTextBox->Name = L"tgtLonTextBox";
			this->tgtLonTextBox->Size = System::Drawing::Size(79, 19);
			this->tgtLonTextBox->TabIndex = 5;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(256, 25);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(38, 12);
			this->label21->TabIndex = 8;
			this->label21->Text = L"Height";
			// 
			// tgtHeightTextBox
			// 
			this->tgtHeightTextBox->Location = System::Drawing::Point(300, 22);
			this->tgtHeightTextBox->Name = L"tgtHeightTextBox";
			this->tgtHeightTextBox->Size = System::Drawing::Size(79, 19);
			this->tgtHeightTextBox->TabIndex = 7;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(7, 44);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(93, 12);
			this->label22->TabIndex = 9;
			this->label22->Text = L"Observation Path";
			// 
			// obsPathComboBox
			// 
			this->obsPathComboBox->FormattingEnabled = true;
			this->obsPathComboBox->Location = System::Drawing::Point(32, 60);
			this->obsPathComboBox->Name = L"obsPathComboBox";
			this->obsPathComboBox->Size = System::Drawing::Size(121, 20);
			this->obsPathComboBox->TabIndex = 10;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(7, 121);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(27, 12);
			this->label23->TabIndex = 11;
			this->label23->Text = L"PRF";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(28, 140);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(23, 12);
			this->label24->TabIndex = 13;
			this->label24->Text = L"Min";
			// 
			// prfMinTextBox
			// 
			this->prfMinTextBox->Location = System::Drawing::Point(57, 137);
			this->prfMinTextBox->Name = L"prfMinTextBox";
			this->prfMinTextBox->Size = System::Drawing::Size(53, 19);
			this->prfMinTextBox->TabIndex = 12;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(116, 140);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(26, 12);
			this->label25->TabIndex = 15;
			this->label25->Text = L"Max";
			// 
			// prfMaxTextBox
			// 
			this->prfMaxTextBox->Location = System::Drawing::Point(148, 137);
			this->prfMaxTextBox->Name = L"prfMaxTextBox";
			this->prfMaxTextBox->Size = System::Drawing::Size(53, 19);
			this->prfMaxTextBox->TabIndex = 14;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(207, 140);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(28, 12);
			this->label26->TabIndex = 17;
			this->label26->Text = L"Step";
			// 
			// prfStepTextBox
			// 
			this->prfStepTextBox->Location = System::Drawing::Point(241, 137);
			this->prfStepTextBox->Name = L"prfStepTextBox";
			this->prfStepTextBox->Size = System::Drawing::Size(53, 19);
			this->prfStepTextBox->TabIndex = 16;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(300, 140);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(43, 12);
			this->label27->TabIndex = 19;
			this->label27->Text = L"Interval";
			// 
			// prfIntervalTextBox
			// 
			this->prfIntervalTextBox->Location = System::Drawing::Point(349, 137);
			this->prfIntervalTextBox->Name = L"prfIntervalTextBox";
			this->prfIntervalTextBox->Size = System::Drawing::Size(53, 19);
			this->prfIntervalTextBox->TabIndex = 18;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(7, 159);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(60, 12);
			this->label28->TabIndex = 20;
			this->label28->Text = L"Modulation";
			// 
			// udCheckBox
			// 
			this->udCheckBox->AutoSize = true;
			this->udCheckBox->Location = System::Drawing::Point(33, 175);
			this->udCheckBox->Name = L"udCheckBox";
			this->udCheckBox->Size = System::Drawing::Size(72, 16);
			this->udCheckBox->TabIndex = 21;
			this->udCheckBox->Text = L"Up/Down";
			this->udCheckBox->UseVisualStyleBackColor = true;
			// 
			// zpCheckBox
			// 
			this->zpCheckBox->AutoSize = true;
			this->zpCheckBox->Location = System::Drawing::Point(112, 174);
			this->zpCheckBox->Name = L"zpCheckBox";
			this->zpCheckBox->Size = System::Drawing::Size(51, 16);
			this->zpCheckBox->TabIndex = 22;
			this->zpCheckBox->Text = L"0/pai";
			this->zpCheckBox->UseVisualStyleBackColor = true;
			// 
			// obsModeComboBox
			// 
			this->obsModeComboBox->FormattingEnabled = true;
			this->obsModeComboBox->Location = System::Drawing::Point(32, 98);
			this->obsModeComboBox->Name = L"obsModeComboBox";
			this->obsModeComboBox->Size = System::Drawing::Size(121, 20);
			this->obsModeComboBox->TabIndex = 24;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(7, 83);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(97, 12);
			this->label29->TabIndex = 23;
			this->label29->Text = L"Observation Mode";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(9, 217);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 25;
			this->button1->Text = L"Generate";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(908, 497);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SecondNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MinuteNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HourNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dayNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->monthNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->yearNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->antennaDataGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rxPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->txPictureBox))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->antennaChart))->EndInit();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prfChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: cli::array<double, 2> ^trans;

	public: OpenGLSimpleAdapter^ GLAdapter;
	private: System::Void earthPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainForm::panelRefresh(void);

	private: System::Void myMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void myMouseMoveLeft(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void myMouseUpLeft(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void myMouseMoveRight(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void myMouseUpRight(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void myMouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void drawAntenna(double lx, double ly, int nx, int ny, double px, double py, Color color, PictureBox^ pictureBox);

	private: System::Void MarshalString(System::String ^ s, string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}


	private: GLuint readTexture();

	private: Bitmap^ mat2bmp(cv::Mat img);

	private: System::Void addButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TLEcontents^ newTLEcontents = gcnew TLEcontents();

		newTLEcontents->setData(tleTextBox->Text, tleTextBoxL1->Text, tleTextBoxL2->Text);

		listTLEcontents->Add(newTLEcontents);
	}

	private: System::Void editButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TLEcontents^ selectedTLEcontents = listTLEcontents[dataGridView1->CurrentRow->Index];

		selectedTLEcontents->setData(tleTextBox->Text, tleTextBoxL1->Text, tleTextBoxL2->Text);

		dataGridView1->Refresh();
	}

	private: System::Void removeButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		listTLEcontents->RemoveAt(dataGridView1->CurrentRow->Index);

		clearInputControl();
	}

	private: System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			XmlSerializer^ xmlSerializer = gcnew XmlSerializer(BindingList<TLEcontents^>::typeid);

			FileStream^ fileStream = File::Open(saveFileDialog1->FileName, FileMode::Create);

			xmlSerializer->Serialize(fileStream, listTLEcontents);

			fileStream->Close();
		}
	}

	private: System::Void earthPanel_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		earthPanel->Focus();
	}

	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
	}

	private: System::Void loadTLEToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			XmlSerializer^ xmlSerializer = gcnew XmlSerializer(BindingList<TLEcontents^>::typeid);

			FileStream^ fileStream = File::Open(openFileDialog1->FileName, FileMode::Open, FileAccess::Read);

			listTLEcontents->Clear();

			listTLEcontents = (BindingList<TLEcontents^>^)xmlSerializer->Deserialize(fileStream);

			dataGridView1->DataSource = listTLEcontents;

			fileStream->Close();
		}
	}

	private: System::Void dataGridView1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		clearInputControl();

		redrawOrbit(totalTimeFromUpDown());
	}

	private:System::Void redrawOrbit(double totalTime_minute) {
		if (dataGridView1->RowCount < 1) {
			return;
		}

		TLEcontents^ selectedTLEcontents = listTLEcontents[dataGridView1->CurrentRow->Index];

		tleTextBox->Text = selectedTLEcontents->Name;
		tleTextBoxL1->Text = selectedTLEcontents->L1;
		tleTextBoxL2->Text = selectedTLEcontents->L2;

		string str1;
		string str2;
		string str3;

		MarshalString(selectedTLEcontents->Name, str1);
		MarshalString(selectedTLEcontents->L1, str2);
		MarshalString(selectedTLEcontents->L2, str3);

		// Create a TLE object using the data above
		cTle tleSDP4(str1, str2, str3);

		// Create a satellite object from the TLE object
		cSatellite satSDP4(tleSDP4);

		for (int i = 0; i < 1800; i++) {
			// Get the location of the satellite. The earth-centered inertial (ECI)
			// information is placed into eciSDP4.
			// Here we ask for the location of the satellite 90 minutes after
			// the TLE epoch.

			cEciTime eciSDP4_epoch = satSDP4.PositionEci(0);
			cJulian totalTime_day0 = eciSDP4_epoch.Date();

			double minute_from_epoch = totalTime_minute - totalTime_day0.FromJan1_12h_2000()*24.*60.;

			printf("[total time from epoch] %f minute\n", minute_from_epoch);

			cEciTime eciSDP4 = satSDP4.PositionEci(minute_from_epoch + i);

			/*printf("[Pos] %16.8f %16.8f %16.8f\n",
				eciSDP4.Position().m_x,
				eciSDP4.Position().m_y,
				eciSDP4.Position().m_z);*/
			printf("[Vel] %16.8f %16.8f %16.8f\n",
				eciSDP4.Velocity().m_x,
				eciSDP4.Velocity().m_y,
				eciSDP4.Velocity().m_z);

			cJulian totalTime_day = eciSDP4.Date();
			double totalTime_sec = totalTime_day.FromJan1_12h_2000()*24.*3600.;

			printf("[total time] %f sec\n", totalTime_sec);

			double omega_e = 7292115.1467e-11;

			//ECI J2000
			double eci_x = eciSDP4.Position().m_x;
			double eci_y = eciSDP4.Position().m_y;
			double eci_z = eciSDP4.Position().m_z;

			//ECR (ECEF) WGS84
			double ecr_x = eci_x*cos(omega_e*totalTime_sec+M_PI/2) + eci_y*sin(omega_e*totalTime_sec + M_PI / 2);
			double ecr_y = -eci_x*sin(omega_e*totalTime_sec + M_PI / 2) + eci_y*cos(omega_e*totalTime_sec + M_PI / 2);
			double ecr_z = eci_z;

			//表示用
			//http://www.lizard-tail.com/isana/tracking/と比較するとこっち
			trans[i, 0] = ecr_x / 6000;
			trans[i, 1] = -ecr_y / 6000;
			trans[i, 2] = ecr_z / 6000;

			printf("[Pos] %16.8f %16.8f %16.8f\n",
				trans[i,0],
				trans[i,1],
				trans[1,2]);
		}

		panelRefresh();
	}

	private: double totalTimeFromUpDown()
	{
		yaString yaStr;

		cJulian time = cJulian(
			yaStr.systemStringToInt(yearNumericUpDown->Value.ToString()),
			yaStr.systemStringToInt(monthNumericUpDown->Value.ToString()),
			yaStr.systemStringToInt(dayNumericUpDown->Value.ToString()),
			yaStr.systemStringToInt(HourNumericUpDown->Value.ToString()),
			yaStr.systemStringToInt(MinuteNumericUpDown->Value.ToString()),
			yaStr.systemStringToDouble(SecondNumericUpDown->Value.ToString()));

		double totalTime_minute = time.FromJan1_12h_2000()*24.*60.;

		return totalTime_minute;
	}

	private: System::Void yearNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawOrbit(totalTimeFromUpDown());
	}

	private: System::Void monthNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawOrbit(totalTimeFromUpDown());
	}

	private: System::Void dayNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawOrbit(totalTimeFromUpDown());
	}

	private: System::Void HourNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawOrbit(totalTimeFromUpDown());
	}

	private: System::Void MinuteNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawOrbit(totalTimeFromUpDown());
	}

	private: System::Void SecondNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawOrbit(totalTimeFromUpDown());
	}

	private: System::Void clearInputControl()
	{
		tleTextBox->Text = "";
		tleTextBoxL1->Text = "";
		tleTextBoxL2->Text = "";
	}

	private: System::Void addAntennaButton_Click(System::Object^  sender, System::EventArgs^  e) {
		ANTENNAcontents^ newANTENNAcontents = gcnew ANTENNAcontents();
		yaString yaStr;

		newANTENNAcontents->setData(
			yaStr.systemStringToDouble(lxTextBox->Text),
			yaStr.systemStringToDouble(lyTextBox->Text),
			yaStr.systemStringToInt(nxTextBox->Text),
			yaStr.systemStringToInt(nyTextBox->Text),
			yaStr.systemStringToDouble(pxTextBox->Text),
			yaStr.systemStringToDouble(pyTextBox->Text),
			yaStr.systemStringToDouble(pzTextBox->Text),
			txrxComboBox->SelectedIndex
			//yaStr.systemStringToInt("1")
		);

		listANTENNAcontents->Add(newANTENNAcontents);

		redrawAntenna();
	}

	private: System::Void editAnttenaButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (antennaDataGridView->RowCount < 1) {
			return;
		}

		ANTENNAcontents^ selectedANTENNAcontents = listANTENNAcontents[antennaDataGridView->CurrentRow->Index];
		yaString yaStr;

		selectedANTENNAcontents->setData(
			yaStr.systemStringToDouble(lxTextBox->Text),
			yaStr.systemStringToDouble(lyTextBox->Text),
			yaStr.systemStringToInt(nxTextBox->Text),
			yaStr.systemStringToInt(nyTextBox->Text),
			yaStr.systemStringToDouble(pxTextBox->Text),
			yaStr.systemStringToDouble(pyTextBox->Text),
			yaStr.systemStringToDouble(pzTextBox->Text),
			txrxComboBox->SelectedIndex
			//yaStr.systemStringToInt("1")
		);

		antennaDataGridView->Refresh();

		redrawAntenna();
	}

	private: System::Void removeAntennaButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		printf("[Antenna Row Count] %d\n", antennaDataGridView->RowCount);
		if (antennaDataGridView->RowCount < 1) {
			return;
		}

		listANTENNAcontents->RemoveAt(antennaDataGridView->CurrentRow->Index);

		clearAntennaInputControl();

		redrawAntenna();
	}

	private: System::Void saveAntennaButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			XmlSerializer^ xmlSerializer = gcnew XmlSerializer(BindingList<ANTENNAcontents^>::typeid);

			FileStream^ fileStream = File::Open(saveFileDialog1->FileName, FileMode::Create);

			xmlSerializer->Serialize(fileStream, listANTENNAcontents);

			fileStream->Close();
		}
	}

	private: System::Void clearAntennaInputControl()
	{
		lxTextBox->Text = "";
		lyTextBox->Text = "";
		nxTextBox->Text = "";
		nyTextBox->Text = "";
		pxTextBox->Text = "";
		pyTextBox->Text = "";
		pzTextBox->Text = "";
	}

	private: System::Void antennaDataGridView_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (antennaDataGridView->RowCount < 1) {
			return;
		}

		clearAntennaInputControl();

		ANTENNAcontents^ selectedANTENNAcontents = listANTENNAcontents[antennaDataGridView->CurrentRow->Index];

		lxTextBox->Text = selectedANTENNAcontents->Lx.ToString();
		lyTextBox->Text = selectedANTENNAcontents->Ly.ToString();
		nxTextBox->Text = selectedANTENNAcontents->Nx.ToString();
		nyTextBox->Text = selectedANTENNAcontents->Ny.ToString();
		pxTextBox->Text = selectedANTENNAcontents->Px.ToString();
		pyTextBox->Text = selectedANTENNAcontents->Py.ToString();
		pzTextBox->Text = selectedANTENNAcontents->Pz.ToString();
		txrxComboBox->SelectedIndex = selectedANTENNAcontents->TxRx;

	}

	private: System::Void loadAntennaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			XmlSerializer^ xmlSerializer = gcnew XmlSerializer(BindingList<ANTENNAcontents^>::typeid);

			FileStream^ fileStream = File::Open(openFileDialog1->FileName, FileMode::Open, FileAccess::Read);

			listANTENNAcontents->Clear();

			listANTENNAcontents = (BindingList<ANTENNAcontents^>^)xmlSerializer->Deserialize(fileStream);

			antennaDataGridView->DataSource = listANTENNAcontents;

			fileStream->Close();
		}

		redrawAntenna();
	}

	private: System::Void redrawAntenna()
	{
		ANTENNAcontents^ selectedANTENNAcontents;

		cli::array<Color> ^color_table = gcnew cli::array<Color>(10);

		color_table[0] = Color::Red;
		color_table[1] = Color::Orange;
		color_table[2] = Color::Yellow;
		color_table[3] = Color::Green;
		color_table[4] = Color::Aqua;
		color_table[5] = Color::Blue;
		color_table[6] = Color::Violet;

		//Bitmapクラスの作成
		//なぜか必要。。
		Bitmap^ bmp;
		bmp = gcnew Bitmap(txPictureBox->Width, txPictureBox->Height);
		txPictureBox->Image = bmp;
		bmp = gcnew Bitmap(rxPictureBox->Width, rxPictureBox->Height);
		rxPictureBox->Image = bmp;

		//ピクチャボックスからGraphicsの作成
		Graphics^ g_tx = Graphics::FromImage(txPictureBox->Image);

		//ピクチャボックスの背景色でクリアする。
		g_tx->Clear(txPictureBox->BackColor);

		g_tx->~Graphics();

		//ピクチャボックスからGraphicsの作成
		Graphics^ g_rx = Graphics::FromImage(rxPictureBox->Image);

		//ピクチャボックスの背景色でクリアする。
		g_rx->Clear(rxPictureBox->BackColor);

		g_rx->~Graphics();

		for (int i = 0; i < antennaDataGridView->RowCount; i++) {
			printf("[Antenna] %d\n", i);
			selectedANTENNAcontents = listANTENNAcontents[i];

			if (selectedANTENNAcontents->TxRx == 0) {
				drawAntenna(selectedANTENNAcontents->Lx, selectedANTENNAcontents->Ly, selectedANTENNAcontents->Nx, selectedANTENNAcontents->Ny, selectedANTENNAcontents->Px, selectedANTENNAcontents->Py, color_table[i % 7], txPictureBox);
			}
			else {
				drawAntenna(selectedANTENNAcontents->Lx, selectedANTENNAcontents->Ly, selectedANTENNAcontents->Nx, selectedANTENNAcontents->Ny, selectedANTENNAcontents->Px, selectedANTENNAcontents->Py, color_table[i % 7], rxPictureBox);
			}
		}
	}

	private: System::Void previewButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		for (int i = 0; i < antennaDataGridView->RowCount; i++) {
			antennaComboBox->Items->Add(i.ToString());
		}

		antennaComboBox->SelectedIndex = 0;
		azelComboBox->SelectedIndex = 0;

		redrawAntennaPattern();
	}

	private: System::Void antennaComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawAntennaPattern();
	}

	private: System::Void azelComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawAntennaPattern();
	}

	private: System::Void AzBeamTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawAntennaPattern();
	}
	private: System::Void ElBeamTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		redrawAntennaPattern();
	}

	private: System::Void redrawAntennaPattern()
	{
		int index = antennaComboBox->SelectedIndex;
		complex<double> pattern[1800];
		double dx, dy;
		yaString yaStr;

		antennaChart->Series["Series1"]->Points->Clear();

		ANTENNAcontents^ selectedANTENNAcontents = listANTENNAcontents[index];

		if (azelComboBox->SelectedIndex == 0) {

			for (int az = 0; az < 1800; az++) {
				pattern[az] = 0;

				for (int i = 0; i < selectedANTENNAcontents->Nx; i++) {
					for (int j = 0; j < selectedANTENNAcontents->Ny; j++) {
						dx = selectedANTENNAcontents->Px
							+ (i - selectedANTENNAcontents->Nx / 2 + 0.5)*selectedANTENNAcontents->Lx;
						dy = selectedANTENNAcontents->Py
							+ (j - selectedANTENNAcontents->Ny / 2 + 0.5)*selectedANTENNAcontents->Ly;

						pattern[az] += elementPattern(
							(az - 900) / 3600.*M_PI, 0, yaStr.systemStringToDouble(AzBeamTextBox->Text),
							0, 0, yaStr.systemStringToDouble(ElBeamTextBox->Text),
							0.3, dx, dy, 1);


					}
				}
				//printf("[Pattern] %f %f\n", abs(pattern[az]), real(pattern[az]));
			}

			for (int az = 0; az < 1800; az++)
			{
				//
				antennaChart->Series["Series1"]->Points->AddXY((az - 900) / 3600.*M_PI, 20 * log10(abs(pattern[az]) + 1e-6));
			}
		}
		else {
			for (int el = 0; el < 1800; el++) {
				pattern[el] = 0;

				for (int i = 0; i < selectedANTENNAcontents->Nx; i++) {
					for (int j = 0; j < selectedANTENNAcontents->Ny; j++) {
						dx = selectedANTENNAcontents->Px
							+ (i - selectedANTENNAcontents->Nx / 2 + 0.5)*selectedANTENNAcontents->Lx;
						dy = selectedANTENNAcontents->Py
							+ (j - selectedANTENNAcontents->Ny / 2 + 0.5)*selectedANTENNAcontents->Ly;

						pattern[el] += elementPattern(
							0, 0, yaStr.systemStringToDouble(AzBeamTextBox->Text),
							(el - 900) / 3600.*M_PI, 0, yaStr.systemStringToDouble(ElBeamTextBox->Text),
							0.3, dx, dy, 1);


					}
				}
				//printf("[Pattern] %f %f\n", abs(pattern[az]), real(pattern[az]));
			}

			for (int el = 0; el < 1800; el++)
			{
				//
				antennaChart->Series["Series1"]->Points->AddXY((el - 900) / 3600.*M_PI, 20 * log10(abs(pattern[el]) + 1e-6));
			}
		}
	}

	private: complex<double> elementPattern(double az, double az_bc, double az_beam_w, double el, double el_bc, double el_beam_w, double lambda, double dx, double dy, double w)
	{
		complex<double> result, a, b, c;

		a = complex<double>(cos(-2 * M_PI / lambda*dx*sin(az) + 2 * M_PI / lambda*dx*sin(az_bc)),
			sin(-2 * M_PI / lambda*dx*sin(az) + 2 * M_PI / lambda*dx*sin(az_bc)));

		b = complex<double>(cos(-2 * M_PI / lambda*dy*sin(el) + 2 * M_PI / lambda*dy*sin(el_bc)),
			sin(-2 * M_PI / lambda*dy*sin(el) + 2 * M_PI / lambda*dy*sin(el_bc)));

		if (abs(az) < az_beam_w && abs(el) < el_beam_w) {
			result = w*a*b;
			//*sinc(az/az_beam_w)*sinc(el/el_beam_w)
		}
		else {
			result = 0;
		}

		//result = w*a*b*sinc(az / az_beam_w)*sinc(el / el_beam_w);

		return result;
	}

	private: double sinc(double t)
	{
		double result;

		if (t < 10e-6) {
			result = 1;
		}
		else {
			result = sin(t) / t;
		}

		return t;
	}


	private: System::Void antennaChart_Click(System::Object^  sender, System::EventArgs^  e) {
	}




	};
}
