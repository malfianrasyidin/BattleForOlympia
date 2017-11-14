#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"

boolean PointInMap (POINT P, MatriksMap M){
	return((Ordinat(P) <= NBrsEff(M)) && (Absis(P) <= NKolEff(M)));
}

boolean IsMoveValid(Unit U, POINT P, MatriksMap M){
//Mengembalikan True jika Move Unit U ke Point P Valid, False Jika Tidak.
	if (MP(U) == 0){
		return(false);
	}
	else if (!PointInMap(P,M)){
		return(false);
	}
	else if (IsUnitIn(P, M)){
		return(false);
	}
	else{
		if ((MP(U)-Distance(Locate(U), P))>=0) return true;
		else return false;
	}
}

void Undo (Stack *History, Unit *U) {
//Mengembalikan current unit ke posisi sebelumya dan menambah movement points jika ada.
	POINT P;

	if (IsEmpty(*History)){
		printf("You don't have any movement history");
	} else {
		Pop(History, &P);
		Absis(Locate(*U)) = Absis(P);
		Ordinat(Locate(*U)) =  Ordinat(P);
	}
}

void History(Stack *S, POINT P){
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history
	Push(S, P);
}