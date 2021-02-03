#pragma once


typedef struct supplier
{
	int id;
	char name[16];
	int status;
	long firstSlaveAddress;
	int slavesCount;
} Supplier;



void getSupplier();
void updateSupplier();
void insertSupplier();
void removeSupplier();
