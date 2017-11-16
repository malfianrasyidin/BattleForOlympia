#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include <stdio.h>
#include "stackt.h"

/* ############################## */
/* ########### MOVE ############# */
/* ############################## */
boolean PointInMap (POINT P, MatriksMap M){
	return((Ordinat(P) <= NBrsEff(M)) && (Absis(P) <= NKolEff(M)));
}
boolean IsMoveValid(Unit U, POINT P, MatriksMap M){
//Mengembalikan True jika Move Unit U ke Point P Valid, False Jika Tidak.
	if (MP(U) == 0){
		return(false);
	}
	else if (!PointInMap(P,M)) {
		return(false);
	}
	else if (IsUnitIn(P,M)) {
		return(false);
	}
	else{
		if ((MP(U)-Distance(Locate(U), P))>=0) return true;
		else return false;
	}
}

MatriksMap PossibleMove (Unit U, MatriksMap M)
//Mengembalikan matriks disertakan tempat2 yang mungkin di move
{
	MatriksMap MOut;
	MOut=M;
	POINT P;
	int i;
	int j;
	j=Ordinat(Locate(U));
	Ordinat(P)=j;
	for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++)	{
		Absis(P)=i;
		if (IsMoveValid(U,P,M))	{
			UnitIn(Elmt(MOut,i,j)).KarType = "$";
		}
	}
	i=Absis(Locate(U));
	Absis(P)=i;
	for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++)	{
		Ordinat(P)=j;
		if (IsMoveValid(U,P,M))	{
			UnitIn(Elmt(MOut,i,j)).KarType = "$";
		}
	}
	return MOut;
}
void MainMove(Stack *S, Unit *U, MatriksMap *M)
//MainMove
{
	MatriksMap MPrint;
	MPrint = PossibleMove(*U,*M);
	PrintMap(MPrint);
	int x,y;
	printf("Please enter cell’s coordinate x y: ");
	scanf("%d %d", &x, &y);
	POINT P=MakePOINT(x,y);
	while (!IsMoveValid(*U,P,*M))	{
		printf("You can’t move there\n");
		printf("Please enter cell’s coordinate x y: ");
		scanf("%d %d", &x, &y);
		POINT P=MakePOINT(x,y);
	}
	//update
	MP(*U)-=Distance(Locate(*U),P);
	Locate(*U)=P;
	UnitIn(Elmt(*M,x,y))=*U;
	*U=NullUnit();
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

void History(Stack *S, POINT P){
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history
	Push(S, P);
}


// CHANGE & RECRUIT UNIT
Queue MakeUnitQueue (List L){
/*Mengembaikan Queue yang berisi semua unit pada L */
	Queue Q;
	addressQ P = First(L);
	while(P){
		Add(&Q,Info(P));
		P = Next(P);
	}
}

void NextUnitQ (Queue *Q, Unit *U, MatriksMap M){
//I.S Q terdefinisi
//F.S Mengembalikan Unit yang akan digunakan setelahnya
	RoundP(&*Q);
	P = Info(Head(*Q));
	*U = UnitIn(Elmt(M,Absis(P),Ordinat(P)));
}

Unit SearchUnit(Queue Q, int x){
//I.S Q terdefinisi, tidak mungkin kosong
//F.S Mengembalikan Unit yang berada di urutan X pada Queue
	P = Head(Q);
	for (i = 1 ; i < x ; i++){
		P = Next(P);
	}
}

void ChangeCurrUnit(Queue *Q, MatriksMap M, Player *P){
//I.S Q terdefinisi, U sembarang.
//F.S Mengganti Current Unit yang diapakai player dengan unit selanjutnya pada Queue,  
	Unit U;
	NextUnitQ(&*Q, &U, M);
	CurrentUnit(*P) = U;
}

void AddUnit (List *L, Queue *Q, Unit U){
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.
	POINT Ul = Locate(U);
	Add(&*Q,Ul);
	InsVLast(&*L,P);
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
		found = UnitIn(M,Absis(PlayerTower(P,i)),Ordinat(PlayerTower(P,i))) != NullUnit();
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

void RecruitUnit (Player P, List *L, Queue *Q, MatriksMap M){
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan Pesan kesalahan jika UR bukan King atau L dan Q yang sudah terisi Unit Baru jika True
	if (Tipe(CurrentUnit(P)) != 'K'){
		printf("Unit yang dipakai Bukan King, Recruit Gagal.\n");
	}
	else if (Locate(CurrentUnit(P)) != PlayerCastle(P)){
		printf("King Tidak di Castle, Recruit Gagal\n");
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
		int i = EmptyTower(P,M)
		if (UPrice > PGold(P)){
			printf("Anda tidak memiliki Gold yang Cukup\n");
		}
		else if (!i){
			printf("Tidak Ada Tower yang kosong\n");
		}
		else{
			printf("Recruit berhasil\n");
			Unit U = MakeNewUnit(N,PlayNumber(P),PlayerTower(P,i));
			Unit(Elmt(M,Absis(PlayerTower(P,i)),Ordinat(PlayerTower(P,i)))) = U;
			AddUnit(&*L,&*Q,U);
		}
	}
}

/* ############################## */
/* ########### INFO ############# */
/* ############################## */
void PrintInfoCell (POINT P, MatriksMap M){
//F.S : Ngeprint info cell (building & unit)
	if (IsUnitIn(P,M))	{	
		printf("== Cell Info ==\n");
		printf("%s\n", Kepanjangan(TipeB(UnitIn(Elmt(Absis(P),Ordinat(P))))));
		printf("Owned by Player %d\n", OwnerB(UnitIn(Elmt(Absis(P),Ordinat(P)))));
	} else {
		printf("There isn't building here\n");
	}
	if (IsBuildIn(P,M))	{
		printf("== Unit Info ==\n");
		printf("%s\n", Kepanjangan(Tipe(BuildIn(Elmt(Absis(P),Ordinat(P))))));
		printf("Owned by Player %d\n", Owner(UnitIn(Elmt(Absis(P),Ordinat(P)))));
		printf("Health: %d/%d | ", HP(U), MaxHP(U));
		printf("ATK: %d | ", Damage(U));
	} else {
		printf("There isn't unit here\n");
	}

}
void Info(MatriksMap M)	{
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