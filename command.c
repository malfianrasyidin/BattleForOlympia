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
	else{
		int M = MP(U);
		POINT PointU = Locate(U);
		while (Absis(PointU) > Absis(P)){
			Absis(PointU)++;
			M--;
		}
		while (Absis(PointU) < Absis(P)){
			Absis(PointU)--;
			M--;
		}
		while (Ordinat(PointU) > Ordinat(P)){
			Ordinat(PointU)++;
			M--;
		}
		while (Ordinat(PointU) < Ordinat(P)){
			Ordinat(PointU)--;
			M--;
		}
		return(M != 0);
	}
}
