/* 告诉C编译器，有一个函数在别的文件里 */

void io_hlt(void);
void write_mem8(int addr , int data);

/* 是函数声明却不用{}，而用;，这表示的意思是：
	函数在别的文件中，你自己找一下 */

void HariMain(void)
{
	int i; //4Byte 变量
	char *p; //用于装载8bit的象素点色彩
	for (i = 0xa0000; i<=0xaffff; i++){
		//write_mem8(i, i & 0x0f);
		//转换方法
		p = i;
		*p = i & 0x0f;
	}

	for(;;){
		io_hlt();
	}

}

