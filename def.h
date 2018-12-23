#ifndef _DEF_H
#define _DEF_H

#define maxlength 2500
#define mapsize 50
#define dist 5 * mapsize / 7
#define windowsize data[0]
#define snakecolour data[1]
#define up_dir data[3]
#define down_dir data[4]
#define left_dir data[5]
#define right_dir data[6]
#define enter data[7]

struct vertex{
	int x, y;
};

int dir_from_key(int, int*);

#endif