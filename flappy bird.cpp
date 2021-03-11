#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <graphics.h>

//                  不仅实现了普通的flappy bird 还增加了如下技能：
//                  Q： 成为不可选取状态，可以穿透柱子，但触底还是会死亡。（使用一次扣3分）
//                  W： 让柱子的通道变宽。
//                  E:  刷新qwr的cd 如果有技能正在作用该技能cd不做处理。
//                  R： r冷却好后身后会拖着幻影，按下时可以回到幻影的位置。
//					F:  闪现过一个柱子 80码 召唤师技能。

// 初始背景图 白天、黑夜
IMAGE BK[2];

// 全局画板
IMAGE bk;

// 飞鸟资源 橘、蓝、红
// 三种颜色 三种姿态 暂时只有两种状态 但不知道为什么第三个变量设置成2时最后一个图片会鬼畜
IMAGE BIRD[3][3][3];

// 管道资源 绿、红
IMAGE PIPE[2][2];

// 三种数字字体
IMAGE NUMBER[3][10];

// 奖牌资源
IMAGE MEDAL[4];

// 地面资源
IMAGE LAND;

// 开始游戏按钮
IMAGE PLAY;

// 得分面板
IMAGE PANEL;

// 以下为五种游戏文字
// 游戏结束 游戏预备 游戏标题 游戏提示 最高分
IMAGE OVER;
IMAGE READY;
IMAGE TITLE;
IMAGE TUTORIAL;
IMAGE NEW;

// 结束时状态
IMAGE OVEIMG;





IMAGE q技能图标冷却完成;
IMAGE w技能图标冷却完成;
IMAGE e技能图标冷却完成;
IMAGE r技能图标冷却完成;
IMAGE f技能图标冷却完成;


IMAGE 拖影;
IMAGE 幻影;



// 冷却动画
IMAGE cd[70];
// 闪现动画
IMAGE 闪现特效[6];

IMAGE 注释;


// 是否为白天
int isDay = 0;

// 是否死亡
bool die = false;

// 鸟的颜色
int birdColor = 0;

// 最高分
int best = 0;

// 游戏初始时间
long startTime = 0;

// 游戏基本属性

// 重力加速度
double g = 6.5;

// 管道的移动速度
double vx = 11;
// 鸟的下落速度
double vy = 10;
// 鸟的当前位置
double y = 220;

// 此处被我加了288
const double x = 288 / 2 - (41 + 8) / 2 - 80 + 288;

bool GetControl = false;

// 分数判断
int fen[5];
// 管道的横向坐标          原本是两个被我加到了四个
double pipeX[5];
// 管道的纵向坐标            改了X忘了改Y 调了一个半小时 纪念一下
int pipeY[5];
// 当前得分
int score;
// 鸟的矩形判断区域
int top = 12;
int buttom = 33;
const int left = 10;
const int right = 40;

const int Top = 12;
const int Buttom = 40;

// 奖牌显示位置
const int medalXY[2] = { 0, 0 };

// 陆地坐标
const double landY = 420;
double landX = -20;

// 飞鸟姿态
int pose = 0;

// 飞行间隔
const int diff = 110;

// 管道上补偿
// 这里原来是const int 可能被道具修改故改成int
int pipeUp = -280;
// 管道下补偿
int pipeDown = 140;
// 固定管道补偿
const int pipeup = -280;
const int pipedown = 140;



// 游戏预处理
void start();
// 游戏函数
void game();
// 结束游戏函数
void end();
// 移动函数
void move(long time);
// 绘制函数
void draw(int con);
// 重置画布
void reset();
// 绘制画布
void put();
// 加载资源
void loadRes();
// 根据透明度绘图
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
// 绘制分数
void drawScore(int y, int sc, int dif, int se, int st, int type);
// 绘制管道
void drawPipe();
// 判断鸟死亡
bool isDie();
// 初始化游戏资源
void init();


// 显示技能图标
void drawqability();
void drawwability();
void draweability();
void drawrability();


void qjineng();
// q技能持续时间
int timeqeffect = 5000;
// q技能开始时间
int timeqstart = 0;
// q技能冷却时间 16s
int timeqcd = 16000;




void wjineng();
// w技能持续时间 7s 前2s 不会减小 之后慢慢变小
int timeweffect = 7000;
// w技能开始时间
int timewstart = 0;
// w技能冷却时间 15s
int timewcd = 20000;
// w技能通道扩大范围
int space = 80;
// 实时管道扩大比例
double bilibili;
// 持续时间地面修正
double landYxiuzheng = landY;


void ejineng();
// e技能开始时间
int timeestart = 0;
// e技能冷却时间 20s
int timeecd = 20000;
// e技能激活
bool ejinengjihuo = false;


// r技能持续时间 即拖影对应时间
int timereffect = 1500;
// r技能开始时间
int timerstart = -20000;
// r技能冷却时间
int timercd = 20000;
// 拖影计数
int tuoyingjishu = 0;
// r技能相关参数初始化
void rinitialize();


// f技能
void fjineng();
// f技能使用时间
int timefstart = 0;
// f技能冷却时间 30s
int timefcd = 30000;
// f技能激活瞬间
bool fjinengjihuo = false;
// 闪现距离
int fjuli = 100; 
// 闪现特效
void ftexiao();
// f 特效计数
int ftexiaojishu = 10;

// 记录鸟的位置
int ftexiaoX;
int ftexiaoY;




// 本来应该是150 防止溢出给他多两个
double tuoyingX[252];
double tuoyingY[252];

// 临时一个数字记录键盘操作
long temp1;

// q技能时死亡
bool qisDie();

// 一个间隔隐身用的数字
int yinshenjiange1 = 1;
int yinshenjiange2 = 1;

// 显示技能图标
void drawcd();
// r技能相关
void rjineng();
void drawtuoying();

bool dazhao = false;

// 拖影坐标修正
const int tuoyingxiuzhengx = 15;
const int tuoyingxiuzhengy = 20;

// 拖影最大值
const int tuoyingmax = 100;

// 拖影出现时间 如果是艾克就是4s 也就是4000
const int tuoyingchuxianshijian = 2500;

// 两个拖影之间x的距离
double betweenx;

// 一个在r技能使用期间的临时数字
double lin;

// 一个修正clock的变量
double thistime;
double xiuzhengtime;
double xiuzheng();

int main()
{
	// 游戏开局页面
	init();
	while (true)
	{
		// 游戏初始化
		start();
		// 游戏进行
		game();
		// 显示得分
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


// 游戏预处理
void start()
{
	// 初始化数据
	isDay = rand() % 2;		
	birdColor = rand() % 3;

	// 此处被我加了 288             又加了两个 每两个之间间隔190？
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

	// 游戏初始时间
	clock_t time = xiuzheng();
	// 开场动画
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


// 游戏函数
void game()
{
	// 根据毫秒
	startTime = xiuzheng();
	long time = xiuzheng();

	//cd重置
	timeqstart = xiuzheng() - timeqcd;
	timewstart = xiuzheng() - timewcd;
	timeestart = xiuzheng() - timeecd;
	timerstart = xiuzheng() - timercd + tuoyingchuxianshijian;
	timefstart = xiuzheng() - timefcd;

	//r技能初始化
	rinitialize();
	
	// 地面修正
	landYxiuzheng = landY;
	
	// f特效修正
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
			//q被按下
			if (timeqcd + timeqstart < xiuzheng())
			{
				//cd转好了 q被激活
				timeqstart = xiuzheng();
				//使用q技能要扣3分
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
			//w被按下
			if (timewcd + timewstart < xiuzheng())
			{
				//cd转好了 w被激活
				timewstart = xiuzheng();
				//使用w技能不用扣分
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
			//e被按下
			if (timeecd + timeestart < xiuzheng())
			{
				//cd转好了 e被激活
				timeestart = xiuzheng();
				ejinengjihuo = true;
			}
		}

		else if (temp1 == 5)
		{
			//r被按下
			if (timercd + timerstart < xiuzheng())
			{
				//cd转好了 r被激活
				timerstart = xiuzheng();
				dazhao = true;
			}
		}

		else if (temp1 == 6)
		{
			//f被按下
			if (timefcd + timefstart < xiuzheng())
			{
				//cd转好了 f被激活
				timefstart = xiuzheng();
				fjinengjihuo = true;
			}
		}

		// 移动
		move(xiuzheng() - time);
		time = xiuzheng();
		// 控制
		if (GetControl)
		{
			vy = -26;
		}
		//计算q技能相关
		qjineng();
		//计算w技能相关
		wjineng();
		//计算e技能相关
		ejineng();
		// 计算r技能相关
		rjineng();
		// 计算f技能相关
		fjineng();

		// 在技能冷却时间或者技能没用时间死亡
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

	// 备份此时图片
	drawAlpha(&OVEIMG, 0, 0, &bk);
}


void flush()
{ 
	while (MouseHit())
		GetMouseMsg();
	while (_kbhit())
		_getch();
}

// 结束函数
void end()
{
	// 将面板移出
	startTime = xiuzheng();
	// 重置画板
	reset();
	// 面板从下方移出
	drawPipe();
	drawAlpha(&bk, (int)landX, (int)landY, &LAND);
	drawAlpha(&bk, 0, 0, &OVEIMG);
	drawAlpha(&bk, 175, 150, &PANEL);
	// 根据评分打印奖牌
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
	// 打印当前分
	drawScore(189, score, 16, 16, 390, 2);
	// 写最高分
	int tmp = best;
	if (best < score)
	{
		best = score;
	}
	// 打印最高分
	drawScore(231, best, 16, 16, 390, 2);

	// 如果当前分超过最高分 则显示新分数图标
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
	// 将分数居中显示
	int t = sc;
	int num[8];
	int length = 0;
	do
	{
		num[length] = t % 10;
		length++;
		t /= 10;
	} while (t != 0);

	// 计算出起始坐标
	int s = st - dif * length;
	for (int i = length - 1; i >= 0; i--)
	{
		drawAlpha(&bk, s, y, &NUMBER[type][num[i]]);
		s += se;
	}
}


// 管道、主角、地面移动
void move(long time)
{
	y += time * vy / 100;
	vy += g * time / 100;

	pipeX[0] -= time * vx / 100;
	pipeX[1] -= time * vx / 100;
	pipeX[2] -= time * vx / 100;
	pipeX[3] -= time * vx / 100;
	pipeX[4] -= time * vx / 100;
	
	//拖影向后移动
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



	// 此处不知道修改的对不对
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

	// 以下为修改过后的评分标准 根据过管道数评分
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


	// 以下为原版评分标准 根据时间评分
	//score = (int)(((xiuzheng() - startTime) * vx / 100 - (288 - x + 30)) / 190 + 1);
	//if (score < 0)
	//{
	//	score = 0;
	//}
}

void draw(int con)
{
	// 初始化背景图
	drawAlpha(&bk, 0, 0, &BK[isDay]);
	// 画管道
	drawPipe();
	// 画陆地
	drawAlpha(&bk, (int)landX, (int)landY, &LAND);

	// 画分数
	drawScore(60, score, 13, 26, 288, 0);
	// 画技能图标
	drawcd();

	// 画r技能拖影效果
	drawtuoying();

	// 画鸟
	drawAlpha(&bk, (int)x, (int)y, &BIRD[birdColor][pose][con]);

	// 画闪现特效
	ftexiao();

	// 将背景画到窗口上
	put();
}


// 根据透明度绘图
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	if (dstimg == NULL)
	{
		return;
	}
	// 变量初始化
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = dstimg->getwidth();
	int dst_height = dstimg->getheight();

	// 实现透明贴图  可优化
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

// 画管道 分管道1和管道2
void drawPipe()
{
	// 画管道
	drawAlpha(&bk, (int)pipeX[0], pipeY[0] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[0], pipeY[0] + pipeDown, &PIPE[isDay][1]);
	// 画管道
	drawAlpha(&bk, (int)pipeX[1], pipeY[1] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[1], pipeY[1] + pipeDown, &PIPE[isDay][1]);
	
	
	drawAlpha(&bk, (int)pipeX[2], pipeY[2] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[2], pipeY[2] + pipeDown, &PIPE[isDay][1]);
	
	
	drawAlpha(&bk, (int)pipeX[3], pipeY[3] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[3], pipeY[3] + pipeDown, &PIPE[isDay][1]);

	drawAlpha(&bk, (int)pipeX[4], pipeY[4] + pipeUp, &PIPE[isDay][0]);
	drawAlpha(&bk, (int)pipeX[4], pipeY[4] + pipeDown, &PIPE[isDay][1]);


}



// 判断鸟是否死亡
bool isDie()
{
	// 触底死亡
	if (y + buttom > landYxiuzheng)
		return true;

	//撞到管道
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

// 在隐身(q)的情况下判断鸟是否死亡
bool qisDie()
{
	// 触底死亡
	if (y + buttom > landYxiuzheng)
		return true;

	return false;
}


//重置
void reset()
{
	drawAlpha(&bk, 0, 0, &BK[isDay]);
}


void put()
{
	putimage(0, 0, &bk);

}


// 初始化游戏资源
void init()
{
	// 加载图形资源
	loadRes();
	// 初始化图形界面 这里被我修改了 原本是288，512
	initgraph(576, 512);
	// 初始化随机数种子
	srand((unsigned int)time(NULL));
	// 初始化变量
	best = 0;
	isDay = rand() % 2;
	birdColor = rand() % 3;
	// 游戏初始时间
	clock_t time = xiuzheng();
	// 开场动画
	while (true)
	{
		reset();
		drawAlpha(&bk, 60 + 144, 120, &TITLE);
		drawAlpha(&bk, 125 + 144, 200, &BIRD[birdColor][pose][1]);
		drawAlpha(&bk, 90 + 144, 270, &PLAY);
		drawAlpha(&bk, 0, 400, &注释);
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


// 加载图片资源
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

	loadimage(&BIRD[0][0][2], _T("res\\bird0_0(隐身).png"));
	loadimage(&BIRD[0][1][2], _T("res\\bird0_1(隐身).png"));
	loadimage(&BIRD[0][2][2], _T("res\\bird0_2(隐身).png"));
	loadimage(&BIRD[1][0][2], _T("res\\bird1_0(隐身).png"));
	loadimage(&BIRD[1][1][2], _T("res\\bird1_1(隐身).png"));
	loadimage(&BIRD[1][2][2], _T("res\\bird1_2(隐身).png"));
	loadimage(&BIRD[2][0][2], _T("res\\bird2_0(隐身).png"));
	loadimage(&BIRD[2][1][2], _T("res\\bird2_1(隐身).png"));
	loadimage(&BIRD[2][2][2], _T("res\\bird2_2(隐身).png"));

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




	loadimage(&q技能图标冷却完成, _T("res\\q技能图标冷却完成.png"));
	loadimage(&w技能图标冷却完成, _T("res\\w技能图标冷却完成.png"));
	loadimage(&e技能图标冷却完成, _T("res\\e技能图标冷却完成.png"));
	loadimage(&r技能图标冷却完成, _T("res\\r技能图标冷却完成.png"));
	loadimage(&r技能图标冷却完成, _T("res\\r技能图标冷却完成.png"));
	loadimage(&f技能图标冷却完成, _T("res\\闪现技能图标冷却完成.png"));

	
	loadimage(&拖影, _T("res\\拖影2.png"));
	loadimage(&幻影, _T("res\\幻影.png"));



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

	loadimage(&闪现特效[0], _T("res\\闪现特效\\flash0.png"));
	loadimage(&闪现特效[1], _T("res\\闪现特效\\flash1.png"));
	loadimage(&闪现特效[2], _T("res\\闪现特效\\flash2.png"));
	loadimage(&闪现特效[3], _T("res\\闪现特效\\flash3.png"));
	loadimage(&闪现特效[4], _T("res\\闪现特效\\flash4.png"));

	loadimage(&注释, _T("res\\注释2.png"));

	
}


void drawqability()
{
	drawAlpha(&bk, 100, 450, &q技能图标冷却完成);

	if (timeqcd + timeqstart > xiuzheng())
	{
		drawAlpha(&bk, 100, 450, &cd[int(((timeqcd + timeqstart - xiuzheng()) / timeqcd) * 60)]);
	}



}

void drawwability()
{
	drawAlpha(&bk, 200, 450, &w技能图标冷却完成);
	if (timewcd + timewstart > xiuzheng())
	{
		drawAlpha(&bk, 200, 450, &cd[int(((timewcd + timewstart - xiuzheng()) / timewcd) * 60)]);
	}

	
}

void draweability()
{
	drawAlpha(&bk, 300, 450, &e技能图标冷却完成);

	if (timeecd + timeestart > xiuzheng())
	{
		drawAlpha(&bk, 300, 450, &cd[int(((timeecd + timeestart - xiuzheng()) / timeecd) * 60)]);
	}
}


void drawrability()
{
	drawAlpha(&bk, 400, 450, &r技能图标冷却完成);
	if (timercd + timerstart > xiuzheng())
	{
		drawAlpha(&bk, 400, 450, &cd[int(((timercd + timerstart - xiuzheng()) / timercd) * 60)]);
	}

}

void drawfability()
{
	drawAlpha(&bk, 500, 450, &f技能图标冷却完成);

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
	// 找个时间把下面的写成一个函数
// 在q技能持续时间死亡
// 同时绘制
	if (timeqeffect + timeqstart > xiuzheng())
	{
		if (timeqeffect + timeqstart > xiuzheng() + 1000)
		{
			//q技能处于激活状态 且还有足够时间
			draw(2);
		}
		else
		{
			//q技能快要结束了 开始闪烁
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
		//在q技能激活的情况下进行死亡判定
		die = qisDie();
	}

}

void wjineng()
{
	// w技能 修改管道的上下补偿 使之都增大
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
{//                                     两个等于号！！！
	if (dazhao == false)
	{
		//如果不是出于按下r的刹那
		if (timerstart + timercd < xiuzheng() + tuoyingchuxianshijian)
		{
			//如果r冷却完毕
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
			// 管道移动
			pipeX[0] += betweenx;
			pipeX[1] += betweenx;
			pipeX[2] += betweenx;
			pipeX[3] += betweenx;
			pipeX[4] += betweenx;

			// 地板移动
			landX += betweenx;
			if (landX >-20)
			{
				landX = -44;
			}	

			// 拖影移动
			for (int i = 0; i < tuoyingmax + 1; i++)
			{
				if (tuoyingX[i] != -1)
				{
					tuoyingX[i] += betweenx;
				}
			
			}

			// 鸟移动(只有上下)
			y = tuoyingY[i];

			// 删除拖影幻影
			tuoyingX[i] = -1;

			// 画出来
			draw(2);
		}
//***************************************************************************最后一个减无可减 只能出此下策
		// 管道移动
		pipeX[0] += betweenx;
		pipeX[1] += betweenx;
		pipeX[2] += betweenx;
		pipeX[3] += betweenx;
		pipeX[4] += betweenx;

		// 地板移动
		landX += betweenx;
		if (landX > -20)
		{
			landX = -44;
		}

		// 拖影移动
		for (int i = 0; i < tuoyingmax + 1; i++)
		{
			if (tuoyingX[i] != -1)
			{
				tuoyingX[i] += betweenx;
			}
		}

		// 鸟移动(只有上下)
		y = tuoyingY[0];

		// 删除拖影幻影
		tuoyingX[0] = -1;

		// 画出来
		draw(2);
 //***************************************************************************************************
		// 这里可以加特效
		
		// r回去后速度归零
		vy = 0;
		// r回去后柱子得分变化
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
	// f技能 闪现神技不解释
	if (fjinengjihuo == true)
	{

		ftexiaoX = x ;
		ftexiaoY = y ;

		pipeX[0] -= fjuli;
		pipeX[1] -= fjuli;
		pipeX[2] -= fjuli;
		pipeX[3] -= fjuli;
		pipeX[4] -= fjuli;

		// 地板移动
		landX -= fjuli;
		if (landX > -20)
		{
			landX = -44;
		}
		fjinengjihuo = false;

		//拖影移动
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
				drawAlpha(&bk, tuoyingX[i], tuoyingY[i], &拖影);
			}

		}
	}
	else if (tuoyingjishu == tuoyingmax + 1)
	{
		for (int i = 0; i < tuoyingmax + 1; i++)
		{
			if (tuoyingX[i] > 0)
			{
				drawAlpha(&bk, tuoyingX[i], tuoyingY[i], &拖影);
			}

		} 
		if (tuoyingX[0] > 0 )
		{
			drawAlpha(&bk, tuoyingX[0] - tuoyingxiuzhengx, tuoyingY[0] - tuoyingxiuzhengy, &幻影);
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
		drawAlpha(&bk, ftexiaoX ,ftexiaoY , &闪现特效[ftexiaojishu]);
		drawAlpha(&bk, ftexiaoX - fjuli,ftexiaoY , &闪现特效[ftexiaojishu]);
		ftexiaojishu += 1;
	}
}
