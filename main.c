#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define  DATA        "F:\\HomeworkData\\data.txt"
#define  TETILE      "---------景点名称--------------\t所在省---------\t特色-----------\t交通方式-------\t天数-----------\t收费标准--------*\t\n"
#define  HELP        "*********************************************** 帮助 ***********************************************\n操作说明：\n\t根据提示输入对应数字键并按下回车执行相应功能。\n\n数据文件路径：\n\tF:\\HomeworkData\\data.txt\n\t如不存在此文件且自动生成失败，请尝试手动建立此数据文件\n\n查询系统：\n\t本系统根据输入类型自动判断查询方式，可用的查询方式有：\n\t\tCase 1: 根据名称查询\n\t\tCase 2: 根据天数或收费查询\n****************************************************************************************************\n"

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
        printf("内容为空！\n");           //首字为'#'用于判断
        system("pause");
        mainMenu();
    }
    else load();
}
void load(){
    printf("*载入中...\n");
    system("cls");                        //清屏
    n = 0;
    while((ch = fgetc(fp)) != '#'){       //读取数据总数
        n *= 10;
        n += ch - '0';
    }
    //printf("*数据总数: %d\n",n);
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
    printf("*加载完成. . .\n");
    fclose(fp);
    //fp = fopen(DATA,"w");
    mainMenu();                          //跳转至主菜单
}
void save(){
    fp =  fopen(DATA,"w");
    char  str[20]   ;
    fputc ('#'  ,fp);
    itoa  (n,str,10);                      //int 转 字符串
    fputs (str  ,fp);
    fputc ('#'  ,fp);
    printf("保存中...\n");
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
    char menu[][8] = {"浏览","增加","修改","查询","删除","帮助","退出"};
    system("cls");
    printf("***************************************** 旅游信息管理系统 *****************************************\n");
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
        default : printf("输入有误，请重试\n"); mainIntent();
    }
}
void show(int mod){
    if(mod) sort(mod);
    char menu[][16] = {"按名称排序","按省份排序","按天数排序","按收费排序","返回主菜单","退出系统  "};
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
        default : printf("输入有误，请重试\n"); showIntent();
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
    printf("请输入新增数据条数\n");
    scanf ("%d",&m);
    system("cls");
    printf("请按如下格式输入数据，每两项中间用空格分隔：\n");
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
    char menu[][16] = {"继续修改","返回主菜单","退出系统"};
    system("cls");
    showViews();
    printf("请输入要修改的数据编号\n");
    scanf("%d",&m);
    if(m != 0){
        m--;
        system("cls");
        showViews();
        printf("请输入新数据(未改动数据原样输入): \n");
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
    else printf("输入有误\n");
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
        default : printf("输入有误，请重试\n"); modifyIntent();
    }
}
void query(){
    int m = 0;
    char search[100];
    char menu[][16] = {"继续查询","返回主菜单","退出系统"};
    system("cls");
    printf("请输入要查询的关键字：\n");
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
    printf("按天数：\n");
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
    if(num == 0) printf("没有找到合适的数据\n");
    putchar(10);
    num = 0;
    printf("按收费：\n");
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
    if(num == 0) printf("没有找到合适的数据\n");
    putchar(10);
}
void queryByStr(char *s){
    int num = 0;
    printf(TETILE);
    printf("按名称：\n");
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
    if(num == 0) printf("没有找到合适的数据\n");
}
void queryIntent(){
    scanf("%d",&input);
    switch(input){
        case   1: query(0);       break;
        case   2: mainMenu();     break;
        case   0: save();exit(0); break;
        default : printf("输入有误，请重试\n"); queryIntent();
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
    char menu[][16] = {"继续删除","返回主菜单","退出系统"};
    system("cls");
    sort(1);
    showViews();
    printf("*****************************************************************************************************************\n");
    printf("请输入要删除的数据编号，  每次输入一个，  输入0结束\n");
    num = n;
    while(1){
        if(~scanf("%d",&m)){
            if(m == 0) break;
            else if(m > n){
                printf("输入有误!\n");
                system("pause");
            }
            else {
                exchange(m-1,n-1);
                n--;
            }
        }
        else{
            if(n < num) n++;              //ctrl+z 撤销删除
            else{
                printf("已达最大撤销次数!\n");
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
        default : printf("输入有误，请重试\n"); deletIntent();
    }
}

/*
**测试数据
大庆油田               黑龙江          石油多湖多      高铁            90              998
哈理工                 黑龙江          无              地铁            1461            40000
汉东省人民检察院       汉东            贪官多          警车            1095            0
花果山                 江苏            猴子多          筋斗云          12              2000
上游洗头一片绿色城     王国            有恶龙出没      骑马            7               12
*/


/*
大庆油田               黑龙江          石油多湖多      高铁            90              998
哈理工                 黑龙江          无              地铁            1461            40000
汉东省人民检察院       汉东          贪官多          警车            1095            0
花果山                 江苏          猴子多          筋斗云          7               233
花果山                 江苏          猴子多          筋斗云          12              2000
上游洗头一片绿色城     王国          有恶龙出没      骑马            7               12
*/
