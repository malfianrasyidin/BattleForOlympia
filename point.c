#include "point.h"
#include <stdio.h>

POINT MakePOINT (int X, int Y){
/* Membentuk sebuah POINT dari komponen-komponennya */
	POINT P;
	Absis(P) = X;
	Ordinat(P) = Y;
	return(P);
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPOINT (POINT * P){
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
	int a,b;
	scanf("%d", &a);
	scanf("%d", &b);
	*P = MakePOINT(a,b);
}

void TulisPOINT (POINT P){
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */               
	printf("%d,%d\n", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
	if ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2))){
		return(true);
	}
	else{
		return(false);
	}
}

boolean NEQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 tidak sama dengan P2 */
	
	if ((Absis(P1) != Absis(P2)) && (Ordinat(P1) != Ordinat(P2))){
		return(true);
	}
	else{
		return(false);
	}
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */              
{
    return MakePOINT(Absis(P) + 1, Ordinat(P));
}

POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
    return MakePOINT(Absis(P), Ordinat(P) + 1);
}

POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
    return MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY);
}