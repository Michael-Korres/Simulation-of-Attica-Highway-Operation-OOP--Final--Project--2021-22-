#include <iostream>

using namespace std;

class Vehicle{
    public:
        Vehicle(const int&,const int&,const bool&);
        ~Vehicle();
        Vehicle(const Vehicle&);
        
        int get_exit() const;
        bool get_if_ready() const;

        void set_ready();
        void set_unready();

    private:
        int exit_interchange;
        int curr_seg;
        bool ready_to_exit;
};