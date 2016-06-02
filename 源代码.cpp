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
	int mode; //mode��Ӧģʽ1234
	initgraph(640,480); //��ʼ��ͼ�ν���
	set_background();  //���ñ���
	moving_str();   //������棺����ʾ��������Լ��������֣�һ��ʱ�����ת����һ������	
	mode = select_mode();//��ť����ѡ��mode, ����������Ϊ��ѡ��ģʽ��ſ�ʼ����
	time_t time_start; //��ʼѵ����ʱ��
	time_start = time(NULL); 
	calculate_base(time_start, mode); //������̣�ѡ��ģʽ��������
	
	getch(); //���ⰴ��
    closegraph();  //�رս���
}

void set_background()  //���ñ���
{
	  for(int i = 0; i < 640; i++)//���ý�����ɫ����
	{
		setlinecolor(RGB(100,100,100+int(i/640.0*155)));  //����ɫ
		line(i, 0, i, 479);}

	  HWND hwnd = GetHWnd();  //��ȡ���ھ�������ô��ڱ�������
	  SetWindowText(hwnd, "��Сѧ���Ŀ���ϵͳ");
}

void moving_str()  //�ƶ������ֺͻ�ӭ����
{
	settextcolor(RGB(128,255,128));
	settextstyle(50, 0, _T("����"));
	setbkmode(TRANSPARENT);
	outtextxy(270,100,"���ߣ�");
	IMAGE photo;  //��ʾ��Ƭ
	loadimage (&photo, "��������С.jpg");
	putimage(270,170,&photo);

	TCHAR str[] = _T("ѧ����ѧ���ӿ��㿪ʼ����ѧ���������"); //���ƶ����ַ���
	int w = textwidth(str); //�洢���ֶ���Ŀ�ȸ߶�
	int h = textheight(str);
	IMAGE temp;//�洢��ʱ����ͼ��

	settextstyle(30, 0, _T("����"));  //�����·��������ֵ���ʽ�������������Ч
	settextcolor(WHITE);
	setbkmode(TRANSPARENT); //͸��ɫ����Ϊ���ڵ�����

	for (int i=0; i<100; i++)  
	{
		getimage(&temp, i, 400, w, h); //��ʱ�洢Ŀ��λ�õı���
		//settextstyle(50, 0, _T("����")); //������� //��仰����Ҫ��
		outtextxy(i, 400, str);
		Sleep(30);
		putimage(i, 400, &temp); //���¼��ػر���
	}
	cleardevice();
	set_background();

}

int select_mode()   //ѡ������ģʽ
{
	int mode;
	setfillcolor(YELLOW);   //���װ����
	fillrectangle(100, 100, 200, 150);
	fillrectangle(100, 200, 200, 250);
	fillrectangle(100, 300, 200, 350);
	fillrectangle(100, 400, 200, 450);

	settextcolor(YELLOW);            //����
	settextstyle(50,0,_T("��������"));
	RECT r1 = {200, 0, 450, 80};
	drawtext(_T("ģʽѡ��"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextcolor(RED);
	settextstyle(30,0,_T("��������"));
	RECT r2 = {100, 100, 200, 150};
	drawtext(_T("ͯ��"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = {100, 200, 200, 250};
	drawtext(_T("���"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = {100, 300, 200, 350};
	drawtext(_T("����"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = {100, 400, 200, 450};
	drawtext(_T("��ʿ"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(YELLOW);
	settextstyle(20,0,_T("����"));
	outtextxy(220, 120, "�Ӽ�������1λ����2λ�����÷���20����");
	outtextxy(220, 220, "�Ӽ��˷�����1λ����2λ�����÷���20����");
	outtextxy(220, 300, "�Ӽ��˳���������Ϊ2λ�����÷���20����");
	outtextxy(220, 330, "����������");
	outtextxy(220, 400, "�Ӽ��˳���������Ϊ2λ�����÷���20����");
	outtextxy(220, 430, "�������̳���С��������һλС��");

	MOUSEMSG m;       //������
	while(true)        //��������whileģʽ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)  //�������
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
	int flag = 1, count=0, levelgrade[4][2]={1,2,3,4,5,6,7,8}; //count�ǵ÷�,levelgrade����������

	while(flag)  //flag==1ʱ����ѭ��
	{
		int val1, val2;  //��ʽ�󷽵�����ֵ
		float input;  //�����갴������ȷ�ϵ���
		srand ((unsigned)time(NULL)); //������������������ <time.h>
		
		switch(mode)
		{
		case 1:      //ͯ������ż���Ķ�����20�ֽ�������1λ����2λ����;����20���Զ�������
		if(count < 20)
		{
		val1 = rand()%10;  //����1λ�������
		val2 = rand()%10;
		count =  cal_sign(val1, val2, count,levelgrade[0][0], time_start);
		}
		
		if(count>=20)  
		{
		val1 = rand()%100;//����2λ�������
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

		case 3: //���ˡ���ʿ��������20�ֽ�������ֻ�мӼ�������������
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
		break; //ע��λ��

		default:
			exit(0);
		}
	}
}

int cal_sign (int val1, int val2, int count, int level, int time_start) //��ʽ���ɼ���������ͼƷֹ��̣����ص÷�
{
	int a, sign, temp, tag; //temp����ʱֵ����������  tag��־�����㷨����1�ǳ�����Ŀһ��������2�ǿ��ܲ�����������һλС��
	float final, input; //final��ʽ��ȷ�����input�������ս��
	srand((unsigned)time(NULL)); //���������
	switch (level)   //ѡ��������ż���%2�Ӽ���%3�Ӽ��ˣ�%4�Ӽ��˳�
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
	    case 1: //�ӷ�
		TCHAR s1[5], s2[5], s3[5]; //������ת�����ַ��������ڻ�ͼģʽ�����
		_stprintf(s1, _T("%d"), val1);
		_stprintf(s2, _T("%d"), val2);
		_stprintf(s3, _T("%d"), count);

		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);   //����ʽ�͵÷�
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,s1);
		outtextxy(150,100,"+");
		outtextxy(200,100,s2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		outtextxy(120,10,s3);

		final = val1 + val2;
		input = mouse_click();  //��갴������ȷ�ϵ���������input

		while(input!= final)//�������ͼ���дֱ����Ϊֹ
		{
			if (input == -9999) //�����˽�����ť
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //������������ˣ��ǾͿ�һ�֣�ע��9999����������ı�־��
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //���������������»��Ʊ���
		
		if (count < 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,s1);
		outtextxy(150,100,"+");
		outtextxy(200,100,s2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		_stprintf(s3, _T("%d"), count);  //count�иı䣬������Ҫ����s3
		outtextxy(120,10,s3);
		input = mouse_click();
		}
		cleardevice();
		set_background();  //���������������»��Ʊ���
          break;   

		case 2:  //����
			//��ʱҪ����������ָ���,���־ͶԻ�val1,val2
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

		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,m1);
		outtextxy(150,100,"-");
		outtextxy(200,100,m2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		outtextxy(120,10,m3);
		final = val1 - val2;
		input = mouse_click();
		
		
		while(input!= final)//�������ͼ���дֱ����Ϊֹ
		{
			if (input == -9999) //�����˽�����ť
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //������������ˣ��ǾͿ�һ�֣�ע��9999����������ı�־��
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //���������������»��Ʊ���
		
		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,m1);
		outtextxy(150,100,"-");
		outtextxy(200,100,m2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		_stprintf(m3, _T("%d"), count);  //count�иı䣬������Ҫ����m3
		outtextxy(120,10,m3);
		input = mouse_click();
		}
		cleardevice();
		set_background();  //���������������»��Ʊ���
		
		break;

		case 3:  //�˷�
		TCHAR w1[5], w2[5], w3[5];
		_stprintf(w1, _T("%d"), val1);
		_stprintf(w2, _T("%d"), val2);
		_stprintf(w3, _T("%d"), count);

		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,w1);
		outtextxy(150,100,"X");
		outtextxy(200,100,w2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		outtextxy(120,10,w3);
		final = val1 * val2;
		input = mouse_click();
		
		while(input!= final)//�������ͼ���дֱ����Ϊֹ
		{
			if (input == -9999) //�����˽�����ť
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //������������ˣ��ǾͿ�һ�֣�ע��9999����������ı�־��
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //���������������»��Ʊ���
		
		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,w1);
		outtextxy(150,100,"X");
		outtextxy(200,100,w2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		_stprintf(w3, _T("%d"), count);  //count�иı䣬������Ҫ����w3
		outtextxy(120,10,w3);
		input = mouse_click();
		}
		cleardevice();
		set_background();
		break;

		case 4:  //����
			//������ת�ɸ��������ܾ�ȷ����
			if(tag == 2)
			{
			while(val2 == 0) //��������Ϊ0
			{
				val2 = rand()%100;
			}
			}
			if (tag == 1)
			{
				while(val1%val2 !=0) //�����������������������
				{
					
					val1 = rand()%100;
					val2 = rand()%100;
					while(val2 == 0) //��������Ϊ0
			{
				val2 = rand()%100;
			}
				}
			}

		TCHAR d1[5], d2[5], d3[5];
		_stprintf(d1, _T("%d"), val1);
		_stprintf(d2, _T("%d"), val2);
		_stprintf(d3, _T("%d"), count);

		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,d1);
		outtextxy(150,100,"/");
		outtextxy(200,100,d2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		outtextxy(120,10,d3);
		final = (float(val1) / float(val2));  //ת���ɸ��������Ǿ�ȷֵ
		temp = (int(final)*10) + int((final-int(final))*10+0.5); //Ŀ�ģ�����һλС�����������루�õ���ʮ��������
		if(tag == 1)
		{
			input = mouse_click(); //�����ˣ��������С����
		}
		else if (tag == 2)
		{
			if (val1%val2 != 0) //�����ȷ������С���ģ�����������,�����û�һ����Ϊ���û�������С����
			{
		input = mouse_click() * 0.1;  //����������С������һλ���������
			}
			else
			{
				input = mouse_click(); //�����ˣ��������С����
			}
		}

		while(fabs(input- temp*0.1)>=1e-6)//�������ͼ���дֱ����Ϊֹ,input�������洢���ܻ��о���ȱʧ
		{
			if (input == -9999) //�����˽�����ť
			{
				 draw_end (time_start,count);
			}
			if(input!=9999)  //������������ˣ��ǾͿ�һ�֣�ע��9999����������ı�־��
			{
				count = count - 1;
			}
		cleardevice();
		set_background();  //���������������»��Ʊ���
		
		if (count < 20) //ʹ��count�ж϶���ʹ��level�жϣ���Ϊcount��ʵʱ��ӳ������
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"����");
		}
		else if (count >= 20) 
		{
		settextcolor(RGB(0,200,200));   //��ʾ��ǰ����
		settextstyle(50, 0, _T("����"));
		outtextxy(200,10,"�߼�");
		}
		settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(50,100,d1);
		outtextxy(150,100,"/");
		outtextxy(200,100,d2);
		outtextxy(300,100,"=");
		settextcolor(BLUE);
		settextstyle(30, 0, _T("����"));
		outtextxy(30,10,"�÷֣�");
		_stprintf(d3, _T("%d"), count);  //count�иı䣬������Ҫ����d3
		outtextxy(120,10,d3);
		if(tag == 1)
		{
			input = mouse_click(); //�����ˣ��������С����
		}
		else if (tag == 2)
		{
			if (val1%val2 != 0) //�����ȷ������С���ģ�����������,�����û�һ����Ϊ���û�������С����
			{
		input = mouse_click() * 0.1;  //����������С������һλ���������
			}
			else
			{
				input = mouse_click(); //�����ˣ��������С����
			}
		}}
		cleardevice();
		set_background();
		break;

		default:printf("����");exit(0);
	}
	 
count = count+2; //��Լ�2��
	return count;
}


int mouse_click()  //��������ĸ������*0.1 ��Ϊ�˺����޷�����float
{
	int flag = 1, draw = 1;//flag���ѭ�����, draw�Ƿ���ʾ����
	int i, j,count=0, value = 0;
	char c;
	char cal_show[4][3];   //��Ļ���̻���
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
		settextstyle(40, 0, _T("����"));
		outtextxy( 50+15+i*65,250+10+j*80, cal_show[i][j]);
	}

	fillrectangle(400,300,500,350); //ȷ�ϰ�ť
	settextcolor(RED);
	settextstyle(50, 0, _T("����"));
	outtextxy(400,300,"ȷ��");

	setfillcolor(RGB(100,100,100));
	fillrectangle(500,400,600,450); //������ť
	settextcolor(BLACK);
	settextstyle(50, 0, _T("����"));
	outtextxy(500,400,"����");

	MOUSEMSG m;
	
		while(flag == 1)
	{
		draw = 1;  //��ʶ��draw == 0 ʱ�ػ���浫�ǲ��۷֣��������������
		m = GetMouseMsg();  //count++;���ܷ�������
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:	
				if(m.x>=50 && m.x<=100 && m.y>=250 && m.y<=300)
		{
			c = '1';
			count++; //�������ǵڼ��ΰ���
			value = value*10+1;
		}
			else if (m.x>=50+65 && m.x<=100+65 && m.y>=250 && m.y<=300)
			{
				c = '2';
				count++; //�������ǵڼ��ΰ���
				value = value*10+2;
			}
			 else if (m.x>=50+65*2 && m.x<=100+65*2 && m.y>=250 && m.y<=300)
			{
				c = '3';
				count++; //�������ǵڼ��ΰ���
				value = value*10+3;
			} 
			else if (m.x>=50 && m.x<=100 && m.y>=250+80 && m.y<=300+80)
			{
				c = '4';
				count++; //�������ǵڼ��ΰ���
				value = value*10+4;
			}
			else if (m.x>=50+65 && m.x<=100+65 && m.y>=250+80 && m.y<=300+80)
			{
				c = '5';
				count++; //�������ǵڼ��ΰ���
				value = value*10+5;
			}
			else if (m.x>=50+65*2 && m.x<=100+65*2 && m.y>=250+80 && m.y<=300+80)
			{
				c = '6';
				count++; //�������ǵڼ��ΰ���
				value = value*10+6;
			} 
			else if (m.x>=50 && m.x<=100 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '7';
				count++; //�������ǵڼ��ΰ���
				value = value*10+7;
			}
			else if (m.x>=50+65 && m.x<=100+65 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '8';
				count++; //�������ǵڼ��ΰ���
				value = value*10+8;
			}
			else if (m.x>=50+65*2 && m.x<=100+65*2 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '9';
				count++; //�������ǵڼ��ΰ���
				value = value*10+9;
			} 
			else if (m.x>=50+65*3 && m.x<=100+65*3 && m.y>=250+80*2 && m.y<=300+80*2)
			{
				c = '0';
				count++; //�������ǵڼ��ΰ���
				value = value*10+0;
			}
			else if (m.x>=50+65*3 && m.x<=100+65*3 && m.y>=250 && m.y<=300)
			{
				draw = 0;
			
				value = 9999; //Ϊ�˸��������Ϊ0�����������β��Բ������9999���������
			}
			else if (m.x>=50+65*3 && m.x<=100+65*3 && m.y>=250+80 && m.y<=300+80) //����С����ֻ����tag==2���
			{
				c = '.';
				count++; //�������ǵڼ��ΰ���   
				
			}
			else if (m.x>=400 && m.x<=500 && m.y>=300 && m.y<=350)//ȷ�ϼ�ȷ��
			{
				flag = 0;
			} 
			else if (m.x>=500 && m.x<=600 && m.y>=400 && m.y<=450) //����������
			{
				draw = 0;

				value = -9999; //Ϊ�˸��������Ϊ0�����������β��Բ������-9999�����������-9999�Ǳ����
			}
			else  //���˽��������հ״�
			{
				draw = 0;
			
				value = 9999; //Ϊ�˸��������Ϊ0�����������β��Բ������9999�����������9999�Ǳ����
			}

			if (flag == 1 && draw == 1)  //����ʲô���֣���ʱ����Ļ�����ʲô����
			{		
			settextcolor(GREEN);
		settextstyle(100, 0, _T("����"));
		setbkmode (TRANSPARENT);
		outtextxy(350+50*(count-1),100,c );
			}
			else if (flag == 1 && draw == 0)
			{
				flag = 0;  
			}
				break;

			case WM_RBUTTONDBLCLK:
				exit(0);				// ˫������Ҽ��˳�����
		}
		}		
return value;
}

void draw_end (int time_start, int count)
{
	time_t time_end; //����ѵ����ʱ��
	time_end = time(NULL);
	int total_time = time_end - time_start;

	set_background();  //���ñ���
	TCHAR x1[5],x2[5];
	_stprintf(x1, _T("%d"), total_time);
	_stprintf(x2, _T("%d"), count);
	settextcolor(RGB(0,200,200));  
	settextstyle(60, 0, _T("����"));
	outtextxy(10,100,"��ʱ��");
	outtextxy(300,100,x1);
	outtextxy(500,100,"��");
	outtextxy(10,300,"�÷֣�");
	outtextxy(300,300,x2);
	outtextxy(500,300,"��");

	getch();   //�����������
	closegraph();
}

