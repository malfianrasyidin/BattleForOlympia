#include "player.h"
#include "boolean.h"
#include "listdpUnit.h"
#include "unit.h"
#include "point.h"
#include "queuelist.h"
#include "MatriksMap.h"
#include <stdio.h>
#include <stdlib.h>

void InitPlayer (Player *P1, Player *P2, int NB, int NK)
//Membuat player pada kondisi awal
{	/* ALGORITMA */
	
	//Player 1 Initial data
	PlayNumber(*P1) = 1;
	PGold(*P1) = StartingGold;
	CurrentUnitPos(*P1) = MakePOINT(NB-1,KolMin+1); // Posisi King pada awal
	PIncome(*P1) = 0;
	PUpKeep(*P1) = 0;
	
	CreateEmptyList(&UnitList(*P1));
	InsVFirst(&UnitList(*P1), CurrentUnitPos(*P1));

	CreateEmptyList(&VillageList(*P1));

	PlayerCastle(*P1, 1) = MakePOINT(NB-2,KolMin+1);
	PlayerCastle(*P1, 2) = MakePOINT(NB-1,KolMin+2);
	PlayerCastle(*P1, 3) = MakePOINT(NB,KolMin+1);
	PlayerCastle(*P1, 4) = MakePOINT(NB-1,KolMin);

	TabTower(*P1) = MakePOINT(NB-1,KolMin+1);

	//Player 2 Initial data
	PlayNumber(*P2) = 2;
	PGold(*P2) = StartingGold;
	CurrentUnitPos(*P2) = MakePOINT(BrsMin+1,NK-1); // Posisi King pada awal
	PIncome(*P2) = 0;
	PUpKeep(*P2) = 0;
	
	CreateEmptyList(&UnitList(*P2));
	InsVFirst(&UnitList(*P2), CurrentUnitPos(*P2));

	CreateEmptyList(&VillageList(*P2));

	PlayerCastle(*P2, 1) = MakePOINT(BrsMin+2,NK-1);
	PlayerCastle(*P2, 2) = MakePOINT(BrsMin+1,NK-2);
	PlayerCastle(*P2, 3) = MakePOINT(BrsMin,NK-1);
	PlayerCastle(*P2, 4) = MakePOINT(BrsMin+1,NK);

	TabTower(*P2) = MakePOINT(BrsMin+1,NK-1);

}

void WinningPlayer(Player P)
// Menyerahkan kemenangan permainan kepada Player P
{
	printf("Congratulations to Player %d who valiantly defeated the forces of Player %d\n", PlayNumber(P), (PlayNumber(P) == 1)? 2 : 1);
	printf("\n");
	printf("Press any key to exit the game...\n");
	getchar();
	exit(EXIT_SUCCESS);
}

List EnemyCanBeAttacked(Unit U, MatriksMap M) {
//Mengembalikan List enemy yg bisa di attack.	
	boolean Top, Bottom, Right, Left;
	POINT PTop,PBottom, PRight, PLeft;
	List L;
	CreateEmptyList(&L);
	
	PTop = NextY(Locate(U));
	PRight = NextX(Locate(U));
	PLeft = PlusDelta(Locate(U), -1, 0);
	PBottom = PlusDelta(Locate(U), 0, -1);
	
	Top = IsUnitIn(PTop,M) && IsEnemy(U,getUnit(PTop,M));
	if (Top){
		InsVFirst(&L,PTop);
	}
	Bottom = IsUnitIn(PBottom,M) && IsEnemy(U,getUnit(PBottom,M));
	if (Bottom) {
		InsVFirst(&L,PBottom);
	}
	Right = IsUnitIn(PRight,M) && IsEnemy(U,getUnit(PRight,M));
	if (Right) {
		InsVFirst(&L,PRight);
	}
	Left = IsUnitIn(PLeft,M) && IsEnemy(U,getUnit(PLeft,M));
	if (Left) {
		InsVFirst(&L,PLeft);
	}
	return (L);
}

void PrintListUnit (List L, MatriksMap M, Unit U)
/* I.S. List mungkin kosong */
/* F.S. 
== List of Units ==
1. King (2,1) | Health 20
2. Swordsman (3,5) | Health 20
*/
{
	printf("== List Of Unit ==");
	addressList p = First(L);
	int i=1;
	while (p!=Nil) {
		printf("%d. ",i);
		printf("Unit: %s (%d,%d) | ", UnitTranslation(Tipe(UnitIn(Elmt(M, Absis(Info(p)), Ordinat(Info(p)))))), 
			Absis(Info(p)), Ordinat(Info(p)));
		printf("Health: %d/%d ", HP(UnitIn(Elmt(M, Absis(Info(p)), Ordinat(Info(p))))), 
			MaxHP(UnitIn(Elmt(M, Absis(Info(p)), Ordinat(Info(p))))));
		if (AttackType(U) == AttackType(UnitIn(Elmt(M, Absis(Info(p)), Ordinat(Info(p)))))) {
			printf(" (Retaliates)");
		}
		if (Next(p)!=Nil) {
			printf("\n");
		}
		p = Next(p);
	}
}

POINT ChooseAttack (List L, int Choice)
{
	addressList P = First(L);
	int i = 1;

	do {
		if (i == Choice) {
			return Info(P);
		}
	} while (P != Nil && i <= Choice);
}

void Attack (MatriksMap *M, Player *P1, Player *P2)
/* Menyerang  */
{
	if (CanAttack(getUnit(CurrentUnitPos(*P1), *M))) {
		List L;
		L = EnemyCanBeAttacked(getUnit(CurrentUnitPos(*P1), *M), *M);
		if (NbElmtList(L) > 0 ) {
			PrintListUnit(L, *M, getUnit(CurrentUnitPos(*P1), *M));
			printf("Select enemy you want to attack: ");
			int AttackChoice;
			do {
				scanf("%d", &AttackChoice);
				if (AttackChoice <= 0 || AttackChoice > NbElmtList(L)) {
					printf("Your input was wrong. Try again.");
				}
			} while (AttackChoice <= 0 || AttackChoice > NbElmtList(L));
			
			AttackU(M, P1, P2, ChooseAttack(L, AttackChoice));

		} else {
			printf("There are no enemy units nearby\n");
		}
	} else {
		printf("This unit currently cannot attack anyone\n");
	}
}

void AttackU (MatriksMap *M, Player *P1, Player *P2, POINT PU2)
//Membuat Unit 1 Menyerang Unit 2
{
	HP(UnitIn(Elmt(*M, Absis(PU2), Ordinat(PU2)))) -= DamagePoints(getUnit(CurrentUnitPos(*P1), *M));
	printf("Enemy's %s is damaged by %d.\n", UnitTranslation(Tipe(getUnit(PU2, *M))), DamagePoints(getUnit(CurrentUnitPos(*P1), *M)));
	if (HP(getUnit(PU2, *M)) <= 0) { // Jika HP dari U2 habis
		printf("Enemy's %s is dead.\n", UnitTranslation(Tipe(getUnit(PU2, *M))));
		if (Tipe(getUnit(PU2, *M)) == 'K') {
			WinningPlayer(*P1); // Jika karakter yang diserang dan HPnya habis adalah king maka player yang menyerang memenangkan permainan
		}
        DelP(&UnitList(*P2), PU2);
		UnitIn(Elmt(*M, Absis(PU2), Ordinat(PU2))) = NullUnit();
	} else if (Tipe(getUnit(PU2, *M)) == 'K' || AttackType(getUnit(CurrentUnitPos(*P1), *M)) == AttackType(getUnit(PU2, *M)) && HP(getUnit(PU2, *M)) > 0 ) {
		printf("Enemy's %s retaliates.\n", UnitTranslation(Tipe(getUnit(PU2, *M))));
		HP(UnitIn(Elmt(*M, Absis(CurrentUnitPos(*P1)), Ordinat(CurrentUnitPos(*P1))))) -= DamagePoints(getUnit(PU2, *M));
		printf("Your %s is damaged by %d.\n", UnitTranslation(Tipe(getUnit(CurrentUnitPos(*P1), *M))), DamagePoints(getUnit(PU2, *M)));
		if (HP(getUnit(CurrentUnitPos(*P1), *M)) <= 0) { // Jika HP dari U1 habis setelah counter attack
        	printf("Your %s is dead.\n", UnitTranslation(Tipe(getUnit(CurrentUnitPos(*P1), *M))));
			if (Tipe(getUnit(CurrentUnitPos(*P1), *M)) == 'K') {
				WinningPlayer(*P2); // Jika karakter yang menyerang dan terkena counter attack lalu HPnya habis adalah king maka player yang diserang memenangkan permainan
			}
			DelP(&UnitList(*P1), CurrentUnitPos(*P1));
			UnitIn(Elmt(*M, Absis(CurrentUnitPos(*P1)), Ordinat(CurrentUnitPos(*P1)))) = NullUnit();
		}
	}
}

/*** BUAT QUEUE PLS JGN DIGANGGU GUGAT ***/

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{	/* ALGORTIMA */
	return ((Head(Q) == Nol) && (Tail(Q) == Nol));
}

boolean IsQFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElmt */
{	/* ALGORTIMA */
	return ((Head(Q) == (Tail(Q) + 1)) || ((Head(Q) == 1) && (Tail(Q) == MaxElmt(Q))));
}

int NBElmtQ (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{	/* ALGORTIMA */
	if (IsQEmpty(Q)) {
		return 0;
	}
	else if (Tail(Q) > Head(Q)) {
		return (Tail(Q) - Head(Q) + 1);
	}
	else {
		return (MaxElmt(Q) - Head (Q) + 1 + Tail(Q));
	}
}


/* *** Kreator *** */
void CreateEmptyQ (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElmt=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{	/* ALGORTIMA */
	(* Q).T = (infotypeQ *) malloc ((Max + 1) * sizeof(infotypeQ));
	if ((*Q).T != NULL) {
		MaxElmt(*Q) = Max;
		Head(*Q) = Nol;
		Tail(*Q) = Nol;
	}
	else {
	MaxElmt(*Q) = 0;
	}
}


/* *** Destruktor *** */
void DeAlokasiQ(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElmt(Q) diset 0 */
{	/* ALGORTIMA */
    MaxElmt(* Q) = 0;
    free((* Q).T);
}


/* *** Primitif Add/Delete *** */
void AddQ (Queue * Q, infotypeQ X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{	/* ALGORTIMA */
	if (IsQEmpty(* Q)) {
		Head(* Q) = 1;
		Tail(* Q) = 1;
	}
	else if (Tail(* Q) == MaxElmt(* Q)) {
		Tail(* Q) = 1;
	}
	else {
		Tail(* Q) = Tail(* Q) + 1;
	}
	InfoTail(* Q) = X;
}

void DelQ (Queue * Q, infotypeQ * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{	/* ALGORTIMA */
	(* X) = InfoHead(* Q);
	if (NBElmtQ(* Q) == 1) {
		Head(* Q) = 0;
		Tail(* Q) = 0;
	}
	else if (Head(* Q) == MaxElmt(* Q)) {
		Head(* Q) = 1;
	}
	else {
		++Head(* Q);
	}
}

void CreateTurn (Queue * Q, Player P1, Player P2) {
	/* Membuat turn dengan urutan 1 dan 2 */
	/* ALGORITMA */
	CreateEmptyQ(Q, 2);
	AddQ(Q, &P1);
	AddQ(Q, &P2);
}

void NextTurn (Queue * Q, Player * CurrentPlayer) {
	/* Mengubah head -> tail dan tail -> head */
	infotypeQ X;
	/* ALGORITMA */
	DelQ(Q, &X);
	AddQ(Q, X);
	CurrentPlayer = InfoHead(* Q);
}

infotypeQ CurrentTurn (Queue Q) {
	/* Mengambilkan turn saat ini */
	return InfoHead(Q);
}
