#include "final.h"

//ListNode
ListNode :: ListNode(Vehicle* vehicle,ListNode* next):
					   vehicle(vehicle),next(next){

}

//List
List :: List(const int& seg_id): seg_id(seg_id),count(0){
	head = new ListNode(NULL,tail);
	tail = new ListNode(NULL,head);
}

List :: ~List(){
	delete head;
	delete tail;
}

bool List :: is_empty() const{
	return !(count > 0);
}

void List :: enter(Vehicle* vehicle){
	count++;
	ListNode* new_node = new ListNode(vehicle,tail);
	//cout << "Print from List Enter" << endl;
	tail->next->next = new_node;	//the previously last node will point to the new last node
	tail->next = new_node;	//the tail-node wiil also point to the new last node
	//cout << "2.Print from List Enter" << endl;
}

void List :: exit(){
	if(!is_empty()){
		
		for(ListNode* ptr = head; ptr->next != tail;ptr = ptr->next){
			while(ptr->next->vehicle->is_ready() && (ptr->next->vehicle->get_exit() == seg_id)){ //Using a while loop instead of an if statement,because otherwise it would never delete consecutive nodes
				delete delete_next(ptr->next);	//same fix as pass()		
			}
		}

	}
}

Vehicle* List :: pass(const bool& destroy){
	if(!is_empty()){
		//ListNode* ptr = head;	//initialize with head
		for(ListNode* ptr = head; ptr->next != tail;ptr = ptr->next){
			while(ptr->next->vehicle->is_ready() || (destroy == true)){ //Using a while loop instead of an if statement,because otherwise it would never delete consecutive nodes
				return delete_next(ptr->next);
			}
		}
	}
	return NULL;
}

int List :: get_ready_ones() const {
	int ready_count = 0;
	if(!is_empty()){
		//ListNode* ptr = head;	//initialize with head
		for(ListNode* ptr = head; ptr->next != tail;ptr = ptr->next){
			if(ptr->next->vehicle->is_ready()){
				ready_count++;
			}
		}
	}
	return ready_count;
}

void List :: set_ready(){
	int unready_ones = count - get_ready_ones();
	int unready_ones_that_will_get_ready = unready_ones * percent;

	ListNode* ptr = head->next;
	
	for(int i = 0;i < unready_ones_that_will_get_ready;i++){
		if(!ptr->vehicle->is_ready()){
			ptr->vehicle->set_ready();
		}
		ptr = ptr->next;
	}
}

Vehicle* List :: delete_next(ListNode* wanted_one){
	//cout << "1st print from delete next." << endl;
	if(!is_empty()){
		ListNode* ptr;	//initialize with head
			
		for(ptr = head; ptr->next != wanted_one; ptr = ptr->next);//so we get the previous node than the wanted one

		//cout << "2nd print from delete next." << endl;
	
		count--;
		Vehicle* to_be_returned = ptr->next->vehicle;	//wanted node's vehicle
		ListNode* second_node = ptr->next->next;	//the wanted node's next
		delete ptr->next;	//delete the wanted node
		ptr->next = second_node;	//connect the nodes
		//to_be_returned->set_unready();	//set unready the vehicle that will be returned
		return to_be_returned;
		
	}
	return NULL;
}

int List :: get_count() const{
	return count;
}

void List :: set_percent(const float& percent){
	List :: percent = percent;
}

float List :: percent = 0.5;