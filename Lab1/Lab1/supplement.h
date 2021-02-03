#pragma once


typedef struct supplement
{
	int masterId;
	int productId;
	int price;
	int amount;
	int exists;
	long selfAddress;
	long nextAddress;
} Supplement;



void getSupplement(); 
void updateSupplement();
void insertSupplement();
void removeSupplement();





