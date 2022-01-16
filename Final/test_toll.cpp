#include "final.h"

using namespace std;

void print_count(Toll&);

int main(int argc,char* argv[]){
	srand(time(NULL));
	
	int NSegs = 5;
    
    Toll toll(5,3,10,false); //(no_of_vehicles_initially,interchange,NSegs,has_a_worker)
	
	print_count(toll);
	
	int cur_capacity = 100;
	int no_of_tolls_with_computer = random_number_generator_within_range(5,9);
	unsigned int no_of_vehicles_to_enter = (cur_capacity * 1.1) / no_of_tolls_with_computer;
	
	cout << "The no of tolls with computer is " << no_of_tolls_with_computer <<
	" and there will enter " << no_of_vehicles_to_enter << " vehicles." << endl;

	toll.enter_the_toll(no_of_vehicles_to_enter,3,10);	//(no_of_cars_to_enter,interchange,NSegs)

	print_count(toll);

	return 0;
}

void print_count(Toll& toll){
	cout << "It has " << toll.get_count() << " vehicles." << endl;
}