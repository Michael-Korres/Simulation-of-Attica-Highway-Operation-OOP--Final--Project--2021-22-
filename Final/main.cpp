#include "final.h"

using namespace std;


int main(int argc,char* argv[]){	//N,NSegs,K,Percent
	srand(time(NULL));								//	^
													//	|
	int N = atoi(argv[1]);							//	|
	int NSegs = atoi(argv[2]);						//	|
	int K = atoi(argv[3]);							//	|	
	float percent = atof(argv[4]);					//	|
	int segs_cap[NSegs];
	if(argc != NSegs + 5)	//name of the program + 4 args + NSegs * capacities
		for(int i = 0; i < NSegs;i++)segs_cap[i] = i * 30;
	else
		for(int i = 0;i < NSegs;i++)segs_cap[i] = atoi(argv[i + 5]);

    Attica attica(NSegs,K,percent,segs_cap);
	
	for(int i = 0; i < N; i++)
		attica.operate();
	return 0;
}