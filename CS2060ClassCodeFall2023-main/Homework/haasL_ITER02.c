/*Lucas Haas
* CS 2060 ITER02
* OS: Win 11
*/




#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

//Maximum length of a string
#define  STRING_LENGTH 80
//Two dimensional array storage amounts for rows and columns of surve data
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


// function prototypes
//Prints the rental property information 
void printRentalPropertyInfo(const struct property* PropertyPtr);

//returns only valid input from the user based on the min and max values inclusively
int getValidInt(int min, int max, int* toStore);

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, const struct property* propertyPtr);

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharged(unsigned int nights, double charges);

//Initializes struct values with user input
void propertySetup(struct property* propertyPtr);

//Login function for owner
int login();

//applies survey data from users to survey array in property struct
void survey(struct property* propertyPtr);

//Prints summary of property for owner at the end
void ownerSummary(unsigned int nights, double charges, const struct property* propertyPtr, unsigned int renters);

//prints all ratings
void printRatings(const struct property* propertyPtr);


struct property {
	int interval1;
	int interval2;
	int rentalRate;
	int discount;
	char name[STRING_LENGTH];
	char location[STRING_LENGTH];
	int survey[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
};


main(void){
	if (login() == 0) {

		struct property newProperty;

		propertySetup(&newProperty);

		printRentalPropertyInfo(&newProperty);

		unsigned int nights = 0;
		int charges = 0;
		unsigned int totalNights = 0;
		int totalCharges = 0;
		unsigned int renters = 0;

		//Will continually execute unless returned sentinel value from within gatValidInt
		while (nights != SENTINAL_NEG1) {
			printf("%s\n", "Enter the amount of nights you want to stay:\n");
			getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, &nights);
			if (nights != -1) {
				charges = calculateCharges(nights, &newProperty);
				totalNights += nights;
				totalCharges += charges;
				survey(&newProperty);
				renters++;
			}
		}

		if (login() == 0) {
			printf("%s\n,", "Rental Property Owner Summary:");
			ownerSummary(totalNights, totalCharges, &newProperty, renters);
		}
	}

	printf("%s\n", "Exiting AirUCCS.");
	
}

void propertySetup(struct property* propertyPtr) {
	printf("%s", "Enter Interval 1:");
	getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, &(propertyPtr->interval1));
	printf("%s", "Enter Interval 2:");
	getValidInt(propertyPtr->interval1 + 1, MAX_RENTAL_NIGHTS, &(propertyPtr->interval2));
	printf("%s", "Enter rental rate:");
	getValidInt(MIN_RATE, MAX_RATE, &(propertyPtr->rentalRate));
	printf("%s", "Enter discount:");
	getValidInt(MIN_RATE, propertyPtr->rentalRate, &(propertyPtr->discount));
	printf("%s", "Enter property name:");
	fgets(&(propertyPtr->name), STRING_LENGTH, stdin);
	propertyPtr->name[strlen(propertyPtr->name) - 1] = "\0";
	printf("%s", "Enter location info:");
	fgets(&(propertyPtr->location), STRING_LENGTH, stdin);
	propertyPtr->location[strlen(propertyPtr->location) - 1] = "\0";
	
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

		if (strcmp(id, CORRECT_ID) == 0 && strcmp(passcode, CORRECT_PASSCODE) == 0) {
			result = 0;
		}
		else {
			printf("%s\n", "Username or passcode incorrect.");
			result = -1;
		}
	}

	return result;
}

void printRentalPropertyInfo(const struct property* propertyPtr) {
	printf("%s can be rented for %d to %d nights.\n", propertyPtr->name, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
	printf("%.2d per night for the first %d nights.\n", propertyPtr->rentalRate, propertyPtr->interval1);
	printf("%.2d discount rate a night for nights %d to %d.\n", propertyPtr->discount, (propertyPtr->interval1 + 1), propertyPtr->interval2);
	printf("%.2d discount rate a night for each remaining night over %d\n", (propertyPtr->discount * DISCOUNT_MULTIPLIER), propertyPtr->interval2);

	return;
}

int getValidInt(int min, int max, int* toStore) {
	

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
		else if (intTest == -1) { //This breaks other components of the program, is there a way to check for a -1 without writing 2 of these functions?
			check = 0;
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


double calculateCharges(unsigned int nights, const struct property* propertyPtr) {
	double charge = 0;
	if (nights <= propertyPtr->interval1) {
		charge = nights * propertyPtr->rentalRate;
		printNightsCharged(nights, charge);
	}
	if (nights > propertyPtr->interval1 && nights <= propertyPtr->interval2) {
		charge = (propertyPtr->interval1 * propertyPtr->rentalRate) + ((nights - propertyPtr->interval1) * (propertyPtr->rentalRate - propertyPtr->discount));
		printNightsCharged(nights, charge);
	}
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


void survey(struct property* propertyPtr) {
	static int renter = 0;
	printCategories();
	if (renter < VACATION_RENTERS) { //ensures we do not go over the 5 renter limit and break
		for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
			printf("\nEnter rating for category %d:\n", i + 1);
			getValidInt(MIN_RATING, MAX_RATING, &(propertyPtr->survey[renter][i]));
		}
	}
	renter++;
}

void printNightsCharged(unsigned int nights, double charges) {
	printf("%s\n", "Nights   Charges");
	printf("%d   %.2f\n", nights, charges);
}

void printRatings(const struct property* propertyPtr) {
	printCategories();
	for (size_t i = 0; i < VACATION_RENTERS; i++) {
		for (size_t j = 0; j < RENTER_SURVEY_CATEGORIES; j++) {
			if (propertyPtr->survey[i][j] > 0 && propertyPtr->survey[i][j] < 6) {
				printf("%d\t", propertyPtr->survey[i][j]);
			}
		}
		printf("\n");
	}
}
	
void ownerSummary(unsigned int nights, double  charges, const struct property* propertyPtr, unsigned int renters) {
	printf("%s\n", "-----Property Totals-----");
	printf("%s\n", "Renters   Nights   Charges");
	printf("%d\t  %d\t   %.2f\n", renters, nights, charges);
	printNightsCharged(nights, charges, renters);
	printf("%s\n", "-----Survey Rating Averages-----");
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {
		double average = 0;
		for (size_t j = 0; j < VACATION_RENTERS; j++) {
			if (propertyPtr->survey[j][i] >= 0 && propertyPtr->survey[j][i] <= 5) { //makes sure value is not garbage before proceeding
				average = average + propertyPtr->survey[j][i];
			}
		}
		average = average / VACATION_RENTERS;
		printf("Category %d: %f\t", i + 1, average);
	}

}