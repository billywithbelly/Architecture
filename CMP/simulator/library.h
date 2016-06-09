#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_LENGTH 1024

typedef unsigned int INST32;
typedef unsigned char INST8;

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
    INST32 memorySize;
    INST32 pageSize;
    INST32 pageEntryNumber;


     MemoryData(){
        memorySize = 32;
        pageSize = 16;
        pageEntryNumber = memorySize / pageSize;
     };
    /* data */
};

//a class that stores cache data
class CacheData
{
public:
    INST32 cacheSize;
    INST32 blockSize;
    int nWay;
    INST32 blockEntryNumber;
    int index;


     CacheData(){
        cacheSize = 16;
        blockSize = 4;
        nWay = 1;
        blockEntryNumber = cacheSize / blockSize;
        index = blockEntryNumber / nWay;
     };
    /* data */
};

//memory entry
class MemoryEntry
{
public:
    char memory[MAX_LENGTH];
    bool validBit;
    int onCycle;

   	MemoryEntry(){
        for (int i=0; i<MAX_LENGTH; i++)
            memory[i] = 0;
        validBit = false;
        onCycle = 0;
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
    CacheBlockEntry *cacheBlock;

    CacheSetEntry(){
        cacheBlock = new CacheBlockEntry[128];
    };
    /* data */
};

class TLBEntry
{
public:
	bool validBit;
	INST32 tags;
	INST32 physicalPageNumber;
	int onCycle;

	TLBEntry(){
		validBit = false;
		tags = 0;
		physicalPageNumber = 0;
		onCycle = 0;
	};
	/* data */
};

class PageTable
{
public:
	int numberOfEntry;
	int pageSize;
	bool validBit[100000];
	INST32 physicalPageNumber[100000];

	PageTable(){
		numberOfEntry = 64;
		pageSize = 0;
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
CacheSetEntry *DCacheEntry, *ICacheEntry;

#endif