#ifndef _UNIT_H
#define _UNIT_H

#include "point.h"
#include "boolean.h"


#define BaseMaxHPArcher 70
#define BaseMaxHPWarrior 90
#define BaseMaxHPMage 120
#define BaseMaxHPKing 200

#define BaseMaxMPArcher 100
#define BaseMaxMPWarrior 80
#define BaseMaxMPMage 150
#define BaseMaxMPKing 210

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
	int price;
} Unit;

#define Locate(U) (U).Loc
#define HP(U) (U).CurrHP
#define Tipe(U) (U).KarType
#define MP(U) (U).CurrMP
#define Owner(U) (U).POwner
#define MaxHP(U) (U).MaximumHP
#define MaxMP(U) (U).MaximumMP
#define TabAttack (U).TAttack
#define Attack(U,i) (U).TAttack[i-1]
#define CanAtk(U)	(U).CanAtk
#define Price(U)	(U).price

//FUNGSI NULLITAS
Unit NullUnit ();

///Initial Status of Unit///
Unit InitArcher(POINT P, int Owner);
//F.S : King dengan state awal

Unit InitWarrior(POINT P, int Owner);
//F.S : King dengan state awal

Unit InitMage(POINT P, int Owner);
//F.S : King dengan state awal

Unit InitKing(POINT P, int Owner);
//F.S : King dengan state awal

//FUNGSI FUNGSI UNIT
int Distance(POINT U1, POINT U2);
//Mengembalikan jarak antara karakter 1 dan 2.

boolean IsAdjacent (POINT P1, POINT P2);
//Mengeluarkan True Jika U1 dan U2 Adjacent atau beda sepetak dengan U2.

boolean IsEnemy(Unit U1, Unit U2);
//I.S:U1 && U2 tidak null
//Mengembalikan true jika U2 adalah musuh dari U1 (U1 ialah player yang sedang bermain)

void AttackU (Unit U1, Unit U2, Atk A);
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1

void PrintAtkType(Unit U);
//Memprint ke layar Tipe Attack yang dapat dilakukan oleh Unit U

void PrintInfoUnit (Unit U);
/* mengeluarkan info unit standar seperti dibawah ini
Unit: King(2,1) | Health 20/20 | Movement Point: 2 | Can Attack: Yes */

boolean CmpUnit (Unit U1, Unit U2);
//True jika U1==U2

#endif
