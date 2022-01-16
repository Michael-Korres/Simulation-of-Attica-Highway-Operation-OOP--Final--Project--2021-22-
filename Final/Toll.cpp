//Toll
#include "final.h"

Toll :: Toll(const int& no_of_cars_initially,const int& interchange,const int& NSegs,const bool& has_a_worker)
			: has_a_worker(has_a_worker){
	int exit_interchange;

	int vehicles = random_number_generator_within_range(no_of_cars_initially,no_of_cars_initially + no_of_cars_initially/2);
	for(int i = 0;i < vehicles;i++){
		exit_interchange = random_number_generator_within_range(interchange + 1,NSegs);
		vehicles_waiting.enter(new Vehicle(exit_interchange));
	}
}

void Toll :: enter_the_toll(const int& no_of_cars_to_enter,const int& interchange,const int& NSegs){
	int exit;
	int vehicles = random_number_generator_within_range(no_of_cars_to_enter,no_of_cars_to_enter + no_of_cars_to_enter/2);
	for(int i = 0;i < vehicles;i++){
		exit = random_number_generator_within_range(interchange + 1,NSegs);
		vehicles_waiting.enter(new Vehicle(exit));
	}
}

Vehicle* Toll :: exit_to_the_seg(){
	return vehicles_waiting.exit();
}

bool Toll :: is_empty() const{
	return vehicles_waiting.is_empty();
}

void Toll :: set_NSegs(const int& NSegs){
    Toll :: NSegs = NSegs;
}

int Toll :: get_count()const{
	return vehicles_waiting.get_count();
}