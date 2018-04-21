/* bootpack */

#include "bootpack.h"
#include <stdio.h>

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	char s[40], mcursor[256];
	int mx, my;

	init_gdtidt();//n»GDT&IDT
	init_palette();// n»?FÂ
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);//n»EÊwi
	mx = (binfo->scrnx - 16) / 2;  /* æÊ¿?I?Z */
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	/*ÝÁèÊu?¦ê¢ÁèIf?i?ûÌj*/
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

	for (;;) {
		io_hlt();
	}
}
