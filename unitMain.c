#include "unit.h"
#include "point.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	Unit U,U1;
	POINT P, P1, P2;
	char cr;
	int Choice, N, Play;

	printf("--This is a driver for Module Unit.c--\n");
	printf("List of commands: \n");
	printf("1. MakeNewUnit \n");
	printf("2. Distance two points \n");
	printf("3. IsEnemy \n");
	printf("4. Unit Translation \n");
	printf("5. PrintInfoUnit \n");
	printf("6. IsNullUnit \n");
	printf("7. Exit \n");

	U = NullUnit();
	printf("Your command: ");
	scanf("%d", &Choice);
	while (Choice != 7){
		if (Choice==1){
			printf("Which one do you want to add?\n");
			printf("1. Swordsman \n");
			printf("2. Archer \n");
			printf("3. White Mage\n");
			printf("4. King \n");
			printf("Your choice: "); scanf("%d", &N);
			printf("Which player are you in? 1 or 2\n");
			scanf("%d", &Play);
			printf("Input a point [X Y]: ");
			BacaPOINT(&P);
			MakeNewUnit(N,Play,P);
			printf("Unit successfully added\n");
		} else if (Choice==2){
			printf("Input the first point [X Y]: ");
			BacaPOINT(&P1);
			printf("Input the second point [X Y]: ");
			BacaPOINT(&P2);
			printf("Distance between those points is: %d\n", Distance(P1,P2));
		} else if (Choice==3){
			printf("Which one do you want to add?\n");
			printf("1. Swordsman \n");
			printf("2. Archer \n");
			printf("3. White Mage\n");
			printf("4. King \n");
			printf("Your choice: "); scanf("%d", &N);
			printf("Which player are you in? 1 or 2\n");
			scanf("%d", &Play);
			printf("Input a point [X Y]: ");
			BacaPOINT(&P);
			MakeNewUnit(N,Play,P);
			printf("Unit 1 successfully added\n");
			printf("Which one do you want to add?\n");
			printf("1. Swordsman \n");
			printf("2. Archer \n");
			printf("3. White Mage\n");
			printf("4. King \n");
			printf("Your choice: "); scanf("%d", &N);
			printf("Which player are you in? 1 or 2\n");
			scanf("%d", &Play);
			printf("Input a point [X Y]: ");
			BacaPOINT(&P);
			MakeNewUnit(N,Play,P);
			printf("Unit 2 successfully added\n");
			if (IsEnemy(U,U1)){
				printf("U1 is an enemy of U2\n");
			} else {
				printf("U1 is not an enemy of U2\n");
			}
		} else if (Choice==4){
			printf("Available char input: K,A,S,W,C,T,V\n");
			printf("Your input: ");
			scanf("%c", &cr);
			if (cr=='\n'){
				scanf("%c", &cr);
			}
			printf("%c means %s\n", cr, UnitTranslation(cr));
		} else if (Choice==5){
			if (IsNullUnit(U)){
				printf("There is no unit has been added\n");
			} else {
				PrintInfoUnit(U);
			}
		} else if (Choice==6) {
			if (IsNullUnit(U)){
				printf("Yes, there is no unit has been added\n");
			} else {
				printf("No, there is a unit already\n");
			}
		} else {
			printf("Wrong commands\n");
		}
		printf("Your command: ");
		scanf("%d", &Choice);
	}
	return 0;
}