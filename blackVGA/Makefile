#文件生成规则

TOOLPATH = ../z_tools/
MAKE	 = $(TOOLPATH)make.exe -r
NASK	 = $(TOOLPATH)nask.exe
EDIMG	 = $(TOOLPATH)edimg.exe
IMGTOL	 = $(TOOLPATH)imgtol.com
COPY	 = copy
DEL 	 = del 

#默认动作

default :
	$(MAKE) img

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst
	
bananaos.sys : bananaos.nas Makefile
	$(NASK) bananaos.nas bananaos.sys bananaos.lst

bananaos.img : ipl10.bin bananaos.sys Makefile
	$(EDIMG)  imgin:../z_tools/fdimg0at.tek \
	  wbinimg src:ipl10.bin len:512 from:0 to:0	\
	  copy from:bananaos.sys to:@: \
	  imgout:bananaos.img
#命令
asm :	
	$(MAKE) ipl10.bin bananaos.sys

img :
	$(MAKE) bananaos.img
	
install: 
	$(MAKE) img
	$(IMGTOL) w a: bananaos.img
	
run : 
	$(MAKE) img
	$(COPY) bananaos.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

clean :
	-$(DEL) ipl10.bin 
	-$(DEL)	ipl10.lst
	-$(DEL) bananaos.sys
	-$(DEL) bananaos.lst

src_only :
	$(MAKE) clean
	-$(DEL) bananaos.img
