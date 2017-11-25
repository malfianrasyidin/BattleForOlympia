#include <stdio.h>
#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "player.h"
#include "stackt.h"
#include "queuelist.h"

/* ############################## */
/* ########### MOVE ############# */
/* ############################## */
boolean PointInMap (POINT P, MatriksMap M){
	return((Ordinat(P) <= NKolEff(M)) && (Absis(P) <= NBrsEff(M)));
}
boolean IsMoveValid(POINT PU, POINT P, MatriksMap M){
//Mengembalikan True jika Move Unit U ke Point P Valid, False Jika Tidak.
	if (MP(UnitIn(Elmt(M,Absis(PU),Ordinat(PU)))) == 0){
		//printf("%d tes1 (%d,%d)\n", MP(UnitIn(Elmt(M,Absis(PU),Ordinat(PU)))), Absis(PU) ,Ordinat(PU));
		return(false);
	}
	else if (!PointInMap(P,M)) {
		//printf("tes2\n");
		return(false);
	}
	else if (IsUnitIn(P, M)){
		//printf("tes3\n");
		return(false);
	}
	else{
		if ((MP(getUnit(PU,M))-Distance(PU, P))>=0) return true;
		else {
			//printf("tes4\n");
			return false;
		}
	}
}

void PossibleMove (POINT PIn, MatriksMap M, MatriksMap *MOut, int *cnt)
//Mengembalikan matriks disertakan tempat2 yang mungkin di move
{
	*MOut=M;
	POINT P;
	int i;
	int j;
	for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++)	{
		for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++)	{
			Absis(P)=i;
			Ordinat(P)=j;
			if (IsMoveValid(PIn,P,M))	{
				Tipe(UnitIn(Elmt(*MOut,i,j))) = '$';
				*cnt+=1;
			}
		}
	}
}

void History(Stack *S, POINT P){
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history
	Push(S, P);
}

void MainMove(Stack *S, POINT PIn, MatriksMap *M, Player *Play)
//MainMove
{
	int cnt=0;
	MatriksMap MPrint;
	PossibleMove(PIn,*M, &MPrint,&cnt);
	if (cnt>0)	{
		PrintMap(MPrint);
		int x,y;
		printf("Please enter cell’s coordinate x y: ");
		scanf("%d %d", &x, &y);
		POINT P = MakePOINT(x,y);
		Unit U = getUnit(PIn,*M);
		while (!IsMoveValid(PIn,P,*M))	{
			printf("You can’t move there\n");
			printf("Please enter cell’s coordinate x y: ");
			scanf("%d %d", &x, &y);
			P = MakePOINT(x,y);
		}
		//update
		UnitIn(Elmt(*M,x,y))=U;
		InsVFirst(&UnitList(*Play),P);
		MP(UnitIn(Elmt(*M,x,y)))-=Distance(PIn,P);
		Locate(UnitIn(Elmt(*M,x,y)))=P;
		UnitIn(Elmt(*M,Absis(PIn),Ordinat(PIn)))=NullUnit();
		DelP(&UnitList(*Play),PIn);
		CurrentUnitPos(*Play) = P;
		printf("You have successfully moved to (%d, %d)\n", Absis(P), Ordinat(P));
		//push P
		History(S,PIn);
	} else {
		printf("Your unit can't move anywhere\n");
	}
}

void Undo (Stack *S, POINT P1, MatriksMap *M, Player *Play) {
//Mengembalikan current unit ke posisi sebelumya dan menambah movement points jika ada.
	POINT P;
	Unit U;

	if (IsEmpty(*S)){
		printf("You don't have any movement history\n");
	} else {
		U = getUnit(P1,*M);
		Pop(S, &P);
		UnitIn(Elmt(*M,Absis(P),Ordinat(P)))=U;
		InsVFirst(&UnitList(*Play),P);
		MP(UnitIn(Elmt(*M,Absis(P),Ordinat(P))))+=Distance(P1,P);
		Locate(UnitIn(Elmt(*M,Absis(P),Ordinat(P))))=P;
		UnitIn(Elmt(*M,Absis(P1),Ordinat(P1)))=NullUnit();
		DelP(&UnitList(*Play),P1);
		CurrentUnitPos(*Play) = P;
	}
}

// CHANGE & RECRUIT UNIT
QueueU MakeUnitQueue (List L){
/*Mengembaikan Queue yang berisi semua unit pada L */
	QueueU Q;
	CreateEmptyUQ(&Q);
	addressList P = First(L);
	while(P){
		AddQU(&Q,Info(P));
		if(P){
			P = Next(P);
		}
	}
	return(Q);
}

void NextUnit(QueueU *Q, POINT *U, MatriksMap M){
//I.S Q terdefinisi
//F.S Mengembalikan Unit yang akan digunakan setelahnya
	RoundP(&*Q);
	*U = InfoQU(Head(*Q));
}

POINT SearchUnit(QueueU Q, int x){
//I.S Q terdefinisi, tidak mungkin kosong
//F.S Mengembalikan Unit yang berada di urutan X pada Queue
	addressQU P;
	P = Head(Q);
	for (int i = 1 ; i < x ; i++){
	 	P = NextQU(P);
	 }
	return(InfoQU(P));
}

void ChangeCurrUnit(QueueU *Q, MatriksMap M, Player *P){
//I.S Q terdefinisi, U sembarang.
//F.S Mengganti Current Unit yang diapakai player dengan unit selanjutnya pada Queue,  
	POINT U;
	NextUnit(&*Q, &U, M);
	CurrentUnitPos(*P) = U;
	printf("%s\n",UnitTranslation(Tipe(UnitIn(Elmt(M,Absis(InfoTailQU(*Q)),Ordinat(InfoTailQU(*Q)))))) );
	printf("%s\n",UnitTranslation(Tipe(UnitIn(Elmt(M,Absis(InfoHeadQU(*Q)),Ordinat(InfoHeadQU(*Q)))))) );
	printf("You have changed your Unit to %s\n", UnitTranslation(Tipe(UnitIn(Elmt(M,Absis(U),Ordinat(U))))));
}

void AddUnit (List *L, QueueU *Q, Unit U){
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.
	POINT Ul = Locate(U);
	AddQU(&*Q,Ul);
	InsVLast(&*L,Ul);
}

void InfoRecruit(int *N){
	printf("1. Mage (30G) \n2. Archer (17G) \n3. Swordsman (25)\n");
	printf("Your desired unit : ");
	scanf("%d", &*N);
}

int EmptyCastle(Player P, MatriksMap M){
	 int i = 1;
	 boolean found = false;
	 while(!found && i <= 4){
	 	 found = IsNullUnit(UnitIn(Elmt(M,Absis(PlayerCastle(P,i)),Ordinat(PlayerCastle(P,i)))));
		if (!found){
	 		i++;
	 	}
	 }
	 if(found){
	 	return(i);
	 }
	 else{
	 	return(0);
	}
}

void RecruitUnit (Player *P, List *L, QueueU *Q, MatriksMap *M){
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan **Pesan kesalahan jika UR bukan King atau L dan Q yang sudah terisi Unit Baru jika True
	if (Tipe(getUnit(CurrentUnitPos(*P), *M)) != 'K'){
		printf("Recruit failed, only King can do this command.\n");
	}
	else if (!EQ(CurrentUnitPos(*P),PlayerTower(*P))){
		printf("King is not in the Tower, King needs to be in the Tower to do this command.\n");
	}
	else {
		printf("Which unit do you want to recruit?\n");
		int N, UPrice;
		InfoRecruit(&N);
		if (N == 1){
			UPrice = PriceMage;
		}
		else if (N == 2){
			UPrice = PriceArcher;
		}
		else{
			UPrice = PriceSwordsman;
		}

		int i = EmptyCastle(*P,*M);
		if (UPrice > PGold(*P)){
			printf("Recruit failed, you do not have enough gold.\n");
		}
		else if (!i){
			printf("Recruit failed, there is no empty castle.\n");
		}
		else{
			printf("Recruit success.\n");
			PGold(*P) -= UPrice;
			Unit U = MakeNewUnit(N,PlayNumber(*P),PlayerCastle(*P,i));
			UnitIn(Elmt(*M,Absis(PlayerCastle(*P,i)),Ordinat(PlayerCastle(*P,i)))) = U;
			AddUnit(&*L,&*Q,U);
		}
	}
}

/* ############################## */
/* ########### INFO ############# */
/* ############################## */
void PrintInfoCell (POINT P, MatriksMap M){
//F.S : Ngeprint info cell (building & unit)
	Unit U = UnitIn(Elmt(M,Absis(P),Ordinat(P)));
	Build B = BuildIn(Elmt(M,Absis(P),Ordinat(P)));
	if (IsBuildIn(P,M))	{	
		printf("== Cell Info ==\n");
		printf("%s\n", UnitTranslation(TipeB(B)));
		printf("Owned by Player %d\n", OwnerB(B));
	} else {
		printf("There is no building here\n");
	}
	if (IsUnitIn(P,M))	{
		printf("== Unit Info ==\n");
		printf("%s\n", UnitTranslation(Tipe(U)));
		printf("Owned by Player %d\n", Owner(U));
		printf("Health: %d/%d | ", HP(U), MaxHP(U));
		printf("ATK: %d | ", DamagePoints(U));
	} else {
		printf("There is no unit here\n");
	}
}

void MainInfo(MatriksMap M)	{
//main info
	int x,y;
	POINT P;
	printf("Enter the coordinate of the cell : ");
	scanf("%d %d", &x, &y);
	P = MakePOINT(x,y);
	while (!PointInMap(P,M))	{
		printf("Enter the coordinate of the cell : ");
		scanf("%d %d", &x, &y);
		P = MakePOINT(x,y);
	}
	PrintInfoCell(P,M);
	printf("\n");
}
