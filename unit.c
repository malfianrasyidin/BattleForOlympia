#include "MatMap.h"
#include "unit.h"
#include "boolean.h"

//FUNGSI LOCATION
boolean IsNormal (Location L){
//Mengembalikan true jika L merupakan Lokasi Normal, false jika tidak
	return(Building(L) == ' ');
}

boolean IsUnitIn (Location L){
//Mengembalikan true jika ada unit di L dan false jika tidak
	return(UnitIn(L) == ' ');
}

boolean IsMoveValid (Unit U, POINT P){
//Mengembalikan True jika Move Unit U ke Point P Valid, False Jika Tidak.
	if (MP(U) == 0){
		return(false);
	}
	else if (!PointInMap){
		return(false);
	}
	else{
		int M = MP(U);
		POINT PointU = Locate(U);
		while (Absis(PointU) > Absis(P)){
			Absis(PointU)++;
			M--;
		}
		while (Absis(PointU) < Absis(P)){
			Absis(PointU)--;
			M--;
		}
		while (Ordinat(PointU) > Ordinat(P)){
			Ordinat(PointU)++;
			M--;
		}
		while (!(Ordinat(PointU) < Ordinat(P)){
			Ordinat(PointU)--;
			M--;
		}
		return(M != 0);
	}
}

//FUNGSI FUNGSI UNIT
boolean IsUnitAdjacent (Unit U1, Unit U2);
//Mengeluarkan True Jika U1 dan U2 Adjacent atau beda sepetak dengan U2.

Unit MakeUnit (int Owner, char Type, POINT Loc);
//Membuat Unit Baru dengan Owner, Type, dan Location yang dispesifikkan

void AttackU (Unit U1, Unit U2, Atk A);
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1

void PrintAtkType(Unit U);
//Memprint ke layar Tipe Attack yang dapat dilakukan oleh Unit U
