#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <unistd.h>
#include <conio.h>

int n1;
int shomarande=0;
char in_topic[200];
int shomarande_topic=0;
int shomarande_topic_save=0;
int n_topic[100];
int count_scan=0;
int score=0;
int sum_score=0;
int end=0;
char name[100];
int load=0;
int see=0;


struct save
{
    int SCORE;
};
struct Load
{
    int SCORE;
};
struct topics
{
    char t[50];

};
struct topic
{
    char t[50];
};

struct topics struct_topic[100];
struct topic struct_in_topic[100];
struct save save[100];
struct Load load_struct[100];


void change_color(int c)
{
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

open_topics ()
{
    FILE *f_A_t;
    f_A_t=fopen("AVAILABLE_TOPICS.txt","r");
    if(f_A_t==NULL)
    {
        printf("can not read available topics \n");
        return -1;
    }

    int k;
    int finish=0;
    for(k=1; k<=100; k++)
    {
        int x=0;
        if(finish==1)
            break;

        while(1)
        {
            if(x==1)
                break;

            int i;
            struct_topic[k].t[0]='t';
            struct_topic[k].t[1]='o';
            struct_topic[k].t[2]='p';
            struct_topic[k].t[3]='i';
            struct_topic[k].t[4]='c';
            struct_topic[k].t[5]='s';
            struct_topic[k].t[6]='/';

            for(i=7; i<=100; i++)
            {

                char c=getc(f_A_t);

                if(c =='\n')
                {
                    struct_topic[k].t[i]='\0';
                    x=1;

                    break;
                }
                if(c==EOF)
                {
                    struct_topic[k].t[i+1]='\0';
                    x=1;
                    finish=1;
                    shomarande=k;
                    break;
                }
                struct_topic[k].t[i]=c;
                //  save[k-1].topic[i]=c;

            }

        }

    }
    change_color(8);
    printf("choose one topic : \n");


    int j;
    int j2=1;
    for(j='a'; j<='k'; j++)
    {
        change_color(14);

        printf("(%c) ",j);
        change_color(15);

        int k;
        for(k=7; k<=100; k++)
        {
            if(struct_topic[j2].t[k]=='.')
                break;
            printf("%c",struct_topic[j2].t[k]);
        }
        printf("\n");
        if(j2==shomarande)
            break;
        j2++;

    }
    char n;
    scanf(" %c",&n);
    if(n=='Q')
    {
        end=1;
        return;
    }
    n1=n;

    n_topic[count_scan]=n1;
    count_scan++;
    int  is_tekrari=0;
    int i;
    if(count_scan>1)
        for(i=count_scan-2; i>=0; i--)
        {

            if(n_topic[i]==n1)
            {
                while(1)
                {
                    int cc=0;

                    printf("this topic choosed before \n");
                    printf("choose a new topic \n");
                    scanf(" %c",&n1);
                    if(n1=='Q')
                    {
                        end=1;
                        return;
                    }
                    int j;
                    for(j=count_scan-2; j>=0; j--)
                    {
                        if(n_topic[j]!=n1)
                            cc++;

                    }
                    if(cc==count_scan-1)
                    {
                        n_topic[count_scan-1]=n1;
                        break;
                    }
                }
            }

        }



    printf("\n");
    fclose(f_A_t);

    FILE *topic;
    topic=fopen(struct_topic[n1-96].t,"r");
    if(topic==NULL)
    {
        printf("can not read topic \n");
        return -1;
    }
    int i2=0;
    int finish2=0;
    while(1)
    {
        if(finish2==1)
            break;

        int i=0;
        char c;
        while(1)
        {
            c=getc(topic);
            // printf("%c\n",c);
            if(c==EOF)
            {
                struct_in_topic[i2].t[i]='\0';
                i2++;
                finish2=1;
                shomarande_topic=i2;
                shomarande_topic_save=i2;


                break;
            }
            if(c==' ')
            {
                struct_in_topic[i2].t[i]='\0';
                break;
            }
            struct_in_topic[i2].t[i]=c;
            //printf("%c\n",struct_in_topic[i2].t[i]);
            i++;
        }
        i2++;
    }
    fclose(topic);
}
struct node
{
    char info[50];
    struct node *next;
};

struct node * create_node(char *a)
{
    struct node * nn;
    nn = (struct node *) malloc(sizeof(struct node));
    int i;
    for(i=0; i<=strlen(a); i++)
    {
        nn->info[i] = a[i];
    }
    nn->next = NULL;
    return nn;
}


void add_end(struct node *list, struct node * new_node)
{
    struct node *current;
    for(current = list; current-> next != NULL; current = current->next);
    current->next = new_node;
    new_node->next = NULL;
}
add_node(struct node* node_topic)
{
    int i;
    for(i=1; i<shomarande_topic_save; i++)
    {
        /*  if(shomarande_topic_save==1)
              break;*/
        struct  node* new_node;
        new_node=create_node(struct_in_topic[i].t);
        add_end(node_topic,new_node);
    }

}
/*void Print (struct node *list)
{

    struct node* current=list;
    if(current==NULL)
        printf("ERROR");
    while(current != NULL)
    {
        int i;
        printf("%s",current->info);
        current=current->next;
    }
}*/
delete_node(struct node* node_qabli,struct node* node,int d)
{
    struct node* current;
    struct node* current1;

    current=node_qabli;
    current1=node;
    if(d==1)
    {
        current=current1;
        current=NULL;
    }

    if(current1->next==NULL)
    {
        free(current->next);
        current->next=NULL;
    }
    else
    {
        current->next = current->next->next;
        free(current1);
        current1=NULL;
    }


}

random_node(struct node* node_topic)
{
    struct node* current;
    struct node* tmp;

    current = node_topic;
    // tmp=current;

    time_t t=time(NULL);
    int random;
    srand(t);
    //printf("%d",shomarande_topic_save);

    random=rand()%shomarande_topic;
    shomarande_topic--;

    // printf("%d ",random);
    int j;


    if(random==0)
    {

        show_node(current);

        if(current->next==NULL)
        {

            free(current);
            current=NULL;

        }
        else
        {
            int i;
            for(i=0; i<strlen(current->next->info); i++)
            {
                current->info[i]=current->next->info[i];
            }
            current->info[i]='\0';
            delete_node(current,current->next,0);
        }

    }
    else
    {
        int i;
        for(i=0; i<shomarande_topic; i++)
        {
            if(i==random-1)
            {
                show_node(current->next);
                delete_node(current,current->next,0);
                break;
            }
            current=current->next;
        }
    }
    // Print(node_topic);
    //printf("\n");
}
int s=0;
print_adamak (int wrong)
{
    char b=176;
    char a=178,a1=205,a2=186;

    if (wrong==5)
        printf("       Bye Bye !\n");

    if(wrong==0||wrong==1||wrong==2||wrong==3||wrong==4)
    {
        change_color(6);
        printf("          %c%c%c%c%c%c\n",a,a,a,a,a,a,a,a);
        printf("         %c%c%c%c%c%c%c%c\n",a,a,a,a,a,a,a,a);
        change_color(15);
        printf("        q%c %c  %c %cp\n",a2,233,233,a2);
    }
    if(wrong==0||wrong==1||wrong==2||wrong==3)
    {
        printf("         %c  __  %c\n",a2,a2);
        printf("         %c%c%c%c%c%c%c%c\n",200,a1,a1,187,201,a1,a1,188);
        printf("     /%c%c%c%c%c%c%c%c%c%c%c%c%c%c\\\n",a1,a1,a1,a1,a1,a1,188,200,a1,a1,a1,a1,a1,a1);
        printf("    /       o        \\\n");
    }
    if(wrong==0||wrong==1||wrong==2)
    {
        printf("   /  /%c    o     %c\\\  \\\n",a2,a2);

        printf("  /  / %c    o     %c \\\  \\\n",a2,a2);
        printf("    /  %c    o     %c  \\\  \n",a2,a2);
    }
    if(wrong==0||wrong==1)
    {
        printf("       %c    o     %c    \n",a2,a2);
        printf("       %c%c%c%c%c%c%c%c%c%c%c%c\n",204,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,185);
        printf("       %c   %c%c%c%c   %c\n",a2,201,a1,a1,187,a2);
    }

    if(wrong==0)
    {
        printf("       %c   %c  %c   %c\n",a2,a2,a2,a2);
        printf("       %c   %c  %c   %c\n",a2,a2,a2,a2);
        printf("       %c   %c  %c   %c\n",a2,a2,a2,a2);
    }
    change_color(15);

    change_color(9);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a);
    change_color(15);
}
show_node(struct node* current)
{

    struct node* word;
    word=current;

    //  printf("%s\n",word);
    int i;
    char A[strlen(word)];
    int wrong=0;
    print_adamak(wrong);
    printf("\n");


    for(i=0; i<strlen(word); i++)
    {
        A[i]='_';
        printf("%c ",A[i]);
    }
    A[i]='\0';
    printf("\n");

    char x;
    int j;
    int length=0;
    int k=0;
    char characters[200];
    int finish=0;

    while(1)
    {
        int  correct=0;
        change_color(8);
        printf("\nguess this word\nEnter a character : ");
        change_color(15);


        printf("\n");
        scanf(" %c",&x);
        if(x=='Q')
        {
            end=1;
            return;
        }
        characters[k]=x;
        printf("\n");
        int k1;
        int count=0;
        for(k1=k-1; k1>=0; k1--)
        {
            if(characters[k1]==x)
            {
                printf("This Character Entered Before \n ");
                count=1;
                break;
            }
        }
        k++;
        if(count==0)
        {
            for(j=0; j<strlen(word); j++)
            {
                if(word->info[j]==x)
                    correct=1;
            }

            if(correct==1)
            {
                change_color(10);
                printf("correct :) (%d/5)\n",5-wrong);
                change_color(15);
                for(i=0; i<strlen(word); i++)
                {
                    if(word->info[i]==x)
                    {
                        A[i]=x;
                        length++;
                    }
                }
                for(i=0; i<strlen(word); i++)
                {
                    if(length==strlen(word))
                    {

                        // SCORES[s]=3*(strlen(word)-wrong);
                        s++;
                        score=score+3*(strlen(word)-wrong);
                        change_color(10);
                        printf("bravpOoOo your guess is True\n");
                        printf("that word were ");
                        change_color(14);
                        printf("'%s'\n",word->info);
                        change_color(15);
                        finish=1;
                        // printf("score this topic until now : %d\n",score);
                        break;
                    }
                    printf("%c ",A[i]);
                }
                if(finish==1)
                    break;
            }

            else
            {
                wrong++;
                change_color(12);
                printf("wrong!(%d/5)\n\n",5-wrong);
                change_color(15);
                print_adamak(wrong);
            }
            if(wrong==5)
            {
                change_color(12);
                printf("ohh!!!you could not guess true :(\n");
                printf("that word were ");
                change_color(14);
                printf("'%s'\n",word->info);
                change_color(15);
                //   printf("score this word : 0 \n");
                //   printf("score this topic until now : %d\n",score);
                break;
            }

        }
    }
}
load_function()
{
    int load_score;
    char load_name[100]= {'s','a','v','e','/'};
    int n = 5;
    int i=0;
    char ch;
    while(1)
    {
        load_name[n]=name[i];
        // printf("%s",name);
        n++;
        i++;
        if(name[i]=='\0')
        {
            load_name[n]='.';
            n++;
            load_name[n]='b';
            n++;
            load_name[n]='i';
            n++;
            load_name[n]='n';
            n++;
            break;
        }
    }
    load_name[n] = '\0';

    FILE *fload;
    fload=fopen(load_name,"rb");
    if(fload==NULL)
    {
        change_color(12);
        printf("there are not save with this name \n");
        change_color(15);
        end=1;
        return;

    }
    int ss=0;
    int j=0,k=0;
    while(1)
    {
        char ch;
        ch=ss+97;
        if(fread(&load_score, sizeof(int), 1, fload)<1)
            break;
        load_struct[ss].SCORE=load_score;
        /*  while(1)
          {
              printf("%c",struct_topic[j].t[k]);
              k++;
              if(struct_topic[j].t[k]=='.')
                  break;
          }*/
        j++;
        if(see==1)
            printf("your best score in topic (%c) = %d \n",ch,load_struct[ss].SCORE);
        ss++;
    }
}
//save ******** ***** ********* ********* *********** *********** *********
save_function()
{
    int load_tmp;
    char save_name[100]= {'s','a','v','e','/'};
    int n = 5;
    int i=0;
    char ch;
    while(1)
    {
        save_name[n]=name[i];
        // printf("%s",name);
        n++;
        i++;
        if(name[i]=='\0')
        {
            save_name[n]='.';
            n++;
            save_name[n]='b';
            n++;
            save_name[n]='i';
            n++;
            save_name[n]='n';
            n++;
            break;
        }
    }
    save_name[n] = '\0';
    if(load==1)
    {
        // printf("midonm load kardiiii\n");
        FILE *fsave;
        fsave=fopen(save_name,"rb+");
        if(fsave==NULL)
        {
            printf("can not read this file");
            return 0;
        }
        int ss;
        for(ss=0; ss<shomarande; ss++)
        {
            fseek(fsave, ss * sizeof(fsave), SEEK_SET);
            if(load_struct[ss].SCORE<save[ss].SCORE)
            {
                fwrite(&save[ss].SCORE,sizeof(save[ss].SCORE),1,fsave);
            }
        }
        fclose(fsave);
    }
    else
    {
        FILE *fsave;
        fsave=fopen(save_name,"wb");
        if(fsave==NULL)
        {
            printf("can not read this file");
            freopen(save_name,"wb",fsave);
        }
        if(fsave==NULL)
        {
            printf("can not read this file");
            return 0;
        }
        int ss;
        for(ss=0; ss<shomarande; ss++)
        {
            fwrite(&save[ss].SCORE,sizeof(save[ss].SCORE),1,fsave);
        }
        fclose(fsave);
    }

    /*   FILE* ten_best;
       ten_best=fopen("save/ten_best.bin","rb+");
       if(ten_best==NULL)
       {
           freopen("save/ten_best.bin","rb+",ten_best);
       }
    if(ten_best==NULL)
    {
       printf("can not creat and read ten_best \n");
       return 0;
    }
       int ten_score;
       int j;
           for(j=0; j<10; j++)
           {
               fseek(ten_best, j * sizeof(int), SEEK_SET);
               if(fread(&ten_best, sizeof(int), 1, ten_score)<1);
               {
               fwrite(&ten_score,sizeof(ten_score),1,sum_score);
               break;
               }
               if(sum_score>ten_score)
               {
                   fwrite(&ten_score,sizeof(ten_score),1,sum_score);
                   break;
               }
           }
*/
    }

    add_new_topic()
    {
        char name_new_topic[100];
        name_new_topic[0]='t';
        name_new_topic[1]='o';
        name_new_topic[2]='p';
        name_new_topic[3]='i';
        name_new_topic[4]='c';
        name_new_topic[5]='s';
        name_new_topic[6]='/';
        change_color(8);
        printf("please Enter the name of the topic that you want add : ");
        change_color(15);
        char ch;
        int i=7;
        ch=getchar();
        while(1)
        {
            ch=getchar();
            if(ch=='\n')
                break;
            name_new_topic[i]=ch;
            i++;
        }
        name_new_topic[i]='.';
        name_new_topic[i+1]='t';
        name_new_topic[i+2]='x';
        name_new_topic[i+3]='t';
        name_new_topic[i+4]='\0';
        FILE* fadd_topic;
        fadd_topic=fopen(name_new_topic,"w");
        if(fadd_topic==NULL)
        {
            freopen(name_new_topic,"w",fadd_topic);
        }
        /*   if(fadd_topic==NULL)
           {
               printf("bazam ridi\n");
                return 0;
           }*/
        char finish[2];
        finish[0]='E';
        finish[1]='O';
        finish[2]='F';
        change_color(8);
        printf("Enter words :\n");
        printf("(if you don't want to continue enter '0' end of word)\n");
        change_color(15);

        while(1)
        {
            ch=getchar();
            if(ch=='\n')
                ch=' ';
            if(ch=='0')
            {
                break;
            }
            fputc(ch,fadd_topic);
        }
        fclose(fadd_topic);

        FILE *f_A_t;
        f_A_t=fopen("AVAILABLE_TOPICS.txt","a+");
        if(f_A_t==NULL)
        {
            printf("can not read available topics \n");
            return -1;
        }
        int j;
        fputc('\n',f_A_t);
        for(j=7; j<=i+3; j++)
        {
            fputc(name_new_topic[j],f_A_t);
        }
        fclose(f_A_t);
        /* while(1)
         {
             int c;
             c=fgetc(fadd_topic);
             if(c==EOF)
             {
                 fputc('\n');
                 for(j=7;j<=i;i++)
                 {
                     fputc()
                 }
             }
         }*/

    }
    int main()
    {
        int n=0;
        char ch;
        change_color(14);
        printf("Hello!!\n");
        change_color(8);
        printf("please Enter your name :\n");
        change_color(15);
        while(1)
        {
            ch=getchar();
            if (ch=='\n')
                break;
            name[n]=ch;
            n++;
        }
        name[n]='\0';
        change_color(14);
        printf("Welcome %s ;)\n",name);
        int start=0;
        change_color(8);
        printf("[1] New game\n");
        printf("[2] Load game\n");
        printf("[3] add a new topic\n");
        change_color(15);
        while(1)
        {
            scanf("%d",&start);
            if(start==1||start==2||start==3)
                break;
            if(start!=1&&start!=2&&start!=3)
            {
                change_color(12);
                printf("Error!! enter 1 or 2 or 3 \n ");
                change_color(15);
            }
        }

        if(start==3)
        {
            add_new_topic();
        }
        if(start==2)
        {
            load_function();
            if(end==1)
                return;
            change_color(14);
            printf("Game loaded !!\n");
            change_color(8);

            char see_ch;
            printf("do yo want to see your best scores? (Y/N)\n");
            change_color(15);

            scanf(" %c",&see_ch);
            if(see_ch!='Y'&&see_ch!='N')
            {
                while(1)
                {
                    change_color(12);
                    printf("what??\nplease enter 'Y' or 'N' :|\n");
                    change_color(15);

                    scanf(" %c",&see_ch);
                    if(see_ch=='Y'||see_ch=='N')
                        break;
                }
            }
            if(see_ch=='Y')
                see=1;
            load=1;
            load_function();
        }

        if(start==1)
        {
            change_color(14);
            printf("Game started !!!\n");
            change_color(15);
        }

        struct node* node_topic=NULL;
        open_topics();

        int SCORES[shomarande-1];
        int i,k;
        int s=0;
        for(k=0; k<shomarande; k++)
        {
            if(end==1)
                break;
            if(k>0)
            {
                node_topic=NULL;
                //  printf("node topic = %s \n",node_topic);
            }
            if(k>0)
                open_topics();
            //  printf("x %s x",struct_in_topic[1].t);
            node_topic=create_node(struct_in_topic[0].t);
            add_node(node_topic);
            // Print(node_topic);
            printf("\n");
            if(end==1)
                break;

            for(i=0; i<shomarande_topic_save; i++)
            {
                //    Print(node_topic);
                printf("\n");

                time_t t1,t2;
                printf("\n");
                if(i==0)
                    t1=time(NULL);

                random_node(node_topic);
                if(end==1)
                    break;
                //printf(" \n%s\n",node_topic);
                if(i==shomarande_topic_save-1)
                {
                    t2=time(NULL);
                    score=(score*100/(t2-t1));
                    printf("your score in this topic : %d  \n",score);
                    save[n1-97].SCORE=score;
                    score=0;
                }
            }
            if(k==shomarande-1)
                break;
            if(end==1)
                break;
            char Continue;
            change_color(8);
            printf("do yo want to continue this game ? (Y/N) \n");
            change_color(15);

            scanf(" %c",&Continue);
            if(Continue!='Y'&&Continue!='N')
            {
                while(1)
                {
                    change_color(12);
                    printf("what??\nplease enter 'Y' or 'N' :|\n");
                    change_color(15);

                    scanf(" %c",&Continue);
                    if(Continue=='Y'||Continue=='N')
                        break;
                }
            }
            if(Continue=='N')
                break;
        }
        //save game

        int ii;
        for(ii=0; ii<shomarande; ii++)
        {
            sum_score+=save[ii].SCORE;
        }
//printf("sum = %d",sum_score);



        char if_save;
        change_color(8);
        printf("Do you want to save? (Y/N)\n");
        change_color(15);

        scanf(" %c",&if_save);
        if(if_save!='Y'&&if_save!='N')
        {
            while(1)
            {
                change_color(12);
                printf("what??\nplease enter 'Y' or 'N' :|\n");
                change_color(15);

                scanf(" %c",&if_save);
                if(if_save=='Y'||if_save=='N')
                    break;
            }
        }
        if(if_save=='Y')
        save_function();


        change_color(14);
        printf("Bye Bye !!\n");
        change_color(15);

        return 0;
    }
