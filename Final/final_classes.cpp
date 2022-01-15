#include "final.h"

int random_number_generator_within_range(int min = 0,int max = 10){
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
Queue :: Queue(const int& count_of_vehicles = 0,Vehicle** vehicles_array = NULL){
	head = new QueueNode(NULL,tail);
	tail = new QueueNode(NULL,head);
	count = count_of_vehicles;
	if(vehicles_array != NULL){
		for(int i = 0; i < count_of_vehicles; i++){
			this->enter(vehicles_array[i]);
		}
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
	if(!is_empty()){
		count--;
		Vehicle* to_be_returned = head->next->vehicle;	//first node's vehicle
		QueueNode* second_node = head->next->next;	//the second node
		delete head->next;	//delete first
		head->next = second_node;	//the second now first
		return to_be_returned;
	}
	return NULL;
}


//Toll
Toll :: Toll(const int& K,const int& interchange,const int& segments,const bool& has_a_worker = false)
			: has_a_worker(has_a_worker){
	int exit_interchange;
	int vehicles = random_number_generator_within_range(K,2*K);
	for(int i = 0;i < vehicles;i++){
		exit_interchange = random_number_generator_within_range(interchange + 1,segments);
		vehicles_waiting.enter(new Vehicle(exit_interchange,interchange));
	}
}

void Toll :: enter(const int& interchange,const int& segments){
	int exit;
	int vehicles = random_number_generator_within_range();
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

//Entrance
Entrance :: Entrance(const int& no_of_tolls_with_worker,const int& no_of_tolls_with_computer,const int& id,const int& K):id(id){
	for(int i = 0; i < no_of_tolls_with_worker;i++)
		tolls_with_workers[i] = new Toll(K,id,true,segments);
	for(int i = 0; i < no_of_tolls_with_computer;i++)
		tolls_with_workers[i] = new Toll(K,id,false,segments);	
}

Entrance :: ~Entrance(){
	delete[] tolls_with_workers;
	delete[] tolls_with_workers;	
}

void Entrance :: operate(const int&){
	
}

void Entrance :: set_segments(const int& segs){
	segments = segs;
}

//List
List :: List(const int& vehicles_count = 0,Vehicle** vehicles_array = NULL){
	head = new ListNode(NULL,tail);
	//tail = new ListNode(NULL,head);
	count = vehicles_count;    
	if(vehicles_array != NULL){
		for(int i = 0; i < vehicles_count; i++){
			this->enter(vehicles_array[i]);
		}
	}
}

List :: ~List(){
	while(count != 0){
		exit();
	}
	delete head;
	delete tail;
}

bool List :: is_empty() const{
	return (count > 0);
}

void List :: enter(Vehicle* vehicle){
	count++;
	ListNode* new_node = new ListNode(vehicle,tail);
	tail->next->next = new_node;	//the previously last node will point to the new last node
	tail->next = new_node;	//the tail-node wiil also point to the new last node
}

// void List :: enter(Vehicle** vehicle,const int& vehicle_count){
// 	for(int i = 0;i < vehicle_count; i++){
// 		count++;
// 		ListNode* new_node = new ListNode(vehicle[i],tail);
// 		tail->next->next = new_node;	//the previously last node will point to the new last node
// 		tail->next = new_node;	//the tail-node wiil also point to the new last node
// 	}
// }


Vehicle* List :: exit(const int& vehicle_to_exit = 0){
	if(!is_empty()){
		int i;
		count--;
		ListNode* ptr = head;	//initialize with head
		
		for(i = 0; i < vehicle_to_exit; i++){
			ptr = ptr->next;	//so we get the previous node than the wanted one
		}

		Vehicle* to_be_returned = ptr->next->vehicle;	//wanted node's vehicle
		ListNode* second_node = ptr->next->next;	//the wanted node
		delete ptr->next;	//delete first
		ptr->next = second_node;	//the second now first
		return to_be_returned;
	}
	return NULL;
}


//Attica

Attica :: Attica(const int& NSegs = 3):NSegs(NSegs){
		cout << "Highway in operation." << endl;
		total_count_of_vehicles = 0;
		for(int i = 0; i < NSegs;i++){
			segs[i] = new Segment();
			total_count_of_vehicles += segs[i]->get_no_of_vehicles();
		}



}

Attica :: ~Attica(){
	delete[] segs;
	cout << "Highway has been closed." << endl;
}

void Attica :: operate(){
	total_count_of_vehicles = 0;
	for(int i = NSegs-1; i > 0; i--){
		segs[i]->operate();
		for(int j = NSegs-1; j > 0; j--){
			total_count_of_vehicles += segs[j]->get_no_of_vehicles();
		}
	}
}