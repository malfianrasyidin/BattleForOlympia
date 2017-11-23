#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mesinkar.h"
#include "mesinkata.h"
#include "boolean.h"
#include "load.h"

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
	*chr = CKata.TabKata[0];
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
	
	/* ALGORITMA */
	ReadPoint(&Locate(*U));
	kataToChar(CKata, &Tipe(*U));
	ADVKATA();
	kataToInt(CKata, &MaxHP(*U));
	ADVKATA();
	kataToInt(CKata, &HP(*U));
	ADVKATA();
	kataToInt(CKata, &MaxMP(*U));
	ADVKATA();
	kataToInt(CKata, &MP(*U));
	ADVKATA();
	kataToChar(CKata, &AtkType(*U));
	ADVKATA();
	kataToInt(CKata, &Damage(*U));
	ADVKATA();
	kataToInt(CKata, &Heal(*U));
	ADVKATA();
	kataToInt(CKata, &CanAtk(*U));
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
	ReadBuild(L.Build);
	ReadUnit(L.Unit);
}

void ReadListOfPoint(List *L)
/* I.S. B sembarang, CKata ada di kata pertama*/
/* F.S. Build B terdefinisi */
{	/* KAMUS LOKAL */
	POINT PTemp;
	/* ALGORITMA */
	CreateEmpty(L);
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
	kataToInt(CKata, &PIncome(*P));
	ADVKATA();
	kataToInt(CKata, &PUpKeep(*P));
	ADVKATA();
	ReadUnit(&CurrentUnit(*P));
	ReadListOfPoint(&UnitList(*P));
	ReadListOfPoint(&VillageList(*P));
	ReadPoint(&TabTower(*P));
	for (int i = 1; i <= 4; ++i){
		ReadPoint(&PlayerTower(*P,i));
	}
}

void ReadUndo(Stack *S)
/* I.S. S sembarang, CKata ada di kata pertama*/
/* F.S. Stack S terdefinisi */
{	/* KAMUS LOKAL */
	POINT PTemp;
	/* ALGORITMA */
	CreateEmpty(S);
	while(strcmp(CKata.TabKata, "EndOfStack")) {
		ReadPoint(&PTemp);
		Push(S, PTemp);
	}
	ADVKATA();
}

void ReadTurn(Queue *Q)
/* I.S. Q sembarang, CKata ada di kata pertama*/
/* F.S. Queue Q terdefinisi */
{	/* KAMUS LOKAL */
	int playertemp;
	/* ALGORITMA */
	CreateEmpty(Q);
	while(strcmp(CKata.TabKata, "EndOfQueue")) {
		kataToInt(CKata, &playertemp);
		Add(Q, playertemp);
		ADVKATA();
	}
	ADVKATA();
}

void Load(Location *Loc, Player *Player1, Player *Player2, Queue *Turn, Stack *Undo)
/* Melakukan load file */
/* I.S. file pitakar.txt berisi hasil save, semua parameter tidak terdefinisi*/
/* F.S. mendefinisikan semua parameter */
{	/* KAMUS LOKAL */
	/* ALGORITMA */
	STARTKATA();
	ReadLocation(Loc);
	ReadPlayer(Player1);
	ReadPlayer(Player2);
	WriteTurn(Turn);
	WriteUndo(Undo);
	while (!EndKata) {
		ADVKATA();
	}
}