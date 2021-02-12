#include <stdio.h>
#include "supplement.h"



void getSupplement()
{
	
}


void updateSupplement()
{
	
}


void insertSupplement()
{

}


void removeSupplement()
{

}




static void readSupplement()
{
	printf_s("\n");

	printf_s("Enter price: ");
	scanf_s("%d", &supplement.price);

	printf_s("Enter amount: ");
	scanf_s("%d", &supplement.amount);

	printf_s("\n");
}


static void showSupplement()
{
	printf_s("\n");

	//printf("Master: %s, %d scores\n", master.name, master.status);
	printf("Price: %d\n", supplement.price);
	printf("Amount: %d\n", supplement.amount);

	printf_s("\n");
}