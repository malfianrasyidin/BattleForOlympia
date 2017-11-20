
#include "player.h"
#include "boolean.h"
#include "listdpUnit.h"
#include "unit.h"

void AttackU (Unit U1, Unit U2)
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1
{
	HP(U2) -= DamagePoints(U1);
	if (HP(U2) <= 0) {
		U2 = NullUnit();
	} else if ((Tipe(U2) == 'K' || AttackType(U1) == AttackType(U2)) && HP(U2) > 0 ) {
		HP(U1) -= DamagePoints(U2);

		if (HP(U1) <= 0) {
			U1 = NullUnit();
		}
	}
}