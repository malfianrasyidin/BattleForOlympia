
#ifndef PLAYER__H
#define PLAYER__H

#include "boolean.h"
#include "listdpunit.h"
#include "unit.h"


typedef struct
{
    char PlayerNumber;
    Unit CurrUnit;
    int Gold;
    int Income;
    int UpKeep;
    List ListOfUnits;
    List ListOfVillages;
} Player;

#endif