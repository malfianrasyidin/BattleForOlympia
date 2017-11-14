#include "point.h"
#include "MatriksMap.h"
#include "unit.h"


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