#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include <stdio.h>

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