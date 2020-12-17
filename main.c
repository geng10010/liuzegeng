#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define  DATA        "F:\\HomeworkData\\data.txt"
#define  TETILE      "---------��������--------------\t����ʡ---------\t��ɫ-----------\t��ͨ��ʽ-------\t����-----------\t�շѱ�׼--------*\t\n"
#define  HELP        "*********************************************** ���� ***********************************************\n����˵����\n\t������ʾ�����Ӧ���ּ������»س�ִ����Ӧ���ܡ�\n\n�����ļ�·����\n\tF:\\HomeworkData\\data.txt\n\t�粻���ڴ��ļ����Զ�����ʧ�ܣ��볢���ֶ������������ļ�\n\n��ѯϵͳ��\n\t��ϵͳ�������������Զ��жϲ�ѯ��ʽ�����õĲ�ѯ��ʽ�У�\n\t\tCase 1: �������Ʋ�ѯ\n\t\tCase 2: �����������շѲ�ѯ\n****************************************************************************************************\n"

void open();
void load();
void save();
void mainMenu();
void mainIntent();
void show(int mod);
void showIntent();
void sort(int mod);
void showViews();
int  big(int a,int b,int mod);
void exchange(int a,int b);
void create();
void modify();
void modifyIntent();
void query();
int  isint(char *s);
void queryByInt(int m);
void queryByStr(char *s);
void queryIntent();
void delet();
void deletIntent();
void help();
FILE *fp;
char ch;
int  n = 0;
int  input;
struct view{
    char name[100];
    char prov[100];
    char spec[100];
    char traf[100];
    int  days;
    int  piec;
}views[10010];
struct view view0;
int main(){
    open();
    return 0;
}
void open(){
    if((fp = fopen(DATA,"r")) == NULL){
        fp = fopen(DATA,"w");
        fp = fopen(DATA,"r");
    }
    ch = fgetc(fp);
    if(ch == EOF){
        printf("����Ϊ�գ�\n");           //����Ϊ'#'�����ж�
        system("pause");
        mainMenu();
    }
    else load();
}
void load(){
    printf("*������...\n");
    system("cls");                        //����
    n = 0;
    while((ch = fgetc(fp)) != '#'){       //��ȡ��������
        n *= 10;
        n += ch - '0';
    }
    //printf("*��������: %d\n",n);
    for(int i = 0;i < n;i++){
        for(int j = 0; ((ch = fgetc(fp)) != '#'); j++){
            views[i].name[j  ] = ch  ;
            views[i].name[j+1] = '\0';
        }
        //printf("%s\t", views[i].name);
        for(int j = 0; ((ch = fgetc(fp)) != '#'); j++){
            views[i].prov[j  ] = ch  ;
            views[i].prov[j+1] = '\0';
        }
        //printf("%s\t", views[i].prov);
        for(int j = 0; ((ch = fgetc(fp)) != '#'); j++){
            views[i].spec[j  ] = ch  ;
            views[i].spec[j+1] = '\0';
        }
        //printf("%s\t", views[i].spec);
        for(int j = 0; ((ch = fgetc(fp)) != '#'); j++){
            views[i].traf[j  ] = ch  ;
            views[i].traf[j+1] = '\0';
        }
        //printf("%s\t", views[i].traf);
        views[i].days = 0;
        while((ch = fgetc(fp)) != '#'){
            views[i].days *= 10      ;
            views[i].days += ch - '0';
        }
        printf("%d\t", views[i].days);
        views[i].piec = 0;
        while((ch = fgetc(fp)) != '#'){
            views[i].piec *= 10      ;
            views[i].piec += ch - '0';
        }
        //printf("%d\t\n",views[i].piec);
    }
    printf("*�������. . .\n");
    fclose(fp);
    //fp = fopen(DATA,"w");
    mainMenu();                          //��ת�����˵�
}
void save(){
    fp =  fopen(DATA,"w");
    char  str[20]   ;
    fputc ('#'  ,fp);
    itoa  (n,str,10);                      //int ת �ַ���
    fputs (str  ,fp);
    fputc ('#'  ,fp);
    printf("������...\n");
    for(int i = 0;i < n;i++){
        fputs(views[i].name,fp);
        fputc(     '#'     ,fp);
        fputs(views[i].prov,fp);
        fputc(     '#'     ,fp);
        fputs(views[i].spec,fp);
        fputc(     '#'     ,fp);
        fputs(views[i].traf,fp);
        fputc(     '#'     ,fp);
        itoa (views[i].days,str, 10);
        fputs(     str     ,fp);
        fputc(     '#'     ,fp);
        itoa (views[i].piec,str, 10);
        fputs(     str     ,fp);
        fputc(     '#'     ,fp);
    }
    fclose(fp);
}
void mainMenu(){
    char menu[][8] = {"���","����","�޸�","��ѯ","ɾ��","����","�˳�"};
    system("cls");
    printf("***************************************** ������Ϣ����ϵͳ *****************************************\n");
    for(int i = 0;i < 6;i++){
        printf("*%d. %s                                                                                           *\n",i+1,menu[i]);
    }
    printf("*%d. %s                                                                                           *\n",0,menu[6]);
    printf("****************************************************************************************************\n");
    mainIntent();
}
void mainIntent(){
    scanf("%d",&input);
    switch(input){
        case   1: show(0);        break;
        case   2: create();       break;
        case   3: modify();       break;
        case   4: query();        break;
        case   5: delet();        break;
        case   6: help();         break;
        case   0: save();exit(0); break;
        default : printf("��������������\n"); mainIntent();
    }
}
void show(int mod){
    if(mod) sort(mod);
    char menu[][16] = {"����������","��ʡ������","����������","���շ�����","�������˵�","�˳�ϵͳ  "};
    //                  1            2            3            4            5            0
    system("cls");
    showViews();
    for(int i = 0;i < 5;i++){
        printf("*%d. %s                                                                                                  *\n",i+1,menu[i]);
    }
    printf("*%d. %s                                                                                                  *\n",0,menu[5]);
    showIntent();
}
void showIntent(){
    scanf("%d",&input);
    switch(input){
        case   1: show(1);         break;
        case   2: show(2);         break;
        case   3: show(3);         break;
        case   4: show(4);         break;
        case   5: mainMenu();      break;
        case   0: save(); exit(0); break;
        default : printf("��������������\n"); showIntent();
    }
}
void showViews(){
    printf(TETILE);
    for(int i = 0;i < n;i++){
        printf( "Case %d\t:",        i+1);
        printf( "%-23s",   views[i].name);
        printf( "%-16s",   views[i].prov);
        printf( "%-16s",   views[i].spec);
        printf( "%-16s",   views[i].traf);
        printf( "%-16d",   views[i].days);
        printf( "%-16d*\n",views[i].piec);
    }
}
void sort(int mod){
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < n - 1 -i;j++){
            if(big(j,j+1,mod)){
                exchange(j,j+1);
            }
        }
    }
}
int big(int a,int b,int mod){
    switch(mod){
        case 1: return (strcmp( views[a].name, views[b].name) > 0);
        case 2: return (strcmp( views[a].prov, views[b].prov) > 0);
        case 3: return        ( views[a].days> views[b].days)     ;
        case 4: return        ( views[a].piec> views[b].piec)     ;
    }
    return 0;
}
void exchange(int a,int b){
    strcpy( view0   .name, views[a].name);
    strcpy( view0   .prov, views[a].prov);
    strcpy( view0   .spec, views[a].spec);
    strcpy( view0   .traf, views[a].traf);
            view0   .days= views[a].days ;
            view0   .piec= views[a].piec ;
    strcpy( views[a].name, views[b].name);
    strcpy( views[a].prov, views[b].prov);
    strcpy( views[a].spec, views[b].spec);
    strcpy( views[a].traf, views[b].traf);
            views[a].days= views[b].days ;
            views[a].piec= views[b].piec ;
    strcpy( views[b].name, view0   .name);
    strcpy( views[b].prov, view0   .prov);
    strcpy( views[b].spec, view0   .spec);
    strcpy( views[b].traf, view0   .traf);
            views[b].days= view0   .days ;
            views[b].piec= view0   .piec ;
}
void create(){
    int m;
    system("cls");
    printf("������������������\n");
    scanf ("%d",&m);
    system("cls");
    printf("�밴���¸�ʽ�������ݣ�ÿ�����м��ÿո�ָ���\n");
    printf(TETILE);
    while (m--){
        scanf("%s %s %s %s %d %d",views[n].name,
                                  views[n].prov,
                                  views[n].spec,
                                  views[n].traf,
                                 &views[n].days,
                                 &views[n].piec);
        if(strlen(views[n].prov) < 5){
            views[n].prov[4] = views[n].prov[2];
            views[n].prov[5] = views[n].prov[3];
            views[n].prov[2] = ' ';
            views[n].prov[3] = ' ';
        }
        n++;
    }
    mainMenu();
}
void modify(){
    int m;
    char menu[][16] = {"�����޸�","�������˵�","�˳�ϵͳ"};
    system("cls");
    showViews();
    printf("������Ҫ�޸ĵ����ݱ��\n");
    scanf("%d",&m);
    if(m != 0){
        m--;
        system("cls");
        showViews();
        printf("������������(δ�Ķ�����ԭ������): \n");
        printf(TETILE);
        scanf("%s %s %s %s %d %d",views[m].name,
                                  views[m].prov,
                                  views[m].spec,
                                  views[m].traf,
                                  &views[m].days,
                                  &views[m].piec);
        if(strlen(views[n].prov) < 5){
            views[m].prov[4] = views[m].prov[2];
            views[m].prov[5] = views[m].prov[3];
            views[m].prov[2] = ' ';
            views[m].prov[3] = ' ';
        }
        system("cls");
        showViews();
    }
    else printf("��������\n");
    for(int i = 0;i < 2;i++){
        printf("*%d. %s\t                                                                                                *\n",i+1,menu[i]);
    }
    printf("*%d. %s\t                                                                                                *\n",0,menu[2]);
    modifyIntent();
}
void modifyIntent(){
    scanf("%d",&input);
    switch(input){
        case   1: modify();       break;
        case   2: mainMenu();     break;
        case   0: save();exit(0); break;
        default : printf("��������������\n"); modifyIntent();
    }
}
void query(){
    int m = 0;
    char search[100];
    char menu[][16] = {"������ѯ","�������˵�","�˳�ϵͳ"};
    system("cls");
    printf("������Ҫ��ѯ�Ĺؼ��֣�\n");
    scanf("%s",search);
    if(isint(search)){
        for(int i = 0;i < strlen(search);i++){
            m *= 10;
            m += search[i] - '0';
        }
        queryByInt(m);
    }
    else queryByStr(search);
    for(int i = 0;i < 2;i++){
        printf("*%d. %s\t                                                                                                *\n",i+1,menu[i]);
    }
    printf("*%d. %s\t                                                                                                *\n",0,menu[2]);
    queryIntent();
}
int isint(char *s){
    for(int i = 0;i < strlen(s);i++){
        if(s[i] < '0'||s[i] > '9'){
            return 0;
        }
    }
    return 1;
}
void queryByInt(int m){
    int num = 0;
    printf(TETILE);
    printf("��������\n");
    for(int i = 0;i < n;i++){
        if(views[i].days == m){
            num++;
            printf( "Case %d\t:",        i+1);
            printf( "%-23s",   views[i].name);
            printf( "%-16s",   views[i].prov);
            printf( "%-16s",   views[i].spec);
            printf( "%-16s",   views[i].traf);
            printf( "%-16d",   views[i].days);
            printf( "%-16d*\n",views[i].piec);
        }
    }
    if(num == 0) printf("û���ҵ����ʵ�����\n");
    putchar(10);
    num = 0;
    printf("���շѣ�\n");
    for(int i = 0;i < n;i++){
        if(views[i].piec == m){
            num++;
            printf( "Case %d\t:",        i+1);
            printf( "%-23s",   views[i].name);
            printf( "%-16s",   views[i].prov);
            printf( "%-16s",   views[i].spec);
            printf( "%-16s",   views[i].traf);
            printf( "%-16d",   views[i].days);
            printf( "%-16d*\n",views[i].piec);
        }
    }
    if(num == 0) printf("û���ҵ����ʵ�����\n");
    putchar(10);
}
void queryByStr(char *s){
    int num = 0;
    printf(TETILE);
    printf("�����ƣ�\n");
    for(int i = 0;i < n;i++){
        if(strstr(views[i].name,s) != NULL){
            num++;
            printf( "Case %d\t:",        i+1);
            printf( "%-23s",   views[i].name);
            printf( "%-16s",   views[i].prov);
            printf( "%-16s",   views[i].spec);
            printf( "%-16s",   views[i].traf);
            printf( "%-16d",   views[i].days);
            printf( "%-16d*\n",views[i].piec);
        }
    }
    if(num == 0) printf("û���ҵ����ʵ�����\n");
}
void queryIntent(){
    scanf("%d",&input);
    switch(input){
        case   1: query(0);       break;
        case   2: mainMenu();     break;
        case   0: save();exit(0); break;
        default : printf("��������������\n"); queryIntent();
    }
}
void help(){
    system("cls");
    printf(HELP);
    system("pause");
    mainMenu();
}
void delet(){
    int m,num;
    char menu[][16] = {"����ɾ��","�������˵�","�˳�ϵͳ"};
    system("cls");
    sort(1);
    showViews();
    printf("*****************************************************************************************************************\n");
    printf("������Ҫɾ�������ݱ�ţ�  ÿ������һ����  ����0����\n");
    num = n;
    while(1){
        if(~scanf("%d",&m)){
            if(m == 0) break;
            else if(m > n){
                printf("��������!\n");
                system("pause");
            }
            else {
                exchange(m-1,n-1);
                n--;
            }
        }
        else{
            if(n < num) n++;              //ctrl+z ����ɾ��
            else{
                printf("�Ѵ����������!\n");
                system("pause");
            }
        }
        system("cls");
        sort(1);
        showViews();
    }
    for(int i = 0;i < 2;i++){
        printf("*%d. %s\t                                                                                                *\n",i+1,menu[i]);
    }
    printf("*%d. %s\t                                                                                                *\n",0,menu[2]);
    deletIntent();
}
void deletIntent(){
    scanf("%d",&input);
    switch(input){
        case   1: delet();        break;
        case   2: mainMenu();     break;
        case   0: save();exit(0); break;
        default : printf("��������������\n"); deletIntent();
    }
}

/*
**��������
��������               ������          ʯ�Ͷ����      ����            90              998
����                 ������          ��              ����            1461            40000
����ʡ������Ժ       ����            ̰�ٶ�          ����            1095            0
����ɽ                 ����            ���Ӷ�          ���          12              2000
����ϴͷһƬ��ɫ��     ����            �ж�����û      ����            7               12
*/


/*
��������               ������          ʯ�Ͷ����      ����            90              998
����                 ������          ��              ����            1461            40000
����ʡ������Ժ       ����          ̰�ٶ�          ����            1095            0
����ɽ                 ����          ���Ӷ�          ���          7               233
����ɽ                 ����          ���Ӷ�          ���          12              2000
����ϴͷһƬ��ɫ��     ����          �ж�����û      ����            7               12
*/
