#include "unit.h"
#include "point.h"
#include "boolean.h"
#include "math.h"

//FUNGSI NULLITAS
Unit NullUnit(){
	Unit U;
	Absis(Locate(U)) = 0;
	Ordinat(Locate(U)) = 0;
	MaxHP(U) = 0;
	MaxMP(U) = 0;
	HP(U) = 0;
	MP(U) = 0;
	Owner(U) = 0;
	Tipe(U) = " ";

	return(U);
}

//FUNGSI FUNGSI UNIT
int Distance(POINT P1, POINT P2){
//Mengembalikan jarak antara titik P1 dan P2.
	int X, Y;

	X = Absis(P1) - Absis(P2);
	if (X<0){
		X*=-1;
	}
	Y = Ordinat(P1) - Ordinat(P2);
	if(Y<0){
		Y*=-1;
	}
	return (X+Y);
}

boolean IsAdjacent (POINT P1, POINT P2){
//Mengeluarkan True Jika P1 dan P2 Adjacent atau beda sepetak dengan U2.
	return (Distance(P1,P2)==1);
}

// boolean IsTopPresent(Unit U){
// //Mengembalikan True jika terdapat unit lain di sebelah atas unit U.
// 	Location L;
// 	L.Loc = PlusDelta(Locate(U).Loc, 0, 1);
// 	return (IsUnitIn(L));
// }

// boolean IsBottomPresent(Unit U){
// //Mengembalikan True jika terdapat unit lain di sebelah bawah unit U.
// 	Location L;
// 	L.Loc = PlusDelta(Locate(U).Loc, 0, -1);
// 	return (IsUnitIn(L));
// }

// boolean IsRightPresent(Unit U){
// //Mengembalikan True jika terdapat unit lain di sebelah kanan unit U.
// 	Location L;
// 	L.Loc = PlusDelta(Locate(U).Loc, 1, 0);
// 	return (IsUnitIn(L));
// }

// boolean IsLeftPresent(Unit U){
// //Mengembalikan True jika terdapat unit lain di sebelah kiri unit U.
// 	Location L;
// 	L.Loc = PlusDelta(Locate(U).Loc, -1, 0);
// 	return (IsUnitIn(L));
// }

boolean IsEnemy(Unit U1, Unit U2){
//Mengembalikan True jika U2 adalah musuh dari U1 (U1 ialah player yang sedang bermain)
	return(Owner(U1)!=Owner(U2));
}

// boolean IsCanAttack(Unit U){
// //Mengembalikan True jika U dapat melakukan attack.	
// 	boolean Top, Bottom, Right, Left;
// 	POINT PTop,PBottom, PRight, PLeft;

// 	PTop = NextY(Locate(U));
// 	PRight = NextX(Locate(U));
// 	PLeft = PlusDelta(Locate(U).Loc, -1, 0);
// 	PBottom = PlusDelta(Locate(U).Loc, 0, -1);

// }

Unit MakeUnit (int Owner, char Type, POINT Loc);
//Membuat Unit Baru dengan Owner, Type, dan Location yang dispesifikkan

void AttackU (Unit U1, Unit U2, Atk A);
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1

void PrintAtkType(Unit U);
//Memprint ke layar Tipe Attack yang dapat dilakukan oleh Unit U
