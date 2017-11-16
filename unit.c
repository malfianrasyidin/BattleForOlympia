#include "unit.h"
#include "point.h"
#include "boolean.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>


//FUNGSI NULLITAS
Unit NullUnit(POINT P){
	Unit U;
	Absis(Locate(U)) = Absis(P);
	Ordinat(Locate(U)) = Absis(P);
	Damage(U) = 0;
	Heal(U) = 0;
	CanAtk(U) = false;
	AtkType(U) = ' ';
	MaxHP(U) = 0;
	MaxMP(U) = 0;
	HP(U) = 0;
	MP(U) = 0;
	Owner(U) = 0;
	Tipe(U) = ' ';
	return(U);
}

Unit MakeNewUnit(int N, int Play, POINT P){
//mengembalikan unit baru dengan initial state
	Unit U;
	Owner(U) = Play;
	if (N == 1){
		Locate(U) = P;
		Tipe(U) = 'W';
		MaxHP(U) = BaseMaxHPWarrior;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPMage;
		MP(U) = MaxMP(U);
		AtkType(U) = 'M';
		Damage(U) = BaseDmgPointWarrior;
		Heal(U)  = 0;
		CanAtk(U) = true;
	}
	else if (N == 2){
		Locate(U) = P;
		Tipe(U) = 'A';
		MaxHP(U) = BaseMaxHPArcher;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPArcher;
		MP(U) = MaxMP(U);
		AtkType(U) = 'R';
		Damage(U) = BaseDmgPointArcher;
		Heal(U)  = 0;
		CanAtk(U) = true;
	}
	else if (N==3) {
		Locate(U) = P;
		Tipe(U) = 'M';
		MaxHP(U) = BaseMaxHPMage;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPMage;
		MP(U) = MaxMP(U);
		AtkType(U) = 'R';
		Damage(U) = BaseDmgPointMage;
		Heal(U)  = BaseHealMage;
		CanAtk(U) = true;
	} else if (N==4)	{
		Locate(U) = P;
		Tipe(U) = 'K';
		MaxHP(U) = BaseMaxHPKing;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPKing;
		MP(U) = MaxMP(U);
		AtkType(U) = 'R';
		Damage(U) = BaseDmgPointKing;
		Heal(U)  = 0;
		CanAtk(U) = true;
	}
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
	printf("Unit: %s (%d,%d) | ", UnitTranslation(Tipe(U)), Absis(Locate(U)), Ordinat(Locate(U)));
	printf("Health: %d/%d | ", HP(U), MaxHP(U));
	printf("Movement Point: %d | ", MP(U));
	if (CanAtk(U))	printf("Can Attack: Yes\n");
	else	printf("Can Attack: No\n");
}

boolean CmpUnit (Unit U1, Unit U2)
//True jika U1==U2
{
	return(EQ(Locate(U1),Locate(U2)));
}
