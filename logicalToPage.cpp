/*
We the undersigned promise that we have in good faith attempted to follow the principles of pair programming. Although we were free to discuss ideas with others, the implementation is our own. We have shared a common workspace and taken turns at the keyboard for the majority of the work that we are submitting. Furthermore, any non programming portions of the assignment were done independently. We recognize that should this not be the case, we will be subject to penalties as outlined in the course syllabus.

Darren Ferrer
821644649 

Ethan Ha
821685521
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include<iomanip>
#include <string>
#include <math.h>
#include <array>
#include "output_mode_helpers.c"
#include "byu_tracereader.c"

using namespace std;

// contains a pointer to the level 0 page structure (Root)
typedef struct 
{
    unsigned int LevelCount = 0;
    unsigned int BitmaskAry[32];
    unsigned int numpages = 0;
    int ShiftAry[32];
    unsigned int tracker = 0;
    unsigned int EntryCount;
    unsigned int *pages;
    int frame = 0;
    bool *frame_assigned;
    unsigned int size = 0;
    unsigned int *phys_addr;
} PAGETABLE;

// represents a sublevel
// an entry for an abitrary level
typedef struct
{
    PAGETABLE *TablePtr;
    unsigned int Depth;
    // somehow intialize all to null
    unsigned int NextLevel[/* 2^NumberOfBits */];
} LEVEL;

typedef struct
{
    // somehow intialize all to invalid
    unsigned int MapPtr;
    unsigned int FrameNum;
} MAP;

// Used in leaf nodes of tree
MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress)
{
    // Do Something
    MAP *map1;
    return map1;
}

// ptr to Pagetable
void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame)
{
    // Do Something
    return;
}

// for levels
void PageInsert(LEVEL *Level, unsigned int LogicalAddress, unsigned int Frame)
{
    // Do Something
    return;
}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    unsigned int pageNumber;

    return pageNumber;
}

int main(int argc, char* argv[])
{
    // initialize a PAGETABLE object
    PAGETABLE pages;

    /* Start reading addresses */
    p2AddrTr trace_item;  /* Structure with trace information */
    bool done = false;

    int k = 1;
    FILE *fp;

    // tries to find a file it can open
    freopen("output2.txt", "w", stdout);
    while (argv != NULL)
    {
        fp = fopen(argv[k], "r");
        // if we cant open file

        // if FILE fails to open, increment k
        if (fp == NULL) 
        {
            /* couldn't open*/
            k++;
            // if the next value of k is NULL, no more args
            // print error and exit
            if (argv[k] == NULL)
            {
                cout << "Couldn't Open File" << endl;
                exit(0);
            }
        }
        // if FILE opened, break out loop
        else
        {
            break;
        }
    }

    int Option;

    while ( (Option = getopt(argc, argv, "n:o:")) != -1) {
        int i = 0;
        int z = 0;
        int shiftLeft = 0;
        unsigned int mask = 0xFFFFFFFF;
        int max_address;
        switch (Option) 
        {
            case 'n': /* Number of addresses to process */
                // optarg is the argument following -n or -o
                max_address = atoi(optarg);
                pages.numpages = atoi(optarg);
                break;

            case 'o': /* produce map of pages */
                if (optarg == string("bitmasks"))
                {
                    // optind is bits per level
                    while (argv[optind] != NULL)
                    {

                        optind++;
                        pages.LevelCount++;

                        // sets the indices of shift array to optind
                        pages.ShiftAry[i] = atoi(argv[optind]);
                        i++;

                        // if the next value is NULL, break
                        if (argv[optind + 1] == NULL)
                        {
                            break;
                        }
                    }

                    // initializes all the bitmasks into an array
                    for (i = 0; i < pages.LevelCount; i++)
                    {
                        // the default mask to shift
                        mask = 0xFFFFFFFF;
                        shiftLeft = 32 - pages.ShiftAry[i];
                        mask = mask << shiftLeft;
                        // tracker is the optinds added together
                        mask = mask >> pages.tracker;
                        pages.BitmaskAry[i] = mask;
                        pages.tracker += pages.ShiftAry[i];
                    }
                    report_bitmasks(pages.LevelCount, pages.BitmaskAry);
                    break;
                }

                if (optarg == string("offset"))
                {
                    while (argv[optind] != NULL)
                    {

                        optind++;
                        pages.LevelCount++;
                        
                        // sets the values for the shift array
                        pages.ShiftAry[i] = atoi(argv[optind]);
                        // sets the value of tracker by adding all the optinds together
                        pages.tracker += atoi(argv[optind]);
                        i++;

                        // if the next item is NULL, break out the loop
                        if (argv[optind + 1] == NULL)
                        {
                            break;
                        }
                    }

                    i = 1;
                    // reads the addresses and shifts them accordingly to get offset
                    while ( !done )
                    {
                        i++;
                        int bytesread = NextAddress(fp, &trace_item);
                        unsigned int result;
                        // shifts original address to the left, leaving only offset
                        result = trace_item.addr << pages.tracker;
                        // shift right same amount of times to get offset value
                        result = result >> pages.tracker;
                        report_logical2offset(trace_item.addr, result);

                        // if i greater than max_addresses, break
                        if (i > max_address)
                        {
                            break;
                        }
                    }
                    break;
                }

                if (optarg == string("logical2physical"))
                {
                    cout << "in logical 2 physical" << endl;
                    while (argv[optind] != NULL)
                    {
                        optind++;
                        pages.LevelCount++;
                        pages.ShiftAry[i] = atoi(argv[optind]);
                        pages.tracker += atoi(argv[optind]);
                        // pages.size would be equal to offset
                        pages.size = 32 - pages.tracker;
                        i++;

                        if (argv[optind + 1] == NULL)
                        {
                            break;
                        }
                    }
                    
                    i = 1;
                    int z = 0;
                    unsigned int physicalAddress = 0;
                    unsigned int numpages = pages.numpages;  //  equal to 2^32 / 2^pagesize
                    // initializes addrs with pages.numpages number of zeroes
                    unsigned int addrs[numpages];
                    pages.phys_addr = addrs;
                    cout << "NUMPAGES " << numpages << endl;
                    while ( !done )
                    {
                        i++;
                        int bytesread = NextAddress(fp, &trace_item);
                        //cout << hex << trace_item.addr << endl;
                        //cout << pages.size << endl; // pages.size has the n in 2^n offset
                        //dcout << physicalAddress << endl;
                        pages.phys_addr[z] = physicalAddress;
                        report_logical2physical(trace_item.addr, physicalAddress);
                        // going to the next physical address
                        physicalAddress += pow (2, pages.size);
                        z++;
                        
                        // if i greater than max_address, break
                        if (i > max_address)
                        {
                            break;
                        }
                    }
                break;
                }

                if (optarg == string("page2frame"))
                {
                    
                    while (argv[optind] != NULL)
                    {

                        optind++;
                        pages.LevelCount++;

                        pages.tracker += atoi(argv[optind]);
                        pages.ShiftAry[i] = atoi(argv[optind]);
                        i++;

                        if (argv[optind + 1] == NULL)
                        {
                            break;
                        }
                    }

                    i = 1;
                    // sets pages.frame to -1 or FFFFFFFF
                    pages.frame--;
                    while ( !done )
                    {
                        i++;
                        int bytesread = NextAddress(fp, &trace_item);
                        unsigned int result;
                        // offset = 2^(32 - pages.tracker)
                        unsigned int offset = pow(2,(32 - pages.tracker));
                        // initializes offset number of page[] and aassigned[] of zeroes
                        unsigned int page[offset];
                        bool assigned[offset];
                        bool seen_before = false;
                        pages.pages = page;
                        //assigns the page frame, saying it has been assigned
                        pages.frame_assigned = assigned;
                        // shifts the original address by offset
                        result = trace_item.addr >> (32 - pages.tracker);

                        // prints out the original address with the offset
                        cout << setw(8) << setfill('0') << hex << trace_item.addr << " ";
                        cout << setw(5) << setfill('0') << hex << result;

                        // if this is the first time in the while loop
                        // assign index 0 to result
                        if (pages.frame == -1)
                        {
                            pages.pages[0] = result;
                            pages.frame = 0;
                        }

                        // checks if we have seen this address before
                        for (z = 0; z < offset; z++)
                        {
                            // if we have seen it before
                            if (pages.pages[z] == result)
                            {
                                cout << " -> " << z << endl;
                                seen_before = true;
                                break;
                            }

                        }

                        // if we have not seen this page before, increment frame number
                        if (pages.pages[pages.frame - 1] != result && seen_before == false)
                        {
                            pages.frame++;
                            cout << " -> " << pages.frame << endl;
                        }
                        
                        // if page frame has not been assigned, then we assign it
                        if (pages.frame_assigned[pages.frame] == 0)
                        {
                            //sets this frame equal to result
                            pages.pages[pages.frame] = result;
                            //say that this fram has now been assigned
                            pages.frame_assigned[pages.frame] = 1;
                        }

                        // if i greater than max_address, break out the loop
                        if (i > max_address)
                        {
                            break;
                        }                    
                    }
                break;
                }
            default:
            // print something about the usage and die…
            printf("BADFLAG\n");
            exit(0); // BADFLAG is an error # defined in a header
        }
    }
    fclose(stdout);
    return EXIT_SUCCESS;
}