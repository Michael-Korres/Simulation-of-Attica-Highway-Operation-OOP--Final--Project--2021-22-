#include <iostream>
#include <time.h>

using namespace std;

 unsigned int random_number_generator_within_range(const int& , const int&);

class Vehicle{
	public:
		Vehicle(const int&,const int& = -1,const bool& = false);
		~Vehicle();
	
		int get_exit() const;
		bool is_ready() const;
		int get_curr_segment() const;

		void set_ready();
		void set_unready();
		void set_segment(const int&);
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
		Queue();
		~Queue();
		bool is_empty() const;
		void enter(Vehicle*);
		int get_count()const;
		void enter(Vehicle** ,const int& );
		Vehicle* exit();
	private:
		int count;
		QueueNode* head;
		QueueNode* tail;
};

class Toll{
	public:
		Toll(unsigned const int&,unsigned const int&,const bool&);
		~Toll();

		void enter_the_toll(unsigned const int&,unsigned const int&);
		Vehicle* exit_to_the_seg();
		bool is_empty() const;
		int get_count() const;

		static void set_NSegs(unsigned const int&);
	
	private:
		static int NSegs;
		bool has_a_worker;
		Queue vehicles_waiting;
};

class Segment;
class Entrance{
	public:
		Entrance(unsigned const int& cur_capacity,unsigned const int& id,Segment* seg_ptr);
		~Entrance();
		bool operate();
		void enter();
		static void set_NSegs(unsigned const int&);
		void increase_K();
		void decrease_K();
	private:
		static int NSegs;
		int id;
		int K;
		Segment* entering_segment;
		Toll** tolls_with_worker;
		Toll** tolls_with_computer;
		int no_of_tolls_with_worker;
		int no_of_tolls_with_computer;
		bool all_empty_with_worker() const;
		bool all_empty_with_computer() const;
		void insert_from_tolls(Toll** ,const int& ,int&, int& );
};

struct ListNode{
	ListNode(Vehicle*,ListNode*);
	Vehicle* vehicle;
	ListNode* next;
};

class List{    //Implemented by a list like: head --> | --> | --> ... --> | <--> tail
	public:
		List(const int&);
		~List();
		bool is_empty() const;
		void enter(Vehicle*);
		void exit();
		Vehicle* pass();
		Vehicle* delete_next(ListNode*);
		void set_ready(const int&);

		int get_count() const;
		int get_ready_ones() const;
		Vehicle* exit(const int&);
	private:
		int count;
		int id;
		ListNode* head;
		ListNode* tail;
};

class Segment{
	public:
		Segment(const int& NSegs,const int& K,const int& vehicle_capacity,const int id,Segment* previous,Segment* next);
		~Segment();
		void operate();
		void insert_vehicle(Vehicle* vehicle);
		void exit();
		bool enter();
		Vehicle* pass();
		void set_ready();
		int get_no_of_vehicles()const;
		static void set_percent(const float&);
		int get_cur_capacity()const;
	private:
		int NSegs;
		Entrance entrance;
		List vehicles_currently;
		const int vehicle_capacity;
		const int id;
		Segment* next;
		Segment* previous;
		static float percent;
};

class Attica{
	public:
		Attica(const int&,const int&,const float&,int*);
		~Attica();
		void operate();
	private:
		int NSegs;
		Segment** segs;
		float percent;
		int total_count_of_vehicles;
};