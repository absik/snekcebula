#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "options.h"
#include "winbgi2.h"
#include "def.h"

void showoptions(int, int*, int);
void changecontrols(int, int*);
int checknewcotrols(int, int*);
void newkeyverified(int, int, int*);
int changewindowsize(int*);
void changesnakecolour(int*);

int options_loop(int* data){
	int pos = 0, running = 1, temp, key = 0;
	cleardevice();
	showoptions(0, data, data[0]);

	while (running){
		for (int i = 0; i < 3; i++){
			key = dir_from_key(getch(), data);
		}
		switch (key){
		case -3:
			running = 0;
			break;
		case 0:
			if (pos > 0){
				pos--;
				cleardevice(); //<-
				showoptions(pos, data, data[0]);
			}
			break;
		case 1:
			if (pos < 6){
				pos++;
				cleardevice(); //<-
				showoptions(pos, data, data[0]);
			}
			break;
		case -2:
			switch (pos){
			case 0:
				temp = changewindowsize(data);
				if (temp != 0){
					cleardevice();
					outtextxy((windowsize - textwidth("RESTART GAME")) / 2., (windowsize - textheight("RESTART GAME")) / 2., "RESTART GAME");
					wait();
					windowsize = temp;
					return 0;
				}
				break;
			case 1:
				changesnakecolour(data);
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				changecontrols(pos, data);
				cleardevice();
				showoptions(pos, data, data[0]);
				break;
			}
		}
		delay(100);
	}
	return 1;
}

void showoptions(int pos, int* data, int size){
	int textsize = 2, y = 0.1*windowsize;

	if (windowsize > 800){
		textsize += windowsize % 100;
	}

	char options[15], window_size[30], snake_colour[20], up[20], down[20], left[20], right[20], accept[20];
	sprintf(options, "OPTIONS");
	sprintf(window_size, "   WINDOW SIZE:  %d", size);
	sprintf(snake_colour, "   SNAKE COLOUR:");
	sprintf(up, "   UP:            %c", data[3]);
	sprintf(down, "   DOWN:      %c", data[4]);
	sprintf(left, "   LEFT:         %c", data[5]);
	sprintf(right, "   RIGHT:      %c", data[6]);
	sprintf(accept, "   ACCEPT:   %c", data[7]);

	switch (pos){
	case 0:
		sprintf(window_size, "-> WINDOW SIZE:  %d", size);
		break;
	case 1:
		sprintf(snake_colour, "-> SNAKE COLOUR:");
		break;
	case 2:
		sprintf(up, "-> UP:            %c", data[3]);
		break;
	case 3:
		sprintf(down, "-> DOWN:      %c", data[4]);
		break;
	case 4:
		sprintf(left, "-> LEFT:         %c", data[5]);
		break;
	case 5:
		sprintf(right, "-> RIGHT:      %c", data[6]);
		break;
	case 6:
		sprintf(accept, "-> ACCEPT:   %c", data[7]);
		break;
	}

	settextstyle(4, HORIZ_DIR, textsize + 4);
	int left_dist = (windowsize - textwidth(options)) / 2.;
	outtextxy(left_dist, y, options);
	settextstyle(4, HORIZ_DIR, textsize);
	y += 4 * textheight(window_size);
	outtextxy(left_dist, y, window_size);
	y += 2 * textheight(snake_colour);
	outtextxy(left_dist, y, snake_colour);
	setcolor(data[1] / 10.);
	setlinestyle(SOLID_LINE, 0, 3);
	line(left_dist + textwidth(snake_colour) + 0.3*textwidth("snake"), y + textheight(snake_colour) / 2, left_dist + textwidth(snake_colour) + 1.3*textwidth("snake"), y + textheight(snake_colour) / 2);
	setgray(1.0);
	y += 2 * textheight(up);
	outtextxy(left_dist, y, up);
	y += 2 * textheight(down);
	outtextxy(left_dist, y, down);
	y += 2 * textheight(left);
	outtextxy(left_dist, y, left);
	y += 2 * textheight(right);
	outtextxy(left_dist, y, right);
	y += 2 * textheight(accept);
	outtextxy(left_dist, y, accept);
}

void changecontrols(int pos, int* data){
	outtextxy((windowsize - textwidth("Press new key.")) / 2., 0.95*windowsize - textheight("Press new key."), "Press new key.");
	int key;//<-
	for (int i = 0; i < 3; i++){
		key = getch();
	}
	switch (pos){
	case 2:
		newkeyverified(3, key, data);
		break;
	case 3:
		newkeyverified(4, key, data);
		break;
	case 4:
		newkeyverified(5, key, data);
		break;
	case 5:
		newkeyverified(6, key, data);
		break;
	case 6:
		newkeyverified(7, key, data);
		break;
	}
}

int checknewcontrols(int key, int* data){
	int error = 0;
	for (int i = 3; i < 8; i++){
		if (key == data[i]){
			error = i;
			break;
		}
	}
	if (error){
		outtextxy((windowsize - textwidth("Key already bound.")) / 2., (windowsize - textheight("Key already bound.")) / 2., "Key already bound.");
		outtextxy((windowsize - textwidth("Press E to unbind, ESC to cancel.")) / 2., (windowsize + textheight("Press E to unbind, ESC to cancel.")) / 2., "Press E to unbind, ESC to cancel.");

		while (1){
			int answer;
			for (int i = 0; i < 3; i++){
				answer = getch();
			}

			if (answer == enter){
				return error;
			}
			if (answer == 27){
				return -1;
			}
		}
	}
	return -2;
}

void newkeyverified(int pos, int key, int* data){
	int result = checknewcontrols(key, data);

	if (result > -1){ //<-
		data[result] = data[pos];
		data[pos] = key;
	}

	if (result == -2){
		data[pos] = key;
	}
}

int changewindowsize(int* data){
	outtextxy((windowsize - textwidth("Enter new window size.")) / 2., 0.95*windowsize - textheight("Enter new window size."), "Enter new window size.");
	int temp = 0, key = 0;
	while (1){
		for (int i = 0; i < 3; i++){
			key = getch();
		}
		switch (key){
		case 48:
			temp *= 10;
			break;
		case 49:
			temp *= 10;
			temp += 1;
			break;
		case 50:
			temp *= 10;
			temp += 2;
			break;
		case 51:
			temp *= 10;
			temp += 3;
			break;
		case 52:
			temp *= 10;
			temp += 4;
			break;
		case 53:
			temp *= 10;
			temp += 5;
			break;
		case 54:
			temp *= 10;
			temp += 6;
			break;
		case 55:
			temp *= 10;
			temp += 7;
			break;
		case 56:
			temp *= 10;
			temp += 8;
			break;
		case 57:
			temp *= 10;
			temp += 9;
			break;
		case 27:
			return 0;
			break;
		default:
			if (key == enter){
				if (temp < 500){
					outtextxy((windowsize - textwidth("Window too small")) / 2., (windowsize + textheight("Window too small")) / 2., "Window too small");
					wait();
					return windowsize;
				}
				return temp;
			}
			break;
		}
		cleardevice();
		showoptions(0, data, temp);
		outtextxy((windowsize - textwidth("Enter new window size.")) / 2., 0.95*windowsize - textheight("Enter new window size."), "Enter new window size.");
	}
}

void changesnakecolour(int* data){
	int key;
	for (int i = 0; i < 3; i++){
		key = getch();
	}
	while (key != enter){
		key = dir_from_key(key, data);
		switch (key){
		case 2:
			if (snakecolour > 0){
				snakecolour--;
				cleardevice();
				showoptions(1, data, data[0]);
			}
			break;
		case 3:
			if (snakecolour < 10){
				snakecolour++;
				cleardevice();
				showoptions(1, data, data[0]);
			}
			break;
		}
		
		for (int i = 0; i < 3; i++){
			key = getch();
		}
	}
}