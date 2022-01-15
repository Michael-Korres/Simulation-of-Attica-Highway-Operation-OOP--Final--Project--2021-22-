//Entrance
#include "final.h"

Entrance :: Entrance(const int& no_of_tolls_with_worker,const int& no_of_tolls_with_computer,const int& id,Segment* seg_ptr):id(id),entering_segment(seg_ptr){
	for(int i = 0; i < no_of_tolls_with_worker;i++)
		tolls_with_workers[i] = new Toll(id,true);
	for(int i = 0; i < no_of_tolls_with_computer;i++)
		tolls_with_workers[i] = new Toll(id,false);	
}

Entrance :: ~Entrance(){
	delete[] tolls_with_workers;
	delete[] tolls_with_workers;	
}

void Entrance :: operate(const int&){
	
}

void Entrance :: set_segments(const int& segments){
	Entrance :: segments = segments;
    Toll :: set_segments(segments);
}
