//Entrance
#include "final.h"

Entrance :: Entrance(unsigned const int& cur_capacity,unsigned const int& seg_id,Segment* seg_ptr):
seg_id(seg_id),entering_segment(seg_ptr),no_of_tolls_with_worker(random_number_generator_within_range(4,9)),no_of_tolls_with_computer(random_number_generator_within_range(3,5)){
								//The no of tolls based in Real-World Attica
	cout << "1st Print from Entrance" << endl;
	cout << "The tolls with worker are " <<  no_of_tolls_with_worker << endl;
	cout << "The tolls with computer are " <<  no_of_tolls_with_computer << endl;

	tolls_with_worker = new Toll*[no_of_tolls_with_worker];
	tolls_with_computer = new Toll*[no_of_tolls_with_computer];

	int least_no_of_cars_in_each = (cur_capacity * 0.4) / no_of_tolls_with_worker;//0.4 of the current capacity / number of tolls with worker
	
	cout << "Each toll with worker will start with at least " << least_no_of_cars_in_each << " vehicles" << endl;

	for(int i = 0; i < no_of_tolls_with_worker;i++){
		cout << "Print from Entrance - Loop" << endl;
		tolls_with_worker[i] = new Toll(least_no_of_cars_in_each,seg_id,true);
	}

	least_no_of_cars_in_each = (cur_capacity * 1.1) / no_of_tolls_with_computer;//1.1 of the current capacity / number of tolls with worker
	
	cout << "Each toll with computer will start with at least " << least_no_of_cars_in_each << " vehicles" << endl;

	
	for(int i = 0; i < no_of_tolls_with_computer;i++){
		tolls_with_computer[i] = new Toll(least_no_of_cars_in_each,seg_id,false);	
	}
}

Entrance :: ~Entrance(){
	delete[] tolls_with_worker;
	delete[] tolls_with_computer;	
}

bool Entrance :: operate(){
	int cars_that_can_enter = entering_segment->get_cur_capacity();
	int count_of_cars_worker = 0;
	int count_of_cars_computer = 0;
	int i = 0;
	int j = 0;
 	Vehicle* temp;
	
	int barrier;
	bool flag;

	if(cars_that_can_enter <= 3 * K){
		barrier = cars_that_can_enter;
		flag = false;
	}
	else{
		barrier = 3 * K;
		flag = true;
	}
	while(count_of_cars_worker + count_of_cars_computer < barrier){
		
		if(count_of_cars_worker < K){
			if(!all_empty_with_worker()){	
				insert_from_tolls(tolls_with_worker,no_of_tolls_with_worker,count_of_cars_worker,i);
					for(int i = 0; i < 2; i++){
						if(!all_empty_with_computer())
						insert_from_tolls(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer,j);
					}
			}
			else{
				if(!all_empty_with_computer()){
						insert_from_tolls(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer,j);
				}
				else{
					break;
				}
			}
		}
		else {
			if(!all_empty_with_computer()){
						insert_from_tolls(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer,j);
			}
			else{
				break;
			}
		}
	}

	if(flag)
		if(count_of_cars_worker + count_of_cars_computer < 3 * K)
			decrease_K();
		else if((count_of_cars_worker == K) && (count_of_cars_computer == 2 * K))
			increase_K();

	bool return_value = (all_empty_with_computer() && all_empty_with_worker()) ? true : false;
	
	enter();

	return return_value;
}

void Entrance :: enter(){
	int seg_cur_capacity = entering_segment->get_cur_capacity();
	int vehicles_to_enter = (seg_cur_capacity * 0.4) / no_of_tolls_with_worker;//0.4 of the current capacity / number of tolls with worker
	for(int i = 0; i < no_of_tolls_with_worker;i++){
		tolls_with_worker[i]->enter_the_toll(seg_cur_capacity,seg_id);
	}

	vehicles_to_enter = (seg_cur_capacity * 1.1) / no_of_tolls_with_computer;//1.1 of the current capacity / number of tolls with computer
	for(int i = 0; i < no_of_tolls_with_computer;i++){
		tolls_with_computer[i]->enter_the_toll(seg_cur_capacity,seg_id);
	}
	
}

void Entrance :: insert_from_tolls(Toll** toll,const int& no_of_tolls,int& count,int& k){
	Vehicle* temp;
	while((temp = toll[k]->exit_to_the_seg()) == NULL){
		k++;
		if(k == no_of_tolls){
			k = 0;
		}
	}

	entering_segment->insert_vehicle(temp);
	count++;
}


void Entrance :: set_NSegs(unsigned const int& NSegs){
	Entrance :: NSegs = NSegs;
	Toll :: set_NSegs(NSegs);
}

int Entrance:: NSegs = 5;

bool Entrance :: all_empty_with_worker() const{
	bool flag = true;
	for(int i = 0; i < no_of_tolls_with_worker;i++){
		if(!tolls_with_worker[i]->is_empty()){
			flag = false;
			break;
		}
	}
	return flag;
}

bool Entrance :: all_empty_with_computer() const{
	bool flag = true;
	for(int i = 0; i < no_of_tolls_with_computer;i++){
		if(!tolls_with_computer[i]->is_empty()){
			flag = false;
			break;
		}
	}
	return flag;
}

void Entrance :: increase_K(){
	K++;
}

void Entrance :: decrease_K(){
	K--;
}