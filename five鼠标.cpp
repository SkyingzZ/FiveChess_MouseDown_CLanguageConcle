#include<iostream>
#include<windows.h>  
using namespace std;
void move(int x,int y)
{
	HANDLE hout;
	COORD coord;	
	coord.X=x;
	coord.Y=y;	
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
}//�ƶ����
class background
{
	int x;
	int y;
public:
	showback();
};//����
background::showback()
{
	int i;
	int j;
	x=31;
	y=31;
	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			if(i==0)
				cout<<"��";
			else if(i==y-1)
				cout<<"��";
			else if(j==0)
				cout<<"��";
			else if(j==x-1)
				cout<<"��";
			else if(i%2==1&&j%2==1)
				cout<<"  ";
			else
				cout<<"��";
		}
			cout<<"\n";
	}	
}//���������ຯ��
class spot
{
public:
	int cx;
	int cy;
	int state;
	showspotbk();//��ʾ��
};//����

spot::showspotbk()
{
	move(((cx-1)*2+1)*2,(cy-1)*2+1);
	if(state==1)
		cout<<"��";
	else
		cout<<"��";
}
void DispMousePos(COORD pos);
void game()
{
	HANDLE hOut;  
	HANDLE hIn;//������������豸���
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���  
    hIn = GetStdHandle(STD_INPUT_HANDLE); // ��ȡ��׼�����豸���  

    INPUT_RECORD mouseRec; //���������¼��ṹ�� 
    DWORD state = 0, res;  //�洢��ȡ��¼
    COORD pos = {0, 0}; //��������
	int t=1;
	background bg;
	bg.showback();
	spot st[15][15];
	register int i,j;
	for(i=1;i<=15;i++)
	{
		for(j=1;j<=15;j++)
		{
			st[i-1][j-1].cx=i;
			st[i-1][j-1].cy=j;
			st[i-1][j-1].state=0;
		}
	}
	while(1)
	{
		pos = mouseRec.Event.MouseEvent.dwMousePosition; //��ȡλ��
		move(0,32);
		cout<<"x="<<pos.X<<"\t"<<"y="<<pos.Y;
		move(14,32);
		cout<<"          ";
		if(t==1)
		{
			move(64,30);
			cout<<"����غ�";
		}
		else
		{
			move(64,30);
			cout<<"����غ�";
		}

    //���϶��������¼����м��  
        ReadConsoleInput(hIn, &mouseRec, 1, &res);  
        if (mouseRec.EventType == MOUSE_EVENT)//�����ǰ�¼�Ϊ����¼�  
        {   
            pos = mouseRec.Event.MouseEvent.dwMousePosition; //��ȡλ�� 
            if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)  
            { //�󰴼� 
				if(pos.X<62&&pos.Y<31)
				{
					i=((pos.X/2)-1)/2;
					j=(pos.Y-1)/2;
					if(st[i][j].state==0)
					{
						st[i][j].state=t;
						if(t==1)
							t=2;
						else
							t=1;
					st[i][j].showspotbk();
					}
				}
			}
        }  
			register int i1,j1;
			for(i1=2;i1<13;i1++)
			{
				for(j1=2;j1<13;j1++)
				{
					if(st[i1][j1].state!=0&&((st[i1][j1].state==st[i1-1][j1].state&&st[i1][j1].state==st[i1-2][j1].state&&st[i1][j1].state==st[i1+1][j1].state&&st[i1][j1].state==st[i1+2][j1].state)||
					(st[i1][j1].state==st[i1][j1-1].state&&st[i1][j1].state==st[i1][j1-2].state&&st[i1][j1].state==st[i1][j1+1].state&&st[i1][j1].state==st[i1][j1+2].state)||
					(st[i1][j1].state==st[i1-1][j1-1].state&&st[i1][j1].state==st[i1-2][j1-2].state&&st[i1][j1].state==st[i1+1][j1+1].state&&st[i1][j1].state==st[i1+2][j1+2].state)||
					(st[i1][j1].state==st[i1-1][j1+1].state&&st[i1][j1].state==st[i1-2][j1+2].state&&st[i1][j1].state==st[i1+1][j1-1].state&&st[i1][j1].state==st[i1+2][j1-2].state)))
					{
						move(64,30);
						if(st[i1][j1].state==1)
							cout<<"����ʤ  ";
						else
							cout<<"����ʤ  ";
					Sleep(3000);
					system("cls");
					CloseHandle(hOut); // �رձ�׼����豸���  
					CloseHandle(hIn); // �رձ�׼�����豸��� 
					
					return ;
					}//�������� ���ʤ����Ϣ

				}
			}
	}
}
int main()
{  
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);//���ع��
	game();
	return 0;
}