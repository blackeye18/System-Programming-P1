// 1h Ergasia SysPro - MAVROMMATIS PANAGIOTIS - sdi1800115 //
#ifndef __mainQuestionsFunctions__
#define __mainQuestionsFunctions__


int doFirstOption(struct uInput *cmd , int **bArrays, struct Virus *rootV, struct Citizen *head, long int bloomSize);
int search_in_SkipList_with_virus(struct SkipListHead ** Table_of_Heads,int noOfVirs,struct uInput *cmd);
int search_in_SkipList(struct SkipListHead ** Table_of_Heads,int noOfVirs,struct uInput *cmd);
int DateInRange(char* sdate0,char* sdate1,char* sdate2);
int population_status(struct SkipListHead ** Table_of_Heads,int noOfVirs,int noOfCountries,struct Country *root,struct uInput *cmd);
int population_status_age(struct SkipListHead ** Table_of_Heads,int noOfVirs,int noOfCountries,struct Country *root,struct uInput *cmd);
int** updateBloom(long int bloomSize,struct Virus *rootV,int *noOfVirs,struct Citizen *head);
struct SkipListHead ** help_insert_c_record(struct SkipListHead ** Table_of_Heads,int *noOfVirs,int *noOfCountries,struct Citizen *head,int ***bArrays, long int bloomSize, struct Virus *rootV,struct Country *rootC,char lineData[9][50]);
struct SkipListHead ** insert_new_citizen_record(struct SkipListHead ** Table_of_Heads,int *noOfVirs,int *noOfCountries,struct Citizen *head,int ***bArrays, long int bloomSize, struct Virus *rootV,struct Country *rootC, struct uInput *cmd);
struct SkipListHead ** vaccinate_Now(struct SkipListHead ** Table_of_Heads,int *noOfVirs,int *noOfCountries,struct Citizen *head,int ***bArrays, long int bloomSize, struct Virus *rootV,struct Country *rootC, struct uInput *cmd);
int list_nonVaccinated(struct SkipListHead ** Table_of_Heads,int *noOfVirs,struct uInput *cmd);

#endif