#include "final.h"

using namespace std;

void print_exit(Vehicle&);
void print_ready(Vehicle&);
void print_curr_seg(Vehicle&);


int main(int argc,char* argv[]){
	int NSegs = 5;
	
	Vehicle v(3);	//toll connstruction

	print_exit(v);	//The exit is: 3

	print_ready(v);	//It is not ready to move at first

	v.set_ready();	//Set to ready

	print_ready(v);	//It is now

	Vehicle v2(4,5); //Segment Construction

	v.set_segment(4); //Segment setting after entering the highway from a toll

	print_curr_seg(v);	//The current segment is: 4
	
	return 0;
}

void print_exit(Vehicle& v){
	cout << "The exit is: " << v.get_exit() << endl;
}

void print_curr_seg(Vehicle& v){
	cout << "The current segment is: " << v.get_curr_segment() << endl;
}


void print_ready(Vehicle& v){
	if(v.is_ready()){
		cout << "It is ready to move." << endl;
	}
	else{
		cout << "It is not ready to move." << endl;
	}

}
