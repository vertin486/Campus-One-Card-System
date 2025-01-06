
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAXNUM 1000

//校园卡结构体相关定义
typedef struct SaveRecord{
    time_t datetime; // 使用time_t类型存储时间戳/
    double spendMoney; //充值金额
    struct SaveRecord *next;// 指向下一个充值记录的指针
}SaveRecord;

typedef struct SpendRecord{
    time_t datetime; // 使用time_t类型存储时间戳
    double spendMoney; //消费金额
    struct SpendRecord *next;// 指向下一个消费记录的指针
}SpendRecord;

typedef struct CARD{
    int cnum; //卡号
    char name[20]; //卡主人姓名
    SpendRecord* spend_records; // 校园卡的每次消费记录
    SaveRecord* save_records; // 校园卡的每次充值记录
    float cbalance; //存储卡余额
    int flag; //存储卡有效条件的值，0-有效，1-无效
} CARD;

CARD cards[MAXNUM]; // 使用数组存储校园卡信息
int count=0;

//主要函数声明
void disp_init(); //显示初始画面模块（完成）测试完成
int select_menu(); //显示菜单并输入功能选择（完成）测试完成
void addnew(); //创建新卡模块（完成）测试完成
void logout(); //注销模块（完成）测试完成
void modify(); //卡信息修改模块(完成) 测试完成
void readcard(); //消费模块(完成)   测试完成
void savemoney(); //充值模块(完成)  测试完成
void inquiry(); //查询卡信息模块（完成）  测试完成
void initfromfile(CARD cards[],int *num_cards); //从文件初始化校园卡管理系统的功能  （完成）测试完成
void exitout(); //退出模块（完成）  测试完成

//辅助函数声明
int findcard(CARD cards[ ],int cardnumber); //查询卡号（完成）
void display(CARD cards[ ],int index); //显示单张一卡通信息(完成)
void muchsortspend(SpendRecord* head);//按金额排序的消费记录（完成）
void muchsortsave(SaveRecord* head);//按金额排序的充值记录 （完成）
int compare_money(double a, double b);// 比较金额的函数 （完成）
int length(struct SpendRecord* head);// 计算链表长度的函数  （完成）
void swapRecords(SpendRecord* a, SpendRecord* b) ;// 交换记录的函数（完成）
void displayspend(SpendRecord* head) ;//显示消费记录（完成）
void displaysave(SaveRecord* head); //显示充值记录（完成）
void displayall(CARD cards[],int index);// 显示所有卡信息(完成)

//主函数
int main(){
    int choose=0;
    disp_init();
    while (choose!=8)
    {
        choose=select_menu();
        switch (choose){
            case 1:
                addnew();//添加新卡
                break;

            case 2:
                logout();//注销卡
                break;

            case 3:
                modify();//修改卡信息
                break;

            case 4:
                readcard();//消费
                break;

            case 5:
                savemoney();//充值
                break;

            case 6:
                inquiry();//查询卡信息
                break;

            case 7:
                initfromfile(cards,&count);//从文件初始化校园卡管理系统的功能
                break;
            case 8:
                exitout();//退出模块
                break;

            default:
                printf("输入错误，请重新输入！\n");
        }
    }
    return 0;
}

//函数定义
void disp_init()// 显示初始画面模块
{
    printf("+----------------------------------------------------+\n");
    printf("|             欢迎使用校园一卡通管理系统！           |\n");
    printf("+----------------------------------------------------+\n");
}

int select_menu()// 显示菜单并输入功能选择
{
    int a;
    printf("+----------------------------------------------------+\n");
    printf("| 1. 新建卡功能                                      |\n");
    printf("| 2. 注销卡功能                                      |\n");
    printf("| 3. 卡信息修改功能                                  |\n");
    printf("| 4. 消费功能                                        |\n");
    printf("| 5. 充值功能                                        |\n");
    printf("| 6. 卡信息查询功能                                  |\n");
    printf("| 7. 从其他指定文件初始化校园卡管理系统的功能        |\n");
    printf("| 8. 退出功能                                        |\n");
    printf("+----------------------------------------------------+\n");
    printf("请选择：");
    scanf("%d",&a);
    return a;
}

void addnew() {
    int i=0;
    int j=0;
    int tool=0;//用于是否有重复卡号的标志变量
    for (i = 0; i < MAXNUM; i++) {
        if (cards[i].cnum == 0) { // 找到空位
            break;
        }
    }
    if (i >= MAXNUM) {
        printf("卡已满，无法添加新卡！\n");
        return;
    }
    while (1) {
        printf("请输入卡号：");
        scanf("%d", &cards[i].cnum);
        while (getchar() != '\n'); // 清除输入缓冲区直到行尾

        if (cards[i].cnum < 0) {
            printf("卡号不能为负数，请重新输入:\n");
            continue;
        }
        tool = 0;// 重置标志变量
        for (int j = 0; j < MAXNUM; j++) {// 检查卡号是否已存在
            if (cards[j].cnum == cards[i].cnum && j != i) {// 找到重复卡号
                printf("该卡号已被占用，请重新输入！\n");
                tool=1;// 标记为已存在
                break;
            }else{
                tool=0;
            }
        }
        if (tool == 1) {// 标记为已存在，重新输入
            continue;
        }

        printf("请输入姓名(不超过20个字符)：");
        scanf("%s", cards[i].name);
        while (getchar() != '\n'); // 清除输入缓冲区直到行尾

        if (strlen(cards[i].name) > 20) {
            printf("名字不能超过20个字符\n");
            continue;
        }

        printf("请输入余额：");
        scanf("%f", &cards[i].cbalance);
        while (getchar() != '\n'); // 清除输入缓冲区直到行尾

        if (cards[i].cbalance < 0) {
            printf("余额不能为负数，请重新输入:\n");
            continue;
        }

        cards[i].flag = 0; // 标记为有效卡
        cards[i].spend_records = NULL; // 初始化消费记录链表
        cards[i].save_records = NULL; // 初始化充值记录链表
        printf("添加成功！\n");
        count++;// 卡数量加1
        display(cards,i);
        return; // 成功后退出函数
    }
}

void logout()// 注销模块
{
    int cardnumber;
    printf("请输入要注销的卡号：");
    scanf("%d",&cardnumber);
    while (getchar() != '\n');

    if(findcard(cards,cardnumber)==-1)//判断卡号是否存在，-1为不存在
    {
        printf("该卡号不存在！\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (cards[i].cnum == cardnumber) {
            cards[i].flag = 1; // 将有效值设置为1，表示注销
            printf("注销成功！\n");
            return;
        }
    }
    printf("该卡号不存在！\n");
}

void modify()// 卡信息修改模块
{
    int cardnumber,tool=0;
    printf("请输入要修改的卡号：");
    scanf("%d",&cardnumber);
    if(findcard(cards,cardnumber)==-1)
    {
        printf("该卡号不存在！\n");
        return;
    }
    for(int i=0;i<MAXNUM;i++)
    {
        if(cardnumber==cards[i].cnum)
        {   
            while(1)
           {
            printf("请输入新卡号：");
            scanf("%d", &cards[i].cnum);
            while (getchar() != '\n'); // 清除输入缓冲区直到行尾

            if (cards[i].cnum < 0) {
            printf("卡号不能为负数，请重新输入:\n");
            continue;
        }
        tool = 0;// 重置标志变量
        for (int j = 0; j < MAXNUM; j++) // 检查卡号是否已存在
        {
            if (cards[j].cnum == cards[i].cnum && j != i) {// 找到重复卡号
                printf("该卡号已被占用，请重新输入！\n");
                tool=1;// 标记为已存在
                break;
            }else{
                tool=0;
            }
        }
        if (tool == 1) {// 标记为已存在，重新输入
            continue;
        }

        printf("请输入姓名(不超过20个字符)：");
        scanf("%s", cards[i].name);
        while (getchar() != '\n'); // 清除输入缓冲区直到行尾

        if (strlen(cards[i].name) > 20) {
            printf("名字不能超过20个字符\n");
            continue;
        }
            printf("修改成功！\n");
            display(cards,i);
            return;
           }
        }
    }
}

int findcard(CARD cards[ ],int cardnumber )// 查找卡号
{
    int i;
    for (i=0;i<count;i++)
   {
     if (cards[i].cnum==cardnumber&&cards[i].flag==0)// 输入卡号=已存在卡号，并且有效
    {
        return 1;// 找到卡号
    }
   }
    return -1;// 未找到卡号
 }

void inquiry()//查询卡信息模块
{   
    int cardnumber,i=0;
    displayall(cards,i);
    printf("请输入要查询的卡号：");
    scanf("%d",&cardnumber);
    while (getchar() != '\n'); // 清除输入缓冲区直到行尾

    if(findcard(cards,cardnumber)==-1)
    {
        printf("该卡号不存在！\n");
        return;
    }

    printf("请选择查询信息：\n");
    printf("1. 卡号基本信息\n");
    printf("2. 消费记录\n");
    printf("3. 充值记录\n");

    int choice;
    scanf("%d",&choice);
    switch (choice) {
        case 1:
            display(cards,i);
            break;

        case 2:
        printf("请选择消费记录的排序方式：\n");
        printf("1. 按时间先后排序\n");
        printf("2. 按消费金额大小排序\n");
        scanf("%d",&choice);

            if (choice == 1) {
           displayspend(cards[i].spend_records);
        } else if (choice == 2) {
            muchsortspend(cards[i].spend_records);
            displayspend(cards[i].spend_records);
        }
            break;

        case 3:
        printf("请选择充值记录的排序方式：\n");
        printf("1. 按时间先后排序\n");
        printf("2. 按充值金额大小排序\n");
        scanf("%d",&choice);
        
            if (choice == 1) {
            displaysave(cards[i].save_records);
            } else if (choice == 2) {
                muchsortsave(cards[i].save_records);
                displaysave(cards[i].save_records);
            }
           
            break;

        default:
            printf("输入错误，请重新输入！\n");
            break;
    }

}
void savemoney()//充值模块
{   double money;
    int cardnumber;
    printf("请输入要充值的卡号：");
    scanf("%d",&cardnumber);
    if(findcard(cards,cardnumber)==-1)
    {
        printf("该卡号不存在！\n");
        return;
    }
    for(int i=0;i<count;i++)
    {
        if(cardnumber==cards[i].cnum)// 找到卡号
        {
            printf("请输入充值金额：");
            scanf("%lf",&money);
            getchar();
            if(money<0)
            {
                printf("充值金额不能为负数！\n");
                continue;
            }
            cards[i].cbalance+=money;

            // 创建新的充值记录节点
            SaveRecord *newRecord = (SaveRecord *)malloc(sizeof(SaveRecord));
            if (newRecord == NULL)
            {
                printf("内存分配失败！\n");
                return;
            }

            time(&newRecord->datetime); // 获取当前时间
            newRecord->spendMoney = money;// 充值金额
            newRecord->next = NULL;// 新记录的下一个指针为NULL

            // 将新记录插入到充值记录链表的头部
            if (cards[i].save_records == NULL)//检查校园卡的充值记录链表是否为空
            {
                cards[i].save_records = newRecord;//将新节点的地址当作校园卡的充值记录链表的头指针
            }
            else
            {
                newRecord->next = cards[i].save_records;//将新节点的地址赋给新记录的下一个指针
                cards[i].save_records = newRecord;//更新cards[i].save_records指针，
                //使其指向新节点newRecord，成为了链表新的头节点。
            }

            printf("充值成功！\n");
            display(cards,i);// 显示卡信息
            return;

          
        }
    }
}
    
void readcard()//消费模块
{   double money;
    int cardnumber;
    printf("请输入要消费的卡号：");
    scanf("%d",&cardnumber);
    if(findcard(cards,cardnumber)==-1)
    {
        printf("该卡号不存在！\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        if (cardnumber == cards[i].cnum)
        {
            printf("请输入消费金额：");
            scanf("%lf", &money);
            getchar();
            if(money<0)
            {
                printf("消费金额不能为负数！\n");
                continue;
            }
            
            if(cards[i].cbalance<money)
            {
                printf("余额不足！\n");
                return;
            }
            cards[i].cbalance-=money;

            // 创建新的消费记录节点
            SpendRecord *newRecord = (SpendRecord *)malloc(sizeof(SpendRecord));//为新节点分配内存 
            if (newRecord == NULL)//检查内存分配是否成功
            {
                printf("内存分配失败！\n");
                return;
            }
            time(&newRecord->datetime);// 获取当前时间
            newRecord->spendMoney = money;// 充值金额
            newRecord->next = NULL;// 新记录的下一个指针为NULL

            // 将新记录插入到充值记录链表的头部
            if (cards[i].spend_records == NULL)
            {
                cards[i].spend_records = newRecord;//将新节点的地址赋给校园卡的充值记录链表的头指针
            }
            else
            {
                newRecord->next = cards[i].spend_records;//将新节点的地址赋给校园卡的充值记录链表的头指针的下一个指针
                cards[i].spend_records = newRecord;//更新cards[i].spend_records指针，
                //使其指向新节点newRecord，成为了链表新的头节点。
            }

            printf("消费成功！\n");
            display(cards,i);
           
            return;
           
           
        }
    }
 }                                                          

void display(CARD cards[],int index)//显示单张或多张一卡通信息
{
     if (index < 0 || index >= MAXNUM) {
        printf("索引超出范围。\n");
        return;
    }

     // 显示基本信息
    printf("\n\t |==== ======== ========== ==========|\n");
    printf("\t |卡号 姓名     充值金额     卡余额 \n|");//最近一次充值金额记录展示，
    printf("\t |----+--------+----------+----------|\n");
    printf("\t |%4d %8s  %6.2f    %6.2f    |\n", cards[index].cnum, cards[index].name, 
           (cards[index].save_records != NULL ? cards[index].save_records->spendMoney : 0), cards[index].cbalance);
           //检查校园卡的充值记录链表是否为空。如果不为空，说明有充值记录。
           //如果有充值记录，获取最近一次充值的金额。
    printf("\t +==== ======== ========== ==========+\n");
    }
// 计算链表长度的函数
int lengthList(struct SpendRecord* head)
{
    int count = 0;
    struct SpendRecord* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
// 比较金额的函数
int compare_money(double a, double b) {
    return a > b; // 如果a大于b，返回1，否则返回0
}
// 交换记录的函数
void swapRecords(SpendRecord* a, SpendRecord* b) {
    double temp_money = a->spendMoney;//按金额排序
    a->spendMoney = b->spendMoney;
    b->spendMoney = temp_money;
}


void muchsortspend(SpendRecord* head) {// 按金额从小到大排序的消费记录
    int length = lengthList(head);// 获取链表长度
    for (int i = 0; i < length - 1; i++) {// 外层循环控制排序轮数
        for (int j = 0; j < length - i - 1; j++) {// 内层循环控制每轮比较次数
            SpendRecord* current = head;// 找到当前节点
            for (int k = 0; k < j; k++) {// 这个循环将current指针移动到第j+1个节点，
                //因为内层循环的索引j是从0开始的，而我们需要比较的是第j+1个节点和第j+2个节点
                current = current->next;
            }
            SpendRecord* next = current->next;
            if (compare_money(current->spendMoney, next->spendMoney)) {
                swapRecords(current, next);
            }
        }
    }
}
void muchsortsave(SaveRecord* head) {// 按金额从小到大排序的充值记录
    int length = lengthList(head); 
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            SaveRecord* current = head;
            for (int k = 0; k < j; k++) {
                current = current->next;
            }
            SaveRecord* next = current->next;
            if (compare_money(current->spendMoney, next->spendMoney)) {
                swapRecords(current, next); 
            }
        }
    }
}

void displayspend(SpendRecord* head) //显示消费记录
{
    printf("\n\t |==== ======== =========== =========|\n");
    printf("\t |消费时间                消费金额   |\n|");
    for(SpendRecord* p=head; p!=NULL; p=p->next)// 遍历链表
    {
        char timeStr[20]; // 创建一个足够大的缓冲区来存储格式化的时间字符串
        // 使用 strftime 函数将 time_t 类型的时间戳转换为指定格式的字符串
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
        printf("\t |%s %10.2f     |\n", timeStr, p->spendMoney); // 输出格式化的时间和金额，确保金额字段宽度一致
    }
    printf("\t |----+------------+----------+------|\n");
}
   
void displaysave(SaveRecord* head) //显示充值记录
{
    printf("\n\t |==== ======== =========== =========|\n");
    printf("\t |充值时间                充值金额   |\n|");
    for(SaveRecord* p=head; p!=NULL; p=p->next)// 遍历链表
    {
        char timeStr[20]; // 创建一个足够大的缓冲区来存储格式化的时间字符串
        // 使用 strftime 函数将 time_t 类型的时间戳转换为指定格式的字符串
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
       printf("\t |%s %10.2f     |\n", timeStr, p->spendMoney); // 输出格式化的时间和金额，确保金额字段宽度一致
    }
    printf("\t |----+------------+----------+------|\n");
}

void displayall(CARD cards[],int index)//显示单张或多张一卡通信息
{
     if (index < 0 || index >= MAXNUM) {
        printf("索引超出范围。\n");
        return;
    }

// 显示基本信息
    for(index=0;index<count;index++)
    { 
        if(cards[index].flag==1)
    {
        continue;
    }
    printf("\n\t |==== ======== ========== ==========|\n");
    printf("\t |卡号 姓名     充值金额     卡余额 \n|");
    printf("\t |----+--------+----------+----------|\n");
    printf("\t |%4d %8s  %6.2f    %6.2f    |\n", cards[index].cnum, cards[index].name, 
           (cards[index].save_records != NULL ? cards[index].save_records->spendMoney : 0), cards[index].cbalance);
           //检查校园卡的充值记录链表是否为空。如果不为空，说明有充值记录。
           //如果有充值记录，获取最近一次充值的金额。
    }
    printf("\t +==== ======== ========== ==========+\n");
    }



void exitout() // 退出系统并保存卡信息、消费记录和充值记录到文件
{   
    FILE *fp; // 文件指针
    // 尝试打开文件，如果文件不存在则创建
    fp = fopen("C:\\Users\\Vertin\\Desktop\\c语言实训项目\\card_info.txt", "w+");
    if (fp == NULL) {
        printf("无法打开文件\n");
        exit(1); // 如果文件打开失败，则退出程序
    }
   
    //写入卡信息到文件
    for (int index = 0; index < MAXNUM; index++) {
        if (cards[index].cnum != 0 && cards[index].flag == 0) { // 只写入有效卡的信息
            fprintf(fp, "卡号: %d, 姓名: %s, 余额: %.2f\n", cards[index].cnum, cards[index].name, cards[index].cbalance);
            
            // 写入消费记录
            fprintf(fp, "消费记录:\n");
            for (SpendRecord *p = cards[index].spend_records; p != NULL; p = p->next) {
                char timeStr[20];
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
                fprintf(fp, "时间: %s, 消费金额: %.2f\n", timeStr, p->spendMoney);
            }

            // 写入充值记录
            fprintf(fp, "充值记录:\n");
            for (SaveRecord *p = cards[index].save_records; p != NULL; p = p->next) {
                char timeStr[20];
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
                fprintf(fp, "时间: %s, 充值金额: %.2f\n", timeStr, p->spendMoney);
            }

            fprintf(fp, "\n"); // 每个卡的信息之后添加一个空行以分隔
        }
    }

    //关闭文件
    fclose(fp);

    printf("感谢使用！\n");
    exit(0);
}

void initfromfile(CARD cards[], int *num_cards) {//初始化结构体数组
    FILE *file = fopen("C:\\Users\\Vertin\\Desktop\\c语言实训项目\\card_info.txt", "r");
    if (file == NULL) {
        perror("无法打开文件");
        exit(1);
    }

    *num_cards = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "卡号:", 4) == 0) {
            // Parse card information
            if (sscanf(line, "卡号: %d, 姓名: %[^,], 余额: %f", &cards[*num_cards].cnum, cards[*num_cards].name, &cards[*num_cards].cbalance) == 3) {
                cards[*num_cards].flag = 0;
                cards[*num_cards].spend_records = NULL;
                cards[*num_cards].save_records = NULL;
                (*num_cards)++;
            }
        } else if (strncmp(line, "时间:", 4) == 0) {
            // Parse spend or save record
            double amount;
            char timeStr[20];
            struct tm tm;// 定义<time.h> 头文件中表示日期和时间的结构体变量
            memset(&tm, 0, sizeof(tm));
            if (sscanf(line, "时间: %[^,], 消费金额: %lf", timeStr, &amount) == 2) {
                sscanf(timeStr, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
                tm.tm_year -= 1900; // struct tm 中年份从1900年开始计数
                tm.tm_mon -= 1;     // struct tm 中月份从0开始计数
                time_t time = mktime(&tm);//将 struct tm 结构体转换为 time_t 时间戳。
                SpendRecord *newSpend = (SpendRecord *)malloc(sizeof(SpendRecord));
                newSpend->datetime = time;
                newSpend->spendMoney = amount;
                newSpend->next = cards[*num_cards - 1].spend_records;
                cards[*num_cards - 1].spend_records = newSpend;
                
            } else if (sscanf(line, "时间: %[^,], 充值金额: %lf", timeStr, &amount) == 2) {
                sscanf(timeStr, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
                tm.tm_year -= 1900; // struct tm 中年份从1900年开始计数
                tm.tm_mon -= 1;     // struct tm 中月份从0开始计数
                time_t time = mktime(&tm);
                SaveRecord *newSave = (SaveRecord *)malloc(sizeof(SaveRecord));
                newSave->datetime = time;
                newSave->spendMoney = amount;
                newSave->next = cards[*num_cards - 1].save_records;
                cards[*num_cards - 1].save_records = newSave;
            }
        }
    }

    fclose(file);
    printf("从文件中读取了 %d 张卡的信息。\n", *num_cards);
    printf("初始化完毕。\n");
}
//%[^,] 是 sscanf 函数中的一个格式说明符，用于从输入字符串中读取字符，直到遇到逗号 , 为止。
//这个格式说明符通常用于读取字符串，其中 ^ 符号表示“除了”或“直到”的意思。
// 具体来说，%[^,] 的含义如下：
// %：表示格式说明符的开始。
// [：表示字符集的开始。
// ^：表示取反，即读取除了指定字符集之外的所有字符。
// ,]：指定字符集，这里是逗号 ,，表示读取直到遇到逗号为止。
// ]：表示字符集的结束。
















