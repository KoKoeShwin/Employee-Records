#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Written by Mr Koe Shwin
// Contact to koeshwin00@gmail.com if you found any error in this source code

int option;
char back;
int signal;
char man_file[30];
int id;
time_t t;

FILE *fptr,*temp,*recent;


struct Data
{
    int id;
    char name[30];
    int age;
    char job[20];
    char position[30];
    char ph[20];
    char email[30];
    char physical_address[50];
    int absent_day;
    long salary;
    int absent_fee;

}man[11];


void list(void);
void menu(void);
void add_record(void);
void pay_roll(void);
void absent_day(void);
void salary(void);
void check_absent_day(void);
void search_record(void);
void delete_record(void);
void edit_record(void);
void recent_action(void);

int main()
{
    time(&t);
    system("color F0");
    printf("\n\tEmployee Records");
    printf("\n\t================");
    list();
    menu();
    return main();
}

void list()
{
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------ ");
    printf("\n[1]Search Record [2]Add Record [3]Edit Record [4]Delete Record [5]Payroll [6]Salary [7]Check Absent Day [8]Add Absent Day [9]Recent Actions [10]Exit Program ");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------ ");
}

void menu()
{
    BACK:
    printf("\nEnter Your Option :");
    scanf("%d",&option);

    switch(option)
    {
        case 1:search_record();break;
        case 2:add_record();break;
        case 3:edit_record();break;
        case 4:delete_record();break;
        case 5:pay_roll();break;
        case 6:salary();break;
        case 7:check_absent_day();break;
        case 8:absent_day();break;
        case 9:recent_action();break;
        case 10:exit(0);
        default :
            printf("\nWrong Option! \a");
            goto BACK;
    }

}

void add_record()
{
    printf("\n\tAdding Employee Records");
    printf("\n\t=======================");

    GO:
    printf("\nEnter ID :");
    scanf("%d",&man[0].id);
    printf("\nEnter Name :");
    fflush(stdin);
    gets(man[1].name);
    printf("\nEnter Age :");
    scanf("%d",&man[2].age);
    printf("\nEnter Job :");
    fflush(stdin);
    gets(man[3].job);
    printf("\nEnter Job Position :");
    gets(man[4].position);
    printf("\nEnter Email Address :");
    gets(man[5].email);
    printf("\nEnter Phone Number :");
    gets(man[6].ph);
    printf("\nEnter Physical Address :");
    gets(man[7].physical_address);

    strcpy(man_file,man[1].name);
    strcat(man_file,".dat");

    fptr=fopen(man_file,"w");
    if(fptr==0)
    {
        printf("\nRecreating the file ..........");
        fptr=fopen(man_file,"w");
    }
    fwrite(&man,sizeof(man),1,fptr);
    printf("\n\nCreated Successfully !");
    fclose(fptr);

    fprintf(recent,"Employee ID>%d named %s was added at %s",man[0].id,man[1].name,ctime(&t));
    fclose(recent);

    printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;

}

void pay_roll()
{
    printf("\n\tCalculation Payroll");
    printf("\n\t===================");

    int day;
    GO:
    printf("\nEnter the ID: ");
    scanf("%d",&id);

    fptr=fopen("Absent_Day.txt","r");
    temp=fopen("Temp.txt","w");
    if(fptr==0 && temp==0)
    {
        printf("\nRecreating the file .......");
        fptr=fopen("Absent_Day.txt","r");
        temp=fopen("Temp.txt","w");
    }

    while(fread(&man,sizeof(man),1,fptr))
    {
        if(id==man[0].id)
        {
            day=man[8].absent_day;
        }
    }

    fseek(fptr,0,SEEK_SET);

    while(fread(&man,sizeof(man),1,fptr))
    {
        if(id!=man[0].id)
        {
            fwrite(&man,sizeof(man),1,temp);

        }
    }
    fclose(fptr);
    fclose(temp);
    remove("Absent_Day.txt");
    rename("Temp.txt","Absent_Day.txt");


    printf("\nDaily Fee");
    printf("\n(1)5000Ks\n(2)6000Ks\n(3)7000Ks\n(4)8000Ks\n(5)9000Ks\n(6)10000Ks\n(7)15000Ks\n(8)20000Ks");
    BACK:
    printf("\n\nEnter the class :");
    scanf("%d",&option);

    switch(option)
    {
    case 1:
        man[9].salary=(31-day)*5000;
        man[10].absent_fee=day*5000;
        break;
    case 2:
        man[9].salary=(31-day)*6000;
        man[10].absent_fee=day*6000;
        break;
    case 3:
        man[9].salary=(31-day)*7000;
        man[10].absent_fee=day*7000;
        break;
    case 4:
        man[9].salary=(31-day)*8000;
        man[10].absent_fee=day*8000;
        break;
    case 5:
        man[9].salary=(31-day)*9000;
        man[10].absent_fee=day*9000;
        break;
    case 6:
        man[9].salary=(31-day)*10000;
        man[10].absent_fee=day*10000;
        break;
    case 7:
        man[9].salary=(31-day)*15000;
        man[10].absent_fee=day*15000;
        break;
    case 8:
        man[9].salary=(31-day)*20000;
        man[10].absent_fee=day*20000;
        break;

    default:
        printf("\nWrong Class !\a");
        goto BACK;
    }

    fptr=fopen("Salary.txt","a");
    if(fptr==0)
    {
        printf("\nRecreating the file .....");
        fptr=fopen("Salary.txt","a");
    }
         man[0].id=id;
         fwrite(&man,sizeof(man),1,fptr);
         printf("\n%ld Ks is successfully added to Employee ID %d",man[9].salary,man[0].id);
         printf("\n%d Ks was withdrawed from Employee ID>%d for %d Absent Days",man[10].absent_fee,man[0].id,day);

    fclose(fptr);

    recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }

    fprintf(recent,"%ld Ks is successfully added to Employee ID %d at %s",man[9].salary,man[0].id,ctime(&t));
    fprintf(recent,"%d Ks was withdrawed from Employee ID>%d for %d Absent Days at %s",man[10].absent_fee,man[0].id,day,ctime(&t));
    fclose(recent);


    printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;



}

void absent_day()
{
    printf("\n\tAdding Absent Day ");
    printf("\n\t==================");

    GO:
    printf("\nEnter the ID :");
    scanf("%d",&man[0].id);
    printf("\nEnter Absent Day :");
    scanf("%d",&man[8].absent_day);
    fptr=fopen("Absent_Day.txt","ab+");
    if(fptr==0)
    {
        printf("\nRecreating the file....");
        fptr=fopen("Absent_Day.txt","ab+");
    }
    fwrite(&man,sizeof(man),1,fptr);
    printf("\nAdded Successfully !");
    fclose(fptr);

    recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }
    fprintf(recent,"Employee ID>%d was added %d Absent Days at %s",man[0].id,man[8].absent_day,ctime(&t));
    fclose(recent);

    printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;


}

void salary()
{
    printf("\n\tSalary of Employee");
    printf("\n\t==================");

    GO:
    printf("\n\nIndividual Salary (1)  All Salaries (2)");
    BACK:
    printf("\nEnter command :");
    scanf("%d",&option);

    fptr=fopen("Salary.txt","r");
    if(fptr==0)
    {
        printf("\nRecreating the file ........");
        fptr=fopen("Salary.txt","r");
    }
    if(option==1)
    {
        printf("\nEnter the ID :");
        scanf("%d",&id);
        while(fread(&man,sizeof(man),1,fptr))
        {
            if(id==man[0].id)
            {
                printf("\nID :%d ",man[0].id);
                printf("\nSalary :%ld Ks",man[9].salary);
                break;
            }
        }
        fclose(fptr);
    }
    else if(option==2)
    {
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nID :%d",man[0].id);
            printf("\nSalary :%ld",man[9].salary);
        }
        fclose(fptr);
    }
    else
    {
         printf("\nWrong Option !");
         goto BACK;
    }

    recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }
    fprintf(recent,"Salary of Employee ID>%d was searched  at %s",man[0].id,ctime(&t));
    fclose(recent);

   printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;
    printf("\n\nWould you like to erase all the information of Employee salary ? ");
    printf("\nEnter command ( Y/N) :");
    back=getch();
    if(tolower(back)=='y')
    {
        remove("Salary.txt");
        printf("\nSuccessfully Erased !\n");

        recent=fopen("Recent_Action.txt","a");
        if(recent==0)
        {
        printf("\nRecreating the file ........");
        recent=fopen("Recent_Action.txt","a");
        }
        fprintf(recent,"All the info of Employee salary was erased at %s",ctime(&t));
        fclose(recent);

    }


}

void check_absent_day()
{
    printf("\n\tChecking Absent Day ");
    printf("\n\t====================");

    fptr=fopen("Absent_Day.txt","r");
    if(fptr==0)
    {
        printf("\nRecreating the file .......");
        fptr=fopen("Absent_Day.txt","r");
    }
    while(fread(&man,sizeof(man),1,fptr))
    {
        printf("\nEmployee ID :%d",man[0].id);
        printf("\tAbsent Day :%d days",man[8].absent_day);
    }

    fclose(fptr);

    recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }
    fprintf(recent,"Checked All the Absent Days at %s",ctime(&t));
    fclose(recent);

    printf("\n");
    system("pause");
}

void search_record()
{
    printf("\n\tSearching Record ");
    printf("\n\t================ ");

    GO:
    printf("\nEnter Name to search :");
    fflush(stdin);
    gets(man_file);
    strcat(man_file,".dat");

    fptr=fopen(man_file,"r");
    if(fptr==0)
    {
        printf("\nRecreating the file ..........");
        fptr=fopen(man_file,"r");
    }

    while(fread(&man,sizeof(man),1,fptr))
    {
        printf("\nEmployee ID :%d",man[0].id);
        printf("\nName :%s",man[1].name);
        printf("\nAge :%d",man[2].age);
        printf("\nJob :%s",man[3].job);
        printf("\nCurrent Position :%s",man[4].position);
        printf("\nEmail Address :%s",man[5].email);
        printf("\nPhone Number :%s",man[6].ph);
        printf("\nPhysical Address :%s",man[7].physical_address);
        break;
        printf("\nHello World !");
    }

    fclose(fptr);

    recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }
    fprintf(recent,"Employee ID>%d named %s was searched at %s",man[0].id,man[1].name,ctime(&t));
    fclose(recent);

    printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;


}

void delete_record()
{
    printf("\n\tDeleting Records ");
    printf("\n\t================ ");

    GO:
    printf("\nEnter Name to delete :");
    fflush(stdin);
    gets(man[1].name);

    strcpy(man_file,man[1].name);
    strcat(man_file,".dat");

    /*fptr=fopen(man_file,"w");
    if(fptr==0)
    {
        printf("\nRecreating the file ..........");
        fptr=fopen(man_file,"w");
    }*/
    remove(man_file);

   /*printf("\nDeleted Successfully !\a");
    fclose(fptr);*/

   printf("\nErased Successfully !\a");

   recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }
    fprintf(recent,"%s was erased at %s ",man[1].name,ctime(&t));
    fclose(recent);

    printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;

}

void edit_record()
{
    printf("\n\tEditing Records ");
    printf("\n\t=============== ");


    int id;
    char name[30];
    int age;
    char job[20];
    char position[30];
    char ph[20];
    char email[30];
    char physical_address[50];


    printf("\nEnter Name to edit :");
    fflush(stdin);
    gets(man[1].name);

    strcpy(man_file,man[1].name);
    strcat(man_file,".dat");

    GO:
    fptr=fopen(man_file,"r+");
    if(fptr==0)
    {
        printf("\nRecreating the file ..........");
        fptr=fopen(man_file,"r+");
    }

    printf("\n\tEditable List ");
    printf("\n\t============= ");

    printf("\n(1)ID (2)Name (3)Age (4)Job (5)Position (6)Phone Number (7)Email Address (8)Physical Address ");
    BACK:
    printf("\nEnter choice :");
    scanf("%d",&option);

    switch(option)
    {
    case 1:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld ID :%d",man[0].id);
            printf("\nEnter New ID :");
            scanf("%d",&id);
            man[0].id=id;
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        fclose(fptr);
        break;
    case 2:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Name :%s",man[1].name);
            printf("\nEnter New Name :");
            fflush(stdin);
            gets(name);
            strcpy(man[1].name,name);
            fseek(fptr,0,SEEK_CUR);

            strcat(name,".dat");
            temp=fopen(name,"w");
            if(temp==0)
                {
                    printf("\nRecreating the file......");
                    temp=fopen(name,"w");
                }
            fwrite(&man,sizeof(man),1,temp);
            signal=0;
        }
        fclose(temp);
        fclose(fptr);
        remove(man_file);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;

    case 3:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Age :%d",man[2].age);
            printf("\nNew Age :");
            scanf("%d",&age);
            man[2].age=age;
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }
        fclose(fptr);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;
    case 4:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Job :%s",man[3].job);
            printf("\nNew Job :");
            fflush(stdin);
            gets(job);
            strcpy(man[3].job,job);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }
        fclose(fptr);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;
    case 5:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Current Position :%s",man[4].position);
            printf("\nNew Current Position :");
            fflush(stdin);
            gets(position);
            strcpy(man[4].position,position);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }
        fclose(fptr);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;
    case 6:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Phone Number :%s",man[5].ph);
            printf("\nNew Phone Number :");
            fflush(stdin);
            gets(ph);
            strcpy(man[5].ph,ph);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }
        fclose(fptr);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;
    case 7:
       while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Email Address :%s",man[6].email);
            printf("\nNew Email Address :");
            fflush(stdin);
            gets(email);
            strcpy(man[6].email,email);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }
        fclose(fptr);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;
    case 8:
        while(fread(&man,sizeof(man),1,fptr))
        {
            printf("\nOld Physical Address :%s",man[7].physical_address);
            printf("\nNew Physical Address :");
            fflush(stdin);
            gets(physical_address);
            strcpy(man[7].physical_address,physical_address);
            fseek(fptr,0,SEEK_CUR);
            fptr=fopen(man_file,"w");
            fwrite(&man,sizeof(man),1,fptr);
            signal=0;
        }
        fclose(fptr);

        if(signal)
            printf("\nEditing Error !");
        else
            printf("\nEdited Successfully !");
        break;

    default :
        printf("\nWrong Command ! \a");
        goto BACK;


    }


    recent=fopen("Recent_Action.txt","a");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","a");
    }

    switch(option)
    {
    case 1:
        fprintf(recent,"Employee ID %d was edited at %s ",id,ctime(&t));
        fclose(recent);
        break;
    case 2:
        fprintf(recent,"Employee Name %s was edited at %s ",name,ctime(&t));
        fclose(recent);
        break;
    case 3:
        fprintf(recent,"Employee Age %d was edited at %s ",age,ctime(&t));
        fclose(recent);
        break;
    case 4:
        fprintf(recent,"Employee Job %s was edited at %s ",job,ctime(&t));
        fclose(recent);
        break;
    case 5:
        fprintf(recent,"Employee Current Position %s was edited at %s ",position,ctime(&t));
        fclose(recent);
        break;
    case 6:
        fprintf(recent,"Employee Phone Number %s was edited at %s ",ph,ctime(&t));
        fclose(recent);
        break;
    case 7:
        fprintf(recent,"Employee Email Address %s was edited at %s ",email,ctime(&t));
        fclose(recent);
        break;
    case 8:
        fprintf(recent,"Employee Physical Address %s was edited at %s ",physical_address,ctime(&t));
        fclose(recent);
        break;
    }

    printf("\nOne More (Y/N) :");
    back=getch();
    if(tolower(back)=='y')
        goto GO;

}

void recent_action()
{
    printf("\n\tRecent Activity ");
    printf("\n\t=============== ");

    char read[100];

    recent=fopen("Recent_Action.txt","r");
    if(recent==0)
    {
    printf("\nRecreating the file ........");
    recent=fopen("Recent_Action.txt","r");
    }

    while(!feof(recent))
    {
        fgets(read,100,recent);
        printf("\n%s",read);
    }
    fclose(recent);
    printf("\n");
    system("pause");

}



















