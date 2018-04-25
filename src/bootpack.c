/* bootpack */

#include "bootpack.h"
#include <stdio.h>

extern struct FIFO8 keyfifo;

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	char s[40], mcursor[256], keybuf[32];
	int mx, my,i;

	init_gdtidt();//���n��GDT&IDT
	init_pic();
	io_sti(); /* IDT/PIC�I���n����?�����C����?��CPU�I���f IF�iinterrupt flag�j*/
	
	fifo8_init(&keyfifo, 32, keybuf);
	io_out8(PIC0_IMR, 0xf9); /* ?��PIC1�a??���f(11111001) */
	io_out8(PIC1_IMR, 0xef); /* ?���l?���f(11101111) */
	
	init_palette();// ���n��?�F��
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);//���n���E�ʔw�i
	mx = (binfo->scrnx - 16) / 2;  /* ?�Z��ʓI���S��?*/
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	/*�ݓ���ʒu?���꘢����I���f?�i?���́j*/
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
			boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);//�������w�i
			putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);//?������
		}
	}
}
