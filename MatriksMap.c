#include "MatriksMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "unit.h"

//FUNGSI NULLITAS
Build NullBuilding(){
	Build B;
	B.Owner = 0;
	B.Tipe = " ";
	return (B);
}

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MatriksMap * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk  */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
	for (int i = 1; i <= NB; i++){
		for (int j = 1; j <=NK ; j++){
			Elmt(*M,i,j).Building = NullBuilding();
			Elmt(*M,i,j).Res = NullUnit();
		}
	}
}


/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
	return((( BrsMax >= i) && (KolMax >= j)) && ((BrsMin <= i) && (KolMin <= j)));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MatriksMap M){
/* Mengirimkan indeks baris terkecil M */
	return(BrsMin);
}
indeks GetFirstIdxKol (MatriksMap M){
/* Mengirimkan indeks kolom terkecil M */
	return(KolMin);
}
indeks GetLastIdxBrs (MatriksMap M){
/* Mengirimkan indeks baris terbesar M */
	return(NBrsEff(M));
}
indeks GetLastIdxKol (MatriksMap M){
/* Mengirimkan indeks kolom terbesar M */
	return(NKolEff(M));
}
boolean IsIdxEff (MatriksMap M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
	return ((IsIdxValid(i,j)) && (( i <= NBrsEff(M)) && (j <= NKolEff(M))));
}
ElType GetElmtDiagonal (MatriksMap M, indeks i){
/* Mengirimkan elemen M(i,i) */
	return(Elmt(M,i,i));
}

boolean IsUnitIn (POINT P, MatriksMap M){
//Mengembalikan true jika ada unit di titik P.
	return (getUnit(P,M).KarType != " ");
}

Unit getUnit(POINT P, MatriksMap M){
//Mengembalikan unit yang berada di titik
	return (Elmt(M,Absis(P),Ordinat(P)).Res);
}

// void PrintMap(MatriksMap M){
// /*Memprint Peta M ke Layar*/
// 	for (int i = 1 ; i <= NBrsEff(M) ; i++){
// 		printf("#");
// 		for (int j = 1 ; j <= NKolEff(M) ; j++){
// 			printf("______");
// 		}
// 		printf("#\n#");
// 		for (int j = 1 ; j <= NKolEff(M) ; j++){
// 			printf("| %c |", Building(Elmt(M,i,j)));
// 		}
// 		printf("#\n#");
// 		for (int j = 1 ; j <= NKolEff(M) ; j++){
// 			printf("| %c |", UnitIn(Elmt(M,i,j)));
// 		}
// 		printf("#\n#");
// 		for (int j = 1 ; j <= NKolEff(M) ; j++){
// 			printf("|    |");
// 		}
// 		printf("#\n#");
// 		for (int j = 1 ; j <= NKolEff(M) ; j++){
// 			printf("______");
// 		}
// 		printf("#\n");
// 	}
// }

// MatriksMap MatGen(indeks NB, indeks NK){
// /*MengGenerate Peta yang baru dengan Random Number */
// 	int R;
// 	MatriksMap M;
// 	MakeMATRIKS(NB,NK, &M);
// 	int SB = NB/2;
// 	Building(Elmt(M,SB,2)) = 'T';
// 	Owner(Elmt(M,SB,2)) = 1;
// 	Building(Elmt(M,SB,1)) = 'C';
// 	Owner(Elmt(M,SB,2)) = 1;
// 	Building(Elmt(M,SB,3)) = 'C';
// 	Owner(Elmt(M,SB,3)) = 1;
// 	Building(Elmt(M,SB + 1, 2)) = 'C';
// 	Owner(Elmt(M,SB + 1,2)) = 1;
// 	Building(Elmt(M,SB - 1, 2)) = 'C';
// 	Owner(Elmt(M,SB - 1, 2)) = 1;
// 	Building(Elmt(M,SB,NK - 1)) = 'T';
// 	Owner(Elmt(M,SB,NK - 1)) = 2;
// 	Building(Elmt(M,SB,NK)) = 'C';
// 	Owner(Elmt(M,SB,NK)) = 2;
// 	Building(Elmt(M,SB,NK + 1)) = 'C';
// 	Owner(Elmt(M,SB,NK + 1)) = 2;
// 	Building(Elmt(M,SB + 1, NK)) = 'C';
// 	Owner(Elmt(M,SB + 1, NK)) = 2;
// 	Building(Elmt(M,SB - 1, NK)) = 'C';
// 	Owner(Elmt(M,SB - 1, NK)) = 2;
// 	for (int i = 1 ; i <= NBrsEff(M) ; i++){
// 		for (int j = 1 ; j <= NKolEff(M) ; j++){
// 			if (Building(Elmt(M,i,j)) != ' '){
// 				R = (unsigned) rand() % 4;
// 				if(R == 0){
// 					Building(Elmt(M,i,j)) = 'V';
// 				}
// 				else {
// 					Building(Elmt(M,i,j)) = ' ';
// 				}
// 			}
// 		}
// 	}
// 	return(M);
// }

