#ifndef _UNIT_H
#define _UNIT_H

#include "unit.h"
#include "point.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

#define BaseMaxHPArcher 29
#define BaseMaxHPSwordsman 55
#define BaseMaxHPMage 35
#define BaseMaxHPKing 70

#define BaseMaxMPArcher 6
#define BaseMaxMPSwordsman 5
#define BaseMaxMPMage 5
#define BaseMaxMPKing 6

#define PriceSwordsman 25
#define PriceArcher  17
#define PriceMage    30

#define BaseDmgPointSwordsman 16
#define BaseDmgPointArcher 13
#define BaseDmgPointMage 8
#define BaseDmgPointKing 18

#define BaseHealMage 8
#define BaseHealVillage 10


typedef struct{
	int DamagePoints;
	char AttackType;
	int HealPoints;
	boolean CanAtk;
	POINT Loc;
	int MaximumHP;
	int CurrHP;
	int MaximumMP;
	int CurrMP;
	int UnitOwner;
	char UnitType;
} Unit;

#define DamagePoints(U) (U).DamagePoints
#define AttackType(U) 	(U).AttackType
#define HealPoints(U) 	(U).HealPoints
#define Locate(U) 			(U).Loc
#define HP(U) 					(U).CurrHP
#define Tipe(U) 				(U).UnitType
#define MP(U) 					(U).CurrMP
#define Owner(U) 				(U).UnitOwner
#define MaxHP(U) 				(U).MaximumHP
#define MaxMP(U) 				(U).MaximumMP
#define CanAttack(U)		(U).CanAtk

//FUNGSI NULLITAS
Unit NullUnit ();

Unit MakeNewUnit(int N, int Play, POINT P);
//mengembalikan unit baru dengan initial state

//FUNGSI FUNGSI UNIT
int Distance(POINT U1, POINT U2);
//Mengembalikan jarak antara karakter 1 dan 2.

boolean IsEnemy(Unit U1, Unit U2);
//I.S:U1 && U2 tidak null
//Mengembalikan true jika U2 adalah musuh dari U1 (U1 ialah player yang sedang bermain)

char* UnitTranslation(char Tipe);
//Mengembalikan singkatan dari unit yang akan ditampilkan di peta.

void PrintInfoUnit (Unit U);
/* mengeluarkan info unit standar seperti dibawah ini
Unit: King(2,1) | Health 20/20 | Movement Point: 2 | Can Attack: Yes */

boolean IsNullUnit(Unit U);

#endif
