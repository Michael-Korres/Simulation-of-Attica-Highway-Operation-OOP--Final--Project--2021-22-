//Entrance
#include "final.h"

Entrance :: Entrance(const int& no_of_tolls_with_worker,const int& no_of_tolls_with_computer,const int& id,Segment* seg_ptr):
id(id),entering_segment(seg_ptr),no_of_tolls_with_worker(no_of_tolls_with_worker),no_of_tolls_with_computer(no_of_tolls_with_computer){
	for(int i = 0; i < no_of_tolls_with_worker;i++)
		tolls_with_worker[i] = new Toll(100,id,segments,true);
	for(int i = 0; i < no_of_tolls_with_computer;i++)
		tolls_with_computer[i] = new Toll(100,id,segments,false);	
}

Entrance :: ~Entrance(){
	delete[] tolls_with_worker;
	delete[] tolls_with_computer;	
}

void Entrance :: operate(){
	int cars_that_can_enter = entering_segment->get_cur_capacity();
	int count_of_cars_worker = 0;
	int count_of_cars_computer = 0;
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
				insert_from_tolls_with_worker(tolls_with_worker,no_of_tolls_with_worker,count_of_cars_worker);
					for(int i = 0; i < 2; i++){
						if(!all_empty_with_computer())
						insert_from_tolls_with_computer(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer);
					}
			}
			else{
				if(!all_empty_with_computer())
						insert_from_tolls_with_computer(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer);
					
			}
		}
		else {
			if(!all_empty_with_computer())
						insert_from_tolls_with_computer(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer);
				
		}
	}

	if(flag)
		if(count_of_cars_worker + count_of_cars_computer == 3 * K)
			K--;

}

void Entrance :: insert_from_tolls_with_worker(Toll** toll,const int& no_of_tolls,int& count){
	Vehicle* temp;
	static int i = 0;
	
	while((temp = toll[i]->exit()) == NULL){
		i++;
		if(i == no_of_tolls){
			i = 0;
		}
	}

	entering_segment->insert_vehicle(temp);
	count++;
}

void Entrance :: insert_from_tolls_with_computer(Toll** toll,const int& no_of_tolls,int& count){
	Vehicle* temp;
	static int j = 0;
	
	while((temp = toll[j]->exit()) == NULL){
		j++;
		if(j == no_of_tolls){
			j = 0;
		}
	}

	entering_segment->insert_vehicle(temp);
	count++;
}

void Entrance :: set_segments(const int& segments){
	Entrance :: segments = segments;
    Toll :: set_segments(segments);
}

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