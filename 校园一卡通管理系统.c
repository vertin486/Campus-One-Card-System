
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAXNUM 1000

//У԰���ṹ����ض���
typedef struct SaveRecord{
    time_t datetime; // ʹ��time_t���ʹ洢ʱ���/
    double spendMoney; //��ֵ���
    struct SaveRecord *next;// ָ����һ����ֵ��¼��ָ��
}SaveRecord;

typedef struct SpendRecord{
    time_t datetime; // ʹ��time_t���ʹ洢ʱ���
    double spendMoney; //���ѽ��
    struct SpendRecord *next;// ָ����һ�����Ѽ�¼��ָ��
}SpendRecord;

typedef struct CARD{
    int cnum; //����
    char name[20]; //����������
    SpendRecord* spend_records; // У԰����ÿ�����Ѽ�¼
    SaveRecord* save_records; // У԰����ÿ�γ�ֵ��¼
    float cbalance; //�洢�����
    int flag; //�洢����Ч������ֵ��0-��Ч��1-��Ч
} CARD;

CARD cards[MAXNUM]; // ʹ������洢У԰����Ϣ
int count=0;

//��Ҫ��������
void disp_init(); //��ʾ��ʼ����ģ�飨��ɣ��������
int select_menu(); //��ʾ�˵������빦��ѡ����ɣ��������
void addnew(); //�����¿�ģ�飨��ɣ��������
void logout(); //ע��ģ�飨��ɣ��������
void modify(); //����Ϣ�޸�ģ��(���) �������
void readcard(); //����ģ��(���)   �������
void savemoney(); //��ֵģ��(���)  �������
void inquiry(); //��ѯ����Ϣģ�飨��ɣ�  �������
void initfromfile(CARD cards[],int *num_cards); //���ļ���ʼ��У԰������ϵͳ�Ĺ���  ����ɣ��������
void exitout(); //�˳�ģ�飨��ɣ�  �������

//������������
int findcard(CARD cards[ ],int cardnumber); //��ѯ���ţ���ɣ�
void display(CARD cards[ ],int index); //��ʾ����һ��ͨ��Ϣ(���)
void muchsortspend(SpendRecord* head);//�������������Ѽ�¼����ɣ�
void muchsortsave(SaveRecord* head);//���������ĳ�ֵ��¼ ����ɣ�
int compare_money(double a, double b);// �ȽϽ��ĺ��� ����ɣ�
int length(struct SpendRecord* head);// ���������ȵĺ���  ����ɣ�
void swapRecords(SpendRecord* a, SpendRecord* b) ;// ������¼�ĺ�������ɣ�
void displayspend(SpendRecord* head) ;//��ʾ���Ѽ�¼����ɣ�
void displaysave(SaveRecord* head); //��ʾ��ֵ��¼����ɣ�
void displayall(CARD cards[],int index);// ��ʾ���п���Ϣ(���)

//������
int main(){
    int choose=0;
    disp_init();
    while (choose!=8)
    {
        choose=select_menu();
        switch (choose){
            case 1:
                addnew();//����¿�
                break;

            case 2:
                logout();//ע����
                break;

            case 3:
                modify();//�޸Ŀ���Ϣ
                break;

            case 4:
                readcard();//����
                break;

            case 5:
                savemoney();//��ֵ
                break;

            case 6:
                inquiry();//��ѯ����Ϣ
                break;

            case 7:
                initfromfile(cards,&count);//���ļ���ʼ��У԰������ϵͳ�Ĺ���
                break;
            case 8:
                exitout();//�˳�ģ��
                break;

            default:
                printf("����������������룡\n");
        }
    }
    return 0;
}

//��������
void disp_init()// ��ʾ��ʼ����ģ��
{
    printf("+----------------------------------------------------+\n");
    printf("|             ��ӭʹ��У԰һ��ͨ����ϵͳ��           |\n");
    printf("+----------------------------------------------------+\n");
}

int select_menu()// ��ʾ�˵������빦��ѡ��
{
    int a;
    printf("+----------------------------------------------------+\n");
    printf("| 1. �½�������                                      |\n");
    printf("| 2. ע��������                                      |\n");
    printf("| 3. ����Ϣ�޸Ĺ���                                  |\n");
    printf("| 4. ���ѹ���                                        |\n");
    printf("| 5. ��ֵ����                                        |\n");
    printf("| 6. ����Ϣ��ѯ����                                  |\n");
    printf("| 7. ������ָ���ļ���ʼ��У԰������ϵͳ�Ĺ���        |\n");
    printf("| 8. �˳�����                                        |\n");
    printf("+----------------------------------------------------+\n");
    printf("��ѡ��");
    scanf("%d",&a);
    return a;
}

void addnew() {
    int i=0;
    int j=0;
    int tool=0;//�����Ƿ����ظ����ŵı�־����
    for (i = 0; i < MAXNUM; i++) {
        if (cards[i].cnum == 0) { // �ҵ���λ
            break;
        }
    }
    if (i >= MAXNUM) {
        printf("���������޷�����¿���\n");
        return;
    }
    while (1) {
        printf("�����뿨�ţ�");
        scanf("%d", &cards[i].cnum);
        while (getchar() != '\n'); // ������뻺����ֱ����β

        if (cards[i].cnum < 0) {
            printf("���Ų���Ϊ����������������:\n");
            continue;
        }
        tool = 0;// ���ñ�־����
        for (int j = 0; j < MAXNUM; j++) {// ��鿨���Ƿ��Ѵ���
            if (cards[j].cnum == cards[i].cnum && j != i) {// �ҵ��ظ�����
                printf("�ÿ����ѱ�ռ�ã����������룡\n");
                tool=1;// ���Ϊ�Ѵ���
                break;
            }else{
                tool=0;
            }
        }
        if (tool == 1) {// ���Ϊ�Ѵ��ڣ���������
            continue;
        }

        printf("����������(������20���ַ�)��");
        scanf("%s", cards[i].name);
        while (getchar() != '\n'); // ������뻺����ֱ����β

        if (strlen(cards[i].name) > 20) {
            printf("���ֲ��ܳ���20���ַ�\n");
            continue;
        }

        printf("��������");
        scanf("%f", &cards[i].cbalance);
        while (getchar() != '\n'); // ������뻺����ֱ����β

        if (cards[i].cbalance < 0) {
            printf("����Ϊ����������������:\n");
            continue;
        }

        cards[i].flag = 0; // ���Ϊ��Ч��
        cards[i].spend_records = NULL; // ��ʼ�����Ѽ�¼����
        cards[i].save_records = NULL; // ��ʼ����ֵ��¼����
        printf("��ӳɹ���\n");
        count++;// ��������1
        display(cards,i);
        return; // �ɹ����˳�����
    }
}

void logout()// ע��ģ��
{
    int cardnumber;
    printf("������Ҫע���Ŀ��ţ�");
    scanf("%d",&cardnumber);
    while (getchar() != '\n');

    if(findcard(cards,cardnumber)==-1)//�жϿ����Ƿ���ڣ�-1Ϊ������
    {
        printf("�ÿ��Ų����ڣ�\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (cards[i].cnum == cardnumber) {
            cards[i].flag = 1; // ����Чֵ����Ϊ1����ʾע��
            printf("ע���ɹ���\n");
            return;
        }
    }
    printf("�ÿ��Ų����ڣ�\n");
}

void modify()// ����Ϣ�޸�ģ��
{
    int cardnumber,tool=0;
    printf("������Ҫ�޸ĵĿ��ţ�");
    scanf("%d",&cardnumber);
    if(findcard(cards,cardnumber)==-1)
    {
        printf("�ÿ��Ų����ڣ�\n");
        return;
    }
    for(int i=0;i<MAXNUM;i++)
    {
        if(cardnumber==cards[i].cnum)
        {   
            while(1)
           {
            printf("�������¿��ţ�");
            scanf("%d", &cards[i].cnum);
            while (getchar() != '\n'); // ������뻺����ֱ����β

            if (cards[i].cnum < 0) {
            printf("���Ų���Ϊ����������������:\n");
            continue;
        }
        tool = 0;// ���ñ�־����
        for (int j = 0; j < MAXNUM; j++) // ��鿨���Ƿ��Ѵ���
        {
            if (cards[j].cnum == cards[i].cnum && j != i) {// �ҵ��ظ�����
                printf("�ÿ����ѱ�ռ�ã����������룡\n");
                tool=1;// ���Ϊ�Ѵ���
                break;
            }else{
                tool=0;
            }
        }
        if (tool == 1) {// ���Ϊ�Ѵ��ڣ���������
            continue;
        }

        printf("����������(������20���ַ�)��");
        scanf("%s", cards[i].name);
        while (getchar() != '\n'); // ������뻺����ֱ����β

        if (strlen(cards[i].name) > 20) {
            printf("���ֲ��ܳ���20���ַ�\n");
            continue;
        }
            printf("�޸ĳɹ���\n");
            display(cards,i);
            return;
           }
        }
    }
}

int findcard(CARD cards[ ],int cardnumber )// ���ҿ���
{
    int i;
    for (i=0;i<count;i++)
   {
     if (cards[i].cnum==cardnumber&&cards[i].flag==0)// ���뿨��=�Ѵ��ڿ��ţ�������Ч
    {
        return 1;// �ҵ�����
    }
   }
    return -1;// δ�ҵ�����
 }

void inquiry()//��ѯ����Ϣģ��
{   
    int cardnumber,i=0;
    displayall(cards,i);
    printf("������Ҫ��ѯ�Ŀ��ţ�");
    scanf("%d",&cardnumber);
    while (getchar() != '\n'); // ������뻺����ֱ����β

    if(findcard(cards,cardnumber)==-1)
    {
        printf("�ÿ��Ų����ڣ�\n");
        return;
    }

    printf("��ѡ���ѯ��Ϣ��\n");
    printf("1. ���Ż�����Ϣ\n");
    printf("2. ���Ѽ�¼\n");
    printf("3. ��ֵ��¼\n");

    int choice;
    scanf("%d",&choice);
    switch (choice) {
        case 1:
            display(cards,i);
            break;

        case 2:
        printf("��ѡ�����Ѽ�¼������ʽ��\n");
        printf("1. ��ʱ���Ⱥ�����\n");
        printf("2. �����ѽ���С����\n");
        scanf("%d",&choice);

            if (choice == 1) {
           displayspend(cards[i].spend_records);
        } else if (choice == 2) {
            muchsortspend(cards[i].spend_records);
            displayspend(cards[i].spend_records);
        }
            break;

        case 3:
        printf("��ѡ���ֵ��¼������ʽ��\n");
        printf("1. ��ʱ���Ⱥ�����\n");
        printf("2. ����ֵ����С����\n");
        scanf("%d",&choice);
        
            if (choice == 1) {
            displaysave(cards[i].save_records);
            } else if (choice == 2) {
                muchsortsave(cards[i].save_records);
                displaysave(cards[i].save_records);
            }
           
            break;

        default:
            printf("����������������룡\n");
            break;
    }

}
void savemoney()//��ֵģ��
{   double money;
    int cardnumber;
    printf("������Ҫ��ֵ�Ŀ��ţ�");
    scanf("%d",&cardnumber);
    if(findcard(cards,cardnumber)==-1)
    {
        printf("�ÿ��Ų����ڣ�\n");
        return;
    }
    for(int i=0;i<count;i++)
    {
        if(cardnumber==cards[i].cnum)// �ҵ�����
        {
            printf("�������ֵ��");
            scanf("%lf",&money);
            getchar();
            if(money<0)
            {
                printf("��ֵ����Ϊ������\n");
                continue;
            }
            cards[i].cbalance+=money;

            // �����µĳ�ֵ��¼�ڵ�
            SaveRecord *newRecord = (SaveRecord *)malloc(sizeof(SaveRecord));
            if (newRecord == NULL)
            {
                printf("�ڴ����ʧ�ܣ�\n");
                return;
            }

            time(&newRecord->datetime); // ��ȡ��ǰʱ��
            newRecord->spendMoney = money;// ��ֵ���
            newRecord->next = NULL;// �¼�¼����һ��ָ��ΪNULL

            // ���¼�¼���뵽��ֵ��¼�����ͷ��
            if (cards[i].save_records == NULL)//���У԰���ĳ�ֵ��¼�����Ƿ�Ϊ��
            {
                cards[i].save_records = newRecord;//���½ڵ�ĵ�ַ����У԰���ĳ�ֵ��¼�����ͷָ��
            }
            else
            {
                newRecord->next = cards[i].save_records;//���½ڵ�ĵ�ַ�����¼�¼����һ��ָ��
                cards[i].save_records = newRecord;//����cards[i].save_recordsָ�룬
                //ʹ��ָ���½ڵ�newRecord����Ϊ�������µ�ͷ�ڵ㡣
            }

            printf("��ֵ�ɹ���\n");
            display(cards,i);// ��ʾ����Ϣ
            return;

          
        }
    }
}
    
void readcard()//����ģ��
{   double money;
    int cardnumber;
    printf("������Ҫ���ѵĿ��ţ�");
    scanf("%d",&cardnumber);
    if(findcard(cards,cardnumber)==-1)
    {
        printf("�ÿ��Ų����ڣ�\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        if (cardnumber == cards[i].cnum)
        {
            printf("���������ѽ�");
            scanf("%lf", &money);
            getchar();
            if(money<0)
            {
                printf("���ѽ���Ϊ������\n");
                continue;
            }
            
            if(cards[i].cbalance<money)
            {
                printf("���㣡\n");
                return;
            }
            cards[i].cbalance-=money;

            // �����µ����Ѽ�¼�ڵ�
            SpendRecord *newRecord = (SpendRecord *)malloc(sizeof(SpendRecord));//Ϊ�½ڵ�����ڴ� 
            if (newRecord == NULL)//����ڴ�����Ƿ�ɹ�
            {
                printf("�ڴ����ʧ�ܣ�\n");
                return;
            }
            time(&newRecord->datetime);// ��ȡ��ǰʱ��
            newRecord->spendMoney = money;// ��ֵ���
            newRecord->next = NULL;// �¼�¼����һ��ָ��ΪNULL

            // ���¼�¼���뵽��ֵ��¼�����ͷ��
            if (cards[i].spend_records == NULL)
            {
                cards[i].spend_records = newRecord;//���½ڵ�ĵ�ַ����У԰���ĳ�ֵ��¼�����ͷָ��
            }
            else
            {
                newRecord->next = cards[i].spend_records;//���½ڵ�ĵ�ַ����У԰���ĳ�ֵ��¼�����ͷָ�����һ��ָ��
                cards[i].spend_records = newRecord;//����cards[i].spend_recordsָ�룬
                //ʹ��ָ���½ڵ�newRecord����Ϊ�������µ�ͷ�ڵ㡣
            }

            printf("���ѳɹ���\n");
            display(cards,i);
           
            return;
           
           
        }
    }
 }                                                          

void display(CARD cards[],int index)//��ʾ���Ż����һ��ͨ��Ϣ
{
     if (index < 0 || index >= MAXNUM) {
        printf("����������Χ��\n");
        return;
    }

     // ��ʾ������Ϣ
    printf("\n\t |==== ======== ========== ==========|\n");
    printf("\t |���� ����     ��ֵ���     ����� \n|");//���һ�γ�ֵ����¼չʾ��
    printf("\t |----+--------+----------+----------|\n");
    printf("\t |%4d %8s  %6.2f    %6.2f    |\n", cards[index].cnum, cards[index].name, 
           (cards[index].save_records != NULL ? cards[index].save_records->spendMoney : 0), cards[index].cbalance);
           //���У԰���ĳ�ֵ��¼�����Ƿ�Ϊ�ա������Ϊ�գ�˵���г�ֵ��¼��
           //����г�ֵ��¼����ȡ���һ�γ�ֵ�Ľ�
    printf("\t +==== ======== ========== ==========+\n");
    }
// ���������ȵĺ���
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
// �ȽϽ��ĺ���
int compare_money(double a, double b) {
    return a > b; // ���a����b������1�����򷵻�0
}
// ������¼�ĺ���
void swapRecords(SpendRecord* a, SpendRecord* b) {
    double temp_money = a->spendMoney;//���������
    a->spendMoney = b->spendMoney;
    b->spendMoney = temp_money;
}


void muchsortspend(SpendRecord* head) {// ������С������������Ѽ�¼
    int length = lengthList(head);// ��ȡ������
    for (int i = 0; i < length - 1; i++) {// ���ѭ��������������
        for (int j = 0; j < length - i - 1; j++) {// �ڲ�ѭ������ÿ�ֱȽϴ���
            SpendRecord* current = head;// �ҵ���ǰ�ڵ�
            for (int k = 0; k < j; k++) {// ���ѭ����currentָ���ƶ�����j+1���ڵ㣬
                //��Ϊ�ڲ�ѭ��������j�Ǵ�0��ʼ�ģ���������Ҫ�Ƚϵ��ǵ�j+1���ڵ�͵�j+2���ڵ�
                current = current->next;
            }
            SpendRecord* next = current->next;
            if (compare_money(current->spendMoney, next->spendMoney)) {
                swapRecords(current, next);
            }
        }
    }
}
void muchsortsave(SaveRecord* head) {// ������С��������ĳ�ֵ��¼
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

void displayspend(SpendRecord* head) //��ʾ���Ѽ�¼
{
    printf("\n\t |==== ======== =========== =========|\n");
    printf("\t |����ʱ��                ���ѽ��   |\n|");
    for(SpendRecord* p=head; p!=NULL; p=p->next)// ��������
    {
        char timeStr[20]; // ����һ���㹻��Ļ��������洢��ʽ����ʱ���ַ���
        // ʹ�� strftime ������ time_t ���͵�ʱ���ת��Ϊָ����ʽ���ַ���
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
        printf("\t |%s %10.2f     |\n", timeStr, p->spendMoney); // �����ʽ����ʱ��ͽ�ȷ������ֶο��һ��
    }
    printf("\t |----+------------+----------+------|\n");
}
   
void displaysave(SaveRecord* head) //��ʾ��ֵ��¼
{
    printf("\n\t |==== ======== =========== =========|\n");
    printf("\t |��ֵʱ��                ��ֵ���   |\n|");
    for(SaveRecord* p=head; p!=NULL; p=p->next)// ��������
    {
        char timeStr[20]; // ����һ���㹻��Ļ��������洢��ʽ����ʱ���ַ���
        // ʹ�� strftime ������ time_t ���͵�ʱ���ת��Ϊָ����ʽ���ַ���
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
       printf("\t |%s %10.2f     |\n", timeStr, p->spendMoney); // �����ʽ����ʱ��ͽ�ȷ������ֶο��һ��
    }
    printf("\t |----+------------+----------+------|\n");
}

void displayall(CARD cards[],int index)//��ʾ���Ż����һ��ͨ��Ϣ
{
     if (index < 0 || index >= MAXNUM) {
        printf("����������Χ��\n");
        return;
    }

// ��ʾ������Ϣ
    for(index=0;index<count;index++)
    { 
        if(cards[index].flag==1)
    {
        continue;
    }
    printf("\n\t |==== ======== ========== ==========|\n");
    printf("\t |���� ����     ��ֵ���     ����� \n|");
    printf("\t |----+--------+----------+----------|\n");
    printf("\t |%4d %8s  %6.2f    %6.2f    |\n", cards[index].cnum, cards[index].name, 
           (cards[index].save_records != NULL ? cards[index].save_records->spendMoney : 0), cards[index].cbalance);
           //���У԰���ĳ�ֵ��¼�����Ƿ�Ϊ�ա������Ϊ�գ�˵���г�ֵ��¼��
           //����г�ֵ��¼����ȡ���һ�γ�ֵ�Ľ�
    }
    printf("\t +==== ======== ========== ==========+\n");
    }



void exitout() // �˳�ϵͳ�����濨��Ϣ�����Ѽ�¼�ͳ�ֵ��¼���ļ�
{   
    FILE *fp; // �ļ�ָ��
    // ���Դ��ļ�������ļ��������򴴽�
    fp = fopen("C:\\Users\\Vertin\\Desktop\\c����ʵѵ��Ŀ\\card_info.txt", "w+");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        exit(1); // ����ļ���ʧ�ܣ����˳�����
    }
   
    //д�뿨��Ϣ���ļ�
    for (int index = 0; index < MAXNUM; index++) {
        if (cards[index].cnum != 0 && cards[index].flag == 0) { // ֻд����Ч������Ϣ
            fprintf(fp, "����: %d, ����: %s, ���: %.2f\n", cards[index].cnum, cards[index].name, cards[index].cbalance);
            
            // д�����Ѽ�¼
            fprintf(fp, "���Ѽ�¼:\n");
            for (SpendRecord *p = cards[index].spend_records; p != NULL; p = p->next) {
                char timeStr[20];
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
                fprintf(fp, "ʱ��: %s, ���ѽ��: %.2f\n", timeStr, p->spendMoney);
            }

            // д���ֵ��¼
            fprintf(fp, "��ֵ��¼:\n");
            for (SaveRecord *p = cards[index].save_records; p != NULL; p = p->next) {
                char timeStr[20];
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&p->datetime));
                fprintf(fp, "ʱ��: %s, ��ֵ���: %.2f\n", timeStr, p->spendMoney);
            }

            fprintf(fp, "\n"); // ÿ��������Ϣ֮�����һ�������Էָ�
        }
    }

    //�ر��ļ�
    fclose(fp);

    printf("��лʹ�ã�\n");
    exit(0);
}

void initfromfile(CARD cards[], int *num_cards) {//��ʼ���ṹ������
    FILE *file = fopen("C:\\Users\\Vertin\\Desktop\\c����ʵѵ��Ŀ\\card_info.txt", "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        exit(1);
    }

    *num_cards = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "����:", 4) == 0) {
            // Parse card information
            if (sscanf(line, "����: %d, ����: %[^,], ���: %f", &cards[*num_cards].cnum, cards[*num_cards].name, &cards[*num_cards].cbalance) == 3) {
                cards[*num_cards].flag = 0;
                cards[*num_cards].spend_records = NULL;
                cards[*num_cards].save_records = NULL;
                (*num_cards)++;
            }
        } else if (strncmp(line, "ʱ��:", 4) == 0) {
            // Parse spend or save record
            double amount;
            char timeStr[20];
            struct tm tm;// ����<time.h> ͷ�ļ��б�ʾ���ں�ʱ��Ľṹ�����
            memset(&tm, 0, sizeof(tm));
            if (sscanf(line, "ʱ��: %[^,], ���ѽ��: %lf", timeStr, &amount) == 2) {
                sscanf(timeStr, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
                tm.tm_year -= 1900; // struct tm ����ݴ�1900�꿪ʼ����
                tm.tm_mon -= 1;     // struct tm ���·ݴ�0��ʼ����
                time_t time = mktime(&tm);//�� struct tm �ṹ��ת��Ϊ time_t ʱ�����
                SpendRecord *newSpend = (SpendRecord *)malloc(sizeof(SpendRecord));
                newSpend->datetime = time;
                newSpend->spendMoney = amount;
                newSpend->next = cards[*num_cards - 1].spend_records;
                cards[*num_cards - 1].spend_records = newSpend;
                
            } else if (sscanf(line, "ʱ��: %[^,], ��ֵ���: %lf", timeStr, &amount) == 2) {
                sscanf(timeStr, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
                tm.tm_year -= 1900; // struct tm ����ݴ�1900�꿪ʼ����
                tm.tm_mon -= 1;     // struct tm ���·ݴ�0��ʼ����
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
    printf("���ļ��ж�ȡ�� %d �ſ�����Ϣ��\n", *num_cards);
    printf("��ʼ����ϡ�\n");
}
//%[^,] �� sscanf �����е�һ����ʽ˵���������ڴ������ַ����ж�ȡ�ַ���ֱ���������� , Ϊֹ��
//�����ʽ˵����ͨ�����ڶ�ȡ�ַ��������� ^ ���ű�ʾ�����ˡ���ֱ��������˼��
// ������˵��%[^,] �ĺ������£�
// %����ʾ��ʽ˵�����Ŀ�ʼ��
// [����ʾ�ַ����Ŀ�ʼ��
// ^����ʾȡ��������ȡ����ָ���ַ���֮��������ַ���
// ,]��ָ���ַ����������Ƕ��� ,����ʾ��ȡֱ����������Ϊֹ��
// ]����ʾ�ַ����Ľ�����
















