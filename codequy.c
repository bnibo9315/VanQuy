
#include <16f877a.h>
#FUSES HS // cho phep su dung thach anh ngoai
#use delay(clock=20M)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)   //chuan uart
UNSIGNED CHAR ma7doan[16]= {0XC0,0XF9,0xA4,0XB0,0X99,0X92,0X83,0XF8,
0X80,0X90,0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
int a=0,b=0,dem=0, val1=15,val2=25;
#DEFINE Xt PIN_c3
#DEFINE Vt PIN_c4
#DEFINE Dt PIN_c5
#DEFINE Dp PIN_c0
#DEFINE Vp PIN_c1
#DEFINE Xp PIN_c2
#DEFINE HNT PIN_B4
#DEFINE HNP PIN_B5
SIGNED INT8 BDN,bdnt;
SIGNED INT8 DOTRAI,XANHTRAI,VANGTRAI; 
SIGNED INT8 DOPHAI,XANHPHAI,VANGPHAI;
signed int8 ghdo,ghxanh,ghvang; 
unsigned int8 ttt,ttp,ktrt,ktrp; 
unsigned int8 led0,led1,led2,led3; //
int1 tt1t,tt1p;

VOID HIENTHI()
{
 OUTPUT_D(led0); OUTPUT_high(PIN_A1); DELAY_MS(1);
OUTPUT_low(PIN_A1);
 OUTPUT_D(led1); OUTPUT_high(PIN_A0); DELAY_MS(1);
OUTPUT_low(PIN_A0);
 OUTPUT_D(led2); OUTPUT_high(PIN_A3); DELAY_MS(1);
OUTPUT_low(PIN_A3);
 OUTPUT_D(led3); OUTPUT_high(PIN_A2); DELAY_MS(1);
OUTPUT_low(PIN_A2);
}
#INT_TIMER1 
VOID INTERRUPT_TIMER1()
{
 BDN++;
 bdnt++;
 SET_TIMER1(3036); 
}


void dem_ben_trai()
{
 if(ttt==0) 
 {
 
 if(xanhtrai>0) // kiem tra co nho hon khong chua
 { // neu chua
 xanhtrai--; //
 led0 = ma7doan[xanhtrai/10]; // 15/10 chia lay nguyen , duoc 1 du 5
 led1 = ma7doan[xanhtrai%10]; //15%10 chia lay du
 OUTPUT_high(DT); // led gan tich cuc muc thap
 OUTPUT_high(VT); // high = 1, low = 0
 OUTPUT_low(XT); // den xanh sang, 2 den con lai tat
 }
 else // -1
 {
 ttt=1;
 xanhtrai=ghxanh; // gh xanh phu thuoc trong chuong trinh main
 vangtrai=ghvang;
 led0 = ma7doan[vangtrai/10];
 led1 = ma7doan[vangtrai%10];
 OUTPUT_high(Dt);
 OUTPUT_low(Vt);
 OUTPUT_high(Xt);
 }
 }
 else if(ttt==1)
 {
 if(vangtrai>0)
 {
 vangtrai--;
 led0 = ma7doan[vangtrai/10];
 led1 = ma7doan[vangtrai%10];
 OUTPUT_high(Dt);
 OUTPUT_low(Vt);
 OUTPUT_high(Xt);
 }
 else
 {
 vangtrai=ghvang;
 dotrai=ghdo;
 led0 = ma7doan[dotrai/10];
 led1 = ma7doan[dotrai%10];
 OUTPUT_low(Dt);
 OUTPUT_high(Vt);
 OUTPUT_high(Xt);
 ttt=2;
 dem++;
 }
 }
 else if(ttt==2)
 {
 if(dotrai>0)
 {
 dotrai--;
 led0 = ma7doan[dotrai/10];
 led1 = ma7doan[dotrai%10];
 OUTPUT_low(Dt);
 OUTPUT_high(Vt);
 OUTPUT_high(Xt);
 }
 else
 {
 dotrai=ghdo;

 xanhtrai=ghxanh;
 led0 = ma7doan[xanhtrai/10];
 led1 = ma7doan[xanhtrai%10];
 OUTPUT_high(DT);
 OUTPUT_high(VT);
 OUTPUT_low(XT);
 ttt=0;
 }
 }
}
void dem_ben_phai()
{
 if(ttp==0)
 {
 if(dophai>0)
 {
 dophai--;
 led2 = ma7doan[dophai/10];
 led3 = ma7doan[dophai%10];
 OUTPUT_low(Dp);
 OUTPUT_high(Vp);
 OUTPUT_high(Xp);
 }
 else
 {
 dophai=ghdo;
 xanhphai=ghxanh;
 led2 = ma7doan[xanhphai/10];
 led3 = ma7doan[xanhphai%10];
 OUTPUT_high(Dp);
 OUTPUT_high(Vp);
 OUTPUT_low(Xp);
 ttp=1;
 }
 }
 else if(ttp==1)
 {
 if(xanhphai>0)
 {
 xanhphai--;
 led2 = ma7doan[xanhphai/10];
 led3 = ma7doan[xanhphai%10];
 OUTPUT_high(Dp);
 OUTPUT_high(Vp);
 OUTPUT_low(Xp);
 }
 else
 {
 xanhphai=ghxanh;
 vangphai=ghvang;
 led2 = ma7doan[vangphai/10];
 led3 = ma7doan[vangphai%10];
 OUTPUT_high(Dp);
 OUTPUT_low(Vp);
 OUTPUT_high(Xp);
 ttp=2;
 }
 }
 else if(ttp==2)
 {
 if(vangphai>0)
 {
 vangphai--;
 led2 = ma7doan[vangphai/10];
 led3 = ma7doan[vangphai%10];
 OUTPUT_high(Dp);
 OUTPUT_low(Vp);
 OUTPUT_high(Xp);
 }
 else
 {
 vangphai=ghvang;
 dophai=ghdo;
 led2 = ma7doan[dophai/10];
 led3 = ma7doan[dophai%10];
 OUTPUT_low(Dp);
 OUTPUT_high(Vp);
 OUTPUT_high(Xp);
 ttp=0;
 }
 }
}
void kiem_tra_hnt() // ham kiem tra ben trai ********************************************
{
 if(tt1t==0) // kiem tra co nhan duoc tin hieu khong
 {
 if(input(hnt)==0) // neu co
 {
 bdnt=0; // reset tgian
 tt1t=1; // chuyen sang kiem tra khong nhan duoc tin hieu
 }
 }
 else // neu khong nhan duoc tin hieu
 {
 if(input(hnt)==1) // neu co
 {
 if(bdnt<10)// chua duoc 1 giay
 {
 delay_ms(100); //

 ktrt=0;
 }
 else // qua 1 giay
 {
 bdnt=0; // bien dem ngat tam
 ktrt=0;
 b=0;
 }
 tt1t=0;
 a++;
 dem =0;
 }
 }
}

void kiem_tra_hnp() // ham kiem tra ben phai ****************************************
{
 if(tt1p==0)
 {
 if(input(hnp)==0)
 {
 bdnt=0;
 tt1p=1;
 }
 }
 else
 {
 if(input(hnp)==1)
 {
 if(bdnt<10)
 {
 delay_ms(100);

 ktrt=0;
 }
 else
 {
 bdnt=0;
 ktrt=0;
 a=0;
 }
 tt1p=0;
  b++;
  dem=0;
 }
 }
}
VOID MAIN()
{
 SET_TRIS_D(0X00);
 SET_TRIS_A(0X00);
 SET_TRIS_C(0X00);
 SET_TRIS_B(0XF0);
 SET_TRIS_E(0X00);
 output_high(xt);
 output_high(vt);
 output_high(dt);
 output_high(xp);
 output_high(vp);
 output_high(dp);
 led0=led1=led2=led3=0xff;
 hienthi();
  ghdo =val1;  ghvang=2;   ghxanh =ghdo-3;
 DOTRAI=ghdo; XANHTRAI=ghxanh; VANGTRAI=ghvang;
 DOPHAI=ghdo; XANHPHAI=ghxanh; VANGPHAI=ghvang;

 ttt=0;
 ttp=0;
 
 SETUP_TIMER_1(T1_INTERNAL|T1_DIV_BY_8);
 SET_TIMER1(3036);

 ENABLE_INTERRUPTS(GLOBAL);
 ENABLE_INTERRUPTS(INT_TIMER1);
 ktrt=1;
 ktrp=1;
 tt1p=0;
 tt1t=0;
 WHILE(TRUE)
 {
    
  ghxanh=ghdo-3;
 IF(BDN<10) // chua duoc 1s
 {
 HIENTHI();
 if(ttt==2) // den do ben trai
 {
 if(ktrt==1)   kiem_tra_hnt();
 
 }
 else // khi den xanh, vang

 {
 ktrt=1;
 tt1t=0;
 }

 if(ttp==0) // den do ben phai
 {
    if(ktrp==1)kiem_tra_hnp();
 }
 else
 {
 ktrp=1;
 tt1p=0;
 }
 }
 ELSE // du 1 giay
 {
 BDN = BDN - 10;
 dem_ben_trai(); //dem led ben trai
 dem_ben_phai(); //dem led ben phai
 }
  if(a>b)  
  {
  if(ttt==0)   //den do ben trai
  {
  ghdo=val1;
  ghxanh=ghdo-3;
  }
  if(ttp==1)   //den do ben phai
  {
  ghdo=val2;
  ghxanh=ghdo-3; 
  }
  if(dem==2  && a!=b)
{
   dem=0;
   a=b;
}
  }
  
 else if(a<b)
 {
   if(ttt==0)
  {
  ghdo=val2;
  ghxanh=ghdo-3;
  }
  if(ttp==1)
  {
  ghdo=val1;
  ghxanh=ghdo-3;
  }
  if(dem==2  && a!=b)
{
   dem=0;
   a=b;
}
 }
 else if(a==b)
 {
 ghdo =15;
 ghxanh=ghdo-3;
 a=b=0;
 }
if(dem==2  && a!=b)
{
   dem=0;
   a=b;
}
 }
}
