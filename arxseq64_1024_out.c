#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define ROUNDS 3

#define M 16
#define rotl(v,d) (((v)<<(d))|((v)>>(64-(d))))
#define outp(p,d) (out[((p)+(d))%M])
#define step(a,r1,r2) {\
	outp(a,2)^=outp(a,0);\
	outp(a,3)^=outp(a,1);\
	outp(a,2)+=outp(a,1);\
	outp(a,3)+=outp(a,0);\
	outp(a,2)=rotl(outp(a,2),r1);\
	outp(a,3)=rotl(outp(a,3),r2);}

void process_block(uint64_t out[16], uint64_t in[16])
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
		step( 0,22,45); // 16+6 48+7
		step( 2,20,43); // 16+4 48+5
		step( 4,18,41); // 16+2 48+3
		step( 6,16,49); // 16+0 48+1
		step( 8,22,45); // 16+6 48+7
		step(10,20,43); // 16+4 48+5
		step(12,18,41); // 16+2 48+3
		step(14,16,49); // 16+0 48+1
	}
}

uint64_t input[16]={0,0},output[16]={0};

void main()
{
	uint64_t i;

	for(;;){
		i=0;
		input[i]++;
		process_block(output,input);
		fwrite(output,8,16,stdout);
	}
}
