#include "command.h"
#include "MatriksMap.h"
#include "unit.h"
#include "point.h"
#include"listdpUnit.h"
#include "player.h"
#include "boolean.h"
#include "jam.h"
#include <stdlib.h>
#include <stdio.h>

char SpaceToUnderscore(char X) {
	if (X == ' ') {
		return '_';
	} else {
		return X;
	}
}

void WriteCurrentTime(TANGGAL *T, JAM *J, FILE *f)
/* Menuliskan tanggal dan jam saat ini dengan format DD/MM/YYYY HH:MM:SS */
{	/* ALGORITMA */
	GetCurrentTime(J,T);
	fprintf(f, "%d %d %d %d %d %d\n",
				Day(*T),
				Month(*T),
				Year(*T),
				Hour(*J),
				Minute(*J),
				Second(*J));
}

void WritePoint(POINT P, FILE *f)
/* I.S. file f sudah dibuka, point P terdefinisi */
/* F.S. file f diisi dengan point P */
{	/* KAMUS LOKAL */
	
	/* ALGORITMA */
	fprintf(f, "%d %d\n",
				Absis(P),
				Ordinat(P));
}

void WriteUnit(Unit U, FILE *f)
/* I.S. file f sudah dibuka, unit U terdefinisi */
/* F.S. file f diisi dengan unit U */
{	/* KAMUS LOKAL */
	char temp;
	/* ALGORITMA */
	temp = SpaceToUnderscore(AttackType(U));
	fprintf(f, "%d %c %d\n",
				DamagePoints(U),
				temp,
				HealPoints(U));
	WritePoint(Locate(U), f);
	temp = SpaceToUnderscore(Tipe(U));
	fprintf(f, "%d %c %d %d %d %d %d\n",
				HP(U),
				temp,
				MP(U),
				Owner(U),
				MaxHP(U),
				MaxMP(U),
				CanAttack(U));
}

void WriteBuild(Build B, FILE *f)
/* I.S. file f sudah dibuka, build B terdefinisi */
/* F.S. file f diisi dengan build B */
{	/* KAMUS LOKAL */
	char temp;
	/* ALGORITMA */
	temp = SpaceToUnderscore(TipeB(B));
	fprintf(f, "%d %c\n",
				OwnerB(B),
				temp);
}

void WriteLocation(Location L, FILE *f)
	/* I.S.  file f sudah dibuka, location L terdefinisi */
	/* F.S. file f diisi dengan location L */
{	/* ALGORITMA */
	WriteBuild(BuildIn(L), f);
	WriteUnit(UnitIn(L), f);
}

void WriteMatriksMap(MatriksMap M, FILE *f)
	/* I.S.  file f sudah dibuka, MatriksMap M terdefinisi */
	/* F.S. file f diisi dengan MatriksMap M */
{	/* KAMUS LOKAL */
	int i, j;
	/* ALGORITMA */
	fprintf(f, "%d %d\n",
				NBrsEff(M),
				NKolEff(M));
	for (i = 1; i <= NBrsEff(M); ++i) {
		for (j = 1; j <= NKolEff(M); ++j) {
			WriteLocation(Elmt(M, i, j), f);
		}
	}
}

void WriteListOfPoint(List L, FILE *f)
	/* I.S.  file f sudah dibuka, List of Point L terdefinisi */
	/* F.S. file f diisi dengan List of Point L */
{	/* KAMUS LOKAL */
	addressList P = Nil;
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
	fprintf(f, "%d %d\n",
				PlayNumber(P),
				PGold(P));
	WritePoint(CurrentUnitPos(P), f);
	fprintf(f, "%d %d\n",
				PIncome(P),
				PUpKeep(P));
	WriteListOfPoint(UnitList(P), f);
	WriteListOfPoint(VillageList(P), f);
	for (int i = 1; i <= 4; ++i){
		WritePoint(PlayerCastle(P,i),f);
	}
	WritePoint(PlayerTower(P), f);
}

void WriteTurn(Queue Q, FILE *f)
	/* I.S.  file f sudah dibuka, queue Q terdefinisi */
	/* F.S. file f diisi dengan queue Q */
{	/* KAMUS LOKAL */

	/* ALGORITMA */
	fprintf(f,"%d %d EndOfQueue\n", InfoHead(Q), InfoTail(Q));
}

void Save(MatriksMap MatMap, Player Player1, Player Player2, Queue Turn, char filename[])
/* Melakukan save file */
/* I.S. MatMap, Player1, Player2, dan Queue terdefinisi*/
/* F.S. menulis file pitakar.txt yang berisi rekaman dari game saat ini */
{	/* KAMUS LOKAL */
	FILE *f;
	TANGGAL T;
	JAM J;
	/* ALGORITMA */
	printf("Saving file '%s' ...\n", filename);
	f = fopen(filename, "w");
	WriteCurrentTime(&T,&J,f);
	WriteMatriksMap(MatMap, f);
	WritePlayer(Player1, f);
	WritePlayer(Player2, f);
	WriteTurn(Turn, f);
	fprintf(f, ".");
	fclose(f);
	printf("Game successfully saved on ");
	TulisTANGGAL(T);
	printf(" ");
	TulisJAM(J);
	printf(".\n");

}