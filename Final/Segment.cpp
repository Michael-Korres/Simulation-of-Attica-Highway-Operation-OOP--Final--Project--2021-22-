#include "final.h"
//Segment
Segment :: Segment(const int& NSegs,const int& K,const int& capacity,const int id,Segment* previous,Segment* next):
	entrance(random_number_generator_within_range(1,capacity/2),random_number_generator_within_range(1,capacity/2),id,this),vehicles_currently(id),vehicle_capacity(capacity),previous(previous),next(next){
	int exit_interchange;
	int vehicles = random_number_generator_within_range(0,vehicle_capacity);
	
    for(int i = 0;i < vehicles;i++){
		exit_interchange = random_number_generator_within_range(id + 1,NSegs);
		vehicles_currently.enter(new Vehicle(exit_interchange,id));
	}

}

int Segment :: get_no_of_vehicles() const{
    return vehicles_currently.get_count();
}

int Segment :: get_cur_capacity()const{
    return vehicle_capacity - vehicles_currently.get_count();
}

void Segment :: operate(){
    cout << "Some vehicles will exit the highway." << endl;
    vehicles_currently.exit();
    
    cout << "Some others will pass onto the next segment." << endl;
    int next_seg_capacity = next->get_cur_capacity();
    //if(vehicles_currently.get_ready_ones() <= next_seg_capacity){
    while(next_seg_capacity != 0){
        next->insert_vehicle(this->pass());
    }      


    cout << "Some vehicles will enter via the entrance." << endl;
    enter();

    cout << "Some vehicles will get ready to move forward." << endl;
    set_ready();
}

void Segment :: enter(){
    entrance.operate();
}

void Segment :: insert_vehicle(Vehicle* vehicle = NULL){
    vehicles_currently.enter(vehicle);
}

void Segment :: exit(){
    vehicles_currently.exit();
}

Vehicle* Segment :: pass(){
    return vehicles_currently.pass();
}

void Segment :: set_ready(){
    vehicles_currently.set_ready(percent);
}