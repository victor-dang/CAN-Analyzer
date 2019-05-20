/*###############################################################################################
  �t�@�C���� : MPCANCtrl.h
  ���e       : MicroPecker CAN �R���g���[���[ API
  �o�[�W���� : 1.16
  �쐬��     : 2012/09/21
  �X�V��     : 2015/07/03
  �J����   : C/C++
  ���̑�     : ���C�u�����t�@�C�� = Microsoft Visual C++ : MPCANCtrl.lib
                                    Embarcadero C++ Builder : MPCANCtrl_BCB.lib
###############################################################################################*/

#ifndef MPCANCtrlH
#define MPCANCtrlH

#include <stdint.h>

/******************** �萔��` ********************/

/* API�R�[������ */
#define E_OK       (0) /* ����                           */
#define E_PARAM    (1) /* �p�����[�^�ُ�                 */
#define E_DEVICE   (2) /* �f�o�C�X�ُ�(�f�o�C�X�������o) */
#define E_COMM     (3) /* USB�ʐM�ُ�                    */
#define E_TGT      (4) /* �^�[�Q�b�g�ُ�                 */
#define E_SLT_BUSY (5) /* �X���b�g�ݒ莸�s               */
#define E_DCT_FULL (6) /* �_�C���N�g���MFIFO�t��         */
#define E_STS      (7) /* ��Ԉُ�                       */
#define E_OTHER    (8) /* �s���ȃG���[                   */

/* �X�e�[�^�X */
#define CAN_STATUS_INT     (0) /* ���������                 */
#define CAN_STATUS_PARAM   (1) /* �p�����[�^�ݒ�҂����     */
#define CAN_STATUS_WAIT    (2) /* ���j�^�J�n�҂����         */
#define CAN_STATUS_SYNC    (3) /* �����҂����               */
#define CAN_STATUS_MON     (4) /* ���j�^���                 */
#define CAN_STATUS_SIM     (5) /* �V�~�����[�V�������[�h��� */
#define CAN_STATUS_UNKNOWN (6) /* �s���ȏ��                 */

/* ���샂�[�h */
#define CAN_MODE_LISTEN  (0) /* ���b�X���I�����[���[�h(Ack�Ȃ�) */
#define CAN_MODE_MONITOR (1) /* ���j�^���[�h(Ack����)           */
#define CAN_MODE_SIM     (2) /* �V�~�����[�V�������[�h          */

/* �����[�g�t���[����M�L�� */
#define CAN_REMOTE_DIS (0) /* �����[�g��M��                        */
#define CAN_REMOTE_ENA (1) /* �����[�g��M����(�X���b�g23/24���L) */

/* �{�[���[�g�ݒ� */
#define CAN_PARAM_BR_1M   (0) /* 1Mbps   */
#define CAN_PARAM_BR_500K (1) /* 500kbps */
#define CAN_PARAM_BR_250K (2) /* 250kbps */
#define CAN_PARAM_BR_125K (3) /* 125kbps */

/* �T���v���|�C���g�ݒ� */
#define CAN_PARAM_SP_60P (0) /* 60%                  */
#define CAN_PARAM_SP_65P (1) /* 65%(1Mbps���g�p�s��) */
#define CAN_PARAM_SP_70P (2) /* 70%                  */
#define CAN_PARAM_SP_75P (3) /* 75%(1Mbps���g�p�s��) */
#define CAN_PARAM_SP_80P (4) /* 80%                  */
#define CAN_PARAM_SP_85P (5) /* 85%(1Mbps���g�p�s��) */

/* �g�p�N���b�N�� */
#define CAN_CLOCK_30MHZ (0) /* �N���b�N(30MHz) */
#define CAN_CLOCK_8MHZ  (1) /* �N���b�N(8MHz)  */
  
/* �X���b�g�L��/���� */
#define CAN_SLOT_DIS (0) /* �X���b�g���� */
#define CAN_SLOT_ENA (1) /* �X���b�g�L�� */
  
/* ���M�C�x���g */
#define CAN_EVENT_PERIODIC      (0) /* ������M         */
#define CAN_EVENT_EVENT         (1) /* �C�x���g���M     */
#define CAN_EVENT_EVENTPERIODIC (2) /* �C�x���g������M */
  
/* ID�t�H�[�}�b�g */
#define CAN_ID_STD (0) /* �W��ID */
#define CAN_ID_EXT (1) /* �g��ID */
  
/* �t���[����� */
#define CAN_RTR_DATA   (0) /* �f�[�^�t���[��   */
#define CAN_RTR_REMOTE (1) /* �����[�g�t���[�� */
  
/* ���� */
#define CAN_DIR_RX (0) /* ��M */
#define CAN_DIR_TX (1) /* ���M */

/* �G���[ */
#define CAN_ERR_NONE  (0) /* �G���[�Ȃ�             */
#define CAN_ERR_ACK   (1) /* Ack�G���[              */
#define CAN_ERR_OLF   (2) /* �I�[�o�[���[�h�t���[�� */
#define CAN_ERR_OTHER (3) /* ���̑��G���[           */
  
/* �o�b�t�@�I�[�o�[ */
#define CAN_BUFOVER_FALSE (0) /* �o�b�t�@�I�[�o�[���� */
#define CAN_BUFOVER_TRUE  (1) /* �o�b�t�@�I�[�o�[���� */

/* LED�ݒ� */
#define CAN_LED_OFF (0) /* LED OFF */
#define CAN_LED_ON  (1) /* LED ON  */


/******************** �\���̒�` ********************/
#pragma pack (1)

/* API�o�[�W���� */
typedef struct {
    char APIVersion[32]; /* API�o�[�W������� */
} StMPCANVersion;

/* CAN���M�t���[�� */
typedef struct {
    unsigned long Id;       /* ID             */
    unsigned char IdFormat; /* ID�t�H�[�}�b�g */
    unsigned char Rtr;      /* �t���[�����   */
    unsigned char Dlc;      /* DLC            */
    unsigned char Reserved; /* �\��̈�       */
    unsigned char Data[8];  /* �f�[�^         */
} StMPCANFrame;

/* �X���b�g��� */
typedef struct {
    unsigned char  Enabled;     /* �X���b�g�L��/���� */
    unsigned char  EventKind;   /* ���M�C�x���g      */
    unsigned short Delay;       /* ���M�f�B���C      */
    unsigned short Cycle;       /* ���M�T�C�N��      */
    unsigned short Offset;      /* ���M�I�t�Z�b�g    */
    unsigned short Count;       /* ���M��          */
    unsigned char  Increment;   /* �C���N�������g�L��(b0:Data1�`b7:Data8�Ή�) */
    unsigned char  Reserved;    /* �\��̈�          */
    StMPCANFrame   Frame;       /* �t���[�����      */
} StMPCANSlot;

/* ���O�f�[�^ */
typedef struct {
    unsigned long  mSec;  /* �~���b          */
    unsigned short uSec;  /* �}�C�N���b      */
    unsigned char  Dir;   /* ����(���M/��M) */
    unsigned char  Err;   /* �G���[          */
    StMPCANFrame   Frame; /* �t���[�����    */
} StMPCANLog;

#pragma pack()


/******************** �֐���` ********************/

/* C++�̏ꍇ�̂݁A���O�C���}�� */
#if defined(__cplusplus)
extern "C" {
#endif

typedef int32_t ER; /* API�߂�l */

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

