#include "final.h"

unsigned int random_number_generator_within_range(const int& min,const int& max){
	if(min <= max){
		int X = rand();
		return (min + X % (max - min + 1));
	}
	else {
		return 0;
	}
}