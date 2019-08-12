#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Node
{
    char name[30];
    char number[12];
    char email[50];
    char birth[12];
    char title[30];
    struct Node* next;
};
void saveList(struct Node *head,int choice)
{
    sorting(head,choice);

    FILE *fptr;
    fptr = fopen("CompanyDatabase.txt","w");
    if(fptr == NULL)
    {
        perror("Error!");
    }
    struct Node *current_node = head;
    while ( current_node != NULL)
    {
        fprintf(fptr,"\"%s,",current_node->name);
        fprintf(fptr,"%s,",current_node->number);
        fprintf(fptr,"%s,",current_node->email);
        fprintf(fptr,"%s,",current_node->birth);
        fprintf(fptr,"%s\"\n",current_node->title);

        current_node = current_node->next;
    }
    fclose(fptr);
}

void bubbleSort(struct Node *start)
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {

            if (toupper(ptr1->name[0]) > toupper(ptr1->next->name[0]))
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void swap(struct Node *a, struct Node *b)
{
    char temp[50];
    init(50,temp);
    strcpy(temp,a->name);
    strcpy(a->name,b->name);
    strcpy(b->name,temp);

    strcpy(temp,a->number);
    strcpy(a->number,b->number);
    strcpy(b->number,temp);

    strcpy(temp,a->birth);
    strcpy(a->birth,b->birth);
    strcpy(b->birth,temp);

    strcpy(temp,a->email);
    strcpy(a->email,b->email);
    strcpy(b->email,temp);

    strcpy(temp,a->title);
    strcpy(a->title,b->title);
    strcpy(b->title,temp);



}

void sorting(struct Node *head,int choice)
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    if (head == NULL)
    {
        printf("List is empty!");
        return;
    }
    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            int year1 = ((ptr1->birth[6]-'0')*1000)+((ptr1->birth[7]-'0')*100)+((ptr1->birth[8]-'0')*10)+(ptr1->birth[9]-'0');
            int year2 = ((ptr1->next->birth[6]-'0')*1000)+((ptr1->next->birth[7]-'0')*100)+((ptr1->next->birth[8]-'0')*10)+(ptr1->next->birth[9]-'0');

            switch(choice)
            {
            case 1:
                if (toupper(ptr1->name[0]) > toupper(ptr1->next->name[0]))
                {
                    swap(ptr1, ptr1->next);
                    swapped = 1;

                }
                break;
            case 2:
                if (toupper(ptr1->name[0]) < toupper(ptr1->next->name[0]))
                {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                break;
            case 3:

                if (year1 < year2)
                {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                break;
            case 4:

                if (year1 > year2)
                {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                break;
            default:
                printf("\nNot sorted!\n");
                return;
                break;
            }

            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}


struct Node* add(struct Node* head,char* name1,char* number1,char *email1,char *birth1,char *title1);

int testName(char* name)
{
    int z=0;
    if(name[0]==NULL)
        return 1;
    for(int i=0; i<strlen(name); i++)

    {
        if(isalpha(name[i])==0&&name[i]!=' ')
            z++;
    }
    if(z!=0)
    {
        printf("\nPlease enter a valid name\n");
        z=0;
        return 1;
    }
    else
        return 0;
}
int testNumber(char *number)
{

    int z=0;
    for(int i=0; i<10; i++)
    {
        if(number[i]==NULL||(int)number[i]>57||(int)number[i]<48)
            z++;
    }
    if(z!=0)
    {
        printf("\nPlease Enter A valid Number\n");
        z=0;
        return 1;
    }
    else
        return 0;
}
int testEmail(char* email)
{
    int sign=0,dot=0;
    char email_org[3][10]= {{"yahoo"},{"gmail"},{"hotmail"}};

    for (int i=0; i<50; i++)
    {
        if(email[i]=='@')
            sign=i;
        if(email[i]=='.')
            dot=i;
    }
    int m=0;
    char email_comp[dot-sign+1];
    init(dot-sign+1,email_comp);
    for (int i=sign+1; i<dot; i++)
    {
        email_comp[m]=email[i];
        m++;
    }
    int z=0;
    int match=0;
    for(int i=0; i<3; i++)
    {
        if(strcmp(email_org[i],email_comp)==0)
            match=1;
    }

    if (sign==0||dot==0)
    {
        printf("\nPlease Enter A valid email\n");
        return 1;
    }
    else if (match==0)
    {
        printf("\nPlease Enter A valid organization\n");
        return 1;
    }
    else if(((int)email[0])<57&&((int)email[0])>48)
    {
        printf("\nPlease Enter A valid Email (cannot start with a number)\n");
        return 1;
    }
    else
        return 0;

}


int testTitle(char* title1)
{

    char ch;
    FILE *fp;
    char buffer[255];
    char line[30][20];
    int i = 0;
    int tot = 0;
    fp = fopen("CompanyInfo.txt", "r");
    if(fp == NULL)
    {
        perror("CompanyInfo.txt Not found!");
    }

    while(fgets(line[i], 30, fp))
    {
        line[i][strlen(line[i])] = '\0';
        i++;
    }
    tot= i;
    char info[tot][15];
    for (int k=0; k<tot; k++)
    {
        for (int d=0; d<15; d++)
        {
            info[k][d]=NULL;

        }
    }

    for(i= 0; i < tot; i++)
    {
        for(int y=0; y<15; y++)
        {
            if(line[i][y]=='\n')
            {
                line[i][y]==NULL;
                break;
            }
            info[i][y]=line[i][y];
        }
    }
    fclose(fp);
    for(int c= 0; c < tot; c++)
    {
        for(int y=0; y<15; y++)
        {
            info[c][y]=toupper(info[c][y]);
        }
    }
    for (int t=0; t<strlen(title1); t++)
    {
        title1[t]=toupper(title1[t]);
    }
    int match=0;
    for(int s=0; s<tot; s++)
    {
        if(strcmp(title1,info[s])==0)
        {
            match=1;
            break;
        }
    }
    if(match==1)
        return 0;
    else if(match==0)
    {
        printf("\nTitle not found in the database!\n");
        return 1;
    }
    else
        return 0;
}



int testBirth(char *birth)
{
    int year = ((birth[6]-'0')*1000)+((birth[7]-'0')*100)+((birth[8]-'0')*10)+(birth[9]-'0');
    if (year<1959||year>1996)
    {
        printf("\nPlease Enter A Valid Year\n");
        return 1;

    }
    int z=0;
    for(int i=0; i<10; i++)
    {
        if(i==2||i==5)
            continue;
        if((int)birth[i]>57||(int)birth[i]<48)
            z++;
    }
    if(z!=0)
    {
        printf("\nPlease Enter A Valid Format\n");
        return 1;
    }
    else if((birth[2]!='/')||(birth[5]!='/'))
    {
        printf("\nPlease Enter A Valid Format\n");
        return 1;
    }
    else if(birth[0]>'3')
    {
        printf("\nPlease Enter A Valid Format\n");
        return 1;
    }
    else if(birth[3]>'1')  // 11/02/2014
    {
        printf("\nPlease Enter A Valid Format\n");
        return 1;
    }
    else if (birth[1]>'1'&&birth[0]=='3'&&((birth[3]=='0'&&birth[4]=='1')||(birth[3]=='0'&&birth[4]=='3')||(birth[3]=='0'&&birth[4]=='5')||(birth[3]=='0'&&birth[4]=='7')||(birth[3]=='0'&&birth[4]=='8')||(birth[3]=='1'&&birth[4]=='0')||(birth[3]=='1'&&birth[4]=='2')))
    {
        printf("\nPlease Enter A Valid Formatt\n");
        return 1;
    }
    else if (birth[1]>'0'&&birth[0]=='3'&&((birth[3]=='0'&&birth[4]=='2')||(birth[3]=='0'&&birth[4]=='4')||(birth[3]=='0'&&birth[4]=='6')||(birth[3]=='0'&&birth[4]=='9')||(birth[3]=='1'&&birth[4]=='1')))
    {
        printf("\nPlease Enter A Valid Formatt\n");
        return 1;
    }
    else if (birth[4]>'2'&&birth[3]=='1')
    {
        printf("\nPlease Enter A Valid Format\n");
        return 1;
    }
    else if (birth[3]=='0'&&birth[4]=='2'&&(birth[0]=='2'||birth[0]=='3'))
    {
        if(birth[0]=='3')
        {
            printf("\nPlease Enter A Valid Format (Leap Year)\n");
            return 1;
        }

        if((year% 4 == 0 && year%100 != 0 || year%400 == 0)&&birth[1]>'9')
        {
            printf("\nPlease Enter A Valid Format (Leap Year)\n");
            return 1;
        }
        else if ((!(year% 4 == 0 && year%100 != 0 || year%400 == 0))&&birth[1]>'8')
        {
            printf("\nPlease Enter A Valid Format (Leap Year)\n");
            return 1;
        }
    }
    else
        return 0;
}

struct Node* del(char* name, struct Node *head)
{
    struct Node *current_node = head;
    struct Node *prev_node;
    int cnt = 0;
    if(head==NULL)
    {
        printf("\nList is empty\n");
        return;
    }
    while ( current_node != NULL)
    {
        if (strcmp(current_node->name,name)==0)
        {
            cnt++;
            if (current_node == head)
            {
                head = current_node->next;
            }
            else
            {
                prev_node->next = current_node->next;
            }

        }
        prev_node = current_node;
        current_node = current_node->next;
    }
    if(cnt==0)
    {
        printf("\nName not found!\n");
    }
    else
        printf("\n%s is removed!\n",name);
    return head;
}


void Search(char* name, struct Node *head)
{
    struct Node *current_node = head;
    int cnt = 0;
    if(head==NULL)
    {
        printf("\nList is empty!\n");
        return;
    }
    while ( current_node != NULL)
    {
        if (strcmp(current_node->name,name)==0)
        {
            cnt++;
            printf("\n\"%s,",current_node->name);
            printf("%s,",current_node->number);
            printf("%s,",current_node->email);
            printf("%s,",current_node->birth);
            printf("%s\"\n",current_node->title);
            return;
        }
        current_node = current_node->next;
    }
    if(cnt==0)
    {
        printf("\nName not found!\n");

    }
}
void modify(struct Node *head,char* name,int choice)
{

    struct Node *current_node = head;
    int cnt = 0;
    char temp[50];
    init(50,temp);
    if(head==NULL)
    {
        printf("\nList is empty!\n");
        return;
    }
    while ( current_node != NULL)
    {
        if (strcmp(current_node->name,name)==0)
        {
            cnt++;
            switch (choice)
            {
            case 1:
                fflush(stdin);
                for(;;)
                {
                    fflush(stdin);
                    printf("\nEnter %s's number: ",current_node->name);
                    scanf("%[^\n]",temp);
                    if((testNumber(temp)==1))
                    {
                        continue;
                    }
                    else
                    {
                        init(12,current_node->number);
                        strcpy(current_node->number,temp);
                        printf("\nModified!\n");
                        break;
                    }
                }
                break;
            case 2:
                fflush(stdin);
                for(;;)
                {
                    fflush(stdin);
                    printf("Enter %s's email: ",current_node->name);
                    scanf("%[^\n]",temp);
                    if((testEmail(temp)==1))
                    {
                        continue;
                    }
                    else
                    {
                        init(50,current_node->email);
                        strcpy(current_node->email,temp);
                        printf("\nModified!\n");
                        break;
                    }
                }

                break;
            case 3:
                for(;;)
                {
                    fflush(stdin);
                    printf("Enter %s's title: ",current_node->name);
                    scanf("%[^\n]",temp);
                    if((testTitle(temp)==1))
                    {
                        continue;
                    }
                    else
                    {
                        init(50,current_node->title);
                        strcpy(current_node->title,temp);
                        printf("\nModified!\n");
                        break;
                    }
                }

                break;
            default:
                printf("\nEnter a valid option!\n");
            }
            return;
        }
        current_node = current_node->next;
    }
    if(cnt==0)
    {
        printf("\nName not found!\n");

    }




}





void init(int arr_count,char*arr)
{
    for(int i=0; i<arr_count; i++)
        arr[i]=NULL;
}

int main()
{
    int sort_choice;
    char op1 = NULL;

    struct  Node* head = NULL;
    char namet[30];
    char numbert[12];
    char emailt[50];
    char birtht[12];
    char titlet[50];

    for(int maincount=0;; maincount++)
    {
        if (maincount==0){
      printf("\nSOAD Company Database\n---------------------------------------\n");
            goto label1;}
        int choice;
    printf("\n1. ADD\n2. LOAD\n3. DELETE\n4. SAVE\n5. SEARCH\n6. MODIFY\n7. QUIT\n");

        printf("\nPlease enter the number of the operation\n");
        scanf("%d",&choice);
        fflush(stdin);
        switch (choice)
        {
        case 1:
        {

            int z=0;
            init(30,namet);
            for(;;)
            {
                fflush(stdin);
                printf("Enter the name: ");
                for(int i=0; i<50; i++)
                {

                    scanf("%c",&namet[i]);
                    if(namet[i]=='\n')
                    {
                        namet[i]=NULL;
                        break;
                    }
                }
                fflush(stdin);

                if (testName(namet)==1)
                    continue;
                else
                    break;
            }
            init(12,numbert);
            fflush(stdin);
            for(;;)
            {
                printf("Enter the phone number: ");
                for(int i=0; i<12; i++)
                {
                    scanf("%c",&numbert[i]);
                    if(numbert[i]=='\n')
                    {
                        numbert[i]=NULL;
                        break;
                    }
                }
                fflush(stdin);
                if(testNumber(numbert)==1)
                    continue;
                else
                    break;
            }
            fflush(stdin);
            for(;;)
            {
                printf("Enter The email: ");
                init(50,emailt);
                int sign=0,dot=0;

                for (int i=0; i<50; i++)
                {
                    scanf("%c",&emailt[i]);
                    if(emailt[i]=='\n')
                    {
                        emailt[i]=NULL;
                        break;
                    }
                }
                fflush(stdin);

                if (testEmail(emailt)==1)
                    continue;
                else
                    break;
            }
            fflush(stdin);
            for(;;)
            {
                init(12,birtht);
                printf("Enter the birthday in the format dd/mm/yyyy :");

                for(int i=0; i<12; i++)
                {
                    scanf("%c",&birtht[i]);
                    if(birtht[i]=='\n')
                    {
                        birtht[i]=NULL;
                        break;
                    }
                }

                fflush(stdin);

                if(testBirth(birtht)==1)
                    continue;
                else
                    break;
            }
            fflush(stdin);
            for(;;)
            {
                fflush(stdin);
                init(50,titlet);
                printf("Enter the title: ");
                for(int i=0; i<50; i++)
                {
                    scanf("%c",&titlet[i]);
                    if(titlet[i]=='\n')
                    {
                        titlet[i]=NULL;
                        break;
                    }
                }
                fflush(stdin);
                char    *title_modify =   (char*)malloc(sizeof(char));
                strcpy(title_modify,titlet);
                if(testTitle(title_modify)==1)
                    continue;
                else
                    break;
            }
            head=add(head,namet,numbert,emailt,birtht,titlet);
            printf("\n%s has been added!\n",namet);
            break;
        }
        case 2:
        {

            char ch, file_name[25];
            FILE *fp;

            printf("\nEnter name of an employee file you wish to add\n");
            gets(file_name);

label1:
            if(maincount==0)
            {
                fp = fopen( "CompanyDatabase.txt", "r");
            }
            else
            {
                fp = fopen(file_name, "r"); // read mode
            }
            if (fp == NULL)
            {
                perror("\nError while opening the file.\n");

            }
            int z=0,d=0,n=0,m=0,e=0,b=0,t=0;

            char data[100][100];
            init(100,data);
            init(30,namet);
            init(12,numbert);
            init(12,birtht);
            init(30,emailt);
            init(50,titlet);
            int data_count=0,tot=0;
            while(fgets(data[data_count], 100, fp))
            {
                data[data_count][strlen(data[data_count])] = '\0';
                data_count++;
            }
            tot = data_count;
            fclose(fp);
            int quotes=0;
            for(int count=0; count<tot; count++)
            {

                z=0,d=0,n=0,m=0,e=0,b=0,t=0;
                init(30,namet);
                init(12,numbert);
                init(12,birtht);
                init(30,emailt);
                init(50,titlet);
                for(int i=0; i<strlen(data[count]); i++)
                {
                    if(data[count][i]=='\n')
                    {
                        data[count][i]==NULL;
                        break;
                    }
                    if (data[count][i]=='"')
                    {
                        quotes++;
                        continue;
                    }

                    if (quotes%2==0)
                        continue;

                    if(data[count][i]==',')
                    {
                        z++;
                        continue;
                    }
                    if(z==0)
                    {
                        namet[n]=data[count][i];
                        n++;
                        continue;
                    }
                    else if(z==1)
                    {
                        if(data[count][i]==' ')
                            continue;
                        numbert[m]=data[count][i];
                        m++;
                        continue;
                    }
                    else if(z==2)
                    {
                        if(data[count][i]==' ')
                            continue;

                        emailt[e]=data[count][i];
                        e++;
                        continue;
                    }
                    else if(z==3)
                    {
                        if(data[count][i]==' ')
                            continue;

                        birtht[b]=data[count][i];
                        b++;
                        continue;
                    }
                    else if(z==4)
                    {

                        titlet[t]=data[count][i];
                        t++;
                        continue;

                    }
                }
                if((quotes%2)!=0)
                {
                    printf("\nEnter A valid format!\n");
                }

                if(testBirth(birtht)==1)
                    continue;
                else if((testName(namet)==1))
                    continue;
                else if((testNumber(numbert)==1))
                    continue;
                else if((testEmail(emailt)==1))
                    continue;
                else if((testTitle(titlet)==1))
                    continue;
                else
                {
                    head=add(head,namet,numbert,emailt,birtht,titlet);
                    if (maincount!=0)

                        printf("\n%s has been added!\n");
                }
            }


            break;
        }
        case 3:
        {
            init(50,namet);
            fflush(stdin);
            printf("\n Enter the name of the employee to remove: ");
            for(int i=0; i<50; i++)
            {

                scanf("%c",&namet[i]);
                if(namet[i]=='\n')
                {
                    namet[i]=NULL;
                    break;
                }
            }
            fflush(stdin);
            char op=NULL;

            printf("\n Are you sure you want to remove %s? (y/n)  ",namet);
            op=getchar();
            switch (op)
            {
            case 'Y':
            case 'y':
                head=del(namet,head);
                break;
            case 'N':
            case 'n':
                break;
                break;
            default:
                printf("\nPlease enter a valid answer\n");
            }


            break;
        }

        case 4:
        {
            if(head==NULL)
            {
                printf("\nList is empty\n");
                break;
            }

            printf("Sort By:\n1. A-Z\n2. Z-A \n3. Youngest to eldest\n4. Eldest to youngest\n");
            scanf("%d",&sort_choice);
            sorting(head,sort_choice);
            saveList(head,sort_choice);
            printf("\nList has been saved!\n");
            break;
        }
        case 5:
        {
            init(50,namet);
            fflush(stdin);
            printf("\n Enter the name of the employee: ");
            for(int i=0; i<50; i++)
            {

                scanf("%c",&namet[i]);
                if(namet[i]=='\n')
                {
                    namet[i]=NULL;
                    break;
                }
            }

            fflush(stdin);
            Search(namet,head);
            break;
        }
        case 6:
        {
            init(50,namet);
            fflush(stdin);
            printf("\n Enter the name of the employee: ");
            for(int i=0; i<50; i++)
            {

                scanf("%c",&namet[i]);
                if(namet[i]=='\n')
                {
                    namet[i]=NULL;
                    break;
                }
            }

            fflush(stdin);
            printf("\n1. Number\n2. Email\n3. Title\n\nThe number of the required field to be modified: ");
            int modify_choice;
            scanf("%d",&modify_choice);
            fflush(stdin);

            modify(head,namet,modify_choice);
            break;
        }
        case 7:

            printf("\n Do you want to save from A-Z? (y/n/any other button to go back) ");
            op1=getchar();
            switch (op1)
            {
            case 'Y':
            case 'y':
                saveList(head,1);
                printf("\nSAVED!\n");
                printf("\n========CODED BY EMARA========\n");
                return 0;
            case 'N':
            case 'n':
                printf("\n========CODED BY EMARA========\n");
                return 0;
                break;
            default:
                break;
            }
            break;
        default:
            printf("\nEnter a valid option!\n");
            break;
        }

    }

    return 0;
}
struct Node* add(struct Node* head,char* name1,char* number1,char *email1,char *birth1,char *title1)

{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    strcpy(new_node->name,name1);
    strcpy(new_node->number,number1);
    strcpy(new_node->email,email1);
    strcpy(new_node->birth,birth1);
    strcpy(new_node->title,title1);
    new_node->next = head;
    head = new_node;
    return head;

}

