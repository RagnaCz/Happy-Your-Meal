#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define enter 13
#define space 32
#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define bullet 3
#define del 8


char kind[3][12] = {"Main dishes","Desserts","Drinks"};
char icon[3]={'A','B','C'};
int tag_line[50] = {0};
int first_line = 0,line_show;
char tag[3][50][21];
int Aline = 0;
int N_tag[3]={0,0,0};
int N_menu[3]={0,0,0};
int type,page=0;
char select[100];
int tag_count[100]={0};
char selected_menu[100][100];
char selected_menu2[100][100];
int m=0,p=0,o=0;
int i,j,k,l,cnt, Select, menu_N;
int topic=-1;

struct{
    char name[31];
    char description[301];
    char tags[15][21];
}menu[3][100];
///////////////////
int Data_import(){
    int mo=0,check=0,t;
    i=k=0;
    FILE *fp;
    fp = fopen("Menu.txt","r");
    fscanf(fp,"%d %d %d",&N_tag[0],&N_tag[1],&N_tag[2]);
    fscanf(fp,"%d %d %d",&N_menu[0],&N_menu[1],&N_menu[2]);
    do{
        char str[1000];
        fscanf(fp,"%s",str);
        const char s[2] = "|";
        char *token;
        token = strtok(str,s);
        while( token != NULL ) {
            strcpy(tag[k][i++],token);
            token = strtok(NULL,s);
        }
        k++;
        i=0;
    }while(k!=3);
    for(i=0;i<3;i++){
        for(j=0;j<N_tag[i];j++){
            for(k=0;k<21;k++){
                if(tag[i][j][k]=='_')tag[i][j][k]=' ' ;
            }
        }
    }
    do{
        for(i=0;i<3;i++){
            for(j=0;j<N_menu[i];j++){
                char str2[1000];
                fscanf(fp,"\n%[^\n]",str2);
                const char s[2] = "|";
                char *token;
                token = strtok(str2,s);
                t=0;
                while( token != NULL ) {
                    if(check==0){
                        strcpy(menu[i][j].name,token);
                        check++;
                    }else{
                        strcpy(menu[i][j].tags[t++],token);
                    }
                    token = strtok(NULL,s);
                }check=0;
                fscanf(fp,"\n%[^\n]",str2);
                token = strtok(str2,s);
                while( token != NULL ){
                    strcpy(menu[i][j].description,token);
                    token = strtok(NULL,s);
                }
            }
        }
    }while(i!=3);
    fclose(fp);
    return 0;
}

int Data_store(){
    int mo=0,check=0,t;
    FILE *fp;
    fp = fopen("Menu.txt","w");
    fprintf(fp,"%d %d %d\n",N_tag[0],N_tag[1],N_tag[2]);
    fprintf(fp,"%d %d %d\n",N_menu[0],N_menu[1],N_menu[2]);
    for(i=0;i<3;i++){
        for(j=0;j<N_tag[i];j++){
            for(k=0;k<strlen(tag[i][j]);k++){
                if(tag[i][j][k]==' ')tag[i][j][k]='_';
            }
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<N_tag[i];j++){
            if(j!=N_tag[i]-1)fprintf(fp,"%s|",tag[i][j]);
            else fprintf(fp,"%s\n",tag[i][j]);
        }
    }
    fprintf(fp,"\n");
    for(i=0;i<3;i++){
        for(j=0;j<N_menu[i];j++){
            fprintf(fp,"%s|",menu[i][j].name);
            for(k=0;k<15;k++){
                if(k!=0&&menu[i][j].tags[k][0]!='\0')fprintf(fp,"|");
                fprintf(fp,"%s",menu[i][j].tags[k]);
            }
            fprintf(fp,"\n");
            fprintf(fp,"%s",menu[i][j].description);
            if(i==2&&j==N_menu[i]-1);
            else fprintf(fp,"\n");
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<N_tag[i];j++){
            for(k=0;k<strlen(tag[i][j]);k++){
                if(tag[i][j][k]=='_')tag[i][j][k]=' ';
            }
        }
    }
    fclose(fp);
    return 0;
}

//1 menu = {Name(0), Kind(1), Tags(2-16), Description(17)}
int pages(){
    int a,i;
    if(topic==-1)
        return 'z';
    switch(page)
    {
    case 0:
    a = start_search();
    break;
    case 1:
    mainmenu();
    break;
    case 2:
    suggested_maindishes();
    break;
    case 3:
    show();
    break;
    }
    return a;
}

char menu_search(){
    //main of search menu
    char a;
    int i,chr;
    //main menu ABC
    do{
        system("cls");
        printf("\n\n\n\n\n\n\t\t\t%c",201);
        for(i=0;i<32;i++)
        printf("%c",205);
        printf("%c\n",187);

        printf("\t\t\t%c  Select your perfered cuisine  %c     Press [i] to get info\n\t\t\t%c",186,186,200);
        for(i=0;i<32;i++)
        printf("%c",205);
        printf("%c",188);
        for(i=0; i<3; i++)
        {
            printf("\n\n\t\t\t %c  %-15s",16,kind[i]);
            if(first_line%3==i)printf("<<<");
        }
        chr = getch();
        if(chr==up){if(first_line==0)first_line=2; else first_line--;}
        else if(chr==down)first_line++;
        if(chr==enter)if(first_line%3==0)return 'a';
        else if(first_line%3==1)return 'b';
        else if(first_line%3==2)return 'c';
        if(chr==esc)return 'z';
        if(chr=='i'||chr=='I')return 'i';
    }while(chr!=enter||chr=='i'||chr=='I');
}
//start search
int start_search(){
    int a=1,i;
    char select = menu_search();
    switch(select)
    {
    case 'a':
    case 'A':
        system("cls");
        type = 0;Aline=0;
        page++;
        for(i=0;i<50;i++)
        tag_line[i]=0;
        mainmenu();
        break;
    case 'i':
        system("cls");
        info_1();
        break;
    case 'b':
    case 'B':
        system("cls");
        type = 1;Aline=0;
        page++;
        for(i=0;i<50;i++)
        tag_line[i]=0;
        mainmenu();
        break;
    case 'c':
    case 'C':
        system("cls");
        type = 2;Aline=0;
        page++;
        for(i=0;i<50;i++)
        tag_line[i]=0;
        mainmenu();
        break;
    case 'z':
        topic = -1;
        break;
    }
    return a;
}

int mainmenu(){
    int i,j=0,k=0,lr=0,side = 0;
    int chr,countno=0,check;
    for(i=0;i<100;i++)
        for(j=0;j<100;j++){
            selected_menu[i][j]='\0';
        }
    do
    {
        system("cls");
        printf("\n\n\n\n\n\t\t\t%c",201);
        for(i=0;i<8+strlen(kind[type]);i++) printf("%c",205);
        printf("%c\n\t\t\t%c  <%c> %s  %c     Press [i] to get info\n\t\t\t%c",187,186,icon[type],kind[type],186,200);
        for(i=0;i<8+strlen(kind[type]);i++) printf("%c",205);printf("%c\n\n\t\t\t",188);
        printf("   Material Tag :\n\n");

        for(i=0; i<N_tag[type]; i++)
        {
            if(i%2==0) printf("\t\t\t\t");
            if(tag_line[i]==1)
            printf("[%c] %s  ",251,tag[type][i]);
            else if(tag_line[i]==0)printf("[ ] %s  ",tag[type][i]);
            else if(tag_line[i]==2)printf("[X] %s  ",tag[type][i]);
            if(Aline%N_tag[type]==i)printf(" <<<");
            else printf("    ");
            if((i+1)%2!=0)for(j=0;j<30-strlen(tag[type][i]);j++) printf(" ");
            else printf("\n\n");
        }
        check = 0;
        if(N_tag[type]%2==1) printf("\n\n");
        for(i=0;i<50;i++)
            if(tag_line[i]==1)
                check++;
        if(countno==1) printf("\n\t\tPlease select tag menu !!");
        chr=getch();
        if(chr==up){
            if(N_tag[type]%2==0)
            {
                if(Aline%N_tag[type]==0){Aline=N_tag[type]-2;}
                else if(Aline%N_tag[type]==1){Aline=N_tag[type]-1;}
                else Aline=Aline-2;
            } else if(N_tag[type]%2==1){
                if(Aline%N_tag[type]==0){Aline=N_tag[type]-1;}
                else if(Aline%N_tag[type]==1){Aline=N_tag[type]-2;}
                else Aline=Aline-2;
            }
        }
        else if(chr==down){
            if(N_tag[type]%2==0)
            {
                if(Aline==N_tag[type]-2){Aline = 0;}
                else if(Aline==N_tag[type]-1){Aline = 1;}
                else Aline=Aline+2;
            }else if(N_tag[type]%2==1){
                if(Aline==N_tag[type]-1){Aline=0;}
                else if(Aline==N_tag[type]-2){Aline=1;}
                else Aline=Aline+2;
            }
        }
        else if(chr==left){
            if(Aline==N_tag[type]-1&&N_tag[type]%2==1);
            else if(Aline%2==0)Aline++;
            else Aline--;
        }
        else if(chr==right)
        {
            if(Aline==N_tag[type]-1&&N_tag[type]%2==1);
            else if(Aline%2==0)Aline++;
            else Aline--;
        }

        else if(chr=='a'||chr=='A')
        {
            if((tag_line[Aline%N_tag[type]]==0)||(tag_line[Aline%N_tag[type]]==2))
            {
                tag_line[Aline%N_tag[type]]=1;
            }else if(tag_line[Aline%N_tag[type]]==1)
            {
                tag_line[Aline%N_tag[type]]=0;
            }
        }

        else if(chr=='s'||chr=='S')
        {
            if((tag_line[Aline%N_tag[type]]==0)||(tag_line[Aline%N_tag[type]]==1))
            {
                tag_line[Aline%N_tag[type]]=2;
            }else if(tag_line[Aline%N_tag[type]]==2)
            {
                tag_line[Aline%N_tag[type]]=0;
            }
        }

        else if(chr==enter){
            if(check>=1){
                countno=0;
                page=2;
                break;
            }else countno=1;
        }
        else if(chr==esc)page=0;
        else if(chr=='i'||chr=='I')info_2();
    }
    while(chr!=esc);
    system("cls");
}

void suggested_maindishes(){
    int i,j,count=0,k,chr,l,n=0,ti,a=0,checke=1,recommend,mp,pos[100],counts,countss=0,q,tempt=0,line=0;
    char ts[100];
    recommend = 0;
    //show menu
    for(i=0;i<100;i++)
        for(j=0;j<100;j++){
            selected_menu[i][j]=0;
            tag_count[i]=0;
        }
    m=0;line=0;
    for(i=0,m=0;i<N_tag[type];i++)
    {
        if(tag_line[i]>=1) //check main_tag
        {
           for(k=0;k<N_menu[type];k++) //ลำดับเมนู
            {
                for(j=0;j<15;j++)
                    if(strcmp(tag[type][i],menu[type][k].tags[j])==0)
                        {
                        for(l=0,count=0;l<m;l++)
                        {
                            if(strcmp(selected_menu[l],menu[type][k].name)==0)
                            {
                                count++;
                                tag_count[l]+=1;
                            }

                        }
                        if(count==0){
                            strcpy(selected_menu[m],menu[type][k].name);
                            // tag_count[m]=1;
                            m++;
                        }

                    }
                }
        }
    }

    for (i=m-2;i>=0;i--)
    {
        for(j=m-1;j>=1;j--)
        if (tag_count[i]<tag_count[j])
            {
                ti = tag_count[i];
                tag_count[i] = tag_count[j];
                tag_count[j] = ti;
                strcpy(ts,selected_menu[i]);
                strcpy(selected_menu[i],selected_menu[j]);
                strcpy(selected_menu[j],ts);
            }
    }

    for(i=0,mp=0;i<=N_tag[type];i++)
    {
        if(tag_line[i]==2)
        {
            tempt=1;
            for(k=0;k<=m;k++)
            {
                for(l=0;l<=N_menu[type];l++){
                    if(strcmp(selected_menu[k],menu[type][l].name)==0)
                    {
                        for(j=0;j<15;j++)
                        {
                            if(strcmp(tag[type][i],menu[type][l].tags[j])==0)
                            {
                                strcpy(selected_menu[k],"none");
                                counts=0;
                            }
                        }
                    }
                }
            }
        }
    }

    for (i=m-2;i>=0;i--)
    {
        for(j=m-1;j>=1;j--)
        if (strcmp(selected_menu[i],"none")==0)
            {
                strcpy(ts,selected_menu[i]);
                strcpy(selected_menu[i],selected_menu[j]);
                strcpy(selected_menu[j],ts);
            }
    }
    for(i=0,countss=0;i<=m;i++)
    {
        if(strcmp(selected_menu[i],"none")==0)
        {
            countss++;
        }
    }
    m=m-countss;

    p=0;
    q=0;
    for(i=0;i<N_tag[type];i++)if(tag_line[i]==1)p++;
    for(i=0;i<N_tag[type];i++)if(tag_line[i]==2)q++;

    if(tempt==1)recommend=-1;
    else recommend = tag_count[0]-q;
    tempt = 0;

    do{
        o=0;
        system("cls");
        //show tag
        printf("\n\n\n\n\n\t\t\t%c",201);
        for(i=0;i<=strlen(kind[type])+7;i++)printf("%c",205);
        printf("%c\n\t\t\t%c  <%c> %s  %c     [ %d of %d menu ]     Press [i] to get info\n\t\t\t%c",187,186,icon[type],kind[type],186,m,N_menu[type],200);
        for(i=0;i<=strlen(kind[type])+7;i++)printf("%c",205);
        printf("%c\n\n",188);
        printf("\t\t\t    Tag : ");
        for(i=0;i<N_tag[type];i++)
            if(tag_line[i]==1)
            {
                if(o!=p-1){
                    printf("%s, ",tag[type][i]);
                    o++;
                }else printf("%s ",tag[type][i]);
            }
        o=0;
        printf("\n\n\t\t\t    Deselected Tag : ");
        for(i=0;i<N_tag[type];i++)
            if(tag_line[i]==2)
            {
                if(o!=q-1){
                    printf("%s, ",tag[type][i]);
                    o++;
                }else printf("%s ",tag[type][i]);
            }
        if(q==0)printf("-");

        printf("\n\n\t\t\t    Suggested menu : ");

        printf("Page %d of %d",((a)/7)+1,((m-1)/7)+1);

        printf("\n");

        if(m!=0){
            if(m<=7&&m>0){
                for(i=0; i<m; i++)
                {
                        printf("\n\t\t\t\t  %2d.)  %-30s",i+1,selected_menu[i]);
                        if(line%m==i)printf("<<<");
                        if(tag_count[i]==recommend&&line%m==i&&tag_count[0]!=0)printf("    Recommend !!");
                        else if(tag_count[i]==recommend&&tag_count[0]!=0)printf("       Recommend !!");
                        printf("\n");
                }
            }else{
                for(i=0+a;i<7+a;i++)
                {
                    if(i+1<=m){
                    if(line<7){
                        printf("\n\t\t\t\t  %2d.)  %-30s",i+1,selected_menu[i]);
                        if(line==i)printf("<<<");
                        if(tag_count[i]==recommend&&line%m==i&&tag_count[0]!=0)printf("    Recommend !!");
                        else if(tag_count[i]==recommend&&tag_count[0]!=0)printf("       Recommend !!");
                    }
                    else{
                        printf("\n\t\t\t\t  %2d.)  %-30s",i+1,selected_menu[i]);
                        if(line==i)printf("<<<");
                        if(tag_count[i]==recommend&&line%m==i&&tag_count[0]!=0)printf("    Recommend !!");
                        else if(tag_count[i]==recommend&&tag_count[0]!=0)printf("       Recommend !!");
                    }
                    printf("\n");}
                }
            }
        }else{
            printf("\n\t\t\t    There is no menu here! please press any key to reselect tags.");
        }
        chr=getch();
        if(m==0){page=1;break;}
        else if(chr==up)
        {
            if(a==(m/7)*7)
            {
                if(line==0+a)
                {
                    line=((m/7)*7)+((m-1)%7);
                }else line--;
            }
            else if(line==0+a)
            {
                line=7+a-1;
            }else{line--;}
        }else if(chr==down)
        {
            if(a==(m/7)*7)
            {
                if(line==m-1)
                {
                    line=(m/7)*7;
                }else line++;
            }
            else if(line==7+a-1)
            {
                line=0+a;
            }else{line++;}
        }
        else if(chr==left)
        {
            if(a==0)
            {
                if(m%7==0)
                    a=(((m/7))*7)-7;
                else a=(((m/7))*7);
                line=0+a;
            }else{
                a=a-7;
                line=0+a;
            }
        }else if(chr==right)
        {
            if(a==(((m/7))*7)||a==m-7)
            {
                a=0;
                line=0+a;
            }else{
                a=a+7;
                line=0+a;
            }
        }
        else if(chr==enter)page=3;
        else if(chr==esc)page=1;
        else if(chr=='i'||chr=='I')info_3();
        strcpy(select,selected_menu[line%m]);
    }while(chr!=enter&&chr!=esc&&m!=0);
    chr = '\0';
    line_show=0;
    fflush(stdin);
    system("cls");
}

void show(){
    char chr;
    int i,j,n,count=0,GTX=0;
    char menu_show[3][50]={"Cusine page","Tag page","Main page"};
    GTX=0;
    o=0;
    for(i=0;i<N_menu[type];i++)
        if(strcmp(select,menu[type][i].name)==0)n=i;

    for(i=0;i<15;i++)
    {
        if(strcmp(menu[type][n].tags[i],"none")==0)
        {
            GTX++;
        }
    }

    do{

    printf("\n\n\n\n\n\n\t\t\t%c",201);
    for(i=0;i<strlen(select)+4;i++)
        printf("%c",205);
    printf("%c\n\t\t\t%c  %s  %c     Press [i] to get info",187,186,select,186);
    printf("\n\t\t\t%c",200);
    for(i=0;i<strlen(select)+4;i++)
        printf("%c",205);
    printf("%c",188);
    printf("\n\n\t\t\t    Cuisine : %s",kind[type]);
    printf("\n\n\t\t\t    Tag     : "); for(i=0;i<15-GTX;i++){
        if(i!=0&&menu[type][n].tags[i][0]!='\0')printf(", ");
        printf("%s",menu[type][n].tags[i]);
    }
    printf("\n\n\t\t\t    Detail  : ");
    for(i=0;i<strlen(menu[type][n].description);i++)
    {
        if(count<=70){
            printf("%c",menu[type][n].description[i]);
            count++;
        }else if(menu[type][n].description[i]==' '){
            printf("\n\n\t\t\t              ");
            count = 0;
        }else printf("%c",menu[type][n].description[i]);
    }
    printf("\n\n\t\t\t");
    for(i=0;i<=96;i++)
    printf("%c",205);

    printf("\n\n\t\t\t    Go to   : ");
    for(i=0;i<3;i++)
    {
        if(line_show%3 == i)printf("[ ");else printf("  ");
        printf("%s",menu_show[i]);
        if(line_show%3 == i)printf(" ]");else printf("  ");
    }


    chr=getch();
    if(chr==esc)page=2;
    else if(chr=='i'||chr=='I')info_4();
    else if(chr==left){if(line_show==0)line_show=2;else line_show--;}
    else if(chr==right){if(line_show==2)line_show=0;else line_show++;}
    else if(chr==enter){if(line_show==0)page=0;else if(line_show==1)page=1;else if(line_show==2){topic=-1;page=0;}}
    }while(chr!=esc&&chr=='i'&&chr=='I'&&chr!=enter);
    system("cls");
}

void info_1()
{
    int chr,c = 0;
    printf("\n\n\n\n\n\n\t\t\tTutorial :");
    printf("\n\n\t\t\t  1. Press %c or %c arrow to move up or down.",30,31);
    printf("\n\n\t\t\t  2. Press Enter to select.");
    printf("\n\n\t\t\tPress any key to continue. \n");
    do{
        chr = getch();
        if(1)c=1;
    }while(c!=1);
    c=0;
}

void info_2()
{
    system("cls");
    int chr,c;
    printf("\n\n\n\n\n\n\t\t\tTutorial :");
    printf("\n\n\t\t\t  1. Press %c or %c arrow to move up or down.",30,31);
    printf("\n\n\t\t\t  2. Press %c or %c arrow to move left or right.",17,16);
    printf("\n\n\t\t\t  3. Press a to select your prefered tag and press s to unselect tags.");
    printf("\n\n\t\t\t  4. Press Enter to search for menu.");
    printf("\n\n\t\t\t  5. Press Esc to go back.");
    printf("\n\n\t\t\tPress any key to continue.");
    do{
        chr = getch();
        if(1)c=1;
    }while(c!=1);
    c=0;
}

void info_3()
{
    system("cls");
    int chr,c;
    printf("\n\n\n\n\n\n\t\t\tTutorial :");
    printf("\n\n\t\t\t  1. Press %c or %c arrow to move up or down.",30,31);
    printf("\n\n\t\t\t  2. Press %c or %c arrow to change pages.",17,16);
    printf("\n\n\t\t\t  3. Press Enter to get info of your prefered menu.");
    printf("\n\n\t\t\t  4. Press Esc to go back.");
    printf("\n\n\t\t\tPress any key to continue.");
    do{
        chr = getch();
        if(1)c=1;
    }while(c!=1);
    c=0;
}

void info_4()
{
    system("cls");
    int chr,c;
    printf("\n\n\n\n\n\n\t\t\tTutorial :");
    printf("\n\n\t\t\t  1. Press Esc to go back.");
    printf("\n\n\t\t\t  2. Press %c or %c arrow to move left or right.",17,16);
    printf("\n\n\t\t\t  4. Press Enter to choose page.");
    printf("\n\n\t\t\tPress any key to continue.");
    do{
        chr = getch();
        if(1)c=1;
    }while(c!=1);
    c=0;
    page = 3;
    system("cls");
}

void red() {
  printf("\033[1;31m");
}

void green() {
  printf("\033[0;32m");
}

void reset() {
  printf("\033[0m");
}


int start(){
    char chr,linem=0;
    int i;
    for(i=0;i<60;i++)
    {
        printf("=");
    }

    do{
        system("cls");
        if(linem==0){
        printf("\n\t  ");

        for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
        for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }

        printf("\n");
        printf("\n\t            /######## /##   /##    /#####  /######  /##     /##            ");
        printf("\n\t           | ##_____/| ### | ##   |__  ## /##__  ##|  ##   /##/            ");
        printf("\n\t           | ##      | ####| ##      | ##| ##  \\ ## \\  ## /##/                          ");
        printf("\n\t           | #####   | ## ## ##      | ##| ##  | ##  \\  ####/              ");
        printf("\n\t           | ##__/   | ##  #### /##  | ##| ##  | ##   \\  ##/              ");
        printf("\n\t           | ##      | ##\\  ###| ##  | ##| ##  | ##    | ##                      ");
        printf("\n\t           | ########| ## \\  ##|  ######/|  ######/    | ##                    ");
        printf("\n\t           |________/|__/  \\__/ \\______/  \\______/     |__/      ");
        printf("\n\t                                                                           ");
        printf("\n\t            /##     /## /######  /##   /## /#######            ");
        printf("\n\t           |  ##   /##//##__  ##| ##  | ##| ##__  ##         _    ___                  _  ");
        printf("\n\t            \\  ## /##/| ##  \\ ##| ##  | ##| ##  \\ ##        / |  / __| ___ __ _ _ _ __| |_    _ __  ___ _ _ _  _  ");
        printf("\n\t             \\  ####/ | ##  | ##| ##  | ##| #######/        | |_ \\__ \\/ -_) _` | '_/ _| ' \\  | '  \\/ -_) ' \\ || |   ");
        printf("\n\t              \\  ##/  | ##  | ##| ##  | ##| ##__  ##        |_(_)|___/\\___\\__,_|_| \\__|_||_| |_|_|_\\___|_||_\\_,_|   ");
        printf("\n\t               | ##   | ##  | ##| ##  | ##| ##  \\ ##                   ");
        printf("\n\t               | ##   |  ######/|  ######/| ##  | ##                       ");
        printf("\n\t               |__/    \\______/  \\______/ |__/  |__/                              2. Management   ");
        printf("\n\t                                                                                  ");
        printf("\n\t            /##      /## /########  /######  /##             /##                   ");
        printf("\n\t           | ###    /###| ##_____/ /##__  ##| ##            | ##                  3. Credit ");
        printf("\n\t           | ####  /####| ##      | ##  \\ ##| ##            | ##                        ");
        printf("\n\t           | ## ##/## ##| #####   | ########| ##            | ##                ");
        printf("\n\t           | ##  ###| ##| ##__/   | ##__  ##| ##            |__/                  4. Exit  ");
        printf("\n\t           | ##\\  # | ##| ##      | ##  | ##| ##                             ");
        printf("\n\t           | ## \\/  | ##| ########| ##  | ##| ########       /##           ");
        printf("\n\t           |__/     |__/|________/|__/  |__/|________/      |__/      [i] Press %c or %c to move, Enter to select. ",30,31);
        printf("\n\n\t  ");

        for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        }


        if(linem==1){
        printf("\n\t  ");

                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }

        printf("\n");
        printf("\n\t            /######## /##   /##    /#####  /######  /##     /##            ");
        printf("\n\t           | ##_____/| ### | ##   |__  ## /##__  ##|  ##   /##/            ");
        printf("\n\t           | ##      | ####| ##      | ##| ##  \\ ## \\  ## /##/                          ");
        printf("\n\t           | #####   | ## ## ##      | ##| ##  | ##  \\  ####/              ");
        printf("\n\t           | ##__/   | ##  #### /##  | ##| ##  | ##   \\  ##/              ");
        printf("\n\t           | ##      | ##\\  ###| ##  | ##| ##  | ##    | ##                     ");
        printf("\n\t           | ########| ## \\  ##|  ######/|  ######/    | ##                ");
        printf("\n\t           |________/|__/  \\__/ \\______/  \\______/     |__/                ");
        printf("\n\t                                                                                  1. Search menu");
        printf("\n\t            /##     /## /######  /##   /## /#######                        ");
        printf("\n\t           |  ##   /##//##__  ##| ##  | ##| ##__  ##      ___    __  __                                       _");
        printf("\n\t            \\  ## /##/| ##  \\ ##| ##  | ##| ##  \\ ##     |_  )  |  \\/  |__ _ _ _  __ _ __ _ ___ _ __  ___ _ _| |_  ");
        printf("\n\t             \\  ####/ | ##  | ##| ##  | ##| #######/      / / _ | |\\/| / _` | ' \\/ _` / _` / -_) '  \\/ -_) ' \\  _|  ");
        printf("\n\t              \\  ##/  | ##  | ##| ##  | ##| ##__  ##     /___(_)|_|  |_\\__,_|_||_\\__,_\\__, \\___|_|_|_\\___|_||_\\__|  ");
        printf("\n\t               | ##   | ##  | ##| ##  | ##| ##  \\ ##                                    |___/        ");
        printf("\n\t               | ##   |  ######/|  ######/| ##  | ##                       ");
        printf("\n\t               |__/    \\______/  \\______/ |__/  |__/                              3. Credit ");
        printf("\n\t                                                                           ");
        printf("\n\t            /##      /## /########  /######  /##             /##              ");
        printf("\n\t           | ###    /###| ##_____/ /##__  ##| ##            | ##                  4. Exit");
        printf("\n\t           | ####  /####| ##      | ##  \\ ##| ##            | ##           ");
        printf("\n\t           | ## ##/## ##| #####   | ########| ##            | ##           ");
        printf("\n\t           | ##  ###| ##| ##__/   | ##__  ##| ##            |__/                       ");
        printf("\n\t           | ##\\  # | ##| ##      | ##  | ##| ##                           ");
        printf("\n\t           | ## \\/  | ##| ########| ##  | ##| ########       /##           ");
        printf("\n\t           |__/     |__/|________/|__/  |__/|________/      |__/      [i] Press %c or %c to move, Enter to select. ",30,31);
        printf("\n\n\t  ");

                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        }



        if(linem==2){
        printf("\n\t  ");

                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }

        printf("\n");
        printf("\n\t            /######## /##   /##    /#####  /######  /##     /##            ");
        printf("\n\t           | ##_____/| ### | ##   |__  ## /##__  ##|  ##   /##/            ");
        printf("\n\t           | ##      | ####| ##      | ##| ##  \\ ## \\  ## /##/                         ");
        printf("\n\t           | #####   | ## ## ##      | ##| ##  | ##  \\  ####/              ");
        printf("\n\t           | ##__/   | ##  #### /##  | ##| ##  | ##   \\  ##/              ");
        printf("\n\t           | ##      | ##\\  ###| ##  | ##| ##  | ##    | ##                       1. Search menu");
        printf("\n\t           | ########| ## \\  ##|  ######/|  ######/    | ##                ");
        printf("\n\t           |________/|__/  \\__/ \\______/  \\______/     |__/                ");
        printf("\n\t                                                                                  2. Management  ");
        printf("\n\t            /##     /## /######  /##   /## /#######                        ");
        printf("\n\t           |  ##   /##//##__  ##| ##  | ##| ##__  ##                   ____    ___            _ _ _ ");
        printf("\n\t            \\  ## /##/| ##  \\ ##| ##  | ##| ##  \\ ##                  |__ /   / __|_ _ ___ __| (_) |_  ");
        printf("\n\t             \\  ####/ | ##  | ##| ##  | ##| #######/                   |_ \\_ | (__| '_/ -_) _` | |  _|");
        printf("\n\t              \\  ##/  | ##  | ##| ##  | ##| ##__  ##                  |___(_) \\___|_| \\___\\__,_|_|\\__|");
        printf("\n\t               | ##   | ##  | ##| ##  | ##| ##  \\ ##                       ");
        printf("\n\t               | ##   |  ######/|  ######/| ##  | ##                       ");
        printf("\n\t               |__/    \\______/  \\______/ |__/  |__/                              4. Exit   ");
        printf("\n\t                                                                           ");
        printf("\n\t            /##      /## /########  /######  /##             /##              ");
        printf("\n\t           | ###    /###| ##_____/ /##__  ##| ##            | ##                ");
        printf("\n\t           | ####  /####| ##      | ##  \\ ##| ##            | ##           ");
        printf("\n\t           | ## ##/## ##| #####   | ########| ##            | ##                   ");
        printf("\n\t           | ##  ###| ##| ##__/   | ##__  ##| ##            |__/                        ");
        printf("\n\t           | ##\\  # | ##| ##      | ##  | ##| ##                           ");
        printf("\n\t           | ## \\/  | ##| ########| ##  | ##| ########       /##           ");
        printf("\n\t           |__/     |__/|________/|__/  |__/|________/      |__/      [i] Press %c or %c to move, Enter to select. ",30,31);
        printf("\n\n\t  ");

                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        }



        if(linem==3){
        printf("\n\t  ");

                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }

        printf("\n");
        printf("\n\t            /######## /##   /##    /#####  /######  /##     /##            ");
        printf("\n\t           | ##_____/| ### | ##   |__  ## /##__  ##|  ##   /##/            ");
        printf("\n\t           | ##      | ####| ##      | ##| ##  \\ ## \\  ## /##/                    1. Search menu ");
        printf("\n\t           | #####   | ## ## ##      | ##| ##  | ##  \\  ####/              ");
        printf("\n\t           | ##__/   | ##  #### /##  | ##| ##  | ##   \\  ##/              ");
        printf("\n\t           | ##      | ##\\  ###| ##  | ##| ##  | ##    | ##                       2. Management");
        printf("\n\t           | ########| ## \\  ##|  ######/|  ######/    | ##                ");
        printf("\n\t           |________/|__/  \\__/ \\______/  \\______/     |__/                ");
        printf("\n\t                                                                                  3. Credit ");
        printf("\n\t            /##     /## /######  /##   /## /#######                        ");
        printf("\n\t           |  ##   /##//##__  ##| ##  | ##| ##__  ##                        _ _    ___     _ _  ");
        printf("\n\t            \\  ## /##/| ##  \\ ##| ##  | ##| ##  \\ ##                       | | |  | __|_ _(_) |_     ");
        printf("\n\t             \\  ####/ | ##  | ##| ##  | ##| #######/                       |_  _| | _|\\ \\ / |  _|    ");
        printf("\n\t              \\  ##/  | ##  | ##| ##  | ##| ##__  ##                         |_(_)|___/_\\_\\_|\\__|    ");
        printf("\n\t               | ##   | ##  | ##| ##  | ##| ##  \\ ##                       ");
        printf("\n\t               | ##   |  ######/|  ######/| ##  | ##                       ");
        printf("\n\t               |__/    \\______/  \\______/ |__/  |__/                      ");
        printf("\n\t                                                                           ");
        printf("\n\t            /##      /## /########  /######  /##             /##           ");
        printf("\n\t           | ###    /###| ##_____/ /##__  ##| ##            | ##               ");
        printf("\n\t           | ####  /####| ##      | ##  \\ ##| ##            | ##           ");
        printf("\n\t           | ## ##/## ##| #####   | ########| ##            | ##           ");
        printf("\n\t           | ##  ###| ##| ##__/   | ##__  ##| ##            |__/                 ");
        printf("\n\t           | ##\\  # | ##| ##      | ##  | ##| ##                           ");
        printf("\n\t           | ## \\/  | ##| ########| ##  | ##| ########       /##           ");
        printf("\n\t           |__/     |__/|________/|__/  |__/|________/      |__/      [i] Press %c or %c to move, Enter to select. ",30,31);
        printf("\n\n\t  ");

                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        printf("\n\t  ");
                for(i=0;i<20;i++)
        {
            green();
            printf("^^");reset();
            red();
            printf("-");reset();
            printf("..");
            red();
            printf("-");reset();
        }
        }
    chr = getch();
    if(chr==up)
    {
        if(linem==0)linem=3; else linem--;
    }else if(chr==down){
        if(linem==3)linem=0; else linem++;
    }else if(chr==enter){
        topic=linem;
    }
    }while(chr!=enter);
}


int credit(){

    char chr=0;
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\t_  _ ____ _  _ ____    _  _ ____ ___ ____ ");
    printf("\n\t\t\t\t\t\t|\\ | |  | |\\ | | __    |\\ | |__|  |  |___    ");
    printf("\n\t\t\t\t\t\t| \\| |__| | \\| |__]    | \\| |  |  |  |___    ");

    printf("\n\n\t\t\t\t\t  ____ _  _ ___     ___ _  _ ____    ____ ____ _  _ ____");
    printf("\n\t\t\t\t\t  |__| |\\ | |  \\     |  |__| |___    | __ |__| |\\ | | __");
    printf("\n\t\t\t\t\t  |  | | \\| |__/     |  |  | |___    |__] |  | | \\| |__] ");

    printf("\n\n\n\t\t\t\t\t\t      EP: Adventure in Code::Blocks\n");

    printf("\n\n\t\t\t\t\t\t       6413220  Natedee Mueankrut");
    printf("\n\n\t\t\t\t\t\t        6413215  Tanawat Kanchan");
    printf("\n\n\t\t\t\t\t\t          6413106   Ploypailin");

    printf("\n\n\n\t\t\t\t\t\t      [i] Press any key to continue.");

    do{
        chr = getch();
        chr = 1;
        topic = -1;
    }while(chr!=1);


}

void edit_tag(){
    char name[21];
    char chr='\0';
    int n1, confirm_mode=0, line=0;
    strcpy(name,tag[type][menu_N]);
    n1=strlen(name);
    do{
        system("cls");
        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+strlen(tag[type][menu_N])+16;i++)printf("%c",205);
        printf("%c\n\t\t%c  Edit %s Tag : %s  %c",187,186,kind[type],tag[type][menu_N],186);
        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+strlen(tag[type][menu_N])+16;i++)printf("%c",205);

        printf("%c",188);
        if(chr==del&&n1>0)name[--n1]='\0';
        else if(!(n1==0&&chr==' ')&&chr!=del&&chr!='\0'){
            name[n1++]=chr;
            name[n1]='\0';
        }
        if(n1>20){n1=20;name[l]='\0';}
        printf("\n\n\t\t Current Name : %s",tag[type][menu_N]);
        printf("\n\n\t\t New Name : %s",name);

        chr=getch();
        if(chr==enter){
            if(n1<1)chr='\0';
            else {for(i=0;i<N_tag[type];i++){if(strcmp(name,tag[type][i])==0){chr='\0';}}}
            if(strcmp(name,tag[type][menu_N])==0)chr=enter;
            if(chr==enter){
                for(i=0;i<N_menu[type];i++)for(j=0;j<15;j++)if(strcmp(tag[type][menu_N],menu[type][i].tags[j])==0)strcpy(menu[type][i].tags[j],name);
                strcpy(tag[type][menu_N],name);
                Data_store();
                chr=esc;
            }
        }
    }while(chr!=esc);
}

void add_new_tag(){//Warning
    char chr='\0';
    char warn[3][60]={"(i) Type your tag name.","(!) This name is not available. Please try again.","(!) Please type sth."};
    int a=0,b=0,line=0;
    int menu_N=N_tag[type];
    tag[type][menu_N][b]='\0';
    do{
        system("cls");
        printf("\n\n\n\n\t\tAdding New %s Tag\n\n\t\t Name Your New Tag (max letters: 20)",kind[type]);
        if(chr==del&&b>0)tag[type][menu_N][--b]='\0';
        else if(!(b==0&&chr==' ')&&chr!=del&&chr!='\0'){
            tag[type][menu_N][b++]=chr;
            tag[type][menu_N][b]='\0';
        }
        if(b>20){b=20;tag[type][menu_N][b]='\0';}
        printf("\n\n\t\t>%s",tag[type][menu_N]);
        printf("\n\n\t\t%s",warn[a]);a=0;

        chr=getch();
        if(chr==enter){
            if(b<1)a=2;
            else {for(i=0;i<N_tag[type];i++){if(strcmp(tag[type][menu_N],tag[type][i])==0){a=1;}}}
            if(a==0){
                N_tag[type]++;
                while(tag[type][menu_N][b-1]==' '){tag[type][menu_N][--b]='\0';}
                chr=esc;
                Data_store();
            }
        }
    }while(chr!=esc);
}

void tag_list(){
    char B[4][16]={"+Add New Tag","Custom Sort","Sort A-Z","Select Tag"};
    //char warn[3][70]={"(i) "}
    char temp_tag[21];
    char chr='\0';
    int Vline, Hline, sort_mode, select_mode, S[2], P[50]={0};
    Vline=Hline=cnt=sort_mode=select_mode=0; S[0]=S[1]=-1;
    do{
        system("cls");
        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+17;i++)printf("%c",205);
        printf("%c\n\t\t%c  Add/Edit %s Tag  %c",187,186,kind[type],186);
        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+17;i++)printf("%c",205);
        printf("%c",188);
        printf("\n\n\t\t{ Tag List }  [ %d/100 ]",N_tag[type]);
        for(i=0;i<4;i++){
            if(i==0)printf("\n\n\t");
            printf("        ");
            if(Vline==0&&Hline==i)printf(">>");
            else printf("  ");
            printf(" %s ",B[i]);
            if(Vline==0&&Hline==i)printf("<<");
            else printf("  ");
        }
        printf("\n\t  ");for(i=0;i<110;i++)printf("_");
        for(i=0;i<N_tag[type];i++){
            if(i%3==0)printf("\n\n\t");
            printf("\t");
            if(Vline==i/3+1&&Hline==i%3)printf(">>");
            else printf("  ");
            if((sort_mode==1&&(S[0]==i||S[1]==i))||(select_mode==1&&P[i]==1)) printf("[");
            else printf("%c",bullet+1);
            j=CountTag(i);
            printf(" %s (%d)",tag[type][i],j);
            if(j<10)j=2;
            else if(j<100)j=1;
            else j=0;
            for(k=0;k<j;k++)printf(" ");
            if((sort_mode==1&&(S[0]==i||S[1]==i))||(select_mode==1&&P[i]==1)) printf("]");
            else printf(" ");
            if(Vline==i/3+1&&Hline==i%3)printf("<<");
            else printf("  ");
            if((i+1)%3!=0) for(j=0;j<20-strlen(tag[type][i]);j++) printf(" ");
        }
        if(N_tag[type]<1) printf("\n\n\n\t\t   (!) There's not a tag. Let's add some new tag!");

        chr=getch();
        switch(chr){
            case up   : if(Vline>0)Vline--;break;
            case down : if((N_tag[type]>0&&Vline<(N_tag[type]-1)/3+1)&&!(Hline>N_tag[type]-Vline*3))Vline++;
                        else Vline=1;
                        if(Vline==0)Hline=0;
                        break;
            case left : i=N_tag[type]-(Vline-1)*3;
                        if(Vline==0)i=4;
                        else if(i>3)i=3;
                        Hline=(Hline+i-1)%i;
                        break;
            case right: i=N_tag[type]-(Vline-1)*3;
                        if(Vline==0)i=4;
                        else if(i>3)i=3;
                        Hline=++Hline%i;
                        break;
            case space:
                    if(Vline>0){
                        if(sort_mode==1){
                            menu_N=(Vline-1)*3+Hline;
                            if(menu_N==S[0]){
                                S[0]=S[1];
                                S[1]=-1;
                            }
                            else if(menu_N==S[1])S[1]=-1;
                            else{
                                S[1]=S[0];
                                S[0]=menu_N;
                            }
                        }
                        else if(select_mode==1){
                            menu_N=(Vline-1)*3+Hline;
                            P[menu_N]=++P[menu_N]%2;
                            if(P[menu_N]==1)cnt++;
                            else if(P[menu_N]==0)cnt--;
                        }
                    }
                break;
            case enter:
                switch(Vline){
                    case 0:
                        sort_mode=select_mode=0;
                        strcpy(B[1],"Custom Sort");
                        strcpy(B[3],"Select Tag");
                        S[0]=S[1]=-1;
                        for(i=0;i<N_tag[type];i++)P[i]=0;
                        cnt=0;
                        switch(Hline){
                            case 0: if(N_tag[type]<100)add_new_tag(); break;
                            case 1: if(N_tag[type]>0){
                                        sort_mode=1;
                                        strcpy(B[1],"[[Custom Sort]]");
                                        Vline=1;Hline=0;
                                    }
                                    break;
                            case 2: if(strcmp(B[2],"Sort A-Z")==0){
                                        sortTagA_Z();
                                        strcpy(B[2],"Sort Z-A");
                                    }
                                    else{
                                        sortTagZ_A();
                                        strcpy(B[2],"Sort A-Z");
                                    }
                                    break;
                            case 3: if(N_tag[type]>0){
                                        select_mode=1;
                                        strcpy(B[3],"[[Select Tag]]");
                                        Vline=1;Hline=0;
                                    }
                                    break;
                        }
                        break;
                    default:
                        if(sort_mode==1){
                            if(S[0]!=-1&&S[1]!=-1){
                                strcpy(temp_tag,tag[type][S[0]]);
                                strcpy(tag[type][S[0]],tag[type][S[1]]);
                                strcpy(tag[type][S[1]],temp_tag);
                                S[0]=S[1]=-1;
                                sort_mode=0;
                                strcpy(B[1],"Custom Sort");
                            }
                        }
                        else if(select_mode==1){
                            if(cnt>0){
                                do{
                                    for(i=k=0,j=1;j<N_tag[type];i++,j++){
                                        if(P[i]>P[j]){
                                            l=P[i];P[i]=P[j];P[j]=l;
                                            strcpy(temp_tag,tag[type][i]);
                                            strcpy(tag[type][i],tag[type][j]);
                                            strcpy(tag[type][j],temp_tag);
                                            k++;
                                        }
                                    }
                                }while(k!=0);
                                N_tag[type]-=cnt;if(N_tag[type]<0)N_tag[type]=0;
                                Hline=0;
                                if(N_tag[type]>0)Vline=1;
                                else Vline=0;
                                for(i=0;i<50;i++)P[i]=0;
                                select_mode=cnt=0;
                                strcpy(B[3],"Select Tag");
                            }
                        }
                        else{
                            menu_N=(Vline-1)*3+Hline;
                            edit_tag();
                        }
                        Data_store();
                }
                break;
        }
    }while(chr!=esc);
}

void AddEdit_tag(){
    int page;
    for(page=1;page<3;page++){
        switch(page){
            case 1: type=choose_kind();
                    if(type==3)page=3;
                    break;
            case 2: tag_list();
                    page=0;
                    break;
        }
    }
}

void edit_menu_tag(){
    char chr;
    int Vline=0, Hline=0;
    do{
        system("cls");
        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+23;i++)printf("%c",205);
        printf("%c\n\t\t%c  Edit %s Menu : %s [Tag]  %c",187,186,kind[type],menu[type][menu_N].name,186);
        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+23;i++)printf("%c",205);
        printf("%c",188);
        for(i=0;i<N_tag[type];i++){
            if(i%3==0)printf("\n\n\t\t");
            else printf("\t");
            if(Vline==i/3&&Hline==i%3) printf(">>");
            else printf("  ");
            if(tag_line[i]==1)printf("[");
            else printf(" ");
            printf(" %s ",tag[type][i]);
            if(tag_line[i]==1)printf("]");
            else printf(" ");
            if(Vline==i/3&&Hline==i%3) printf("<<");
            else printf("  ");
            if((i+1)%3!=0) for(j=0;j<30-strlen(tag[type][i]);j++)printf(" ");
        }
        chr=getch();
        if(chr==up){
            if(Vline==0&&(N_tag[type]%3==0||Hline>N_tag[type]%3-1))Vline=N_tag[type]/3-1;
            else if(Vline==0)Vline=N_tag[type]/3;
            else Vline--;
        }
        else if(chr==down){
            if((Vline==N_tag[type]/3-1&&N_tag[type]%3==0)||(N_tag[type]%3!=0&&(Hline>N_tag[type]%3-1&&Vline==N_tag[type]/3-1)||(Hline<=N_tag[type]%3-1&&Vline==N_tag[type]/3))) Vline=0;
            else Vline++;
        }
        else if(chr==left){
            i=N_tag[type]-Vline*3;
            if(i>3)i=3;
            Hline=(Hline+i-1)%i;
        }
        else if(chr==right){
            i=N_tag[type]-Vline*3;
            if(i>3)i=3;
            Hline=++Hline%i;
        }
        else if(chr==space){
            i=Vline*3+Hline;
            if(tag_line[i]==0&&cnt<15){
                cnt++;
                tag_line[i]=1;
            }
            else if(tag_line[i]==1){
                cnt--;
                tag_line[i]=0;
            }
        }
        else if(chr==enter) {
            if(cnt==0)chr='\0';
        }
    }while(chr!=enter&&chr!=esc);
}

void edit_menu(){
    char name[31],des[301];
    char warn[3][65]={"(i) Type something then press Enter."};
    char chr;
    int a=0,n1,n2, confirm_mode=0, line=0;
    int cnt=0,count = 17,count1 = 17 ,count2 = 17;
    strcpy(name,menu[type][menu_N].name);
    n1=strlen(name);
    strcpy(des,menu[type][menu_N].description);
    n2=strlen(des);
    for(i=0;i<N_tag[type];i++)tag_line[i]=0;
    for(j=0;j<15;j++){
        if(strcmp(menu[type][menu_N].tags[j],"none")!=0){
            for(i=0;i<N_tag[type];i++){
                if(strcmp(menu[type][menu_N].tags[j],tag[type][i])==0){tag_line[i]=1;cnt++;}
            }
        }
    }
    do{
        system("cls");
        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+17;i++)printf("%c",205);
        printf("%c\n\t\t%c  Edit %s Menu : %s  %c",187,186,kind[type],menu[type][menu_N].name,186);
        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+17;i++)printf("%c",205);
        printf("%c",188);
        if(line==0) printf("\n\n\t      >>> ");
        else printf("\n\n\t          ");
        printf("[1]New Name : %s",name);

        if(line==1)printf("\n\n\t      >>> ");
        else printf("\n\n\t          ");
        printf("[2]Tags : ");
        for(i=j=0;i<N_tag[type];i++){
            if(tag_line[i]==1){
                if(j!=0)printf(", ");
                printf("%s",tag[type][i]);
                j++;
            }
        }

        printf("\n\n\t");
        if(line==2)printf("      >>> ");
        else printf("          ");
        printf("[3]Description : ");
        for(i=0;i<strlen(des);i++)
        {
            if(count<=100){
                printf("%c",des[i]);
                count++;
            }else if(des[i]==' '){
                printf("\n\n\t\t  ");
                count = 0;
            }else printf("%c",des[i]);
        }
        count = 17;
        printf("\n\n\t\t\t\t");
        switch(confirm_mode){
            case 0:
                if(line==3)printf(">> Save <<");
                else printf("   Save   ");
                if(line==4)printf("\t>> Dismiss <<");
                else printf("\t   Dismiss");
                break;
            case 1:
                printf("\tSave ?\n\n\t\t\t\t");
                if(line==3)printf(">> Save <<");
                else printf("   Save   ");
                if(line==4)printf("\t>> Cancel <<");
                else printf("\t   Cancel");
                break;
            case 2:
                printf("\tCancel ?\n\n\t\t\t\t");
                if(line==3)printf(">> Dismiss <<");
                else printf("   Dismiss   ");
                if(line==4)printf("\t>> Cancel <<");
                else printf("\t   Cancel");
                break;
        }

        chr=getch();
        switch(chr){
            case up: if(line>2){
                        line=2;
                        confirm_mode=0;
                     }
                     else if(line>0)line--;
                     break;
            case down: if(line<3)line++;   break;
            case left: if(line==4)line--;  break;
            case right: if(line==3)line++; break;
            case enter:
                chr='\0';
                switch(line){
                case 0:
                    strcpy(warn[1],"(!) This name is not available. Please try again.");
                    strcpy(warn[2],"(!) There should be a name for your menu. Please type something.");
                    do{
                        system("cls");
                        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+23;i++)printf("%c",205);
                        printf("%c\n\t\t%c  Edit %s Menu : %s [Name] %c",187,186,kind[type],menu[type][menu_N].name,186);
                        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+23;i++)printf("%c",205);
                        printf("%c",188);
                        if(chr==del&&n1>0)name[--n1]='\0';
                        else if(!(n1==0&&chr==' ')&&chr!=del&&chr!='\0'){
                            name[n1++]=chr;
                            name[n1]='\0';
                        }
                        if(n1>30){n1=30;name[n1]='\0';}
                        printf("\n\n\t\tCurrent Name : %s\n\n\t\t    New name : %s",menu[type][menu_N].name,name);
                        printf("\n\n\t\t%s",warn[a]);a=0;
                        chr=getch();
                        if(chr==enter&&n1<1){a=1;chr='\0';}
                        //else if(chr==enter){for(i=0;i<N_menu[type];i++){if(strcmp(name,menu[type][i].name)==0){a=1;chr='\0';}}}
                        if(chr==enter&&a==0)while(name[n1-1]==' '){name[--n1]='\0';}
                    }while(chr!=enter&&chr!=esc);
                    chr='\0';
                    break;
                case 1: edit_menu_tag();break;
                case 2:
                    strcpy(warn[2],"(!) There should be a short description for your menu. Please type something.");
                    do{
                        system("cls");
                        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+32;i++)printf("%c",205);
                        printf("%c\n\t\t%c  Edit %s Menu : %s [Description]   %c",187,186,kind[type],menu[type][menu_N].name,186);
                        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+strlen(menu[type][menu_N].name)+32;i++)printf("%c",205);
                        printf("%c",188);
                        if(chr==del&&n2>0)des[--n2]='\0';
                        else if(!(n2==0&&chr==' ')&&chr!=del&&chr!='\0'){
                            des[n2++]=chr;
                            des[n2]='\0';
                        }
                        if(n2>300){n2=300;des[n2]='\0';}
                        printf("\n\n\n\n\t\tCurrent Description : ");
                        for(i=0;i<strlen(menu[type][menu_N].description);i++)
                            {
                                if(count1<=100){
                                    printf("%c",menu[type][menu_N].description[i]);
                                    count1++;
                                }else if(des[i]==' '){
                                    printf("\n\n\t\t");
                                    count1 = 0;
                                }else printf("%c",menu[type][menu_N].description[i]);
                            }
                        count1 = 17;
                        printf("\n\n\n\n\t\tNew Description : ");
                        for(i=0;i<strlen(des);i++)
                            {
                                if(count2<=100){
                                    printf("%c",des[i]);
                                    count2++;
                                }else if(des[i]==' '){
                                    printf("\n\n\t\t");
                                    count2 = 0;
                                }else printf("%c",des[i]);
                            }
                        count2 = 17;
                        printf("\n\n\n\n\t\t%s",warn[a]);a=0;
                        chr=getch();
                        if(chr==enter&&n2<1){a=2;chr='\0';}
                        if(chr==enter&&a==0)while(des[n2-1]==' '){des[--n2]='\0';}
                    }while(chr!=enter&&chr!=esc);
                    chr='\0';
                    break;
                case 3:
                    switch(confirm_mode){
                    case 0: confirm_mode=1; line=4; break;
                    case 1:
                        for(i=0;i<N_menu[type];i++){if(strcmp(name,menu[type][i].name)==0){a=1;chr='\0';}}
                        if(strcmp(name,menu[type][menu_N].name)==0) a=0;
                        if(a!=1){
                            strcpy(menu[type][menu_N].name,name);
                            strcpy(menu[type][menu_N].description,des);
                            for(i=0;i<15;i++)strcpy(menu[type][menu_N].tags[i],"none");
                            for(i=j=0;i<N_tag[type]&&j<15;i++){
                                if(tag_line[i]==1)strcpy(menu[type][menu_N].tags[j++],tag[type][i]);
                            }
                            Data_store();
                        }
                    case 2: chr=esc; break;
                    }break;
                case 4:
                    switch(confirm_mode){
                    case 0: confirm_mode=2; break;
                    case 1:
                    case 2: confirm_mode=0; line=3; break;
                    }break;
                } break;
        }
    }while(chr!=esc);
}

int new_menu_confirm(){
    char chr;
    int confirm_mode=0, line=0,count = 17;
    do{
        system("cls");
        printf("\n\n\n\n\t\tAdding New %s Menu [Part4/4]",kind[type]);

        printf("\n\n\t");
        if(line==0)printf("      >>> ");
        else printf("          ");
        printf("[1]Name : %s",menu[type][menu_N].name);

        printf("\n\n\t");
        if(line==1)printf("      >>> ");
        else printf("          ");
        printf("[2]Tags : ");
        for(i=0,j=1;i<15;i++){
            if(strcmp(menu[type][menu_N].tags[i],"none")!=0){
                if(j!=1)printf(", ");
                printf("%s",menu[type][menu_N].tags[i]);
                j++;
            }
        }

        printf("\n\n\t");
        if(line==2)printf("      >>> ");
        else printf("          ");
        //printf("[3]Description : %s",menu[type][menu_N].description);
        printf("[3]Description : ");
        for(i=0;i<strlen(menu[type][menu_N].description);i++)
        {
            if(count<=100){
                printf("%c",menu[type][menu_N].description[i]);
                count++;
            }else if(menu[type][menu_N].description[i]==' '){
                printf("\n\n\t\t  ");
                count = 0;
            }else printf("%c",menu[type][menu_N].description[i]);
        }
        count = 17;
        printf("\n\n\t\t\t\t");
        switch(confirm_mode){
            case 0:
                if(line==3)printf(">> Save <<");
                else printf("   Save   ");
                if(line==4)printf("\t>> Delete <<");
                else printf("\t   Delete");
                break;
            case 1:
                printf("\tSave ?\n\n\t\t\t\t");
                if(line==3)printf(">> Save <<");
                else printf("   Save   ");
                if(line==4)printf("\t>> Cancel <<");
                else printf("\t   Cancel");
                break;
            case 2:
                printf("\tDelete ?\n\n\t\t\t\t");
                if(line==3)printf(">> Delete <<");
                else printf("   Delete   ");
                if(line==4)printf("\t>> Cancel <<");
                else printf("\t   Cancel");
                break;
        }

        chr=getch();
        switch(chr){
            case up: if(line>2){
                        line=2;
                        confirm_mode=0;
                     }
                     else if(line>0)line--;
                     break;
            case down: if(line<3)line++;   break;
            case left: if(line==4)line--;  break;
            case right: if(line==3)line++; break;
            case enter:
                chr='\0';
                switch(line){
                case 0: new_menu_name(); break;
                case 1: new_menu_tag();break;
                case 2: chr=esc;break;
                case 3:
                    switch(confirm_mode){
                    case 0: confirm_mode=1; line=4; break;
                    case 1: N_menu[type]++;
                            Data_store();
                            chr=enter; break;
                    case 2: chr=esc; break;
                    }break;
                case 4:
                    switch(confirm_mode){
                    case 0: confirm_mode=2; break;
                    case 1:
                    case 2: confirm_mode=0; line=3; break;
                    }break;
                } break;
        }
    }while(chr!=esc&&chr!=enter);
    switch(chr){
        case esc: return 0;break;
        default:return 1;
    }
}

int new_menu_description(){
    char chr='\0';
    int count=1;
    do{
        system("cls");
        printf("\n\n\n\n\t\tAdding New %s Menu [Part3/4]\n\n\t\t Write a short description for your menu! (max letters: 300)\n\n\t\t>",kind[type]);
        if(chr==del&&m>0)menu[type][menu_N].description[--m]='\0';
        else if(!(m==0&&chr==' ')&&chr!=del&&chr!='\0'){
            menu[type][menu_N].description[m++]=chr;
            menu[type][menu_N].description[m]='\0';
        }
        if(m>300){m=300;menu[type][menu_N].description[m]='\0';}
        //printf("%s",menu[type][menu_N].description);

        for(i=0;i<strlen(menu[type][menu_N].description);i++)
        {
            if(count<=100){
                printf("%c",menu[type][menu_N].description[i]);
                count++;
            }else if(menu[type][menu_N].description[i]==' '){
                printf("\n\n\t\t");
                count = 0;
            }else printf("%c",menu[type][menu_N].description[i]);
        }
        count = 1;



        chr=getch();
        if(chr==enter&&m<1){chr='\0';}
        if(chr==enter)while(menu[type][menu_N].description[m-1]==' '){menu[type][menu_N].description[--m]='\0';}
    }while(chr!=enter&&chr!=esc);
    switch(chr){
        case enter: return 1;break;
        case esc: return 0;break;
    }
}

int new_menu_tag(){
    char chr;
    int Vline=0, Hline=0;
    do{
        system("cls");
        printf("\n\n\n\n\t\tAdding New %s Menu [Part2/4]\n\n\t\t What ingredient is in your menu? (%d/15)\t\tPress '+' to add new tag",kind[type],cnt);
        for(i=0;i<N_tag[type];i++){
            if(i%3==0)printf("\n\n\t\t");
            else printf("\t");
            if(Vline==i/3&&Hline==i%3) printf(">>");
            else printf("  ");
            if(tag_line[i]==1)printf("[");
            else printf(" ");
            printf(" %s ",tag[type][i]);
            if(tag_line[i]==1)printf("]");
            else printf(" ");
            if(Vline==i/3&&Hline==i%3) printf("<<");
            else printf("  ");
            if((i+1)%3!=0) for(j=0;j<20-strlen(tag[type][i]);j++)printf(" ");
        }
        if(N_tag[type]<1)printf("\n\n\n\t\t  (!) Press '+' to add new tag");

        chr=getch();
        if(chr==up){
            if(Vline==0&&(N_tag[type]%3==0||Hline>N_tag[type]%3-1))  Vline=N_tag[type]/3-1;
            else if(Vline==0)  Vline=N_tag[type]/3;
            else Vline--;
        }
        else if(chr==down){
            if((Vline==N_tag[type]/3-1&&N_tag[type]%3==0)||
               (N_tag[type]%3!=0&&(Hline>N_tag[type]%3-1&&Vline==N_tag[type]/3-1)
                ||(Hline<=N_tag[type]%3-1&&Vline==N_tag[type]/3)))  Vline=0;
            else Vline++;
        }
        else if(chr==left){
            i=N_tag[type]-Vline*3;
            if(i>3) i=3;
            Hline=(Hline+i-1)%i;
        }
        else if(chr==right){
            i=N_tag[type]-Vline*3;
            if(i>3) i=3;
            Hline=++Hline%i;
        }
        else if(chr==space){
            i=Vline*3+Hline;
            if(tag_line[i]==0&&cnt<15){
                cnt++;
                tag_line[i]=1;
            }
            else if(tag_line[i]==1){
                cnt--;
                tag_line[i]=0;
            }
        }
        else if(chr=='+'){
            i=N_tag[type];
            add_new_tag();
            if(i!=N_tag[type])tag_line[N_tag[type]-1]=0;
        }
        else if(chr==enter){
            if(cnt==0)chr='\0';//warning
            else{
                for(i=0;i<15;i++) strcpy(menu[type][menu_N].tags[i],"none");
                for(i=j=0;i<N_tag[type]&&j<15;i++)
                    if(tag_line[i]==1) strcpy(menu[type][menu_N].tags[j++],tag[type][i]);
            }
        }
    }while(chr!=enter&&chr!=esc);
    switch(chr){
        case enter: return 1;break;
        case esc: return 0;break;
    }
}

int new_menu_name(){
    char chr='\0';
    do{
        system("cls");
        printf("\n\n\n\n\t\tAdding New %s Menu [Part1/4]\n\n\t\t Name Your New Menu (max letters: 30)",kind[type]);
        if(chr==del&&l>0)menu[type][menu_N].name[--l]='\0';
        else if(!(l==0&&chr==' ')&&chr!=del&&chr!='\0'){//(chr==up||chr==down||chr==left||chr==right||')//||(chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')
            menu[type][menu_N].name[l++]=chr;
            menu[type][menu_N].name[l]='\0';
        }
        if(l>30){l=30;menu[type][menu_N].name[l]='\0';}
        printf("\n\n\t\t>%s",menu[type][menu_N].name);
        /*printf("\n\n\t\t>%s_%d\n\n\n\t\t",menu[type][menu_N].name,l);
        for(i=0;i<=l;i++)printf("%d ; ",menu[type][menu_N].name[i]);*/
        chr=getch();
        if(chr==enter&&l<1){chr='\0';}
        else if(chr==enter){for(i=0;i<N_menu[type];i++){if(strcmp(menu[type][menu_N].name,menu[type][i].name)==0){chr='\0';printf("\n\n\t\t(!) This name is not available.");chr=getch();}}}
        if(chr==enter)while(menu[type][menu_N].name[l-1]==' '){menu[type][menu_N].name[--l]='\0';}
    }while(chr!=enter&&chr!=esc);
    switch(chr){
        case enter: return 1;break;
        case esc: return 0;break;
    }
}

void add_new_menu(){
    int a,page;
    for(i=0;i<N_tag[type];i++)tag_line[i]=0;
    menu_N = N_menu[type];
    menu[type][menu_N].name[0]=menu[type][menu_N].description[0]='\0';
    l=m=cnt=0;
    for(page=1;page<5;page++){
        switch(page){
        case 1:a=new_menu_name();
            if(a==0)page=5;break;
        case 2:a=new_menu_tag();
            if(a==0)page=0;break;
        case 3:a=new_menu_description();
            if(a==0)page=1;break;
        case 4:a=new_menu_confirm();
            if(a==0)page=2;break;
        }
    }
}

void menu_list(){
    char B[4][16]={"+Add New menu","Custom Sort","Sort A-Z","Select Menu"};
    char temp_menu[15][21];
    char temp_des[301];
    char chr='\0';
    int Vline, Hline, sort_mode, select_mode, S[2], P[100]={0};
    Vline=Hline=cnt=sort_mode=select_mode=0; S[0]=S[1]=-1;
    do{
        system("cls");
        printf("\n\n\n\n\t\t%c",201); for(i=0;i<strlen(kind[type])+18;i++)printf("%c",205);
        printf("%c\n\t\t%c  Add/Edit %s Menu  %c",187,186,kind[type],186);
        printf("\n\t\t%c",200);       for(i=0;i<strlen(kind[type])+18;i++)printf("%c",205);
        printf("%c",188);
        printf("\n\n\t\t{ Menu List }  [ %d/100 ]",N_menu[type]);
        for(i=0;i<4;i++){
            if(i==0)printf("\n\n\t");
            printf("        ");
            if(Vline==0&&Hline==i)printf(">>");
            else printf("  ");
            printf(" %s ",B[i]);
            if(Vline==0&&Hline==i)printf("<<");
            else printf("  ");
        }
        printf("\n\t     ");for(i=0;i<120;i++)printf("_");
        for(i=0;i<N_menu[type];i++){
            if(i%3==0)printf("\n\n\t");
            printf("\t");
            if(Vline==i/3+1&&Hline==i%3)printf(">>");
            else printf("  ");
            if((sort_mode==1&&(S[0]==i||S[1]==i))||(select_mode==1&&P[i]==1)) printf("[");
            else printf("%c",bullet);
            printf(" %s ",menu[type][i].name);
            if((sort_mode==1&&(S[0]==i||S[1]==i))||(select_mode==1&&P[i]==1)) printf("]");
            else printf(" ");
            if(Vline==i/3+1&&Hline==i%3)printf("<<");
            else printf("  ");
            if((i+1)%3!=0) for(j=0;j<30-strlen(menu[type][i].name);j++) printf(" ");
        }
        if(N_menu[type]<1) printf("\n\n\n\t\t\t\t   --- No menu ---");

        chr=getch();
        switch(chr){
            case up   : if(Vline>0)Vline--;break;
            case down : if(N_menu[type]>0&&Vline<(N_menu[type]-1)/3+1&&!(Hline>N_menu[type]-Vline*3))Vline++;
                        else Vline=1;
                        if(Vline==0)Hline=0;
                        break;
            case left : i=N_menu[type]-(Vline-1)*3;
                        if(Vline==0)i=4;
                        else if(i>3)i=3;
                        Hline=(Hline+i-1)%i;
                        break;
            case right: i=N_menu[type]-(Vline-1)*3;
                        if(Vline==0)i=4;
                        else if(i>3)i=3;
                        Hline=++Hline%i;
                        break;
            case space:
                if(Vline>0){
                    if(sort_mode==1){
                        menu_N=(Vline-1)*3+Hline;
                        if(menu_N==S[0]){
                            S[0]=S[1];
                            S[1]=-1;
                        }
                        else if(menu_N==S[1])S[1]=-1;
                        else{
                            S[1]=S[0];
                            S[0]=menu_N;
                        }
                    }
                    else if(select_mode==1){
                        menu_N=(Vline-1)*3+Hline;
                        P[menu_N]=++P[menu_N]%2;
                        if(P[menu_N]==1)cnt++;
                        else if(P[menu_N]==0)cnt--;
                    }
                }
                break;
            case enter:
                switch(Vline){
                    case 0:
                        switch(Hline){
                            case 0: sort_mode=select_mode=0;
                                    strcpy(B[1],"Custom Sort");
                                    strcpy(B[3],"Select Menu");
                                    S[0]=S[1]=-1;
                                    for(i=0;i<N_menu[type];i++)P[i]=0;
                                    cnt=0;
                                    if(N_menu[type]<100)add_new_menu();
                                    break;
                            case 1: if(sort_mode==0&&N_menu[type]>0){
                                        sort_mode=1;
                                        strcpy(B[1],"[[Custom Sort]]");
                                        Vline=1;Hline=0;
                                    }
                                    else{
                                        sort_mode=0;
                                        strcpy(B[1],"Custom Sort");
                                        S[0]=S[1]=-1;
                                    }
                                    select_mode=0;
                                    strcpy(B[3],"Select Menu");
                                    for(i=0;i<N_menu[type];i++)P[i]=0;
                                    cnt=0;
                                    break;
                            case 2: if(strcmp(B[2],"Sort A-Z")==0){
                                        sortA_Z();
                                        strcpy(B[2],"Sort Z-A");
                                    }
                                    else{
                                        sortZ_A();
                                        strcpy(B[2],"Sort A-Z");
                                    }
                                    sort_mode=select_mode=0;
                                    strcpy(B[1],"Custom Sort");
                                    strcpy(B[3],"Select Menu");
                                    S[0]=S[1]=-1;
                                    for(i=0;i<N_menu[type];i++)P[i]=0;
                                    cnt=0;
                                    break;
                            case 3: if(select_mode==0&&N_menu[type]>0){
                                        select_mode=1;
                                        strcpy(B[3],"[[Select Menu]]");
                                        Vline=1;Hline=0;
                                    }
                                    else{
                                        select_mode=0;
                                        strcpy(B[3],"Select Menu");
                                        for(i=0;i<N_menu[type];i++)P[i]=0;
                                        cnt=0;
                                    }
                                    sort_mode=0;
                                    strcpy(B[1],"Custom Sort");
                                    S[0]=S[1]=-1;
                                    break;
                        }
                        break;
                    default:
                        if(sort_mode==1){
                            if(S[0]!=-1&&S[1]!=-1){
                                strcpy(temp_des,menu[type][S[0]].name);
                                strcpy(menu[type][S[0]].name,menu[type][S[1]].name);
                                strcpy(menu[type][S[1]].name,temp_des);
                                for(i=0;i<15;i++)strcpy(temp_menu[i],menu[type][S[0]].tags[i]);
                                for(i=0;i<15;i++)strcpy(menu[type][S[0]].tags[i],menu[type][S[1]].tags[i]);
                                for(i=0;i<15;i++)strcpy(menu[type][S[1]].tags[i],temp_menu[i]);
                                strcpy(temp_des,menu[type][S[0]].description);
                                strcpy(menu[type][S[0]].description,menu[type][S[1]].description);
                                strcpy(menu[type][S[1]].description,temp_des);
                                S[0]=S[1]=-1;
                                sort_mode=0;
                                strcpy(B[1],"Custom Sort");
                            }
                        }
                        else if(select_mode==1){
                            if(cnt>0){
                                do{
                                    for(i=k=0,j=1;j<N_menu[type];i++,j++){
                                        if(P[i]>P[j]){
                                            l=P[i];P[i]=P[j];P[j]=l;
                                            strcpy(temp_des,menu[type][i].name);
                                            strcpy(menu[type][i].name,menu[type][j].name);
                                            strcpy(menu[type][j].name,temp_des);
                                            for(l=0;l<15;l++)strcpy(temp_menu[l],menu[type][i].tags[l]);
                                            for(l=0;l<15;l++)strcpy(menu[type][i].tags[l],menu[type][j].tags[l]);
                                            for(l=0;l<15;l++)strcpy(menu[type][j].tags[l],temp_menu[l]);
                                            strcpy(temp_des,menu[type][i].description);
                                            strcpy(menu[type][i].description,menu[type][j].description);
                                            strcpy(menu[type][j].description,temp_des);
                                            k++;
                                        }
                                    }
                                }while(k!=0);
                                N_menu[type]-=cnt;if(N_menu[type]<0)N_menu[type]=0;
                                Hline=0;
                                if(N_menu[type]>0)Vline=1;
                                else Vline=0;
                                for(i=0;i<100;i++)P[i]=0;
                                select_mode=cnt=0;
                                strcpy(B[3],"Select Menu");
                            }
                        }
                        else{
                            menu_N=(Vline-1)*3+Hline;
                            edit_menu();
                        }
                        Data_store();
                }
                break;
        }
    }while(chr!=esc);
}

int choose_kind(){
    char A[2][5]={"Menu","Tag "};
    char chr;
    int line=0;
    do{
        system("cls");
        printf("\n\n\n\n\n\t\t\t%c",201);
        for(i=0;i<=16;i++)
        {
            printf("%c",205);
        }
        printf("%c\n\t\t\t%c  Add/Edit %s  %c",187,186, A[Select-1],186);
        printf("\n\t\t\t%c",200);

        for(i=0;i<=16;i++)
        {
            printf("%c",205);
        }
        printf("%c",188);
        printf("\n\n\t\t\tSelect a Kind of Food (one choice)");
        for(i=0;i<3;i++){
            printf("\n\n\t\t\t  %-14s",kind[i]);
            if(line==i)printf("<<<");
        }
        chr=getch();
        if(chr==up&&line>0)         line--;
        else if(chr==down&&line<2)  line++;
    }while(chr!=enter&&chr!=esc);
    if(chr==enter) return line;
    else if(chr==esc) return 3;
}

void AddEdit_menu(){
    int page;
    for(page=1;page<3;page++){
        switch(page){
            case 1: type=choose_kind();
                    if(type==3)page=3;
                    break;
            case 2: menu_list();
                    page=0;
                    break;
        }
    }
}

int fselect(){
    char merchant_menu[2][14]={"Add/Edit Menu","Add/Edit Tag"};
    char chr;
    int line=0;
    do{
        system("cls");
        printf("\n\n\n\n\n\n\t\t\t%c",201);
        for(i=0;i<=29;i++)printf("%c",205);
        printf("%c\n\t\t\t%c   Menu and Tags Management   %c\n\t\t\t%c",187,186,186,200);
        for(i=0;i<=29;i++)printf("%c",205);
        printf("%c",188);
        for(i=0;i<2;i++){
            printf("\n\n\n\t\t\t %-15s",merchant_menu[i]);
            if(line==i)printf("<<<");
        }
        chr=getch();
        switch(chr){
            case up:    if(line!=0)line--;                       break;
            case down:  if(line!=1)line++;                       break;
            case enter: return line+1;                           break;
            case esc:   return 0;                                break;
        }
    }while(chr!=enter&&chr!=esc);
}

int for_merchant(){
    switch(Select=fselect()){
        case 1: AddEdit_menu();          break;
        case 2: AddEdit_tag();           break;
    }
    if(Select==0){topic = -1;return 0;}
    else return 1;
}

void sortZ_A(){
    char temp_menu[15][21];
    char temp_des[301];
    do{
        for(i=0,j=1,cnt=0;j<N_menu[type];i++,j++){
            if(strcmp(menu[type][i].name,menu[type][j].name)<0){
                strcpy(temp_des,menu[type][i].name);
                strcpy(menu[type][i].name,menu[type][j].name);
                strcpy(menu[type][j].name,temp_des);
                for(k=0;k<15;k++)strcpy(temp_menu[k],menu[type][i].tags[k]);
                for(k=0;k<15;k++)strcpy(menu[type][i].tags[k],menu[type][j].tags[k]);
                for(k=0;k<15;k++)strcpy(menu[type][j].tags[k],temp_menu[k]);
                strcpy(temp_des,menu[type][i].description);
                strcpy(menu[type][i].description,menu[type][j].description);
                strcpy(menu[type][j].description,temp_des);
                cnt++;
            }
        }
    }while(cnt!=0);
}

void sortA_Z(){
    char temp_menu[15][21];
    char temp_des[301];
    do{
        for(i=0,j=1,cnt=0;j<N_menu[type];i++,j++){
            if(strcmp(menu[type][i].name,menu[type][j].name)>0){
                strcpy(temp_des,menu[type][i].name);
                strcpy(menu[type][i].name,menu[type][j].name);
                strcpy(menu[type][j].name,temp_des);
                for(k=0;k<15;k++)strcpy(temp_menu[k],menu[type][i].tags[k]);
                for(k=0;k<15;k++)strcpy(menu[type][i].tags[k],menu[type][j].tags[k]);
                for(k=0;k<15;k++)strcpy(menu[type][j].tags[k],temp_menu[k]);
                strcpy(temp_des,menu[type][i].description);
                strcpy(menu[type][i].description,menu[type][j].description);
                strcpy(menu[type][j].description,temp_des);
                cnt++;
            }
        }
    }while(cnt!=0);
}

void sortTagA_Z(){
    char temp_tag[21];
    do{
        for(i=0,j=1,cnt=0;j<N_tag[type];i++,j++){
            if(strcmp(tag[type][i],tag[type][j])>0){
                strcpy(temp_tag,tag[type][i]);
                strcpy(tag[type][i],tag[type][j]);
                strcpy(tag[type][j],temp_tag);
                cnt++;
            }
        }
    }while(cnt!=0);
}

void sortTagZ_A(){
    char temp_tag[21];
    do{
        for(i=0,j=1,cnt=0;j<N_tag[type];i++,j++){
            if(strcmp(tag[type][i],tag[type][j])<0){
                strcpy(temp_tag,tag[type][i]);
                strcpy(tag[type][i],tag[type][j]);
                strcpy(tag[type][j],temp_tag);
                cnt++;
            }
        }
    }while(cnt!=0);
}

int CountTag(int a){
    int b,c,sum=0;
    for(b=0;b<N_menu[type];b++){
        for(c=0;c<15;c++){
            if(strcmp(tag[type][a],menu[type][b].tags[c])==0)sum++;
        }
    }
    return sum;
}
//Start
int main(){
    Data_import();
    do{
        if(topic==-1){
            start();
        }else if(topic==0){
            pages();
        }else if(topic==1){
            for_merchant();
        }else if(topic==2){
            credit();
        }else if(topic==3){
            break;
        }

    }while(1);
    return 0;
}
