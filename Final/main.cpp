#include "final.h"

using namespace std;


int main(int argc,char* argv[]){	//N,NSegs,K,Percent
	srand(time(NULL));
	
	int N = atoi(argv[1]);
	int NSegs = atoi(argv[2]);
	int K = atoi(argv[3]);
	float percent = atoi(argv[4]);
	int segs_cap[NSegs];
	for(int i = 0; i < NSegs;i++)segs_cap[i] = i * 50;

    Attica attica(NSegs,K,percent,segs_cap);
	
	for(int i = 0; i < N; i++)
		attica.operate();
	return 0;
}