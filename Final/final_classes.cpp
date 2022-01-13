#include "final.h"

//Vehicle
Vehicle :: Vehicle(const int& interchange = 0,const int& seg = -1,const bool& move_state = false):
		exit_interchange(interchange),curr_seg(seg),ready_to_exit(move_state)
{
	cout << "Just constructed a vehicle." << endl; 
}

Vehicle :: ~Vehicle(){
	cout << "Just destructed a vehicle." << endl; 
}

int Vehicle :: get_exit() const{
	return exit_interchange;
}

bool Vehicle :: get_if_ready() const{
	return ready_to_exit;
};


void Vehicle :: set_ready(){
	ready_to_exit = true;
}

void Vehicle :: set_unready(){
	ready_to_exit = false;
}


//QueueNode
QueueNode :: QueueNode(Vehicle* vehicle = NULL,QueueNode* next = NULL):
					   vehicle(vehicle),next(next){

}


//Queue
Queue :: Queue(const int& vehicles = 0,Vehicle** vehicles_array = NULL){
	head = new QueueNode(NULL,tail);
	tail = new QueueNode(NULL,head);
	count = vehicles;    
	for(int i = 0; i < vehicles; i++){
		this->enter(vehicles_array[i]);
	}
}

Queue :: ~Queue(){
	while(count != 0){
		exit();
	}
	delete head;
	delete tail;
}

bool Queue :: is_empty(){
	return (count > 0);
}

void Queue :: enter(Vehicle* vehicle){
	count++;
	QueueNode* new_node = new QueueNode(vehicle,tail);
	tail->next->next = new_node;	//the previously last node will point to the new last node
	tail->next = new_node;	//the tail-node wiil also point to the new last node
}

Vehicle* Queue :: exit(){
	if(is_empty()){
		count--;
		Vehicle* to_be_returned = head->next->vehicle;	//first node's vehicle
		QueueNode* second_node = head->next->next;	//the second node
		delete head->next;	//delete first
		head->next = second_node;	//the second now first
		return to_be_returned;
	}
	return NULL;
}