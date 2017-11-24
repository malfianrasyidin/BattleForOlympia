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
	char filename[256];

	printf("--This is a driver for Module Load--\n");
	printf("Input a filename do you would like to load: ");
	scanf("%s", filename);

	Load(&M, &P1, &P2, &Q, filename);

	printf("--Load Check--\n");
	printf("Please enter your desired filename to save: ");
	scanf("%s", filename);
	Save(M,P1,P2,Q, filename);

	return 0;
}