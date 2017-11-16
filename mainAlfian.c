#include "MatriksMap.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	MatriksMap M;

	MakeMATRIKS(3, 3, &M);
	PrintMap(M);
	return 0;
}