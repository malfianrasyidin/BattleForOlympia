#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"

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
	else if (IsUnitIn(P)){
		return(false);
	}
	else{
		if ((MP(U)-Distance(Locate(U), P))>=0) return true;
		else return false;
	}
}