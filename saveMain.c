/* driver save.c */
#include <stdio.h>
#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"
#include "string.h"
#include "player.h"
#include "queuelist.h"
#include "save.h"


int main () {
	Player P1, P2;
	MatriksMap M;
	Queue Q;

	printf("--This is a driver for Module Save--\n");
	
	printf("*Initialize map, player, and turn*\n");

	M = MatGen(10,10);
	InitPlayer(&P1, &P2, 10, 10);
	CreateTurn(&Q);
	char filename[256];

	printf("*Initialization finished*\n");
	printf("*Save file*\n");
	Save(M,P1,P2,Q);

	return 0;
}