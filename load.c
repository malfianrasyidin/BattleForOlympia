#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mesinkar.h"
#include "mesinkata.h"
#include "boolean.h"
#include "load.h"
#include "command.h"
#include "MatriksMap.h"
#include "unit.h"
#include "point.h"
#include "listdpUnit.h"
#include "player.h"
#include "jam.h"

void kataToString (Kata CKata, char *str) 
/* I.S. CKata terdefinisi, str sembarang */
/* F.S. str terdefinisi dengan isi dari CKata.TabKata */
{	/* KAMUS LOKAL */

	/* ALGORITMA */
	strcpy(str, CKata.TabKata);
}

void kataToChar (Kata CKata, char *chr)
/* I.S. CKata terdefinisi, str sembarang */
/* F.S. str terdefinisi dengan isi dari CKata.TabKata */
{	/* ALGORITMA */
	if (CKata.TabKata[0] == '_') {
		*chr = ' ';
	} else {
		*chr = CKata.TabKata[0];
	}
}

void kataToInt (Kata CKata, int *bil) 
/* I.S. CKata terdefinisi, str sembarang */
/* F.S. str terdefinisi dengan isi dari CKata.TabKata */
{	/* KAMUS LOKAL */

	/* ALGORITMA */
	*bil = 0;
	for (int i = 0; i < CKata.Length; ++i) {
		*bil = (*bil) * 10 + CKata.TabKata[i] - '0';
	}
}

/*** MEMBACA FILE EKSTERNAL ***/

void ReadTime(TANGGAL *T, JAM *J)
/* I.S. T dan J sembarang, CKata ada di kata pertama*/
/* F.S. Tanggal T dan Jam J terdefinisi */
{	/* KAMUS LOKAL */
	
	/* ALGORITMA */
	kataToInt(CKata, &Day(*T));
	ADVKATA();
	kataToInt(CKata, &Month(*T));
	ADVKATA();
	kataToInt(CKata, &Year(*T));
	ADVKATA();
	kataToInt(CKata, &Hour(*J));
	ADVKATA();
	kataToInt(CKata, &Minute(*J));
	ADVKATA();
	kataToInt(CKata, &Second(*J));
	ADVKATA();
}

void ReadPoint (POINT *P)
/* I.S. P sembarang, CKata ada di kata pertama*/
/* F.S. Point P terdefinisi */
{	/* KAMUS LOKAL */
	
	/* ALGORITMA */
	kataToInt(CKata, &Absis(*P));
	ADVKATA();
	kataToInt(CKata, &Ordinat(*P));
	ADVKATA();
}

void ReadUnit (Unit *U)
/* I.S. U sembarang, CKata ada di kata pertama*/
/* F.S. Unit U terdefinisi */
{	/* KAMUS LOKAL */
	int CanAtk;
	/* ALGORITMA */
	kataToInt(CKata, &DamagePoints(*U));
	ADVKATA();
	kataToChar(CKata, &AttackType(*U));
	ADVKATA();
	kataToInt(CKata, &HealPoints(*U));
	ADVKATA();
	ReadPoint(&Locate(*U));
	kataToInt(CKata, &HP(*U));
	ADVKATA();
	kataToChar(CKata, &Tipe(*U));
	ADVKATA();
	kataToInt(CKata, &MP(*U));
	ADVKATA();
	kataToInt(CKata, &Owner(*U));
	ADVKATA();
	kataToInt(CKata, &MaxMP(*U));
	ADVKATA();
	kataToInt(CKata, &MaxMP(*U));
	ADVKATA();
	kataToInt(CKata, &CanAtk);
	CanAttack(*U) = (char) CanAtk;
	ADVKATA();
}

void ReadBuild(Build *B)
/* I.S. B sembarang, CKata ada di kata pertama*/
/* F.S. Build B terdefinisi */
{	/* KAMUS LOKAL */
	
	/* ALGORITMA */
	kataToInt(CKata, &OwnerB(*B));
	ADVKATA();
	kataToChar(CKata, &TipeB(*B));
	ADVKATA();
}

void ReadLocation(Location *L)
/* I.S. L sembarang, CKata ada di kata pertama*/
/* F.S. Location L terdefinisi */
{	/* ALGORITMA */
	ReadBuild(&BuildIn(*L));
	ReadUnit(&UnitIn(*L));
}

void ReadMatriksMap(MatriksMap *M)
	/* I.S.  file f sudah dibuka, MatriksMap M terdefinisi */
	/* F.S. file f diisi dengan MatriksMap M */
{	/* KAMUS LOKAL */
	int NBrs, NKol, i, j;
	/* ALGORITMA */
	kataToInt(CKata, &NBrs);
	ADVKATA();
	kataToInt(CKata, &NKol);
	ADVKATA();
	MakeMATRIKS(NBrs, NKol, M);
	for (i = 1; i <= NBrsEff(*M); ++i) {
		for (j = 1; j <= NKolEff(*M); ++j) {
			ReadLocation(&Elmt(*M, i, j));
		}
	}
}

void ReadListOfPoint(List *L)
/* I.S. B sembarang, CKata ada di kata pertama*/
/* F.S. Build B terdefinisi */
{	/* KAMUS LOKAL */
	POINT PTemp;
	/* ALGORITMA */
	CreateEmptyList(L);
	while(strcmp(CKata.TabKata, "EndOfList")) {
		ReadPoint(&PTemp);
		InsVLast(L, PTemp);
	}
	ADVKATA();
}

void ReadPlayer(Player *P)
/* I.S. P sembarang, CKata ada di kata pertama*/
/* F.S. Player P terdefinisi */
{	/* KAMUS LOKAL */

	/* ALGORITMA */
	kataToInt(CKata, &PlayNumber(*P));
	ADVKATA();
	kataToInt(CKata, &PGold(*P));
	ADVKATA();
	ReadPoint(&CurrentUnitPos(*P));
	kataToInt(CKata, &PIncome(*P));
	ADVKATA();
	kataToInt(CKata, &PUpKeep(*P));
	ADVKATA();
	ReadListOfPoint(&UnitList(*P));
	ReadListOfPoint(&VillageList(*P));
	for (int i = 1; i <= 4; ++i){
		ReadPoint(&PlayerCastle(*P,i));
	}
	ReadPoint(&PlayerTower(*P));
}

void ReadTurn(Queue *Q)
/* I.S. Q sembarang, CKata ada di kata pertama*/
/* F.S. Queue Q terdefinisi */
{	/* KAMUS LOKAL */
	int playertemp;
	/* ALGORITMA */
	CreateEmptyQ(Q,2);
	while(strcmp(CKata.TabKata, "EndOfQueue")) {
		kataToInt(CKata, &playertemp);
		AddQ(Q, playertemp);
		ADVKATA();
	}
	ADVKATA();
}

void Load(MatriksMap *MatMap, Player *Player1, Player *Player2, Queue *Turn, char filename[])
/* Melakukan load file */
/* I.S. file pitakar.txt berisi hasil save, semua parameter tidak terdefinisi*/
/* F.S. mendefinisikan semua parameter */
{	/* KAMUS LOKAL */
	TANGGAL T;
	JAM J;
	/* ALGORITMA */
	printf("Loading file '%s' ...\n", filename);
	STARTKATA(filename);
	ReadTime(&T, &J);
	ReadMatriksMap(MatMap);
	ReadPlayer(Player1);
	ReadPlayer(Player2);
	ReadTurn(Turn);
	while (!EndKata) {
		ADVKATA();
	}
	printf("File from ");
	TulisTANGGAL(T);
	printf(" ");
	TulisJAM(J);
	printf(" successfully loaded.\n");

}