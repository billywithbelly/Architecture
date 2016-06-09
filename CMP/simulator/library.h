#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_LENGTH 1024

typedef unsigned int INST32;
typedef unsigned char INST8;

char DDisk[MAX_LENGTH];
INST32 IDisk[MAX_LENGTH];

class result
{
public:
	int hit;
	int miss;

	result(){
		hit = 0; 
		miss = 0;
	};
	~result();

	/* data */
};

bool ch, cm , th, tm , ph, pm;

int DCount;
int ICount;
int ITLBNumber;
int DTLBNumber;

//a class that stores memory data
class MemoryData
{
public:
    INST32 MemorySize;
    INST32 PageSize;
    INST32 PageEntryNumber;


     MemoryData(){
        MemorySize = 32;
        PageSize = 16;
        PageEntryNumber = MemorySize / PageSize;
     };
    /* data */
};

//a class that stores cache data
class CacheData
{
public:
    INST32 CacheSize;
    INST32 BlockSize;
    int nWay;
    INST32 BlockEntryNumber;
    int index;


     CacheData(){
        CacheSize = 16;
        BlockSize = 4;
        nWay = 1;
        BlockEntryNumber = CacheSize / BlockSize;
        index = BlockEntryNumber / nWay;
     };
    /* data */
};

//memory entry
class MemoryEntry
{
public:
    char memory[MAX_LENGTH];
    bool validBit;
    int cycle;

   	MemoryEntry(){
        for (int i=0; i<MAX_LENGTH; i++)
            memory[i] = '\0'
        validBit = false;
        cycle = 0;
    };
    /* data */
};

//DCacheEntry
class CacheBlockEntry
{
public:
    char content[128];
    bool validBit;
    INST32 tags;
    int MRU;

    CacheBlockEntry(){
        for (int i=0; i<128; i++)
            content[i] = 0;
        validBit = false;
        tags = 0;
        MRU = 0;
    };
    /* data */
};

class CacheSetEntry
{
public:
    CacheBlockEntry *CacheBlock;

    DCacheSetEntry(){
        CacheBlock = new CacheBlockEntry[128];
    };
    /* data */
};

class TLBEntry
{
public:
	bool validBit;
	INST32 tags;
	INST32 physicalPageNumber;
	int cycle;

	TLBEntry(){
		validBit = false;
		tags = 0;
		physicalPageNumber = 0;
		cycle = 0;
	};
	/* data */
};

class PageTable
{
public:
	int NumberOfEntry;
	int PageSize;
	bool validBit[100000];
	INST32 physicalPageNumber[100000];

	PageTable(){
		NumberOfEntry = 0;
		PageTable = 0;
		for (int i=0; i<100000; i++){
			validBit[i] = false;
			physicalPageNumber[i] = 0;
		}
	};
	/* data */
};

//blocks~
//datas
MemoryData DMemoryData, IMemoryData;
CacheData DCacheData, ICacheData;
PageTable IPageTable, DPageTable;
TLBEntry *ITLBEntry, *DTLBEntry;

result DCacheResult, ICacheResult;
result DTLBResult, ITLBResult;
result DPageResult, IPageResult;

//entries
MemoryEntry *DMemoryEntry, *IMemoryEntry;
CacheSetEntry *DCacheSetEntry, *ICacheEntry;

#endif