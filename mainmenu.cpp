#define _CRT_SECURE_NO_WARNINGS
#include "mainmenu.h"
#include <stdio.h>
#include "winbgi2.h"
#include "def.h"

void showmenu(int, int, int);
void snek(int, int, int, int);

int menu_loop(int* data){
	int pos = 0;
	cleardevice();
	showmenu(0, data[2], data[0]);

	while (1){
		//animate(10);
		if (kbhit()){
			int key;
			for (int i = 0; i < 3; i++){
				key = dir_from_key(getch(), data);
			}
			switch (key){
			case 0:
				if (pos > 0){
					pos--;
					cleardevice(); 
					showmenu(pos, data[2], data[0]); //<-
				}
				break;
			case 1:
				if (pos < 2){
					pos++;
					cleardevice(); 
					showmenu(pos, data[2], data[0]); //<-
				}
				break;
			case -2:
				return pos;
			}
		}
		delay(100);
	}
}

void showmenu(int pos, int score, int size){
	setactivepage(1);
	setvisualpage(1);
	int textsize = 2, y = 0.1*size;

	if (size > 800){
		textsize += size % 100;
	}

	char menu[5], newgame[15], options[15], exitgame[15], highscore[30];
	sprintf(menu, "MENU");
	sprintf(newgame, "    NEW GAME");
	sprintf(options, "    OPTIONS");
	sprintf(exitgame, "    EXIT GAME");
	sprintf(highscore, "HIGHSCORE: %d", score);

	switch (pos){
	case 0:
		sprintf(newgame, "->  NEW GAME");
		break;
	case 1:
		sprintf(options, "->  OPTIONS");
		break;
	case 2:
		sprintf(exitgame, "->  EXIT GAME");
		break;
	}

	settextstyle(4, HORIZ_DIR, textsize + 4);
	int left = (size - textwidth(menu)) / 2.;
	outtextxy(left, y, menu);
	settextstyle(4, HORIZ_DIR, textsize);
	y += 4 * textheight(newgame);
	outtextxy(left, y, newgame);
	y += 2 * textheight(options);
	outtextxy(left, y, options);
	y += 2 * textheight(exitgame);
	outtextxy(left, y, exitgame);
	y += 2.5 * textheight(highscore);
	outtextxy((size - textwidth(highscore)) / 2, y, highscore);
}

void snek(int x0, int y0, int cw, int ch){
	//gorna S
	line(x0 + cw / 3., y0, x0 + cw * 35.5 / 21., y0);
	//dolna S
	line(x0, y0 + ch, x0 + cw * 9.5 / 7., y0 + ch);
	//lewa S
	line(x0, y0 + ch, x0 + cw / 3., y0);
	//prawa S
	line(x0 + cw, y0 + ch, x0 + cw * 4. / 3., y0);
	//srodek gora S
	line(x0 + cw * 13. / 18., y0 + ch / 3., x0 + cw * 11. / 9., y0 + ch / 3.);
	//srodek dol S
	line(x0 + cw / 9., y0 + ch * 2. / 3., x0 + cw * 11. / 18., y0 + ch * 2. / 3.);
	//skos lewy gora N
	line(x0 + cw * 35.5 / 21., y0, x0 + cw * 113.5 / 63., y0 + ch / 3.);
	//skos lewy dol N
	line(x0 + cw * 9.5 / 7., y0 + ch, x0 + cw * 92.5 / 63., y0 + ch * 2. / 3.);
	//skos prawy dolny N
	line(x0 + cw * 92.5 / 63., y0 + ch * 2. / 3., x0 + cw * 99.5 / 63., y0 + ch);
	//skos gorny prawy N
	line(x0 + cw * 113.5 / 63., y0 + ch / 3., x0 + cw * 120.5 / 63., y0);
	//gora N
	line(x0 + cw * 120.5 / 63., y0, x0 + cw * 228.5 / 63., y0);
	//dol N
	line(x0 + cw * 99.5 / 63., y0 + ch, x0 + cw * 207.5 / 63., y0 + ch);
	//prawe N
	line(x0 + cw * 143. / 63., y0, x0 + cw * 122. / 63., y0 + ch);
	//srodek gora E
	line(x0 + cw * 167.5 / 63., y0 + ch / 3., x0 + cw * 199. / 63., y0 + ch / 3.);
	//srodek dol E
	line(x0 + cw * 64. / 21., y0 + ch * 2. / 3., x0 + cw * 53.5 / 21., y0 + ch * 2. / 3.);
	//prawe E
	line(x0 + cw * 206. / 63., y0, x0 + cw * 185. / 63., y0 + ch);
	//lewy skos gora K
	line(x0 + cw * 228.5 / 63., y0, x0 + cw * 221.5 / 63., y0 + ch / 3.);
	//lewy skos dol K
	line(x0 + cw * 207.5 / 63., y0 + ch, x0 + cw * 71.5 / 21., y0 + ch * 2. / 3.);
	//prawy skos gora K
	line(x0 + cw * 221.5 / 63., y0 + ch / 3., x0 + cw * 107. / 28., y0);
	//prawy skos dol K
	line(x0 + cw * 71.5 / 21., y0 + ch * 2. / 3., x0 + cw * 25. / 7., y0 + ch);
	//gora K
	line(x0 + cw * 107. / 28., y0, x0 + cw * 59. / 14., y0);
	//dol K
	line(x0 + cw * 25. / 7., y0 + ch, x0 + cw * 27.75 / 7., y0 + ch);
	//prawa gora K
	line(x0 + cw * 59. / 14., y0, x0 + cw * 11. / 3., y0 + ch / 1.86);
	//prawa dol K
	line(x0 + cw * 11. / 3., y0 + ch / 1.86, x0 + cw * 27.75 / 7., y0 + ch);
}

void intro(int window_height, int window_width){
	setlinestyle(0, 1, 3);
	settextstyle(4, HORIZ_DIR, 2);

	int press = 0;
	while (!kbhit()){
		switch (press)
		{
		case 0:
			cleardevice();
			snek(window_width / 4., window_height * 0.3, window_width / 8., window_height / 7.);
			press = 1;
			break;
		default:
			cleardevice();
			snek(window_width / 4., window_height * 0.3, window_width / 8., window_height / 7.);
			outtextxy((window_width - textwidth("- PRESS ANY KEY -")) / 2., window_height / 2.1, "- PRESS ANY KEY -");
			press = 0;
			break;
		}
		animate(3);
	}

	getch();
}