#include "final.h"
//Segment
Segment :: Segment(const int& NSegs,const int& K,const int& capacity,const int id,Segment* previous,Segment* next):
	NSegs(NSegs),entrance(get_cur_capacity(),id,this),vehicles_currently(id),id(id),vehicle_capacity(capacity),previous(previous),next(next){
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

    int message = 0;    //if nothing is true then we have the case 0

    if(id != NSegs - 1){
        cout << "Some others will pass onto the next segment." << endl;
        
        int next_seg_capacity = next->get_cur_capacity();
        

        if(vehicles_currently.get_ready_ones() > next_seg_capacity)
            message = 1;    //if the ready ones are more than the next seg's capacity then case 1
        
        for(int i = 0; i < next_seg_capacity; i++){
            next->insert_vehicle(this->pass());
        }      
        
        cout << "Some vehicles will enter via the entrance." << endl;

        bool  flag = enter();
        if(flag){
            if(message == 0){
                message = 2;    //if the ready ones are less than the next segs's capacity
            }                   //but all vehicles from the tolls entered then case 2
            else{
                message = 3;    //if both are true then case 3
            }
        }
    }    

    

    cout << "Some vehicles will get ready to move forward." << endl;
    set_ready();

    switch(message){
        case 0:
            cout << "Maintain the safety distances after interchange " << this->id << "." << endl;
            break;
        case 1:
            cout << "Delays after interchange " << this->id << "." << endl;              
            break;
        case 2:
            cout << "Delays in the entrance of interchange " << this->id << "." << endl;
            break;
        case 3:
            cout << "Delays in the entrance of interchange " << this->id << "." << endl;
            cout << "Delays after interchange " << this->id << "." << endl;
    }
}

bool Segment :: enter(){
    return entrance.operate();
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