#include "unit.h"
#include "point.h"
#include "boolean.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>


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

Unit InitArcher(POINT P,int Owner)
//F.S : King dengan state awal
{
	Unit U;
	Locate(U)=P;
	MaxHP(U)=BaseMaxHPArcher;
	HP(U)=BaseMaxHPArcher;
	MaxMP(U)=BaseMaxMPArcher;
	MP(U)=BaseMaxMPArcher;
	Owner(U)=Owner;
	Tipe(U)="Archer";
	CanAtk(U)=true;
	DamagePoints(U)=45;
	AttackType(U)="Ranged";
	HealPoints(U) = 0;
	Price(U)=5;
	return U;
}

Unit InitWarrior(POINT P,int Owner)
//F.S : King dengan state awal
{
	Unit U;
	Locate(U)=P;
	MaxHP(U)=BaseMaxHPWarrior;
	HP(U)=BaseMaxHPWarrior;
	MaxMP(U)=BaseMaxMPWarrior;
	MP(U)=BaseMaxMPWarrior;
	Owner(U)=Owner;
	Tipe(U)="Warrior";
	CanAtk(U)=true;
	DamagePoints(U)=40;
	AttackType(U)="Melee";
	HealPoints(U) = 0;
	Price(U)=4;
	return U;
}

Unit InitMage(POINT P,int Owner)
//F.S : King dengan state awal
{
	Unit U;
	Locate(U)=P;
	MaxHP(U)=BaseMaxHPMage;
	HP(U)=BaseMaxHPMage;
	MaxMP(U)=BaseMaxMPMage;
	MP(U)=BaseMaxMPMage;
	Owner(U)=Owner;
	Tipe(U)="Mage";
	CanAtk(U)=true;
	DamagePoints(U)=30;
	AttackType(U)="Melee";
	HealPoints(U) = 10;
	Price(U)=5;
	return U;
}

Unit InitKing(POINT P,int Owner)
//F.S : King dengan state awal
{
	Unit U;
	Locate(U)=P;
	MaxHP(U)=BaseMaxHPKing;
	HP(U)=BaseMaxHPKing;
	MaxMP(U)=BaseMaxMPKing;
	MP(U)=BaseMaxMPKing;
	Owner(U)=Owner;
	Tipe(U)="King";
	CanAtk(U)=true;
	DamagePoints(U)=50;
	AttackType(U)="Melee";
	HealPoints(U) = 0;
	return U;
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
//Mengeluarkan true Jika P1 dan P2 Adjacent atau beda sepetak dengan U2.
	return (Distance(P1,P2)==1);
}

boolean IsEnemy(Unit U1, Unit U2){
//I.S:U1 && U2 tidak null
//Mengembalikan true jika U2 adalah musuh dari U1 (U1 ialah player yang sedang bermain)
	return(Owner(U1)!=Owner(U2));
}

void PrintInfoUnit (Unit U)
/* mengeluarkan info unit standar seperti dibawah ini
Unit: King(2,1) | Health 20/20 | Movement Point: 2 | Can Attack: Yes */
{
	printf("Unit: %s (%d,%d) | ", Tipe(U), Absis(Locate(U)), Ordinat(Locate(U)));
	printf("Health: %d/%d | ", HP(U), MaxHP(U));
	printf("Movement Point: %d | ", MP(U));
	if (CanAtk(U))	printf("Can Attack: Yes\n");
	else	printf("Can Attack: No\n");
}

void AttackU (Unit U1, Unit U2);
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1

void PrintAtkType(Unit U);
//Memprint ke layar Tipe Attack yang dapat dilakukan oleh Unit U

boolean CmpUnit (POINT U1, POINT U2)
//True jika U1==U2
{
	return(EQ(U1,U2));
}