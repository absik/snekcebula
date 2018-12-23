#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "gameplay.h"
#include "def.h"
#include "winbgi2.h"

void prep(vertex*, vertex*);
void new_apple(vertex*, vertex*, int);
int collision(vertex*, vertex*, int);
void move(vertex*, int, int*, int*);
void draw_map(vertex*, vertex, int, int, int);
int pause_menu(int*);

int game_loop(int* data){
	vertex coords[maxlength], apple;
	int score = 0, grow = 0, currentlength = 1, dir = -1;
	int pixelsize = (windowsize - 100) / mapsize;
	prep(coords, &apple);
	settextstyle(4, HORIZ_DIR, 2);

	draw_map(coords, apple, currentlength, pixelsize, snakecolour);

	while (dir == -1){
		int key = dir_from_key(getch(), data);
		if (key > -1){
			dir = key;
		}
	}

	while (1){
		animate(5);
		cleardevice();
		draw_map(coords, apple, currentlength, pixelsize, snakecolour);

		char showscore[20];
		sprintf(showscore, "%d", score);
		outtextxy(windowsize / 2.17, 5, showscore);
		
		if (kbhit()){
			int key = dir_from_key(getch(), data);
			if (key > -1){
				dir = key;
			}
			if (key == -3){
				cleardevice();
				if (!pause_menu(data)){ //<-- nie wyswietla sie, ale dziala
					return score;
				}
			}
		}

		move(coords, dir, &currentlength, &grow);
		int col_result = collision(coords, &apple, currentlength);

		switch (col_result){
		case 1:
			cleardevice();
			setactivepage(1);
			setvisualpage(1);
			draw_map(coords, apple, currentlength, pixelsize, snakecolour);
			outtextxy((windowsize - textwidth("GAME OVER")) / 2., windowsize / 2. - textheight("GAME OVER"), "GAME OVER");
			outtextxy((windowsize - textwidth(showscore)) / 2., (windowsize + textheight(showscore)) / 2., showscore);
			
			for (int i = 0; i < 3; i++){
				getch();
			}
			return score;
			break;
		case 2:
			grow = 1;
			score++;
			break;
		}
	}
}

void prep(vertex* coords, vertex* apple){
	srand(time(NULL));

	coords[0].x = rand() % (mapsize - 2) + 1;
	coords[0].y = rand() % (mapsize - 2) + 1;
	(*apple).x = rand() % (mapsize - 2) + 1;
	(*apple).y = rand() % (mapsize - 2) + 1;
	
	while (((*apple).x == coords[0].x) && ((*apple).y == coords[0].y)){
		(*apple).x = rand() % (mapsize - 2) + 1;
		(*apple).y = rand() % (mapsize - 2) + 1;
	}
}

void new_apple(vertex* coords, vertex* apple, int currentlength){
	int ok = 0;

	while (!ok){
		(*apple).x = rand() % (mapsize - 2) + 1;
		(*apple).y = rand() % (mapsize - 2) + 1;
		ok = 1;
		for (int i = 0; i < currentlength; i++){
			if ((coords[i].x == (*apple).x) && (coords[i].y == (*apple).y)){
				ok = 0;
				break;
			}
		}
	}
}

int collision(vertex* coords, vertex* apple, int currentlength){
	if ((coords[0].x < 0) || (coords[0].x > 50)){
		return 1;
	}
	if ((coords[0].y < 0) || (coords[0].y > 50)){
		return 1;
	}

	for (int i = 1; i < currentlength; i++){
		if ((coords[0].x == coords[i].x) && (coords[0].y == coords[i].y)){
			return 1;
		}
	}

	if ((coords[0].x == (*apple).x) && (coords[0].y == (*apple).y)){
		new_apple(coords, apple, currentlength);
		return 2;
	}

	return 0;
}

void move(vertex* coords, int dir, int* currentlength, int* grow){
	if (*grow){
		*grow = 0;
		(*currentlength)++;
	}

	for (int i = *currentlength - 1; i > 0; i--){
		coords[i] = coords[i - 1];
	}
	
	switch (dir){
	case 0:
		coords[0].y--;
		break;
	case 1:
		coords[0].y++;
		break;
	case 2:
		coords[0].x--;
		break;
	case 3:
		coords[0].x++;
		break;
	}
}

void draw_map(vertex* coords, vertex apple, int currentlength, int pixelsize, int snake_colour){
	setgray(1.0);
	rectangle(dist, dist, dist + 51 * pixelsize, dist + 51 * pixelsize);

	setcolor((double) snake_colour / 10.);
	for (int i = 0; i < currentlength; i++){
		rectangle(dist + coords[i].x * pixelsize, dist + coords[i].y * pixelsize, dist + (coords[i].x + 1) * pixelsize, dist + (coords[i].y + 1) * pixelsize);
	}

	setgray(1.0);
	rectangle(dist + apple.x * pixelsize, dist + apple.y * pixelsize, dist + (apple.x + 1) * pixelsize, dist + (apple.y + 1) * pixelsize);
}

int pause_menu(int* data){
	setactivepage(1);
	setvisualpage(1);
	cleardevice();
	outtextxy((windowsize - textwidth("PAUSE")) / 2, 5, "PAUSE");
	outtextxy((windowsize - textwidth("Press enter to resume")) / 2, 2 * (10 + textheight("PAUSE")), "Press enter to resume");
	outtextxy((windowsize - textwidth("Press escape to exit")) / 2, 3 * (10 + textheight("PAUSE")), "Press escape to exit");

	while (1){
		int key;
		for (int i = 0; i < 3; i++){
			key = getch();
		}
		if (key == enter){
			return 1;
		}
		if (key == 27){
			return 0;
		}
	}
}