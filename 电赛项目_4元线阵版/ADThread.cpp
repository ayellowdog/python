#include "stdAfx.h"
#include "math.h"
#include "RealPlayDlg.h"
#include "fft.h"
#include "cuda.h"
#include "RealPlay.h"
#include "PTZButton.h"
#include "PCI8018.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include "ADThread.h"
//////////////////////////////////doa
#define PI 3.1415926535897932384626433832795028841971               //����Բ����ֵ
#define FFT_N 1024
#define SFFT_N 512
#define M 4
#define fs 48000
#define d 0.027
#define v 340
   struct complex x1[FFT_N],x2[FFT_N],x3[FFT_N],x4[FFT_N];
struct complex EE(struct complex a,struct complex b);//�������������г˷�����
float a_x1[FFT_N],a_x2[FFT_N],a_x3[FFT_N],a_x4[FFT_N];
float a_x11[SFFT_N],a_x22[SFFT_N],a_x33[SFFT_N],a_x44[SFFT_N];
long b_x1[FFT_N],b_x2[FFT_N],b_x3[FFT_N],b_x4[FFT_N];
void FFT(struct complex *xin);//������ĸ�������п��ٸ���Ҷ�任��FFT��
int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4);//�����γɼ���Ƕ� 
int flag=0;
int engercount=0;
//////////////////////////////////////
//LONG ADBuffer[SEGMENT_COUNT][HALF_SIZE_WORDS]; // ���仺������(�洢ԭʼ����)
//ULONG g_ulSegmentID = 0;
CWinThread* m_ReadThread;          // ���߳̾��
ULONGLONG g_TrigPosAD;
HWND run_hwnd;
//////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------------------------------
UINT ReadDataThread_Npt(PVOID hWnd);
UINT ReadDataThread_Dma(PVOID hWnd);
UINT ReadDataThread_Half(PVOID hWnd);
UINT ReadDataThread_INT(PVOID hWnd);
void yuntai(int angle);
int deg;
int numberyuntai=0;
int tempp=1;
string out;
	


SHORT ADData;
	float fVolt;
ofstream myfile("deg.txt",ios::out);  //deg.txt����Ҫ������ļ�������
//###############################################################

//int fs,d,v,FFT_N;
/*fs=48000;%����Ƶ��
//M=4;%��˷���Ԫ�� 
//d=0.06;%��Ԫ���
//FFT_N=768;%��������
//v=340;%����������
//f_xxÿ·����FFT֮������� */
//struct complex EE(struct complex a,struct complex b);//�������������г˷�����
//void FFT(struct complex *xin);//������ĸ�������п��ٸ���Ҷ�任��FFT��

FILE *fp1 = NULL;
int angle=0;
int doa_scan[181];
int capnumber=0;
int energy(long *adbuffer);
// �ɼ��̺߳���(����ʽ��ȡ����)
//
UINT ReadDataThread_Npt(PVOID hWnd)  
{


	//CADDoc* pDoc = theApp.m_pADDoc; 
	CRealPlayDlg *dlg = (CRealPlayDlg *)hWnd;
	run_hwnd = dlg->m_hWnd;
	gl_nReadIndex = 0;              // ��λ��������
	ULONG nReadSizeWords = HALF_SIZE_WORDS - HALF_SIZE_WORDS % gl_nChannelCount;       // ��ȡ����

	HANDLE hDevice = dlg->m_hDevice; 
	DWORD dTmp;
	if (!PCI8018_InitDeviceProAD(hDevice, &ADPara)) // ��Ӳ��������ʼ���豸
	{
		//AfxMessageBox(L"�����ĳ�ʼ������.....", MB_ICONERROR);		
		return -1;
	}

	PCI8018_StartDeviceProAD(hDevice);  // ��ʼ���������豸���� 

	while (gl_bDeviceADRun)  // ѭ���ɼ�AD����
	{	

//		DWORD dwStart = GetTickCount();
		// ������
		//_restart:
		if (!PCI8018_ReadDeviceProAD_Npt(hDevice, ADBuffer[gl_nReadIndex], nReadSizeWords, (LONG*)gl_ReadSizeWords))
		{
			//AfxMessageBox(L"Read Data Error.....");
		}
// 		else
// 		{
// 			FILE *fp = fopen("C:\\capdata.txt","a+");
// 			fprintf(fp,"%d\n",capnumber);
// 			fclose(fp);
// 			fp = NULL;
// 			capnumber++;
		/*	if (energy(ADBuffer[gl_nReadIndex]) == 1000)
		{
		goto _restart;
		}*/
		deg= run(ADBuffer[gl_nReadIndex]);
		if (deg==1000)
		{
		}else
		{
			yuntai(deg);
		}
		
			//if (deg==1000)
			//{
			//}else
			//{
			//	myfile.open("deg.txt",ios::out | ios::app);

			//	myfile<<deg<<endl;
			//	myfile.close();
			//}
	
			//memset(ADBuffer, 0x00, sizeof(ADBuffer)); 
		//}

		if (!PCI8018_GetDevStatusProAD(hDevice, &ADStatus))
		{
			//AfxMessageBox(L"Get Device Status Error...\n");	
			goto ExitReadThread;
		}			

// 		if (gl_nProcMode == PROC_MODE_SAVE)
// 			WriteFile(gl_hFileObject, ADBuffer[gl_nReadIndex], nReadSizeWords*sizeof(LONG), &dTmp, NULL);
		gl_nDrawIndex = gl_nReadIndex;          
		gl_nReadIndex++;
		if (gl_nReadIndex >= MAX_SEGMENT_COUNT) gl_nReadIndex = 0;

		// �����¼������߻��ƴ����̣߳����������Ѳɼ����
		SetEvent(gl_hEvent); // ������ʾ	

		if (gl_FirstScreenStop) // ��Ҫ������ֹͣ����ֻ��һ��ˢ��	
		{
			gl_bDeviceADRun = FALSE; // ��ֹAD�ɼ�
			PCI8018_ReleaseDeviceProAD(hDevice); // �ͷ�AD
			goto ExitReadThread;
		}

// 		DWORD dwStop = GetTickCount()-dwStart;
// 		DWORD iii=0;
	} // �߳�ѭ��ȡ�� 


ExitReadThread:
	SetEvent(gl_hExitEvent); // �����豸�ɹ��˳���Ϣ���ùر��豸���̵߳ô���Ϣ
	if (gl_FirstScreenStop)	dlg->StopDeviceAD();

	return TRUE;  
} // ReadDataThread_Pro

// �ɼ��̺߳���(������ʽ��ȡ����)
UINT ReadDataThread_Half(PVOID hWnd)
{


	CRealPlayDlg *dlg = (CRealPlayDlg *)hWnd;
	HANDLE hDevice = dlg->m_hDevice; // �豸���
	int iReadSizeWords = HALF_SIZE_WORDS - HALF_SIZE_WORDS % gl_nChannelCount; // ��ȡ���ݵĴ�С(�ڰ�����ʽ��,Ӧ����С�ڰ�������)
	DWORD dTmp;
	if (!PCI8018_InitDeviceProAD(hDevice, &ADPara)) // ��Ӳ��������ʼ���豸
	{
		//AfxMessageBox(L"�����ĳ�ʼ������.....", MB_ICONERROR);		
		return -1;
	}

	PCI8018_StartDeviceProAD(hDevice);  // ��ʼ���������豸���� 
	while (gl_bDeviceADRun)  // ѭ���ɼ�AD����
	{	
		while (gl_bDeviceADRun) // ��ѯ��ǰFIFO�洢��״̬�Ƿ��Ѵﵽ����
		{
			if (!PCI8018_GetDevStatusProAD(hDevice, &ADStatus))
			{
				//AfxMessageBox(L"Get Device Status Error...\n");	
				goto ExitReadThread;
			}

			if (ADStatus.bHalf)
			{
				break;
			}		
			else
			{				
				if (!gl_bDeviceADRun)
					goto ExitReadThread;				
			}
		}
		long nRetReadSizeWords;
		if (!PCI8018_ReadDeviceProAD_Half(hDevice, ADBuffer[gl_nReadIndex], iReadSizeWords, (long*)&nRetReadSizeWords))
		{
			//AfxMessageBox(L"Read Data Error.....");
		}else
		{
			deg= run(ADBuffer[gl_nReadIndex]);

			myfile.open("deg.txt",ios::out | ios::app);

			myfile<<deg<<endl;
			myfile.close();
			memset(ADBuffer, 0x00, sizeof(ADBuffer)); 

		}

		// 		if (gl_nProcMode == PROC_MODE_SAVE)
		// 			PCI8018_WriteFile(gl_hFileObject, ADBuffer[gl_nReadIndex], iReadSizeWords*sizeof(LONG));
		if (gl_nProcMode == PROC_MODE_SAVE)
		{
			//WriteFile(gl_hFileObject, ADBuffer[gl_nReadIndex], iReadSizeWords*sizeof(LONG), &dTmp, NULL);
			
		}
		gl_nDrawIndex = gl_nReadIndex;
		gl_nReadIndex++;

		if (gl_nReadIndex >= MAX_SEGMENT_COUNT)	gl_nReadIndex = 0;

		SetEvent(gl_hEvent);// ������ʾ	

		if (gl_FirstScreenStop) // ��Ҫ������ֹͣ����ֻ��һ��ˢ��	
		{
			gl_bDeviceADRun = FALSE;            // ��ֹAD�ɼ�
			PCI8018_ReleaseDeviceProAD( hDevice ); // �ͷ�AD			
			goto ExitReadThread;
		}
	}// �߳�ѭ��ȡ��   

ExitReadThread:
	SetEvent(gl_hExitEvent); // �����豸�ɹ��˳���Ϣ���ùر��豸���̵߳ô���Ϣ
	if (gl_FirstScreenStop)	dlg->StopDeviceAD();

	return TRUE;  


} // ReadDataThread_Half

// �ɼ��̺߳���(DMA��ʽ��ȡ����)
UINT ReadDataThread_Dma(PVOID hWnd)  
{
	CRealPlayDlg *dlg = (CRealPlayDlg *)hWnd;
	//CADDoc* pDoc = pApp->m_pADDoc; 
	DWORD dTmp;
	int iReadSizeWords = HALF_SIZE_WORDS - HALF_SIZE_WORDS % gl_nChannelCount; // ��ȡ���ݵĴ�С

	gl_nReadIndex = 0;            // ADBuffer��ǰд���ݻ���������
	ULONG SegmentID = 0;
	PCI8018_STATUS_DMA DMAStatus;                            // Ӳ��״̬	
	HANDLE hDevice = dlg->m_hDevice;                      // �豸���	
	HANDLE hDmaEvent = PCI8018_CreateSystemEvent();      // �����ж��¼�

	int DMASegment0 = 0;

	if (!PCI8018_InitDeviceDmaAD(hDevice, hDmaEvent, 
		&ADBuffer[0][0], iReadSizeWords,
		MAX_SEGMENT_COUNT, AD_FIFO_HALF_LENGTH, &ADPara)) // ��Ӳ��������ʼ���豸
	{
		//AfxMessageBox(L"�����ĳ�ʼ������.....", MB_ICONERROR);		
		return -1;
	}
	PCI8018_StartDeviceDmaAD(hDevice);  // ��ʼ���������豸���� 
	int nTempIndex = 0;
	
	while (gl_bDeviceADRun) // ѭ���ɼ�AD����
	{		
		while (TRUE)
		{
			if (WaitForSingleObject(hDmaEvent, 200) == WAIT_OBJECT_0)
				break;
			else
			{
				if (!gl_bDeviceADRun) 
					goto ExitReadThread;
			}
			Sleep(1);
		}


		if (!PCI8018_GetDevStatusDmaAD(hDevice, &DMAStatus))
		{
			//MessageBox(_T("Get Device Status Error...\n"));	
			goto ExitReadThread;
		}


		SegmentID = DMASegment0;

		for (int index = 0; index < MAX_SEGMENT_COUNT; index++)
		{
			if(DMAStatus.bSegmentSts[SegmentID])
			{


				// 				if(gl_nProcMode == PROC_MODE_SAVE)
				// 				{
				// 					PCI8018_WriteFile(gl_hFileObject, ADBuffer[gl_nReadIndex], iReadSizeWords*sizeof(LONG));
				// 				}
				if (gl_nProcMode == PROC_MODE_SAVE)
				{
					//WriteFile(gl_hFileObject, ADBuffer[gl_nReadIndex], iReadSizeWords*sizeof(LONG), &dTmp, NULL);
					
					deg=run(ADBuffer[0]); 
					PCI8018_ReleaseDeviceDmaAD(hDevice);
					PCI8018_InitDeviceDmaAD(hDevice, hDmaEvent, 
						&ADBuffer[0][0], iReadSizeWords,
						MAX_SEGMENT_COUNT, AD_FIFO_HALF_LENGTH, &ADPara);
					PCI8018_StartDeviceDmaAD(hDevice);
					memset(ADBuffer,0x00,sizeof(ADBuffer));
					
				

					
					

				}
				gl_nReadIndex = SegmentID;
				gl_nReadIndex++;

				if (gl_nReadIndex >= MAX_SEGMENT_COUNT)	gl_nReadIndex = 0;
				SetEvent(gl_hEvent); // �����¼������߻��ƴ����̣߳����������Ѳɼ����


				if(!PCI8018_SetDevStatusDmaAD(hDevice, SegmentID))
				{
					//AfxMessageBox(L"SetDevStatusDmaAD Error...\n");
					goto ExitReadThread;
				}	
				DMASegment0 = (SegmentID + 1)%MAX_SEGMENT_COUNT;
			}
			SegmentID ++;
			if (SegmentID >= MAX_SEGMENT_COUNT)
			{
				SegmentID = 0;
			}
		}

		if (gl_FirstScreenStop) // ��Ҫ������ֹͣ����ֻ��һ��ˢ��	
		{
			gl_bDeviceADRun = FALSE;            // ��ֹAD�ɼ�			
			goto ExitReadThread;
		}

	} // �߳�ѭ��ȡ�� 

ExitReadThread:


	if (ADPara.ClockSource == 0)
	{
		PCI8018_StopDeviceDmaAD(hDevice);
		//PCI8018_ReleaseDeviceDmaAD( hDevice ); // �ͷ�AD

		if (!PCI8018_GetDevStatusDmaAD(hDevice, &DMAStatus))
		{
			//AfxMessageBox(L"Get Device Status Error...\n");	
		}	

		SegmentID = DMASegment0;	
		for (int index = 0; index < MAX_SEGMENT_COUNT; index++)
		{
			if(DMAStatus.bSegmentSts[SegmentID])
			{			
				if(gl_nProcMode == PROC_MODE_SAVE)
				{
					WriteFile(gl_hFileObject, ADBuffer[gl_nReadIndex], iReadSizeWords*sizeof(LONG),&dTmp ,NULL);
				}

				gl_nReadIndex = SegmentID;			
				gl_nReadIndex++;				
				if (gl_nReadIndex >= MAX_SEGMENT_COUNT)	gl_nReadIndex = 0;
				SetEvent(gl_hEvent); // �����¼������߻��ƴ����̣߳����������Ѳɼ����

				if(!PCI8018_SetDevStatusDmaAD(hDevice, SegmentID))
				{
					//AfxMessageBox(L"SetDevStatusDmaAD Error...\n");				
				}	
				DMASegment0 = (SegmentID + 1)%MAX_SEGMENT_COUNT;
			}
			SegmentID ++;
			if (SegmentID >= MAX_SEGMENT_COUNT)
			{
				SegmentID = 0;
			}
		}

	}

	SetEvent(gl_hExitEvent); // �����豸�ɹ��˳���Ϣ���ùر��豸���̵߳ô���Ϣ
	if (gl_FirstScreenStop)	dlg->StopDeviceAD();		  
	return 0;		    
} // ReadDataThread_Dma

// �ɼ��̺߳���(�жϷ�ʽ��ȡ����)
UINT ReadDataThread_INT(PVOID hWnd)  
{

	
	return 0;		  
} // ReadDataThread_INT

BOOL MyStopDeviceAD(HANDLE hDevice)
{
	gl_bDeviceADRun = FALSE;   // ��ֹAD�ɼ�
	::WaitForSingleObject(gl_hExitEvent, INFINITE);

	switch(gl_nSampleMode)
	{
	case NPT_MODE:
		PCI8018_ReleaseDeviceProAD( hDevice ); // �ͷ�AD
		break;
	case HALF_MODE:
		PCI8018_ReleaseDeviceProAD( hDevice ); // �ͷ�AD
		break;
	case DMA_MODE:
		PCI8018_ReleaseDeviceDmaAD( hDevice ); // �ͷ�AD
		break;
	case INT_MODE:
		PCI8018_ReleaseDeviceIntAD( hDevice ); // �ͷ�AD
		break;
	}
	
	gl_bCreateDevice = FALSE;
	return TRUE;
}
void yuntai(int angle)
{
	//time=180+8.54*deg�Ƕ�ʱ�乫ʽ
	/*FILE *fp = fopen("C:\\degedeeg.txt","a+");
	fprintf(fp,"%d\n",angle);
	fclose(fp);*/
//	fp = NULL;

	LONG lPlayHandle = g_pMainDlg->GetPlayHandle();
	
	int delay=0;
	delay=angle-tempp;
	if (delay>0)
	{
		NET_DVR_PTZControlWithSpeed(lPlayHandle,PAN_LEFT,0,7);
		Sleep(180+8.3*abs(delay));

		NET_DVR_PTZControlWithSpeed(lPlayHandle,PAN_LEFT,1,7);
	}else if(delay<0)
	{
		NET_DVR_PTZControlWithSpeed(lPlayHandle,PAN_RIGHT,0,7);
		Sleep(180+8.3*abs(delay));

		NET_DVR_PTZControlWithSpeed(lPlayHandle,PAN_RIGHT,1,7);
	}else if (delay==0)
	{
		
	}
	tempp=angle;
}

int run(long *adbuffer)
{
	long ADData;
	float fVolt;
	for (int z = 0; z < FFT_N; z++)
	{
		b_x1[z]=adbuffer[4*z];
		b_x2[z]=adbuffer[4*z+1];
		b_x3[z]=adbuffer[4*z+2];
		b_x4[z]=adbuffer[4*z+3];


	}
	for (int j = 0; j < FFT_N; j++)
	{
		a_x1[j]=(20000.0/16384)*((b_x1[j]^0x2000)&0x3FFF)- 10000.0;
		a_x2[j]=(20000.0/16384)*((b_x2[j]^0x2000)&0x3FFF)- 10000.0;
		a_x3[j]=(20000.0/16384)*((b_x3[j]^0x2000)&0x3FFF)- 10000.0;
		a_x4[j]=(20000.0/16384)*((b_x4[j]^0x2000)&0x3FFF)- 10000.0;
	}



	 int i=0;int deg=0;	float end_point_power=0.0;
     struct complex s[FFT_N];          //FFT������������S[1]��ʼ��ţ����ݴ�С�Լ�����
     struct complex x1[FFT_N],x2[FFT_N],x3[FFT_N],x4[FFT_N];
	 for(int k=0;k<FFT_N;k++)
	 { 
		 x1[k].real=a_x1[k]/1000 ; x1[k].imag=0;
		 x2[k].real=a_x2[k]/1000  ; x2[k].imag=0;
		 x3[k].real=a_x3[k]/1000  ; x3[k].imag=0;
		 x4[k].real=a_x4[k]/1000   ; x4[k].imag=0;
	 } 
	
		 float temp=0;
		 for(int u=0;u<FFT_N;u++)
		 {
			 temp+=x1[u].real;		 
		 }
		 temp=temp/FFT_N;
		 for(int y=0;y<FFT_N;y++)
		 { end_point_power+=abs(x1[y].real-temp)*abs(x1[y].real-temp);}
		 	 ::SendMessage(run_hwnd,WM_LEVELOK,end_point_power,NULL);
		 if(end_point_power<100){
			 engercount++;
			 if (engercount==20)
			 {
				 flag=0;
				 engercount=0;
			 }
			 return 1000;}
		 //FILE *fp = fopen("C:\\x1.txt","a+");

		 //for (int x11=0;x11<FFT_N;x11++)
		 //{
			// fprintf(fp,"%f\n",x1[x11].real);
			// fprintf(fp,"%f\n",x2[x11].real);
			// fprintf(fp,"%f\n",x3[x11].real);
			// fprintf(fp,"%f\n",x4[x11].real);
		 //}

		 //fclose(fp);
		 //fp=NULL;
		 fft(FFT_N,x1);//for(int i=1;i<FFT_N+1)f_x1=x1;                                        //���п��ٸ���Ҷ�任
		 fft(FFT_N,x2);//f_x2=x2;  
		 fft(FFT_N,x3);//f_x3=x3
		 fft(FFT_N,x4);//f_x4=x4
		 deg=DOA(x1,x2,x3,x4);
	
		 flag++;
		 if (flag==1)
		 {		
			  ::SendMessage(run_hwnd,WM_DEGOK,deg,NULL);
			  return deg;
		 }else if(flag==6)
		 { 
			 flag=0;
			 return 1000;
		 }
		 else
		 {
			 return 1000;
		 } 	 

	
}
struct complex EE(struct complex a,struct complex b)      
{
	struct complex c;
	c.real=a.real*b.real-a.imag*b.imag;    
	c.imag=a.real*b.imag+a.imag*b.real;
	return(c);
}
int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4)
{
	struct complex Energy;
	struct complex Y,Ytemp;
	struct complex t[M];
	struct complex cov_x[M][FFT_N],temp[M][FFT_N],f_x[M][FFT_N];
	float delay,DOA_scan[181]={0.0},Earray[181][FFT_N]={0.0},max=0.0;
	int angle=0;
	int doa_scan[181];
	for(int i=0;i<181;i++)
		doa_scan[i]=i-90;
	Y.real=0;Y.imag=0;
	for(int i=0;i<FFT_N;i++)
	{
		f_x[0][i]=f_x1[i];
		f_x[1][i]=f_x2[i];
		f_x[2][i]=f_x3[i];
		f_x[3][i]=f_x4[i];               
	}                                   

	for(int i=0;i<=180;i++)
		for(int j=0;j<FFT_N;j++)
		{    
			//����Ȩϵ��t 
			delay=-2*PI*j*fs*d*sin(PI*doa_scan[i]/180)/v/FFT_N;
			for(int k=0;k<M;k++)
			{t[k].real=cos(k*delay);
			t[k].imag=sin(k*delay);
			}
			//��fdata�����õ�Y
			for(int k=0;k<M;k++) 
			{
				Ytemp=EE(t[k],f_x[k][j]);
				Y.real=Y.real+Ytemp.real;
				Y.imag=Y.imag+Ytemp.imag;
			}
			Earray[i][j]=Y.real*Y.real+Y.imag*Y.imag;
			Y.real=0;Y.imag=0;
		}

		for(int i=0;i<=180;i++)
		{
			for(int j=0;j<FFT_N/2;j++)
				DOA_scan[i]+=Earray[i][j];
			if(DOA_scan[i]>max)
			{max=DOA_scan[i];angle=i-90;}
		}
		return angle;          
}

//
//
//
//
//}
//
//int energy(long *adbuffer)
//{
//	long ADData;
//	float fVolt;
//	for (int z = 0; z < N; z++)
//	{
//		b_x1[z]=adbuffer[4*z];
//		b_x2[z]=adbuffer[4*z+1];
//		b_x3[z]=adbuffer[4*z+2];
//		b_x4[z]=adbuffer[4*z+3];
//
//
//	}
//	for (int j = 0; j < N; j++)
//	{
//		a_x1[j]=(20000.0/16384)*((b_x1[j]^0x2000)&0x3FFF)- 10000.0;
//		a_x2[j]=(20000.0/16384)*((b_x2[j]^0x2000)&0x3FFF)- 10000.0;
//		a_x3[j]=(20000.0/16384)*((b_x3[j]^0x2000)&0x3FFF)- 10000.0;
//		a_x4[j]=(20000.0/16384)*((b_x4[j]^0x2000)&0x3FFF)- 10000.0;
//	}
//	//if (true)
//	//{
//	//	return 1000;
//	//}
//	//ADData=(adbuffer[i]^0x2000)&0x3FFF;//��ѹĬ��-10v---+10v
//	//	fVolt=((20000.0/16384) * ADData - 10000.0)/1000;
//
//
//	int i=0;int deg=0;	float end_point_power=0.0;
//	struct complex s[FFT_N];          //FFT������������S[1]��ʼ��ţ����ݴ�С�Լ�����
//	struct complex x1[FFT_N],x2[FFT_N],x3[FFT_N],x4[FFT_N];
//	for(int k=0;k<FFT_N;k++)
//	{ 
//		x1[k].real=a_x1[k]/1000 ; x1[k].imag=0;
//		x2[k].real=a_x2[k]/1000  ; x2[k].imag=0;
//		x3[k].real=a_x3[k]/1000  ; x3[k].imag=0;
//		x4[k].real=a_x4[k]/1000   ; x4[k].imag=0;
//	}   
//	float temp=0;
//	for(int u=0;u<FFT_N;u++)
//	{
//		temp+=x1[u].real;		 
//	}
//	temp=temp/FFT_N;
//	for(int y=0;y<FFT_N;y++)
//		end_point_power+=abs(x1[y].real-temp)*abs(x1[y].real-temp);
//	if(end_point_power<100)
//	{
//		end_point_power=0;
//		return 1000;
//	}
//	else
//	{
//		return 500;
//	}
//}



