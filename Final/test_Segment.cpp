#include "final.h"

using namespace std;

void print_count(Toll&);

int main(int argc,char* argv[]){
	srand(time(NULL));
	
	int NSegs = 5;
    cout << "Attica has " << NSegs << " segments." << endl;

	int cur_capacity = 100;	//Current capacity: 100
	cout << "The current capacity of the segment is " << cur_capacity << " vehicles." << endl;
	
	Segment :: set_NSegs(NSegs);
    Segment :: set_percent(0.5);
	Segment segment(cur_capacity,10,3,NULL,NULL);

    cout << "There are currently " << segment.get_no_of_vehicles() << " vehicles on the Segment." << endl;

    cur_capacity = segment.get_cur_capacity();
    cout << "The current capacity of the segment is " << cur_capacity << " vehicles." << endl;
	
    cout << "Now ready are " << segment.get_ready_ones() << " vehicles" << endl;
    
    segment.set_ready();
    
    cout << "Now ready,after setting some, are " << segment.get_ready_ones() << " vehicles" << endl;
    

    segment.exit();

    cout << "There are currently " << segment.get_no_of_vehicles() << " vehicles on the Segment." << endl;

    cur_capacity = segment.get_cur_capacity();
    cout << "The current capacity of the segment is " << cur_capacity << " vehicles." << endl;
	
    segment.enter();

    cout << "There are currently " << segment.get_no_of_vehicles() << " vehicles on the Segment." << endl;

    cur_capacity = segment.get_cur_capacity();
    cout << "The current capacity of the segment is " << cur_capacity << " vehicles." << endl;
	

	return 0;
}