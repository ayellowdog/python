 #include "StdAfx.h"

////////////////////////////////////////////////////////////////////////

LONG ADBuffer[MAX_SEGMENT_COUNT][MAX_SEGMENT_SIZE/2];	// �������1024*64
ULONG gl_ReadSizeWords;									// ��������ݳ���

BOOL gl_bDeviceADRun = FALSE;
PCI8018_PARA_AD ADPara;
PCI8018_STATUS_AD ADStatus;

int		gl_nSampleMode = HALF_MODE;					// �ɼ�ģʽ(1����ѯ��2���жϣ� 3��DMA)
BOOL	gl_bCreateFile = FALSE;
int		gl_ScreenVolume;							// ������Ļ��ʾ������
int		gl_InputRange[MAX_CHANNEL_COUNT];			// ��ͨ�����õĵ�ѹ���̷�Χ
int		gl_ADINRange = 0;
int		gl_TopTriggerVolt;							// ���޵�ѹ
int		gl_BottomTriggerVolt;						// ���޵�ѹ
int		gl_MiddleLsb[MAX_CHANNEL_COUNT] = {0};		// ��ƽ�Ƶ�ѹʱ���м�ֵ
int		gl_HistMiddleLsb[MAX_CHANNEL_COUNT] = {0};	// ��ƽ�Ƶ�ѹʱ���м�ֵ
int		gl_nChannelCount = MAX_CHANNEL_COUNT;
float	gl_PerLsbVolt[MAX_CHANNEL_COUNT];			// ��λLSB�ĵ�ѹֵ
float	gl_AnalyzeAllCount;
UINT	gl_OverLimitCount;
BOOL	gl_bProcessMoveVolt;		// Ϊ1ʱ, ƽ�Ƶ�ѹ
BOOL	gl_bHistProcessMoveVolt;	// Ϊ1ʱ, ƽ�Ƶ�ѹ
BOOL	gl_bCreateDevice = FALSE;
BOOL	gl_bProgress = FALSE;		// �Ƿ���½�����
int		gl_nProcessMode;			// ���ݴ���ʽ 1��������ʾ  2��������ʾ  3�����ݴ���
HANDLE	gl_hEvent = INVALID_HANDLE_VALUE;					// �ɼ��߳�������̵߳�ͬ���ź�
int		gl_DigitShowMode;			// ���ִ�����ʾģʽ
HANDLE	gl_hFileObject;
BOOL	gl_bCloseFile;
HANDLE	gl_hExitEvent = NULL;
ULONGLONG gl_FileLenghtWords;
int		gl_Offset=0;				// ��ǰ�������ƫ��
int		gl_nDrawIndex = 0;			// ��ͼ������
int		gl_nReadIndex = 0;			// ����������

BOOL	gl_bDataProcessing = FALSE;
CString g_strFileFullName;
BOOL	gl_FirstScreenStop = FALSE;
BOOL gl_bTileWave = TRUE;
int  gl_nProcMode = PROC_MODE_SAVE;
double gl_VoltRange = 20000.0;



int gl_AD7865 = 0;  // Ĭ��ADоƬ7865-1
