/* driver load.c */
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
#include "load.h"
#include "mesinkata.h"
#include "mesinkar.h"


int main () {
	Player P1, P2;
	MatriksMap M;
	Queue Q;

	printf("--This is a driver for Module Load--\n");
	printf("*Load file*\n");
	Load(&M, &P1, &P2, &Q);

	printf("*Save file*\n");
	Save(M,P1,P2,Q);

	return 0;
}