/*Lucas Haas
* CS 2060 ITER01
*/




#include <stdio.h>

// function prototypes
//Prints the rental property information 
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount);

//returns only valid input from the user based on the min and max values inclusively
int getValidInt(int min, int max, int sentinel);

//Calculates the charge based on the number of nights rented
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount);

//Prints the number of nights, and the charge  if there were any rentals
//Use for printing  vacationer charge or for property owner summary
void printNightsCharged(unsigned int nights, double charges);


main(void){
	int const SENTINEL_NEG1 = -1;
	int unsigned const MIN_RENTAL_NIGHTS = 1;
	unsigned int const MAX_RENTAL_NIGHTS = 14;
	unsigned int const INTERVAL_1_NIGHTS = 3;
	unsigned int const INTERVAL_2_NIGHTS = 6;
	double const RENTAL_RATE = 400;
	double const DISCOUNT = 50;

	printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
	
	unsigned int nights = 0;
	double charges = 0;
	unsigned int totalNights = 0;
	double totalCharges = 0;
	
	//Will continually execute unless returned sentinel value from within gatValidInt
	while (nights != SENTINEL_NEG1) {
		nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1);
		if (nights != -1) {
			charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);
			totalNights += nights;
			totalCharges += charges;
		}
	}
	
	printf("%s,", "Rental Property Owner Total Summary:");
	printNightsCharged(totalNights, totalCharges);
}

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount) {
	printf("Rental property can be rented for %d to %d nights.", minNights, maxNights);
	printf("\n%.2f per night for the first %d nights.", rate, interval1Nights);
	printf("\n%.2f discount rate a night for nights %d to %d.", discount, (interval1Nights + 1), interval2Nights);
	printf("\n%.2f discount rate a night for each remaining night over %d", (discount * 2), interval2Nights);

	return;
}

int getValidInt(int min, int max, int sentinel) {
	int valid = 0;
	int input = 0;

	printf("\n%s\n", "Enter the number of nights you want to rent the property");

	int check = scanf("%d", &input);
	
	while (getchar() != '\n');
	
	//check stores scanf return, while loop is invalid by default and will become 1 upon either sentinel or
	//matching value to interval specifications
	while (valid != 1) {
		if (input == sentinel) {
			valid = 1;
		}

		else if (check == 0) {
			printf("\n%s\n", "Error: Not an integer number. Please enter the value again.\n");
			check = scanf("%d", &input);
			while (getchar() != '\n');
		}

		else if (check == 1 && (input < min || input > max)) {
			printf("\nError: not within min %d min or %d max. Please enter the value again.\n", min, max);
			check = scanf("%d", &input);
			while (getchar() != '\n');
		}

		else {
			valid = 1;
		}
	}

	return input;
}

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount) {
	double charge = 0;
	if (nights <= interval1Nights) {
		charge = nights * rate;
		printNightsCharged(nights, charge);
	}
	if (nights > interval1Nights && nights <= interval2Nights) {
		charge = (interval1Nights * rate) + ((nights - interval1Nights) * (rate - discount));
		printNightsCharged(nights, charge);
	}
	if (nights > interval2Nights ) {
		charge = (interval1Nights * rate) + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - (discount * 2)));
		printNightsCharged(nights, charge);
	}

	return charge;
}

void printNightsCharged(unsigned int nights, double charges) {
	printf("%s", "Nights   Charges");
	printf("\n%d   %.2f", nights, charges);
}