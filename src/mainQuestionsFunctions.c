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

//1h epilogh
int doFirstOption(struct uInput *cmd , int **bArrays, struct Virus *rootV, struct Citizen *head, long int bloomSize){
    char *ID = cmd->args[1];
    char *vName = cmd->args[2];

    struct Virus *tmp = searchVirus(&rootV,vName);
    if (tmp==NULL) return -1;
    struct Citizen *tmp1 = searchList(head,ID);
    if (tmp1 ==NULL) return -1;
    for (unsigned int idx = 0; idx < NO_OF_HASH_FUNCTIONS; idx++) //16 functions
            {
                unsigned long bit = hash_i((unsigned char *) tmp1->citizenID, idx) % bloomSize;
                int chk = checkBit(bArrays[tmp->rank],bit);
                if (chk ==0) return 0;
            }
 return 1;
}


//2h epilogh
int search_in_SkipList_with_virus(struct SkipListHead ** Table_of_Heads,int noOfVirs,struct uInput *cmd){
    char *citizenID = cmd->args[1];
    char *virusName = cmd->args[2];
    int dnoOfVirs=noOfVirs*2;
    struct SkipListHead* Headpointer=NULL;
    struct SkipListNode * Nodepointer=NULL;
    int i,j,k,flag=0,flag2=0,local_max_depth=0;
    for(i=0;i<dnoOfVirs;i++){
        Headpointer=Table_of_Heads[i];
        if(strcmp(Headpointer->vaccinated_or_no,"YES")==0){//an vrikame to swsto skiplist
            if(strcmp(Headpointer->virusName,virusName)==0){
                flag=1;
                local_max_depth=Headpointer->depth;//apothikevoume to megisto vathos/ypsos ths sygkekrimenhs skiplist
                for(j=local_max_depth-1;j>=0;j--){// paw anapoda gia mikroterh polyplokothta, an to vrei se pio psilo shmeio
                    Nodepointer=Headpointer->next[j];
                    while(Nodepointer!=NULL){//psaxnoume to skiplistnode pou mas endiaferei
                        if(strcmp(Nodepointer->citizen_node->citizenID,citizenID)==0){
                            flag2=1;
                            if(strcmp(Nodepointer->citizen_node->vaccinated,"YES")==0){//an to vroume emfanizoume analogo minima
                                printf("VACCINATED ON %s\n",Nodepointer->citizen_node->dateVaccinated );
                                return 0;}
                        }
                        Nodepointer=Nodepointer->next;
                    }
                }
            }
        }

    }
    if (flag==0 || flag2==0)
        printf("NOT VACCINATED\n");//an telika den to vrikame pali emfanizoume analogo mnm
    return 1;
}
//3h epilogh
int search_in_SkipList(struct SkipListHead ** Table_of_Heads,int noOfVirs,struct uInput *cmd){
    char *citizenID = cmd->args[1];
    int dnoOfVirs=noOfVirs*2;
    struct SkipListHead* Headpointer=NULL;
    struct SkipListNode * Nodepointer=NULL;
    int i,j,k,flag=0,flag2=0,local_max_depth=0;
    for(i=0;i<dnoOfVirs;i++){
        Headpointer=Table_of_Heads[i];//to idio me panw aplws pleon psaxnoume se oles tis skip list afou mas endiaferei gia olous tous ious
        
        local_max_depth=Headpointer->depth;
        flag2=0;
            for(j=local_max_depth-1;j>=0;j--){
                if(flag2==0){
                    Nodepointer=Headpointer->next[j];
                    while(Nodepointer!=NULL){
                        if(strcmp(Nodepointer->citizen_node->citizenID,citizenID)==0){//an vrikame to id pou mas endiaferei
                            flag2=1;
                            flag=1;
                            printf("%s %s %s \n",Nodepointer->citizen_node->virusName->virusName,Nodepointer->citizen_node->vaccinated,Nodepointer->citizen_node->dateVaccinated );//ektypwnoume ta stoixeia tou, opws zhteite sthn ekfwnhsh
                        }
                        Nodepointer=Nodepointer->next;
                    }
                }
            }
            
    }
    if (flag==0){
        printf("ERROR! GIVEN ID DOES NOT EXIST\n" );
        return 1;
    }else 
        return 0;
    
}
//Elegxei an to date0 einai anamesa sto date1 kai date2 
int DateInRange(char* sdate0,char* sdate1,char* sdate2){//to date0 einai afto poy theloyme na doyme an einai endimesa sto date1 kai sto date2
    char * date0;
    char* date1;
    char* date2;
    date0=strdup(sdate0);
    date1=strdup(sdate1);
    date2=strdup(sdate2);
//spame to string se day month year vash ths - kai meta to kanoume noumera kai sygkrinoume
    char* tmp=strtok(date0,"-");
    char* day0=strdup(tmp);
    tmp=strtok(NULL,"-");
    char* month0=strdup(tmp);
    tmp=strtok(NULL,"-");
    char* year0=strdup(tmp);
    tmp=strtok(NULL,"-");

    char* tmp1=strtok(date1,"-");
    char* day1=strdup(tmp1);
    tmp1=strtok(NULL,"-");
    char* month1=strdup(tmp1);
    tmp1=strtok(NULL,"-");
    char* year1=strdup(tmp1);
    tmp1=strtok(NULL,"-");

    char* tmp2=strtok(date2,"-");
    char* day2=strdup(tmp2);
    tmp2=strtok(NULL,"-");
    char* month2=strdup(tmp2);
    tmp2=strtok(NULL,"-");
    char* year2=strdup(tmp2);
    tmp2=strtok(NULL,"-");

    int iday0=atoi(day0),iday1=atoi(day1),iday2=atoi(day2);
    int imonth0=atoi(month0),imonth1=atoi(month1),imonth2=atoi(month2);
    int iyear0=atoi(year0),iyear1=atoi(year1),iyear2=atoi(year2);
    int flag1=0,flag2=0;

    if(iyear1<iyear0)
        flag1=1;
    if(iyear1==iyear0 && imonth1<imonth0)
        flag1=1;
    if(iyear1==iyear0 && imonth1==imonth0 && iday1<iday0)
        flag1=1;

    if(iyear0<iyear2)
        flag2=1;
    if(iyear0==iyear2 && imonth0<imonth2)
        flag2=1;
    if(iyear0==iyear2 && imonth0==imonth2 && iday0<iday2)
        flag2=1;
    free(date0);
    free(date1);
    free(date2);
    free(day0);
    free(month0);
    free(year0);
    free(day1);
    free(month1);
    free(year1);
    free(day2);
    free(month2);
    free(year2);
    if(flag1==1 && flag2==1)
        return 1;
    else
        return 0;

    return 0;
}
//4h epilogh
int population_status(struct SkipListHead ** Table_of_Heads,int noOfVirs,int noOfCountries,struct Country *root,struct uInput *cmd){
    int i,j;
    struct SkipListHead* Headpointer=NULL;
    struct SkipListNode * Nodepointer=NULL;
    int dnoOfVirs=noOfVirs*2;
    float percentage=0;
    if(cmd->argnum==5){//ama theloume sygkekrimenh xwra
        float yescounter=0,nocounter=0,yescounterdate=0;
        float percentage=0;
        char *country = cmd->args[1];
        char *virusName = cmd->args[2];
        char *date1 = cmd->args[3];
        char *date2 = cmd->args[4];
        for(i=0;i<dnoOfVirs;i++){
            Headpointer=Table_of_Heads[i];
            if(strcmp(Headpointer->virusName,virusName)==0){//vriskoume thn skiplist pou mas endiaferei
                if(strcmp(Headpointer->vaccinated_or_no,"YES")==0){//gia ta yes counter
                    Nodepointer=Headpointer->next[0];//psaxnoume sto ypsos 0 poy exei sigoura ola ta stoxeia
                    while(Nodepointer!=NULL){
                        if(strcmp(country,Nodepointer->citizen_node->country->countryName)==0){//an einai h xwra pous endiaferei
                            yescounter++;
                            if(DateInRange(Nodepointer->citizen_node->dateVaccinated,date1,date2)){//kai einai kai endiamesa stis hmeromhnies
                                yescounterdate++;  
                            }
                        }
                        Nodepointer=Nodepointer->next;
                    }
                }
                if(strcmp(Headpointer->vaccinated_or_no,"NO")==0){//gia ta no counter
                    Nodepointer=Headpointer->next[0];//mhdenikh dioti ta xreiazomai ola etsi kai alliws opote to xrisimopoiw san list
                    while(Nodepointer!=NULL){
                        if(strcmp(country,Nodepointer->citizen_node->country->countryName)==0)//an einai h xwra pous endiaferei
                            nocounter++;
                        Nodepointer=Nodepointer->next;
                    }   
                }                
            }
        }
        if((yescounter+nocounter)!=0 && yescounterdate!=0 )//den diairw me 0
            percentage=(yescounterdate/(yescounter+nocounter)*100);
        printf("%s %.f %.2f%%\n",country,yescounterdate,percentage );//emfanizw opws zhteite sthn ekfwnhsh

    }
    else if(cmd->argnum==4){// an den dinete orisma country, kanoume akrivws to idio me panw alla gia kathe xwra opote xrisimopoiw pinakes pleon
        char *virusName = cmd->args[1];
        char *date1 = cmd->args[2];
        char *date2 = cmd->args[3];
        j=0;
        char** Table_of_Countries=NULL;
        Table_of_Countries=malloc(noOfCountries*sizeof(char*));
        makearrayCountry(root,Table_of_Countries,&j);
        float yescounter[noOfCountries],nocounter[noOfCountries],yescounterdate[noOfCountries];
        float percentage[noOfCountries];
        for(i=0;i<noOfCountries;i++){
            yescounter[i]=0.0;
            nocounter[i]=0.0;
            yescounterdate[i]=0.0;
            percentage[i]=0.0;
        }
        for(i=0;i<dnoOfVirs;i++){
            Headpointer=Table_of_Heads[i];
            if(strcmp(Headpointer->virusName,virusName)==0){
                if(strcmp(Headpointer->vaccinated_or_no,"YES")==0){
                    Nodepointer=Headpointer->next[0];
                    while(Nodepointer!=NULL){
                        j=0;
                        while(strcmp(Table_of_Countries[j],Nodepointer->citizen_node->country->countryName)!=0)
                            j++;
                        yescounter[j]++;
                        if(DateInRange(Nodepointer->citizen_node->dateVaccinated,date1,date2)){
                            yescounterdate[j]++;  
                        }
                        Nodepointer=Nodepointer->next;
                    }
                }
                if(strcmp(Headpointer->vaccinated_or_no,"NO")==0){
                    Nodepointer=Headpointer->next[0];//mhdenikh dioti ta xreiazomai ola etsi kai alliws opote to xrisimopoiw san list
                    while(Nodepointer!=NULL){
                        j=0;
                        while(strcmp(Table_of_Countries[j],Nodepointer->citizen_node->country->countryName)!=0)
                            j++;
                        nocounter[j]++;
                        Nodepointer=Nodepointer->next;
                    }   
                }                
            }
        }
        for(j=0;j<noOfCountries;j++){
            if((yescounter[j]+nocounter[j])!=0 && yescounterdate[j]!=0){
                percentage[j]=(yescounterdate[j]/(yescounter[j]+nocounter[j])*100);
            }
            printf("%s %.f %.2f%%\n",Table_of_Countries[j],yescounterdate[j],percentage[j] );
        }
        free(Table_of_Countries);
    }
    return -1;

}
//5h epilogh
int population_status_age(struct SkipListHead ** Table_of_Heads,int noOfVirs,int noOfCountries,struct Country *root,struct uInput *cmd){
   int i,j;
    struct SkipListHead* Headpointer=NULL;
    struct SkipListNode * Nodepointer=NULL;
    int dnoOfVirs=noOfVirs*2;
    float percentage=0;
    if(cmd->argnum==5){//opws kai prin an mas dinete country
        float yescounter[4],nocounter[4],yescounterdate[4];//kanw akrivws oti ekana kai apo panw aplws me pinaka 4 thesewn, dhladh gia kathe hlikiakh omada
        float percentage[4];
        char *country = cmd->args[1];
        char *virusName = cmd->args[2];
        char *date1 = cmd->args[3];
        char *date2 = cmd->args[4];
        
        for(i=0;i<4;i++){
            yescounter[i]=0.0;
            nocounter[i]=0.0;
            yescounterdate[i]=0.0;
            percentage[i]=0.0;
        }
        
        for(i=0;i<dnoOfVirs;i++){
            Headpointer=Table_of_Heads[i];
            if(strcmp(Headpointer->virusName,virusName)==0){
                if(strcmp(Headpointer->vaccinated_or_no,"YES")==0){
                    Nodepointer=Headpointer->next[0];
                    while(Nodepointer!=NULL){
                        if(strcmp(country,Nodepointer->citizen_node->country->countryName)==0){
            
                            if(Nodepointer->citizen_node->age>=0 && Nodepointer->citizen_node->age<20)//>=0 <20
                                yescounter[0]++;
                            else if(Nodepointer->citizen_node->age>=20 && Nodepointer->citizen_node->age<40)//>=20 <40
                                yescounter[1]++;
                            else if(Nodepointer->citizen_node->age>=40 && Nodepointer->citizen_node->age<60)//>=40 <60
                                yescounter[2]++;
                            else if(Nodepointer->citizen_node->age>=60)// >=60
                                yescounter[3]++;
                            else
                                printf("ERROR WITH AGE!\n");
                            if(DateInRange(Nodepointer->citizen_node->dateVaccinated,date1,date2)){
                            
                                if(Nodepointer->citizen_node->age>=0 && Nodepointer->citizen_node->age<20)
                                    yescounterdate[0]++;
                                else if(Nodepointer->citizen_node->age>=20 && Nodepointer->citizen_node->age<40)
                                    yescounterdate[1]++;
                                else if(Nodepointer->citizen_node->age>=40 && Nodepointer->citizen_node->age<60)
                                    yescounterdate[2]++;
                                else if(Nodepointer->citizen_node->age>=60)
                                    yescounterdate[3]++;
                                else
                                    printf("ERROR WITH AGE!\n");  
                            }
                        }
                        Nodepointer=Nodepointer->next;
                    }
                }
                if(strcmp(Headpointer->vaccinated_or_no,"NO")==0){
                    Nodepointer=Headpointer->next[0];//mhdenikh dioti ta xreiazomai ola etsi kai alliws opote to xrisimopoiw san list
                    while(Nodepointer!=NULL){
                        if(strcmp(country,Nodepointer->citizen_node->country->countryName)==0)
                        
                            if(Nodepointer->citizen_node->age>=0 && Nodepointer->citizen_node->age<20)
                                nocounter[0]++;
                            else if(Nodepointer->citizen_node->age>=20 && Nodepointer->citizen_node->age<40)
                                nocounter[1]++;
                            else if(Nodepointer->citizen_node->age>=40 && Nodepointer->citizen_node->age<60)
                                nocounter[2]++;
                            else if(Nodepointer->citizen_node->age>=60)
                                nocounter[3]++;
                            else
                                printf("ERROR WITH AGE!\n");
                        Nodepointer=Nodepointer->next;
                    }   
                }                
            }
        }
        printf("%s\n",country);
        for(i=0;i<4;i++){
            if((yescounter[i]+nocounter[i])!=0 && yescounterdate[i]!=0)
                percentage[i]=(yescounterdate[i]/(yescounter[i]+nocounter[i])*100);
            if(i==0)
                printf("0-20 ");//<20 kai meta >=20 klp
            else if(i==1)
                printf("20-40 ");
            else if(i==2)
                printf("40-60 ");
            else if(i==3)
                printf("60+ ");
            printf("%.f %.2f%%\n",yescounterdate[i],percentage[i] );
        }

        

    }
    else if(cmd->argnum==4){//ama den exw orisma country
        char *virusName = cmd->args[1];
        char *date1 = cmd->args[2];
        char *date2 = cmd->args[3];
        j=0;
        char** Table_of_Countries=NULL;
        Table_of_Countries=malloc(noOfCountries*sizeof(char*));
        makearrayCountry(root,Table_of_Countries,&j);
        float yescounter[noOfCountries][4],nocounter[noOfCountries][4],yescounterdate[noOfCountries][4];//opws eipa kai prin, kanw akrivws oti ekana kai apo panw aplws me disdiastato pinaka
        float percentage[noOfCountries][4];//opou kathe grammh einai diaforetikh xwra, kai gia kathe xwra exw 4 hlikiakes omades
       
        
        for(i=0;i<noOfCountries;i++){
            for(j=0;j<4;j++){
                yescounter[i][j]=0.0;
                nocounter[i][j]=0.0;
                yescounterdate[i][j]=0.0;
                percentage[i][j]=0.0;
            }
        }
        for(i=0;i<dnoOfVirs;i++){
            Headpointer=Table_of_Heads[i];
            if(strcmp(Headpointer->virusName,virusName)==0){
                if(strcmp(Headpointer->vaccinated_or_no,"YES")==0){
                    Nodepointer=Headpointer->next[0];
                    while(Nodepointer!=NULL){
                        j=0;
                        while(strcmp(Table_of_Countries[j],Nodepointer->citizen_node->country->countryName)!=0)
                            j++;
                        if(Nodepointer->citizen_node->age>=0 && Nodepointer->citizen_node->age<20)
                            yescounter[j][0]++;
                        else if(Nodepointer->citizen_node->age>=20 && Nodepointer->citizen_node->age<40)
                            yescounter[j][1]++;
                        else if(Nodepointer->citizen_node->age>=40 && Nodepointer->citizen_node->age<60)
                            yescounter[j][2]++;
                        else if(Nodepointer->citizen_node->age>=60)
                            yescounter[j][3]++;
                        else
                            printf("ERROR WITH AGE!\n");
                        if(DateInRange(Nodepointer->citizen_node->dateVaccinated,date1,date2)){
                            if(Nodepointer->citizen_node->age>=0 && Nodepointer->citizen_node->age<20)
                                yescounterdate[j][0]++;
                            else if(Nodepointer->citizen_node->age>=20 && Nodepointer->citizen_node->age<40)
                                yescounterdate[j][1]++;
                            else if(Nodepointer->citizen_node->age>=40 && Nodepointer->citizen_node->age<60)
                                yescounterdate[j][2]++;
                            else if(Nodepointer->citizen_node->age>=60)
                                yescounterdate[j][3]++;
                            else
                                printf("ERROR WITH AGE!\n");  
                        }
                        Nodepointer=Nodepointer->next;
                    }
                }
                if(strcmp(Headpointer->vaccinated_or_no,"NO")==0){
                    Nodepointer=Headpointer->next[0];//mhdenikh dioti ta xreiazomai ola etsi kai alliws opote to xrisimopoiw san list
                    while(Nodepointer!=NULL){
                        j=0;
                        while(strcmp(Table_of_Countries[j],Nodepointer->citizen_node->country->countryName)!=0)
                            j++;
                        if(Nodepointer->citizen_node->age>=0 && Nodepointer->citizen_node->age<20)
                            nocounter[j][0]++;
                        else if(Nodepointer->citizen_node->age>=20 && Nodepointer->citizen_node->age<40)
                            nocounter[j][1]++;
                        else if(Nodepointer->citizen_node->age>=40 && Nodepointer->citizen_node->age<60)
                            nocounter[j][2]++;
                        else if(Nodepointer->citizen_node->age>=60)
                            nocounter[j][3]++;
                        else
                            printf("ERROR WITH AGE!\n");
                        Nodepointer=Nodepointer->next;
                    }   
                }                
            }
        }
        for(i=0;i<noOfCountries;i++){
            printf("%s\n",Table_of_Countries[i]);
            for(j=0;j<4;j++){
            if((yescounter[i][j]+nocounter[i][j])!=0 && yescounterdate[i][j]!=0){
                percentage[i][j]=(yescounterdate[i][j]/(yescounter[i][j]+nocounter[i][j])*100);

            }
            if(j==0)
                printf("0-20 ");//<20 kai meta >=20 klp
            else if(j==1)
                printf("20-40 ");
            else if(j==2)
                printf("40-60 ");
            else if(j==3)
                printf("60+ ");
            printf("%.f %.2f%%\n",yescounterdate[i][j],percentage[i][j] );
            }
        }
        free(Table_of_Countries);
    }
    return -1;

}
//voithikh synarthsh gia thn 6h epilogh, gia thn dhmiourgeia neou bloom filter
int** updateBloom(long int bloomSize,struct Virus *rootV,int *noOfVirs,struct Citizen *head){//oti kanw kai sthn main, afou dimiourgw apo thn arxh bloom
    int **NewbArrays;
    long int bArrayLength = bloomSize / (long)sizeof(int);
    NewbArrays = (int **)malloc(sizeof (int *)*(*noOfVirs));
    
    for (int v=0; v<*noOfVirs; v++) 
        NewbArrays[v] = (int *) malloc(sizeof(int)*bArrayLength);
    
    for (int lines = 0; lines<*noOfVirs; lines++){
        //free(bArrays[lines]);
       
        for (long cols=0; cols<bArrayLength; cols++){
            NewbArrays[lines][cols]=0;
        }
    }
    
   
    NewbArrays = makeBloom(head,rootV,NewbArrays,bloomSize);


    return NewbArrays;

}

//voithikh synarthsh gia thn 6h epilogh, gia periptwseis pou xreiazetai dhmiourgeia neou komvou sthn arxikh single linked list, dhladh exoume kainouria dedomena kai aples allages
struct SkipListHead ** help_insert_c_record(struct SkipListHead ** Table_of_Heads,int *noOfVirs,int *noOfCountries,struct Citizen *head,int ***bArrays, long int bloomSize, struct Virus *rootV,struct Country *rootC,char lineData[9][50]){
    struct Citizen *headholder=head;
    char *citizenID=strdup(lineData[1]);
    char *firstName=strdup(lineData[2]);
    char *lastName=strdup(lineData[3]);
    char *Country=strdup(lineData[4]);
    char *age=strdup(lineData[5]);
    char *virusName = strdup(lineData[6]);
    char *YesOrNo=strdup(lineData[7]);
    char *date=strdup(lineData[8]);
    int VirusFlag=0;
    int VirusCountHolder=0;
    struct Virus *tempV;
    //vlepw an exw hdh ton io gia na kserw an yparxei hdh bloom filter kai skip lists gia afton h oxi.
    tempV = searchVirus(&rootV,lineData[6]); 
    if (tempV == NULL)
    {
        VirusFlag=1;
        VirusCountHolder=*noOfVirs;
    }
    
    head=addToList(head,lineData, &rootC, &rootV, noOfVirs,noOfCountries );// to prosthetw sthn arxiki lista
    *bArrays=updateBloom(bloomSize,rootV,noOfVirs,head);//friaxnw to ananewmeno bloomfilter

    
    if(VirusFlag){//an prepei na ftiaksw skip list epeidh einai neos ios to kanw, diaforetika synexizw
        if(VirusCountHolder<*noOfVirs){//deyteros elegxos gia na eimai sigouros, an h ylopoihsh mou einai swsth afto einai axreiasto
            int dnoOfVirs=*noOfVirs*2;
            int i;
            struct SkipListHead **NewTable_of_Heads;

            NewTable_of_Heads=malloc(dnoOfVirs*sizeof(struct SkipListHead *));
            for(i=0;i<dnoOfVirs-2;i++){
                NewTable_of_Heads[i]=Table_of_Heads[i];//adigrafw ta hdh yparxwn skiplists
            }
            NewTable_of_Heads[dnoOfVirs-2]=CreateNewSkipList(head,"NO",virusName);// kai ftiaxnw gia YES kai gia NO gia ton kainourio io
            NewTable_of_Heads[dnoOfVirs-1]=CreateNewSkipList(head,"YES",virusName);
            free(Table_of_Heads);
            //edw exoume kapoia mikra memory leaks apo tis strdup, den mporw na tis kanw free epeidh tis xrhsimopoiw meta kai tha exw segmentation
            //Me psaksimo ftiaxnete aplws den exw ton xrono......
            // free(citizenID);
            // free(firstName);
            // free(lastName);
            // free(Country);
            // free(age);
            // free(virusName);
            // free(YesOrNo);
            // free(date);
           
            return NewTable_of_Heads;
        }
    }else{
        while(head!=NULL){
            if(strcmp(citizenID,head->citizenID)==0 && strcmp(virusName,head->virusName->virusName)==0)//vriskw to head pou ekana insert
                break;

            head=head->next;
        }
        insert_in_SkipList(Table_of_Heads,head,*noOfVirs);//kai to eisxwrw se hdh yparxwn skip list
        // free(Table_of_Heads);
        // free(citizenID);
        // free(firstName);
        // free(lastName);
        // free(Country);
        // free(age);
        // free(virusName);
        // free(YesOrNo);
        // free(date);
        return Table_of_Heads;
    }

  

}

//6h epilogh
struct SkipListHead ** insert_new_citizen_record(struct SkipListHead ** Table_of_Heads,int *noOfVirs,int *noOfCountries,struct Citizen *head,int ***bArrays, long int bloomSize, struct Virus *rootV,struct Country *rootC, struct uInput *cmd){
    char *citizenID=cmd->args[1];
    char *firstName=cmd->args[2];
    char *lastName=cmd->args[3];
    char *Country=cmd->args[4];
    char *age=cmd->args[5];
    char *virusName = cmd->args[6];
    char *YesOrNo=cmd->args[7];
    char *date;
    int temp=0;
    struct Citizen *headholder=head;
    char lineData[9][50];
    if(strcmp(YesOrNo,"YES")==0)
        date=cmd->args[8];
    else
        date=strdup("");
    //printf("%s\n",date );
    //vlepw an yparxei id hdh, an yparxei vlepw an exei idia stoixeia. An exei diaforetika stop kai error
    while(head!=NULL){
        if(strcmp(citizenID,head->citizenID)==0){
            if((strcmp(firstName,head->firstName)) || (strcmp(lastName,head->lastName)) || (atoi(age)!=head->age) || (strcmp(Country,head->country->countryName)) ){
                printf("ERROR, ID ALREADY EXISTS WITH DIFFERENT NAME|LASTNAME|COUNTRY|AGE\n");
                if(strcmp(date,"")==0)
                    free(date);
                return Table_of_Heads;

            }
            if(strcmp(virusName,head->virusName->virusName)==0){//ama exw hdh eggrafh gia ton io
                if(strcmp("YES",head->vaccinated)==0){//kai exei hdh emvoliastei gia afton
                    printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %s\n",head->citizenID,head->dateVaccinated );
                    if(strcmp(date,"")==0)
                    free(date);
                    return Table_of_Heads;
                }
                else if(strcmp("NO",head->vaccinated)==0 && strcmp("YES",YesOrNo)==0){//ama yparxei hdh me no kai prepei na to kaw yes
                    //prepei diagrapsw apo no skip list kai eisxwrhsw se nai skip list
                    temp=delete_from_SkipList(Table_of_Heads,head,*noOfVirs);
                    strcpy(head->vaccinated,"YES");
                    strcpy(head->dateVaccinated,date);
                    temp=insert_in_SkipList(Table_of_Heads,head,*noOfVirs);
                    printf("Updated an Already Existing Rerord\n");
                    //!!!!!!BLOOM_FILTER!!!!!!!!!!!!!
                    
                    for(int lines=0;lines<*noOfVirs;lines++)
                        free((*bArrays)[lines]);
                    
                   free(*bArrays);
                    *bArrays=updateBloom(bloomSize,rootV,noOfVirs,head);
                    //prepei diagrapsw apo no skip list kai eisxwrhsw se nai skip list
                    if(strcmp(date,"")==0)
                        free(date);
                    return Table_of_Heads;
                }
                else//diaforetika exw hdh NO kai mou ksanaleei NO opote den kanw tipota
                {
                    printf("Record does not need an update\n");
                    if(strcmp(date,"")==0)
                    free(date);
                    return Table_of_Heads;
                }
            }
            
           

            
        }
        head=head->next;
            
    }
   
     //EDW KANW AMA EINAI KAINOURIO ID,IOS KLP DHLADH DEN YPARXEI HDH KAI PREPEI NA DHMIOURGHSW NEO CITIZEN KLP
                //prepei na dhmiourghsw arxika neo record sthn arxikh mou lista me ton neo io
                //meta na ftiaksw neo table of skiplist afksieno kata 2 theseis, mia gia to no kai mia gia to yes
                //meta to bloom filter gia ton io.
                //ola afta ginonte me thn voithia ths help_insert_c_record
                strcpy(lineData[1],citizenID);
                strcpy(lineData[2],firstName);
                strcpy(lineData[3],lastName);
                strcpy(lineData[4],Country);
                strcpy(lineData[5],age);
                strcpy(lineData[6],virusName);
                strcpy(lineData[7],YesOrNo);
                strcpy(lineData[8],date);
                for(int lines=0;lines<*noOfVirs;lines++)
                    free((*bArrays)[lines]);
                free(*bArrays);                
                Table_of_Heads=help_insert_c_record(Table_of_Heads,noOfVirs,noOfCountries,headholder,bArrays,bloomSize,rootV,rootC,lineData);
                //print_TableOfSkipList(Table_of_Heads,*noOfVirs);
                if(strcmp(date,"")==0)
                    free(date);
                return Table_of_Heads;



}

//7h epilogh, ousiastika kalei thn 6h epilogh me YES kai shmerinh hmeromhnia
struct SkipListHead ** vaccinate_Now(struct SkipListHead ** Table_of_Heads,int *noOfVirs,int *noOfCountries,struct Citizen *head,int ***bArrays, long int bloomSize, struct Virus *rootV,struct Country *rootC, struct uInput *cmd){
    time_t tm=time(NULL);
    struct tm timestruct=*localtime(&tm);
    int day,month,year;
    strcpy(cmd->args[7],"YES");//vazw YES, afou einai vaccinatenow
    //vriskw thn shmerinh hmeromhnia
    year=timestruct.tm_year + 1900;
    month=timestruct.tm_mon + 1;
    day=timestruct.tm_mday;
    //kai thn ftiaxnw sthn morfh pou thelw dld "day-month-year"
    char date[50]="";
    char temp[50]="";
    sprintf(temp,"%d",day);
    strcat(date,temp);
    strcat(date,"-");
    sprintf(temp,"%d",month);
    strcat(date,temp);
    strcat(date,"-");
    sprintf(temp,"%d",year);
    strcat(date,temp);
    strcpy(cmd->args[8],date);
    Table_of_Heads = insert_new_citizen_record(Table_of_Heads,noOfVirs,noOfCountries,head,bArrays,bloomSize,rootV,rootC,cmd);
    return Table_of_Heads;
}
//8h epilogh
int list_nonVaccinated(struct SkipListHead ** Table_of_Heads,int *noOfVirs,struct uInput *cmd){
    int dnoOfVirs=*noOfVirs*2;
    int i,j;
    struct SkipListHead* Headpointer=NULL;
    struct SkipListNode * Nodepointer=NULL;
    char *virusName=cmd->args[1];
    for(i=0;i<dnoOfVirs;i++){
        Headpointer=Table_of_Heads[i];
       if(strcmp(Headpointer->virusName,virusName)==0 && strcmp(Headpointer->vaccinated_or_no,"NO")==0){//psaxnw to skiplist pou mas endiaferei
            Nodepointer=Headpointer->next[0];
            while (Nodepointer!=NULL){//kai emfanizw ta dedomena pou prepei
                printf("%s %s %s %s %d \n",Nodepointer->citizen_node->citizenID,Nodepointer->citizen_node->firstName,Nodepointer->citizen_node->lastName, Nodepointer->citizen_node->country->countryName,Nodepointer->citizen_node->age);
                Nodepointer=Nodepointer->next;
            }
        }
    }

    return 0;
}

