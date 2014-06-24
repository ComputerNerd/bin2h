#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//compile gcc main.c -Wall -Wextra -O2 -s -o bin2h
int main(int argc,char ** argv){
	if((argc!=3)&&(argc!=4)){
		puts("Usage: in out [array name]");
		return 1;
	}
	FILE*fi,*fo;
	fi=fopen(argv[1],"rb");
	fo=fopen(argv[2],"w");
	fseek(fi,0L,SEEK_END);
	uint32_t sizeh=ftell(fi);
	rewind(fi);
	uint32_t sizel;
	if(argc==4)
		fprintf(fo,"static const uint8_t %s[]={\n",argv[3]);
	else
		fprintf(fo,"static const uint8_t %s[]={\n",argv[1]);
	for(sizel=0;sizel<sizeh-1;++sizel){
		fprintf(fo,"%d,",fgetc(fi));
		if((sizel&127)==127)
			fputc('\n',fo);
	}
	fprintf(fo,"%d};",fgetc(fi));
	fclose(fi);
	fclose(fo);
	return 0;
}
