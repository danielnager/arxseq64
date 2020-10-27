all: arxseq64_512_bm arxseq64_512_fast_bm arxseq64_512_fast_out arxseq64_512_out

arxseq64_512_bm: arxseq64_512_bm.c
	gcc -o arxseq64_512_bm arxseq64_512_bm.c -O4 -Wall

arxseq64_512_fast_bm: arxseq64_512_fast_bm.c
	gcc -o arxseq64_512_fast_bm arxseq64_512_fast_bm.c -O4 -Wall

arxseq64_512_fast_out: arxseq64_512_fast_out.c
	gcc -o arxseq64_512_fast_out arxseq64_512_fast_out.c -O4 -Wall

arxseq64_512_out: arxseq64_512_out.c
	gcc -o arxseq64_512_out arxseq64_512_out.c -O4 -Wall

