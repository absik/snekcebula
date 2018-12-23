#include "def.h"

int dir_from_key(int key, int* data){
	if (key == up_dir){
		return 0;
	}
	if (key == down_dir){
		return 1;
	}
	if (key == left_dir){ 
		return 2;
	}
	if (key == right_dir){
		return 3;
	}
	if (key == enter){
		return -2;
	}
	if (key == 27){
		return -3;
	}

	return -1;
}