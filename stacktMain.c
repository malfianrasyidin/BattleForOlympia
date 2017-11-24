#include <stdio.h>
#include "stackt.h"
#include "point.h"
#include "boolean.h"


int main () {
	Stack S;
	int Choice,X,Y;
	infotype P;
	CreateEmpty(&S);

	printf("--This is a driver for ADT Stack of Points--\n");
	printf("List of commands: \n");
	printf("1. Push to a stack \n");
	printf("2. Pull from a Stack\n");
	printf("3. Exit\n");

	printf("Your command: ");
	scanf("%d", &Choice);
	while (Choice!=3) {
		if (Choice==1) {
			printf("Input a point [X Y]: ");
			BacaPOINT(&P);
			Push(&S,P);
		} else if (Choice==2){
			if (!IsEmpty(S)){
				Pop(&S, &P);
				TulisPOINT(P);
			} else {
				printf("Empty Stack\n");
			}
		} else {
			printf("Wrong commands\n");
		}
		printf("Your command: ");
		scanf("%d", &Choice);
	}
	return 0;
}