#include <stdio.h>
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "player.h"
#include "stackt.h"
#include "queuelist.h"


/* ############################## */
/* ########### MOVE ############# */
/* ############################## */
boolean PointInMap (POINT P, MatriksMap M);
/* I.S Sembarang
 * F.S Return true jika P terdefinisi di M dan 
 * 	   false jika P tidak terdefinisi di M
 */
boolean IsMoveValid(POINT PU, POINT P, MatriksMap M);
/* I.S Unit bukan unit Null, M Terdefinisi
 * F.S True jika Movement ke P Valid, False jika tidak */

void History(Stack *S, POINT P);
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history

MatriksMap PossibleMove (POINT PIn, MatriksMap M);
//Mengembalikan matriks disertakan tempat2 yang mungkin di move

void MainMove(Stack *S, POINT PIn, MatriksMap *M, Player *Play);
//MainMove

void Undo (Stack *History, Unit *U);
//Mengembalikan current unit ke posisi sebelumya dan menambah movement points jika ada.

// CHANGE & RECRUIT UNIT
QueueU MakeUnitQueue (List L);
/*Mengembaikan Queue yang berisi semua unit pada L */

void NextUnitQ (QueueU *Q, POINT *U, MatriksMap M);
//I.S Q terdefinisi
//F.S Mengembalikan Unit yang akan digunakan setelahnya

POINT SearchUnit(QueueU Q, int x);
//I.S Q terdefinisi, tidak mungkin kosong
//F.S Mengembalikan Unit yang berada di urutan X pada Queue

void ChangeUnit(QueueU *Q, Unit *U);
//I.S Q terdefinisi, U sembarang.
//F.S U adalah Unit selanjutnya pada Queue,  

void AddUnitQ (QueueU *Q, POINT P);
//I.S Q dan U terdefinisi
//F.S Mengembalikan Q yang sudah berisi Unit U

void AddUnitL (List *L, POINT P);
//I.S L dan U terdefinisi
//F.S Mengembalikan L yang sudah terisi Unit U

void AddUnit (List *L, QueueU *Q, Unit U);
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.

void RecruitUnit (Player P, List *L, QueueU *Q, MatriksMap M);
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan Pesan kesalahan jika UR bukan King atau Gold Player Tidak Cukup
//    atau L dan Q yang sudah terisi Unit Baru jika True

/* ############################## */
/* ########### INFO ############# */
/* ############################## */
void PrintInfoCell (POINT P, MatriksMap M);
//F.S : Ngeprint info cell (building & unit)

void MainInfo(MatriksMap M);
//main info
