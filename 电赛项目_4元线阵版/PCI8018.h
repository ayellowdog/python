#ifndef _PCI8018_DEVICE_
#define _PCI8018_DEVICE_
//#################### ADӲ������PCI8018_PARA_AD���� #####################
// ����AD������ʵ��Ӳ������
typedef struct _PCI8018_PARA_AD     
{
	LONG bChannelArray[16]; // ����ͨ��ѡ�����У��ֱ����16��ͨ����=TRUE��ʾ��ͨ�����������򲻲���
	LONG Gains[16];			// ������ƣ��ֱ����16��ͨ��
	LONG Frequency;         // �ɼ�Ƶ��, ��λΪHz, [3, 80000]
	LONG TriggerMode;		// ����ģʽѡ��
	LONG TriggerSource;		// ����Դѡ��
	LONG TriggerType;		// ��������ѡ��(���ش���/���崥��)
	LONG TriggerDir;		// ��������ѡ��(����/���򴥷�)
	LONG TrigLevelVolt;		// ������ƽ(0--10000mV)
	LONG TrigWindow;		// ����������[1, 65535], ��λ50����
	LONG ClockSource;		// ʱ��Դѡ��(��/��ʱ��Դ)
	LONG bClockOutput;      // ����ʱ�������CLKOUT,=TRUE:����ʱ�����, =FALSE:��ֹʱ�����
} PCI8018_PARA_AD, *PPCI8018_PARA_AD;

//***********************************************************
// ADӲ������PCI8018_PARA_AD�е�Gains[x]ģ�������뷶Χ��ʹ�õ�ѡ��
const long PCI8018_GAINS_1MULT			= 0x00; // 1������
const long PCI8018_GAINS_2MULT			= 0x01; // 2������
const long PCI8018_GAINS_4MULT			= 0x02; // 4������
const long PCI8018_GAINS_8MULT			= 0x03; // 8������

//***********************************************************
// ADӲ������PCI8018_PARA_AD�е�TriggerMode��Ա������ʹ�ô���ģʽѡ��
const long PCI8018_TRIGMODE_SOFT		= 0x00; // ����ڴ���
const long PCI8018_TRIGMODE_POST		= 0x01; // Ӳ���󴥷�

//***********************************************************
// ADӲ������PCI8018_PARA_AD�е�TriggerSource����Դ�ź���ʹ�õ�ѡ��
const long PCI8018_TRIGSRC_ATR			= 0x00; // ѡ���ⲿATR����Դ
const long PCI8018_TRIGSRC_DTR			= 0x01; // ѡ���ⲿDTR����Դ

// ADӲ������PCI8018_PARA_AD�е�TriggerType����������ʹ�õ�ѡ��
const long PCI8018_TRIGTYPE_EDGE		= 0x00; // ���ش���
const long PCI8018_TRIGTYPE_PULSE		= 0x01; // ���崥��(��ƽ)

//***********************************************************
// ADӲ������PCI8018_PARA_AD�е�TriggerDir����������ʹ�õ�ѡ��
const long PCI8018_TRIGDIR_NEGATIVE		= 0x00; // ���򴥷�(������/�½��ش���)
const long PCI8018_TRIGDIR_POSITIVE		= 0x01; // ���򴥷�(������/�����ش���)
const long PCI8018_TRIGDIR_POSIT_NEGAT	= 0x02; // �����򴥷�(��/�����������/�½��ش���)

//***********************************************************
// ADӲ������PCI8018_PARA_AD�е�ClockSourceʱ��Դ��ʹ�õ�ѡ��
const long PCI8018_CLOCKSRC_IN			= 0x00; // �ڲ�ʱ��
const long PCI8018_CLOCKSRC_OUT			= 0x01; // �ⲿʱ��

//*************************************************************************************
// ����AD������ʵ��Ӳ������
typedef struct _PCI8018_STATUS_AD     
{
	LONG bNotEmpty;			// ����FIFO�洢���ķǿձ�־��=TRUE�ǿգ� = FALSE ��
	LONG bHalf;				// ����FIFO�洢���İ�����־��=TRUE�������ϣ� = FALSE ��������
	LONG bOverflow;			// ����FIFO�洢���������־��= TRUE�ѷ�������� = FALSE��δ�������
	LONG nRemainCount;      // AD����ʣ�����
} PCI8018_STATUS_AD, *PPCI8018_STATUS_AD;

const int MAX_SEGMENT_COUNT = 64;
typedef struct _PCI8018_STATUS_DMA     
{
	LONG iCurSegmentID;								// ��ǰ�λ���ID,��ʾDMA���ڴ���Ļ�������
	LONG bSegmentSts[MAX_SEGMENT_COUNT];			// �������������¾�״̬,=1��ʾ����Ӧ����������Ϊ��,����Ϊ��
	LONG bBufferOverflow;							// �������״̬
} PCI8018_STATUS_DMA, *PPCI8018_STATUS_DMA;

//***********************************************************
// �û������ӿ�
#ifndef _PCI8018_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## ����ͨ�ú��� #################################
	// �����ڱ��豸�����������
	HANDLE DEVAPI FAR PASCAL PCI8018_CreateDevice(int DeviceID = 0);  // �����豸����
	HANDLE DEVAPI FAR PASCAL PCI8018_CreateDeviceEx(int DevicePhysID = 0);  // ������Ŵ����豸����
	int DEVAPI FAR PASCAL PCI8018_GetDeviceCount(HANDLE hDevice);	  // ȡ���豸��̨��
	BOOL DEVAPI FAR PASCAL PCI8018_GetDeviceCurrentID(HANDLE hDevice, PLONG DevicePhysID, PLONG DeviceLgcID);
	BOOL DEVAPI FAR PASCAL PCI8018_ListDeviceDlg(HANDLE hDevice); // �б�ϵͳ���е����еĸ�PCI�豸
    BOOL DEVAPI FAR PASCAL PCI8018_ReleaseDevice(HANDLE hDevice); // �ر��豸,��ֹ����,���ͷ���Դ

	//####################### AD���ݶ�ȡ���� #################################
	// ���ڴ������ͨ�û�����Щ�ӿ���򵥡����ݡ���ɿ������û�����֪���豸
	// �Ͳ㸴�ӵ�Ӳ������Э��ͷ����������Ʊ�̣���������ĳ�ʼ���豸�Ͷ�ȡ
	// AD�������������������ɸ�Ч��ʵ�ָ��١����������ݲɼ�

	// AD�����ѯ��ʽ����
	BOOL DEVAPI FAR PASCAL PCI8018_InitDeviceProAD(			// ��ʼ���豸��������TRUE��,�豸��׼������.
										HANDLE hDevice,			// �豸����,����CreateDevice��������
										PPCI8018_PARA_AD pADPara); // Ӳ������, �����ڴ˺����о���Ӳ��״̬

	BOOL DEVAPI FAR PASCAL PCI8018_StartDeviceProAD(			// �ڳ�ʼ��֮�������豸
										HANDLE hDevice);		// �豸������,����CreateDevice��������

	BOOL DEVAPI FAR PASCAL PCI8018_ReadDeviceProAD_Npt(		// ��AD��־��Чʱ���ô˺�����ȡ�豸�ϵ�AD����(����ǿշ�ʽ)
										HANDLE hDevice,			// �豸���,����CreateDevice��������
										LONG ADBuffer[],		// ����ԭʼAD���ݵ��û�������
										LONG nReadSizeWords,	// �����ƫ�Ƶ���������ݳ���(��)
										PLONG nRetSizeWords);   // ����ʵ�ʶ�ȡ�ĳ���(��)

	BOOL DEVAPI FAR PASCAL PCI8018_GetDevStatusProAD(			// ��AD����������ȡ���豸�ĸ���״̬,����ֵ��ʾ�����Ƿ�ɹ�
										HANDLE hDevice,			// �豸���,����CreateDevice��������
										PPCI8018_STATUS_AD pADStatus); // AD�ĸ�����Ϣ�ṹ��

	BOOL DEVAPI FAR PASCAL PCI8018_ReadDeviceProAD_Half(		// ��AD��־��Чʱ���ô˺�����ȡ�豸�ϵ�AD����(���������ʽ)
										HANDLE hDevice,			// �豸���,����CreateDevice��������
										LONG ADBuffer[],		// ����ԭʼAD���ݵ��û�������
										LONG nReadSizeWords,	// �����ƫλ����������ݳ���(��)
										PLONG nRetSizeWords);	// ����ʵ�ʶ�ȡ�ĳ���(��)
		
    BOOL DEVAPI FAR PASCAL PCI8018_StopDeviceProAD(				// �������豸֮����ͣ�豸
										HANDLE hDevice);		// �豸������,����CreateDevice��������

	BOOL DEVAPI FAR PASCAL PCI8018_ReleaseDeviceProAD(			// �ر�AD�豸,��ֹ����,���ͷ���Դ
										HANDLE hDevice);		// �豸���,����CreateDevice��������

	//##################### AD���ݶ�ȡ����(�жϷ�ʽ)(�ϲ��û�����) ###########################
	BOOL DEVAPI FAR PASCAL PCI8018_InitDeviceIntAD(				// ��ʼ���豸��������TRUE��,�豸��׼������.
										HANDLE hDevice,			// �豸����,����CreateDevice��������
										HANDLE hEvent,			// �ж��¼����,����CreateSystemEvent����
										ULONG nFifoHalfLength,	// �����ƫλ����������ݳ���(����С��FIFO��������)
										PPCI8018_PARA_AD pPara);// Ӳ������, �����ڴ˺����о���Ӳ��״̬
    BOOL DEVAPI FAR PASCAL PCI8018_StartDeviceIntAD(			// �ڳ�ʼ��֮�������豸
										HANDLE hDevice);		// �豸������
	BOOL DEVAPI FAR PASCAL PCI8018_ReadDeviceIntAD(HANDLE hDevice,// �豸���
										PLONG pADBuffer,		// �����ڽ���ԭʼAD���ݵ��û�������								
										LONG nReadSizeWords,	// ��������ݳ���(��)
										PLONG nRetSizeWords);	// ���ش����ʵ�ʳ���(��)  
	
    BOOL DEVAPI FAR PASCAL PCI8018_StopDeviceIntAD(				// �ڿ�ʼAD�ɼ���ֹͣ�豸
										HANDLE hDevice);		// �豸������
	BOOL DEVAPI FAR PASCAL PCI8018_ReleaseDeviceIntAD(HANDLE hDevice);

	//##################### AD���ݶ�ȡ����(DMA��ʽ)(�ϲ��û�����) ###########################
	// ADֱ���ڴ�(DMA)��ʽ����
	BOOL DEVAPI FAR PASCAL PCI8018_InitDeviceDmaAD(				// ��ʼ���豸��������TRUE��,�豸��׼������.
										HANDLE hDevice,			// �豸����,����CreateDevice��������
										HANDLE hDmaEvent,		// DMA�¼����,����CreateSystemEvent����
										LONG ADBuffer[],		// �û�������,���Ϊ��ά����
										LONG nReadSizeWords,	// ÿ��DMAʱ,�û���ָ������Ӧ��ȡ��ʵ�ʳ���(ҪС�ڻ����nSegmentSizeWords)
										LONG nSegmentCount,		// ����ֶε�����,ȡֵ��ΧΪ2-128
										LONG nSegmentSizeWords,	// �������ֶεĶγ�(�������FIFO��������)
										PPCI8018_PARA_AD pADPara);// Ӳ������, �����ڴ˺����о���Ӳ��״̬

    BOOL DEVAPI FAR PASCAL PCI8018_StartDeviceDmaAD(			// �ڳ�ʼ��֮�������豸
										HANDLE hDevice);		// �豸������,����CreateDevice��������

	BOOL DEVAPI FAR PASCAL PCI8018_GetDevStatusDmaAD(			// ��AD����������ȡ��DMA���й�״̬,����ֵ��ʾ�����Ƿ�ɹ�
										HANDLE hDevice,			// �豸���,����CreateDevice��������
										PPCI8018_STATUS_DMA pDMAStatus); // ��õ�DMA����״̬

	BOOL DEVAPI FAR PASCAL PCI8018_SetDevStatusDmaAD(			// ��AD��������������DMA���й�״̬,����ֵ��ʾ�����Ƿ�ɹ�
										HANDLE hDevice,			// �豸���,����CreateDevice��������
										LONG iClrBufferID);		// Ҫ����Ļ�����ID,������Ϊ0
		
    BOOL DEVAPI FAR PASCAL PCI8018_StopDeviceDmaAD(				// �������豸֮����ͣ�豸
										HANDLE hDevice);		// �豸������,����CreateDevice��������

	BOOL DEVAPI FAR PASCAL PCI8018_ReleaseDeviceDmaAD(			// �ر�AD�豸,��ֹ����,���ͷ���Դ
										HANDLE hDevice);		// �豸���,����CreateDevice��������
	
	//##################### AD��Ӳ�������������� ###########################
	BOOL DEVAPI FAR PASCAL PCI8018_SaveParaAD(HANDLE hDevice, PPCI8018_PARA_AD pADPara); // ����ǰ��AD��������������ϵͳ��
    BOOL DEVAPI FAR PASCAL PCI8018_LoadParaAD(HANDLE hDevice, PPCI8018_PARA_AD pADPara); // ��AD����������ϵͳ�ж���
    BOOL DEVAPI FAR PASCAL PCI8018_ResetParaAD(HANDLE hDevice, PPCI8018_PARA_AD pADPara); // ��AD���������ָ�������Ĭ��ֵ

	//################# �ڴ�ӳ��Ĵ���ֱ�Ӳ�������д���� ########################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	BOOL DEVAPI FAR PASCAL PCI8018_GetDeviceBar(				// ȡ��ָ����ָ���豸�Ĵ�����BAR��ַ
										HANDLE hDevice,			// �豸������,����CreateDevice��������
										__int64 pbPCIBar[6]);	// ����PCI BAR���е�ַ,����PCI BAR���ж��ٿ��õ�ַ�뿴Ӳ��˵����
	BOOL DEVAPI FAR PASCAL PCI8018_GetDevVersion(				// ��ȡ�豸�̼�������汾
										HANDLE hDevice,			// �豸������,����CreateDevice��������
										PULONG pulFmwVersion,	// �̼��汾
										PULONG pulDriverVersion);// �����汾
	BOOL DEVAPI FAR PASCAL PCI8018_WriteRegisterByte(			// ��ָ���Ĵ����ռ�λ��д�뵥��������
										HANDLE hDevice,			// �豸������,����CreateDevice��������
										__int64 pbLinearAddr,	// ָ���Ĵ��������Ի���ַ,������GetDeviceAddr�е�pbLinearAddr��������ֵ
										ULONG OffsetBytes,		// ��������Ի���ַ����ַ��ƫ��λ��(�ֽ�)
										BYTE Value);			// ��ָ����ַд�뵥�ֽ����ݣ����ַ�����Ի���ַ��ƫ��λ�þ�����

	BOOL DEVAPI FAR PASCAL PCI8018_WriteRegisterWord(			// д˫�ֽ����ݣ�����ͬ�ϣ�
										HANDLE hDevice, 
										__int64 pbLinearAddr, 
										ULONG OffsetBytes,  
										WORD Value);

	BOOL DEVAPI FAR PASCAL PCI8018_WriteRegisterULong(			// д�Ľ������ݣ�����ͬ�ϣ�
										HANDLE hDevice, 
										__int64 pbLinearAddr, 
										ULONG OffsetBytes,  
										ULONG Value);

	BYTE DEVAPI FAR PASCAL PCI8018_ReadRegisterByte(			// ���뵥�ֽ����ݣ�����ͬ�ϣ�
										HANDLE hDevice, 
										__int64 pbLinearAddr, 
										ULONG OffsetBytes);

	WORD DEVAPI FAR PASCAL PCI8018_ReadRegisterWord(			// ����˫�ֽ����ݣ�����ͬ�ϣ�
										HANDLE hDevice, 
										__int64 pbLinearAddr, 
										ULONG OffsetBytes);

	ULONG DEVAPI FAR PASCAL PCI8018_ReadRegisterULong(			// �������ֽ����ݣ�����ͬ�ϣ�
										HANDLE hDevice, 
										__int64 pbLinearAddr, 
										ULONG OffsetBytes);

	//################# I/O�˿�ֱ�Ӳ�������д���� ########################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	// ����Щ������Ҫ�����ڴ�ͳ�豸����ISA���ߡ����ڡ����ڵ��豸���������ڱ�PCI�豸
    BOOL DEVAPI FAR PASCAL PCI8018_WritePortByte(				// 8λд�˿�
										HANDLE hDevice,			// �豸���(��CreateDevice����)
										__int64 pPort,				// �˿ڵ�ַ
										BYTE Value);			// д����8λ��������

    BOOL DEVAPI FAR PASCAL PCI8018_WritePortWord(HANDLE hDevice, __int64 pPort, WORD Value);
    BOOL DEVAPI FAR PASCAL PCI8018_WritePortULong(HANDLE hDevice, __int64 pPort, ULONG Value);

    BYTE DEVAPI FAR PASCAL PCI8018_ReadPortByte(HANDLE hDevice, __int64 pPort);
    WORD DEVAPI FAR PASCAL PCI8018_ReadPortWord(HANDLE hDevice, __int64 pPort);
    ULONG DEVAPI FAR PASCAL PCI8018_ReadPortULong(HANDLE hDevice, __int64 pPort);
	// �����Ҫ���û�ģʽ�£�ֱ�ӷ���Ӳ���˿ڣ��밲װ��ʹ��ISA\CommUser�µ�����ReadPortByteEx�Ⱥ���

	//########################### ���Ӳ������� ######################################
	HANDLE DEVAPI FAR PASCAL PCI8018_CreateSystemEvent(void); // �����ں��¼����󣬹�InitDeviceDmaAD��VB���̵߳Ⱥ���ʹ��
	BOOL DEVAPI FAR PASCAL PCI8018_ReleaseSystemEvent(HANDLE hEvent); // �ͷ��ں��¼�����

#ifdef __cplusplus
}
#endif

//***********************************************************
// ����FIFO�洢���ĳ���(��)
const long FIFO_IDT7202_LENGTH			= 1024;
const long FIFO_IDT7203_LENGTH			= 2048;
const long FIFO_IDT7204_LENGTH			= 4096;
const long FIFO_IDT7205_LENGTH			= 8192;
const long FIFO_IDT7206_LENGTH			= 16384;
const long FIFO_IDT7207_LENGTH			= 32768;

// �Զ������������������
#ifndef _PCI8018_DRIVER_
	#ifndef _WIN64
		#pragma comment(lib, "PCI8018_32.lib")
		#pragma message("======== Welcome to use our art company's products!")
		#pragma message("======== Automatically linking with PCI8018_32.dll...")
		#pragma message("======== Successfully linked with PCI8018_32.dll")
	#else
		#pragma comment(lib, "PCI8018_64.lib")
		#pragma message("======== Welcome to use our art company's products!")
		#pragma message("======== Automatically linking with PCI8018_64.dll...")
		#pragma message("======== Successfully linked with PCI8018_64.dll")
	#endif
#endif

#endif // _PCI8018_DEVICE_