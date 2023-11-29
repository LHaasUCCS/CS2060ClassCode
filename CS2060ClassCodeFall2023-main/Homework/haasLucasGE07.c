#include <stdio.h>
#include <stdlib.h>

#define STRING_MAX 80

typedef struct pets {
	char name[STRING_MAX];
	int age;
	struct pets* nextPtr;
} Pets;


int stringCompare(const char string1[STRING_MAX], const char string2[STRING_MAX]);
void insert(Pets** headPtr);
void display(const Pets* headPtr);
void toFile(const Pets* headPtr);
void removePet(Pets** headPtr);
void removeAll(Pets* headPtr);

void main() {
	Pets* headPtr = NULL;
	insert(&headPtr);
	display(headPtr);
	toFile(headPtr);
	removePet(&headPtr);
	removeAll(headPtr);
	
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

void insert(Pets** headPtr) {
	char input =  'y';
	while (input == 'y') {
		printf("%s: ", "Do you want to add another pet? Please enter (y)es or (n)o");
		input = getchar();
		while ((getchar()) != '\n');
		printf("\n");
		if (input == 'y') {
			Pets* newPetPtr = malloc(sizeof(Pets));
			printf("%s", "Enter name ");
			fgets(&(newPetPtr->name), STRING_MAX, stdin);
			newPetPtr->name[strlen(newPetPtr->name) - 1] = '\0';
			printf("\n%s", "Enter age ");
			scanf("%d", &(newPetPtr->age));
			while ((getchar()) != '\n');

			if (newPetPtr != NULL)
			{
				newPetPtr->nextPtr = NULL;

				Pets* previousPtr = NULL;

				Pets* currentPtr = *headPtr;


				while (currentPtr != NULL && strcmp(currentPtr->name, newPropPtr->name) < 0) {
					previousPtr = currentPtr;
					currentPtr = currentPtr->nextPtr;
				}

				if (currentPtr == NULL) {
					// Handle the case where you reached the end of the list
					// You might want to append newPropPtr to the end in this case
					if (previousPtr == NULL) {
						*headPtr = newPropPtr;  // Set as the first node if the list is empty
					}
					else {
						previousPtr->nextPtr = newPropPtr;  // Append to the end of the list
					}
				}
				else {
					// Your existing logic for inserting in the middle of the list
					if (previousPtr == NULL) {
						*headPtr = newPropPtr;
					}
					else {
						previousPtr->nextPtr = newPropPtr;
					}
					newPropPtr->nextPtr = currentPtr;
				}
			}
		}
	}
}

void display(const Pets* headPtr) {
	if (headPtr == NULL) {
		printf("%s\n", "List is empty");
	}

	else {
		printf("%s\n", "The names in alphabetical order:");
		Pets* currentPtr = headPtr;
		while (currentPtr != NULL) {
			printf("%s is %d years old\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;
		}
	}
}

void toFile(const Pets* headPtr) {
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
		Pets* currentPtr = headPtr;
		while (currentPtr != NULL) {
			fprintf(filePtr, "%s is %d years old\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;
		}
	}
	fclose(filePtr);
}

void removePet(Pets** headPtr) {
	Pets* previous = NULL;
	Pets* current = *headPtr;

	char input = 'y';
	while (input == 'y') {
		char nameToDelete[STRING_MAX];
		puts("Do you want to delete a pet from the list? Please enter (y)es or (no): ");
		input = getchar();
		while (getchar() != '\n');


		if (input == 'y') {
			puts("Enter the pet's name to delete");
			fgets(&nameToDelete, STRING_MAX, stdin);
			nameToDelete[strlen(nameToDelete) - 1] = '\0';
			
			if (*headPtr != NULL) {
				
				if (strcmp((*headPtr)->name, nameToDelete) == 0) {
					*headPtr = (*headPtr)->nextPtr;
					 
					free(current);
					current = NULL;
				}
				
				else 
				{
					
					while (current != NULL && strcmp(current->name, nameToDelete) != 0)
					{
						 
						previous = current;
						current = current->nextPtr;
					}

						
					if (current != NULL)
					{
						 
						previous->nextPtr = current->nextPtr;
						
						free(current);
						current = NULL;
					}
					
					else
					{
						printf("%s is not found in the list of pets!\n", nameToDelete);
					}
				}
				display(*headPtr);
			}
			else 
			{
				puts("There are no pets in the list!");
				input = 'n';
			}
		}
	}
}

void removeAll(Pets* headPtr)
{
	Pets* current = headPtr;
	Pets* nextPtr = NULL;

	while (current != NULL)
	{
		nextPtr = current->nextPtr;
		free(current);
		current = nextPtr;
	}

	headPtr = NULL;
}
