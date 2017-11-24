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
	int trash;
	char filename[256];

	scanf("%s", &filename);
	printf("'%s'\n", filename);

	Load(&M, &P1, &P2, &Q, filename);

	scanf("%s", &filename);
	printf("'%s'\n", filename);
	Save(M,P1,P2,Q, filename);

	//printf("Cek apakah pitakar saat ini sama dengan isi dari yang sebelumnya\n");

	return 0;
}