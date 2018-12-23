#include <stdio.h>
#include <Windows.h>
#include "winbgi2.h"
#include "def.h"
#include "handle_data.h"
#include "gameplay.h"
#include "mainmenu.h"
#include "options.h"

int main(){
	int data[8];
	read_data(data);
	graphics(windowsize, windowsize);

	setcolor(snakecolour / 10.);
	intro(windowsize, windowsize);
	cleardevice();
	setgray(1.0);

	int running = 1, score = 0;
	while (running){
		switch (menu_loop(data)){
		case 0:
			cleardevice();
			score = game_loop(data);
			cleardevice();
			if (score > data[2]) data[2] = score;
			break;
		case 1:
			cleardevice();
			if (options_loop(data) == 0){
				save_data(data);
				return 0;
			}
			cleardevice();
			break;
		case 2:
			running = 0;
			break;
		}
	}

	save_data(data);
	return 0;
}