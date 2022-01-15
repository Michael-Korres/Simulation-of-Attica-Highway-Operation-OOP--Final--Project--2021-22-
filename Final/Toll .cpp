//Toll
#include "final.h"

Toll :: Toll(const int& under_barrier,const int& interchange,const int& segments,const bool& has_a_worker)
			: has_a_worker(has_a_worker){
	int exit_interchange;
	int vehicles = random_number_generator_within_range(under_barrier,2*under_barrier);
	for(int i = 0;i < vehicles;i++){
		exit_interchange = random_number_generator_within_range(interchange + 1,segments);
		vehicles_waiting.enter(new Vehicle(exit_interchange,interchange));
	}
}

void Toll :: enter(const int& interchange,const int& segments){
	int exit;
	int vehicles = random_number_generator_within_range(0,10);
	for(int i = 0;i < vehicles;i++){
		exit = random_number_generator_within_range(interchange + 1,segments);
		vehicles_waiting.enter(new Vehicle(exit,interchange));
	}
}

Vehicle* Toll :: exit(){
	return vehicles_waiting.exit();
}

bool Toll :: is_empty() const{
	return vehicles_waiting.is_empty();
}

void Toll :: set_segments(const int& segments){
    Toll :: segments = segments;
}

int Toll :: get_count()const{
	return vehicles_waiting.get_count();
}