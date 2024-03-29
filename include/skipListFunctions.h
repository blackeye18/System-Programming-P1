// 1h Ergasia SysPro - MAVROMMATIS PANAGIOTIS - sdi1800115 //
#ifndef __skipListFunctions__
#define __skipListFunctions__

int flip_a_coin();
int rand_depth();
struct SkipListHead *CreateNewSkipList(struct Citizen *headC,char *vaccinated_or_no, char *virusName);
struct SkipListHead **CreateAllSkipLists(struct Citizen *headC,struct Virus *rootV,int noOfVirs);
void print_TableOfSkipList(struct SkipListHead ** Table_of_Heads,int noOfVirs);
int insert_in_SkipList(struct SkipListHead ** Table_of_Heads,struct Citizen *headC,int noOfVirs);
int delete_from_SkipList(struct SkipListHead ** Table_of_Heads,struct Citizen *headC,int noOfVirs );

#endif