#include<stdio.h> 
#include<malloc.h> 

typedef struct myNode {   //���ݽṹ  
    float coef;   //ϵ��coefficient  
    int expn;    //ָ��exponent  
    struct myNode * next;
}PLOY;

void start()  //�û�ѡ����� 
{
    printf(" \n"); 
    printf("                     ************************************\n");
    printf("                     *     ��ӭʹ��һԪ����ʽ������     *\n");
    printf("                     ************************************\n");
    printf("\n");
    printf("  ��ѡ�����:\n\n");
    printf("  0.�˳�����\n");
    printf("  1.һԪ����ʽ���\n");
    printf("  2.һԪ����ʽ���\n");
    printf("  3.һԪ����ʽ���\n\n");
}
void insert(PLOY *head, PLOY *inpt)
{
    PLOY *pre, *now;
    int signal = 0;  pre = head;
    if (pre->next == NULL) {
        pre->next = inpt;
    }
    else {
        now = pre->next;
        while (signal == 0) {
            if (inpt->expn < now->expn)
            {
                if (now->next == NULL)

                {
                    now->next = inpt;
                    signal = 1;
                }
                else {
                    pre = now;
                    now = pre->next;
                }
            }
            else if (inpt->expn > now->expn) {
                inpt->next = now;
                pre->next = inpt;
                signal = 1;
            }
            else {
                now->coef = now->coef + inpt->coef;
                signal = 1;
                free(inpt);      if (now->coef == 0) { pre->next = now->next;      free(now); }
            }
        }
    }
}

PLOY *creat(char ch)  //��������ʽ 
{
    PLOY *head, *inpt;
    float x;
    int y;
    head = (PLOY *)malloc(sizeof(PLOY));
    head->next = NULL;
    printf("������һԪ����ʽ%c:(��ʽ�ǣ�ϵ�� ָ������0 0 ������)\n", ch);
    scanf("%f %d", &x, &y);

    while (x != 0) {

        inpt = (PLOY *)malloc(sizeof(PLOY));
        inpt->coef = x;
        inpt->expn = y;
        inpt->next = NULL;
        insert(head, inpt);
        printf("������һԪ����ʽ%c:(��0 0 ������)\n", ch);
        scanf("%f %d", &x, &y);
    }  return head;
}
PLOY *addPLOY(PLOY *head, PLOY *pre)  //����ʽ��� 
{
    PLOY *inpt;
    int flag = 0;
    while (flag == 0) {
        if (pre->next == NULL)
            flag = 1;
        else {
            pre = pre->next;
            inpt = (PLOY *)malloc(sizeof(PLOY));
            inpt->coef = pre->coef;
            inpt->expn = pre->expn;
            inpt->next = NULL;
            insert(head, inpt);
        }
    }  return head;
}
PLOY *minusPLOY(PLOY *head, PLOY *pre)  //����ʽ��� 
{
    PLOY *inpt;
    int flag = 0;
    while (flag == 0) {
        if (pre->next == NULL)
            flag = 1;
        else {
            pre = pre->next;
            inpt = (PLOY *)malloc(sizeof(PLOY));
            inpt->coef = 0 - pre->coef;
            inpt->expn = pre->expn;
            inpt->next = NULL;
            insert(head, inpt);
        }
    }  return head;
}
PLOY *byPLOY(PLOY *head1, PLOY *head2)  //����ʽ��� 
{
    PLOY *inpt, *res, *pre;
    int flag = 0;
    res = (PLOY *)malloc(sizeof(PLOY));
    res->next = NULL;
    head1 = head1->next;
    pre = head2;
    while (flag == 0) {
        if (pre->next == NULL) {
            pre = head2;
            head1 = head1->next;
            continue;
        }   if (head1 == NULL) {
            flag = 1;    continue;
        }
        pre = pre->next;
        inpt = (PLOY *)malloc(sizeof(PLOY));
        inpt->coef = pre->coef*head1->coef;
        inpt->expn = pre->expn + head1->expn;
        inpt->next = NULL;   insert(res, inpt);
    }  return res;
}

void print(PLOY *fun) {
    PLOY *printing;  int flag = 0;

    printing = fun->next;
    if (fun->next == NULL) {
        printf("0\n");
        return;
    }  while (flag == 0) {
        if (printing->coef > 0 && fun->next != printing)
            printf("+");
        if (printing->coef == 1);
        else if (printing->coef == -1)
            printf("-");
        else   printf("%f", printing->coef);
        if (printing->expn != 0) printf("x^%d", printing->expn);
        else if ((printing->coef == 1) || (printing->coef == -1))
            printf("1");
        if (printing->next == NULL)
            flag = 1;
        else   printing = printing->next;
    }
    printf("\n");
}
void main() {
    PLOY *f, *g;
    int sign = -1;
    start();
    while (sign != 0) {
        scanf("%d", &sign);
        switch (sign) {
        case 0:    break;
        case 1: {     printf("��ѡ��Ĳ����Ƕ���ʽ���:\n");
            f = creat('f');
            printf("f(x)=");
            print(f);
            g = creat('g');
            printf("g(x)=");
            print(g);
            printf("--------------------\n\n");
            printf("��������ʽ��ӽ��Ϊ��\n\n");
            printf(" F(x)=f(x)+g(x)=");
            f = addPLOY(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start();
            break;
        }
        case 2: {
            printf("��ѡ��Ĳ����Ƕ���ʽ���:\n");
            f = creat('f');
            printf("f(x)=");
            print(f);
            g = creat('g');
            printf("g(x)=");
            print(g);
            printf("--------------------\n\n");
            printf("��������ʽ������Ϊ��\n\n");
            printf(" F(x)=f(x)-g(x)=");
            f = minusPLOY(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start();
            break;
        }
        case 3: {
            printf("��ѡ��Ĳ����Ƕ���ʽ���:\n");
            f = creat('f');
            printf("f(x)=");
            print(f);
            g = creat('g');
            printf("g(x)=");
            print(g);
            printf("--------------------\n\n");
            printf("��������ʽ��˽��Ϊ��\n\n");
            printf(" F(x)=f(x)*g(x)=");
            f = byPLOY(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start();
            break;
        }
        case 4: {
            sign = -1;
            start();
            break;
        }
        default: {
            printf("Error!������ѡ�����!\n");
            start();
            break;    }
        }
    }  printf("                           ***********************\n");
    printf("                           *      ллʹ�ã�     *\n");
    printf("                           ***********************\n");
}