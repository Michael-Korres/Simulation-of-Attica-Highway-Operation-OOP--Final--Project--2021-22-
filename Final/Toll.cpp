//Toll

#include "final.h"

Toll :: Toll(unsigned const int& no_of_vehicles_initially,unsigned const int& seg_id,const bool& has_a_worker)
			: seg_id(seg_id),has_a_worker(has_a_worker){
	int exit_interchange;

	int vehicles = random_number_generator_within_range(no_of_vehicles_initially,no_of_vehicles_initially + no_of_vehicles_initially/2);
	//cout << "At start this toll has " << vehicles << " vehicles." <<  endl;
	for(int i = 0; i < vehicles; i++){
		//cout << i <<".Print from Toll-Loop" <<  endl;
		exit_interchange = random_number_generator_within_range(seg_id + 1,NSegs);
		vehicles_waiting.enter(new Vehicle(exit_interchange));
	}
	//cout << "Exiting Toll constructor." <<  endl;
	
}


Toll :: ~Toll(){
	while(!is_empty()){
		delete vehicles_waiting.exit();
	}

	cout << "Just destructed a toll." <<  endl;
	
}


void Toll :: enter_the_toll(unsigned const int& no_of_vehicles_to_enter){
	int exit_interchange;
	int vehicles_that_will = random_number_generator_within_range(no_of_vehicles_to_enter,no_of_vehicles_to_enter + no_of_vehicles_to_enter/2);
	for(int i = 0;i < vehicles_that_will;i++){
		exit_interchange = random_number_generator_within_range(seg_id + 1,NSegs);
		vehicles_waiting.enter(new Vehicle(exit_interchange));
	}
	
}

Vehicle* Toll :: exit_to_the_seg(){
	return vehicles_waiting.exit();
}

bool Toll :: is_empty() const{
	return vehicles_waiting.is_empty();
}

void Toll :: set_NSegs(const unsigned int& Nsegs){
    NSegs = Nsegs;
}

int Toll :: get_count()const{
	return vehicles_waiting.get_count();
}

int Toll :: NSegs = 5;