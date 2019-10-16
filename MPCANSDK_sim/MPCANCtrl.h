

#ifndef MPCANCtrlH
#define MPCANCtrlH

#include <stdint.h>

/******************** 定数定義 ********************/

/* APIコール結果 */
#define E_OK       (0) /* 正常                           */
#define E_PARAM    (1) /* パラメータ異常                 */
#define E_DEVICE   (2) /* デバイス異常(デバイスが未検出) */
#define E_COMM     (3) /* USB通信異常                    */
#define E_TGT      (4) /* ターゲット異常                 */
#define E_SLT_BUSY (5) /* スロット設定失敗               */
#define E_DCT_FULL (6) /* ダイレクト送信FIFOフル         */
#define E_STS      (7) /* 状態異常                       */
#define E_OTHER    (8) /* 不明なエラー                   */

/* ステータス */
#define CAN_STATUS_INT     (0) /* 初期化状態                 */
#define CAN_STATUS_PARAM   (1) /* パラメータ設定待ち状態     */
#define CAN_STATUS_WAIT    (2) /* モニタ開始待ち状態         */
#define CAN_STATUS_SYNC    (3) /* 同期待ち状態               */
#define CAN_STATUS_MON     (4) /* モニタ状態                 */
#define CAN_STATUS_SIM     (5) /* シミュレーションモード状態 */
#define CAN_STATUS_UNKNOWN (6) /* 不明な状態                 */

/* 動作モード */
#define CAN_MODE_LISTEN  (0) /* リッスンオンリーモード(Ackなし) */
#define CAN_MODE_MONITOR (1) /* モニタモード(Ackあり)           */
#define CAN_MODE_SIM     (2) /* シミュレーションモード          */

/* リモートフレーム受信有無 */
#define CAN_REMOTE_DIS (0) /* リモート受信無                        */
#define CAN_REMOTE_ENA (1) /* リモート受信あり(スロット23/24を占有) */

/* ボーレート設定 */
#define CAN_PARAM_BR_1M   (0) /* 1Mbps   */
#define CAN_PARAM_BR_500K (1) /* 500kbps */
#define CAN_PARAM_BR_250K (2) /* 250kbps */
#define CAN_PARAM_BR_125K (3) /* 125kbps */

/* サンプルポイント設定 */
#define CAN_PARAM_SP_60P (0) /* 60%                  */
#define CAN_PARAM_SP_65P (1) /* 65%(1Mbps時使用不可) */
#define CAN_PARAM_SP_70P (2) /* 70%                  */
#define CAN_PARAM_SP_75P (3) /* 75%(1Mbps時使用不可) */
#define CAN_PARAM_SP_80P (4) /* 80%                  */
#define CAN_PARAM_SP_85P (5) /* 85%(1Mbps時使用不可) */

/* 使用クロック源 */
#define CAN_CLOCK_30MHZ (0) /* クロック(30MHz) */
#define CAN_CLOCK_8MHZ  (1) /* クロック(8MHz)  */
  
/* スロット有効/無効 */
#define CAN_SLOT_DIS (0) /* スロット無効 */
#define CAN_SLOT_ENA (1) /* スロット有効 */
  
/* 送信イベント */
#define CAN_EVENT_PERIODIC      (0) /* 定期送信         */
#define CAN_EVENT_EVENT         (1) /* イベント送信     */
#define CAN_EVENT_EVENTPERIODIC (2) /* イベント定期送信 */
  
/* IDフォーマット */
#define CAN_ID_STD (0) /* 標準ID */
#define CAN_ID_EXT (1) /* 拡張ID */
  
/* フレーム種別 */
#define CAN_RTR_DATA   (0) /* データフレーム   */
#define CAN_RTR_REMOTE (1) /* リモートフレーム */
  
/* 方向 */
#define CAN_DIR_RX (0) /* 受信 */
#define CAN_DIR_TX (1) /* 送信 */

/* エラー */
#define CAN_ERR_NONE  (0) /* エラーなし             */
#define CAN_ERR_ACK   (1) /* Ackエラー              */
#define CAN_ERR_OLF   (2) /* オーバーロードフレーム */
#define CAN_ERR_OTHER (3) /* その他エラー           */
  
/* バッファオーバー */
#define CAN_BUFOVER_FALSE (0) /* バッファオーバー無し */
#define CAN_BUFOVER_TRUE  (1) /* バッファオーバー発生 */

/* LED設定 */
#define CAN_LED_OFF (0) /* LED OFF */
#define CAN_LED_ON  (1) /* LED ON  */


/******************** 構造体定義 ********************/
#pragma pack (1)

/* APIバージョン */
typedef struct {
    char APIVersion[32]; /* APIバージョン情報 */
} StMPCANVersion;

/* CAN送信フレーム */
typedef struct {
    unsigned long Id;       /* ID             */
    unsigned char IdFormat; /* IDフォーマット */
    unsigned char Rtr;      /* フレーム種別   */
    unsigned char Dlc;      /* DLC            */
    unsigned char Reserved; /* 予約領域       */
    unsigned char Data[8];  /* データ         */
} StMPCANFrame;

/* スロット情報 */
typedef struct {
    unsigned char  Enabled;     /* スロット有効/無効 */
    unsigned char  EventKind;   /* 送信イベント      */
    unsigned short Delay;       /* 送信ディレイ      */
    unsigned short Cycle;       /* 送信サイクル      */
    unsigned short Offset;      /* 送信オフセット    */
    unsigned short Count;       /* 送信回数          */
    unsigned char  Increment;   /* インクリメント有無(b0:Data1～b7:Data8対応) */
    unsigned char  Reserved;    /* 予約領域          */
    StMPCANFrame   Frame;       /* フレーム情報      */
} StMPCANSlot;

/* ログデータ */
typedef struct {
    unsigned long  mSec;  /* ミリ秒          */
    unsigned short uSec;  /* マイクロ秒      */
    unsigned char  Dir;   /* 方向(送信/受信) */
    unsigned char  Err;   /* エラー          */
    StMPCANFrame   Frame; /* フレーム情報    */
} StMPCANLog;

#pragma pack()


/******************** 関数定義 ********************/

/* C++の場合のみ、名前修飾抑制 */
#if defined(__cplusplus)
extern "C" {
#endif

typedef int32_t ER; /* API戻り値 */

#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT ER __stdcall MPCANGetVersion(StMPCANVersion* Version);
DLL_EXPORT ER __stdcall MPCANOpen(long* Serial);
DLL_EXPORT ER __stdcall MPCANClose();
DLL_EXPORT ER __stdcall MPCANSetLED(unsigned char Red, unsigned char Green, unsigned char GreenBlink);
DLL_EXPORT ER __stdcall MPCANGetStatus(unsigned short* Status);
DLL_EXPORT ER __stdcall MPCANMonitorStart();
DLL_EXPORT ER __stdcall MPCANMonitorStop(unsigned long* mSec, unsigned short* uSec);
DLL_EXPORT ER __stdcall MPCANGetTimeStamp(unsigned long* mSec, unsigned short* uSec);
DLL_EXPORT ER __stdcall MPCANGetLog(StMPCANLog** LogPointer, unsigned long* Count, unsigned char* BufferOver);
DLL_EXPORT ER __stdcall MPCANGetLogEx(StMPCANLog* Log, unsigned long* Num, unsigned long* Count, unsigned char* BufferOver);
DLL_EXPORT ER __stdcall MPCANSetParamSimple(unsigned char Mode, unsigned char RecvRemote, unsigned char Baudrate, unsigned char SamplePoint);
DLL_EXPORT ER __stdcall MPCANSetParamDetail(unsigned char Mode, unsigned char RecvRemote, unsigned short Brg, unsigned char TSeg1, unsigned char TSeg2, unsigned char Sjw, unsigned char Clock);
DLL_EXPORT ER __stdcall MPCANSetSlot(StMPCANSlot* Slot, unsigned char Num);
DLL_EXPORT ER __stdcall MPCANChangeSlotData(unsigned char SlotNo, unsigned char Ena, unsigned char* Data);
DLL_EXPORT ER __stdcall MPCANSendSlot(unsigned char SlotNo);
DLL_EXPORT ER __stdcall MPCANSendDirect(StMPCANFrame Frame);
DLL_EXPORT ER __stdcall MPCANSendDirectEx(StMPCANFrame* Frame);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */

#endif /* MPCANCtrlH */

