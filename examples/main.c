// 1h Ergasia SysPro - MAVROMMATIS PANAGIOTIS - sdi1800115 //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>

#include "structs.h"
#include "mainQuestionsFunctions.h"
#include "skipListFunctions.h"
#include "StartersAndHelpFunctions.h"
#include "bloomfilter.h"
#include "bloomFunctions.h"
#include "BST.h"





int main(int argc, char *argv[] )
{   
    srand(time(NULL));
    struct Citizen *headCitizen=NULL; //single linked list gia tous Citizens
    struct Country *rootC=NULL; //BST riza gia to Countries
    struct Virus *rootV=NULL; //BST riza gia to Viruses
    int noOfVirs = 0, noOfCountries = 0; //plithos viruses and countries
    int **bArrays;
    struct uInput *command;
    int result;


    if (!argsOK(argc, argv)) return 0; //error checks on arguments

    printf("reading file contents\n");
    headCitizen = processFile(argv[2],&rootC, &rootV, &noOfVirs,&noOfCountries); //process citizens input file
    if (headCitizen == NULL)
    {
        printf("No records loaded. Exiting...\n");
        return 0;
    }

     //display citizen list, # of viruses for debug
    //printf("\nList Contains (sorted by ID ascending):\n");
    //printList(headCitizen);
    //printf("\nCountries\n");
   //innorderC(rootC);
    //printf("\n# of viruses: %d\n",noOfVirs);

// traverse BSTs for debug
    // innorderV(rootV);

    //bloom: Xrhsimopoiw int. Kathe int exei sizeof(int) bytes. Ara an to bloomsize einai stai 100.000 bytes kai sizeof(int)=4, xreiazomaste pinaka me 25.000 akeraious
    long int bloomSize = atol(argv[4]); //parameter
    long int bArrayLength = bloomSize / (long)sizeof(int);
    printf("\nThere are %d viruses (rows), each with a bloom 1-d array of size %ld (columns)\n",noOfVirs,bArrayLength);
    bArrays = (int **)malloc(sizeof (int *)*(noOfVirs));
    for (int v=0; v<noOfVirs; v++) bArrays[v] = (int *) malloc(sizeof(int)*bArrayLength);
    for (int lines = 0; lines<noOfVirs; lines++)
        for (long cols=0; cols<bArrayLength; cols++)
            bArrays[lines][cols]=0;

    bArrays = makeBloom(headCitizen,rootV,bArrays,bloomSize);// dimiourgeia toy bloomfilter


   struct SkipListHead **Table_of_Heads;
   Table_of_Heads=CreateAllSkipLists(headCitizen,rootV,noOfVirs);//dimiourgeia twn SkipList
   //print_TableOfSkipList(Table_of_Heads,noOfVirs); // emfanizei ola ta skipList, xrhsimopoeithike gia debug
   



// main loop
    printf("\nyour wish is my command, bro!>");
    command = checkUserInput();
    while (command->command !=0)
    {
        switch (command->command)
        {
        case 1://vaccineStatusBloom
            result = doFirstOption(command,bArrays, rootV,headCitizen, bloomSize);
            if (result ==-1) printf("ID or virusname not exist\n"); else
            if (result) printf ("MAYBE\n"); else printf("NOT VACCINATED\n");
            break;
        case 2:
            result = search_in_SkipList_with_virus(Table_of_Heads,noOfVirs,command);
            break; //vaccineStatus
        case 3:
            result =search_in_SkipList(Table_of_Heads,noOfVirs,command);
            break; //vaccineStatus citizenID
        case 4:
            result = population_status(Table_of_Heads,noOfVirs,noOfCountries,rootC,command);
            break; //populationStatus
        case 5:
            result = population_status_age(Table_of_Heads,noOfVirs,noOfCountries,rootC,command);
            break; //popStatusByAge
        case 6:
            Table_of_Heads = insert_new_citizen_record(Table_of_Heads,&noOfVirs,&noOfCountries,headCitizen,&bArrays,bloomSize,rootV,rootC,command);
            break; //insertCitizenRecord
        case 7:
            Table_of_Heads = vaccinate_Now(Table_of_Heads,&noOfVirs,&noOfCountries,headCitizen,&bArrays,bloomSize,rootV,rootC,command);
            break; //vaccinateNow
        case 8:
            result = list_nonVaccinated(Table_of_Heads,&noOfVirs,command);
            break; //list-nonVaccinated-Persons
        default:
            printf("Error in command, try again\n");
            break;
        }
        printf("your wish is my command, bro!>");
        free(command);
        command = checkUserInput();

    }

    printf("Exiting....freeing memory...\n");
    free(command);
    //free BSTs
    freeBSTC (rootC);
    freeBSTV(rootV);
    //free bloom arrays
    for (int v=0; v<noOfVirs; v++) 
        free(bArrays[v]);
    free(bArrays);
    //free SkipLists
    struct SkipListHead *Headpointer=NULL;
    struct SkipListNode *Nodepointer=NULL;
    struct SkipListNode *NodepointerHolder=NULL;
    int dnoOfVirs=noOfVirs*2;
    int maxdepth=0;
    for(int i=0;i<dnoOfVirs;i++){
        if(Table_of_Heads[i]!=NULL){
            Headpointer=Table_of_Heads[i];
            maxdepth=Headpointer->depth;
            for(int j=0;j<DEPTH_MAX_LIMIT;j++){
                if(Headpointer->next[j]!=NULL){    
                    Nodepointer=Headpointer->next[j];
                    while(Nodepointer!=NULL){
                        NodepointerHolder=Nodepointer->next;
                        free(Nodepointer);
                        Nodepointer=NodepointerHolder;
                    }
                }
            }
            free(Headpointer);
        }
    }
    free(Table_of_Heads);
    free(NodepointerHolder);

struct Citizen *headCitizenHold=NULL;
    //free Citizen single linked list
    while(headCitizen!=NULL)
    {
        free(headCitizen->citizenID);
        free(headCitizen->firstName);
        free(headCitizen->lastName);
        free(headCitizen->vaccinated);
        free(headCitizen->dateVaccinated);
        headCitizenHold=headCitizen;
        headCitizen=headCitizen->next;
        free(headCitizenHold);
    }

    return 0;
}
