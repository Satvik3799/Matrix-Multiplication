#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#ifndef SW
#include "vhdlCStubs.h"
#endif

#define ORDER 16

// Give inputs as 
// Matrix A:
// 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
// 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
// 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
// 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
// ...

// Matrix B:
// 1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
// 2  2  2  2  2  2  2  2  2  2  2  2  2  2  2  2
// 3  3  3  3  3  3  3  3  3  3  3  3  3  3  3  3
// 4  4  4  4  4  4  4  4  4  4  4  4  4  4  4  4
// ...


int main(int argc, char* argv[])
{
	int I, J;
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			storeA(I, J,(uint32_t)  I+1);
			storeB(I, J,(uint32_t)  J+1);
		}
	}
	fprintf(stderr,"Stored A, B\n");
	
	mmul();

	fprintf(stderr,"finished dot_product, results:\n");
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			uint32_t result = loadC (I,J);
			fprintf(stderr,"C[%d][%d] = %d.\n",I, J, result);

		}
	}

	return(0);
}
