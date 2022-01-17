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
	
	// Segment segment(10,cur_capacity,3,NULL,NULL);
	
	// Segment :: set_NSegs(NSegs);

	Entrance entrance(cur_capacity,3,NULL);

	return 0;
}
