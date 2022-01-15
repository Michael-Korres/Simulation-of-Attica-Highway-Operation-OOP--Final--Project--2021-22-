#include "final.h"

int random_number_generator_within_range(int min,int max){
	srand(time(NULL));
	int num = rand();
	return (num + min) % (max + 1);
}


//List
List :: List(const int& id): id(id),count(0){
	head = new ListNode(NULL,tail);
	//tail = new ListNode(NULL,head);
}

List :: ~List(){
	while(count != 0){
		//exit();
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


void List :: exit(){
	if(!is_empty()){
		//ListNode* ptr = head;	//initialize with head
		for(ListNode* ptr = head; ptr->next!= NULL;ptr = ptr->next){
			if(ptr->next->vehicle->get_if_ready() && (ptr->next->vehicle->get_exit() == id)){
				delete_next(ptr);
			}
		}
	}
}

Vehicle* List :: pass(){
	if(!is_empty()){
		//ListNode* ptr = head;	//initialize with head
		for(ListNode* ptr = head; ptr->next!= NULL;ptr = ptr->next){
			if(ptr->next->vehicle->get_if_ready()){
				return delete_next(ptr);
			}
		}
	}
}

int List :: get_ready_ones() const {
	int ready_count = 0;
	if(!is_empty()){
		//ListNode* ptr = head;	//initialize with head
		for(ListNode* ptr = head; ptr->next != NULL;ptr = ptr->next){
			if(ptr->next->vehicle->get_if_ready()){
				ready_count++;
			}
		}
	}
	return ready_count;
}

void List :: set_ready(const int& percent){
	int unready_ones = count - get_ready_ones();
	int unready_ones_that_will_get_ready = unready_ones * percent;

	ListNode* ptr = head->next;
	
	for(int i = 0;i < unready_ones_that_will_get_ready;i++){
		if(!ptr->vehicle->get_if_ready())
			ptr->vehicle->set_ready();
		ptr = ptr->next;
	}
}

Vehicle* List :: delete_next(ListNode* wanted_one){
	if(!is_empty()){
		int i;
		count--;
		
		ListNode* ptr;	//initialize with head
		
		for(ptr = head; ptr->next != wanted_one; ptr = ptr->next){
			ptr = ptr->next;	//so we get the previous node than the wanted one
		}

		Vehicle* to_be_returned = ptr->next->vehicle;	//wanted node's vehicle
		ListNode* second_node = ptr->next->next;	//the wanted node's next
		delete ptr->next;	//delete the wanted node
		ptr->next = second_node;	//connect the nodes
		to_be_returned->set_unready();	//set unready the vehicle that will be returned
		return to_be_returned;
	}
	return NULL;
}

