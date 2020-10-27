#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define ROUNDS 3

#define M 8
#define rotl(v,d) (((v)<<(d))|((v)>>(64-(d))))
#define outp(p,d) (out[((p)+(d))%M])
#define step(a,r1,r2) {\
	outp(a,2)^=outp(a,0);\
	outp(a,3)^=outp(a,1);\
	outp(a,2)+=outp(a,1);\
	outp(a,3)+=outp(a,0);\
	outp(a,2)=rotl(outp(a,2),r1);\
	outp(a,3)=rotl(outp(a,3),r2);}

void process_block(uint64_t out[8], uint64_t in[8])
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
		step( 0,22,41); // 16+6 40+1
		step( 2,20,43); // 16+4 40+3
		step( 4,18,45); // 16+2 40+5
		step( 6,16,47); // 16+0 40+7
	}
}

uint64_t input[8]={0,1},output[8]={0};

int main()
{
	for(;;){
		input[0]++;
		process_block(output,input);
		fwrite(output,8,8,stdout);
	}

	return 0;
}
