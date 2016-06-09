/*
	* author : billywithbelly
	*
	* objects:
	* a header that contains all members
*/
#ifndef OBJECTS_H
#define OBJECTS_H

#include "library.h"

#define toI "iimage.bin"
#define toD "dimage.bin"
#define toS "snapshot.rpt"
#define toE "error_dump.rpt"


//file read/write
FILE *snapShot, *error, *PCrpt, *Datarpt, *report;
int numOfCycle = 0;
int halt = 0;
INST32 registers[32];
INST32 PC;
INST8 DMemory[MAX_LENGTH], IMemory[MAX_LENGTH];

#endif