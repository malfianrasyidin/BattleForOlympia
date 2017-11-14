#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"

boolean PointInMap (POINT P, MatriksMap M);
/* I.S Sembarang
 * F.S Return true jika P terdefinisi di M dan 
 * 	   false jika P tidak terdefinisi di M
 */

boolean IsMoveValid(Unit U, POINT P, MatriksMap M);
/* I.S Unit bukan unit Null, M Terdefinisi
 * F.S True jika Movement ke P Valid, False jika tidak */
