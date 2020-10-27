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

uint64_t input[8]={0},output[4096]={0};

void process_state(uint64_t out[8], uint64_t in[8])
{
	int i;
	
	for(i=0;i<8;i++)
		out[i]=in[i];
/*
	Order of operations:

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
	}
}

uint64_t seek_random(uint64_t i)
{
	if(i%8==0){
		input[0]=i+1;
		process_state(output,input);
	}
	return output[i%8];
}

int main()
{
	int i;
	clock_t c;

	printf("Generating 2^30 bytes (%d rounds)\n",ROUNDS);
	printf("CLOCKS_PER_SEC:%ld\n",CLOCKS_PER_SEC);

	c=clock();

	for(i=1;i<(1<<24)+1;i++){ // generate 2^30 bytes, 2^24 buffers of 64 bytes
		input[0]=i;
		process_state(output+(i*8)%4096,input);
	}

	c=clock()-c;

	printf("Raw block generation to memory:\n");
	printf("  %f seconds\n",c/(double)CLOCKS_PER_SEC);
	printf("  %.3f GB/second\n",CLOCKS_PER_SEC/(double)c);

	c=clock();

	for(i=0;i<1<<27;i++)  // generate 2^30 bytes, 2^27 64-bit words
		seek_random(i);

	c=clock()-c;

	printf("Extracting 64-bit words:\n");
	printf("  %f seconds\n",c/(double)CLOCKS_PER_SEC);
	printf("  %.3f GB/second\n",CLOCKS_PER_SEC/(double)c);

	return 0;
}
