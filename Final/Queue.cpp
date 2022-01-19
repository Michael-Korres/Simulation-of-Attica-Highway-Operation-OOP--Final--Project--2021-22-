#include "final.h"

//QueueNode
QueueNode :: QueueNode(Vehicle* vehicle,QueueNode* next):
					   vehicle(vehicle),next(next){

}
//Queue
Queue :: Queue(){
	// cout << "1st Print of Queue" << endl;
	head = new QueueNode(NULL,tail);
	// cout << "head:" << head << endl;
	tail = new QueueNode(NULL,head);
	count = 0;
}

Queue :: ~Queue(){
	while(count > 0){
		exit();
	}
	delete head;
	delete tail;
}

bool Queue :: is_empty() const{
	return !(count > 0);
}

void Queue :: enter(Vehicle* vehicle){
	QueueNode* new_node = new QueueNode(vehicle,tail);

	// cout << "1st Print from Queue :: enter()" << endl;


	if(is_empty()){
		// cout << "head:" << head << endl;
		// cout << "new_node:" << new_node << endl;

		head->next = new_node;	//Problematic Command
	}

	// cout << "2nd Print from Queue :: enter()" << endl;

	count++;
	
	tail->next->next = new_node;	//the previously last node will point to the new last node
	tail->next = new_node;	//the tail-node wiil also point to the new last node
}


Vehicle* Queue :: exit(){
	if(!is_empty()){
		count--;
		if(is_empty()){
			tail->next = head;
		}
		Vehicle* to_be_returned = head->next->vehicle;	//first node's vehicle
		QueueNode* second_node = head->next->next;	//the second node
		delete head->next;	//delete first
		head->next = second_node;	//the second now first
		return to_be_returned;
	}
	return NULL;
}

int Queue :: get_count() const{
	return count;
}