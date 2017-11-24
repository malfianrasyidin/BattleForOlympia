#include "command.h"
#include "MatriksMap.h"
#include "unit.h"
#include "point.h"
#include"listdpUnit.h"
#include "player.h"
#include "boolean.h"
#include "jam.h"

void WriteCurrentTime(TANGGAL *T, JAM *J, FILE *f);
/* Menuliskan tanggal dan jam saat ini dengan format DD/MM/YYYY HH:MM:SS */

void WritePoint(POINT P, FILE *f);
/* I.S. file f sudah dibuka, point P terdefinisi */
/* F.S. file f diisi dengan point P */

void WriteUnit(Unit U, FILE *f);
/* I.S. file f sudah dibuka, unit U terdefinisi */
/* F.S. file f diisi dengan unit U */

void WriteBuild(Build B, FILE *f);
/* I.S. file f sudah dibuka, build B terdefinisi */
/* F.S. file f diisi dengan build B */

void WriteLocation(Location L, FILE *f);
	/* I.S.  file f sudah dibuka, location L terdefinisi */
	/* F.S. file f diisi dengan location L */

void WriteMatriksMap(MatriksMap M, FILE *f);
	/* I.S.  file f sudah dibuka, MatriksMap M terdefinisi */
	/* F.S. file f diisi dengan MatriksMap M */

void WriteListOfPoint(List L, FILE *f);
	/* I.S.  file f sudah dibuka, List of Point L terdefinisi */
	/* F.S. file f diisi dengan List of Point L */

void WritePlayer(Player P, FILE *f);
	/* I.S.  file f sudah dibuka, player P terdefinisi */
	/* F.S. file f diisi dengan player P */

void WriteUndo(Stack *S, FILE *f);
	/* I.S.  file f sudah dibuka, stack P terdefinisi */
	/* F.S. file f diisi dengan stack P */

void WriteTurn(Queue Q, FILE *f);
	/* I.S.  file f sudah dibuka, queue Q terdefinisi */
	/* F.S. file f diisi dengan queue Q */

void Save(MatriksMap MatMap, Player Player1, Player Player2, Queue Turn, char filename[]);
/* Melakukan save file */
/* I.S. */
/* F.S. menulis file pitakar.txt yang berisi rekaman dari game saat ini */