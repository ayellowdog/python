
#include "PCI8018.h"  // ������������ӿ�
//#############################################################
// �������ڿ�������λ�������̵ĳ���
#define AD_LSB_COUNT  16384.0       // LSB������
#define AD_LSB_HALF   8192          // ��ȡƫ����ʱ����ԭ��λ��
#define AD_VOLT_RANGE 20000.0		// ���̣�mV��(ע������С��)
#define MASK_MSB      0x3FFF			// 
#define MASK_BUMA	  0x2000 

#define DA_VOLT_RANGE 20000.0          // DA���������(mV)
// ������������
#define DEVICE_NAME        "PCI8018"   // �����豸��
#define MAX_FREQUENCY     250000       // ���Ƶ��Hz
#define MAX_AD_CHANNELS   16           // ADͨ����
#define MAX_CHANNEL_COUNT MAX_AD_CHANNELS
#define MAX_SEGMENT_SIZE   8192         
#define DA_LSB_COUNT 4096
#define MAX_DA_BUFFER_SIZE 4096			// DA�������ݵ���󳤶�(��)

//#############################################################
// Header define
#define PCI_BUS     0x01
#define USB_BUS     0x02
#define ISA_BUS     0x03
#define PC104_BUS   0x04
#define PXI_BUS     0x05

const int MAX_RAM_SIZE = 1024 * 64; // ÿͨ��RAM���������(�����)

#define NPT_MODE	0x01 // �ǿղɼ�
#define HALF_MODE   0x02 // �����ɼ�
#define INT_MODE	0x04 // �жϲɼ�
#define DMA_MODE	0x03 // DMA�ɼ�

#define AD_FILE_TYPE 0x00  // �洢AD���ݵ��ļ�
#define DA_FILE_TYPE 0x01  // �洢DA���ݵ��ļ�
#define DIO_FILE_TYPE 0x02 // �洢DIO���ݵ��ļ�

// ����FIFO�ĳ���(��)
#define FIFO_IDT7202_LENGTH 1024
#define FIFO_IDT7203_LENGTH 2048
#define FIFO_IDT7204_LENGTH 4096
#define FIFO_IDT7205_LENGTH 8192
#define FIFO_IDT7206_LENGTH 16384
#define FIFO_IDT7207_LENGTH 32768

#define AD_FIFO_FULL_LENGTH FIFO_IDT7205_LENGTH	   // FIFOȫ������
#define AD_FIFO_HALF_LENGTH AD_FIFO_FULL_LENGTH/2  // FIFO��������
#define LSB_HALF AD_FIFO_HALF_LENGTH 
#define HALF_SIZE_WORDS AD_FIFO_HALF_LENGTH

// �������ݴ���ʽ(gl_nProcModeʹ�õ�ѡ��)
#define PROC_MODE_DIGIT 1 // ������ʾ
#define PROC_MODE_WAVE 2 // ������ʾ
#define PROC_MODE_SAVE 3 // ���̴���

// ���ִ�����ʾģʽ(gl_DigitShowModeʹ�õ�ѡ��)
#define SHOW_MODE_DEC   0 // ʮ������ʾ
#define SHOW_MODE_HEX   1 // ʮ��������ʾ
#define SHOW_MODE_VOLT  2 // ��ѹֵ��ʾ

#define DEFAULT_FILE_TYPE AD_FILE_TYPE
#define DEFAULT_BUSTYPE  PCI_BUS
#define DEFAULT_DEVICE_NUM 0x8018   // Ĭ�ϵ��豸���


#define DEFAULT_VOLTBOTTOM_RANGE -50000
#define DEFAULT_VOLTTOP_RANGE     5000

#define HEAD_END_FLAG  0xAA55AA55

#define MsgBox AfxMessageBox

typedef struct _FILE_HEADER
{
	LONG HeadSizeBytes;						// �ļ�ͷ��Ϣ����
	LONG FileType;  
	// ���豸�����ļ����еĳ�Ա
	LONG BusType;							// �豸��������(DEFAULT_BUS_TYPE)
	LONG DeviceNum;							// ���豸�ı��(DEFAULT_DEVICE_NUM)
	LONG HeadVersion;      					// ͷ��Ϣ�汾(D31-D16=Major  D15-D0=Minijor) = 1.0
	LONG VoltBottomRange[MAX_AD_CHANNELS];	// ��������(mV)
	LONG VoltTopRange[MAX_AD_CHANNELS];	    // ��������(mV)	
	PCI8018_PARA_AD ADPara;					// ����Ӳ������

	LONG nTriggerPos;						// ������λ��
	LONG bOverflow;							// ��̬�����־
	LONG BatCode;							// ͬ���ļ�ʶ����
	LONG HeadEndFlag;						// �ļ�����λ

} FILE_HEADER, *PFILE_HEADER;

typedef struct _THREAD_PARA_        // DA�߳�ʹ��
{
	BOOL	bDeviceRun;				// �߳����б�־
	BOOL	bConstant;				// �㶨ֵ��� ��־
	WORD	WaveValue[4096];		// ��Ų�������
	INT		DigitValue;				// ��ź㶨ֵʹ��
	LONG	OutputRange;			// ÿ�������ĸ���
	HANDLE  hDADevice;				// �豸���
	HANDLE  hExit;					// �˳���־	
}THREAD_PARA, *PTHREAD_PARA;


#define MsgBox AfxMessageBox

