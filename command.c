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
	return((Ordinat(P) <= NBrsEff(M)) && (Absis(P) <= NKolEff(M)));
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

MatriksMap PossibleMove (POINT PIn, MatriksMap M)
//Mengembalikan matriks disertakan tempat2 yang mungkin di move
{
	MatriksMap MOut;
	MOut=M;
	POINT P;
	int i;
	int j;
	j=Ordinat(PIn);
	Ordinat(P)=j;
	for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++)	{
		Absis(P)=i;
		if (IsMoveValid(PIn,P,M))	{
			UnitIn(Elmt(MOut,i,j)).UnitType = '$';
		}
	}
	i=Absis(PIn);
	Absis(P)=i;
	for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++)	{
		Ordinat(P)=j;
		if (IsMoveValid(PIn,P,M))	{
			UnitIn(Elmt(MOut,i,j)).UnitType = '$';
		}
	}
	return MOut;
}

void History(Stack *S, POINT P){
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history
	Push(S, P);
}

void MainMove(Stack *S, POINT PIn, MatriksMap *M, Player *Play)
//MainMove
{
	MatriksMap MPrint;
	MPrint = PossibleMove(PIn,*M);
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
		POINT P = MakePOINT(x,y);
	}
	//update
	UnitIn(Elmt(*M,x,y))=U;
	InsVFirst(&UnitList(*Play),P);
	MP(UnitIn(Elmt(*M,x,y)))-=Distance(PIn,P);
	Locate(UnitIn(Elmt(*M,x,y)))=P;
	UnitIn(Elmt(*M,Absis(PIn),Ordinat(PIn)))=NullUnit();
	DelP(&UnitList(*Play),PIn);
	printf("You have successfully moved to (%d, %d)\n", Absis(P), Ordinat(P));
	//push P
	History(S,P);
}

void Undo (Stack *History, Unit *U) {
//Mengembalikan current unit ke posisi sebelumya dan menambah movement points jika ada.
	POINT P;

	if (IsEmpty(*History)){
		printf("You don't have any movement history");
	} else {
		Pop(History, &P);
		Absis(Locate(*U)) = Absis(P);
		Ordinat(Locate(*U)) =  Ordinat(P);
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
}

void AddUnit (List *L, QueueU *Q, Unit U){
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.
	POINT Ul = Locate(U);
	AddQU(&*Q,Ul);
	InsVLast(&*L,Ul);
}

void InfoRecruit(int *N){
	printf("1. Warrior\n2. Archer\n3. Mage \n");
	printf("Unit yang diinginkan : ");
	scanf("%d", &*N);
}

int EmptyTower(Player P, MatriksMap M){
	 int i;
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

void RecruitUnit (Player P, List *L, QueueU *Q, MatriksMap M){
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan Pesan kesalahan jika UR bukan King atau L dan Q yang sudah terisi Unit Baru jika True
	if (Tipe(getUnit(CurrentUnitPos(P), M)) != 'K'){
		printf("Unit yang dipakai Bukan King, Recruit Gagal.\n");
	}
	else if (!EQ(CurrentUnitPos(P),PlayerTower(P))){
		printf("King Tidak di Tower, Recruit Gagal\n");
	}
	else {
		printf("Pilih Unit yang Ingin di recruit\n");
		int N, UPrice;
		InfoRecruit(&N);
		if (N == 1){
			UPrice = PriceWarrior;
		}
		else if (N == 2){
			UPrice = PriceArcher;
		}
		else{
			UPrice = PriceMage;
		}

		int i = EmptyTower(P,M);
		if (UPrice > PGold(P)){
			printf("Anda tidak memiliki Gold yang Cukup\n");
		}
		else if (!i){
			printf("Tidak Ada Tower yang kosong\n");
		}
		else{
			printf("Recruit berhasil\n");
			Unit U = MakeNewUnit(N,PlayNumber(P),PlayerCastle(P,i));
			UnitIn(Elmt(M,Absis(PlayerCastle(P,i)),Ordinat(PlayerCastle(P,i)))) = U;
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
		printf("There isn't building here\n");
	}
	if (IsUnitIn(P,M))	{
		printf("== Unit Info ==\n");
		printf("%s\n", UnitTranslation(Tipe(U)));
		printf("Owned by Player %d\n", Owner(U));
		printf("Health: %d/%d | ", HP(U), MaxHP(U));
		printf("ATK: %d | ", DamagePoints(U));
	} else {
		printf("There isn't unit here\n");
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
}
