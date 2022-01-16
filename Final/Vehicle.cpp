//Vehicle
#include "final.h"

Vehicle :: Vehicle(const int& exit_interchange,const int& curr_seg,const bool& move_state):
		exit_interchange(exit_interchange),curr_seg(curr_seg),ready_to_exit(move_state)
{
	cout << "Just constructed a vehicle.";
	if(this->curr_seg == -1){
		cout << "It is going to enter the highway.";
	}
	else{
		cout << "It is currently positioned in the segment no." << this->curr_seg << " of the highway.";
	}
	cout << "It is headed to the interchange no." << this->exit_interchange << "." << endl;
}

Vehicle :: ~Vehicle(){
	cout << "Just destructed a vehicle." << endl; 
}

int Vehicle :: get_exit() const{
	return exit_interchange;
}

bool Vehicle :: is_ready() const{
	return ready_to_exit;
};


void Vehicle :: set_ready(){
	ready_to_exit = true;
}

void Vehicle :: set_unready(){
	ready_to_exit = false;
}

void Vehicle :: set_segment(const int& seg_id){
	this->curr_seg = seg_id;
}

int Vehicle :: get_curr_segment() const{
	return this->curr_seg;
}