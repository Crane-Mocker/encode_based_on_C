//encode_decode system for Windows
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include"otp.h"
#include"caser.h"
#include"rail.h"

HANDLE wOut;//����

void drawBox(SMALL_RECT rc)//���߿򣬵�����936ʱ�߿򻭲�����QAQ
{
	CONSOLE_SCREEN_BUFFER_INFO wInfo;//������Ϣ
	DWORD pointer;
	//COORD position={0,0};
	//wOut=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼�����豸����
	//GetConsoleScreenBufferInfo(wOut,&wInfo);//��ȡ������Ϣ

	char box[6];
	COORD position;

	box[0]=(char)0xc9;//����
	box[1]=(char)0xbf;//����
	box[2]=(char)0xc0;//����
	box[3]=(char)0xd9;//����
	box[4]=(char)0xc4;//��
	box[5]=(char)0xb3;//��

	//���߿�
	//�����ߺ͹ս�
	for(position.X=rc.Left+1;position.Y<rc.Right-1;position.X++)
	{
		position.Y=rc.Top;//�������ı߿�����
		WriteConsoleOutputCharacter(wOut,&box[4],1,position,&pointer);

		if(position.X==rc.Left+1)//���������ϽǴ������ս�
		{
			position.X--;
			WriteConsoleOutputCharacter(wOut,&box[0],1,position,&pointer);
			position.X++;
		}
		if(position.X==rc.Right-2)//���������ϽǴ������ս�
		{
			position.X++;
			WriteConsoleOutputCharacter(wOut,&box[1],1,position,&pointer);
			position.X--;
		}

		position.Y=rc.Bottom;//�������ı߿�����
		WriteConsoleOutputCharacter(wOut,&box[4],1,position,&pointer);

		if(position.X==rc.Left+1)//���������½Ǵ������ս�
		{
			position.X--;
			WriteConsoleOutputCharacter(wOut,&box[2],1,position,&pointer);
			position.X++;
		}
		if(position.X==rc.Right-2)//���������½Ǵ������ս�
		{
			position.X++;
			WriteConsoleOutputCharacter(wOut,&box[3],1,position,&pointer);
			position.X--;
		}

	}

	//������
	for(position.Y=rc.Top+1;position.Y<=rc.Bottom-1;position.Y++)
	{
		position.X=rc.Left;
		WriteConsoleOutputCharacter(wOut,&box[5],1,position,&pointer);
		position.X=rc.Right;
		WriteConsoleOutputCharacter(wOut,&box[5],1,position,&pointer);
	}
}

void dispBox(char *str)//��һ��box
{
	CONSOLE_SCREEN_BUFFER_INFO wInfo;//������Ϣ
	DWORD pointer;
	//COORD position={0,0};
	//wOut=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼�����豸����
	GetConsoleScreenBufferInfo(wOut,&wInfo);//��ȡ������Ϣ

	SMALL_RECT rc;
	WORD att0,att1,att2;
	int i,j=strlen(str);
	//����box��С��λ��,ʹ֮����
	rc.Left=(wInfo.dwSize.X-j)/2-2;
	rc.Top=8;//wInfo.dwSize.Y/2-2;
	rc.Right=rc.Left+j+4;
	rc.Bottom=rc.Top+4;
	//��ɫ&��Ӱ
	att0=BACKGROUND_INTENSITY;
	att1=FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE;
	att2=FOREGROUND_RED | FOREGROUND_INTENSITY;
	COORD positionShadow={rc.Left+1,rc.Top+1},positionText={rc.Left,rc.Top};
	for(i=0;i<5;i++)
	{
		FillConsoleOutputAttribute(wOut,att0,j+4,positionShadow,&pointer);
		positionShadow.Y++;
	}
	for(i=0;i<5;i++)
	{
		FillConsoleOutputAttribute(wOut,att1,j+4,positionText,&pointer);
		positionText.Y++;
	}
	//�ı�
	positionText.X=rc.Left+2;
	positionText.Y=rc.Top+2;
	WriteConsoleOutputCharacter(wOut,str,j,positionText,&pointer);
	//drawBox(rc);
	SetConsoleTextAttribute(wOut,wInfo.wAttributes);//�ָ�ԭ��
}

int main()
{
	CONSOLE_SCREEN_BUFFER_INFO wInfo;//������Ϣ
	//COORD position={0,0};
	wOut=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼�����豸����
	GetConsoleScreenBufferInfo(wOut,&wInfo);//��ȡ������Ϣ

	//ui
	//char src[]="";
	SetConsoleTitle("encode system");
	system("color 70");
	//HRESULT ShowPic(src,wOut);
	//SetConsoleTextAttribute(wOut, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	SetConsoleOutputCP(936);//����ҳ������
	//dispBox("welcome");

	int i=-1;
	printf("Welcome to encode/decode system! Here are 3 options.\n");
	while (i != 0)
	{
		printf("\nplease input your option at first\n
            then you can choose to encode or decode after choosing an option\n");
		printf("1.caser\n2.rail\n3.otp\n");
	    scanf("%d", &i);
	    switch (i)
	    {
	    case 1:caser(); break;
	    case 2:rail(); break;
	    case 3:otp(); break;
	    case 0:break;
	    default:printf("please input again");break;
	    }
	}
	dispBox("��л����ʹ�ã�");
	system("PAUSE");
	CloseHandle(wOut);//�رվ���
	return 0;
}
