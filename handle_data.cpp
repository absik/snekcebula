#define  _CRT_SECURE_NO_WARNINGS
#include "handle_data.h"
#include <stdio.h>

void read_data(int* tab){
	FILE* data;
	data = fopen("data.txt", "r");
	for (int i = 0; i < 8; i++){
		fscanf(data, "%d", &tab[i]);
	}
	fclose(data);
}

void save_data(int* tab){
	FILE* data;
	data = fopen("data.txt", "w");
	for (int i = 0; i < 8; i++){
		fprintf(data, "%d ", tab[i]);
	}
	fclose(data);
}