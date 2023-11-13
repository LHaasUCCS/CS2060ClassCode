#include <stdio.h>
#include <stdlib.h>

#define STRING_MAX 80

int stringCompare(const char string1[STRING_MAX], const char string2[STRING_MAX]);
void insert(struct pets** headPtr);
void display(const struct pets* headPtr);
void toFile(const struct pets* headPtr);
void remove(struct pets* headPtr, char nameRemove[STRING_MAX]);
//void remove all();

struct pets {
	char name[STRING_MAX];
	int age;
	struct pets *nextPtr;
};

void main() {
	struct pets* headPtr = NULL;
	insert(&headPtr);
	display(headPtr);
	toFile(headPtr);
	
}

int stringCompare(const char string1[STRING_MAX], const char string2[STRING_MAX]) {
	for (int i = 0; i < strlen(string1); i++) {
		tolower(string1[i]);
	}

	for (int i = 0; i < strlen(string2); i++) {
		tolower(string2[i]);
	}

	return strcmp(string1, string2);
}

void insert(struct pets** headPtr) {
	char input =  'y';
	while (input == 'y') {
		printf("%s: ", "Do you want to add another pet? Please enter (y)es or (n)o");
		input = getchar();
		while ((getchar()) != '\n');
		printf("\n");
		if (input == 'y') {
			struct pets* newPetPtr = malloc(sizeof(struct pets));
			printf("%s", "Enter name ");
			fgets(&(newPetPtr->name), STRING_MAX, stdin);
			newPetPtr->name[strlen(newPetPtr->name) - 1] = '\0';
			printf("\n%s", "Enter age ");
			scanf("%d", &(newPetPtr->age));
			while ((getchar()) != '\n');

			if (newPetPtr != NULL)
			{
				newPetPtr->nextPtr = NULL;

				struct pets* previousPtr = NULL;

				struct pets* currentPtr = *headPtr;


				while (currentPtr != NULL && stringCompare(currentPtr->name, newPetPtr->name) == -1)
				{
					previousPtr = currentPtr;
					currentPtr = currentPtr->nextPtr;
				}

				if (previousPtr == NULL)
				{
					*headPtr = newPetPtr;
				}
				else
				{
					previousPtr->nextPtr = newPetPtr;
				}

				newPetPtr->nextPtr = currentPtr;
			}
		}
	}
}

void display(const struct pets* headPtr) {
	if (headPtr == NULL) {
		printf("%s\n", "List is empty");
	}

	else {
		printf("%s\n", "The names in alphabetical order:");
		struct pets* currentPtr = headPtr;
		while (currentPtr != NULL) {
			printf("%s is %d years old\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;
		}
	}
}

void toFile(const struct pets* headPtr) {
	FILE* filePtr;
	if (filePtr = fopen("petlist.txt", "w") == NULL) {
		printf("%s", "Could not open file.");
	}
	else {
		filePtr = fopen("petlist.txt", "w");
	}
	if (headPtr == NULL) {
		fprintf(filePtr, "%s\n", "List is empty");
	}

	else {
		fprintf(filePtr, "%s\n", "The names in alphabetical order:");
		struct pets* currentPtr = headPtr;
		while (currentPtr != NULL) {
			fprintf(filePtr, "%s is %d years old\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;
		}
	}
	fclose(filePtr);
}

void remove(struct pets* headPtr, char nameRemove[STRING_MAX]) {

}
