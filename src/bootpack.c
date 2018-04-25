/* bootpack */

#include "bootpack.h"
#include <stdio.h>

extern struct FIFO8 keyfifo;

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	char s[40], mcursor[256], keybuf[32];
	int mx, my,i;

	init_gdtidt();//初始化GDT&IDT
	init_pic();
	io_sti(); /* IDT/PIC的初始化已?完成，于是?放CPU的中断 IF（interrupt flag）*/
	
	fifo8_init(&keyfifo, 32, keybuf);
	io_out8(PIC0_IMR, 0xf9); /* ?放PIC1和??中断(11111001) */
	io_out8(PIC1_IMR, 0xef); /* ?放鼠?中断(11101111) */
	
	init_palette();// 初始化?色板
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);//初始化界面背景
	mx = (binfo->scrnx - 16) / 2;  /* ?算画面的中心坐?*/
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	/*在特定位置?示一个特定的像素?（?方体）*/
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
	
	for (;;) {
		io_cli();
		if (fifo8_status(&keyfifo) == 0) {
			io_stihlt();
		} else {
			i = fifo8_get(&keyfifo);
			io_sti();
			sprintf(s, "%02X", i);
			boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);//数字快背景
			putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);//?示数字
		}
	}
}
