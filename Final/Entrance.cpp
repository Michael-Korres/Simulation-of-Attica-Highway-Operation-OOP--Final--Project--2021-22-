//Entrance
#include "final.h"

Entrance :: Entrance(unsigned const int& cur_capacity,unsigned const int& K,unsigned const int& seg_id,Segment* seg_ptr):
 K(K),seg_id(seg_id),entering_segment(seg_ptr),no_of_tolls_with_worker(random_number_generator_within_range(4,9)),no_of_tolls_with_computer(random_number_generator_within_range(3,5)){
								//The no of tolls based in Real-World Attica
	// cout << "The tolls with worker are " <<  no_of_tolls_with_worker << endl;
	// cout << "The tolls with computer are " <<  no_of_tolls_with_computer << endl;

	tolls_with_worker = new Toll*[no_of_tolls_with_worker];
	tolls_with_computer = new Toll*[no_of_tolls_with_computer];

	int least_no_of_vehicles_in_each = (cur_capacity * 0.4) / no_of_tolls_with_worker;//0.4 of the current capacity / number of tolls with worker
	
	// cout << "Each toll with worker will start with at least " << least_no_of_vehicles_in_each << " vehicles" << endl;

	for(int i = 0; i < no_of_tolls_with_worker;i++){
		tolls_with_worker[i] = new Toll_with_worker(least_no_of_vehicles_in_each,seg_id);
	}

	least_no_of_vehicles_in_each = (cur_capacity * 1.1) / no_of_tolls_with_computer;//1.1 of the current capacity / number of tolls with worker
	
	// cout << "Each toll with computer will start with at least " << least_no_of_vehicles_in_each << " vehicles" << endl;

	
	for(int i = 0; i < no_of_tolls_with_computer;i++){
		tolls_with_computer[i] = new Toll_with_computer(least_no_of_vehicles_in_each,seg_id);	
	}
}

Entrance :: ~Entrance(){
	Vehicle* temp;
	for(int i = 0; i < no_of_tolls_with_worker; i++){
		delete tolls_with_worker[i];
	}
	for(int i = 0; i < no_of_tolls_with_computer; i++){
		delete tolls_with_computer[i];
	}
	delete[] tolls_with_worker;
	delete[] tolls_with_computer;
	//cout << "Just destructed an entrance" << endl;	
}

bool Entrance :: operate(unsigned const int& cars_that_can_enter){
	//cars_that_can_enter == current capacity of the segment;
	int count_of_cars_worker = 0;
	int count_of_cars_computer = 0;
	int i = 0;
	int j = 0;

 	Vehicle* temp;
	
	int barrier;
	bool flag;

										//3K is the maximum no of cars to enter the seg
	if(cars_that_can_enter >= 3 * K){	//if the cars_that_can_enter are more than or as many as that
		barrier = 3 * K;	
		flag = true;					//then 
	}
	else{
		barrier = cars_that_can_enter;	//then either K by the tolls with worker or 2K by the tolls with computer
		flag = false;					//is not to be reached
	}
	
	if(flag){	// if barrier is 3 * K
	
		while((count_of_cars_worker < K) && (!all_empty_with_worker())){	// insert from tolls with worker,as long as there are some containing vehicles
			insert_from_tolls(tolls_with_worker,no_of_tolls_with_worker,count_of_cars_worker,i);
		}

		if(all_empty_with_worker())	flag = false;	// then K was not reached

		//then,if vehicles from tolls with worker reached K or there aren't any tolls with worker containing vehicles
		while((count_of_cars_computer < 2 * K ) && (!all_empty_with_computer())){ // insert from tolls with computer,as long as there are some containing vehicles
			insert_from_tolls(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer,j);
		}

		if(all_empty_with_computer())	flag = false;	// then 2K was not reached


		//if maximum reached then increase K
		if((count_of_cars_worker == K) && (count_of_cars_computer == 2 * K)){
			increase_K();
		}
		else {	//else decrease K
			decrease_K();
		}

	}
	else{	//if barrier is cars_that_can_enter < 3 * K
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int empty_tolls = 0;
		while(count_of_cars_worker + count_of_cars_computer < barrier){
		
			if(count_of_cars_worker < K){	
				if(!all_empty_with_worker()){
					insert_from_tolls(tolls_with_worker,no_of_tolls_with_worker,count_of_cars_worker,i);
				}
				else{
					empty_tolls = 1;
				}
			}

			for(int p = 0; p < 2;p++){
				if(count_of_cars_worker + count_of_cars_computer >= barrier)break;
			
				if(count_of_cars_computer < 2 * K){	
					if(!all_empty_with_computer()){
						insert_from_tolls(tolls_with_computer,no_of_tolls_with_computer,count_of_cars_computer,j);
					}
					else{
						empty_tolls = 2;
						}
					}
			}

			if(empty_tolls == 2)break;

		}
		///////////////////////////////////////////////////////////////////////////////////////////
		decrease_K();	//as of course fewer than 3 * K vehicles passed through,decrease K

	}

	int seg_cur_capacity = entering_segment->get_cur_capacity();

	enter(seg_cur_capacity);

	return !flag;	//If K conditions were false ---> flag == false
}					//So return !flag == True ---> In order to print the "Delays" message
					//OR the opposite of the above
void Entrance :: enter(unsigned const int& seg_cur_capacity){ 
	int least_no_of_vehicles_to_enter_in_each = (seg_cur_capacity * 0.4) / no_of_tolls_with_worker;//0.4 of the current capacity / number of tolls with worker

	for(int i = 0; i < no_of_tolls_with_worker;i++){
		tolls_with_worker[i]->enter_the_toll(seg_cur_capacity);
	}

	least_no_of_vehicles_to_enter_in_each = (seg_cur_capacity * 1.1) / no_of_tolls_with_computer;//1.1 of the current capacity / number of tolls with computer
	

	for(int i = 0; i < no_of_tolls_with_computer;i++){
		tolls_with_computer[i]->enter_the_toll(seg_cur_capacity);
	}
	
}

void Entrance :: insert_from_tolls(Toll** toll,const int& no_of_tolls,int& count,int& ij){
	Vehicle* temp = NULL;
	
	temp = toll[ij]->exit_to_the_seg();
	ij++;
	if(ij == no_of_tolls){
		ij = 0;
	}

	if(temp == NULL)return;

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