#include "final.h"
//Segment
Segment :: Segment(const int& vehicle_capacity,const int& K,const int seg_id,Segment* previous,Segment* next): entrance(vehicle_capacity,K,seg_id,this),vehicles_currently(seg_id),seg_id(seg_id),vehicle_capacity(vehicle_capacity),previous(previous),next(next){
    
    int exit_interchange;
	int vehicles = random_number_generator_within_range(0,vehicle_capacity/4);
	
    for(int i = 0;i < vehicles;i++){
        exit_interchange = random_number_generator_within_range(seg_id + 1,NSegs);
        
        vehicles_currently.enter(new Vehicle(exit_interchange,seg_id));
	}
    // cout << "Just constructed a segment." <<  endl;
	
}

Segment :: ~Segment(){
    Vehicle* temp;
    while((temp = vehicles_currently.pass(true)) != NULL){
        delete temp;
	}

	// cout << "Just destructed a segment." <<  endl;
	
}

int Segment :: get_no_of_vehicles() const{
    return vehicles_currently.get_count();
}

int Segment :: get_cur_capacity()const{
    return vehicle_capacity - vehicles_currently.get_count();
}

void Segment :: operate(){
    // cout << "Some vehicles will exit the highway." << endl;
    
    if(seg_id != 0)vehicles_currently.exit();

    int message = 0;    //Case 0: The message: "Maintain distances" | if none of the other cases is true

    if((seg_id != NSegs - 1)){
        // cout << "Some others will pass onto the next segment." << endl;
        
        int next_seg_capacity = next->get_cur_capacity();
 
        if(vehicles_currently.get_ready_ones() > next_seg_capacity){
            message = 1;    //Case 1: The message : "Delays after Interchange" | Some of the ready ones will not pass
        
            // cout << "the ready ones are more than the next seg's capacity." << endl;
        
            Vehicle* temp;
            for(int i = 0; i < next_seg_capacity; i++){
                temp = this->pass();
                if(temp != NULL){
                    next->insert_vehicle(temp);
                }
            }

        }
        else{

            // cout << "the ready ones are fewer than the next seg's capacity." << endl;
            

            Vehicle* temp;
            
            // cout << "Currently ready ones:" << vehicles_currently.get_ready_ones() << endl;

            while(vehicles_currently.get_ready_ones() != 0){
                temp = this->pass();
                if(temp != NULL){
                    next->insert_vehicle(temp);
                }
            }
        }

        // cout << "Some vehicles will enter via the entrance." << endl;

        bool  flag = enter();
        if(flag){
            if(message == 0){
                message = 2;   //Case 2: Case 1 is false | which means:
                                //the ready ones are less than the next segs's capacity and they shall pass
            }                   //but the K conditions were true
            else{
                message = 3;    //Case 3: if both Case 1 & Case 2 are true
            }
        }
    }    
    

    // cout << "Some vehicles will get ready to move forward." << endl;
    set_ready();

    switch(message){
        case 0:
            cout << "Maintain the safety distances after interchange " << this->seg_id << "." << endl;
            break;
        case 1:
            cout << "Delays after interchange " << this->seg_id << "." << endl;              
            break;
        case 2:
            cout << "Delays in the entrance of interchange " << this->seg_id << "." << endl;
            break;
        case 3:
            cout << "Delays in the entrance of interchange " << this->seg_id << "." << endl;
            cout << "Delays after interchange " << this->seg_id << "." << endl;
    }
}

bool Segment :: enter(){
    unsigned const int& cur_capacity = get_cur_capacity();
    return entrance.operate(cur_capacity);
}

void Segment :: insert_vehicle(Vehicle* vehicle){
    vehicles_currently.enter(vehicle);
}

void Segment :: exit(){
    vehicles_currently.exit();
}

Vehicle* Segment :: pass(){
    Vehicle* temp = NULL;
    while((temp = vehicles_currently.pass()) == NULL);
    return temp;
}

void Segment :: set_ready(){
    vehicles_currently.set_ready();
}

void Segment :: set_percent(const float& percent){
    Segment:: percent = percent;
    List :: set_percent(percent);
}

float Segment :: percent = 0.5;

void Segment :: set_NSegs(const int& NSegs){
    Segment:: NSegs = NSegs;
    Entrance ::set_NSegs(NSegs);
}

int Segment :: NSegs = 5;

unsigned int Segment :: get_ready_ones() const {
    return vehicles_currently.get_ready_ones();
}

void Segment:: set_pointers(Segment* previous,Segment* next){
    
    this->previous = previous;
    this->next = next;

}