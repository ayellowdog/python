//CUDA_Transfer.cpp

#include "cuda.h"

#include "stdafx.h"

 

extern "C" int runtest(long *adbuffer);

 

int run_cuda(long *adbuffer)

{

	//runtest(adbuffer[]);
	return runtest(adbuffer);
       
}

