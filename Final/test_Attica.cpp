#include "final.h"

using namespace std;


int main(int argc,char* argv[]){
	srand(time(NULL));
	int N = 2;
	int NSegs = 5;
	int K = 20;
	float percent = 0.5;
	int segs_cap[NSegs];
	for(int i = 0; i < NSegs;i++)segs_cap[i] = i * 50;

    Attica attica(NSegs,K,percent,segs_cap);
	attica.operate();
	attica.operate();

	return 0;
}