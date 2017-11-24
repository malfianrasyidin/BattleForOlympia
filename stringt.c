#include <string.h>
#include "stringt.h"

char* DelFirstChar(char Sin[25]){
	char* DD = Sin + 1;
	return(DD);
}
void DelLastChar(char Sin[], char Sout[]){
	strcpy(Sout,Sin);
	int n = strlen(Sout);
	Sout[n-1] = '\0';
}

char TakeFirstChar (char Sin[25]){
	return(Sin[0]);
}

char TakeLastChar (char Sin[25]){
	return(Sin[strlen(Sin) - 1]);
}

void AppendChar(char S[25], char c){
    int len = strlen(S);
    if(len == 0){
		S[0] = c;
	}
	else {
		S[len] = c;
		S[len+1] = '\0';
	}
}

void delAllStr(char Sin[25]){
	for (int i = 0; i < strlen(Sin); i++){
		DelFirstChar(Sin);
	}
}

void AppendStr(char Sin[25], char SS[25]){
	for (int i = 0 ; i < strlen(SS); i++){
		AppendChar(Sin,SS[i])
	}
}