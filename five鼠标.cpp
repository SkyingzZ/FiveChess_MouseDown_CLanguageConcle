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
}//移动光标
class background
{
	int x;
	int y;
public:
	showback();
};//背景
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
				cout<<"┳";
			else if(i==y-1)
				cout<<"┻";
			else if(j==0)
				cout<<"┣";
			else if(j==x-1)
				cout<<"┫";
			else if(i%2==1&&j%2==1)
				cout<<"  ";
			else
				cout<<"╋";
		}
			cout<<"\n";
	}	
}//创建背景类函数
class spot
{
public:
	int cx;
	int cy;
	int state;
	showspotbk();//显示点
};//点类

spot::showspotbk()
{
	move(((cx-1)*2+1)*2,(cy-1)*2+1);
	if(state==1)
		cout<<"○";
	else
		cout<<"●";
}
void DispMousePos(COORD pos);
void game()
{
	HANDLE hOut;  
	HANDLE hIn;//创建输入输出设备句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄  
    hIn = GetStdHandle(STD_INPUT_HANDLE); // 获取标准输入设备句柄  

    INPUT_RECORD mouseRec; //定义输入事件结构体 
    DWORD state = 0, res;  //存储读取记录
    COORD pos = {0, 0}; //鼠标的坐标
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
		pos = mouseRec.Event.MouseEvent.dwMousePosition; //获取位置
		move(0,32);
		cout<<"x="<<pos.X<<"\t"<<"y="<<pos.Y;
		move(14,32);
		cout<<"          ";
		if(t==1)
		{
			move(64,30);
			cout<<"黑棋回合";
		}
		else
		{
			move(64,30);
			cout<<"白棋回合";
		}

    //不断对鼠标这个事件进行检测  
        ReadConsoleInput(hIn, &mouseRec, 1, &res);  
        if (mouseRec.EventType == MOUSE_EVENT)//如果当前事件为鼠标事件  
        {   
            pos = mouseRec.Event.MouseEvent.dwMousePosition; //获取位置 
            if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)  
            { //左按键 
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
							cout<<"黑棋胜  ";
						else
							cout<<"白棋胜  ";
					Sleep(3000);
					system("cls");
					CloseHandle(hOut); // 关闭标准输出设备句柄  
					CloseHandle(hIn); // 关闭标准输入设备句柄 
					
					return ;
					}//满足条件 输出胜利信息

				}
			}
	}
}
int main()
{  
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);//隐藏光标
	game();
	return 0;
}