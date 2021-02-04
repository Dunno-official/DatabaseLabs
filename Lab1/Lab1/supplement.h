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



static Supplement supplement;


void getSupplement(); 
void updateSupplement();
void insertSupplement();
void removeSupplement();

static void readSupplement();
static void showSupplement();





