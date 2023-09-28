#include <stdio.h>
#define RENTER_SURVEY_CATEGORY 3
#define RENTER_NUMBER 5

void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int survey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY]);
int getValidInt(int min, int max);
void printSurveyResults(int survey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY]);
void calculateCategoryAverages(int survey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY], double average[RENTER_SURVEY_CATEGORY]);
void printCategoryData(double averages[RENTER_SURVEY_CATEGORY], const char* categories[RENTER_SURVEY_CATEGORY]);

int main(void) {

	int rentalSurvey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY] = { 0 };
	double categoryAverages[RENTER_SURVEY_CATEGORY] = { 0 };
	const char* surveyCategories[RENTER_SURVEY_CATEGORY] = { "Check-in Process", "Cleanliness", "Amenities" };
	
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORY);
	getRatings(rentalSurvey);
	printf("\n%s", "");
	printf("\n%s\n", "Survey Results");
	printCategories(surveyCategories, RENTER_SURVEY_CATEGORY);
	printSurveyResults(rentalSurvey);

	calculateCategoryAverages(rentalSurvey, categoryAverages);
	printCategoryData(categoryAverages, surveyCategories);
    
	
}

void getRatings(int survey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY]) {
	for (size_t i = 0; i < RENTER_NUMBER; i++) {
		printf("\nRenter %zu", i+1);
		for (size_t j = 0; j < RENTER_SURVEY_CATEGORY; j++) {
			printf("\n%s", "Enter your rating for\n");
			printf("\nCategory %zu:", j+1);
			int validInt = getValidInt(1, 5);

			survey[i][j] = validInt;
		}
	}
	

}

void printCategories(const char* categories[], size_t totalCategories)

{

    //loop to display each category horizontally 

    printf("%s", "Rating Categories:\t");

    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)

    {

        printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);

    }

    puts(""); // start new line of output 

}

int getValidInt(int min, int max) {
	int valid = 0;
	int input = 0;


	int check = scanf("%d", &input);

	while (getchar() != '\n');

	//check stores scanf return, while loop is invalid by default and will become 1 upon either sentinel or
	//matching value to interval specifications
	while (valid != 1) {

		if (check == 0) {
			printf("\n%s\n", "Error: Not an integer number. Please enter the value again.\n");
			check = scanf("%d", &input);
			while (getchar() != '\n');
		}

		else if (check == 1 && (input < min || input > max)) {
			printf("\nError: not within min %d or %d. Please enter the value again.\n", min, max);
			check = scanf("%d", &input);
			while (getchar() != '\n');
		}

		else {
			valid = 1;
		}
	}

	return input;
}

void printSurveyResults(int survey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY]) {
	for (size_t i = 0; i < RENTER_NUMBER; i++) {
		printf("\nSurvey %zu:", i + 1);
		for (size_t j = 0; j < RENTER_SURVEY_CATEGORY; j++) {
			printf("\t\t%d\t\t", survey[i][j]);
		}
	}
}

void calculateCategoryAverages(int survey[RENTER_NUMBER][RENTER_SURVEY_CATEGORY], double average[RENTER_SURVEY_CATEGORY]) {
	
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORY; i++) {
		double result = 0;
		for (size_t j = 0; j < RENTER_NUMBER; j++) {
			result += survey[j][i];
		}
		average[i] = result / RENTER_NUMBER;
	}
}

void printCategoryData(double averages[RENTER_SURVEY_CATEGORY], const char* categories[RENTER_SURVEY_CATEGORY]) {
	printf("\nRating Categories: \t");
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORY; i++) {
		printf("%s\t", categories[i]);
	}

	printf("\n%s\n", "");
	printf("\nRating averages: ");
	
	for (size_t i = 0; i < RENTER_SURVEY_CATEGORY; i++) {
		printf("\t%.1f\t\t", averages[i]);
	}
}