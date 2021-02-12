#include "DBcontroller.h"



int checkIndexExistence(FILE* indexTable, int ID)
{
	fseek(indexTable, 0, SEEK_END);

	long indexTableSize = ftell(indexTable);

	return indexTableSize != 1L && ID * sizeof(Indexer) <= indexTableSize;
}

