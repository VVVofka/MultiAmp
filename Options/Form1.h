#pragma once
#include "Cell4.h"
#include "OptionExternDecl.h"

namespace CppCLRWinformsProjekt{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Zusammenfassung fьr Form1
/// </summary>
public ref class Form1 : public System::Windows::Forms::Form{
	//int OkCancel = 1; // Ok=1 Cancel=0
	int* iArr;
private: System::Windows::Forms::Label^ label11;
private: System::Windows::Forms::Label^ lbLaysCnt;
private: System::Windows::Forms::Label^ label12;
private: System::Windows::Forms::ListBox^ lstMask0000;
private: System::Windows::Forms::Label^ lbMask0001;
private: System::Windows::Forms::ListBox^ lstMask0001;

private: System::Windows::Forms::Label^ label14;
private: System::Windows::Forms::ListBox^ lstMask0011;
private: System::Windows::Forms::Label^ label15;
private: System::Windows::Forms::ListBox^ lstMask1111;
private: System::Windows::Forms::Label^ label13;
private: System::Windows::Forms::ListBox^ lstMask0111;
private: System::Windows::Forms::Label^ label16;
private: System::Windows::Forms::ListBox^ lstMask0110;
private: System::Windows::Forms::TextBox^ txSeedRnd;
private: System::Windows::Forms::Label^ label17;

	   double* dArr;
public:
	void setDir(int a, int ncell, int nitem, int dir){ cells[a]->getCell(ncell, nitem)->setDir(dir); }
	int getDir(int a, int ncell, int nitem){ return cells[a]->getCell(ncell, nitem)->getDir(); }
	//int getOk(){ return OkCancel; }
	void setArr(int* i_arr, double* d_arr){
		iArr = i_arr; dArr = d_arr;
		for(int a = 0, n = 0; a < 16; a++)
			for(int ncell = 0; ncell < 4; ncell++)
				for(int nitem = 0; nitem < 4; nitem++)
					setDir(a, ncell, nitem, iArr[n++]);
		chNormDirs->Checked = (iArr[InpOptions::NormDir] != 0);
		txSizeYUp->Text = Convert::ToString(iArr[InpOptions::LaysSzUpY]);
		txSizeXUp->Text = Convert::ToString(iArr[InpOptions::LaysSzUpX]);
		txSizeDn->Text = Convert::ToString(iArr[InpOptions::LaysSzDn]);
		//chSeedRnd->Checked = (iArr[InpOptions::SeedRnd] > 0);
		txSeedRnd->Text = Convert::ToString(iArr[InpOptions::SeedRnd]);
		lbLaysCnt->Text = Convert::ToString(iArr[InpOptions::LaysCnt]);
		lstMask0000->SelectedIndex = iArr[InpOptions::AMasks];
		lstMask0001->SelectedIndex = iArr[InpOptions::AMasks + 1];
		lstMask0011->SelectedIndex = iArr[InpOptions::AMasks + 3];
		lstMask0110->SelectedIndex = iArr[InpOptions::AMasks + 6];
		lstMask0111->SelectedIndex = iArr[InpOptions::AMasks + 7];
		lstMask1111->SelectedIndex = iArr[InpOptions::AMasks + 15];

		txKFillRnd->Text = Convert::ToString(dArr[InpOptions::kFillRnd]);
		txKSigmaY->Text = Convert::ToString(dArr[InpOptions::kSigmaY]);
		txKSigmaX->Text = Convert::ToString(dArr[InpOptions::kSigmaX]);
		txKInertion->Text = Convert::ToString(dArr[InpOptions::kInertion]);
		txKBorder->Text = Convert::ToString(dArr[InpOptions::kBorder]);
		txKLaysFrom->Text = Convert::ToString(dArr[InpOptions::kLays]);
		txKLaysTo->Text = Convert::ToString(dArr[InpOptions::kLays + iArr[InpOptions::LaysCnt] - 1]);
	} // ////////////////////////////////////////////////////////////////////////////////////////
	Form1(void){
		InitializeComponent();
		//TODO: Konstruktorcode hier hinzufьgen.
		cells[0b0000] = gcnew Cell4(box0000);
		cells[0b0001] = gcnew Cell4(box0001);
		cells[0b0010] = gcnew Cell4(box0010);
		cells[0b0011] = gcnew Cell4(box0011);
		cells[0b0100] = gcnew Cell4(box0100);
		cells[0b0101] = gcnew Cell4(box0101);
		cells[0b0110] = gcnew Cell4(box0110);
		cells[0b0111] = gcnew Cell4(box0111);

		cells[0b1000] = gcnew Cell4(box1000);
		cells[0b1001] = gcnew Cell4(box1001);
		cells[0b1010] = gcnew Cell4(box1010);
		cells[0b1011] = gcnew Cell4(box1011);
		cells[0b1100] = gcnew Cell4(box1100);
		cells[0b1101] = gcnew Cell4(box1101);
		cells[0b1110] = gcnew Cell4(box1110);
		cells[0b1111] = gcnew Cell4(box1111);
	}
private:
	array<Cell4^>^ cells = gcnew array<Cell4^>(16);
private: System::Windows::Forms::PictureBox^ box0010;
private: System::Windows::Forms::PictureBox^ box0100;
private: System::Windows::Forms::PictureBox^ box1000;
private: System::Windows::Forms::PictureBox^ box1010;
private: System::Windows::Forms::PictureBox^ box1100;
private: System::Windows::Forms::PictureBox^ box0101;
private: System::Windows::Forms::PictureBox^ box1001;
private: System::Windows::Forms::PictureBox^ box1011;
private: System::Windows::Forms::PictureBox^ box1101;
private: System::Windows::Forms::PictureBox^ box0000;
private: System::Windows::Forms::PictureBox^ box0001;
private: System::Windows::Forms::PictureBox^ box0011;
private: System::Windows::Forms::PictureBox^ box0110;
private: System::Windows::Forms::PictureBox^ box0111;
private: System::Windows::Forms::PictureBox^ box1111;
private: System::Windows::Forms::Button^ btn0001;
private: System::Windows::Forms::Button^ btn0011;
private: System::Windows::Forms::Button^ btn0111;
private: System::Windows::Forms::Button^ btn0110;
private: System::Windows::Forms::Button^ btOk;
private: System::Windows::Forms::CheckBox^ chNormDirs;
private: System::Windows::Forms::TextBox^ txSizeYUp;

private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::TextBox^ txSizeXUp;
private: System::Windows::Forms::TextBox^ txSizeDn;


private: System::Windows::Forms::Label^ label3;

private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::TextBox^ txKFillRnd;
private: System::Windows::Forms::TextBox^ txKSigmaY;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::TextBox^ txKSigmaX;
private: System::Windows::Forms::TextBox^ txKInertion;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::TextBox^ txKBorder;

private: System::Windows::Forms::Button^ btCancel;
private: System::Windows::Forms::TextBox^ txKLaysFrom;

private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::TextBox^ txKLaysTo;


private: System::Windows::Forms::PictureBox^ box1110;
protected:
	/// <summary>
	/// Verwendete Ressourcen bereinigen.
	/// </summary>
	~Form1(){
		if(components){
			delete components;
		}
	}


private: System::ComponentModel::IContainer^ components;


protected:

private:
	/// <summary>
	/// Erforderliche Designervariable.
	/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode fьr die Designerunterstьtzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geдndert werden.
		/// </summary>
	void InitializeComponent(void){
		this->box0110 = (gcnew System::Windows::Forms::PictureBox());
		this->box0000 = (gcnew System::Windows::Forms::PictureBox());
		this->box0001 = (gcnew System::Windows::Forms::PictureBox());
		this->box0011 = (gcnew System::Windows::Forms::PictureBox());
		this->box0111 = (gcnew System::Windows::Forms::PictureBox());
		this->box1111 = (gcnew System::Windows::Forms::PictureBox());
		this->box0010 = (gcnew System::Windows::Forms::PictureBox());
		this->box0100 = (gcnew System::Windows::Forms::PictureBox());
		this->box1000 = (gcnew System::Windows::Forms::PictureBox());
		this->box1010 = (gcnew System::Windows::Forms::PictureBox());
		this->box1100 = (gcnew System::Windows::Forms::PictureBox());
		this->box0101 = (gcnew System::Windows::Forms::PictureBox());
		this->box1001 = (gcnew System::Windows::Forms::PictureBox());
		this->box1011 = (gcnew System::Windows::Forms::PictureBox());
		this->box1101 = (gcnew System::Windows::Forms::PictureBox());
		this->box1110 = (gcnew System::Windows::Forms::PictureBox());
		this->btn0001 = (gcnew System::Windows::Forms::Button());
		this->btn0011 = (gcnew System::Windows::Forms::Button());
		this->btn0111 = (gcnew System::Windows::Forms::Button());
		this->btn0110 = (gcnew System::Windows::Forms::Button());
		this->btOk = (gcnew System::Windows::Forms::Button());
		this->chNormDirs = (gcnew System::Windows::Forms::CheckBox());
		this->txSizeYUp = (gcnew System::Windows::Forms::TextBox());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->txSizeXUp = (gcnew System::Windows::Forms::TextBox());
		this->txSizeDn = (gcnew System::Windows::Forms::TextBox());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->txKFillRnd = (gcnew System::Windows::Forms::TextBox());
		this->txKSigmaY = (gcnew System::Windows::Forms::TextBox());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->txKSigmaX = (gcnew System::Windows::Forms::TextBox());
		this->txKInertion = (gcnew System::Windows::Forms::TextBox());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->txKBorder = (gcnew System::Windows::Forms::TextBox());
		this->btCancel = (gcnew System::Windows::Forms::Button());
		this->txKLaysFrom = (gcnew System::Windows::Forms::TextBox());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->txKLaysTo = (gcnew System::Windows::Forms::TextBox());
		this->label11 = (gcnew System::Windows::Forms::Label());
		this->lbLaysCnt = (gcnew System::Windows::Forms::Label());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->lstMask0000 = (gcnew System::Windows::Forms::ListBox());
		this->lbMask0001 = (gcnew System::Windows::Forms::Label());
		this->lstMask0001 = (gcnew System::Windows::Forms::ListBox());
		this->label14 = (gcnew System::Windows::Forms::Label());
		this->lstMask0011 = (gcnew System::Windows::Forms::ListBox());
		this->label15 = (gcnew System::Windows::Forms::Label());
		this->lstMask1111 = (gcnew System::Windows::Forms::ListBox());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->lstMask0111 = (gcnew System::Windows::Forms::ListBox());
		this->label16 = (gcnew System::Windows::Forms::Label());
		this->lstMask0110 = (gcnew System::Windows::Forms::ListBox());
		this->txSeedRnd = (gcnew System::Windows::Forms::TextBox());
		this->label17 = (gcnew System::Windows::Forms::Label());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0110))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0000))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0001))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0011))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0111))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1111))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0010))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0100))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1000))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1010))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1100))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0101))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1001))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1011))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1101))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1110))->BeginInit();
		this->SuspendLayout();
		// 
		// box0110
		// 
		this->box0110->Location = System::Drawing::Point(263, 392);
		this->box0110->Name = L"box0110";
		this->box0110->Size = System::Drawing::Size(96, 96);
		this->box0110->TabIndex = 22;
		this->box0110->TabStop = false;
		this->box0110->Tag = L"0110";
		// 
		// box0000
		// 
		this->box0000->Location = System::Drawing::Point(25, 392);
		this->box0000->Name = L"box0000";
		this->box0000->Size = System::Drawing::Size(96, 96);
		this->box0000->TabIndex = 7;
		this->box0000->TabStop = false;
		this->box0000->Tag = L"0000";
		// 
		// box0001
		// 
		this->box0001->Location = System::Drawing::Point(25, 36);
		this->box0001->Name = L"box0001";
		this->box0001->Size = System::Drawing::Size(96, 96);
		this->box0001->TabIndex = 11;
		this->box0001->TabStop = false;
		this->box0001->Tag = L"0001";
		// 
		// box0011
		// 
		this->box0011->Location = System::Drawing::Point(25, 148);
		this->box0011->Name = L"box0011";
		this->box0011->Size = System::Drawing::Size(96, 96);
		this->box0011->TabIndex = 15;
		this->box0011->TabStop = false;
		this->box0011->Tag = L"0011";
		// 
		// box0111
		// 
		this->box0111->Location = System::Drawing::Point(25, 260);
		this->box0111->Name = L"box0111";
		this->box0111->Size = System::Drawing::Size(96, 96);
		this->box0111->TabIndex = 20;
		this->box0111->TabStop = false;
		this->box0111->Tag = L"0111";
		// 
		// box1111
		// 
		this->box1111->Location = System::Drawing::Point(144, 392);
		this->box1111->Name = L"box1111";
		this->box1111->Size = System::Drawing::Size(96, 96);
		this->box1111->TabIndex = 16;
		this->box1111->TabStop = false;
		this->box1111->Tag = L"1111";
		// 
		// box0010
		// 
		this->box0010->Location = System::Drawing::Point(174, 36);
		this->box0010->Name = L"box0010";
		this->box0010->Size = System::Drawing::Size(96, 96);
		this->box0010->TabIndex = 8;
		this->box0010->TabStop = false;
		this->box0010->Tag = L"0010";
		// 
		// box0100
		// 
		this->box0100->Location = System::Drawing::Point(412, 36);
		this->box0100->Name = L"box0100";
		this->box0100->Size = System::Drawing::Size(96, 96);
		this->box0100->TabIndex = 9;
		this->box0100->TabStop = false;
		this->box0100->Tag = L"0100";
		// 
		// box1000
		// 
		this->box1000->Location = System::Drawing::Point(293, 36);
		this->box1000->Name = L"box1000";
		this->box1000->Size = System::Drawing::Size(96, 96);
		this->box1000->TabIndex = 10;
		this->box1000->TabStop = false;
		this->box1000->Tag = L"1000";
		// 
		// box1010
		// 
		this->box1010->Location = System::Drawing::Point(174, 148);
		this->box1010->Name = L"box1010";
		this->box1010->Size = System::Drawing::Size(96, 96);
		this->box1010->TabIndex = 12;
		this->box1010->TabStop = false;
		this->box1010->Tag = L"1010";
		// 
		// box1100
		// 
		this->box1100->Location = System::Drawing::Point(293, 148);
		this->box1100->Name = L"box1100";
		this->box1100->Size = System::Drawing::Size(96, 96);
		this->box1100->TabIndex = 13;
		this->box1100->TabStop = false;
		this->box1100->Tag = L"1100";
		// 
		// box0101
		// 
		this->box0101->Location = System::Drawing::Point(412, 148);
		this->box0101->Name = L"box0101";
		this->box0101->Size = System::Drawing::Size(96, 96);
		this->box0101->TabIndex = 14;
		this->box0101->TabStop = false;
		this->box0101->Tag = L"0101";
		// 
		// box1001
		// 
		this->box1001->Location = System::Drawing::Point(412, 392);
		this->box1001->Name = L"box1001";
		this->box1001->Size = System::Drawing::Size(96, 96);
		this->box1001->TabIndex = 21;
		this->box1001->TabStop = false;
		this->box1001->Tag = L"1001";
		// 
		// box1011
		// 
		this->box1011->Location = System::Drawing::Point(174, 260);
		this->box1011->Name = L"box1011";
		this->box1011->Size = System::Drawing::Size(96, 96);
		this->box1011->TabIndex = 17;
		this->box1011->TabStop = false;
		this->box1011->Tag = L"1011";
		// 
		// box1101
		// 
		this->box1101->Location = System::Drawing::Point(412, 260);
		this->box1101->Name = L"box1101";
		this->box1101->Size = System::Drawing::Size(96, 96);
		this->box1101->TabIndex = 19;
		this->box1101->TabStop = false;
		this->box1101->Tag = L"1101";
		// 
		// box1110
		// 
		this->box1110->Location = System::Drawing::Point(293, 260);
		this->box1110->Name = L"box1110";
		this->box1110->Size = System::Drawing::Size(96, 96);
		this->box1110->TabIndex = 18;
		this->box1110->TabStop = false;
		this->box1110->Tag = L"1110";
		// 
		// btn0001
		// 
		this->btn0001->Location = System::Drawing::Point(127, 73);
		this->btn0001->Name = L"btn0001";
		this->btn0001->Size = System::Drawing::Size(41, 23);
		this->btn0001->TabIndex = 6;
		this->btn0001->Text = L">>";
		this->btn0001->UseVisualStyleBackColor = true;
		this->btn0001->Click += gcnew System::EventHandler(this, &Form1::btn0001_Click);
		// 
		// btn0011
		// 
		this->btn0011->Location = System::Drawing::Point(127, 185);
		this->btn0011->Name = L"btn0011";
		this->btn0011->Size = System::Drawing::Size(41, 23);
		this->btn0011->TabIndex = 6;
		this->btn0011->Text = L">>";
		this->btn0011->UseVisualStyleBackColor = true;
		this->btn0011->Click += gcnew System::EventHandler(this, &Form1::btn0011_Click);
		// 
		// btn0111
		// 
		this->btn0111->Location = System::Drawing::Point(127, 297);
		this->btn0111->Name = L"btn0111";
		this->btn0111->Size = System::Drawing::Size(41, 23);
		this->btn0111->TabIndex = 6;
		this->btn0111->Text = L">>";
		this->btn0111->UseVisualStyleBackColor = true;
		this->btn0111->Click += gcnew System::EventHandler(this, &Form1::btn0111_Click);
		// 
		// btn0110
		// 
		this->btn0110->Location = System::Drawing::Point(365, 429);
		this->btn0110->Name = L"btn0110";
		this->btn0110->Size = System::Drawing::Size(41, 23);
		this->btn0110->TabIndex = 6;
		this->btn0110->Text = L">>";
		this->btn0110->UseVisualStyleBackColor = true;
		this->btn0110->Click += gcnew System::EventHandler(this, &Form1::btn0110_Click);
		// 
		// btOk
		// 
		this->btOk->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->btOk->Location = System::Drawing::Point(536, 604);
		this->btOk->Name = L"btOk";
		this->btOk->Size = System::Drawing::Size(75, 23);
		this->btOk->TabIndex = 23;
		this->btOk->Text = L"Ok";
		this->btOk->UseVisualStyleBackColor = true;
		this->btOk->Click += gcnew System::EventHandler(this, &Form1::btOk_Click);
		// 
		// chNormDirs
		// 
		this->chNormDirs->AutoSize = true;
		this->chNormDirs->Location = System::Drawing::Point(557, 36);
		this->chNormDirs->Name = L"chNormDirs";
		this->chNormDirs->Size = System::Drawing::Size(68, 17);
		this->chNormDirs->TabIndex = 24;
		this->chNormDirs->Text = L"auto Dirs";
		this->chNormDirs->UseVisualStyleBackColor = true;
		// 
		// txSizeYUp
		// 
		this->txSizeYUp->Location = System::Drawing::Point(617, 77);
		this->txSizeYUp->Name = L"txSizeYUp";
		this->txSizeYUp->Size = System::Drawing::Size(37, 20);
		this->txSizeYUp->TabIndex = 25;
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(554, 84);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(57, 13);
		this->label1->TabIndex = 26;
		this->label1->Text = L"SizeUp  Y:";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(660, 83);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(17, 13);
		this->label2->TabIndex = 27;
		this->label2->Text = L"X:";
		// 
		// txSizeXUp
		// 
		this->txSizeXUp->Location = System::Drawing::Point(684, 77);
		this->txSizeXUp->Name = L"txSizeXUp";
		this->txSizeXUp->Size = System::Drawing::Size(44, 20);
		this->txSizeXUp->TabIndex = 28;
		// 
		// txSizeDn
		// 
		this->txSizeDn->Location = System::Drawing::Point(650, 103);
		this->txSizeDn->Name = L"txSizeDn";
		this->txSizeDn->Size = System::Drawing::Size(78, 20);
		this->txSizeDn->TabIndex = 25;
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(554, 110);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(90, 13);
		this->label3->TabIndex = 26;
		this->label3->Text = L"Size Dn Max(Y,X)";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(557, 148);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(48, 13);
		this->label4->TabIndex = 29;
		this->label4->Text = L"k fill Rnd";
		// 
		// txKFillRnd
		// 
		this->txKFillRnd->Location = System::Drawing::Point(612, 140);
		this->txKFillRnd->Name = L"txKFillRnd";
		this->txKFillRnd->Size = System::Drawing::Size(100, 20);
		this->txKFillRnd->TabIndex = 30;
		// 
		// txKSigmaY
		// 
		this->txKSigmaY->Location = System::Drawing::Point(611, 166);
		this->txKSigmaY->Name = L"txKSigmaY";
		this->txKSigmaY->Size = System::Drawing::Size(37, 20);
		this->txKSigmaY->TabIndex = 25;
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(548, 173);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(58, 13);
		this->label5->TabIndex = 26;
		this->label5->Text = L"kSigma  Y:";
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(654, 172);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(17, 13);
		this->label6->TabIndex = 27;
		this->label6->Text = L"X:";
		// 
		// txKSigmaX
		// 
		this->txKSigmaX->Location = System::Drawing::Point(678, 166);
		this->txKSigmaX->Name = L"txKSigmaX";
		this->txKSigmaX->Size = System::Drawing::Size(44, 20);
		this->txKSigmaX->TabIndex = 28;
		// 
		// txKInertion
		// 
		this->txKInertion->Location = System::Drawing::Point(612, 192);
		this->txKInertion->Name = L"txKInertion";
		this->txKInertion->Size = System::Drawing::Size(100, 20);
		this->txKInertion->TabIndex = 30;
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(557, 199);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(50, 13);
		this->label7->TabIndex = 29;
		this->label7->Text = L"k inertion";
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = System::Drawing::Point(556, 225);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(46, 13);
		this->label8->TabIndex = 29;
		this->label8->Text = L"k border";
		// 
		// txKBorder
		// 
		this->txKBorder->Location = System::Drawing::Point(611, 218);
		this->txKBorder->Name = L"txKBorder";
		this->txKBorder->Size = System::Drawing::Size(100, 20);
		this->txKBorder->TabIndex = 30;
		// 
		// btCancel
		// 
		this->btCancel->Location = System::Drawing::Point(618, 604);
		this->btCancel->Name = L"btCancel";
		this->btCancel->Size = System::Drawing::Size(75, 23);
		this->btCancel->TabIndex = 33;
		this->btCancel->Text = L"Cancel";
		this->btCancel->UseVisualStyleBackColor = true;
		this->btCancel->Click += gcnew System::EventHandler(this, &Form1::btCancel_Click);
		// 
		// txKLaysFrom
		// 
		this->txKLaysFrom->Location = System::Drawing::Point(612, 260);
		this->txKLaysFrom->Name = L"txKLaysFrom";
		this->txKLaysFrom->Size = System::Drawing::Size(37, 20);
		this->txKLaysFrom->TabIndex = 25;
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Location = System::Drawing::Point(549, 267);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(58, 13);
		this->label9->TabIndex = 26;
		this->label9->Text = L"kLays from";
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Location = System::Drawing::Point(655, 266);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(19, 13);
		this->label10->TabIndex = 27;
		this->label10->Text = L"to ";
		// 
		// txKLaysTo
		// 
		this->txKLaysTo->Location = System::Drawing::Point(679, 260);
		this->txKLaysTo->Name = L"txKLaysTo";
		this->txKLaysTo->Size = System::Drawing::Size(44, 20);
		this->txKLaysTo->TabIndex = 28;
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = System::Drawing::Point(543, 297);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(68, 13);
		this->label11->TabIndex = 34;
		this->label11->Text = L"Lays count =";
		// 
		// lbLaysCnt
		// 
		this->lbLaysCnt->AutoSize = true;
		this->lbLaysCnt->Location = System::Drawing::Point(612, 297);
		this->lbLaysCnt->Name = L"lbLaysCnt";
		this->lbLaysCnt->Size = System::Drawing::Size(13, 13);
		this->lbLaysCnt->TabIndex = 35;
		this->lbLaysCnt->Text = L"0";
		// 
		// label12
		// 
		this->label12->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->label12->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->label12->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
														   static_cast<System::Byte>(204)));
		this->label12->Location = System::Drawing::Point(557, 342);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(34, 35);
		this->label12->TabIndex = 36;
		this->label12->Text = L"0 0 0 0";
		this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lstMask0000
		// 
		this->lstMask0000->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															   static_cast<System::Byte>(204)));
		this->lstMask0000->FormattingEnabled = true;
		this->lstMask0000->ItemHeight = 16;
		this->lstMask0000->Items->AddRange(gcnew cli::array< System::Object^  >(2){ L"0", L"1" });
		this->lstMask0000->Location = System::Drawing::Point(597, 342);
		this->lstMask0000->Name = L"lstMask0000";
		this->lstMask0000->Size = System::Drawing::Size(20, 36);
		this->lstMask0000->TabIndex = 37;
		// 
		// lbMask0001
		// 
		this->lbMask0001->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->lbMask0001->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->lbMask0001->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															  static_cast<System::Byte>(204)));
		this->lbMask0001->Location = System::Drawing::Point(643, 343);
		this->lbMask0001->Name = L"lbMask0001";
		this->lbMask0001->Size = System::Drawing::Size(34, 35);
		this->lbMask0001->TabIndex = 36;
		this->lbMask0001->Text = L"1 0 0 0";
		this->lbMask0001->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lstMask0001
		// 
		this->lstMask0001->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															   static_cast<System::Byte>(204)));
		this->lstMask0001->FormattingEnabled = true;
		this->lstMask0001->ItemHeight = 16;
		this->lstMask0001->Items->AddRange(gcnew cli::array< System::Object^  >(2){ L"0", L"1" });
		this->lstMask0001->Location = System::Drawing::Point(683, 343);
		this->lstMask0001->Name = L"lstMask0001";
		this->lstMask0001->Size = System::Drawing::Size(20, 36);
		this->lstMask0001->TabIndex = 37;
		// 
		// label14
		// 
		this->label14->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->label14->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->label14->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
														   static_cast<System::Byte>(204)));
		this->label14->Location = System::Drawing::Point(557, 394);
		this->label14->Name = L"label14";
		this->label14->Size = System::Drawing::Size(34, 35);
		this->label14->TabIndex = 36;
		this->label14->Text = L"1 1 0 0";
		this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lstMask0011
		// 
		this->lstMask0011->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															   static_cast<System::Byte>(204)));
		this->lstMask0011->FormattingEnabled = true;
		this->lstMask0011->ItemHeight = 16;
		this->lstMask0011->Items->AddRange(gcnew cli::array< System::Object^  >(2){ L"0", L"1" });
		this->lstMask0011->Location = System::Drawing::Point(597, 394);
		this->lstMask0011->Name = L"lstMask0011";
		this->lstMask0011->Size = System::Drawing::Size(20, 36);
		this->lstMask0011->TabIndex = 37;
		// 
		// label15
		// 
		this->label15->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->label15->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->label15->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
														   static_cast<System::Byte>(204)));
		this->label15->Location = System::Drawing::Point(643, 444);
		this->label15->Name = L"label15";
		this->label15->Size = System::Drawing::Size(34, 35);
		this->label15->TabIndex = 36;
		this->label15->Text = L"1 1 1 1";
		this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lstMask1111
		// 
		this->lstMask1111->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															   static_cast<System::Byte>(204)));
		this->lstMask1111->FormattingEnabled = true;
		this->lstMask1111->ItemHeight = 16;
		this->lstMask1111->Items->AddRange(gcnew cli::array< System::Object^  >(2){ L"0", L"1" });
		this->lstMask1111->Location = System::Drawing::Point(683, 444);
		this->lstMask1111->Name = L"lstMask1111";
		this->lstMask1111->Size = System::Drawing::Size(20, 36);
		this->lstMask1111->TabIndex = 37;
		// 
		// label13
		// 
		this->label13->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->label13->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->label13->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
														   static_cast<System::Byte>(204)));
		this->label13->Location = System::Drawing::Point(557, 443);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(34, 35);
		this->label13->TabIndex = 36;
		this->label13->Text = L"1 1 1 0";
		this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lstMask0111
		// 
		this->lstMask0111->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															   static_cast<System::Byte>(204)));
		this->lstMask0111->FormattingEnabled = true;
		this->lstMask0111->ItemHeight = 16;
		this->lstMask0111->Items->AddRange(gcnew cli::array< System::Object^  >(2){ L"0", L"1" });
		this->lstMask0111->Location = System::Drawing::Point(597, 443);
		this->lstMask0111->Name = L"lstMask0111";
		this->lstMask0111->Size = System::Drawing::Size(20, 36);
		this->lstMask0111->TabIndex = 37;
		// 
		// label16
		// 
		this->label16->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->label16->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->label16->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
														   static_cast<System::Byte>(204)));
		this->label16->Location = System::Drawing::Point(643, 395);
		this->label16->Name = L"label16";
		this->label16->Size = System::Drawing::Size(34, 35);
		this->label16->TabIndex = 36;
		this->label16->Text = L"0 1 1 0";
		this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lstMask0110
		// 
		this->lstMask0110->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
															   static_cast<System::Byte>(204)));
		this->lstMask0110->FormattingEnabled = true;
		this->lstMask0110->ItemHeight = 16;
		this->lstMask0110->Items->AddRange(gcnew cli::array< System::Object^  >(2){ L"0", L"1" });
		this->lstMask0110->Location = System::Drawing::Point(683, 395);
		this->lstMask0110->Name = L"lstMask0110";
		this->lstMask0110->Size = System::Drawing::Size(20, 36);
		this->lstMask0110->TabIndex = 37;
		// 
		// txSeedRnd
		// 
		this->txSeedRnd->Location = System::Drawing::Point(678, 37);
		this->txSeedRnd->Name = L"txSeedRnd";
		this->txSeedRnd->Size = System::Drawing::Size(74, 20);
		this->txSeedRnd->TabIndex = 38;
		this->txSeedRnd->Text = L"-1";
		// 
		// label17
		// 
		this->label17->AutoSize = true;
		this->label17->Location = System::Drawing::Point(621, 44);
		this->label17->Name = L"label17";
		this->label17->Size = System::Drawing::Size(56, 13);
		this->label17->TabIndex = 39;
		this->label17->Text = L"seed Rnd:";
		// 
		// Form1
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(803, 662);
		this->Controls->Add(this->label17);
		this->Controls->Add(this->txSeedRnd);
		this->Controls->Add(this->lstMask1111);
		this->Controls->Add(this->lstMask0110);
		this->Controls->Add(this->lstMask0011);
		this->Controls->Add(this->lstMask0111);
		this->Controls->Add(this->lstMask0001);
		this->Controls->Add(this->lstMask0000);
		this->Controls->Add(this->label15);
		this->Controls->Add(this->label16);
		this->Controls->Add(this->label14);
		this->Controls->Add(this->label13);
		this->Controls->Add(this->lbMask0001);
		this->Controls->Add(this->label12);
		this->Controls->Add(this->lbLaysCnt);
		this->Controls->Add(this->label11);
		this->Controls->Add(this->btCancel);
		this->Controls->Add(this->txKBorder);
		this->Controls->Add(this->txKInertion);
		this->Controls->Add(this->label8);
		this->Controls->Add(this->txKFillRnd);
		this->Controls->Add(this->label7);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->txKLaysTo);
		this->Controls->Add(this->txKSigmaX);
		this->Controls->Add(this->label10);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->txSizeXUp);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label9);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->txKLaysFrom);
		this->Controls->Add(this->txKSigmaY);
		this->Controls->Add(this->txSizeDn);
		this->Controls->Add(this->txSizeYUp);
		this->Controls->Add(this->chNormDirs);
		this->Controls->Add(this->btOk);
		this->Controls->Add(this->btn0110);
		this->Controls->Add(this->btn0111);
		this->Controls->Add(this->btn0011);
		this->Controls->Add(this->btn0001);
		this->Controls->Add(this->box0000);
		this->Controls->Add(this->box0010);
		this->Controls->Add(this->box0100);
		this->Controls->Add(this->box1000);
		this->Controls->Add(this->box0001);
		this->Controls->Add(this->box1010);
		this->Controls->Add(this->box1100);
		this->Controls->Add(this->box0101);
		this->Controls->Add(this->box0011);
		this->Controls->Add(this->box1111);
		this->Controls->Add(this->box1011);
		this->Controls->Add(this->box1110);
		this->Controls->Add(this->box1101);
		this->Controls->Add(this->box0111);
		this->Controls->Add(this->box1001);
		this->Controls->Add(this->box0110);
		this->Name = L"Form1";
		this->Text = L"Options";
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0110))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0000))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0001))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0011))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0111))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1111))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0010))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0100))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1000))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1010))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1100))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box0101))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1001))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1011))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1101))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box1110))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

private: System::Void btn0001_Click(System::Object^ sender, System::EventArgs^ e){
	cells[0b0010]->Rotate(cells[0b0001]);
	box0010->Refresh();

	cells[0b1000]->Rotate(cells[0b0010]);
	box1000->Refresh();

	cells[0b0100]->Rotate(cells[0b1000]);
	box0100->Refresh();
} // /////////////////////////////////////////////////////////////////////////
private: System::Void btn0011_Click(System::Object^ sender, System::EventArgs^ e){
	cells[0b1010]->Rotate(cells[0b0011]);
	box1010->Refresh();

	cells[0b1100]->Rotate(cells[0b1010]);
	box1100->Refresh();

	cells[0b0101]->Rotate(cells[0b1100]);
	box0101->Refresh();
} // /////////////////////////////////////////////////////////////////////////
private: System::Void btn0111_Click(System::Object^ sender, System::EventArgs^ e){
	cells[0b1011]->Rotate(cells[0b0111]);
	box1011->Refresh();

	cells[0b1110]->Rotate(cells[0b1011]);
	box1110->Refresh();

	cells[0b1101]->Rotate(cells[0b1110]);
	box1101->Refresh();
} // /////////////////////////////////////////////////////////////////////////
private: System::Void btn0110_Click(System::Object^ sender, System::EventArgs^ e){
	cells[0b1001]->Rotate(cells[0b0110]);
	box1001->Refresh();
} // /////////////////////////////////////////////////////////////////////////
private: System::Void btOk_Click(System::Object^ sender, System::EventArgs^ e){
	for(int a = 0, n = 0; a < 16; a++)
		for(int ncell = 0; ncell < 4; ncell++)
			for(int nitem = 0; nitem < 4; nitem++)
				iArr[n++] = getDir(a, ncell, nitem);

	iArr[InpOptions::AMasks] = lstMask0000->SelectedIndex;
	iArr[InpOptions::AMasks + 1] = iArr[InpOptions::AMasks + 2] = iArr[InpOptions::AMasks + 4] = iArr[InpOptions::AMasks + 8] = lstMask0001->SelectedIndex;
	iArr[InpOptions::AMasks + 3] = iArr[InpOptions::AMasks + 5] = iArr[InpOptions::AMasks + 10] = iArr[InpOptions::AMasks + 12] = lstMask0011->SelectedIndex;
	iArr[InpOptions::AMasks + 6] = iArr[InpOptions::AMasks + 9] = lstMask0110->SelectedIndex;
	iArr[InpOptions::AMasks + 7] = iArr[InpOptions::AMasks + 11] = iArr[InpOptions::AMasks + 13] = iArr[InpOptions::AMasks + 14] = lstMask0111->SelectedIndex;
	iArr[InpOptions::AMasks + 15] = lstMask1111->SelectedIndex;

	iArr[InpOptions::NormDir] = converti(chNormDirs);
	iArr[InpOptions::SeedRnd] = converti(txSeedRnd);

	iArr[InpOptions::LaysSzUpY] = converti(txSizeYUp);
	iArr[InpOptions::LaysSzUpX] = converti(txSizeXUp);
	iArr[InpOptions::LaysSzDn] = converti(txSizeDn);

	dArr[InpOptions::kFillRnd] = convertd(txKFillRnd);
	dArr[InpOptions::kSigmaY] = convertd(txKSigmaY);
	dArr[InpOptions::kSigmaX] = convertd(txKSigmaX);
	dArr[InpOptions::kInertion] = convertd(txKInertion);
	dArr[InpOptions::kBorder] = convertd(txKBorder);

	int cnt = iArr[InpOptions::LaysCnt] - 1;
	if(cnt <= 1){
		iArr[InpOptions::Restart] = 0;
	} else{
		double kfrom = convertd(txKLaysFrom);
		double kto = convertd(txKLaysTo);
		double step = (kto - kfrom) / (cnt - 1);
		for(int n = 0; n < cnt; n++)
			dArr[InpOptions::kLays + n] = kfrom + step * n;
		iArr[InpOptions::Restart] = 1;
	}
	this->Close();
} // ///////////////////////////////////////////////////////////////////////////
private: System::Void btCancel_Click(System::Object^ sender, System::EventArgs^ e){
	iArr[InpOptions::Restart] = 0;
	this->Close();
} // ///////////////////////////////////////////////////////////////////////////
private: double convertd(TextBox^ tx){
	double result;
	String^ value = tx->Text;
	try{
		result = Convert::ToDouble(value);
	}
	catch(String^ s){
		Console::WriteLine("Unable to convert '{0}' to a Double.", s);
	}
	return result;
} // ///////////////////////////////////////////////////////////////////////////
private: int converti(TextBox^ tx){
	int result;
	String^ value = tx->Text;
	try{
		result = Convert::ToInt32(value);
	}
	catch(String^ s){
		Console::WriteLine("Unable to convert '{0}' to a Double.", s);
	}
	return result;
} // ///////////////////////////////////////////////////////////////////////////
private: int converti(CheckBox^ ch){
	return ch->Checked ? 1 : 0;
} // ///////////////////////////////////////////////////////////////////////////
}; // *******************************************************************************
}
