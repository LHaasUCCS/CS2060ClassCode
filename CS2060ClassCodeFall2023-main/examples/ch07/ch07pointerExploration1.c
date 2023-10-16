/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	// ptr stores address of houseNum
	int *houseNumPtr = &houseNum;
	
	// print houseNum
	printf("houseNum %d\n", houseNum);

	// print address of houseNum
	printf("&houseNum %p\n\n", &houseNum);

	// prints value of houseNumPtr with the * dereference
	printf ("*houseNumPtr  %d\n", *houseNumPtr);

	// prints address of houseNum via ptr
	printf ("houseNumPtr %p\n\n", houseNumPtr);

	// prints the address of the ptr itself
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);

	// dereferencing houseNumPtr makes it 13 + 13 for 26
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	// calcHouseNum1 integer printed
	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);

	// multiply 2 * the dereferenced ptr (16)
	calcHouseNum2 = 2 * (*houseNumPtr);

	//print int value of calcHouseNum2
	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);

	// looks like 2 different ways to dereference a ptr. both reference houseNum
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", *houseNumPtr, &houseNumPtr);
			
	return 0;
}
