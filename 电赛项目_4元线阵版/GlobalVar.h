

extern LONG	ADBuffer[MAX_SEGMENT_COUNT][MAX_SEGMENT_SIZE/2];	// �������
extern ULONG	gl_ReadSizeWords;								// ��������ݳ���
extern BOOL		gl_bDeviceADRun;
extern PCI8018_PARA_AD ADPara;
extern PCI8018_STATUS_AD ADStatus;
extern int		gl_nSampleMode;									// �ɼ�ģʽ(1, ��ѯ�� 2, �жϣ� 3�� DMA)
extern BOOL		gl_bCreateFile;
extern int		gl_ScreenVolume;								// ������Ļ��ʾ������
extern int		gl_InputRange[MAX_CHANNEL_COUNT];				// ��ͨ�����õĵ�ѹ���̷�Χ
extern int		gl_ADINRange;
extern int		gl_TopTriggerVolt;								// ���޵�ѹ
extern int		gl_BottomTriggerVolt;							// ���޵�ѹ
extern int		gl_MiddleLsb[MAX_CHANNEL_COUNT];				// ��ƽ�Ƶ�ѹʱ���м�ֵ
extern int		gl_HistMiddleLsb[MAX_CHANNEL_COUNT];			// ��ƽ�Ƶ�ѹʱ���м�ֵ
extern int		gl_nChannelCount;
extern float	gl_PerLsbVolt[MAX_CHANNEL_COUNT];				// ��λLSB�ĵ�ѹֵ
extern float	gl_AnalyzeAllCount;
extern UINT		gl_OverLimitCount;
extern BOOL		gl_bProcessMoveVolt;							// Ϊ1ʱ, ƽ�Ƶ�ѹ
extern BOOL		gl_bHistProcessMoveVolt;						// Ϊ1ʱ, ƽ�Ƶ�ѹ
extern BOOL		gl_bCreateDevice;
extern BOOL		gl_bProgress;									// �Ƿ���½�����

extern int		gl_nProcMode;				// ���ݴ���ʽ 1��������ʾ  2��������ʾ  3�����ݴ���
extern int		gl_DigitShowMode;			// ���ִ�����ʾģʽ
extern HANDLE	gl_hEvent;					// �ɼ��߳�������̵߳�ͬ���ź�
extern HANDLE	gl_hFileObject;
extern BOOL		gl_bCloseFile;
extern HANDLE	gl_hExitEvent;

extern ULONGLONG	gl_FileLenghtWords;
extern int			gl_Offset;				// ��ǰ�������ƫ��
extern int			gl_nDrawIndex;			// ��ͼ������

extern BOOL			gl_bDataProcessing;
extern CString		g_strFileFullName;
extern BOOL			gl_bTileWave;
extern BOOL			gl_FirstScreenStop;
extern int			gl_nReadIndex;
extern int gl_AD7865;
extern double gl_VoltRange;

#define WM_SHOW_DIGIT (WM_USER+0x100)
#define WM_DEGOK      (WM_USER+0x101)
#define WM_LEVELOK    (WM_USER+0x102)