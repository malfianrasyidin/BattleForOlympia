#include <stdio.h>
#include "point.h"
#include "boolean.h"

int main () {
	int Choice,X,Y;
	POINT P1,P2;

	printf("--This is a driver for ADT Point--\n");
	printf("List of commands: \n");
	printf("1. Read two Points \n");
	printf("2. Write two Points\n");
	printf("3. EQ or NEQ\n");
	printf("4. Exit\n");

	printf("Your command: ");
	scanf("%d", &Choice);
	while (Choice!=4) {
		if (Choice==1) {
			printf("Input the first point [X Y]: ");
			BacaPOINT(&P1);
			printf("Input the second point [X Y]: ");
			BacaPOINT(&P2);
		} else if (Choice==2){
				TulisPOINT(P1);
				TulisPOINT(P2);
		} else if (Choice==3) {
			if (EQ(P1,P2)) {
				printf("These two points are equal\n");
			} else if (NEQ(P1,P2)) {
				printf("These two points are not equal\n");
			} else {
				printf("Undetermined\n");
			}
		} else {
			printf("Wrong commands\n");
		}
		printf("Your command: ");
		scanf("%d", &Choice);
	}
	return 0;
}