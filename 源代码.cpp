#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include<time.h>
#include <stdlib.h>
#include <math.h>

int cal_sign (int val1, int val2, int count, int level, int time_start); 
void set_background();
void calculate_base(int time_start, int mode);
void moving_str();
int mouse_click();
int select_mode();
void draw_end (int time_start, int count);

void main()
{
	int mode; //mode对应模式1234
	initgraph(640,480); //初始化图形界面
	set_background();  //设置背景
	moving_str();   //进入界面：先显示进入界面以及滚动文字，一定时间后跳转到下一个界面	
	mode = select_mode();//按钮界面选择mode, 放在这里是为了选择模式后才开始运行
	time_t time_start; //开始训练的时间
	time_start = time(NULL); 
	calculate_base(time_start, mode); //计算过程：选择模式——计算
	
	getch(); //任意按键
    closegraph();  //关闭界面
}

void set_background()  //设置背景
{
	  for(int i = 0; i < 640; i++)//设置渐变紫色背景
	{
		setlinecolor(RGB(100,100,100+int(i/640.0*155)));  //渐变色
		line(i, 0, i, 479);}

	  HWND hwnd = GetHWnd();  //获取窗口句柄并设置窗口标题文字
	  SetWindowText(hwnd, "给小学生的口算系统");
}

void moving_str()  //移动的文字和欢迎界面
{
	settextcolor(RGB(128,255,128));
	settextstyle(50, 0, _T("隶书"));
	setbkmode(TRANSPARENT);
	outtextxy(270,100,"作者：");
	IMAGE photo;  //显示照片
	loadimage (&photo, "个人照缩小.jpg");
	putimage(270,170,&photo);

	TCHAR str[] = _T("学好数学，从口算开始！数学魅力妙妙妙！"); //待移动的字符串
	int w = textwidth(str); //存储文字对象的宽度高度
	int h = textheight(str);
	IMAGE temp;//存储临时背景图像

	settextstyle(30, 0, _T("隶书"));  //设置下方滚动文字的制式，放在这里才有效
	settextcolor(WHITE);
	setbkmode(TRANSPARENT); //透明色，是为不遮挡背景

	for (int i=0; i<100; i++)  
	{
		getimage(&temp, i, 400, w, h); //暂时存储目标位置的背景
		//settextstyle(50, 0, _T("楷体")); //输出文字 //这句话不能要的
		outtextxy(i, 400, str);
		Sleep(30);
		putimage(i, 400, &temp); //重新加载回背景
	}
	cleardevice();
	set_background();

}

int select_mode()   //选择计算的模式
{
	int mode;
	setfillcolor(YELLOW);   //画底板矩形
	fillrectangle(100, 100, 200, 150);
	fillrectangle(100, 200, 200, 250);
	fillrectangle(100, 300, 200, 350);
	fillrectangle(100, 400, 200, 450);

	settextcolor(YELLOW);            //文字
	settextstyle(50,0,_T("方正舒体"));
	RECT r1 = {200, 0, 450, 80};
	drawtext(_T("模式选择"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextcolor(RED);
	settextstyle(30,0,_T("方正舒体"));
	RECT r2 = {100, 100, 200, 150};
	drawtext(_T("童生"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = {100, 200, 200, 250};
	drawtext(_T("秀才"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = {100, 300, 200, 350};
	drawtext(_T("举人"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = {100, 400, 200, 450};
	drawtext(_T("进士"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(YELLOW);
	settextstyle(20,0,_T("宋体"));
	outtextxy(220, 120, "加减法，从1位数到2位数，得分满20晋级");
	outtextxy(220, 220, "加减乘法，从1位数到2位数，得分满20晋级");
	outtextxy(220, 300, "加减乘除法，上限为2位数，得分满20晋级");
	outtextxy(220, 330, "除法能整除");
	outtextxy(220, 400, "加减乘除法，上限为2位数，得分满20晋级");
	outtextxy(220, 430, "除法若商出现小数，则保留一位小数");

	MOUSEMSG m;       //鼠标操作
	while(true)        //鼠标操作的while模式
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)  //左键按下
		{
			if (m.x>=100 && m.x<=200 && m.y>=100 && m.y<=150)
			{
				mode = 1;
				break;
			}
			if (m.x>=100 && m.x<=200 && m.y>=200 && m.y<=250)
			{
				mode = 2;
				break;
			}
			if (m.x>=100 && m.x<=200 && m.y>=300 && m.y<=350)
			{
				mode = 3;
				break;
			}
			if (m.x>=100 && m.x<=200 && m.y>=400 && m.y<=450)
			{
				mode = 4;
				break;
			}

		}
	}
	cleardevice();
	set_background();
	return mode;
}

void calculate_base(int time_start, int mode)
{
	int flag = 1, count=0, levelgrade[4][2]={1,2,3,4,5,6,7,8}; //count是得分,levelgrade是算术级别

	while(flag)  //flag==1时进行循环
	{
		int val1, val2;  //算式左方的两个值
		float input;  //存放鼠标按键最终确认得数
		srand ((unsigned)time(NULL)); //随机数种子随机生成数 <time.h>
		
		switch(mode)
		{
		case 1:      //童生、秀才级别的都是满20分晋级（从1位数到2位数）;不满20分自动降级了
		if(count < 20)
		{
		val1 = rand()%10;  //生成1位数随机数
		val2 = rand()%10;
		count =  cal_sign(val1, val2, count,levelgrade[0][0], time_start);
		}
		
		if(count>=20)  
		{
		val1 = rand()%100;//生成2位数随机数
		val2 = rand()%100;
		count =  cal_sign(val1, val2, count,levelgrade[0][1], time_start);
		}
		break;

		case 2:
		if(count < 20)
		{
		val1 = rand()%10;
		val2 = rand()%10;
		count =  cal_sign(val1, val2, count,levelgrade[1][0], time_start);
		}
		
		if(count>=20)
		{
		val1 = rand()%100;
		val2 = rand()%100;
		count =  cal_sign(val1, val2, count,levelgrade[1][1], time_start);
		}
		break;

		case 3: //举人、进士级别都是满20分晋级，从只有加减法到四则运算
		val1 = rand()%100;
		val2 = rand()%100;
		if(count < 20)
		{
		count =  cal_sign(val1, val2, count,levelgrade[2][0], time_start);
		}
		
		if(count>=20)
		{
		count =  cal_sign(val1, val2, count,levelgrade[2][1], time_start);
		}
		break;

		case 4:
		val1 = rand()%100;
		val2 = rand()%100;
		if(count < 20) 
		{
		count =  cal_sign(val1, val2, count,levelgrade[3][0], time_start);
		}
	

		if(count>=20)
		{
		count =  cal_sign(val1, val2, count,levelgrade[3][1], time_start);
		}
		break; //注意位置

		default:
			exit(0);
		}
	}
}

int cal_sign (int val1, int val2, int count, int level, int time_start) //算式生成及得数检验和计分过程，返回得分
{
	int a, sign, temp, tag; //temp是临时值，用作交换  tag标志除法算法级别：1是出现题目一定整除，2是可能不整除，保留一位小数
	float final, input; //final算式正确结果，input输入最终结果
	srand((unsigned)time(NULL)); //随机数种子
	switch (level)   //选择运算符号级别：%2加减，%3加减乘，%4加减乘除
	{
	case 1:
		sign = rand()%2+1;break;
	case 2:
		sign = rand()%2+1;break;
	case 3:
		sign = rand()%3+1;break;
	case 4:
		sign = rand()%3+1;break;
	case 5:
		sign = rand()%2+1;break;  
	case 6:
		sign = rand()%4+1; tag = 1; break;
	case 7:
		sign = rand()%2+1;break;
	case 8:
		sign = rand()%4+1; tag = 2; break;
	default:exit(0);
	}
	
	switch (sign)
	{
	    case 1: //加法
		TCHAR s1[5], s2[5], s3[5]; //把数字转换成字符串便于在绘图模式下输出
		_stprintf(s1, _T("%d"), val1);
		_stprintf(s2, _T("%d"), val2);
		_stprintf(s3, _T("%d"), count);

		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);   //画算式和得分
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,s1);
		outtextxy(150,100,"+");
		outtextxy(200,100,s2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		outtextxy(120,10,s3);

		final = val1 + val2;
		input = mouse_click();  //鼠标按键最终确认得数返还给input

		while(input!= final)//如果做错就继续写直到对为止
		{
			if (input == -9999) //鼠标点了结束按钮
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //如果是真的算错了，那就扣一分；注意9999是清除操作的标志数
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //在清屏后立即重新绘制背景
		
		if (count < 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,s1);
		outtextxy(150,100,"+");
		outtextxy(200,100,s2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		_stprintf(s3, _T("%d"), count);  //count有改变，所以需要赋给s3
		outtextxy(120,10,s3);
		input = mouse_click();
		}
		cleardevice();
		set_background();  //在清屏后立即重新绘制背景
          break;   

		case 2:  //减法
			//此时要求减法不出现负数,出现就对换val1,val2
			final = val1 - val2;
				if(final<0)
				{
					temp = val1;
					val1 = val2;
					val2 = temp;
				}

		TCHAR m1[5], m2[5], m3[5];
		_stprintf(m1, _T("%d"), val1);
		_stprintf(m2, _T("%d"), val2);
		_stprintf(m3, _T("%d"), count);

		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,m1);
		outtextxy(150,100,"-");
		outtextxy(200,100,m2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		outtextxy(120,10,m3);
		final = val1 - val2;
		input = mouse_click();
		
		
		while(input!= final)//如果做错就继续写直到对为止
		{
			if (input == -9999) //鼠标点了结束按钮
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //如果是真的算错了，那就扣一分；注意9999是清除操作的标志数
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //在清屏后立即重新绘制背景
		
		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,m1);
		outtextxy(150,100,"-");
		outtextxy(200,100,m2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		_stprintf(m3, _T("%d"), count);  //count有改变，所以需要赋给m3
		outtextxy(120,10,m3);
		input = mouse_click();
		}
		cleardevice();
		set_background();  //在清屏后立即重新绘制背景
		
		break;

		case 3:  //乘法
		TCHAR w1[5], w2[5], w3[5];
		_stprintf(w1, _T("%d"), val1);
		_stprintf(w2, _T("%d"), val2);
		_stprintf(w3, _T("%d"), count);

		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,w1);
		outtextxy(150,100,"X");
		outtextxy(200,100,w2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		outtextxy(120,10,w3);
		final = val1 * val2;
		input = mouse_click();
		
		while(input!= final)//如果做错就继续写直到对为止
		{
			if (input == -9999) //鼠标点了结束按钮
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //如果是真的算错了，那就扣一分；注意9999是清除操作的标志数
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //在清屏后立即重新绘制背景
		
		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,w1);
		outtextxy(150,100,"X");
		outtextxy(200,100,w2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		_stprintf(w3, _T("%d"), count);  //count有改变，所以需要赋给w3
		outtextxy(120,10,w3);
		input = mouse_click();
		}
		cleardevice();
		set_background();
		break;

		case 4:  //除法
			//把整数转成浮点数才能精确计算
			if(tag == 2)
			{
			while(val2 == 0) //除数不能为0
			{
				val2 = rand()%100;
			}
			}
			if (tag == 1)
			{
				while(val1%val2 !=0) //不能整除则重新生成随机数
				{
					
					val1 = rand()%100;
					val2 = rand()%100;
					while(val2 == 0) //除数不能为0
			{
				val2 = rand()%100;
			}
				}
			}

		TCHAR d1[5], d2[5], d3[5];
		_stprintf(d1, _T("%d"), val1);
		_stprintf(d2, _T("%d"), val2);
		_stprintf(d3, _T("%d"), count);

		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,d1);
		outtextxy(150,100,"/");
		outtextxy(200,100,d2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		outtextxy(120,10,d3);
		final = (float(val1) / float(val2));  //转换成浮点数才是精确值
		temp = (int(final)*10) + int((final-int(final))*10+0.5); //目的：保留一位小数，四舍五入（得到乘十倍的数）
		if(tag == 1)
		{
			input = mouse_click(); //整除了，不会出现小数点
		}
		else if (tag == 2)
		{
			if (val1%val2 != 0) //如果正确答案是有小数的（不是整除）,按照用户一般行为，用户会输入小数点
			{
		input = mouse_click() * 0.1;  //除法：考虑小数点留一位，特殊操作
			}
			else
			{
				input = mouse_click(); //整除了，不会出现小数点
			}
		}

		while(fabs(input- temp*0.1)>=1e-6)//如果做错就继续写直到对为止,input浮点数存储可能会有精度缺失
		{
			if (input == -9999) //鼠标点了结束按钮
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //如果是真的算错了，那就扣一分；注意9999是清除操作的标志数
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //在清屏后立即重新绘制背景
		
		if (count < 20) //使用count判断而不使用level判断：因为count是实时反映分数的
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"初级");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //显示当前级别
		settextstyle(50, 0, _T("楷体"));
		outtextxy(200,10,"高级");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,d1);
		outtextxy(150,100,"/");
		outtextxy(200,100,d2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(30,10,"得分：");
		_stprintf(d3, _T("%d"), count);  //count有改变，所以需要赋给d3
		outtextxy(120,10,d3);
		if(tag == 1)
		{
			input = mouse_click(); //整除了，不会出现小数点
		}
		else if (tag == 2)
		{
			if (val1%val2 != 0) //如果正确答案是有小数的（不是整除）,按照用户一般行为，用户会输入小数点
			{
		input = mouse_click() * 0.1;  //除法：考虑小数点留一位，特殊操作
			}
			else
			{
				input = mouse_click(); //整除了，不会出现小数点
			}
		}}
		cleardevice();
		set_background();
		break;

		default:printf("出错！");exit(0);
	}
	 
count = count+2; //答对加2分
	return count;
}


int mouse_click()  //除法：在母步骤再*0.1 因为此函数无法返回float
{
	int flag = 1, draw = 1;//flag点击循环标记, draw是否显示数字
	int i, j,count=0, value = 0;
	char c;
	char cal_show[4][3];   //屏幕键盘绘制
	TCHAR s1[5];
	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
		{
			cal_show[i][j] = '0'+ (3*j + (i+1));
		}
	cal_show[3][0] = 'X';
	cal_show[3][1] = '.';
	cal_show[3][2] = '0';

	setfillcolor(YELLOW);
	for (i=0; i<4; i++)
		for (j=0; j<3; j++)
	{
		fillrectangle(50+i*65, 250+j*80,100+i*65, 300+j*80);
		settextcolor(RED);
		settextstyle(40, 0, _T("宋体"));
		outtextxy( 50+15+i*65,250+10+j*80, cal_show[i][j]);
	}

	fillrectangle(400,300,500,350); //确认按钮
	settextcolor(RED);
	settextstyle(50, 0, _T("楷体"));
	outtextxy(400,300,"确认");

	setfillcolor(RGB(100,100,100));
	fillrectangle(500,400,600,450); //结束按钮
	settextcolor(BLACK);
	settextstyle(50, 0, _T("楷体"));
	outtextxy(500,400,"结束");

	MOUSEMSG m;
	
		while(flag == 1)
	{
		draw = 1;  //标识：draw == 0 时重绘界面但是不扣分（就是清除得数）
		m = GetMouseMsg();  //count++;不能放在这里
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:	
				if(m.x>=50 && m.x<=100 && m.y>=250 && m.y<=300)
		{
			c = '1';
			count++; //数：这是第几次按键
			value = value*10+1;
		}
			else if (m.x>=50+65 && m.x<=100+65 && m.y>=250 && m.y<=300)
			{
				c = '2';
				count++; //数：这是第几次按键
				value = value*10+2;
			}
			 else if (m.x>=50+65*2 && m.x<=100+65*2 && m.y>=250 && m.y<=300)
			{
				c = '3';
				count++; //数：这是第几次按键
				value = value*10+3;
			} 
			else if (m.x>=50 && m.x<=100 && m.y>=250+80 && m.y<=300+80)
			{
				c = '4';
				count++; //数：这是第几次按键
				value = value*10+4;
			}
			else if (m.x>=50+65 && m.x<=100+65 && m.y>=250+80 && m.y<=300+80)
			{
				c = '5';
				count++; //数：这是第几次按键
				value = value*10+5;
			}
			else if (m.x>=50+65*2 && m.x<=100+65*2 && m.y>=250+80 && m.y<=300+80)
			{
				c = '6';
				count++; //数：这是第几次按键
				value = value*10+6;
			} 
			else if (m.x>=50 && m.x<=100 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '7';
				count++; //数：这是第几次按键
				value = value*10+7;
			}
			else if (m.x>=50+65 && m.x<=100+65 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '8';
				count++; //数：这是第几次按键
				value = value*10+8;
			}
			else if (m.x>=50+65*2 && m.x<=100+65*2 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '9';
				count++; //数：这是第几次按键
				value = value*10+9;
			} 
			else if (m.x>=50+65*3 && m.x<=100+65*3 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '0';
				count++; //数：这是第几次按键
				value = value*10+0;
			}
			else if (m.x>=50+65*3 && m.x<=100+65*3 && m.y>=250 && m.y<=300)
			{
				draw = 0;
			
				value = 9999; //为了跟真正结果为0区别开来；本次测试不会出现9999的真正结果
			}
			else if (m.x>=50+65*3 && m.x<=100+65*3 && m.y>=250+80 && m.y<=300+80) //出现小数点只有在tag==2情况
			{
				c = '.';
				count++; //数：这是第几次按键   
				
			}
			else if (m.x>=400 && m.x<=500 && m.y>=300 && m.y<=350)//确认键确认
			{
				flag = 0;
			} 
			else if (m.x>=500 && m.x<=600 && m.y>=400 && m.y<=450) //结束键结束
			{
				draw = 0;

				value = -9999; //为了跟真正结果为0区别开来；本次测试不会出现-9999的真正结果；-9999是标记数
			}
			else  //点了界面其它空白处
			{
				draw = 0;
			
				value = 9999; //为了跟真正结果为0区别开来；本次测试不会出现9999的真正结果；9999是标记数
			}

			if (flag == 1 && draw == 1)  //按下什么数字，即时在屏幕上输出什么数字
			{		
			settextcolor(GREEN);
		settextstyle(100, 0, _T("宋体"));
		setbkmode (TRANSPARENT);
		outtextxy(350+50*(count-1),100,c );
			}
			else if (flag == 1 && draw == 0)
			{
				flag = 0;  
			}
				break;

			case WM_RBUTTONDBLCLK:
				exit(0);				// 双击鼠标右键退出程序
		}
		}		
return value;
}

void draw_end (int time_start, int count)
{
	time_t time_end; //结束训练的时间
	time_end = time(NULL);
	int total_time = time_end - time_start;

	set_background();  //设置背景
	TCHAR x1[5],x2[5];
	_stprintf(x1, _T("%d"), total_time);
	_stprintf(x2, _T("%d"), count);
	settextcolor(RGB(0,200,200));  
	settextstyle(60, 0, _T("楷体"));
	outtextxy(10,100,"用时：");
	outtextxy(300,100,x1);
	outtextxy(500,100,"秒");
	outtextxy(10,300,"得分：");
	outtextxy(300,300,x2);
	outtextxy(500,300,"分");

	getch();   //按任意键结束
	closegraph();
}

