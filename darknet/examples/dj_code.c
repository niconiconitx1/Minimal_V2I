// [niconeco]
#include "darknet.h"




void dj_python(){
	system("python ./python/take_oneshot_gray.py");
}


// char darknet_to_client_command[256];
void write_command(char *log_content){

	FILE *fp_w;
	printf("read log : %s\n",log_content );
	fp_w = fopen("./darknet/Log/log.txt","a+");
	fprintf(fp_w,"%s\n",log_content );
	// fputs(log_content,fp_w);
	fclose(fp_w);


}
