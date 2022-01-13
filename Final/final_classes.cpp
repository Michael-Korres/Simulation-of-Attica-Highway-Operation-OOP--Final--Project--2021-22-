#include "final.h"

int random_number_generator_within_range(int min = 0,int max = 100){
	srand(time(NULL));
	int num = rand();
	return (num + min) % (max + 1);
}


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

bool Queue :: is_empty() const{
	return (count > 0);
}

void Queue :: enter(Vehicle* vehicle){
	count++;
	QueueNode* new_node = new QueueNode(vehicle,tail);
	tail->next->next = new_node;	//the previously last node will point to the new last node
	tail->next = new_node;	//the tail-node wiil also point to the new last node
}

// void Queue :: enter(Vehicle** vehicle,const int& vehicle_count){
// 	for(int i = 0;i < vehicle_count; i++){
// 		count++;
// 		QueueNode* new_node = new QueueNode(vehicle[i],tail);
// 		tail->next->next = new_node;	//the previously last node will point to the new last node
// 		tail->next = new_node;	//the tail-node wiil also point to the new last node
// 	}
// }


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

Toll :: Toll(const int& vehicles,const int& K,const int& interchange,const int& segments,const bool& has_a_worker = false): has_a_worker(has_a_worker){
	int exit_interchange;
	for(int i = 0;i < vehicles;i++){
		exit_interchange = random_number_generator_within_range(interchange + 1,segments);
		vehicles_waiting.enter(new Vehicle(exit_interchange,interchange));
	}
}

void Toll :: enter(const int& vehicles,const int& interchange,const int& segments){
	int num;
	for(int i = 0;i < vehicles;i++){
		num = random_number_generator_within_range(interchange + 1,segments);
		vehicles_waiting.enter(new Vehicle(num,interchange));
	}
}

Vehicle* Toll :: exit(){
	return vehicles_waiting.exit();
}

bool Toll :: is_empty() const{
	return vehicles_waiting.is_empty();
}