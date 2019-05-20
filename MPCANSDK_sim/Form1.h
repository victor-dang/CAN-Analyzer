#pragma comment(lib,"MPCANCtrl.lib")
#include "MPCANCtrl.h"

#pragma once

#include <cstdlib> // for mbstowcs()
#include <clocale> // for setlocale()
#include <cstring>

namespace MPCANSDK_sim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ER ret;

	/* 構造体のインスタンス生成 */
	StMPCANFrame CANFrame;
	StMPCANSlot CANSlot[24];
	StMPCANLog* CANLog;

	/// <summary>
	/// Form1 の概要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Data;
	protected: 
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  msec;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  usec;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Dir;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  IDformat;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DLC;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  Stop_Button;
	private: System::Windows::Forms::Button^  Start_Button;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  ChangeData_Button;
	private: System::Windows::Forms::Button^  SlotSend_Button;
	private: System::Windows::Forms::Button^  DirectSend_Button;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
	


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->Data = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->msec = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->usec = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Dir = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->IDformat = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DLC = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Stop_Button = (gcnew System::Windows::Forms::Button());
			this->Start_Button = (gcnew System::Windows::Forms::Button());
			this->ChangeData_Button = (gcnew System::Windows::Forms::Button());
			this->SlotSend_Button = (gcnew System::Windows::Forms::Button());
			this->DirectSend_Button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// Data
			// 
			this->Data->HeaderText = L"Data";
			this->Data->Name = L"Data";
			this->Data->Width = 200;
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->msec, this->usec, 
				this->Dir, this->IDformat, this->ID, this->DLC, this->Data});
			this->dataGridView1->Location = System::Drawing::Point(7, 41);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->Height = 21;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(445, 171);
			this->dataGridView1->TabIndex = 15;
			// 
			// msec
			// 
			this->msec->HeaderText = L"msec";
			this->msec->Name = L"msec";
			this->msec->Width = 50;
			// 
			// usec
			// 
			this->usec->HeaderText = L"usec";
			this->usec->Name = L"usec";
			this->usec->Width = 50;
			// 
			// Dir
			// 
			this->Dir->HeaderText = L"Dir";
			this->Dir->Name = L"Dir";
			this->Dir->Width = 50;
			// 
			// IDformat
			// 
			this->IDformat->HeaderText = L"IDformat";
			this->IDformat->Name = L"IDformat";
			this->IDformat->Width = 50;
			// 
			// ID
			// 
			this->ID->HeaderText = L"ID";
			this->ID->Name = L"ID";
			this->ID->Width = 50;
			// 
			// DLC
			// 
			this->DLC->HeaderText = L"DLC";
			this->DLC->Name = L"DLC";
			this->DLC->Width = 50;
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Stop_Button
			// 
			this->Stop_Button->Enabled = false;
			this->Stop_Button->Location = System::Drawing::Point(377, 12);
			this->Stop_Button->Name = L"Stop_Button";
			this->Stop_Button->Size = System::Drawing::Size(75, 23);
			this->Stop_Button->TabIndex = 14;
			this->Stop_Button->Text = L"Stop";
			this->Stop_Button->UseVisualStyleBackColor = true;
			this->Stop_Button->Click += gcnew System::EventHandler(this, &Form1::Stop_Button_Click);
			// 
			// Start_Button
			// 
			this->Start_Button->Location = System::Drawing::Point(30, 12);
			this->Start_Button->Name = L"Start_Button";
			this->Start_Button->Size = System::Drawing::Size(75, 23);
			this->Start_Button->TabIndex = 13;
			this->Start_Button->Text = L"Start";
			this->Start_Button->UseVisualStyleBackColor = true;
			this->Start_Button->Click += gcnew System::EventHandler(this, &Form1::Start_Button_Click);
			// 
			// ChangeData_Button
			// 
			this->ChangeData_Button->Location = System::Drawing::Point(30, 219);
			this->ChangeData_Button->Name = L"ChangeData_Button";
			this->ChangeData_Button->Size = System::Drawing::Size(75, 23);
			this->ChangeData_Button->TabIndex = 16;
			this->ChangeData_Button->Text = L"ChangeData";
			this->ChangeData_Button->UseVisualStyleBackColor = true;
			this->ChangeData_Button->Click += gcnew System::EventHandler(this, &Form1::ChangeData_Button_Click);
			// 
			// SlotSend_Button
			// 
			this->SlotSend_Button->Location = System::Drawing::Point(187, 218);
			this->SlotSend_Button->Name = L"SlotSend_Button";
			this->SlotSend_Button->Size = System::Drawing::Size(75, 23);
			this->SlotSend_Button->TabIndex = 17;
			this->SlotSend_Button->Text = L"SlotSend";
			this->SlotSend_Button->UseVisualStyleBackColor = true;
			this->SlotSend_Button->Click += gcnew System::EventHandler(this, &Form1::SlotSend_Button_Click);
			// 
			// DirectSend_Button
			// 
			this->DirectSend_Button->Location = System::Drawing::Point(377, 219);
			this->DirectSend_Button->Name = L"DirectSend_Button";
			this->DirectSend_Button->Size = System::Drawing::Size(75, 23);
			this->DirectSend_Button->TabIndex = 18;
			this->DirectSend_Button->Text = L"DirectSend";
			this->DirectSend_Button->UseVisualStyleBackColor = true;
			this->DirectSend_Button->Click += gcnew System::EventHandler(this, &Form1::DirectSend_Button_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(468, 262);
			this->Controls->Add(this->DirectSend_Button);
			this->Controls->Add(this->SlotSend_Button);
			this->Controls->Add(this->ChangeData_Button);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->Stop_Button);
			this->Controls->Add(this->Start_Button);
			this->Name = L"Form1";
			this->Text = L"MicroPecker CAN SDK Sample Porgram(Simuration)";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			/* MicroPeckerオープン */
			long SID;
			ret = MPCANOpen(&SID);
			if (ret != E_OK)
		    {
		        MessageBox::Show("error");
			    exit(1);
		    }
			else
			{
			    /* LED消灯 */
			    MPCANSetLED(CAN_LED_OFF, CAN_LED_OFF, CAN_LED_OFF);
			}

			/* APIバージョン情報 */
			StMPCANVersion Version;
			MPCANGetVersion(&Version);
			MessageBox::Show(%String(Version.APIVersion));

		 }
private: System::Void Start_Button_Click(System::Object^  sender, System::EventArgs^  e) {

			
			dataGridView1->Rows->Clear(); 
						
			/* ボタンの有効・無効を変更 */
			Start_Button->Enabled = false;
			Stop_Button->Enabled = true;
			ChangeData_Button->Enabled = true;
			SlotSend_Button->Enabled = true;
			DirectSend_Button->Enabled  =true;

			/* CAN通信パラメータ設定 */
			ret = MPCANSetParamSimple(CAN_MODE_SIM, CAN_REMOTE_DIS, CAN_PARAM_BR_500K, CAN_PARAM_SP_70P);
			if (ret != E_OK)
			{
			    MessageBox::Show("error");
				exit(1);
			}

			/* シミュレーションデータ設定 */
			for (int i = 0; i < 2; i++)
			{
				CANSlot[i].Enabled = CAN_SLOT_ENA;	
				CANSlot[i].Cycle = 1000;
				CANSlot[i].Count = 0;
				CANSlot[i].Frame.IdFormat = CAN_ID_STD;
				CANSlot[i].Frame.Rtr = CAN_RTR_DATA;
				CANSlot[i].Frame.Dlc = 8;					 
				for (int j = 0; j < 8; j++)
				{
					unsigned char dt = 0;
					if (i == 1)
					{
						dt = 0x20;
					}

					CANSlot[i].Frame.Data[j] = dt;
				}
			}
			CANSlot[0].Frame.Id = 0x100;
			CANSlot[1].Frame.Id = 0x200;
			CANSlot[0].EventKind = CAN_EVENT_PERIODIC;
			CANSlot[1].EventKind = CAN_EVENT_EVENT;

			/* スロット設定 */
			ret = MPCANSetSlot(CANSlot, 2);
			if (ret != E_OK)
			{
				MessageBox::Show("error");
				exit(1);
			}
			/* モニタリングスタート */	 
			ret = MPCANMonitorStart();
			if (ret != E_OK)
			{
				MessageBox::Show("error");
				exit(1);
			}
			/* タイマ開始 */
			timer1->Enabled = true;

		 }
private: System::Void Stop_Button_Click(System::Object^  sender, System::EventArgs^  e) {

			/* タイマ停止 */
			timer1->Enabled = false;

			/* ボタンの有効・無効を変更 */
			Start_Button->Enabled = true;
			Stop_Button->Enabled = false;

			/* モニタリング停止 */
			unsigned long MSec; 
			unsigned short USec;
			ret = MPCANMonitorStop(&MSec, &USec);
			if (ret != E_OK)
			{
				MessageBox::Show("error");
				exit(1);
			}

		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

			/*モニタログ取得*/
			StMPCANLog* CANLog;
			unsigned long Count;
			unsigned char BufferOver;
			ret = MPCANGetLog(&CANLog, &Count, &BufferOver);
			if (ret != E_OK)
			{
			    exit(1);
			}
			 
			/* 最新の100レコードまでを表示 */
			int start = 0;
			if (Count >= 100) 
			{
			    start = Count - 100;
			}

			/* ログ表示 */
			for (int i = start; i < (int)Count; i++)
			{
				
				/* エラーチェック */
				if (CANLog[i].Err == CAN_ERR_NONE)
				{

					/* 最大100行まで */
					for (int overline=dataGridView1->RowCount; overline > 100; overline--)
					{
					    dataGridView1->Rows->RemoveAt(0);
					}
				 
					/* Data */
					String^ str = "";
					for (int j = 0; j < CANLog[i].Frame.Dlc; j++)
					{
						str += CANLog[i].Frame.Data[j].ToString("X2") + ",";

					}

					/* 方向 */
					String^ dir = "";
					if (CANLog[i].Dir == CAN_DIR_RX)
					{
						dir = "Rx ";
					}
					else
					{
						dir = "Tx ";
					}

					/* IDフォーマット */
					String^ format = "";
					if (CANLog[i].Frame.IdFormat == CAN_ID_STD)
					{
						format = "Std ";
					}
					else
					{
						format = "Ext ";
					}

					/* ID */
					String^ ID = CANLog[i].Frame.Id.ToString("X3");

					/* データグリッドに追加 */
					dataGridView1->Rows->Add(CANLog[i].mSec, CANLog[i].uSec, dir, format, ID, CANLog[i].Frame.Dlc, str); 
				 
				}
				else
				{
					String^ str = "Err";
					if (CANLog[i].Err == CAN_ERR_ACK) 
					{
						str = "Ack E.";
					}
					else if (CANLog[i].Err == CAN_ERR_OLF) 
					{
						str = "OLF E.";
					}

					/* データグリッドに追加 */
					dataGridView1->Rows->Add(CANLog[i].mSec, CANLog[i].uSec, str, "", "", "", ""); 

				}

			}

			/* 表示の更新 */
			dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->RowCount-1;	
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			MPCANClose();
		 }
private: System::Void ChangeData_Button_Click(System::Object^  sender, System::EventArgs^  e) {
			/* 送信データをインクリメント */
			for (int i = 0; i < 8; i++)
			{
				CANSlot[0].Frame.Data[i] += 1;
			}

			MPCANChangeSlotData(0, CANSlot[0].Enabled, CANSlot[0].Frame.Data);

		 }
private: System::Void SlotSend_Button_Click(System::Object^  sender, System::EventArgs^  e) {
			/* スロット送信 */
			MPCANSendSlot(1);
		 }
private: System::Void DirectSend_Button_Click(System::Object^  sender, System::EventArgs^  e) {
			/* 送信データ設定 */
			CANFrame.IdFormat = CAN_ID_STD;
			CANFrame.Rtr = CAN_RTR_DATA;
			CANFrame.Id = 0x300;
			CANFrame.Dlc = 8;
			for (int i = 0; i < 8; i++)
			{
			    CANFrame.Data[i] = 0x30;
			}

			/* ダイレクト送信 */	 
			ret = MPCANSendDirect(CANFrame);
			if (ret != E_OK)
			{
			    MessageBox::Show("error");
				exit(1);
			}
		 }
};
}

