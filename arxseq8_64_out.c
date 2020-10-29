#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define ROUNDS 5

//#define M 8
#define rotl(v,d) (((v)<<(d))|((v)>>(8-(d))))
#define outp(p,d) (out[((p)+(d))%8])
#define step(a,r1,r2) {\
	outp(a,2)^=outp(a,0);\
	outp(a,3)^=outp(a,1);\
	outp(a,2)+=outp(a,1);\
	outp(a,3)+=outp(a,0);\
	outp(a,2)=rotl(outp(a,2),r1);\
	outp(a,3)=rotl(outp(a,3),r2);}

void process_block(uint8_t out[8], uint8_t in[8])
{
	int i;
	
	for(i=0;i<8;i++)
		out[i]=in[i];
/*
	xor 2<-0
	xor 3<-1
	add 2<-1
	add 3<-0
	rot 2
	rot 3
*/


	for(i=0;i<ROUNDS;i++){
		step( 0,1,6); 
		step( 2,3,4); 
		step( 4,5,2); 
		step( 6,7,1); 
	}
}

uint8_t input[8]={0,0},output[8]={0};

int main()
{
	int i;

	for(;;){
		i=0;
		input[i]++;
		while(input[i]==0){
			i++;
			input[i]++;
		}
		process_block(output,input);
		fwrite(output,1,8,stdout);
	}

	return 0;
}
