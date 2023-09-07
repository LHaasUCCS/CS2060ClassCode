#include <stdio.h>;

int main(void) {
	double length = 5;
	double width = 8;
	double area = length * width;

	printf("%f\n", area);

	double divide = length / width;

	double average = (length + width) / 2;

	printf("%.1f", average);
}