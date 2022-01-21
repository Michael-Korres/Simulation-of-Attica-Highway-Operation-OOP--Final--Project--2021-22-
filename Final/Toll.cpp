//Toll

#include "final.h"

Toll :: Toll(unsigned const int& no_of_vehicles_initially,unsigned const int& seg_id)
			: seg_id(seg_id),vehicles_waiting(){
	int exit_interchange;
	//cout << "Just Constructed a toll" << endl;
	int vehicles = random_number_generator_within_range(no_of_vehicles_initially,no_of_vehicles_initially + no_of_vehicles_initially/2);
	
	for(int i = 0; i < vehicles; i++){
		exit_interchange = random_number_generator_within_range(seg_id + 1,NSegs);
		vehicles_waiting.enter(new Vehicle(exit_interchange));
	}
	
}



Toll :: ~Toll(){
	
	//delete vehicles_waiting;

	//cout << "Just destructed a toll." <<  endl;
	
}


void Toll :: enter_the_toll(unsigned const int& no_of_vehicles_to_enter){
	int exit_interchange;
	int vehicles_that_will = random_number_generator_within_range(no_of_vehicles_to_enter,no_of_vehicles_to_enter + no_of_vehicles_to_enter/2);
	for(int i = 0;i < vehicles_that_will;i++){
		exit_interchange = random_number_generator_within_range(seg_id + 1,NSegs-1);
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

bool Toll :: has_a_worker() const{
	return false;
}

//Specializations of Toll
Toll_with_worker :: Toll_with_worker(unsigned const int& no_of_vehicles_initially,unsigned const int& seg_id):Toll(no_of_vehicles_initially,seg_id){
	// cout << " Just constructed Toll with worker" << endl;
}


Toll_with_worker :: ~Toll_with_worker(){
	// cout << "Just destructed Toll with worker" << endl;
}


bool Toll_with_worker :: has_a_worker() const{
	return true;	
}



Toll_with_computer :: Toll_with_computer(unsigned const int& no_of_vehicles_initially,unsigned const int& seg_id):Toll(no_of_vehicles_initially,seg_id){
	// cout << "Just constructed Toll with computer" << endl;	
}

Toll_with_computer :: ~Toll_with_computer(){
	// cout << "Just destructed Toll with computer" << endl;
}

bool Toll_with_computer :: has_a_worker() const{
	return false;
}