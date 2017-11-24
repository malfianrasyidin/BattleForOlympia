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

	M = MatGen(10,10);
	InitPlayer(&P1, &P2, 10, 10);
	CreateTurn(&Q);
	char filename[256];

	scanf("%s", &filename);
	Save(M,P1,P2,Q, filename);

	return 0;
}