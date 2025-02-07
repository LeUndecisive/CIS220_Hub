#include <stdio.h>
#include <string.h>
// Joshua S 
// Chpt2 PA

char* ReverseString(char* STR) {
	/* TODO: Complete recursive ReverseString() function here. */
	
	// We need to get the length of the string / array (Address)
		int Length = strlen(STR);
		//printf("%d is Length\n",Length);
		
	// We need a base case to break out of recall
		if  (Length <= 1) {
		return STR;
	}
	
	// We need to get the letter
	char Letter = STR[0];
	
	// We need the letter as a string for strcat
	char SLetter[2] = {Letter, '\0'};
	//printf("%c is Letter\n",Letter);
	
	// We need to cut the string 
	char* CutString = &STR[1];

	// We need to recall the function
	STR = ReverseString(CutString);
	
	// We need to put the letter at the end
	
	//printf("Out of recall\n");
	strcat(STR,SLetter);
	
return STR;
}

int main(void) {
	char inStr[50];
	char* resultStr;
   
	printf("Enter the string to be reversed: ");
	fgets(inStr, 20, stdin);
	strtok(inStr, "\n");  // Remove newline character from input.
	
	resultStr = ReverseString(inStr);
	
	printf("Reversed: %s\n", resultStr);

   return 0;
}