#include "final.h"

int random_number_generator_within_range(const int& min,const int& max){
	int num = rand();
	return ((num + min) % (max + 1));
}