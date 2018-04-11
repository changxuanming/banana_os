/* C语言的函数在汇编中实现 */

void io_hlt(void);
void io_cli(void);
void io_out8(int port,int data); // port：设别号（硬件规定）
int io_load_eflags(void);
void io_store_eflags(int eflags);


void init_palette(void );//初始化调色板
void set_palette(int start, int end, unsigned char *rgb);//设置调色板颜色
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);


#define COL8_BLACK		0
#define COL8_RED		1
#define COL8_GREEN		2
#define COL8_YELLOW		3
#define COL8_BLUE		4
#define COL8_PURPLE		5
#define COL8_blue		6
#define COL8_WHITE		7
#define COL8_GRAY		8
#define COL8_red		9
#define COL8_green		10
#define COL8_yellow		11
#define COL8_cyan		12
#define COL8_purple		13
#define COL8_Lblue		14
#define COL8_gray		15

void HariMain(void)
{
	int xsize, ysize;
	char * vram;
	
	init_palette(); // 初始化调色板设备
	vram = (char*) 0xa0000;//显卡内存地址
	
	xsize=320;
	ysize=200;
	
	boxfill8(vram, xsize, COL8_gray, 20, 20, 100, 100);
	
	for(;;){
		io_hlt();
	}

}

void init_palette(void){
	static unsigned char table_rgb[16*3] = {
		0x00, 0x00, 0x00,	/*  0:黑 */
		0xff, 0x00, 0x00,	/*  1:亮红 */
		0x00, 0xff, 0x00,	/*  2:亮绿 */
		0xff, 0xff, 0x00,	/*  3:亮黄 */
		0x00, 0x00, 0xff,	/*  4:亮蓝 */
		0xff, 0x00, 0xff,	/*  5:亮紫 */
		0x00, 0xff, 0xff,	/*  6:浅亮蓝 */
		0xff, 0xff, 0xff,	/*  7:白 */
		0xc6, 0xc6, 0xc6,	/*  8:亮灰 */
		0x84, 0x00, 0x00,	/*  9:暗红 */
		0x00, 0x84, 0x00,	/* 10:暗绿 */
		0x84, 0x84, 0x00,	/* 11:暗黄 */
		0x00, 0x00, 0x84,	/* 12:暗青 */
		0x84, 0x00, 0x84,	/* 13:暗紫 */
		0x00, 0x84, 0x84,	/* 14:浅暗蓝 */
		0x84, 0x84, 0x84	/* 15:暗灰 */
	};
	set_palette(0,15,table_rgb);
	return;
}

void set_palette(int start, int end, unsigned char *rgb){
	int i, eflags;
	eflags = io_load_eflags();//保存中断标志位
	
	io_cli();	//中断许可标志为0，禁止中断
	io_out8(0x03c8,start);
	for(i = start; i <= end; i++){
		io_out8(0x03c9, rgb[0]/4);
		io_out8(0x03c9, rgb[1]/4);
		io_out8(0x03c9, rgb[2]/4);
		rgb += 3;
	}
	io_store_eflags(eflags);
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c,int x0, int y0, int x1, int y1)
{
	int x, y;
	for(y = y0; y<y1; y++){
		for(x = x0; x<x1; x++){
			/* 根据 0xa0000 + x + y * xsize 计算坐标 8*/
			vram[y*xsize+x]=c;
		}
	}
	return;
}
