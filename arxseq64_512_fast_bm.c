#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define ROUNDS 2

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

uint64_t out[8]={0};

static inline void process_state(uint64_t buf[8])
{
	int i;
	static uint64_t idx=1;
	
/*
	Order of operations:

	xor 2<-0
	xor 3<-1
	add 2<-1
	add 3<-0
	rot 2
	rot 3
*/

	out[0]=idx++;

	for(i=0;i<ROUNDS;i++){
		step( 0,22,45); // 16+6 48+7
		step( 2,20,43); // 16+4 48+5
		step( 4,18,41); // 16+2 48+3
		step( 6,16,49); // 16+0 48+1
	}

	for(i=0;i<8;i++)
		buf[i]=out[i];
}

uint64_t buffer[4096];

int main()
{
	int i;
	clock_t c;

	printf("Generating 2^30 bytes (%d rounds)\n",ROUNDS);
	printf("CLOCKS_PER_SEC:%ld\n",CLOCKS_PER_SEC);

	c=clock();

	for(i=0;i<(1<<24);i++) // generate 2^30 bytes, 2^24 buffers of 64 bytes
		process_state(&buffer[(i*8)%4096]);

	c=clock()-c;
	printf("Raw block generation (writting to memory):\n");
	printf("%f seconds\n",c/(double)CLOCKS_PER_SEC);
	printf("%.3f GB/second\n",CLOCKS_PER_SEC/(double)c);

	return 0;
}
