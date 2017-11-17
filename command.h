#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"


/* ############################## */
/* ########### MOVE ############# */
/* ############################## */
boolean PointInMap (POINT P, MatriksMap M);
/* I.S Sembarang
 * F.S Return true jika P terdefinisi di M dan 
 * 	   false jika P tidak terdefinisi di M
 */
boolean IsMoveValid(Unit U, POINT P, MatriksMap M);
/* I.S Unit bukan unit Null, M Terdefinisi
 * F.S True jika Movement ke P Valid, False jika tidak */
MatriksMap PossibleMove (Unit U, MatriksMap M);
//Mengembalikan matriks disertakan tempat2 yang mungkin di move
void MainMove(Stack *S,Unit *U, MatriksMap *M);
//MainMove

// CHANGE & RECRUIT UNIT
Queue MakeUnitQueue (List L);
/*Mengembaikan Queue yang berisi semua unit pada L */

void NextUnitQ (Queue *Q, Unit *U);
//I.S Q terdefinisi
//F.S Mengembalikan Unit yang akan digunakan setelahnya

Unit SearchUnit(Queue Q, int x);
//I.S Q terdefinisi, tidak mungkin kosong
//F.S Mengembalikan Unit yang berada di urutan X pada Queue

void ChangeUnit(Queue *Q, Unit *U);
//I.S Q terdefinisi, U sembarang.
//F.S U adalah Unit selanjutnya pada Queue,  

void AddUnitQ (Queue *Q, POINT P);
//I.S Q dan U terdefinisi
//F.S Mengembalikan Q yang sudah berisi Unit U

void AddUnitL (List *L, POINT P);
//I.S L dan U terdefinisi
//F.S Mengembalikan L yang sudah terisi Unit U

void AddUnit (List *L, Queue *Q, Unit U);
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.

void RecruitUnit (Unit UR, Player P, Queue *Q);
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan Pesan kesalahan jika UR bukan King atau Gold Player Tidak Cukup
//    atau L dan Q yang sudah terisi Unit Baru jika True

/* ############################## */
/* ########### INFO ############# */
/* ############################## */
void PrintInfoCell (POINT P, MatriksMap M){
//F.S : Ngeprint info cell (building & unit)
}

void Info(MatriksMap M)	{
//main info
}