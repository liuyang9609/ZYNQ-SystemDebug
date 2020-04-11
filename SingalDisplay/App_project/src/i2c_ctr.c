#include "sleep.h"
#include "emio_initial.h"


#define CAM_OV5640 0x78

void sccb_start(void)
{
	CLOCK_HIGH();
	DATA_HIGH();
	usleep(10);
	DATA_LOW();
	usleep(10);
	CLOCK_LOW();
	usleep(10);
}

void sccb_end(void)
{
	DATA_LOW();
	usleep(10);
	CLOCK_HIGH();
	usleep(10);
	DATA_HIGH();
	usleep(10);
}

void sccb_sendbyte( unsigned char value )
{
	//��������ת����������������������˳��Ϊ�ȸ�λ�ٵ�λ
	unsigned char  i=0;

	for(i=0; i<8; i++)
	{
		if(value & 0x80 )
			DATA_HIGH();
		else
			DATA_LOW();

		usleep(10);
		CLOCK_HIGH();
		usleep(10);
		CLOCK_LOW();
		usleep(10);
		//DATA_LOW();
		//usleep(10);

		value<<=1;
	}

	//��9λ��Don��t Care
	DATA_LOW();
	usleep(10);
	CLOCK_HIGH();
	usleep(10);
	CLOCK_LOW();
	usleep(10);
}

void sccb_senddata(unsigned char subaddr1,unsigned char subaddr2,unsigned char value)
{
	//3��д��������
	sccb_start();					//����SCCB
	sccb_sendbyte(CAM_OV5640);		//OV6620�豸�ӵ�ַ��д����
	sccb_sendbyte(subaddr1);		//�豸�ڴ��ַ
	sccb_sendbyte(subaddr2);		//�豸�ڴ��ַ
	sccb_sendbyte(value);			//д�����ֽ�
	sccb_end();						//����SCCB

	usleep(2000);
}