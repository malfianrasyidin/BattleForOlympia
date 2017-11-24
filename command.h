#include <stdio.h>
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "player.h"
#include "stackt.h"
#include "queuelist.h"


boolean PointInMap (POINT P, MatriksMap M);

boolean IsMoveValid(Unit U, POINT P, MatriksMap M);

MatriksMap PossibleMove (Unit U, MatriksMap M);
//Mengembalikan matriks disertakan tempat2 yang mungkin di move

void History(Stack *S, POINT P);
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history

void MainMove(Stack *S, Unit *U, MatriksMap *M);
//MainMove

void Undo (Stack *History, Unit *U);
//Mengembalikan current unit ke posisi sebelumya dan menambah movement points jika ada.

// CHANGE & RECRUIT UNIT
QueueU MakeUnitQueue (List L);
/*Mengembaikan Queue yang berisi semua unit pada L */

void NextUnit(QueueU *Q, POINT *U, MatriksMap M);
//I.S Q terdefinisi
//F.S Mengembalikan Unit yang akan digunakan setelahnya

POINT SearchUnit(QueueU Q, int x);
//I.S Q terdefinisi, tidak mungkin kosong
//F.S Mengembalikan Unit yang berada di urutan X pada Queue

void ChangeCurrUnit(QueueU *Q, MatriksMap M, Player *P);
//I.S Q terdefinisi, U sembarang.
//F.S Mengganti Current Unit yang diapakai player dengan unit selanjutnya pada Queue,  

void AddUnit (List *L, QueueU *Q, Unit U);
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.

void InfoRecruit(int *N);

int EmptyTower(Player P, MatriksMap M);

void RecruitUnit (Player P, List *L, QueueU *Q, MatriksMap M);
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan Pesan kesalahan jika UR bukan King atau L dan Q yang sudah terisi Unit Baru jika True

/* ############################## */
/* ########### INFO ############# */
/* ############################## */
void PrintInfoCell (POINT P, MatriksMap M);
//F.S : Ngeprint info cell (building & unit)

void MainInfo(MatriksMap M);
//main info