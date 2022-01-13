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

struct QueueNode{
	QueueNode(Vehicle*,QueueNode*);
	Vehicle* vehicle;
	QueueNode* next;
};

class Queue{    //Implemented by a list like: head --> | --> | --> ... --> | <--> tail
	public:
		Queue(const int&,Vehicle**);
		~Queue();
		bool is_empty();
		void enter(Vehicle*);
		Vehicle* exit();
	private:
		int count;
		QueueNode* head;
		QueueNode* tail;
};

class Toll{
	public:
		Toll(const int&,const int&,const int&);
		~Toll();

		void enter();
		void exit(const int&);

	private:
		Queue vehicles_waiting;
};

