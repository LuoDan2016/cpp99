#include <stdio.h>
#include <stdint.h>
#include "GB2312_UNI.h"

#define LEN2 (LEN>>1)

int main()
{
	uint8_t buf[4];
	char * filenane ="utf8togb2312.csv";
	FILE *ff;
	ff =fopen(filenane, "ab");
	fprintf(ff, "%s,%s,%s\n","NO.","UNICODE","UTF8");
	for(uint16_t i = 0; i<LEN2;i++)
	{
		uint16_t uni = GB2312_UNI[ 2* i + 1];
		if( (uni >= 0x20) && (uni <= 0x7f) )
		{
			buf[0] = uni & 0x7F;
			fprintf(ff,"%04d,0x%04X,utf8:%02X:%c \n",i, uni, buf[0],buf[0]);
		}
		else if( (uni >= 0x80) && (uni <= 0x07ff) )
		{
			buf[0] = (( uni >> 6) & 0x1f) | 0xC0;
			buf[1] = (  uni       & 0x3F) | 0x80;
			fprintf(ff,"%04d,0x%04X,utf8:%02X-%02X:%c%c\n",i, uni, buf[0], buf[1],buf[0],buf[1]);
		}
		else
		{
			buf[0] = ((uni >> 12) & 0x0f) | 0xE0;
			buf[1] = ((uni >>  6) & 0x3f) | 0x80;
			buf[2] = (uni         & 0x3f) | 0x80;
			fprintf(ff,"%04d,0x%04X,utf8:%02X-%02X-%02X:%c%c%c\n",i, uni, buf[0],buf[1],buf[2],buf[0],buf[1],buf[2]);
		}
	}
	//fflush(ff);
	fclose(ff);
	printf("ok");
	return 0;
}