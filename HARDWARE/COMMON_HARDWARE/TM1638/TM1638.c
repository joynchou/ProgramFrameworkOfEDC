/***********************************************************
* ��֯���ƣ�
* �ļ�����: TM1638.c
* ����:  ��־ǿ
* �汾: v1.0
* ����:
* ����: ������ʼ������غ���
* ��Ҫ�������书�� : 

* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* ��־ǿ
***********************************************************/
#include "TM1638.H"

unsigned char data DisBuffer[8]={0,0,0,0,0,0,0,0};    /*��ʾ������*/	//�����������ʾ��ֵ
unsigned char code tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x40,0xef};

/*typedef struct
{
	
}Tm1638Button;*/

/**********************************************
 *������void setTM1638Write(unsigned char	DATA)
 *������д����
 *���룺unsigned char
 *�������
 *����ֵ��void
 *����˵����
 **********************************************/
void setTM1638Write(unsigned char	DATA)			//д���ݺ���
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		TM1638_CLK=0;
		delay_us(1);
		if(DATA&0X01)
			TM1638_DIO=1;
		else
			TM1638_DIO=0;
		DATA>>=1;
		TM1638_CLK=1;
		delay_us(1);
	}
}

/**********************************************
 *������unsigned char getTM1638Read(void)
 *��������ȡ����
 *���룺void
 *�����unsigned char
 *����ֵ��void
 *����˵����
 **********************************************/
unsigned char getTM1638Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
	TM1638_DIO=1;	//����Ϊ����
	for(i=0;i<8;i++)
	{
		temp>>=1;
		TM1638_CLK=0;
		delay_us(1);
		if(TM1638_DIO)
			temp|=0x80;
		TM1638_CLK=1;
		delay_us(1);
	}
	return temp;
}		

/**********************************************
 *������void setTM1638COM(unsigned char cmd)
 *��������������
 *���룺unsigned char
 *�������
 *����ֵ��void
 *����˵����
 **********************************************/
void setTM1638COM(unsigned char cmd)		//����������
{
	TM1638_STB=0;
	delay_us(1);
	setTM1638Write(cmd);
	TM1638_STB=1;
	delay_us(1);
}

/**********************************************
 *������unsgined char getButtonNum(void)
 *���������ذ��µİ������
 *���룺void
 *�����unsigned char
 *����ֵ�����ذ��µİ������
 *����˵����
 **********************************************/
unsigned char getButtonNum(void)
{
	unsigned char c[4],i,key_value=0;
	TM1638_STB=0;
	setTM1638Write(0x42);
	delay_ms(1);
	for(i=0;i<4;i++)
		c[i]=getTM1638Read();
	TM1638_STB=1;					//4���ֽ����ݺϳ�һ���ֽ�
	if(c[0]==0x04) key_value=1;
	else if(c[0]==0x40) key_value=2;
	else if(c[1]==0x04) key_value=3;
	else if(c[1]==0x40) key_value=4;
	else if(c[2]==0x04) key_value=5;
	else if(c[2]==0x40) key_value=6;
	else if(c[3]==0x04) key_value=7;
	else if(c[3]==0x40) key_value=8;
	else if(c[0]==0x02) key_value=9;
	else if(c[0]==0x20) key_value=10;
	else if(c[1]==0x02) key_value=11;
	else if(c[1]==0x20) key_value=12;
	else if(c[2]==0x02) key_value=13;
	else if(c[2]==0x20) key_value=14;
	else if(c[3]==0x02) key_value=15;
	else if(c[3]==0x20) key_value=16;
	else return 0;
	delay_ms(1);
	return (key_value);
}

/**********************************************
 *������void Init_TM1638(void)
 *������TM1638��ʼ��
 *���룺
 *�������
 *����ֵ��void
 *����˵����
 **********************************************/
void Init_TM1638(void)
{
	unsigned char i;
	setTM1638COM(0x8a);//����
	setTM1638COM(0x8a);//����
	setTM1638COM(0x40); //д ��������
	TM1638_STB=0;
	setTM1638Write(0xc0);		//д��ַ����
	for(i=0;i<16;i++)	
	setTM1638Write(0xff);
	TM1638_STB=1;
}

/**********************************************
 *������Inti_Str_Motor(float,float,float,unsigned int)
 *�������Զ�����г�ʼ��
 *���룺
 *1.plΪ��Ϳɽ��յ������ȣ���λΪms                  
 *2.phΪ��߿ɽ��յ������ȣ���λΪms                 
 *3.nΪ����ּ�
 *�������
 *����ֵ��void
 *����˵����
 **********************************************/
//unsigned char ButtonNum(void)
//{		
//   	unsigned char key_value;
//LedDisplay(1,3,7,0,2,1,0,2);
//	delay_ms(1000);
//	delay_ms(250);
//	delay_ms(250);
//	delay_ms(250);
//	delay_ms(250);
//	
//   while(1)
//   {
//	key_value=getButtonNum();
//	switch (key_value) 
//	{ 
//		case 1: 
//		TM1638LedDisplay(0,0,0,0,0,0,0,1); 
//		break; 
//		case 2 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,2);
//		break; 
//		case 3 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,3);
//		break; 
//		case 4 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,4);
//		break; 
//		case 5 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,5);
//		break; 
//		case 6 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,6);
//		break;  
//		case 7 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,7);
//		break; 
//		case 8 : 
//		TM1638LedDisplay(0,0,0,0,0,0,0,8);
//		break;  
//		case 9: 
//		TM1638LedDisplay(0,0,0,0,0,0,0,9); 
//		break; 
//		case 10 : 
//		TM1638LedDisplay(0,0,0,0,0,0,1,0);
//		break; 
//		case 11 : 
//		TM1638LedDisplay(0,0,0,0,0,0,1,1);
//		break; 
//		case 12 : 
//		TM1638LedDisplay(0,0,0,0,0,0,1,2);
//		break; 
//		case 13 : 
//		TM1638LedDisplay(0,0,0,0,0,0,1,3);
//		break; 
//		case 14 : 
//		TM1638LedDisplay(0,0,0,0,0,0,1,4);
//		break;  
//		case 15: 
//		TM1638LedDisplay(0,0,0,0,0,0,1,5);
//		break; 
//		case 16 : 
//		TM1638LedDisplay(0,0,0,0,0,0,1,6);
//		break;  
//		default : 
//		break;//TM1638LedDisplay(0,0,0,0,0,0,0,0); 
//	}
//	return key_value;
// }
//}

/**********************************************
 *������void TM1638LedDisplay(unsigned char ddata0,unsigned char ddata1,unsigned char ddata2,unsigned char ddata3,
               unsigned char ddata4,unsigned char ddata5,unsigned char ddata6,unsigned char ddata7)
 *������LED��ʾ
 *���룺�Ӹߵ�������������ֵ��ʹLED����ܴӸߵ���������ʾ
 *�������
 *����ֵ��void
 *����˵����
 **********************************************/
void TM1638LedDisplay(unsigned char ddata0,unsigned char ddata1,unsigned char ddata2,unsigned char ddata3,
               unsigned char ddata4,unsigned char ddata5,unsigned char ddata6,unsigned char ddata7)

{
	unsigned char  writedata0,writedata1,writedata2,writedata3,writedata4,writedata5,writedata6,writedata7;
	unsigned char  data0,data1,data2,data3,data4,data5,data6,data7;
	data0=ddata7;
	data1=ddata6;
	data2=ddata5;
	data3=ddata4;
	data4=ddata3;
	data5=ddata2;
	data6=ddata1;
	data7=ddata0;

	writedata0=(tab[data0]&0x01)+((tab[data1]&0x01)<<1)+((tab[data2]&0x01)<<2)+((tab[data3]&0x01)<<3)+((tab[data4]&0x01)<<4)
		+((tab[data5]&0x01)<<5)+((tab[data6]&0x01)<<6)+((tab[data7]&0x01)<<7);

	writedata1=((tab[data0]&0x02)>>1)+((tab[data1]&0x02))+((tab[data2]&0x02)<<1)+((tab[data3]&0x02)<<2)+((tab[data4]&0x02)<<3)
		+((tab[data5]&0x02)<<4)+((tab[data6]&0x02)<<5)+((tab[data7]&0x02)<<6);

	writedata2=((tab[data0]&0x04)>>2)+((tab[data1]&0x04)>>1)+((tab[data2]&0x04))+((tab[data3]&0x04)<<1)+((tab[data4]&0x04)<<2)
		+((tab[data5]&0x04)<<3)+((tab[data6]&0x04)<<4)+((tab[data7]&0x04)<<5);

	writedata3=((tab[data0]&0x08)>>3)+((tab[data1]&0x08)>>2)+((tab[data2]&0x08)>>1)+((tab[data3]&0x08))+((tab[data4]&0x08)<<1)
		+((tab[data5]&0x08)<<2)+((tab[data6]&0x08)<<3)+((tab[data7]&0x08)<<4);

	writedata4=((tab[data0]&0x10)>>4)+((tab[data1]&0x10)>>3)+((tab[data2]&0x10)>>2)+((tab[data3]&0x10)>>1)+((tab[data4]&0x10))
		+((tab[data5]&0x10)<<1)+((tab[data6]&0x10)<<2)+((tab[data7]&0x10)<<3);

	writedata5=((tab[data0]&0x20)>>5)+((tab[data1]&0x20)>>4)+((tab[data2]&0x20)>>3)+((tab[data3]&0x20)>>2)+((tab[data4]&0x20)>>1)
		+((tab[data5]&0x20))+((tab[data6]&0x20)<<1)+((tab[data7]&0x20)<<2);

	writedata6=((tab[data0]&0x40)>>6)+((tab[data1]&0x40)>>5)+((tab[data2]&0x40)>>4)+((tab[data3]&0x40)>>3)+((tab[data4]&0x40)>>2)
		+((tab[data5]&0x40)>>1)+((tab[data6]&0x40))+((tab[data7]&0x40)<<1);

	writedata7=((tab[data0]&0x80)>>7)+((tab[data1]&0x80)>>6)+((tab[data2]&0x80)>>5)+((tab[data3]&0x80)>>4)+((tab[data4]&0x80)>>3)
		+((tab[data5]&0x80)>>2)+((tab[data6]&0x80)>>1)+((tab[data7]&0x80));

	setTM1638COM(0x8a);//����
	setTM1638COM(0x40); //д��������
	TM1638_STB=0;
	setTM1638Write(0xc0);		//д��ַ����
	
	setTM1638Write(writedata0);
	setTM1638Write(0x80);
	setTM1638Write(writedata1);
	setTM1638Write(0x00);
	setTM1638Write(writedata2);
	setTM1638Write(0x00);
	setTM1638Write(writedata3);
	setTM1638Write(0x00);
	setTM1638Write(writedata4);
	setTM1638Write(0x00);
	setTM1638Write(writedata5);
	setTM1638Write(0x00);
	setTM1638Write(writedata6);
	setTM1638Write(0x00);
	setTM1638Write(writedata7);
	setTM1638Write(0x00);

	TM1638_STB=1;


}

/**********************************************
 *������void CloseTM1638Display(void)
 *�������ر���Ļ
 *���룺void
 *�������
 *����ֵ��void
 *����˵����
 **********************************************/
void CloseTM1638Display(void)
{
	setTM1638COM(0x80);
}