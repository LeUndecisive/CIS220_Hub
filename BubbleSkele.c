#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
//Joshua S
//Chp 3 PA

int main(void) {
	

// We need to define some variables for later funcs
	int i; 
	int j;
	int ArrSize = 26;
	int ArrayMix [ArrSize];
	srand(time(0)); // Used to ensure numbers are random
	
// We need create an array of 25 elements randomly
	void GenArray(int Array[], int Size){
		
		for ( i = 0; i < Size - 1; i++){
			int Num = rand() % 1001;
			Array[i] = Num;
		}
	}

//Call the GenArray to fill ArrayMix
	GenArray(ArrayMix,ArrSize);
	
// A Element printf func is need and an alt printf statment
	void printArray(int Array[], int n, bool Sorted){

		if ( Sorted == true){
				printf("Sorted Array:\n");
		}else{
				printf("Unsorted Array:\n");
		}
		
		for ( i = 0; i < n - 1; i++){
			printf("%d ",Array[i]);
			
		}
		printf("\n\n");
	}
	
// We should create a swap element function 
	void ElementSwap( int Array[], int LowIndex, int HighIndex){
		
		int TempValue = Array[LowIndex];
		Array[LowIndex] = Array[HighIndex];
		Array[HighIndex] = TempValue;
		
	}
	
// A bubble sort func should be made
	void BubbleFunc(int Array[], int n){
		
		for ( i = 0; i < n - 2; i++){
	
			for ( j = 0; j < n - 2; j++){
				if (Array[j] > Array[j+1]){
					ElementSwap(Array,j,j+1);
				}		
			}
		}

	}
	
// Display the unsorted Array
	printArray(ArrayMix,ArrSize,false);
	
// We can call BubbleFunc
	BubbleFunc(ArrayMix, ArrSize);
	
//Display the sorted Array
	printArray(ArrayMix,ArrSize,true);
	return 0;
}
