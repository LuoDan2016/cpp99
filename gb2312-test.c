#include <stdio.h>
#include <stdint.h>
#include "GB2312_UNI.h"

uint16_t binarysearch(uint16_t uni);
//char blank[176]={0};
uint16_t unicode;
uint16_t gb2312;
uint32_t i;
int main()
{
	//uint32_t i=0;
	char *filename ="u312.txt";
	FILE *ff;
	//char buf[2];
	ff =fopen(filename, "w+");
	if(!ff)
	{	
	    printf("Cannot found File!!\n");
	    return -1;
	}
	
	//fwrite(blank,176,1,ff);
	#if 0
	//uint32_t i=0;
	for(uint16_t utf89 =0xC2A2; utf89<=0xD1BF;utf89++)
	{
	    uint8_t utf1=	(utf89>>8) &0xff;
	    uint8_t utf2=	 (utf89   & 0xff);
	    unicode=	((utf1&0x1f)<<6) |	(utf2&0x3f);
	    printf("%04x\t",unicode);
	    gb2312=binarysearch(unicode);
	    printf("%04X\n",gb2312);
	    //buf[0]=	(sjis >>8) & 0xff;
	    //buf[1]=	sjis & 0xff;
	   //fwrite(buf,2, 1,ff); 
	   //fprintf(ff,"%08x--%04x--%04x---%04x--%c%c\n", 0xb0+i*2,utf89,unicode, gb2312,utf1, utf2);
	    i++;
	
	}
	
	#endif
	
	
		#if 1
	//uint32_t io=0;
	for(uint32_t utf8 =	0xe28090; utf8<0xe2c000;utf8++)
	{
	    uint8_t utf1=	(utf8>>16) &0xff;
	    uint8_t utf2=	(utf8>>8) & 0xff;
	    uint8_t utf3=	utf8 & 0xff;
	    
	    unicode=	((utf1&0x0f)<<12)|((utf2&0x3f)<<6)|(utf3&0x3f);
	    uint16_t gb2312=	binarysearch(unicode);
	    //buf[0]=	(gb2312>>8) & 0xff;
	    //buf[1]=	gb2312 & 0xff;
	   //fwrite(buf,2, 1,ff); 
	   fprintf(ff,"%08x--%06x--%04x---%04x--%c%c%c \n", 0x1eec+i*2,utf8,unicode, gb2312,utf1, utf2,utf3);
	    i++;
	
	}
	
	#endif
	
	//fflush(ff);
	fclose(ff);
	printf("ok");
	return 0;
}


uint16_t binarysearch(uint16_t uni)
{
	uint16_t  s=	0;
	uint16_t  e=	(LEN>>1)-1;
	
	while(s <=e)
	{
		uint16_t mid =((e-s)>>1)+s;
		if(GB2312_UNI[mid*2+1]>uni)
		{
			e =	mid-1;
		}
		else if(GB2312_UNI[mid*2+1]<uni)
		{
			s =	mid+1;
		}
		else
		{
			return GB2312_UNI[2*mid];
	    }
	}
	return 0x0000;
}