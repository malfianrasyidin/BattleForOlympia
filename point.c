#include "point.h"
#include <stdio.h>
#include <math.h>


POINT MakePOINT (float X, float Y){
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
	float a,b;
	scanf("%f", &a);
	scanf("%f", &b);
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
	printf("%.2f,%.2f\n", Absis(P), Ordinat(P));
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

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P){
/* Menghasilkan true jika P adalah titik origin */
	if((Absis(P) == 0) && (Ordinat(P) == 0)){
		return(true);
	}
	else{
		return(false);
	}
}
boolean IsOnSbX (POINT P){
/* Menghasilkan true jika P terletak Pada sumbu X */
	if(Ordinat(P) == 0){
		return(true);
	}
	else{
		return(false);
	}
}
boolean IsOnSbY (POINT P){
	/* Menghasilkan true jika P terletak pada sumbu Y */
	if(Absis(P) == 0){
		return(true);
	}
	else{
		return(false);
	}
}

int Kuadran (POINT P){
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
	int k;
	if ((Absis(P) == 0) || (Ordinat(P))){
		k = 0;
	}
	else if ((Absis(P) > 0) && (Ordinat(P) > 0)){
		k = 1;
	}
	else if (Absis(P) > 0) {
		k = 2;
	}
	else if ((Absis(P) < 0) && (Ordinat(P) < 0)) {
		k = 4;
	}
	else{
		k = 3;
	}
	return(k);
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P){
/* Mengirim salinan P dengan absis ditambah satu */
	float x;
	x = Absis(P) + 1;
	return(MakePOINT(x, Ordinat(P)));
}              
POINT NextY (POINT P){
/* Mengirim salinan P dengan ordinat ditambah satu */
	float y;
	y = Ordinat(P) + 1;
	return(MakePOINT(Absis(P), y));
}
POINT PlusDelta (POINT P, float deltaX, float deltaY){
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
	float x,y;
	x = Absis(P) + deltaX;
	y = Ordinat(P) + deltaY;
	return(MakePOINT(x,y));
}
POINT MirrorOf (POINT P, boolean SbX){
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
	POINT a;
	if (SbX){
		a = MakePOINT(Absis(P), -Ordinat(P));
	}
	else{
		a = MakePOINT(-Absis(P), Ordinat(P));
	}
	return(a);
}
float Jarak0 (POINT P){
/* Menghitung jarak P ke (0,0) */
	
	return sqrt((Absis(P))*(Absis(P)) + (Ordinat(P))*(Ordinat(P)));
}
float Panjang (POINT P1, POINT P2){
/* Menghitung Jarak antara 2 titik P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
	float x,y;
	x = Absis(P1) - Absis(P2);
	y = Ordinat(P1) - Ordinat(P2);
	return sqrt(x*x + y*y);
}
void Geser (POINT *P, float deltaX, float deltaY){
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
	float x,y;
	x = Absis(*P) + deltaX;
	y = Ordinat(*P) + deltaY;
	*P = MakePOINT(x,y);
}
void GeserKeSbX (POINT *P){
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
	float x,y;
	x = Absis(*P);
	y = 0;
	*P = MakePOINT(x,y);
}
void GeserKeSbY (POINT *P){
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
	float x,y;
	x = 0;
	y = Ordinat(*P);
	*P = MakePOINT(x,y);
}
void Mirror (POINT *P, boolean SbX){
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
	if (SbX){
		*P = MakePOINT(Absis(*P), -Ordinat(*P));
	}
	else{
		*P = MakePOINT(-Absis(*P), Ordinat(*P));
	}
}
void Putar (POINT *P, float Sudut){
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
	float x,y;
	float R;
	R = (Sudut/180)*(3.1415926535897932);	
	x = (Absis(*P))*(cos(R) - sin(R));
	y = (Ordinat(*P))*(cos(R) + sin(R));
	*P = MakePOINT(x,y);
}
