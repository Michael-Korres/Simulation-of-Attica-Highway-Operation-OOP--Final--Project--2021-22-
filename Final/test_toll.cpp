#include "final.h"

using namespace std;

void print_count(Toll&);

int main(int argc,char* argv[]){
	srand(time(NULL));
	
	int NSegs = 5;
    cout << "Attica has " << NSegs << " segments." << endl;
	Toll :: set_NSegs(NSegs);

	int cur_capacity = 100;	//Current capacity: 100
	cout << "The current capacity of the segment is " << cur_capacity << " vehicles." << endl;
	
	int no_of_tolls_with_computer = random_number_generator_within_range(5,9); //Number of tolls with computer
	cout << "The number of tolls with computer of the entrance is " << no_of_tolls_with_computer << "." << endl;
	

	unsigned int no_of_vehicles_initially = (cur_capacity * 1.1) / no_of_tolls_with_computer; //no_of_vehicles_initially
	
	cout << "It will start with at least " << no_of_vehicles_initially << " vehicles." << endl;
    
	Toll toll(no_of_vehicles_initially,3,false); //(no_of_vehicles_initially,interchange,has_a_worker)
	
	print_count(toll);	//print the count of vehicles
	
	cur_capacity = 50;	//Now the capacity is: 50
	cout << "The current capacity of the segment is " << cur_capacity << " vehicles." << endl;
	
	unsigned int no_of_vehicles_to_enter = (cur_capacity * 1.1) / no_of_tolls_with_computer;


	cout << "There will enter at least " << no_of_vehicles_to_enter << " vehicles." << endl;

	toll.enter_the_toll(no_of_vehicles_to_enter);	//(no_of_cars_to_enter,interchange,NSegs)

	print_count(toll);	//print the count of vehicles
	
	cout << "There will exit 10 vehicles." << endl;

	for(int k = 0; k < 10;k++)toll.exit_to_the_seg();	//the 1st car in the Queue of the toll

	print_count(toll); //print the count of vehicles

	return 0;
}

void print_count(Toll& toll){
	cout << "It has " << toll.get_count() << " vehicles." << endl;
}