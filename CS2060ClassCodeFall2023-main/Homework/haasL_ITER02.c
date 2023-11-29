/*Lucas Haas
* CS 2060 ITER02
* OS: Win 11
* Description: A simple program that allows owners to submit property info and users to rent out properties.
* Uses linked lists to store owner properties and in user mode will allow renters to rent the properties. 
* If login is successful at the end, a summary of all properties will be printed and also saved to separate
* files.
*/




#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

//Maximum length of a string
#define  STRING_LENGTH 80
//Two dimensional array storage amounts for rows and columns of survey data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3
//Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1
//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2
#define MIN_RATING 1
#define MAX_RATING 5

#define CATEGORIES "Check-in process", "Cleanliness", "Amenities"


struct property {
	int interval1;
	int interval2;
	int rentalRate;
	int discount;
	char name[STRING_LENGTH];
	char location[STRING_LENGTH];
	int totalNights;
	int totalCharges;
	int renters;
	int survey[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
	struct property *nextPtr;
};


// function prototypes

//Prints the rental property information
void printRentalPropertyInfo(const struct property* headPtr);

//returns only valid input from the user based on the min and max values inclusively
int getValidInt(int min, int max, int* toStore, int fromFunction);

//Calculates the charge based on the number of nights rented
int calculateCharges(int nights, const struct property* propertyPtr);

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharged(int nights, int charges);

//Initializes struct values with user input
void propertySetup(struct property** headPtr);

//Login function for owner
int login();

//prints categories for easy changes
void printCategories();

//applies survey data from users to survey array in property struct
void survey(struct property* currentPtr);

//Prints summary of property for owner at the end
void ownerSummary(const struct property* headPtr);

//prints all ratings
void printRatings(const struct property* headPtr);

//checks if name is in linked list and stores in validName variable from main.
//This works because char arrays are passed by reference by default
void getValidName(const struct property* headPtr, char validName[STRING_LENGTH]);

//Creates a files and writes the summary for each property in the linked list their separate files
void printSummaries(struct property* headPtr);





int main(void){
	if (login() == 0) {

		struct property* headPtr = NULL; //declare our headPtr to null, issues appeared when not NULL.

		propertySetup(&headPtr); //function call to start our linked list

		printRentalPropertyInfo(&*headPtr); //takes the headPtr and prints all items in the list

		int nights = 0;
		int charges = 0;

		//Will continually execute unless returned sentinel value from within gatValidInt
		while (nights != SENTINAL_NEG1) {
			char validName[STRING_LENGTH]; //needed to store from getValidName
			getValidName(headPtr, validName); //checks if name exists in list

			struct property* currentPtr = headPtr;
			while (strcmp(currentPtr->name, validName) != 0) { //finds the linked list item with the name to use below
				currentPtr = currentPtr->nextPtr;
			}
			printf("%s\n", "Enter the amount of nights you want to stay:\n");
			getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, &nights, 2); //the 2 is to tell getValidInt it needs to check for a -1
			if (nights != -1) {
				charges = calculateCharges(nights, currentPtr);
				currentPtr->totalNights = currentPtr->totalNights + nights;
				currentPtr->totalCharges = currentPtr->totalCharges + charges;
				survey(currentPtr);
				headPtr->renters++;
			} 
			
		}

		if (login() == 0) {
			printf("%s\n,", "Rental Property Owner Summary:");
			ownerSummary(headPtr);
			printSummaries(headPtr);
		}
	}

	printf("%s\n", "Exiting AirUCCS.");
	
	return 0;
}

void propertySetup(struct property** headPtr) {
	char input = 'y'; //to start the while loop
	while (input == 'y') {
		struct property* newPropPtr = malloc(sizeof(struct property)); //set up memory for new property
		if (newPropPtr != NULL) {
			printf("%s", "Enter Interval 1:");
			getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, &(newPropPtr->interval1), 1);
			printf("%s", "Enter Interval 2:");
			getValidInt(newPropPtr->interval1 + 1, MAX_RENTAL_NIGHTS, &(newPropPtr->interval2), 1);
			printf("%s", "Enter rental rate:");
			getValidInt(MIN_RATE, MAX_RATE, &(newPropPtr->rentalRate), 1);
			printf("%s", "Enter discount:");
			getValidInt(MIN_RATE, newPropPtr->rentalRate, &(newPropPtr->discount), 1);
			printf("%s", "Enter property name:");
			fgets(newPropPtr->name, STRING_LENGTH, stdin);
			newPropPtr->name[strlen(newPropPtr->name) - 1] = '\0';
			printf("%s", "Enter location info:");
			fgets(newPropPtr->location, STRING_LENGTH, stdin);
			newPropPtr->location[strlen(newPropPtr->location) - 1] = '\0';
			
			newPropPtr->renters = 0;
			newPropPtr->totalCharges = 0;
			newPropPtr->totalNights = 0; //these set to 0 just to have them initialized to use later
		}

		if (newPropPtr != NULL) { //if memory allocated successfully
			newPropPtr->nextPtr = NULL;

			struct property* previousPtr = NULL;

			struct property* currentPtr = *headPtr; 

			while (currentPtr != NULL && strcmp(currentPtr->name, newPropPtr->name) < 0) //while newPropPtr is alphabetically less than current, walk
			{
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}

			if (previousPtr == NULL) //if the list is empty, set head to new
			{
				*headPtr = newPropPtr;
			}
			else
			{
				previousPtr->nextPtr = newPropPtr;
			}

			newPropPtr->nextPtr = currentPtr;
		}

		printf("Would you like to add another property? (y)es or (n)o\n");
		input = getchar();
		while ((getchar()) != '\n');
	}

}
	

int login() {
	char id[STRING_LENGTH];
	char passcode[STRING_LENGTH];
	int result = -1;

	int attempts = 0;

	while (result != 0 && attempts < LOGIN_MAX_ATTEMPTS) {
		attempts++;

		printf("%s\n", "Enter your AirUCCS ID:");
		fgets(id, STRING_LENGTH, stdin);

		printf("%s\n", "Enter your AirUCCS passcode:");
		fgets(passcode, STRING_LENGTH, stdin);

		id[strlen(id) - 1] = '\0';
		passcode[strlen(passcode) - 1] = '\0';

		if (strcmp(id, CORRECT_ID) == 0 && strcmp(passcode, CORRECT_PASSCODE) == 0) { //if username AND password are both correct
			result = 0;
		}
		else {
			printf("%s\n", "Username or passcode incorrect.");
			result = -1;
		}
	}

	return result;
}

void printRentalPropertyInfo(const struct property* headPtr) {
	if (headPtr == NULL) { //list is empty if headPtr is NULL
		puts("No properties added");
	}
	else {
		const struct property* currentPtr = headPtr; 
			//walk through to the end to print every item
			while (currentPtr != NULL) {
				printf("%s can be rented for %d to %d nights.\n", currentPtr->name, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
				printf("%.2d per night for the first %d nights.\n", currentPtr->rentalRate, currentPtr->interval1);
				printf("%.2d discount rate a night for nights %d to %d.\n", currentPtr->discount, (currentPtr->interval1 + 1), currentPtr->interval2);
				printf("%.2d discount rate a night for each remaining night over %d\n", (currentPtr->discount * DISCOUNT_MULTIPLIER), currentPtr->interval2);
				if (currentPtr->survey != NULL) {
					puts("Survey Results:");
					printRatings(currentPtr);
				}
				else {
					puts("Survey Results:");
					puts("No Ratings Currently");
				}
				currentPtr = currentPtr->nextPtr;
				puts("");
				puts("");
			}
	}

	return;
}

int getValidInt(int min, int max, int* toStore, int fromFunction) {
	
	int check = -1;

	while (check == -1) {
		char buff[STRING_LENGTH];
		fgets(buff, STRING_LENGTH, stdin);
		buff[strlen(buff) - 1] = '\0';
		char* end;
		errno = 0;
		int validInt = 0;
		long intTest = strtol(buff, &end, 10);

		if (end == buff) {
			fprintf(stderr, "%s: not a decimal number\n", buff);
		}
		else if ('\0' != *end) {
			fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
		}
		else if (intTest == SENTINAL_NEG1 && fromFunction == 2) { //the fromFunction param is used here so that the only call that
			check = 0;											 //uses this test is where we want the sentinal value from
			validInt = (int)intTest;
			*toStore = validInt;
		}
		else if (intTest > max) {
			fprintf(stderr, "%ld greater than %d\n", intTest, max);
		}
		else if (intTest < min) {
			fprintf(stderr, "%ld less than %d\n", intTest, min);
		}
		else {
			validInt = (int)intTest;
			check = 0;
			*toStore = validInt;
		}
	}

	return check; //left in case we want to store result 
}


int calculateCharges(int nights, const struct property* propertyPtr) {
	int charge = 0;
	if (nights <= propertyPtr->interval1) {
		charge = nights * propertyPtr->rentalRate;
		printNightsCharged(nights, charge);
	}

	//interval 1 to 2, 1x discount rate
	if (nights > propertyPtr->interval1 && nights <= propertyPtr->interval2) {
		charge = (propertyPtr->interval1 * propertyPtr->rentalRate) + ((nights - propertyPtr->interval1) * (propertyPtr->rentalRate - propertyPtr->discount));
		printNightsCharged(nights, charge);
	}

	//interval 2 to max, 2x discount rate
	if (nights > propertyPtr->interval2 ) {
		charge = (propertyPtr->interval1 * propertyPtr->rentalRate) + ((propertyPtr->interval2 - propertyPtr->interval1) * (propertyPtr->rentalRate - propertyPtr->discount)) + ((nights - propertyPtr->interval2) * (propertyPtr->rentalRate - (propertyPtr->discount * DISCOUNT_MULTIPLIER)));
		printNightsCharged(nights, charge);
	}

	return charge;
}

void printCategories()
{
	char array[RENTER_SURVEY_CATEGORIES][STRING_LENGTH] = {CATEGORIES}; //set preprocessor for this to change more easily
	printf("%s", "Categories are: ");
	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
		printf("%d: %s\t", i + 1, array[i]);
	}
	printf("\n");
}


void survey(struct property* currentPtr) {
	static int renter = 0;
	printCategories();
	if (renter < VACATION_RENTERS) { //ensures we do not go over the predefined renter limit and break
		for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
			printf("\nEnter rating for category %d:\n", i + 1);
			getValidInt(MIN_RATING, MAX_RATING, &(currentPtr->survey[renter][i]), 3);
		}
	}
	renter++;
}

void printNightsCharged(int nights, int charges) {
	printf("%s\n", "Nights   Charges");
	double doubleCharge = (double)charges;
	printf("%d   %.2f\n", nights, doubleCharge);
}

void printRatings(const struct property* propertyPtr) {
	printCategories(); //gives us the categories first

	//double for loop to traverse survey 2d array
	for (size_t i = 0; i < VACATION_RENTERS; i++) { 
		for (size_t j = 0; j < RENTER_SURVEY_CATEGORIES; j++) {
			if (propertyPtr->survey[i][j] > 0 && propertyPtr->survey[i][j] < 6) {
				printf("%d\t", propertyPtr->survey[i][j]);
			}
		}
		printf("\n");
	}
}
	
void ownerSummary(const struct property* headPtr) {
	const struct property* currentPtr = headPtr;

	//walk through each property and print values to stdout
	while (currentPtr != NULL) {
		puts("");
		printf("%s\n", "-----Property Totals-----");
		printf("%s\n", "Renters   Nights   Charges");
		printf("%d\t  %d\t   %.2f\n", currentPtr->renters, currentPtr->totalNights, (double)currentPtr->totalCharges);
		printNightsCharged(currentPtr->totalNights, currentPtr->totalCharges);
		printf("%s\n", "-----Survey Rating Averages-----");
		for (size_t i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
			double average = 0;
			for (size_t j = 0; j < VACATION_RENTERS; j++) {
				if (currentPtr->survey[j][i] >= MIN_RATING && currentPtr->survey[j][i] <= MAX_RATING) { //makes sure value is not garbage before proceeding
					average = average + currentPtr->survey[j][i]; //total ratings for each category
				}
			}
			average = average / currentPtr->renters; //divide by # of renters (not VACATION_RENTERS cause we may have less than that)
			printf("Category %zu: %.2f\t", i + 1, average); //unsinged int print for cat # and float for average rating
		}
		currentPtr = currentPtr->nextPtr;
	}
}


void getValidName(const struct property* headPtr, char validName[STRING_LENGTH]) {
	char userPropInput[STRING_LENGTH]; //declare to use with fgets later
	int result = 0;
	const struct property* currentPtr;
	while (result != 1) {
		puts("Enter the name of the property you want to rent.");
		fgets(userPropInput, STRING_LENGTH, stdin);
		userPropInput[strlen(userPropInput) - 1] = '\0';

		currentPtr = headPtr;

		while (currentPtr != NULL) {
			if (strcmp(userPropInput, currentPtr->name) == 0) { //checks if name exists in list
				result = 1;
				strcpy(validName, currentPtr->name); //copies the found name to validName (address returns value to main)
			}

			currentPtr = currentPtr->nextPtr;
		}
		if (result != 1) {
			puts("Error, the property you entered doesn't match. Enter the property again.");
		}
	}
}

void printSummaries(struct property* headPtr) {
	struct property* currentPtr = headPtr;
	FILE* filePtr;
	while (currentPtr != NULL) {
		
		//search every letter in the name array for spaces and replace with _
		for (int i = 0; i < strlen(currentPtr->name); i++) {
			if (currentPtr->name[i] == ' ') {
				currentPtr->name[i] = '_';
			}
		}
		
		//set directory name and file name
		const char* directory = "C:\\fundraiser\\";
		const char* fileName = currentPtr->name;

		//set fullpath variable
		char fullPath[STRING_LENGTH];

		//strcpy to start directory into fullPath and strcat to add onto directory path
		strcpy(fullPath, directory);
		strcat(fullPath, fileName);
		strcat(fullPath, ".txt");

		if ((filePtr = fopen(fullPath, "w")) == NULL) { //if file cannot be opened
			puts("Could not open file.");
		}
		else {
			filePtr = fopen(fullPath, "w");


			fprintf(filePtr, "%s\n", "-----Property Totals-----");
			fprintf(filePtr, "%s\n", "Renters   Nights   Charges");
			fprintf(filePtr, "%d\t  %d\t   %.2f\n", currentPtr->renters, currentPtr->totalNights, (double)currentPtr->totalCharges);
			fprintf(filePtr, "%s\n", "-----Survey Rating Averages-----");
			for (size_t i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
				double average = 0;
				for (size_t j = 0; j < VACATION_RENTERS; j++) {
					if (currentPtr->survey[j][i] >= 0 && currentPtr->survey[j][i] <= 5) { //makes sure value is not garbage before proceeding
						average = average + currentPtr->survey[j][i];
					}
				}
				average = average / currentPtr->renters;
				fprintf(filePtr, "Category %zu: %.2f\t", i + 1, average); //same as owner summary
			}
			fclose(filePtr); //close filePtr before looping to open again
		}
		currentPtr = currentPtr->nextPtr;
	}
}