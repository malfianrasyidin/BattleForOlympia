#include "unit.h"
#include "point.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>


//FUNGSI NULLITAS
Unit NullUnit(){
	Unit U;
	Absis(Locate(U)) = 0;
	Ordinat(Locate(U)) = 0;
	DamagePoints(U) = 0;
	HealPoints(U) = 0;
	CanAttack(U) = false;
	AttackType(U) = ' ';
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
		MaxHP(U) = BaseMaxHPMage;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPMage;
		MP(U) = MaxMP(U);
		AttackType(U) = 'R';
		DamagePoints(U) = BaseDmgPointMage;
		HealPoints(U)  = BaseHealMage;
		CanAttack(U) = true;
	}
	else if (N == 2){
		Locate(U) = P;
		Tipe(U) = 'A';
		MaxHP(U) = BaseMaxHPArcher;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPArcher;
		MP(U) = MaxMP(U);
		AttackType(U) = 'R';
		DamagePoints(U) = BaseDmgPointArcher;
		HealPoints(U)  = 0;
		CanAttack(U) = true;
	}
	else if (N==3) {
		Locate(U) = P;
		Tipe(U) = 'S';
		MaxHP(U) = BaseMaxHPSwordsman;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPSwordsman;
		MP(U) = MaxMP(U);
		AttackType(U) = 'M';
		DamagePoints(U) = BaseDmgPointSwordsman;
		HealPoints(U)  = 0;
		CanAttack(U) = true;
	} else if (N==4)	{
		Locate(U) = P;
		Tipe(U) = 'K';
		MaxHP(U) = BaseMaxHPKing;
		HP(U) = MaxHP(U);
		MaxMP(U) = BaseMaxMPKing;
		MP(U) = MaxMP(U);
		AttackType(U) = 'R';
		DamagePoints(U) = BaseDmgPointKing;
		HealPoints(U)  = 0;
		CanAttack(U) = true;
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

boolean IsEnemy(Unit U1, Unit U2){
//I.S:U1 && U2 tidak null
//Mengembalikan true jika U2 adalah musuh dari U1 (U1 ialah player yang sedang bermain)
	return(Owner(U1)!=Owner(U2));
}

char* UnitTranslation(char Tipe){
//Mengembalikan singkatan dari unit yang akan ditampilkan di peta.
	switch (Tipe) {
		case 'K' : return "King"; break;
		case 'A' : return "Archer"; break;
		case 'S' : return "Swordsman"; break;
		case 'W' : return "White Mage"; break;
		case 'C' : return "Castle"; break;
		case 'T' : return "Tower"; break;
		case 'V' : return "Village"; break;
	}
	return 0;
}

void PrintInfoUnit (Unit U)
/* mengeluarkan info unit standar seperti dibawah ini
Unit: King(2,1) | Health 20/20 | Movement Point: 2 | Can Attack: Yes */
{
	printf("Unit: %s (%d,%d) | " ,UnitTranslation(Tipe(U)), Absis(Locate(U)), Ordinat(Locate(U)));
	printf("Health: %d/%d | ", HP(U), MaxHP(U));
	printf("Movement Point: %d | ", MP(U));
	if (CanAttack(U))	printf("Can Attack: Yes\n");
	else	printf("Can Attack: No\n");
}

boolean IsNullUnit(Unit U){
	boolean N;
	N = (Absis(Locate(U)) == 0) &&
	(Ordinat(Locate(U)) == 0) &&
	(DamagePoints(U) == 0) &&
	(HealPoints(U) == 0) &&
	(CanAttack(U) == false) &&
	(AttackType(U) == ' ') &&
	(MaxHP(U) == 0) &&
	(MaxMP(U) == 0) &&
	(HP(U) == 0) &&
	(MP(U) == 0) &&
	(Owner(U) == 0) &&
	(Tipe(U) == ' ');
	return(N);
}
