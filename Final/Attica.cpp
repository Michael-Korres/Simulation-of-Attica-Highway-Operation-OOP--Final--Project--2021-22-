//Attica
#include "final.h"

Attica :: Attica(const int& NSegs,const int& K,const float& percent,int* segs_capacity):NSegs(NSegs),percent(percent){
		cout << "Highway in operation." << endl;
		total_count_of_vehicles = 0;
		for(int id = 1; id < NSegs;id++){
			if(id == 1){
				segs[0] = new Segment(NSegs,K,segs_capacity[0],0,NULL,segs[1]);
				total_count_of_vehicles += segs[0]->get_no_of_vehicles();
			}
			else if(id == NSegs - 1){
				segs[NSegs - 1] = new Segment(NSegs,K,segs_capacity[NSegs - 1],NSegs - 1,segs[NSegs - 2],NULL);
				total_count_of_vehicles += segs[NSegs - 1]->get_no_of_vehicles();
				break;
			}
			segs[id] = new Segment(NSegs,K,segs_capacity[id],id,segs[id - 1],segs[id + 1]);
			total_count_of_vehicles += segs[id]->get_no_of_vehicles();
		
		}
		Segment :: set_percent(percent);

}

Attica :: ~Attica(){
	delete[] segs;
	cout << "Highway has been closed." << endl;
}

void Attica :: operate(){
	total_count_of_vehicles = 0;
	for(int i = NSegs-1; i > 0; i--){
		segs[i]->operate();
		for(int j = NSegs-1; j > 0; j--){
			total_count_of_vehicles += segs[j]->get_no_of_vehicles();
		}
	}
}