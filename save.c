#include "command.h"
#include "MatriksMap.h"
#include "unit.h"
#include "point.h"
#include"listdpunit.h"
#include "player.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

void WritePoint(POINT P, FILE *f)
/* I.S. file f sudah dibuka, point P terdefinisi */
/* F.S. file f diisi dengan point P */
{	/* KAMUS LOKAL */
	
	/* ALGORITMA */
	fprintf(f, "%d %d ",
				Absis(P),
				Ordinat(P));
}

void WriteUnit(Unit U, FILE *f)
/* I.S. file f sudah dibuka, unit U terdefinisi */
/* F.S. file f diisi dengan unit U */
{	/* KAMUS LOKAL */
	
	/* ALGORITMA */
	WritePoint(Locate(U), f);
	fprintf(f, "%c %d %d %d %d %c %d %d %d\n",
				Tipe(U),
				MaxHP(U),
				HP(U),
				MaxMP(U),
				MP(U),
				AtkType(U),
				Damage(U),
				Heal(U),
				CanAtk(U));
}

void WriteBuild(Build B, FILE *f)
/* I.S. file f sudah dibuka, build B terdefinisi */
/* F.S. file f diisi dengan build B */
{	/* KAMUS LOKAL */

	/* ALGORITMA */
	fprintf(f, "%d %c\n",
				OwnerB(B),
				TipeB(B));
}

void WriteLocation(Location L, FILE *f)
	/* I.S.  file f sudah dibuka, location L terdefinisi */
	/* F.S. file f diisi dengan location L */
{	/* ALGORITMA */
	WriteBuild(L.Build, f);
	WriteUnit(L.Unit, f);
}

void WriteListOfPoint(List L, FILE *f)
	/* I.S.  file f sudah dibuka, List of Point L terdefinisi */
	/* F.S. file f diisi dengan List of Point L */
{	/* KAMUS LOKAL */
	address P = Nil;
	/* ALGORITMA */
	P = First(L);
	while (P != Nil) {
		WritePoint(Info(P), f);
		P = Next(P);
	}
	fprintf(f, "EndOfList\n");
}

void WritePlayer(Player P, FILE *f)
	/* I.S.  file f sudah dibuka, player P terdefinisi */
	/* F.S. file f diisi dengan player P */
{	/* KAMUS LOKAL */
	/* ALGORITMA */
	fprintf(f, "%d %d %d %d\n",
				PlayNumber(P),
				PGold(P),
				PIncome(P),
				PUpKeep(P),
				);
	WriteUnit(CurrentUnit(P), f);
	WriteListOfPoint(UnitList(P), f);
	WriteListOfPoint(VillageList(P), f);
	WritePoint(TabTower(P), f);
	for (int i = 1; i <= 4; ++i){
		WritePoint(PlayerTower(P,i),f);
	}
	fprintf(f,"\n");
}

void WriteUndo(Stack *S, FILE *f)
	/* I.S.  file f sudah dibuka, stack P terdefinisi */
	/* F.S. file f diisi dengan stack P */
{	/* KAMUS LOKAL */
	infotype X;
	Stack STemp;
	/* ALGORITMA */
	while(!IsEmpty(*S)) {
		Pop(S,&X);
		Push(&STemp,X);
	}
	while(!IsEmpty(STemp)) {
		Pop(STemp,&X);
		WritePoint(X, f);
		Push(S,X);
	}
	fprintf(f, "EndOfStack\n");
}


/*** Belum Nulis Write Turn Karena Turn nya Hilang :((( ***/

void WriteTurn(Queue Q, FILE *f)
	/* I.S.  file f sudah dibuka, queue Q terdefinisi */
	/* F.S. file f diisi dengan queue Q */
{	/* KAMUS LOKAL */

	/* ALGORITMA */
	fprintf(f,"%d %d EndOfQueue\n", InfoTail(Q), InfoHead(Q));
}

void Save(Location Loc, Player Player1, Player Player2, Queue Turn, Stack *Undo)
/* Melakukan save file */
/* I.S. */
/* F.S. menulis file pitakar.txt yang berisi rekaman dari game saat ini */
{	/* KAMUS LOKAL */
	FILE *f;
	/* ALGORITMA */
	f = fopen("pitakar.txt", "w");
	WriteLocation(Loc, f);
	WritePlayer(Player1, f);
	WritePlayer(Player2, f);
	WriteTurn(Turn, f);
	WriteUndo(Undo, f);
	fprintf(f, ".");
	fclose(f);
}