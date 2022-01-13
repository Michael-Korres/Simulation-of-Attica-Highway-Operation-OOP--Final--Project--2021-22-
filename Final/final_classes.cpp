#include "final.h"

//Vehicle
Vehicle :: Vehicle(const int& interchange = 0,const int& seg = -1,const bool& move_state = false):
        exit_interchange(interchange),curr_seg(seg),ready_to_exit(move_state)
{
    cout << "Just constructed a vehicle." << endl; 
}

Vehicle :: ~Vehicle(){
    cout << "Just destructed a vehicle." << endl; 
}

int Vehicle :: get_exit() const{
    return exit_interchange;
}

bool Vehicle :: get_if_ready() const{
    return ready_to_exit;
};


void Vehicle :: set_ready(){
    ready_to_exit = true;
}

void Vehicle :: set_unready(){
    ready_to_exit = false;
}
