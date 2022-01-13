#include <iostream>
#include <time.h>

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
		bool is_empty() const;
		void enter(Vehicle*);
		void enter(Vehicle** ,const int& );
		Vehicle* exit();
	private:
		int count;
		QueueNode* head;
		QueueNode* tail;
};

class Toll{
	public:
		Toll(const int&,const int&,const int&,const int&,const bool&);
		virtual ~Toll();

		void enter(const int& ,const int& ,const int&);
		Vehicle* exit();

	private:
		bool is_empty() const;
		bool has_a_worker;
		Queue vehicles_waiting;
};