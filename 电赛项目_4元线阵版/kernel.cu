
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cufft.h"
#include "cufftw.h"
#include <stdlib.h>

#include<math.h>  
#include "cufftXt.h"
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include <fstream>

//using namespace std;
//#define PI 3.1415926535897932384626433832795028841971               //����Բ����ֵ
//#define FFT_N 1024	
//#define N 1024   //ͨ����*����   һ����ĵ�ѹֵռ��4���ֽ� 
//#define M 4
//#define fs 48000
//#define d 0.06
//#define v 340
////int fs,d,v,FFT_N;
///*fs=48000;%����Ƶ��
////M=4;%��˷���Ԫ�� 
////d=0.06;%��Ԫ���
////FFT_N=768;%��������
////v=340;%����������
////f_xxÿ·����FFT֮������� */
////struct complex EE(struct complex a,struct complex b);//�������������г˷�����
////void FFT(struct complex *xin);//������ĸ�������п��ٸ���Ҷ�任��FFT��
//int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4);//�����γɼ���Ƕ� 
//float a_x1[N],a_x2[N],a_x3[N],a_x4[N];
//long b_x1[N],b_x2[N],b_x3[N],b_x4[N];
//FILE *fp1 = NULL;
//struct complex x1[FFT_N],x2[FFT_N],x3[FFT_N],x4[FFT_N];
// struct complex Energy;
//     struct complex Y,Ytemp;
//  struct complex t[4];
//     struct complex cov_x[4][1024],temp[4][1024],f_x[4][1024];
//	 float delay,DOA_scan[181]={0},Earray[181][1024],maxx=0;
//     int angle=0;
//	 int doa_scan[181];
extern "C" int runtest(long *adbuffer)
{

	//long ADData;
	//float fVolt;
	//for (int z = 0; z < N; z++)
	//{
	//	b_x1[z]=adbuffer[4*z];
	//	b_x2[z]=adbuffer[4*z+1];
	//	b_x3[z]=adbuffer[4*z+2];
	//	b_x4[z]=adbuffer[4*z+3];


	//}
	//for (int j = 0; j < N; j++)
	//{
	//	a_x1[j]=(20000.0/16384)*((b_x1[j]^0x2000)&0x3FFF)- 10000.0;
	//	a_x2[j]=(20000.0/16384)*((b_x2[j]^0x2000)&0x3FFF)- 10000.0;
	//	a_x3[j]=(20000.0/16384)*((b_x3[j]^0x2000)&0x3FFF)- 10000.0;
	//	a_x4[j]=(20000.0/16384)*((b_x4[j]^0x2000)&0x3FFF)- 10000.0;
	//}
	////if (true)
	////{
	////	return 1000;
	////}
	////ADData=(adbuffer[i]^0x2000)&0x3FFF;//��ѹĬ��-10v---+10v
	////	fVolt=((20000.0/16384) * ADData - 10000.0)/1000;


	// int i=0;int deg=0;	float end_point_power=0.0;
 //    struct complex s[FFT_N];          //FFT������������S[1]��ʼ��ţ����ݴ�С�Լ�����
 //    struct complex x1[FFT_N],x2[FFT_N],x3[FFT_N],x4[FFT_N];
 //    for(int k=0;k<FFT_N;k++)
 //       { 
 //       x1[k].real=a_x1[k]/1000 ; x1[k].imag=0;
	//	x2[k].real=a_x2[k]/1000  ; x2[k].imag=0;
 //       x3[k].real=a_x3[k]/1000  ; x3[k].imag=0;
 //       x4[k].real=a_x4[k]/1000   ; x4[k].imag=0;
 //       }   

	///* for(int u=0;u<FFT_N;u++)
	//	end_point_power+=abs(x1[u].real)*abs(x1[u].real);
	//if(end_point_power<1500){
	//	end_point_power=0;
	//	return 1000;}*/
 // /*********����FFT*******/
 //  fft(FFT_N,x1);//for(int i=1;i<FFT_N+1)f_x1=x1;                                        //���п��ٸ���Ҷ�任
 //  fft(FFT_N,x2);//f_x2=x2;  
 //  fft(FFT_N,x3);//f_x3=x3
 //  fft(FFT_N,x4);//f_x4=x4;                                     //Ŀ����Ϊ����֤��FFT_N���źŽ���FFT֮���Ч���ȶ�                                //Ŀ����Ϊ����֤��FFT_N���źŽ���FFT֮���Ч���ȶ�                
 //  deg=DOA(x1,x2,x3,x4);  
 //  return deg;
	return 0;










}
///*******************************************************************
//����ԭ�ͣ�struct complex EE(struct complex b1,struct complex b2)  
//�������ܣ��������������г˷�����
//��������������������嶨��ĸ���a,b
//���������a��b�ĳ˻��������������ʽ���
//*******************************************************************/
//struct complex EE(struct complex a,struct complex b)      
//{
// struct complex c;
// c.real=a.real*b.real-a.imag*b.imag;    
// c.imag=a.real*b.imag+a.imag*b.real;
// return(c);
//}
//
///*****************************************************************
//����ԭ�ͣ�void FFT(struct complex *xin,int FFT_N)
//�������ܣ�������ĸ�������п��ٸ���Ҷ�任��FFT��
//���������*xin�����ṹ������׵�ַָ�룬struct��
//*****************************************************************/
////void FFT(struct complex *xin)
////{
////  int f,m,nv2,nm1,i,k,l,j=0;
////  struct complex u,w,t;
////  static struct complex f_xin; 
////   nv2=FFT_N/2;                 //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
////   nm1=FFT_N-1;  
////   for(i=0;i<nm1;i++)        
////   {
////    if(i<j)                    //���i<j,�����б�ַ
////     {
////      t=xin[j];           
////      xin[j]=xin[i];
////      xin[i]=t;
////     }
////    k=nv2;                    //��j����һ����λ��
////    while(k<=j)               //���k<=j,��ʾj�����λΪ1   
////     {           
////      j=j-k;                 //�����λ���0
////      k=k/2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
////     }
////   j=j+k;                   //��0��Ϊ1
////  }
////                         
////  {
////   int le,lei,ip;                            //FFT����ˣ�ʹ�õ����������FFT����
////    f=FFT_N;
////   for(l=1;(f=f/2)!=1;l++)                  //����l��ֵ����������μ���
////           ;
////  for(m=1;m<=l;m++)                         // ���Ƶ��νἶ��
////   {                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��FFT_N
////    le=2<<(m-1);                            //le���ν���룬����m�����εĵ��ν����le��
////    lei=le/2;                               //ͬһ���ν��вμ����������ľ���
////    u.real=1.0;                             //uΪ���ν�����ϵ������ʼֵΪ1
////    u.imag=0.0;
////    w.real=cos(PI/lei);                     //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
////    w.imag=-sin(PI/lei);
////    for(j=0;j<=lei-1;j++)              //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
////     {
////      for(i=j;i<=FFT_N-1;i=i+le)         //����ͬһ���ν����㣬������ϵ����ͬ���ν�
////       {
////        ip=i+lei;                           //i��ip�ֱ��ʾ�μӵ�������������ڵ�
////        t=EE(xin[ip],u);                    //�������㣬�����ʽ
////        xin[ip].real=xin[i].real-t.real;
////        xin[ip].imag=xin[i].imag-t.imag;
////        xin[i].real=xin[i].real+t.real;
////        xin[i].imag=xin[i].imag+t.imag;
////       }
////      u=EE(u,w);                           //�ı�ϵ����������һ����������
////     }
////   }
////  }
////}
//
//int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4)
//{
//	 for(int i=0;i<181;i++)
//		 doa_scan[i]=i-90;
//	 Y.real=0;Y.imag=0;
//     for(int i=0;i<FFT_N;i++)
//     {
//        f_x[0][i]=f_x1[i];
//        f_x[1][i]=f_x2[i];
//        f_x[2][i]=f_x3[i];
//        f_x[3][i]=f_x4[i];               
//     }                                 
//    
//for(int i=0;i<=180;i++)
//    for(int j=0;j<FFT_N;j++)
//    {    
//        //����Ȩϵ��t 
//		delay=2*PI*j*fs*d*sin(PI*doa_scan[i]/180)/v/FFT_N;
//         for(int k=0;k<M;k++)
//         {t[k].real=cos(k*delay);
//          t[k].imag=sin(k*delay);
//         }
//       //��fdata�����õ�Y
//         for(int k=0;k<M;k++) 
//		 {
//			 Ytemp=EE(t[k],f_x[k][j]);
//			 Y.real=Y.real+Ytemp.real;
//			 Y.imag=Y.imag+Ytemp.imag;
//		 }
//         Earray[i][j]=Y.real*Y.real+Y.imag*Y.imag;
//		  Y.real=0;Y.imag=0;
//    }
//
//     for(int i=0;i<=180;i++)
//     {
//       for(int j=0;j<FFT_N/2;j++)
//     DOA_scan[i]+=Earray[i][j];
//       if(DOA_scan[i]>maxx)
//       {maxx=DOA_scan[i];angle=i-90;}
//     }
//     return angle;          
//}
//
//
////           t[0].real=cos(delay);t[0].imag=sin(delay);
////           t[1].real=4*cos(delay);t[1].imag=4*sin(delay);
////           t[2].real=8*cos(delay);t[2].imag=8*sin(delay); 
////           t[3].real=16*cos(delay);t[3].imag=16*sin(delay);   
///*     for(int i=1;i<FFT_N+1;i++)
//     f_x[0][i]=f_x1[i];
//     for(int i=1;i<FFT_N+1;i++)
//     f_x[1][i]=f_x2[i];
//     for(int i=1;i<FFT_N+1;i++)
//     f_x[2][i]=f_x3[i];
//     for(int i=1;i<FFT_N+1;i++)
//     f_x[3][i]=f_x4[i];   */
// /*    for(int i=0;i<FFT_N;i++)
//     {
//          for(int ii=0;ii<M;ii++)                                              //����Э�������
//           for(int jj=0;jj<M;jj++)
//             cov_x[ii][jj]=EE(f_x[ii][i],f_x[jj][i]);                          //��ÿ��Ƶ���Ӧ��4·�źŵ�Э���� 
//      for(int j=-90;j<=90;j++)
//       {
//           delay=-2*PI*i*fs*d*sin(PI*j/180)/v/FFT_N;
//           for(int k=0;k<M;k++)
//           {t[k].real=k*cos(delay);
//            t[k].imag=k*sin(delay);
//           }
//                                                                                //����ÿ��Ƶ�㣬ÿ���Ƕȵ�����ֵt��*cov_x*t��
//           for(int ii=0;ii<M;i++)                                               //����t'*cov_x =temp 
//            for(int jj=0;jj<M;jj++)
//               {
//                    temp[1][ii].real+=EE(t[jj],cov_x[jj][ii]).real;
//                    temp[1][ii].imag+=EE(t[jj],cov_x[jj][ii]).imag;
//               }
//          for(int ii=0;ii<M;ii++)
//               {
//                    Energy.real=EE(temp[1][ii],t[ii]).real; 
//                    Energy.imag=EE(temp[1][ii],t[ii]).imag; 
//               }                                           //����temp*t 
//            Earray[j][i]=sqrt(Energy.real*Energy.real+Energy.imag*Energy.imag);   
//       }
//     } 
//     */




