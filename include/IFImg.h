// -----------------------------------------------------------------------------
//
//		GPC/GPF-5520 Header file
//
//		File Name: IFImg.h
//		Version		:	2.00
//
//					Copyright 2003, 2011 Interface Corporation. All rights reserved.
// -----------------------------------------------------------------------------
#if !defined( _IFIMG_H_ )
#define _IFIMG_H_

#ifdef __cplusplus
extern	"C" {
#endif

// -----------------------------------------------------------------------------
//	エラー識別子
// -----------------------------------------------------------------------------
#define IFIMG_ERROR_SUCCESS					0x00000000
#define IFIMG_ERROR_NOT_DEVICE				0xC0000001
#define IFIMG_ERROR_NOT_OPEN				0xC0000002
#define IFIMG_ERROR_INVALID_HANDLE			0xC0000003
#define IFIMG_ERROR_ALREADY_OPEN			0xC0000004
#define IFIMG_ERROR_IO_PENDING				0xC0000008
#define IFIMG_ERROR_INSUFFICIENT_BUFFER		0xC0000007
#define IFIMG_ERROR_NOT_SUPPORTED			0xC0000009
#define IFIMG_ERROR_INVALID_PARAMETER		0xC0000010
#define IFIMG_ERROR_NOT_ALLOCATE_MEMORY		0xC0000021

#define IFIMG_ERROR_NOW_CAPTURING			0xC0001000
#define IFIMG_ERROR_NOW_STOP				0xC0001001
#define IFIMG_ERROR_NULL_POINTER			0xC0001002
#define IFIMG_ERROR_WRITE_FAILED			0xC0001003
#define IFIMG_ERROR_READ_FAILED				0xC0001004
#define	IFIMG_ERROR_NOBUFFER				0xC0001005
#define IFIMG_ERROR_INVALID_OFFSET			0xC0001006

#define IFIMG_ERROR_SDRAM_NOW_CAPTURING		0xC0001007
#define IFIMG_ERROR_SDRAM_NOW_STOP			0xC0001008
#define IFIMG_ERROR_NOT_SET_COMPDATA		0xC0001009
#define IFIMG_ERROR_SDRAM_NOTSET_CAPDATA	0xC000100A
#define IFIMG_ERROR_NOT_COMPDATA			0xC000100B
#define IFIMG_ERROR_INVALID_SDRAM_HANDLE	0xC000100C
#define IFIMG_ERROR_SDRAM_NOT_CAPDATA		0xC000100D
#define IFIMG_ERROR_SDRAM_NOMEMORY			0xC000100E
#define IFIMG_ERROR_INVALID_FORMAT			0xC000100F
#define IFIMG_ERROR_NOW_SDRAM_BM			0xC0001010
#define IFIMG_ERROR_FAILED_REGWRITE			0xC0001012

#define IFIMG_ERROR_INVALID_FILEPARAMETER	0xC0001013
#define IFIMG_ERROR_NOTSET_CAMFILE			0xC0001014
#define IFIMG_ERROR_SERIAL_TIMEOUT			0xC0001015
#define IFIMG_ERROR_SERIAL_FIFO_OVERRUN		0xC0001016
#define IFIMG_ERROR_FAILED_CAPTURE			0xC0001017
#define IFIMG_ERROR_FAILED_CAPSTOP			0xC0001018
#define IFIMG_ERROR_FAILED_BUSY				0xC0001019
#define IFIMG_ERROR_ROM_WRITE				0xC000101A
#define IFIMG_ERROR_FAILED_DEVIOCTL			0xC000101B
#define IFIMG_ERROR_OTHER_ERR				0xC000101C
#define IFIMG_ERROR_NOW_IMPOSEDATA_WRITE	0xC000101D

// -----------------------------------------------------------------------------
//　データフォーマット識別子
// -----------------------------------------------------------------------------
#define IFIMG_COLOR_RGB32	0x00000001
#define IFIMG_COLOR_RGB24	0x00000002
#define IFIMG_COLOR_RGB15	0x00000003
#define IFIMG_COLOR_GRAY8	0x00000004
#define IFIMG_COLOR_RED8	0x00000005
#define IFIMG_COLOR_GREEN8	0x00000006
#define IFIMG_COLOR_BLUE8	0x00000007
#define IFIMG_COLOR_BIN8	0x00000008
#define IFIMG_COLOR_CMP8	0x0000000A
#define IFIMG_COLOR_RGB16	0x0000000B
#define IFIMG_COLOR_FIL8	0x0000000C
#define IFIMG_COLOR_LABEL8	0x0000000D

#define IFIMG_COLOR_GRAY10	0x0000000E
#define IFIMG_COLOR_GRAY12	0x0000000F
#define IFIMG_COLOR_GRAY14	0x00000010
#define IFIMG_COLOR_GRAY16	0x00000011

#define IFIMG_MEASUEMENT_HIST	0x00000200
#define IFIMG_MEASUEMENT_PRO	0x00000400
#define IFIMG_MEASUEMENT_LBLCNT	0x00000800
#define IFIMG_MEASUEMENT_AREA	0x00001000
#define IFIMG_MEASUEMENT_GRV	0x00002000
#define IFIMG_MEASUEMENT_FERE	0x00004000
#define IFIMG_MEASUEMENT_ELLIPSE 0x00008000

#define IFIMG_RESOLUTION_640_480	0x00000000
#define IFIMG_RESOLUTION_320_240	0x80000000
#define IFIMG_RESOLUTION_160_120	0x40000000

#define IFIMG_RESOLUTION_768_572	0x08000000
#define IFIMG_RESOLUTION_384_286	0x04000000
#define IFIMG_RESOLUTION_192_143	0x02000000

#define IFIMG_DIGITALZOOM_2			0x00100000
#define IFIMG_DIGITALZOOM_4			0x00200000
#define IFIMG_DIGITALZOOM_8			0x00300000

#define IFIMG_CL_RESOLUTION			0x00010000
#define IFIMG_NTSC_RESOLUTION		0x00000000

// -----------------------------------------------------------------------------
//  　キャプチャ開始識別子
// -----------------------------------------------------------------------------
#define IFIMG_DMACAPTURE_START		0x00000001
#define IFIMG_SDRAMCAPTURE_START	0x00000002

// -----------------------------------------------------------------------------
//  　キャプチャ停止識別子
// -----------------------------------------------------------------------------
#define IFIMG_FRAME_STOP			0x00000001
#define IFIMG_IMMEDIATE_STOP		0x00000002
#define IFIMG_SDRAM_FRAME_STOP		0x00000004
#define IFIMG_SDRAM_IMMEDIATE_STOP	0x00000008

// -----------------------------------------------------------------------------
//　映像出力モード識別子
// -----------------------------------------------------------------------------
#define IFIMG_OUTMODE_THROUGH	0x00000001
#define IFIMG_OUTMODE_COLORBAR  0x00000002
#define IFIMG_OUTMODE_STILL_PICTURE  0x00000003


// -----------------------------------------------------------------------------
//　二値化処理　色成分選択識別子
// -----------------------------------------------------------------------------
#define	IFIMG_INGREDIENT_RED		0x00000001
#define	IFIMG_INGREDIENT_GREEN		0x00000002
#define	IFIMG_INGREDIENT_BLUE		0x00000003
#define	IFIMG_INGREDIENT_GRAY		0x00000004

// -----------------------------------------------------------------------------
//　二値化処理　二値化条件の反転指定　識別子
// -----------------------------------------------------------------------------
#define	IFIMG_BINMODE_NORMAL    0x00000001
#define	IFIMG_BINMODE_REVERSAL  0x00000002

// -----------------------------------------------------------------------------
//　キャプチャモード　識別子
// -----------------------------------------------------------------------------
#define	IFIMG_CAPTURE_NORMAL			0x00000001
#define	IFIMG_CAPTURE_THINOUT			0x00000002
#define	IFIMG_CAPTURE_TIMER				0x00000003
#define	IFIMG_CAPTURE_CH_FRAME			0x00000004
#define	IFIMG_CAPTURE_CH_TIMER			0x00000005

// -----------------------------------------------------------------------------
//  　使用チャンネル識別子
// -----------------------------------------------------------------------------
#define IFIMG_CHANNEL_CN1				0x00000001
#define IFIMG_CHANNEL_CN4				0x00000004
#define IFIMG_CHANNEL_CN5				0x00000005
#define IFIMG_CHANNEL_CN6				0x00000006
#define IFIMG_CHANNEL_CN7				0x00000007

// -----------------------------------------------------------------------------
//　パターン一致自動補正　識別子
// -----------------------------------------------------------------------------
#define IFIMG_AUTO_ENABLE				0x00000001
#define IFIMG_AUTO_DISABLE				0x00000002

// -----------------------------------------------------------------------------
//　パターン一致条件の反転指定　識別子
// -----------------------------------------------------------------------------
#define	IFIMG_PTNMATCH_NORMAL			0x00000001
#define	IFIMG_PTNMATCH_REVERSAL			0x00000002
#define	IFIMG_PTNMATCH_NONE				0x00000003

// -----------------------------------------------------------------------------
//  　SDRAM転送識別子
// -----------------------------------------------------------------------------
#define IFIMG_BUFF_HEAD                  0x00000000
#define IFIMG_BUFF_CONTINUATION          0x00000001

// -----------------------------------------------------------------------------
//  　フィルタ識別子
// -----------------------------------------------------------------------------
#define IFIMG_SPATIAL_FILTER			0x00000001
#define IFIMG_EDGE_FILTER				0x00000002

// -----------------------------------------------------------------------------
//  　ラベリング識別子
// -----------------------------------------------------------------------------
#define IFIMG_FOUR_CONNECTION			0x00000000
#define IFIMG_EIGHT_CONNECTION			0x00000001

// -----------------------------------------------------------------------------
//  　同期信号選択識別子
// -----------------------------------------------------------------------------
#define IFIMG_ERR_DETECTION_MODE1		0x00000001
#define IFIMG_ERR_DETECTION_MODE2		0x00000002
#define IFIMG_ERR_DETECTION_MODE3		0x00000003
#define IFIMG_ERR_DETECTION_MODE4		0x00000004
#define IFIMG_ERR_DETECTION_MODE5		0x00000005
#define IFIMG_ERR_DETECTION_MODE6		0x00000006
#define IFIMG_ERR_DETECTION_MODE7		0x00000007
#define IFIMG_ERR_DETECTION_MODE8		0x00000008

// -----------------------------------------------------------------------------
//  　カメラ接続状態識別子
// -----------------------------------------------------------------------------
#define IFIMG_CAMERA_NOTSUPPORTED		0x00000000
#define IFIMG_CAMERA_CONNECTION			0x00000001
#define IFIMG_CAMERA_UNCONNECTION		0x00000002


// -----------------------------------------------------------------------------
//    OS情報識別子
//-----------------------------------------------------------------------
#define IFIMG_OS_ARCHITECTURE_x64		0x00000001
#define IFIMG_OS_ARCHITECTURE_x86		0x00000002



// -----------------------------------------------------------------------------
//    キャプチャモード選択識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define	IFIMGCL_SYNCCAP_NONE			0x00000000
#define IFIMGCL_SYNCCAP_DI_START		0x00000001
#define IFIMGCL_SYNCCAP_TIMER1_START	0x00000002
#define IFIMGCL_SYNCCAP_ENC_START		0x00000004
#define IFIMGCL_SYNCCAP_SENC1_START		0x00000005
#define IFIMGCL_SYNCCAP_SENC2_START		0x00000006

// -----------------------------------------------------------------------------
//    CC信号識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define IFIMGCL_CC1						0x00000001
#define IFIMGCL_CC2						0x00000002
#define IFIMGCL_CC3						0x00000004
#define IFIMGCL_CC4						0x00000008

// -----------------------------------------------------------------------------
//    CC信号出力モード識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define IFIMGCL_CC_MODE_SOFT			0x00000000
#define IFIMGCL_CC_MODE_DI				0x00000001
#define IFIMGCL_CC_MODE_EDGE			0x00000002
#define IFIMGCL_CC_MODE_TIMER1			0x00000003
#define IFIMGCL_CC_MODE_ENC_CYCLE		0x00000005
#define IFIMGCL_CC_MODE_SENC1_CYCLE		0x00000006
#define IFIMGCL_CC_MODE_SENC2_CYCLE		0x00000007
#define IFIMGCL_CC_MODE_ENC_CNTUP		0x00000008
#define IFIMGCL_CC_MODE_SENC1_CNTUP		0x00000009
#define IFIMGCL_CC_MODE_SENC2_CNTUP		0x0000000A
#define IFIMGCL_ACTIVE_LOW				0x00000100

// -----------------------------------------------------------------------------
//    CC信号同期 汎用出力モード識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define IFIMGCL_CCSYNC_STOROBO			0x00000001
#define IFIMGCL_CCSYNC_BOARDSYNC		0x00000002
#define IFIMGCL_ENABLE					0x00000001
#define IFIMGCL_DISABLE					0x00000000
#define IFIMGCL_SYNC_CC1				0x00000001
#define IFIMGCL_SYNC_CC2				0x00000002
#define IFIMGCL_SYNC_CC3				0x00000003
#define IFIMGCL_SYNC_CC4				0x00000004
#define IFIMGCL_DO_LOGIC_HIGH			0x00000001
#define IFIMGCL_DO_LOGIC_LOW			0x00000002

// -----------------------------------------------------------------------------
//    CameraLinkシリアル通信制御識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define IFIMGCL_SEND_FIFO				0x00000001
#define IFIMGCL_RECEIVE_FIFO			0x00000002

// -----------------------------------------------------------------------------
//    CameraLink 電源出力識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define IFIMGCL_PWR_ON					0x00000001
#define IFIMGCL_PWR_OFF					0x00000000

// -----------------------------------------------------------------------------
//    インターバルタイマ/エンコーダパルスカウンタ識別子(PEX-H531322用)
//-----------------------------------------------------------------------
#define IFIMGCL_INTERVALTIMER1			0x00000001
#define IFIMGCL_ENCCNT_DIFFRENTIAL		0x00000003
#define IFIMGCL_ENCCNT_SINGLEENDED1		0x00000004
#define IFIMGCL_ENCCNT_SINGLEENDED2		0x00000005

#define IFIMGCL_DIRECTION_NORMAL		0x00000000
#define IFIMGCL_DIRECTION_REVERSE		0x00000001
#define IFIMGCL_SINGLE_EDGE				0x00000000
#define IFIMGCL_DOUBLE_EDGE				0x00000001
#define IFIMGCL_QUAD_EDGE				0x00000002
#define IFIMGCL_SINGLE_PHASE_MODE		0x00000000
#define IFIMGCL_PHASE_SHIFTED_MODE		0x00000001
#define IFIMGCL_CLOCK_100_NANO			0x00000000
#define IFIMGCL_CLOCK_10_MICRO			0x00000001
#define IFIMGCL_CNT_START_NONE			0x00000000
#define IFIMGCL_CNT_START_DIN1			0x00000001
#define IFIMGCL_CNT_START_ZPHASE		0x00000002

#define IFIMG_SET_IMPOSE				0x00000000
#define IFIMG_SELECT_IMPOSE				0x00000001
#define IFIMG_NON_IMPOSE				0x00000002
#define IFIMG_CHECK_SETINPOSE			0x00000003
#define IFIMG_CHECK_SETIMPOSE_STOP		0x00000005

#define IFIMG_IMPOSE_REPLACE			0x00000001
#define IFIMG_IMPOSE_ADD				0x00000002
#define IFIMG_IMPOSE_SUB				0x00000003
#define IFIMG_IMPOSE_XOR				0x00000004
#define IFIMG_IMPOSE_OVERWRITE			0x00000008
#define IFIMG_IMPOSE_PERMEATION_3_1		0x00000009
#define IFIMG_IMPOSE_PERMEATION			0x0000000A
#define IFIMG_IMPOSE_PERMEATION_1_3		0x0000000B

#define IFIMG_IMPOSE_NONE_DATETIME		0x00000000
#define IFIMG_IMPOSE_SET_DATE			0x00000001
#define IFIMG_IMPOSE_SET_TIME			0x00000002
#define IFIMG_IMPOSE_STRING_OUTLINE		0x00010000

// -----------------------------------------------------------------------------
//	ボード情報構造体
// -----------------------------------------------------------------------------
typedef struct {
	WORD	wType;
	WORD	wRsw;
} IMGDEVICEINFO, *PIMGDEVICEINFO;


// -----------------------------------------------------------------------------
//	バッファ領域情報構造体
// -----------------------------------------------------------------------------
typedef struct {
	PVOID	pBufferAddress;
	DWORD	dwBufferSize;
} IMGBUFFERINFO, *PIMGBUFFERINFO;


// -----------------------------------------------------------------------------
//	キャプチャー状態情報構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwCapture;
	DWORD	dwFrameCnt;
	DWORD	dwTrigger;
} IMGCAPSTATUS, *PIMGCAPSTATUS;

// -----------------------------------------------------------------------------
//	キャプチャー状態情報構造体(5521/5523/5531/5533専用)
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwCapture;
	DWORD	dwFrameCntDMA;
	DWORD	dwFrameCntSDRAM;
	DWORD	dwTrigger;
} IMGCAPSTATUSEX, *PIMGCAPSTATUSEX;

// -----------------------------------------------------------------------------
//	割り込みマスク構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwDI;
	DWORD	dwFrame;
	DWORD	dwTrigger;
} IMGEVENTTABLE, *PIMGEVENTTABLE;

// -----------------------------------------------------------------------------
//	割り込み用イベントテーブル構造体(5521/5523/5531/5533専用)
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwDI;
	DWORD	dwFrame;
	DWORD	dwTrigger;
	DWORD	dwFrameCntDMA;
	DWORD	dwFrameCntSDRAM;
	DWORD	dwXcoordinates;
	DWORD	dwYcoordinates;
	DWORD	dwPercentage;
} IMGEVENTTABLEEX, *PIMGEVENTTABLEEX;


#ifdef _WIN64
typedef void (CALLBACK IMGCALLBACK)(IMGEVENTTABLE Event, DWORD dwFrameCnt, PVOID pUser);
typedef IMGCALLBACK FAR *PIMGCALLBACK;
typedef void (CALLBACK IMGCALLBACKEX)(IMGEVENTTABLEEX Event, PVOID pUser);
typedef IMGCALLBACKEX FAR *PIMGCALLBACKEX;
#else
typedef void (CALLBACK IMGCALLBACK)(IMGEVENTTABLE Event, DWORD dwFrameCnt, DWORD dwUser);
typedef IMGCALLBACK FAR *PIMGCALLBACK;
typedef void (CALLBACK IMGCALLBACKEX)(IMGEVENTTABLEEX Event, DWORD dwUser);
typedef IMGCALLBACKEX FAR *PIMGCALLBACKEX;
#endif

// -----------------------------------------------------------------------------
//	割り込み構造体
// -----------------------------------------------------------------------------
typedef struct {
	HWND		hWnd;
	UINT		uMessage;
	HANDLE		hEvent;
	PIMGCALLBACK	pCallBackProc;
#ifdef _WIN64
	PVOID			pUser;
#else
	DWORD			dwUser;
#endif
} IMGEVENTREQ, *PIMGEVENTREQ;

// -----------------------------------------------------------------------------
//	割り込み構造体(5521/5523専用)
// -----------------------------------------------------------------------------
typedef struct {
	HWND	hWnd;
	UINT	uMessage;
	HANDLE	hEvent;
	PIMGCALLBACKEX	pCallBackProcEx;
#ifdef _WIN64
	PVOID			pUser;
#else
	DWORD			dwUser;
#endif
} IMGEVENTREQEX, *PIMGEVENTREQEX;

// -----------------------------------------------------------------------------
//	二値化処理構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwColorIngredient;
	DWORD	dwMaxthreshold;
	DWORD	dwMinthreshold;
	DWORD	dwBinarizationMode;
} IMGBINCONFIG, *PIMGBINCONFIG;

// -----------------------------------------------------------------------------
//	トリガ設定構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD   dwTriggerEnabled;
	DWORD	dwAreaMax;
	DWORD	dwAreaMin;
	DWORD   dwStartPointX;
	DWORD	dwStartPointY;
	DWORD	dwXLength;
	DWORD	dwYLength;
	DWORD	dwTriggerRangeMode;
} IMGTRGCONFIG, *PIMGTRGCONFIG;

// -----------------------------------------------------------------------------
//	キャプチャ条件構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwMode;
	DWORD	dwThinFrameCnt;
	DWORD	dwTimerCycle;
	DWORD	dwChFrameCnt;
	DWORD	dwChangePattern[5];
} IMGCAPCONFIG, *PIMGCAPCONFIG;

// -----------------------------------------------------------------------------
//	クリッピング設定構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwDataFormat;
	DWORD   dwXCoordinates;
	DWORD	dwYCoordinates;
	DWORD	dwXLength;
	DWORD   dwYLength;
} IMGCLIPCONFIG, *PIMGCLIPCONFIG;

// -----------------------------------------------------------------------------
//	パターン一致設定構造体
// -----------------------------------------------------------------------------
typedef struct {
	HANDLE	hSDRAMhandle;
	DWORD	dwAutoRevision;
	DWORD	dwXCoordinates;
	DWORD   dwYCoordinates;
	DWORD	dwPercentage;
	DWORD	dwTriggerMode;
} IMGPTNCONFIG, *PIMGPTNCONFIG;


// -----------------------------------------------------------------------------
//	画像処理構造体
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	dwArea;
	DWORD	dwXCoordinates;
	DWORD   dwYCoordinates;
	DWORD   dwFeretX1;
	DWORD   dwFeretX2;
	DWORD   dwFeretY1;
	DWORD   dwFeretY2;
	DWORD   dwFeretH;
	DWORD   dwFeretV;
	float   dAngle;
} IMGMEASURE, *PIMGMEASURE;

// -----------------------------------------------------------------------------
//  フィルタ構造体
// -----------------------------------------------------------------------------
typedef struct {
	INT	a;
	INT	b;
	INT	c;
	INT	d;
	INT	e;
	INT	f;
	INT	g;
	INT	h;
	INT	i;
} IMGFILTER, *PIMGFILTER;

// -----------------------------------------------------------------------------
//  LUT構造体
// -----------------------------------------------------------------------------
typedef struct {
   BYTE    rgbBlue[256];
   BYTE    rgbGreen[256];
   BYTE    rgbRed[256];
} IMGLUTINFO, *PIMGLUTINFO;

// -----------------------------------------------------------------------------
//  膨張・収縮処理構造体
// -----------------------------------------------------------------------------
typedef struct {
   DWORD    dwStepCnt;
   DWORD    dwSelectD_E;
   DWORD	dwNeighborhood;
} IMGDILATE_ERODE, *PIMGDILATE_ERODE;


// -----------------------------------------------------------------------------
//   CameraLink キャプチャ設定用 構造体(PEX-H531322用)
// -----------------------------------------------------------------------------

typedef struct{
	DWORD	XStart;
	DWORD	YStart;
	DWORD	SyncMode;
	DWORD	LVALInterVal;
}IFIMGCLCAPCFG, *PIFIMGCLCAPCFG;

// -----------------------------------------------------------------------------
//   CC信号同期 汎用出力設定構造体 (PEX-H531322用)
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	OutputMode;
	DWORD	OutputEnabled;
	DWORD	CC;
	DWORD	Logic;
	DWORD	DoPulse;
	DWORD	Delay;
}IFIMGCLSYNCDO, *PIFIMGCLSYNCDO;

// -----------------------------------------------------------------------------
//  エンコーダカウンタ設定構造体 (PEX-H531322用)
// -----------------------------------------------------------------------------
typedef struct {
	DWORD	Direction;
	DWORD	Edge;
	DWORD	PulseMode;
	DWORD	StartMode;
	DWORD	StartCounter;
	DWORD	FilterBaceClock;
	DWORD	FilterCount;
}IFIMGCLENCCFG, *PIFIMGCLENCCFG;


// -----------------------------------------------------------------------------
//  スーパーインポーズ時刻設定構造体 (PCI-540111用)
// -----------------------------------------------------------------------------
typedef struct{
	INT	sec;
	INT	min;
	INT	hour;
}IFIMGTIME, *PIFIMGTIME;

// -----------------------------------------------------------------------------
//  スーパーインポーズ日付設定構造体 (PCI-540111用)
// -----------------------------------------------------------------------------
typedef struct{
	INT	mday;
	INT	mon;
	INT	year;
}IFIMGDATE, *PIFIMGDATE;

// -----------------------------------------------------------------------------
//  スーパーインポーズ時刻設定構造体 (PCI-540111用)
// -----------------------------------------------------------------------------
typedef struct{
	IFIMGTIME	Time;
	INT			Xcoordinates;
	INT			Ycoordinates;
}IFIMGTIMEINFO, *PIFIMGTIMEINFO;

// -----------------------------------------------------------------------------
//  スーパーインポーズ日付設定構造体 (PCI-540111用)
// -----------------------------------------------------------------------------
typedef struct{
	IFIMGDATE	Date;
	INT			Xcoordinates;
	INT			Ycoordinates;
}IFIMGDATEINFO, *PIFIMGDATEINFO;


// -----------------------------------------------------------------------------
//	関数定義
// -----------------------------------------------------------------------------
#ifdef _WIN64
HANDLE WINAPI ImgOpen(LPCSTR lpszName);
#else
HANDLE WINAPI ImgOpen(LPCTSTR lpszName);
#endif
int WINAPI ImgClose(HANDLE);
int WINAPI ImgGetDeviceInfo(HANDLE, PIMGDEVICEINFO);
int WINAPI ImgGetCaptureStatus(HANDLE, PIMGCAPSTATUS);
int WINAPI ImgSetBuffer(HANDLE, PIMGBUFFERINFO, DWORD);
int WINAPI ImgGetMemPtrValue(HANDLE, PVOID*);
int WINAPI ImgStartCapture(HANDLE, DWORD, DWORD);
int WINAPI ImgStopCapture(HANDLE, DWORD);
int WINAPI ImgInputDI(HANDLE, PWORD);
int WINAPI ImgOutputDO(HANDLE, WORD);
int WINAPI ImgSetOutputMode(HANDLE, WORD);
int WINAPI ImgSetPosition(HANDLE, INT, INT);
int WINAPI ImgSetEvent(HANDLE, PIMGEVENTREQ);
int WINAPI ImgSetEventMask(HANDLE, PIMGEVENTTABLE);
int WINAPI ImgGetEventMask(HANDLE, PIMGEVENTTABLE);
int WINAPI ImgSetBinarizationConfig(HANDLE, PIMGBINCONFIG);
int WINAPI ImgSetMeasurementRange(HANDLE, DWORD, DWORD, DWORD, DWORD);
int WINAPI ImgGetMeasurementValue(HANDLE, PDWORD, PDWORD, PDWORD, PDWORD);
int WINAPI ImgSetTriggerConfig(HANDLE, PIMGTRGCONFIG);
int WINAPI ImgSetChannel(HANDLE, DWORD);
int WINAPI ImgSetCaptureConfig(HANDLE, PIMGCAPCONFIG);
int WINAPI ImgAllocateSDRAM(HANDLE, DWORD, DWORD, DWORD, DWORD, PHANDLE);
int WINAPI ImgFreeSDRAM(HANDLE, HANDLE);
int WINAPI ImgSetSDRAM(HANDLE, HANDLE);
int WINAPI ImgReadCaptureData(HANDLE, HANDLE, DWORD, DWORD, PVOID, DWORD);
int WINAPI ImgClipData(PVOID, PVOID, DWORD, PIMGCLIPCONFIG);
int WINAPI ImgWriteComparisonData(HANDLE, HANDLE, PVOID, DWORD);
int WINAPI ImgSetComparisonConfig(HANDLE, PIMGPTNCONFIG);
int WINAPI ImgGetCaptureStatusEx(HANDLE, PIMGCAPSTATUSEX);
int WINAPI ImgSetEventEx(HANDLE, PIMGEVENTREQEX);
int WINAPI ImgGetMatchingLevel(HANDLE, PDWORD, PDWORD);
int WINAPI ImgBmCaptureData(HANDLE, HANDLE, DWORD, DWORD, DWORD);
int WINAPI ImgSetColorIngredient(HANDLE, DWORD);
int WINAPI ImgGetMeasurementValueEx(HANDLE, PIMGMEASURE, PDWORD);
int WINAPI ImgSetConversionConfig(HANDLE,DWORD);
int WINAPI ImgSetLUT(HANDLE, PIMGLUTINFO);
int WINAPI ImgSetFilter(HANDLE, DWORD, PIMGFILTER);
int WINAPI ImgSetDil_Er(HANDLE, PIMGDILATE_ERODE);
int WINAPI ImgSetStillPictureData(HANDLE, PVOID);
int WINAPI ImgGetStillPictureData(HANDLE, PVOID);
int WINAPI ImgSetLabelingConfig(HANDLE, DWORD);
int WINAPI ImgGetMeasurementValueLBL(HANDLE, PVOID,DWORD, PDWORD, PIMGMEASURE);
int WINAPI ImgSetDecoderConfig(HANDLE, WORD, WORD);
int WINAPI ImgSetEncoderConfig(HANDLE, WORD, WORD);
int WINAPI ImgSetGainControl(HANDLE, INT);
int WINAPI ImgSetBlankingLevel(HANDLE, INT);
int WINAPI ImgGetSyncErrCnt(HANDLE,PDWORD);
int WINAPI ImgSetSyncErrorDetection(HANDLE, DWORD);
int WINAPI ImgGetCameraConnectionStatus(HANDLE, PDWORD);
int WINAPI ImgGetOsArchitecture(HANDLE, PDWORD);

int WINAPI ImgSetCLCaptureConfig(HANDLE, LPCSTR, PIFIMGCLCAPCFG);
int WINAPI ImgSetCCMode(HANDLE, DWORD, DWORD, DWORD);
int WINAPI ImgOutputCCPluse(HANDLE, DWORD);
int WINAPI ImgSerialSend(HANDLE, PVOID, PDWORD, DWORD);
int WINAPI ImgSerialReceive(HANDLE, PVOID, PDWORD, DWORD);
int WINAPI ImgGetSerialStatus(HANDLE, PDWORD, PDWORD);
int WINAPI ImgSerialClear(HANDLE, DWORD);
int WINAPI ImgOutputPower(HANDLE, DWORD);
int WINAPI ImgSetEncodeCntMode(HANDLE, DWORD, PIFIMGCLENCCFG);
int WINAPI ImgSetCounterCycle(HANDLE, DWORD, DWORD);
int WINAPI ImgGetCounterValue(HANDLE, DWORD, PDWORD);

int WINAPI ImgSetImposeImage(HANDLE, DWORD, DWORD, DWORD, PVOID, DWORD);
int WINAPI ImgSetImposeDateTime(HANDLE, PIFIMGDATE, PIFIMGTIME);
int WINAPI ImgSetImposeDateTimeInfo(HANDLE, PIFIMGDATEINFO, PIFIMGTIMEINFO, DWORD, PDWORD, DWORD);
int WINAPI ImgSetImposeFont(HANDLE, DWORD, PVOID, DWORD);

#ifdef __cplusplus
}
#endif

#endif
