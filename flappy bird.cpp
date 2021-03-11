#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <graphics.h>

//                  ����ʵ������ͨ��flappy bird �����������¼��ܣ�
//                  Q�� ��Ϊ����ѡȡ״̬�����Դ�͸���ӣ������׻��ǻ���������ʹ��һ�ο�3�֣�
//                  W�� �����ӵ�ͨ�����
//                  E:  ˢ��qwr��cd ����м����������øü���cd��������
//                  R�� r��ȴ�ú��������Ż�Ӱ������ʱ���Իص���Ӱ��λ�á�
//					F:  ���ֹ�һ������ 80�� �ٻ�ʦ���ܡ�

// ��ʼ����ͼ ���졢��ҹ
IMAGE BK[2];

// ȫ�ֻ���
IMAGE bk;

// ������Դ �١�������
// ������ɫ ������̬ ��ʱֻ������״̬ ����֪��Ϊʲô�������������ó�2ʱ���һ��ͼƬ�����
IMAGE BIRD[3][3][3];

// �ܵ���Դ �̡���
IMAGE PIPE[2][2];

// ������������
IMAGE NUMBER[3][10];

// ������Դ
IMAGE MEDAL[4];

// ������Դ
IMAGE LAND;

// ��ʼ��Ϸ��ť
IMAGE PLAY;

// �÷����
IMAGE PANEL;

// ����Ϊ������Ϸ����
// ��Ϸ���� ��ϷԤ�� ��Ϸ���� ��Ϸ��ʾ ��߷�
IMAGE OVER;
IMAGE READY;
IMAGE TITLE;
IMAGE TUTORIAL;
IMAGE NEW;

// ����ʱ״̬
IMAGE OVEIMG;





IMAGE q����ͼ����ȴ���;
IMAGE w����ͼ����ȴ���;
IMAGE e����ͼ����ȴ���;
IMAGE r����ͼ����ȴ���;
IMAGE f����ͼ����ȴ���;


IMAGE ��Ӱ;
IMAGE ��Ӱ;



// ��ȴ����
IMAGE cd[70];
// ���ֶ���
IMAGE ������Ч[6];

IMAGE ע��;


// �Ƿ�Ϊ����
int isDay = 0;

// �Ƿ�����
bool die = false;

// �����ɫ
int birdColor = 0;

// ��߷�
int best = 0;

// ��Ϸ��ʼʱ��
long startTime = 0;

// ��Ϸ��������

// �������ٶ�
double g = 6.5;

// �ܵ����ƶ��ٶ�
double vx = 11;
// ��������ٶ�
double vy = 10;
// ��ĵ�ǰλ��
double y = 220;

// �˴����Ҽ���288
const double x = 288 / 2 - (41 + 8) / 2 - 80 + 288;

bool GetControl = false;

// �����ж�
int fen[5];
// �ܵ��ĺ�������          ԭ�����������Ҽӵ����ĸ�
double pipeX[5];
// �ܵ�����������            ����X���˸�Y ����һ����Сʱ ����һ��
int pipeY[5];
// ��ǰ�÷�
int score;
// ��ľ����ж�����
int top = 12;
int buttom = 33;
const int left = 10;
const int right = 40;

const int Top = 12;
const int Buttom = 40;

// ������ʾλ��
const int medalXY[2] = { 0, 0 };

// ½������
const double landY = 420;
double landX = -20;

// ������̬
int pose = 0;

// ���м��
const int diff = 110;

// �ܵ��ϲ���
// ����ԭ����const int ���ܱ������޸Ĺʸĳ�int
int pipeUp = -280;
// �ܵ��²���
int pipeDown = 140;
// �̶��ܵ�����
const int pipeup = -280;
const int pipedown = 140;



// ��ϷԤ����
void start();
// ��Ϸ����
void game();
// ������Ϸ����
void end();
// �ƶ�����
void move(long time);
// ���ƺ���
void draw(int con);
// ���û���
void reset();
// ���ƻ���
void put();
// ������Դ
void loadRes();
// ����͸���Ȼ�ͼ
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
// ���Ʒ���
void drawScore(int y, int sc, int dif, int se, int st, int type);
// ���ƹܵ�
void drawPipe();
// �ж�������
bool isDie();
// ��ʼ����Ϸ��Դ
void init();


// ��ʾ����ͼ��
void drawqability();
void drawwability();
void draweability();
void drawrability();


void qjineng();
// q���ܳ���ʱ��
int timeqeffect = 5000;
// q���ܿ�ʼʱ��
int timeqstart = 0;
// q������ȴʱ�� 16s
int timeqcd = 16000;




void wjineng();
// w���ܳ���ʱ�� 7s ǰ2s �����С ֮��������С
int timeweffect = 7000;
// w���ܿ�ʼʱ��
int timewstart = 0;
// w������ȴʱ�� 15s
int timewcd = 20000;
// w����ͨ������Χ
int space = 80;
// ʵʱ�ܵ��������
double bilibili;
// ����ʱ���������
double landYxiuzheng = landY;


void ejineng();
// e���ܿ�ʼʱ��
int timeestart = 0;
// e������ȴʱ�� 20s
int timeecd = 20000;
// e���ܼ���
bool ejinengjihuo = false;


// r���ܳ���ʱ�� ����Ӱ��Ӧʱ��
int timereffect = 1500;
// r���ܿ�ʼʱ��
int timerstart = -20000;
// r������ȴʱ��
int timercd = 20000;
// ��Ӱ����
int tuoyingjishu = 0;
// r������ز�����ʼ��
void rinitialize();


// f����
void fjineng();
// f����ʹ��ʱ��
int timefstart = 0;
// f������ȴʱ�� 30s
int timefcd = 30000;
// f���ܼ���˲��
bool fjinengjihuo = false;
// ���־���
int fjuli = 100; 
// ������Ч
void ftexiao();
// f ��Ч����
int ftexiaojishu = 10;

// ��¼���λ��
int ftexiaoX;
int ftexiaoY;




// ����Ӧ����150 ��ֹ�������������
double tuoyingX[252];
double tuoyingY[252];

// ��ʱһ�����ּ�¼���̲���
long temp1;

// q����ʱ����
bool qisDie();

// һ����������õ�����
int yinshenjiange1 = 1;
int yinshenjiange2 = 1;

// ��ʾ����ͼ��
void drawcd();
// r�������
void rjineng();
void drawtuoying();

bool dazhao = false;

// ��Ӱ��������
const int tuoyingxiuzhengx = 15;
const int tuoyingxiuzhengy = 20;

// ��Ӱ���ֵ
const int tuoyingmax = 100;

// ��Ӱ����ʱ�� ����ǰ��˾���4s Ҳ����4000
const int tuoyingchuxianshijian = 2500;

// ������Ӱ֮��x�ľ���
double betweenx;

// һ����r����ʹ���ڼ����ʱ����
double lin;

// һ������clock�ı���
double thistime;
double xiuzhengtime;
double xiuzheng();

int main()
{
	// ��Ϸ����ҳ��
	init();
	while (true)
	{
		// ��Ϸ��ʼ��
		start();
		// ��Ϸ����
		game();
		// ��ʾ�÷�
		end();
	}
	return 0;
}


int Control()
{
	int res = 0;

	if (_kbhit())
	{
		char ch = _getch();
		if (ch == ' ')
		{
			res = 1;
		}
		if (ch == 'q'|| ch == 'Q')
		{
			res = 2;
		}
		if (ch == 'w' || ch == 'W')
		{
			res = 3;
		}
		if (ch == 'e' || ch == 'E')
		{
			res = 4;
		}
		if (ch == 'r' || ch == 'R')
		{
			res = 5;
		}
		if (ch == 'f' || ch == 'F')
		{
			res = 6;
		}
	}

	MOUSEMSG msg;
	while (MouseHit())
	{
		msg = GetMouseMsg();
		if (msg.mkLButton)
		{
			res = 1;
		}
	}

	return res;
}


// ��ϷԤ����
void start()
{
	// ��ʼ������
	isDay = rand() % 2;		
	birdColor = rand() % 3;

	// �˴����Ҽ��� 288             �ּ������� ÿ����֮����190��
	pipeX[0] = 288 + 30 + 288;
	pipeX[1] = 288 + 30 + 288 + 190;
	pipeX[2] = 288 + 30 + 288 + 190 + 190;
	pipeX[3] = 288 + 30 + 288 + 190 + 190 + 190;
	pipeX[4] = 288 + 30 + 288 + 190 + 190 + 190 + 190;


	pipeY[0] = rand() % 250;
	pipeY[1] = rand() % 250;
	pipeY[2] = rand() % 250;
	pipeY[3] = rand() % 250;
	pipeY[4] = rand() % 250;



	pose = 0;
	landX = 0;
	score = 0;
	y = 220;
	vy = 0;

	// ��Ϸ��ʼʱ��
	clock_t time = xiuzheng();
	// ��������
	clock_t t = xiuzheng();
	while (true)
	{
		reset();
		drawScore(60, score, 13, 26, 144, 0);
		drawAlpha(&bk, 50 + 144 + 70, 120, &READY);
		drawAlpha(&bk, (int)x, (int)y, &BIRD[birdColor][pose][1]);
		drawAlpha(&bk, 90 + 144 + 60, 180, &TUTORIAL);
		drawAlpha(&bk, (int)landX, (int)landY, &LAND);
		landX -= (xiuzheng() - t) * vx / 100;
		t = xiuzheng();
		pose = (((int)xiuzheng() - time) / diff) % 3;
		put();
		if (landX < -44)
		{
			landX = -20;
		}
		if (Control() == 1)
		{
			break;
		}
		Sleep(10);
	}
}


// ��Ϸ����
void game()
{
	// ���ݺ���
	startTime = xiuzheng();
	long time = xiuzheng();

	//cd����
	timeqstart = xiuzheng() - timeqcd;
	timewstart = xiuzheng() - timewcd;
	timeestart = xiuzheng() - timeecd;
	timerstart = xiuzheng() - timercd + tuoyingchuxianshijian;
	timefstart = xiuzheng() - timefcd;

	//r���ܳ�ʼ��
	rinitialize();
	
	// ��������
	landYxiuzheng = landY;
	
	// f��Ч����
	ftexiaojishu = 10;

	dazhao = false;
	tuoyingjishu = 0;
	die = false;

	fen[0] = 1;
	fen[1] = 1;
	fen[2] = 1;
	fen[3] = 1;
	fen[4] = 1;



	while (!die)
	{
		
		GetControl = false;
		temp1 = Control();
		if (temp1 == 1)
		{
			GetControl = true;
		}
		else if (temp1 == 2)
		{
			//q������
			if (timeqcd + timeqstart < xiuzheng())
			{
				//cdת���� q������
				timeqstart = xiuzheng();
				//ʹ��q����Ҫ��3��
				if (score > 2)
				{
					score -= 3;
				}
				else
				{
					score = 0;
				}


			}
		}
		else if (temp1 == 3)
		{
			//w������
			if (timewcd + timewstart < xiuzheng())
			{
				//cdת���� w������
				timewstart = xiuzheng();
				//ʹ��w���ܲ��ÿ۷�
			/*	if (score > 2)
				{
					score -= 3;
				}
				else
				{
					score = 0;
				}*/
			}
		}
		else if (temp1 == 4)
		{
			//e������
			if (timeecd + timeestart < xiuzheng())
			{
				//cdת���� e������
				timeestart = xiuzheng();
				ejinengjihuo = true;
			}
		}

		else if (temp1 == 5)
		{
			//r������
			if (timercd + timerstart < xiuzheng())
			{
				//cdת���� r������
				timerstart = xiuzheng();
				dazhao = true;
			}
		}

		else if (temp1 == 6)
		{
			//f������
			if (timefcd + timefstart < xiuzheng())
			{
				//cdת���� f������
				timefstart = xiuzheng();
				fjinengjihuo = true;
			}
		}

		// �ƶ�
		move(xiuzheng() - time);
		time = xiuzheng();
		// ����
		if (GetControl)
		{
			vy = -26;
		}
		//����q�������
		qjineng();
		//����w�������
		wjineng();
		//����e�������
		ejineng();
		// ����r�������
		rjineng();
		// ����f�������
		fjineng();

		// �ڼ�����ȴʱ����߼���û��ʱ������
		if (timeqeffect + timeqstart < xiuzheng() || timeqeffect + timeqstart == xiuzheng())
		{
			die = isDie();
			draw(1);
		}
		
		
		Sleep(10);

	}

	startTime = xiuzheng();
	while (xiuzheng() - startTime < 1000);
	vy = -30;
	time = xiuzheng();
	while (y < 520)
	{
		y += (xiuzheng() - time) * vy / 100;
		vy += g * (xiuzheng() - time) / 100;
		time = xiuzheng();
		draw(1);
		Sleep(10);
	}

	// ���ݴ�ʱͼƬ
	drawAlpha(&OVEIMG, 0, 0, &bk);
}


void flush()
{ 
	while (MouseHit())
		GetMouseMsg();
	while (_kbhit())
		_getch();
}

// ��������
void end()
{
	// ������Ƴ�
	startTime = xiuzheng();
	// ���û���
	reset();
	// �����·��Ƴ�
	drawPipe();
	drawAlpha(&bk, (int)landX, (int)landY, &LAND);
	drawAlpha(&bk, 0, 0, &OVEIMG);
	drawAlpha(&bk, 175, 150, &PANEL);
	// �������ִ�ӡ����
	int r = score / 30;
	if (score > 10)
	{
		if (r > 3)
		{
			r = 3;
		}
		if (r < 0)
		{
			r = 0;
		}
		drawAlpha(&bk, 207, 195, &MEDAL[r]);
	}
	// ��ӡ��ǰ��
	drawScore(189, score, 16, 16, 390, 2);
	// д��߷�
	int tmp = best;
	if (best < score)
	{
		best = score;
	}
	// ��ӡ��߷�
	drawScore(231, best, 16, 16, 390, 2);

	// �����ǰ�ֳ�����߷� ����ʾ�·���ͼ��
	if (tmp < score)
	{
		drawAlpha(&bk, 315, 210, &NEW);
	}
	flush();
	put();
	while (true)
	{
		if (Control() == 1 )
		{
			break;
		}
		Sleep(10);
	}
}


void drawScore(int y, int sc, int dif, int se, int st, int type)
{
	// ������������ʾ
	int t = sc;
	int num[8];
	int length = 0;
	do
	{
		num[length] = t % 10;
		length++;
		t /= 10;
	} while (t != 0);

	// �������ʼ����
	int s = st - dif * length;
	for (int i = length - 1; i >= 0; i--)
	{
		drawAlpha(&bk, s, y, &NUMBER[type][num[i]]);
		s += se;
	}
}


// �ܵ������ǡ������ƶ�
void move(long time)
{
	y += time * vy / 100;
	vy += g * time / 100;

	pipeX[0] -= time * vx / 100;
	pipeX[1] -= time * vx / 100;
	pipeX[2] -= time * vx / 100;
	pipeX[3] -= time * vx / 100;
	pipeX[4] -= time * vx / 100;
	
	//��Ӱ����ƶ�
	for (int i = 0; i < tuoyingmax + 1; i++)
	{
		tuoyingX[i] -= time * vx / 100;
	}

	landX -= time * vx / 100;
	pose = (((int)xiuzheng() - startTime) / diff) % 3;
	if (landX < -44)
	{
		landX = -20;
	}



	// �˴���֪���޸ĵĶԲ���
	//***********************************************************************
	if (pipeX[0] < -200)
	{
		pipeX[0] = pipeX[4] + 190;
		pipeY[0] = rand() % 250;
		fen[0] = 1;
	}
	if (pipeX[1] < -200)
	{
		pipeX[1] = pipeX[0] + 190;
		pipeY[1] = rand() % 250;
		fen[1] = 1;
	}
	if (pipeX[2] < -200)
	{
		pipeX[2] = pipeX[1] + 190;
		pipeY[2] = rand() % 250;
		fen[2] = 1;
	}
	if (pipeX[3] < -200)
	{
		pipeX[3] = pipeX[2] + 190;
		pipeY[3] = rand() % 250;
		fen[3] = 1;
	}
	if (pipeX[4] < -200)
	{
		pipeX[4] = pipeX[3] + 190;
		pipeY[4] = rand() % 250;
		fen[4] = 1;
	}


	//********************************************************************

	// ����Ϊ�޸Ĺ�������ֱ�׼ ���ݹ��ܵ�������
	if (pipeX[0] < x && fen[0] == 1)
	{
		score += 1;
		fen[0] = 0;
	}
	if (pipeX[1] < x && fen[1] == 1)
	{
		score += 1;
		fen[1] = 0;
	}
	if (pipeX[2] < x && fen[2] == 1)
	{
		score += 1;
		fen[2] = 0;
	}
	if (pipeX[3] < x && fen[3] == 1)
	{
		score += 1;
		fen[3] = 0;
	}
	if (pipeX[4] < x && fen[4] == 1)
	{
		score += 1;
		fen[4] = 0;
	}

	//****************************************************

	if (y < 0 - top)
	{
		y = -top;
	}


	// ����Ϊԭ�����ֱ�׼ ����ʱ������
	//score = (int)(((xiuzheng() - startTime) * vx / 100 - (288 - x + 30)) / 190 + 1);
	//if (score < 0)
	//{
	//	score = 0;
	//}
}

void draw(int con)
{
	// ��ʼ������ͼ
	drawAlpha(&bk, 0, 0, &BK[isDay]);
	// ���ܵ�
	drawPipe();
	// ��½��
	drawAlpha(&bk, (int)landX, (int)landY, &LAND);

	// ������
	drawScore(60, score, 13, 26, 288, 0);
	// ������ͼ��
	drawcd();

	// ��r������ӰЧ��
	drawtuoying();

	// ����
	drawAlpha(&bk, (int)x, (int)y, &BIRD[birdColor][pose][con]);

	// ��������Ч
	ftexiao();

	// ����������������
	put();
}


// ����͸���Ȼ�ͼ
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	if (dstimg == NULL)
	{
		return;
	}
	// ������ʼ��
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = dstimg->getwidth();
	int dst_height = dstimg->getheight();

	// ʵ��͸����ͼ  ���Ż�
	for (int iy = 0; iy < src_height; iy++)
	{
		for (int ix = 0; ix < src_width; ix++)
		{
			int srcX = ix + iy * src_width;
			int sa = ((src[srcX] & 0xff000000) >> 24);
			int sr = ((src[srcX] & 0xff0000) >> 16);
			int sg = ((src[srcX] & 0xff00) >> 8);
			int sb = src[srcX] & 0xff;
			if (x + ix >= 0 && x + ix < dst_width
				&& y + iy >= 0 && y + iy < dst_height)
			{
				int dstX = (x + ix) + (y + iy) * dst_width;
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				dst[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
					| (sb * sa / 255 + db * (255 - sa) / 255);
			}
		}
	}
}

// ���ܵ� �ֹܵ�1�͹ܵ�2
void drawPipe()
{
	// ���ܵ�
	drawAlpha(&bk, (int)pipeX[0], pipeY[0] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[0], pipeY[0] + pipeDown, &PIPE[isDay][1]);
	// ���ܵ�
	drawAlpha(&bk, (int)pipeX[1], pipeY[1] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[1], pipeY[1] + pipeDown, &PIPE[isDay][1]);
	
	
	drawAlpha(&bk, (int)pipeX[2], pipeY[2] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[2], pipeY[2] + pipeDown, &PIPE[isDay][1]);
	
	
	drawAlpha(&bk, (int)pipeX[3], pipeY[3] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[3], pipeY[3] + pipeDown, &PIPE[isDay][1]);

	drawAlpha(&bk, (int)pipeX[4], pipeY[4] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[4], pipeY[4] + pipeDown, &PIPE[isDay][1]);


}



// �ж����Ƿ�����
bool isDie()
{
	// ��������
	if (y + buttom > landYxiuzheng)
		return true;

	//ײ���ܵ�
	if (x + right > pipeX[0] && x + left < pipeX[0] + 52)
	{
		if (y + top < pipeY[0] + 40 || y + buttom > pipeY[0] + 140)
			return true;
	}

	if (x + right > pipeX[1] && x + left < pipeX[1] + 52)
	{
		if (y + top < pipeY[1] + 40 || y + buttom > pipeY[1] + 140)
			return true;
	}

	if (x + right > pipeX[2] && x + left < pipeX[2] + 52)
	{
		if (y + top < pipeY[2] + 40 || y + buttom > pipeY[2] + 140)
			return true;
	}

	if (x + right > pipeX[3] && x + left < pipeX[3] + 52)
	{
		if (y + top < pipeY[3] + 40 || y + buttom > pipeY[3] + 140)
			return true;
	}

	if (x + right > pipeX[4] && x + left < pipeX[4] + 52)
	{
		if (y + top < pipeY[4] + 40 || y + buttom > pipeY[4] + 140)
			return true;
	}


	return false;
}

// ������(q)��������ж����Ƿ�����
bool qisDie()
{
	// ��������
	if (y + buttom > landYxiuzheng)
		return true;

	return false;
}


//����
void reset()
{
	drawAlpha(&bk, 0, 0, &BK[isDay]);
}


void put()
{
	putimage(0, 0, &bk);

}


// ��ʼ����Ϸ��Դ
void init()
{
	// ����ͼ����Դ
	loadRes();
	// ��ʼ��ͼ�ν��� ���ﱻ���޸��� ԭ����288��512
	initgraph(576, 512);
	// ��ʼ�����������
	srand((unsigned int)time(NULL));
	// ��ʼ������
	best = 0;
	isDay = rand() % 2;
	birdColor = rand() % 3;
	// ��Ϸ��ʼʱ��
	clock_t time = xiuzheng();
	// ��������
	while (true)
	{
		reset();
		drawAlpha(&bk, 60 + 144, 120, &TITLE);
		drawAlpha(&bk, 125 + 144, 200, &BIRD[birdColor][pose][1]);
		drawAlpha(&bk, 90 + 144, 270, &PLAY);
		drawAlpha(&bk, 0, 400, &ע��);
		pose = (((int)xiuzheng() - time) / diff) % 3;
		put();
		if (Control() == 1)
		{
			break;
		}
		Sleep(10);
	}
	xiuzhengtime = 0;
	thistime = 0;
}


// ����ͼƬ��Դ
void loadRes()
{
	loadimage(&BK[0], _T("res\\bg_day.png"));
	loadimage(&BK[1], _T("res\\bg_night.png"));

	loadimage(&bk, _T("res\\bg_day.png"));

	loadimage(&OVEIMG, _T("res\\bg_day.png"));

	loadimage(&BIRD[0][0][1], _T("res\\bird0_0.png"));
	loadimage(&BIRD[0][1][1], _T("res\\bird0_1.png"));
	loadimage(&BIRD[0][2][1], _T("res\\bird0_2.png"));
	loadimage(&BIRD[1][0][1], _T("res\\bird1_0.png"));
	loadimage(&BIRD[1][1][1], _T("res\\bird1_1.png"));
	loadimage(&BIRD[1][2][1], _T("res\\bird1_2.png"));
	loadimage(&BIRD[2][0][1], _T("res\\bird2_0.png"));
	loadimage(&BIRD[2][1][1], _T("res\\bird2_1.png"));
	loadimage(&BIRD[2][2][1], _T("res\\bird2_2.png"));

	loadimage(&BIRD[0][0][2], _T("res\\bird0_0(����).png"));
	loadimage(&BIRD[0][1][2], _T("res\\bird0_1(����).png"));
	loadimage(&BIRD[0][2][2], _T("res\\bird0_2(����).png"));
	loadimage(&BIRD[1][0][2], _T("res\\bird1_0(����).png"));
	loadimage(&BIRD[1][1][2], _T("res\\bird1_1(����).png"));
	loadimage(&BIRD[1][2][2], _T("res\\bird1_2(����).png"));
	loadimage(&BIRD[2][0][2], _T("res\\bird2_0(����).png"));
	loadimage(&BIRD[2][1][2], _T("res\\bird2_1(����).png"));
	loadimage(&BIRD[2][2][2], _T("res\\bird2_2(����).png"));

	loadimage(&PIPE[0][0], _T("res\\pipe_down.png"));
	loadimage(&PIPE[0][1], _T("res\\pipe_up.png"));
	loadimage(&PIPE[1][0], _T("res\\pipe2_down.png")); 
	loadimage(&PIPE[1][1], _T("res\\pipe2_up.png"));

	loadimage(&NUMBER[0][0], _T("res\\font_048.png"));
	loadimage(&NUMBER[0][1], _T("res\\font_049.png"));
	loadimage(&NUMBER[0][2], _T("res\\font_050.png"));
	loadimage(&NUMBER[0][3], _T("res\\font_051.png"));
	loadimage(&NUMBER[0][4], _T("res\\font_052.png"));
	loadimage(&NUMBER[0][5], _T("res\\font_053.png"));
	loadimage(&NUMBER[0][6], _T("res\\font_054.png"));
	loadimage(&NUMBER[0][7], _T("res\\font_055.png"));
	loadimage(&NUMBER[0][8], _T("res\\font_056.png"));
	loadimage(&NUMBER[0][9], _T("res\\font_057.png"));

	loadimage(&NUMBER[1][0], _T("res\\number_context_00.png"));
	loadimage(&NUMBER[1][1], _T("res\\number_context_01.png"));
	loadimage(&NUMBER[1][2], _T("res\\number_context_02.png"));
	loadimage(&NUMBER[1][3], _T("res\\number_context_03.png"));
	loadimage(&NUMBER[1][4], _T("res\\number_context_04.png"));
	loadimage(&NUMBER[1][5], _T("res\\number_context_05.png"));
	loadimage(&NUMBER[1][6], _T("res\\number_context_06.png"));
	loadimage(&NUMBER[1][7], _T("res\\number_context_07.png"));
	loadimage(&NUMBER[1][8], _T("res\\number_context_08.png"));
	loadimage(&NUMBER[1][9], _T("res\\number_context_09.png"));

	loadimage(&NUMBER[2][0], _T("res\\number_score_00.png"));
	loadimage(&NUMBER[2][1], _T("res\\number_score_01.png"));
	loadimage(&NUMBER[2][2], _T("res\\number_score_02.png"));
	loadimage(&NUMBER[2][3], _T("res\\number_score_03.png"));
	loadimage(&NUMBER[2][4], _T("res\\number_score_04.png"));
	loadimage(&NUMBER[2][5], _T("res\\number_score_05.png"));
	loadimage(&NUMBER[2][6], _T("res\\number_score_06.png"));
	loadimage(&NUMBER[2][7], _T("res\\number_score_07.png"));
	loadimage(&NUMBER[2][8], _T("res\\number_score_08.png"));
	loadimage(&NUMBER[2][9], _T("res\\number_score_09.png"));

	loadimage(&MEDAL[0], _T("res\\medals_3.png"));
	loadimage(&MEDAL[1], _T("res\\medals_2.png"));
	loadimage(&MEDAL[2], _T("res\\medals_1.png"));
	loadimage(&MEDAL[3], _T("res\\medals_0.png"));

	loadimage(&LAND, _T("res\\land.png"));

	loadimage(&PLAY, _T("res\\button_play.png"));

	loadimage(&OVER, _T("res\\text_game_over.png"));

	loadimage(&READY, _T("res\\text_ready.png"));

	loadimage(&TITLE, _T("res\\title.png"));

	loadimage(&TUTORIAL, _T("res\\tutorial.png"));

	loadimage(&NEW, _T("res\\new.png"));

	loadimage(&PANEL, _T("res\\score_panel.png"));




	loadimage(&q����ͼ����ȴ���, _T("res\\q����ͼ����ȴ���.png"));
	loadimage(&w����ͼ����ȴ���, _T("res\\w����ͼ����ȴ���.png"));
	loadimage(&e����ͼ����ȴ���, _T("res\\e����ͼ����ȴ���.png"));
	loadimage(&r����ͼ����ȴ���, _T("res\\r����ͼ����ȴ���.png"));
	loadimage(&r����ͼ����ȴ���, _T("res\\r����ͼ����ȴ���.png"));
	loadimage(&f����ͼ����ȴ���, _T("res\\���ּ���ͼ����ȴ���.png"));

	
	loadimage(&��Ӱ, _T("res\\��Ӱ2.png"));
	loadimage(&��Ӱ, _T("res\\��Ӱ.png"));



	loadimage(&cd[0], _T("res\\cd\\cd0.png"));
	loadimage(&cd[1], _T("res\\cd\\cd1.png"));
	loadimage(&cd[2], _T("res\\cd\\cd2.png"));
	loadimage(&cd[3], _T("res\\cd\\cd3.png"));
	loadimage(&cd[4], _T("res\\cd\\cd4.png"));
	loadimage(&cd[5], _T("res\\cd\\cd5.png"));
	loadimage(&cd[6], _T("res\\cd\\cd6.png"));
	loadimage(&cd[7], _T("res\\cd\\cd7.png"));
	loadimage(&cd[8], _T("res\\cd\\cd8.png"));
	loadimage(&cd[9], _T("res\\cd\\cd9.png"));
	loadimage(&cd[10], _T("res\\cd\\cd10.png"));
	loadimage(&cd[11], _T("res\\cd\\cd11.png"));
	loadimage(&cd[12], _T("res\\cd\\cd12.png"));
	loadimage(&cd[13], _T("res\\cd\\cd13.png"));
	loadimage(&cd[14], _T("res\\cd\\cd14.png"));
	loadimage(&cd[15], _T("res\\cd\\cd15.png"));
	loadimage(&cd[16], _T("res\\cd\\cd16.png"));
	loadimage(&cd[17], _T("res\\cd\\cd17.png"));
	loadimage(&cd[18], _T("res\\cd\\cd18.png"));
	loadimage(&cd[19], _T("res\\cd\\cd19.png"));
	loadimage(&cd[20], _T("res\\cd\\cd20.png"));
	loadimage(&cd[21], _T("res\\cd\\cd21.png"));
	loadimage(&cd[22], _T("res\\cd\\cd22.png"));
	loadimage(&cd[23], _T("res\\cd\\cd23.png"));
	loadimage(&cd[24], _T("res\\cd\\cd24.png"));
	loadimage(&cd[25], _T("res\\cd\\cd25.png"));
	loadimage(&cd[26], _T("res\\cd\\cd26.png"));
	loadimage(&cd[27], _T("res\\cd\\cd27.png"));
	loadimage(&cd[28], _T("res\\cd\\cd28.png"));
	loadimage(&cd[29], _T("res\\cd\\cd29.png"));
	loadimage(&cd[30], _T("res\\cd\\cd30.png"));
	loadimage(&cd[31], _T("res\\cd\\cd31.png"));
	loadimage(&cd[32], _T("res\\cd\\cd32.png"));
	loadimage(&cd[33], _T("res\\cd\\cd33.png"));
	loadimage(&cd[34], _T("res\\cd\\cd34.png"));
	loadimage(&cd[35], _T("res\\cd\\cd35.png"));
	loadimage(&cd[36], _T("res\\cd\\cd36.png"));
	loadimage(&cd[37], _T("res\\cd\\cd37.png"));
	loadimage(&cd[38], _T("res\\cd\\cd38.png"));
	loadimage(&cd[39], _T("res\\cd\\cd39.png"));
	loadimage(&cd[40], _T("res\\cd\\cd40.png"));
	loadimage(&cd[41], _T("res\\cd\\cd41.png"));
	loadimage(&cd[42], _T("res\\cd\\cd42.png"));
	loadimage(&cd[43], _T("res\\cd\\cd43.png"));
	loadimage(&cd[44], _T("res\\cd\\cd44.png"));
	loadimage(&cd[45], _T("res\\cd\\cd45.png"));
	loadimage(&cd[46], _T("res\\cd\\cd46.png"));
	loadimage(&cd[47], _T("res\\cd\\cd47.png"));
	loadimage(&cd[48], _T("res\\cd\\cd48.png"));
	loadimage(&cd[49], _T("res\\cd\\cd49.png"));
	loadimage(&cd[50], _T("res\\cd\\cd50.png"));
	loadimage(&cd[51], _T("res\\cd\\cd51.png"));
	loadimage(&cd[52], _T("res\\cd\\cd52.png"));
	loadimage(&cd[53], _T("res\\cd\\cd53.png"));
	loadimage(&cd[54], _T("res\\cd\\cd54.png"));
	loadimage(&cd[55], _T("res\\cd\\cd55.png"));
	loadimage(&cd[56], _T("res\\cd\\cd56.png"));
	loadimage(&cd[57], _T("res\\cd\\cd57.png"));
	loadimage(&cd[58], _T("res\\cd\\cd58.png"));
	loadimage(&cd[59], _T("res\\cd\\cd59.png"));
	loadimage(&cd[60], _T("res\\cd\\cd60.png"));

	loadimage(&������Ч[0], _T("res\\������Ч\\flash0.png"));
	loadimage(&������Ч[1], _T("res\\������Ч\\flash1.png"));
	loadimage(&������Ч[2], _T("res\\������Ч\\flash2.png"));
	loadimage(&������Ч[3], _T("res\\������Ч\\flash3.png"));
	loadimage(&������Ч[4], _T("res\\������Ч\\flash4.png"));

	loadimage(&ע��, _T("res\\ע��2.png"));

	
}


void drawqability()
{
	drawAlpha(&bk, 100, 450, &q����ͼ����ȴ���);

	if (timeqcd + timeqstart > xiuzheng())
	{
		drawAlpha(&bk, 100, 450, &cd[int(((timeqcd + timeqstart - xiuzheng()) / timeqcd) * 60)]);
	}



}

void drawwability()
{
	drawAlpha(&bk, 200, 450, &w����ͼ����ȴ���);
	if (timewcd + timewstart > xiuzheng())
	{
		drawAlpha(&bk, 200, 450, &cd[int(((timewcd + timewstart - xiuzheng()) / timewcd) * 60)]);
	}

	
}

void draweability()
{
	drawAlpha(&bk, 300, 450, &e����ͼ����ȴ���);

	if (timeecd + timeestart > xiuzheng())
	{
		drawAlpha(&bk, 300, 450, &cd[int(((timeecd + timeestart - xiuzheng()) / timeecd) * 60)]);
	}
}


void drawrability()
{
	drawAlpha(&bk, 400, 450, &r����ͼ����ȴ���);
	if (timercd + timerstart > xiuzheng())
	{
		drawAlpha(&bk, 400, 450, &cd[int(((timercd + timerstart - xiuzheng()) / timercd) * 60)]);
	}

}

void drawfability()
{
	drawAlpha(&bk, 500, 450, &f����ͼ����ȴ���);

	if (timefcd + timefstart > xiuzheng())
	{
		drawAlpha(&bk, 500, 450, &cd[int(((timefcd + timefstart - xiuzheng()) / timefcd) * 60)]);
	}

}

void drawcd()
{
	drawqability();
	drawwability();
	draweability();
	drawrability();
	drawfability();

}

void qjineng()
{
	// �Ҹ�ʱ��������д��һ������
// ��q���ܳ���ʱ������
// ͬʱ����
	if (timeqeffect + timeqstart > xiuzheng())
	{
		if (timeqeffect + timeqstart > xiuzheng() + 1000)
		{
			//q���ܴ��ڼ���״̬ �һ����㹻ʱ��
			draw(2);
		}
		else
		{
			//q���ܿ�Ҫ������ ��ʼ��˸
			if (yinshenjiange1 < 20)
			{
				yinshenjiange1 += 1;
				if (yinshenjiange1 < 10)
				{
					yinshenjiange2 = 1;
				}
				else
				{
					yinshenjiange2 = 2;
				}
			}
			else
			{
				yinshenjiange1 = 1;
			}
			draw((int)yinshenjiange2);
		}
		//��q���ܼ��������½��������ж�
		die = qisDie();
	}

}

void wjineng()
{
	// w���� �޸Ĺܵ������²��� ʹ֮������
	if (timeweffect + timewstart > xiuzheng())
	{
		if (timeweffect + timewstart > xiuzheng() + 5000)
		{
			pipeUp = pipeup - (space / 2);
			pipeDown = pipedown + (space / 2);
			top = Top + (space / 2);
			buttom = Buttom - (space / 2);
			landYxiuzheng = landY - (space / 2);
		}
		else
		{
			bilibili = (timeweffect + timewstart - xiuzheng()) / 5000;
			pipeUp = pipeup - ((space / 2) * bilibili);
			pipeDown = pipedown + ((space / 2) * bilibili);
			top = Top + ((space / 2) * bilibili);
			buttom = Buttom - ((space / 2) * bilibili);
			landYxiuzheng = landY - ((space / 2) * bilibili);

		}
		
	}
	else
	{
		pipeUp = pipeup;
		pipeDown = pipedown;

		top = Top;
		buttom = Buttom;
		landYxiuzheng = landY;
	}
}

void ejineng()
{
	if (ejinengjihuo == true)
	{
		if (timeqeffect + timeqstart < xiuzheng())
		{
			timeqstart = xiuzheng() - timewcd;
		}
		if (timeweffect + timewstart < xiuzheng())
		{
			timewstart = xiuzheng() - timewcd;
		}
		if (timerstart > xiuzheng() - timercd + tuoyingchuxianshijian)
		{
			timerstart = xiuzheng() - timercd + tuoyingchuxianshijian;
		}
		timefstart = xiuzheng() - timefcd;
		ejinengjihuo = false;

	}

}


void rjineng()
{//                                     �������ںţ�����
	if (dazhao == false)
	{
		//������ǳ��ڰ���r��ɲ��
		if (timerstart + timercd < xiuzheng() + tuoyingchuxianshijian)
		{
			//���r��ȴ���
			if (tuoyingjishu < tuoyingmax + 1)
			{
				tuoyingjishu += 1;
				tuoyingX[tuoyingjishu] = x + tuoyingxiuzhengx;
				tuoyingY[tuoyingjishu] = y + tuoyingxiuzhengy;
			}
			else if (tuoyingjishu == tuoyingmax + 1)
			{
				for (int i = 0; i < tuoyingmax; i++)
				{

					tuoyingX[i] = tuoyingX[i + 1];
					tuoyingY[i] = tuoyingY[i + 1];
				}
				tuoyingX[tuoyingmax] = x + tuoyingxiuzhengx;
				tuoyingY[tuoyingmax] = y + tuoyingxiuzhengy;
			}
		}
	}

	if (dazhao == true)
	{
		thistime = xiuzheng();
		for (int i = tuoyingmax ; i > 0 ; i--)
		{
			betweenx = tuoyingX[i] - tuoyingX[i - 1];
			// �ܵ��ƶ�
			pipeX[0] += betweenx;
			pipeX[1] += betweenx;
			pipeX[2] += betweenx;
			pipeX[3] += betweenx;
			pipeX[4] += betweenx;

			// �ذ��ƶ�
			landX += betweenx;
			if (landX >-20)
			{
				landX = -44;
			}	

			// ��Ӱ�ƶ�
			for (int i = 0; i < tuoyingmax + 1; i++)
			{
				if (tuoyingX[i] != -1)
				{
					tuoyingX[i] += betweenx;
				}
			
			}

			// ���ƶ�(ֻ������)
			y = tuoyingY[i];

			// ɾ����Ӱ��Ӱ
			tuoyingX[i] = -1;

			// ������
			draw(2);
		}
//***************************************************************************���һ�����޿ɼ� ֻ�ܳ����²�
		// �ܵ��ƶ�
		pipeX[0] += betweenx;
		pipeX[1] += betweenx;
		pipeX[2] += betweenx;
		pipeX[3] += betweenx;
		pipeX[4] += betweenx;

		// �ذ��ƶ�
		landX += betweenx;
		if (landX > -20)
		{
			landX = -44;
		}

		// ��Ӱ�ƶ�
		for (int i = 0; i < tuoyingmax + 1; i++)
		{
			if (tuoyingX[i] != -1)
			{
				tuoyingX[i] += betweenx;
			}
		}

		// ���ƶ�(ֻ������)
		y = tuoyingY[0];

		// ɾ����Ӱ��Ӱ
		tuoyingX[0] = -1;

		// ������
		draw(2);
 //***************************************************************************************************
		// ������Լ���Ч
		
		// r��ȥ���ٶȹ���
		vy = 0;
		// r��ȥ�����ӵ÷ֱ仯
		for (int i = 0; i < 5; i++)
		{
			if (pipeX[i] > x)
			{
				fen[i] = 1;
			}
		}
		
		dazhao = false;
		xiuzhengtime += xiuzheng() - thistime;

	}
}


void fjineng()
{
	// f���� �����񼼲�����
	if (fjinengjihuo == true)
	{

		ftexiaoX = x ;
		ftexiaoY = y ;

		pipeX[0] -= fjuli;
		pipeX[1] -= fjuli;
		pipeX[2] -= fjuli;
		pipeX[3] -= fjuli;
		pipeX[4] -= fjuli;

		// �ذ��ƶ�
		landX -= fjuli;
		if (landX > -20)
		{
			landX = -44;
		}
		fjinengjihuo = false;

		//��Ӱ�ƶ�
		for (int i = 0; i < tuoyingmax + 1; i++)
		{
			if (tuoyingX[i] != -1)
			{
				tuoyingX[i] -= fjuli;
			}
		}
		ftexiaojishu = 0;
	}
}


void drawtuoying()
{
	if (tuoyingjishu < tuoyingmax + 1)
	{
		for (int i = 0; i < tuoyingmax + 1; i++)
		{
			if (tuoyingX[i] > 0)
			{
				drawAlpha(&bk, tuoyingX[i], tuoyingY[i], &��Ӱ);
			}

		}
	}
	else if (tuoyingjishu == tuoyingmax + 1)
	{
		for (int i = 0; i < tuoyingmax + 1; i++)
		{
			if (tuoyingX[i] > 0)
			{
				drawAlpha(&bk, tuoyingX[i], tuoyingY[i], &��Ӱ);
			}

		} 
		if (tuoyingX[0] > 0 )
		{
			drawAlpha(&bk, tuoyingX[0] - tuoyingxiuzhengx, tuoyingY[0] - tuoyingxiuzhengy, &��Ӱ);
		}
	}
	
}

void rinitialize()
{
	for (int i = 0; i < tuoyingmax + 1; i++)
	{
		tuoyingX[i] = -1;
		tuoyingY[i] = -1;
	}
	timerstart = xiuzheng() - timercd + tuoyingchuxianshijian;
}


double xiuzheng()
{
	return clock() - xiuzhengtime;
}

void ftexiao()
{
	if (ftexiaojishu < 5)
	{
		drawAlpha(&bk, ftexiaoX ,ftexiaoY , &������Ч[ftexiaojishu]);
		drawAlpha(&bk, ftexiaoX - fjuli,ftexiaoY , &������Ч[ftexiaojishu]);
		ftexiaojishu += 1;
	}
}
