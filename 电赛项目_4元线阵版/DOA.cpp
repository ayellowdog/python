#include<iostream>
#include<stdlib.h>
#include <fstream>
#include<math.h>  
#include"fftguo.h"
using namespace std;
#define PI 3.1415926535897932384626433832795028841971               //����Բ����ֵ
#define FFT_N 512
#define M 4
#define fs 48000
#define d 0.06
#define v 340
//int fs,d,v,FFT_N;
/*fs=48000;%����Ƶ��
//M=4;%��˷���Ԫ�� 
//d=0.06;%��Ԫ���
//FFT_N=768;%��������
//v=340;%����������
//f_xxÿ·����FFT֮������� */
struct complex EE(struct complex a,struct complex b);//�������������г˷�����
void FFT(struct complex *xin);//������ĸ�������п��ٸ���Ҷ�任��FFT��
int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4);//�����γɼ���Ƕ� 
int main()
{
    int i=0;int deg=0;
    struct complex s[FFT_N];          //FFT������������S[1]��ʼ��ţ����ݴ�С�Լ�����
//    cout<<"hello"<<endl;
//    system("pause");
     ifstream in1("send1.txt");
     ifstream in2("send2.txt");
     ifstream in3("send3.txt");
     ifstream in4("send4.txt");
     ofstream out("output.txt");
     struct complex x1[FFT_N],x2[FFT_N],x3[FFT_N],x4[2*FFT_N];
     for(int i=0;i<FFT_N;i++)
        { 
        in1>>x1[i].real; x1[i].imag=0;
		in2>>x2[i].real; x2[i].imag=0;
        in3>>x3[i].real; x3[i].imag=0;
        in4>>x4[i].real; x4[i].imag=0;
      //     out<<x1[i]<<" ";
        }   
    //  cout<<i<<" "<<x1[i];
    //  system("pause");
//    for(int i=1;i<FFT_N;i++)
//    out<<x1[i]<<" ";
  /*********����FFT*******/
   fft(FFT_N,x1);//for(int i=1;i<FFT_N+1)f_x1=x1;                                        //���п��ٸ���Ҷ�任
   fft(FFT_N,x2);//f_x2=x2;  
   fft(FFT_N,x3);//f_x3=x3
   fft(FFT_N,x4);//f_x4=x4; 
    
  //for(i=0;i<FFT_N;i++)                   //��任������ģֵ�����븴����ʵ������
  //  {x1[i].real=sqrt(x1[i].real*x1[i].real+x1[i].imag*x1[i].imag);
  //  out<<x1[i].real<<" ";                 //��任������ģֵ�����븴����ʵ������,���������"output.txt" 
  //  }       
    //  for(i=0;i<FFT_N;i++)                   //��任������ģֵ�����븴����ʵ������
    //{x2[i].real=sqrt(x2[i].real*x2[i].real+x2[i].imag*x2[i].imag);
    //out<<x2[i].real<<" ";                 //��任������ģֵ�����븴����ʵ������,���������"output.txt" 
    //}                                    //Ŀ����Ϊ����֤��FFT_N���źŽ���FFT֮���Ч���ȶ�                                //Ŀ����Ϊ����֤��FFT_N���źŽ���FFT֮���Ч���ȶ�   
               
 //   system("pause");
    deg=DOA(x1,x2,x3,x4);  
    cout<<"��Դ�ĽǶ�Ϊ:"<<deg<<"��"<<endl;
	system("pause");
    return 0;
}
/*******************************************************************
����ԭ�ͣ�struct complex EE(struct complex b1,struct complex b2)  
�������ܣ��������������г˷�����
��������������������嶨��ĸ���a,b
���������a��b�ĳ˻��������������ʽ���
*******************************************************************/
struct complex EE(struct complex a,struct complex b)      
{
 struct complex c;
 c.real=a.real*b.real-a.imag*b.imag;    
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

/*****************************************************************
����ԭ�ͣ�void FFT(struct complex *xin,int FFT_N)
�������ܣ�������ĸ�������п��ٸ���Ҷ�任��FFT��
���������*xin�����ṹ������׵�ַָ�룬struct��
*****************************************************************/
void FFT(struct complex *xin)
{
  int f,m,nv2,nm1,i,k,l,j=0;
  struct complex u,w,t;
  static struct complex f_xin; 
   nv2=FFT_N/2;                 //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
   nm1=FFT_N-1;  
   for(i=0;i<nm1;i++)        
   {
    if(i<j)                    //���i<j,�����б�ַ
     {
      t=xin[j];           
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //��j����һ����λ��
    while(k<=j)               //���k<=j,��ʾj�����λΪ1   
     {           
      j=j-k;                 //�����λ���0
      k=k/2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
     }
   j=j+k;                   //��0��Ϊ1
  }
                         
  {
   int le,lei,ip;                            //FFT����ˣ�ʹ�õ����������FFT����
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //����l��ֵ����������μ���
           ;
  for(m=1;m<=l;m++)                         // ���Ƶ��νἶ��
   {                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��FFT_N
    le=2<<(m-1);                            //le���ν���룬����m�����εĵ��ν����le��
    lei=le/2;                               //ͬһ���ν��вμ����������ľ���
    u.real=1.0;                             //uΪ���ν�����ϵ������ʼֵΪ1
    u.imag=0.0;
    w.real=cos(PI/lei);                     //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
    w.imag=-sin(PI/lei);
    for(j=0;j<=lei-1;j++)              //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
     {
      for(i=j;i<=FFT_N-1;i=i+le)         //����ͬһ���ν����㣬������ϵ����ͬ���ν�
       {
        ip=i+lei;                           //i��ip�ֱ��ʾ�μӵ�������������ڵ�
        t=EE(xin[ip],u);                    //�������㣬�����ʽ
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
       }
      u=EE(u,w);                           //�ı�ϵ����������һ����������
     }
   }
  }
}

int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4)
{
     struct complex Energy;
     struct complex Y,Ytemp;
     struct complex t[M];
     struct complex cov_x[M][FFT_N],temp[M][FFT_N],f_x[M][FFT_N];
	 float delay,DOA_scan[181]={0},Earray[181][FFT_N],max=0;
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
     }                                   //��ȥ�������ڴ���� 
    
for(int i=0;i<=180;i++)
    for(int j=0;j<FFT_N;j++)
    {    
        //����Ȩϵ��t 
		delay=2*PI*j*fs*d*sin(PI*doa_scan[i]/180)/v/FFT_N;
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


//           t[0].real=cos(delay);t[0].imag=sin(delay);
//           t[1].real=4*cos(delay);t[1].imag=4*sin(delay);
//           t[2].real=8*cos(delay);t[2].imag=8*sin(delay); 
//           t[3].real=16*cos(delay);t[3].imag=16*sin(delay);   
/*     for(int i=1;i<FFT_N+1;i++)
     f_x[0][i]=f_x1[i];
     for(int i=1;i<FFT_N+1;i++)
     f_x[1][i]=f_x2[i];
     for(int i=1;i<FFT_N+1;i++)
     f_x[2][i]=f_x3[i];
     for(int i=1;i<FFT_N+1;i++)
     f_x[3][i]=f_x4[i];   */
 /*    for(int i=0;i<FFT_N;i++)
     {
          for(int ii=0;ii<M;ii++)                                              //����Э�������
           for(int jj=0;jj<M;jj++)
             cov_x[ii][jj]=EE(f_x[ii][i],f_x[jj][i]);                          //��ÿ��Ƶ���Ӧ��4·�źŵ�Э���� 
      for(int j=-90;j<=90;j++)
       {
           delay=-2*PI*i*fs*d*sin(PI*j/180)/v/FFT_N;
           for(int k=0;k<M;k++)
           {t[k].real=k*cos(delay);
            t[k].imag=k*sin(delay);
           }
                                                                                //����ÿ��Ƶ�㣬ÿ���Ƕȵ�����ֵt��*cov_x*t��
           for(int ii=0;ii<M;i++)                                               //����t'*cov_x =temp 
            for(int jj=0;jj<M;jj++)
               {
                    temp[1][ii].real+=EE(t[jj],cov_x[jj][ii]).real;
                    temp[1][ii].imag+=EE(t[jj],cov_x[jj][ii]).imag;
               }
          for(int ii=0;ii<M;ii++)
               {
                    Energy.real=EE(temp[1][ii],t[ii]).real; 
                    Energy.imag=EE(temp[1][ii],t[ii]).imag; 
               }                                           //����temp*t 
            Earray[j][i]=sqrt(Energy.real*Energy.real+Energy.imag*Energy.imag);   
       }
     } 
     */
