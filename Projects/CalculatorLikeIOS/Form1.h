//#include <string>
//#include <cstring>
//using namespace std;
#include <cmath>

bool usedComma = false;
bool first = false;
int pushedButton = 0;
/*__int64*/ double a, b;

#pragma once


namespace proj1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//using namespace System::String;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button17;


	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Button^  button20;
	private: System::Windows::Forms::Button^  button19;




	protected: 


	protected: 

	protected: 

















	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::WindowText;
			this->textBox1->ForeColor = System::Drawing::Color::White;
			this->textBox1->Location = System::Drawing::Point(0, -1);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->textBox1->Size = System::Drawing::Size(200, 70);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"0";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(153, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(44, 40);
			this->button1->TabIndex = 1;
			this->button1->Text = L"/";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(153, 53);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(44, 40);
			this->button2->TabIndex = 2;
			this->button2->Text = L"*";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Location = System::Drawing::Point(153, 103);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(44, 40);
			this->button3->TabIndex = 3;
			this->button3->Text = L"-";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(153, 153);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(44, 40);
			this->button4->TabIndex = 3;
			this->button4->Text = L"+";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button5->Location = System::Drawing::Point(3, 3);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(44, 40);
			this->button5->TabIndex = 4;
			this->button5->Text = L"AC";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel1->Controls->Add(this->button20, 3, 4);
			this->tableLayoutPanel1->Controls->Add(this->button16, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->button19, 2, 4);
			this->tableLayoutPanel1->Controls->Add(this->button15, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->button14, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->button13, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->button12, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->button11, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->button10, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->button9, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->button8, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->button7, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->button6, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->button1, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->button3, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->button5, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button2, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->button4, 3, 3);
			this->tableLayoutPanel1->Controls->Add(this->button17, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->button18, 1, 4);
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 75);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(200, 250);
			this->tableLayoutPanel1->TabIndex = 5;
			// 
			// button20
			// 
			this->button20->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button20->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->button20->ForeColor = System::Drawing::Color::White;
			this->button20->Location = System::Drawing::Point(153, 203);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(44, 44);
			this->button20->TabIndex = 20;
			this->button20->Text = L"=";
			this->button20->UseVisualStyleBackColor = false;
			this->button20->Click += gcnew System::EventHandler(this, &Form1::button20_Click);
			// 
			// button16
			// 
			this->button16->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button16->Location = System::Drawing::Point(103, 153);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(44, 40);
			this->button16->TabIndex = 15;
			this->button16->Text = L"3";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::button16_Click);
			// 
			// button19
			// 
			this->button19->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button19->Location = System::Drawing::Point(103, 203);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(44, 44);
			this->button19->TabIndex = 18;
			this->button19->Text = L",";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &Form1::button19_Click);
			// 
			// button15
			// 
			this->button15->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button15->Location = System::Drawing::Point(53, 153);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(44, 40);
			this->button15->TabIndex = 14;
			this->button15->Text = L"2";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::button15_Click);
			// 
			// button14
			// 
			this->button14->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button14->Location = System::Drawing::Point(3, 153);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(44, 40);
			this->button14->TabIndex = 13;
			this->button14->Text = L"1";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
			// 
			// button13
			// 
			this->button13->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button13->Location = System::Drawing::Point(103, 103);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(44, 40);
			this->button13->TabIndex = 12;
			this->button13->Text = L"6";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// button12
			// 
			this->button12->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button12->Location = System::Drawing::Point(53, 103);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(44, 40);
			this->button12->TabIndex = 11;
			this->button12->Text = L"5";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
			// 
			// button11
			// 
			this->button11->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button11->Location = System::Drawing::Point(3, 103);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(44, 40);
			this->button11->TabIndex = 10;
			this->button11->Text = L"4";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
			// 
			// button10
			// 
			this->button10->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button10->Location = System::Drawing::Point(103, 53);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(44, 40);
			this->button10->TabIndex = 9;
			this->button10->Text = L"9";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// button9
			// 
			this->button9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button9->Location = System::Drawing::Point(53, 53);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(44, 40);
			this->button9->TabIndex = 8;
			this->button9->Text = L"8";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// button8
			// 
			this->button8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button8->Location = System::Drawing::Point(3, 53);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(44, 40);
			this->button8->TabIndex = 7;
			this->button8->Text = L"7";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// button7
			// 
			this->button7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button7->Location = System::Drawing::Point(103, 3);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(44, 40);
			this->button7->TabIndex = 6;
			this->button7->Text = L"cos";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button6
			// 
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->Location = System::Drawing::Point(53, 3);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(44, 40);
			this->button6->TabIndex = 5;
			this->button6->Text = L"sin";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button17
			// 
			this->button17->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button17->Location = System::Drawing::Point(3, 203);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(44, 44);
			this->button17->TabIndex = 16;
			this->button17->Text = L"0";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &Form1::button17_Click);
			// 
			// button18
			// 
			this->button18->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button18->Location = System::Drawing::Point(53, 203);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(44, 44);
			this->button18->TabIndex = 19;
			this->button18->Text = L"00";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &Form1::button18_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlText;
			this->ClientSize = System::Drawing::Size(200, 328);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"Form1";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (first) {
				 this->textBox1->Text = L"0";
				 first = false; 
			 } else {
				 if (this->textBox1->Text->Length < 9)
			        if (this->textBox1->Text != "0")
				        this->textBox1->Text += L"0";
			 }
		 }
private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) {	
			 if (!first) {
				 if (this->textBox1->Text->Length < 8)
			         if (this->textBox1->Text != "0")
				         this->textBox1->Text += L"00";
			 } 
		 }
private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (!usedComma && !first) {
				     usedComma = true;
					 this->textBox1->Text += L",";
			 }
		 }
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
			  if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"1";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"1";
		 }
private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"2";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"2";
		 }
private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"3";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"3";
		 }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"4";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"4";
		 }
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"5";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"5";
		 }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"6";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"6";
		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"7";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"7";
		 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
          if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"8";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"8";
		 }
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
	      if (this->textBox1->Text == "0" || first) {
				 this->textBox1->Text = L"9";
				 first = false;
		      } else
				 if (this->textBox1->Text->Length < 9)	
				     this->textBox1->Text += L"9";
		 }

System:: String^ leftOperand;
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->textBox1->Text = L"0";
			 usedComma = false;
			 first = false;
			 pushedButton = false;
			 leftOperand = "0";
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (pushedButton) {
				 a = Convert::ToDouble(leftOperand);
				 b = Convert::ToDouble(this->textBox1->Text);
				 if (pushedButton == 1) this->textBox1->Text = Convert::ToString(a + b); 
				 if (pushedButton == 2) this->textBox1->Text = Convert::ToString(a - b);
				 if (pushedButton == 3) this->textBox1->Text = Convert::ToString(a * b);
				 if (pushedButton == 4) 
					 if (b == 0) 
                          this->textBox1->Text = "ERROR!!!";
					 else 
					      this->textBox1->Text = Convert::ToString(a / b);

			 }
			 if (this->textBox1->Text == "ERROR!!!") 
				 leftOperand = "0";
			 else
			     leftOperand = this->textBox1->Text;

			 usedComma = false;
			 first = true;
			 pushedButton = 1;			             
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			  if (pushedButton) {
				 a = Convert::ToDouble(leftOperand);
				 b = Convert::ToDouble(this->textBox1->Text);
				 if (pushedButton == 1) this->textBox1->Text = Convert::ToString(a + b); 
				 if (pushedButton == 2) this->textBox1->Text = Convert::ToString(a - b);
				 if (pushedButton == 3) this->textBox1->Text = Convert::ToString(a * b);
				 if (pushedButton == 4) 
					 if (b == 0) 
                          this->textBox1->Text = "ERROR!!!";
					 else 
					      this->textBox1->Text = Convert::ToString(a / b);

			 }
			 if (this->textBox1->Text == "ERROR!!!") 
				 leftOperand = "0";
			 else
			     leftOperand = this->textBox1->Text;

			 usedComma = false;
			 first = true;
			 pushedButton = 2;		
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			  if (pushedButton) {
				 a = Convert::ToDouble(leftOperand);
				 b = Convert::ToDouble(this->textBox1->Text);
				 if (pushedButton == 1) this->textBox1->Text = Convert::ToString(a + b); 
				 if (pushedButton == 2) this->textBox1->Text = Convert::ToString(a - b);
				 if (pushedButton == 3) this->textBox1->Text = Convert::ToString(a * b);
				 if (pushedButton == 4) 
					 if (b == 0) 
                          this->textBox1->Text = "ERROR!!!";
					 else 
					      this->textBox1->Text = Convert::ToString(a / b);

			 }
			 if (this->textBox1->Text == "ERROR!!!") 
				 leftOperand = "0";
			 else
			     leftOperand = this->textBox1->Text;

			 usedComma = false;
			 first = true;
			 pushedButton = 3;		
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			  if (pushedButton) {
				 a = Convert::ToDouble(leftOperand);
				 b = Convert::ToDouble(this->textBox1->Text);
				 if (pushedButton == 1) this->textBox1->Text = Convert::ToString(a + b); 
				 if (pushedButton == 2) this->textBox1->Text = Convert::ToString(a - b);
				 if (pushedButton == 3) this->textBox1->Text = Convert::ToString(a * b);
				 if (pushedButton == 4) 
					 if (b == 0) 
                          this->textBox1->Text = "ERROR!!!";
					 else 
					      this->textBox1->Text = Convert::ToString(a / b);

			 }
			 if (this->textBox1->Text == "ERROR!!!") 
				 leftOperand = "0";
			 else
			     leftOperand = this->textBox1->Text;

			 usedComma = false;
			 first = true;
			 pushedButton = 4;		
		 }
private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {
			  if (pushedButton) {
				 a = Convert::ToDouble(leftOperand);
				 b = Convert::ToDouble(this->textBox1->Text);
				 if (pushedButton == 1) this->textBox1->Text = Convert::ToString(a + b); 
				 if (pushedButton == 2) this->textBox1->Text = Convert::ToString(a - b);
				 if (pushedButton == 3) this->textBox1->Text = Convert::ToString(a * b);
				 if (pushedButton == 4) 
					 if (b == 0) 
                          this->textBox1->Text = "ERROR!!!";
					 else 
					      this->textBox1->Text = Convert::ToString(a / b);

			 }
			 if (this->textBox1->Text == "ERROR!!!") 
				 leftOperand = "0";
			 else
			     leftOperand = this->textBox1->Text;

			 usedComma = false;
			 first = true;
			 pushedButton = 0;		
		 }


private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->textBox1->Text = Convert :: ToString(sin(Convert:: ToDouble(this->textBox1->Text)));
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->textBox1->Text = Convert :: ToString(cos(Convert:: ToDouble(this->textBox1->Text)));
		 }
};
}

