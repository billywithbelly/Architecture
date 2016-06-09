#ifndef MESSY_H
#define MESSY_H

#include "objects.h"
#include "environment.h"
#include "library.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

void setArgument (char* memorySize, char* pageSize, char* cacheSize, 
    char* blockSize, char* n, int sort)
{
    switch (sort){
        //I
        case 0:
            IMemoryData.memorySize = atoi (memorySize);
            IMemoryData.pageSize = atoi (pageSize);
            ICacheData.cacheSize = atoi (cacheSize);
            ICacheData.blockSize = atoi (blockSize);
            ICacheData.nWay = atoi (n);

            IMemoryData.pageEntryNumber = IMemoryData.memorySize / IMemoryData.pageSize;
            for (int i=0; i<IMemoryData.pageEntryNumber; i++){
                IMemoryEntry[i].validBit = false;
                IMemoryEntry[i].onCycle = 0;
                for (int j=0; j<(IMemoryData.pageSize/4); j++)
                    IMemoryEntry[i].memory[j] = 0;
            }

            ICacheData.blockEntryNumber = ICacheData.cacheSize / ICacheData.blockSize;
            ICacheData.index = ICacheData.blockEntryNumber / ICacheData.nWay;
            for (int i=0; i<ICacheData.index; i++){
                for (int j=0; j<ICacheData.nWay; j++){
                    ICacheEntry[i].cacheBlock[j].validBit = false;
                    ICacheEntry[i].cacheBlock[j].MRU = 0;
                }
            }
            break;
        case 1:
            DMemoryData.memorySize = atoi (memorySize);
            DMemoryData.pageSize = atoi (pageSize);
            DCacheData.cacheSize = atoi (cacheSize);
            DCacheData.blockSize = atoi (blockSize);
            DCacheData.nWay = atoi (n);

            DMemoryData.pageEntryNumber = DMemoryData.memorySize / DMemoryData.pageSize;
            for (int i=0; i<DMemoryData.pageEntryNumber; i++){
                DMemoryEntry[i].validBit = false;
                DMemoryEntry[i].onCycle = 0;
                for (int j=0; j<(DMemoryData.pageSize/4); j++)
                    DMemoryEntry[i].memory[j] = 0;
            }

            DCacheData.blockEntryNumber = DCacheData.cacheSize / DCacheData.blockSize;
            DCacheData.index = DCacheData.blockEntryNumber / DCacheData.nWay;
            for (int i=0; i<DCacheData.index; i++){
                for (int j=0; j<DCacheData.nWay; j++){
                    DCacheEntry[i].cacheBlock[j].validBit = false;
                    DCacheEntry[i].cacheBlock[j].MRU = 0;
                }
            }
            break;
    }
}

//TLB==========================================================================================
bool checkTLB (INST32 virtualPageNumber, int sort)
{
    switch (sort)
    {
        case 0:
            for (int i=0; i<ITLBNumber; i++)
                if (ITLBEntry[i].validBit && ITLBEntry[i].tags == virtualPageNumber)
                    return true;
            return false;
        case 1:
            for (int i=0; i<DTLBNumber; i++)
                if(DTLBEntry[i].validBit && DTLBEntry[i].tags == virtualPageNumber)
                    return true;
            return false;
    }
}

INST32 readTLB (INST32 virtualPageNumber, int sort)
{
    switch (sort)
    {
        case 0:
            for (int i=0; i<ITLBNumber; i++)
                if (ITLBEntry[i].validBit && ITLBEntry[i].tags == virtualPageNumber)
                    return ITLBEntry[i].physicalPageNumber;
            break;
            //return false;
        case 1:
            for (int i=0; i<DTLBNumber; i++)
                if(DTLBEntry[i].validBit && DTLBEntry[i].tags == virtualPageNumber)
                    return DTLBEntry[i].physicalPageNumber;
            break;
            //return false;
    }
}

INST32 findUsableTLBIndex (int sort)
{
    INST32 minCycle = 100000;
    INST32 index = 0;
    switch (sort)
    {
        case 0:
            for (int i=0; i<ITLBNumber; i++)
                if (!ITLBEntry[i].validBit)
                    return numOfCycle;
                else {
                    if (ITLBEntry[i].onCycle < minCycle){
                        minCycle = ITLBEntry[i].onCycle;
                        index = 1;
                    }
                }
            
            return index;
        case 1:
            for (int i=0; i<DTLBNumber; i++)
                if(!DTLBEntry[i].validBit)
                    return numOfCycle;
                else {
                    if (DTLBEntry[i].onCycle < minCycle){
                        minCycle = DTLBEntry[i].onCycle;
                        index = 1;
                    }
                }
            return index;
    }
}

void updatePC (int counter, INST32 virtualPageNumber, int sort)
{
    switch (sort)
    {
        case 0:
            for (int i=0; i<ITLBNumber; i++)
                if (ITLBEntry[i].validBit && ITLBEntry[i].tags == virtualPageNumber)
                    ITLBEntry[i].onCycle = counter;
            break;
        case 1:
            for (int i=0; i<DTLBNumber; i++)
                if(DTLBEntry[i].validBit && DTLBEntry[i].tags == virtualPageNumber)
                    DTLBEntry[i].onCycle = counter;
            break;
    }
}

void updateTLB (INST32 index, int counter, INST32 virtualPageNumber,
        INST32 ppn, int sort)
{
    switch (sort)
    {
        case 0:
            ITLBEntry[index].validBit = true;
            ITLBEntry[index].tags = virtualPageNumber;
            ITLBEntry[index].physicalPageNumber = ppn;
            ITLBEntry[index].onCycle = counter;
            break;
        case 1:
            DTLBEntry[index].validBit = true;
            DTLBEntry[index].tags = virtualPageNumber;
            DTLBEntry[index].physicalPageNumber = ppn;
            DTLBEntry[index].onCycle = counter;
            break;
    }
}

void updateTLBWithPageFault (INST32 index, int counter, INST32 virtualPageNumber,
        INST32 ppn, int sort)
{
    switch (sort)
    {
        case 0:
            for (int i=0; i<ITLBNumber; i++)
                if (ITLBEntry[i].physicalPageNumber == ppn)
                    ITLBEntry[i].validBit = false;
            index = findUsableTLBIndex (0);

            ITLBEntry[index].validBit = true;
            ITLBEntry[index].tags = virtualPageNumber;
            ITLBEntry[index].physicalPageNumber = ppn;
            ITLBEntry[index].onCycle = counter;
            break;
        case 1:
            for (int i=0; i<DTLBNumber; i++)
                if (DTLBEntry[i].physicalPageNumber == ppn)
                    DTLBEntry[i].validBit = false;
            index = findUsableTLBIndex (1);
            
            DTLBEntry[index].validBit = true;
            DTLBEntry[index].tags = virtualPageNumber;
            DTLBEntry[index].physicalPageNumber = ppn;
            DTLBEntry[index].onCycle = counter;
            break;
    }
}
//\TLB==========================================================================================

//page==========================================================================================
bool checkPage (INST32 virtualPageNumber, int sort)
{
    switch (sort)
    {
        case 0:
            if (IPageTable.validBit[virtualPageNumber])
                return true;
            else 
                return false;
        case 1:
            if (DPageTable.validBit[virtualPageNumber])
                return true;
            else
                return false;
    }
}

INST32 readPage (INST32 virtualPageNumber, int sort)
{
    switch (sort)
    {
        case 0:
            return IPageTable.physicalPageNumber[virtualPageNumber];
        case 1:
            return DPageTable.physicalPageNumber[virtualPageNumber];
    }
}

void updatePage (INST32 virtualPageNumber, INST32 ppn, int sort)
{
    switch (sort)
    {
        case 0:
            for (int i=0; i<IPageTable.numberOfEntry; i++)
                if (IPageTable.physicalPageNumber[i] == ppn)
                    IPageTable.validBit[i] = false;
            IPageTable.validBit[virtualPageNumber] = true;
            IPageTable.physicalPageNumber[virtualPageNumber] = ppn;
        case 1:
            for (int i=0; i<DPageTable.numberOfEntry; i++)
                if (DPageTable.physicalPageNumber[i] == ppn)
                    DPageTable.validBit[i] = false;
            DPageTable.validBit[virtualPageNumber] = true;
            DPageTable.physicalPageNumber[virtualPageNumber] = ppn;
    }
}
#endif
