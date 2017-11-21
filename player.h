#ifndef PLAYER__H
#define PLAYER__H

#include "boolean.h"
#include "listdpUnit.h"
#include "unit.h"

typedef struct {
    int PlayerNumber;
    Unit CurrUnit;
    int Gold;
    int Income;
    int UpKeep;
    List ListOfUnits;
    List ListOfVillages;
    POINT CastlePointer;
    POINT TowersPointer[4];
} Player;

typedef Player ArrPlayer[3];

#define PlayNumber(P)       (P).PlayerNumber
#define PGold(P) 			(P).Gold
#define CurrentUnit(P)		(P).CurrUnit
#define PIncome(P)			(P).Income
#define PUpKeep(P)			(P).UpKeep
#define UnitList(P)			(P).ListOfUnits
#define VillageList(P)		(P).ListOfVillages
#define PlayerCastle(P)		(P).CastlePointer
#define TabTower(P)			(P).TowersPointer
#define PlayerTower(P,i) 	(P).TowersPointer[i-1]


void AttackU (Unit U1, Unit U2);
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1

#endif