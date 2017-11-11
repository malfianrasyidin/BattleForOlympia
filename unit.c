#include "unit.h"
#include "MatriksMap.h"
#include "point.h"
#include "boolean.h"

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
	Tipe(U) = ' ';
	return(U);
}

//FUNGSI LOCATION
boolean IsNormal (Location L){
//Mengembalikan true jika L merupakan Lokasi Normal, false jika tidak
	return(Building(L) == ' ');
}

boolean IsUnitIn (Location L){
//Mengembalikan true jika ada unit di L dan false jika tidak
	return(UnitIn(L) == ' ');
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
