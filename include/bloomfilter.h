// 1h Ergasia SysPro - MAVROMMATIS PANAGIOTIS - sdi1800115 //
#ifndef __bloomfilter__
#define __bloomfilter__

int *changeBit(int *A,long k);
int checkBit(int *A, long k);
int **makeBloom(struct Citizen *headCitizen,struct Virus *rootV,int **bArrays, long bloomSize);




#endif