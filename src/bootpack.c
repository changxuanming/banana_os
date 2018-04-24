/* bootpack */

#include "bootpack.h"
#include <stdio.h>

extern struct KEYBUF keybuf;

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	char s[40], mcursor[256];
	int mx, my,i;

	init_gdtidt();//n»GDT&IDT
	init_pic();
	io_sti(); /* IDT/PICIn»ß?®¬C°¥?úCPUIf IFiinterrupt flagj*/

	io_out8(PIC0_IMR, 0xf9); /* ?úPIC1a??f(11111001) */
	io_out8(PIC1_IMR, 0xef); /* ?úl?f(11101111) */
	
	init_palette();// n»?FÂ
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);//n»EÊwi
	mx = (binfo->scrnx - 16) / 2;  /* ?ZæÊIS¿?*/
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	/*ÝÁèÊu?¦ê¢ÁèIf?i?ûÌj*/
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
	
	for (;;) {
		io_cli();
		if (keybuf.flag == 0) {
			io_stihlt();//?¢ïÒ÷
		} else {
			i = keybuf.data;
			keybuf.flag = 0;
			io_sti();
			sprintf(s, "%02X", i);
			boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);//õwi
			putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);//?¦
		}
	}
}
