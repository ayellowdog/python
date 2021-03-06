#include<iostream>
#include<stdlib.h>
#include <fstream>
#include<math.h>  
#include"fftguo.h"
using namespace std;
#define PI 3.1415926535897932384626433832795028841971               //定义圆周率值
#define FFT_N 512
#define M 4
#define fs 48000
#define d 0.06
#define v 340
//int fs,d,v,FFT_N;
/*fs=48000;%采样频率
//M=4;%麦克风阵元数 
//d=0.06;%阵元间距
//FFT_N=768;%采样点数
//v=340;%空气中声速
//f_xx每路数据FFT之后的数据 */
struct complex EE(struct complex a,struct complex b);//对两个复数进行乘法运算
void FFT(struct complex *xin);//对输入的复数组进行快速傅里叶变换（FFT）
int DOA(struct complex *f_x1,struct complex *f_x2,struct complex *f_x3,struct complex *f_x4);//波束形成计算角度 
int main()
{
    int i=0;int deg=0;
    struct complex s[FFT_N];          //FFT输入和输出：从S[1]开始存放，根据大小自己定义
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
  /*********计算FFT*******/
   fft(FFT_N,x1);//for(int i=1;i<FFT_N+1)f_x1=x1;                                        //进行快速福利叶变换
   fft(FFT_N,x2);//f_x2=x2;  
   fft(FFT_N,x3);//f_x3=x3
   fft(FFT_N,x4);//f_x4=x4; 
    
  //for(i=0;i<FFT_N;i++)                   //求变换后结果的模值，存入复数的实部部分
  //  {x1[i].real=sqrt(x1[i].real*x1[i].real+x1[i].imag*x1[i].imag);
  //  out<<x1[i].real<<" ";                 //求变换后结果的模值，存入复数的实部部分,数据输出到"output.txt" 
  //  }       
    //  for(i=0;i<FFT_N;i++)                   //求变换后结果的模值，存入复数的实部部分
    //{x2[i].real=sqrt(x2[i].real*x2[i].real+x2[i].imag*x2[i].imag);
    //out<<x2[i].real<<" ";                 //求变换后结果的模值，存入复数的实部部分,数据输出到"output.txt" 
    //}                                    //目的是为了验证对FFT_N点信号进行FFT之后的效果比对                                //目的是为了验证对FFT_N点信号进行FFT之后的效果比对   
               
 //   system("pause");
    deg=DOA(x1,x2,x3,x4);  
    cout<<"声源的角度为:"<<deg<<"度"<<endl;
	system("pause");
    return 0;
}
/*******************************************************************
函数原型：struct complex EE(struct complex b1,struct complex b2)  
函数功能：对两个复数进行乘法运算
输入参数：两个以联合体定义的复数a,b
输出参数：a和b的乘积，以联合体的形式输出
*******************************************************************/
struct complex EE(struct complex a,struct complex b)      
{
 struct complex c;
 c.real=a.real*b.real-a.imag*b.imag;    
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

/*****************************************************************
函数原型：void FFT(struct complex *xin,int FFT_N)
函数功能：对输入的复数组进行快速傅里叶变换（FFT）
输入参数：*xin复数结构体组的首地址指针，struct型
*****************************************************************/
void FFT(struct complex *xin)
{
  int f,m,nv2,nm1,i,k,l,j=0;
  struct complex u,w,t;
  static struct complex f_xin; 
   nv2=FFT_N/2;                 //变址运算，即把自然顺序变成倒位序，采用雷德算法
   nm1=FFT_N-1;  
   for(i=0;i<nm1;i++)        
   {
    if(i<j)                    //如果i<j,即进行变址
     {
      t=xin[j];           
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //求j的下一个倒位序
    while(k<=j)               //如果k<=j,表示j的最高位为1   
     {           
      j=j-k;                 //把最高位变成0
      k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
     }
   j=j+k;                   //把0改为1
  }
                         
  {
   int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
           ;
  for(m=1;m<=l;m++)                         // 控制蝶形结级数
   {                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）FFT_N
    le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
    lei=le/2;                               //同一蝶形结中参加运算的两点的距离
    u.real=1.0;                             //u为蝶形结运算系数，初始值为1
    u.imag=0.0;
    w.real=cos(PI/lei);                     //w为系数商，即当前系数与前一个系数的商
    w.imag=-sin(PI/lei);
    for(j=0;j<=lei-1;j++)              //控制计算不同种蝶形结，即计算系数不同的蝶形结
     {
      for(i=j;i<=FFT_N-1;i=i+le)         //控制同一蝶形结运算，即计算系数相同蝶形结
       {
        ip=i+lei;                           //i，ip分别表示参加蝶形运算的两个节点
        t=EE(xin[ip],u);                    //蝶形运算，详见公式
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
       }
      u=EE(u,w);                           //改变系数，进行下一个蝶形运算
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
     }                                   //我去，总是内存溢出 
    
for(int i=0;i<=180;i++)
    for(int j=0;j<FFT_N;j++)
    {    
        //计算权系数t 
		delay=2*PI*j*fs*d*sin(PI*doa_scan[i]/180)/v/FFT_N;
         for(int k=0;k<M;k++)
         {t[k].real=cos(k*delay);
          t[k].imag=sin(k*delay);
         }
       //对fdata补偿得到Y
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
          for(int ii=0;ii<M;ii++)                                              //计算协方差矩阵
           for(int jj=0;jj<M;jj++)
             cov_x[ii][jj]=EE(f_x[ii][i],f_x[jj][i]);                          //求每个频点对应的4路信号的协方差 
      for(int j=-90;j<=90;j++)
       {
           delay=-2*PI*i*fs*d*sin(PI*j/180)/v/FFT_N;
           for(int k=0;k<M;k++)
           {t[k].real=k*cos(delay);
            t[k].imag=k*sin(delay);
           }
                                                                                //计算每个频点，每个角度的能量值t‘*cov_x*t；
           for(int ii=0;ii<M;i++)                                               //计算t'*cov_x =temp 
            for(int jj=0;jj<M;jj++)
               {
                    temp[1][ii].real+=EE(t[jj],cov_x[jj][ii]).real;
                    temp[1][ii].imag+=EE(t[jj],cov_x[jj][ii]).imag;
               }
          for(int ii=0;ii<M;ii++)
               {
                    Energy.real=EE(temp[1][ii],t[ii]).real; 
                    Energy.imag=EE(temp[1][ii],t[ii]).imag; 
               }                                           //计算temp*t 
            Earray[j][i]=sqrt(Energy.real*Energy.real+Energy.imag*Energy.imag);   
       }
     } 
     */
