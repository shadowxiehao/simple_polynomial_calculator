#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h> 
#include <windows.h>
typedef struct polynomial {   //���ݽṹ  
    float coef;   //ϵ��coefficient  
    int expo;    //ָ��exponent  
    struct polynomial * next;
}Poly;

void menu() {  //�û��˵�ѡ����� 
    printf("\n"
        "\t*****************************************************************\n"
        "\t********************        ��ѡ�����       ********************\n"
        "\t********                 1.���ϸ�x������ֵ,��ʾ������  ********\n"
        "\t********                 2.һԪ����ʽ���                ********\n"
        "\t********                 3.һԪ����ʽ���                ********\n"
        "\t********                 4.һԪ����ʽ���                ********\n"
        "\t********                   0.�˳�������                  ********\n"
        "\t*****************************************************************\n"
        "\t                        ����Ҫִ�е��ǣ�");
}
void insert(Poly *head, Poly *input)//��һ����㰴 ָ���Ӵ�С˳�� ���뵽һ��������
{
    Poly *pre, *now;//��¼һ������������һ�����
    int signal = 0;//����Ƿ���������ѭ��
    pre = head;//����preΪͷ����

    if (pre->next == NULL) {//���ֻ��ͷ����
        pre->next = input;//�Ͱ�input�嵽ͷ������һ��
    }
    else {//�ǿ�����
        now = pre->next;//��nowΪpre����һ��
        while (signal == 0) {
            if (input->expo < now->expo)//���Ҫ����������ָ��С��now��,��ô
            {
                if (now->next == NULL) {//���now��֮��û�н��,�Ͱ�input�嵽now����,Ҳ�����������
                    now->next = input;
                    signal = 1;//�������־����,�Ӷ���ν����˳�ѭ��,�������
                }
                else {//���now���н��,�Ͱ�pre��now���������ƶ�һ��,Ȼ��ʼһ���µıȽ�
                    pre = now;
                    now = pre->next;
                }
            }
            else if (input->expo > now->expo) {//���Ҫ����������ָ������now��,��ô��input���뵽pre��now֮��
                input->next = now;
                pre->next = input;
                signal = 1;//�������־����,�Ӷ���ν����˳�ѭ��,�������
            }
            else {//��-��Ҫ����������ָ������now��,��ô��input��ϵ����now�ĺϲ�
                now->coef = now->coef + input->coef;//�ϲ�ϵ��
                signal = 1;//�������־����,�Ӷ���ν����˳�ѭ��,�������
                free(input);//�ϲ���Ϳ���ɾ��input�ڴ�,�ͷſռ�
                if (now->coef == 0) {//���ϵ��������ӵ���,��ɾ��now���
                    pre->next = now->next;
                    free(now);
                }
            }
        }
    }
}

Poly *creat(char ch) {  //��������ʽ 
    Poly *head, *input;//����ͷ����һ��������
    float 
x;//��ʱ���ϵ��
    int y;//��ʱ���ָ��
    int n = 1;//��Ŷ���ʽ����
    head = (Poly *)malloc(sizeof(Poly));//����ͷ����ڴ�
    head->next = NULL;//��ʼ��next
    //�Ѻû�������ʾ ��ϵ����ָ����ֵ
    printf("\n%c(x)�ĵ�%d��ʽϵ��:", ch, n);
    scanf("%f", &x);//��ϵ����ֵ

    while (x != 0) {//���ϵ����Ϊ0(ϵ��Ϊ0���������),�Ͳ�ͣ�������½�㲢��ֵ��ϲ�������
        //�Ѻû�������ʾ ��ϵ����ָ����ֵ
        printf("%c(x)�ĵ�%d��ʽָ��:", ch, n++);
        scanf("%d", &y);//��ָ����ֵ
        printf("\n");
        input = (Poly *)malloc(sizeof(Poly));
        input->coef = x;
        input->expo = y;
        input->next = NULL;
        insert(head, input);
        //�Ѻû�������ʾ ��ϵ����ָ����ֵ
        printf("%c(x)�ĵ�%d��ʽϵ��:", ch, n);
        scanf("%f", &x);//��ϵ����ֵ
    }
    return head;//���������ͷ���
}

Poly *add(Poly *head, Poly *pre)  //����ʽ��� 
{
    Poly *input;
    int flag = 0;
    //�������ԭ���ǽ��ڶ��������еĽ��һ�����ϲ�����һ��������,��Ϊ���
    while (flag == 0) {
        if (pre->next == NULL)
            flag = 1;
        else {
            pre = pre->next;
            input = (Poly *)malloc(sizeof(Poly));
            input->coef = pre->coef;
            input->expo = pre->expo;
            input->next = NULL;
            insert(head, input);
        }
    }
    return head;//���ص�һ������(�ϲ��������)��ͷ���
}
Poly *minus(Poly *head, Poly *pre)  //����ʽ��� 
{
    Poly *input;
    int flag = 0;
    //������������,ֻ�ǰ�ÿ��ϵ��ȡ�෴��
    while (flag == 0) {
        if (pre->next == NULL)
            flag = 1;
        else {
            pre = pre->next;
            input = (Poly *)malloc(sizeof(Poly));
            input->coef = 0 - pre->coef;
            input->expo = pre->expo;
            input->next = NULL;
            insert(head, input);
        }
    }  return head;
}

/**
 * @pargm *head1 *head2 ����Ҫ��˵�һԪ����ʽ����
 * @return ����һ����˽����һԪ����ʽ(�˻�)
 */
Poly *multiply(Poly *head1, Poly *head2)  //����ʽ��� 
{
    Poly *input, *product, *pre;
    int flag = 0;//flagΪ�Ƿ���� ��˲���ѭ�� ���ж�����
    product = (Poly *)malloc(sizeof(Poly));//����˻� һԪ����ʽ �ռ�
    product->next = NULL;
    head1 = head1->next;//�ֽ���һ������λ�����ĵ�һ��ֵ����
    pre = head2;
    //���ԭ��Ϊ:��ȡ��һ�������һ��,Ȼ�󽫵ڶ��������е�ÿ���������,���˻��ϲ���product������
    //Ȼ����ȡ��һ������ڶ���,�ظ�ǰ�沽��,ֱ��ȫ������.
    while (flag == 0) {
        if (head1 == NULL) {//�����һ������Ԫ��ȡ��,����
            flag = 1;
            continue;
        }
        if (pre->next == NULL) {//����ڶ�������Ԫ��ȡ��,��һ������ȡ��һ��,���س�һ��
            pre = head2;
            head1 = head1->next;
            continue;
        }
        pre = pre->next;
        input = (Poly *)malloc(sizeof(Poly));//�����½��洢��˽��,�����ںϲ���˻�����
        input->coef = pre->coef*head1->coef;//����ʽϵ��Ϊ��ϵ�����
        input->expo = pre->expo + head1->expo;//����ʽָ��Ϊ��ָ�����
        input->next = NULL;//��ʼ��next
        insert(product, input);//�ϲ���˻�����
    }
    return product;//���س˻�
}
double calcu(Poly *head, double x) {
    Poly *s; //����ʽ 
    double sum = 0, n;
    int i;
    s = head->next;//ͷ�����һ�� 
    while (1) {
        n = 1;
        for (i = 0; i < s->expo; i++)//ָ������ 
            n = n * x;
        sum += n * s->coef;//���� 
        if (s->next == NULL) {
            return sum;
        }
        else s = s->next;
    }
}

void print(Poly *fun) {//�������һԪ����ʽ
    Poly *printing; //�������ڱ�������Ľ��
    int flag = 0;//�ж��Ƿ����print�ı��
    float ex0 = 0;//���㳣��

    printing = fun->next;
    if (fun->next == NULL) {//����ǿ�����,�����0
        printf("0\n");
        return;
    }
    while (flag == 0) {
        if (printing->coef > 0 && printing->expo != 0 && fun->next != printing)//fun->next != printing�����ж��Ƿ�Ϊ��һ�����
            printf("+");

        if (printing->expo != 0) {
            if (printing->coef == 1);//���ϵ����1,�Ͳ����ϵ��
            else if (printing->coef == -1)
                printf("-");//���ϵ��-1,ϵ����ֻ�������
            else printf("%.3f", printing->coef);//��������������,���������ϵ����ֵ
            if (printing->expo > 0)
                printf("x^%d", printing->expo);//���ָ��>0,���x^ Ȼ�����ָ����ֵ
            else
                printf("x^%d ", printing->expo);//���ָ��<0,���x^ Ȼ�����ָ����ֵ,�ټӸ��ո�
        }
        else if (printing->expo == 0)//���ָ��Ϊ0,��������
            ex0 += printing->coef;
        if (printing->next == NULL) {
            if (ex0 != 0)
            {
                printf("+%.3f", ex0);//����������
            }
            flag = 1;
        }
        else printing = printing->next;
    }
    printf("\n");
}
int main() {

    Poly *f, *g;//�����������ṹ��ָ��
    int sign = -1;//��¼ѡ�˲˵��ĵڼ���
    int start = 0;//��¼�Ƿ�֮ǰ���й�����
    char flag = 'N';//�ж��Ƿ��������
    int flagg = 0;//�ж��Ƿ��������
    system("color f0");
    
    while (sign != 0) {//����ѡ���˳��Ļ�
        menu();//��ʾ��ʼ�˵�ҳ��
        scanf("%d", &sign);//��¼�˵�ѡ��
        switch (sign) {//����ѡ��Ķ�Ӧ����
        case 0:    break;//0���˳�
        case 1: {
            double val = 0;
            if (start!=0) {
                printf("\n�������ϸ����x��ֵ:");
                scanf("%lf", &val);
                val = calcu(f, val);
                printf("\n��ֵ���ϸ�ʽ�ӽ����:%lf\n", val);
            }
            else {
                system("cls");
                printf("\n ����!û��֮ǰ������!���Ƚ���һ������!\n");
                Sleep(1500);
            }
            break;
        }
        case 2: {
            system("cls");
            
            printf("PS:�����ʽ:ϵ�� ָ����������ϵ��Ϊ0ʱ������\n");
            printf("PS:�����ʽ:ϵ�� ָ����������ϵ��Ϊ0ʱ������\n\n");
            printf("��ʼ����ʽ���:\n");
            if (flagg == 1) {
                printf("�ϸ����f(x)=");
                print(f);
            }
            if (flagg == 0) {
                f = creat('f');
                printf("f(x)=");
                print(f);
            }
            g = creat('g');
            printf("g(x)=");
            print(g);
            printf("--------------------\n\n");
            printf("��������ʽ��ӽ��Ϊ��\n\n");
            printf(" F(x)=f(x)+g(x)=");
            f = add(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start = 1;
            getchar();
            printf("\n�Ƿ��Խ��Ϊһ������ʽ��������?(Y/N):");
            scanf("%c", &flag);
            if (flag == ('Y' | 'y')) {
                flagg = 1;//���Ϊ��������
            }
            else if (flag == ('N' | 'n')) {
                flagg = 0;//���Ϊ��������
            }
            printf("\n�Ѽ�¼����ѡ��,�����´β���ʱ��Ч");
            break;
        }
        case 3: {
            system("cls");
            
            printf("PS:�����ʽ:ϵ�� ָ����������ϵ��Ϊ0ʱ������\n");
            printf("PS:�����ʽ:ϵ�� ָ����������ϵ��Ϊ0ʱ������\n\n");
            printf("��ʼ����ʽ���:\n");
            if (flagg == 1) {
                printf("�ϸ����f(x)=");
                print(f);
            }
            if (flagg == 0) {
                f = creat('f');
                printf("f(x)=");
                print(f);
            }
            g = creat('g');
            printf("g(x)=");
            print(g);
            printf("--------------------\n\n");
            printf("��������ʽ������Ϊ��\n\n");
            printf(" F(x)=f(x)-g(x)=");
            f = minus(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start = 1;
            getchar();
            printf("\n�Ƿ��Խ��Ϊһ������ʽ��������?(Y/N):");
            scanf("%c", &flag);
            if (flag == ('Y' | 'y')) {
                flagg = 1;//���Ϊ��������
            }
            else if (flag == ('N' | 'n')) {
                flagg = 0;//���Ϊ��������
            }
            printf("\n�Ѽ�¼����ѡ��,�����´β���ʱ��Ч");
            break;
        }
        case 4: {
            system("cls");
            
            printf("PS:�����ʽ:ϵ�� ָ����������ϵ��Ϊ0ʱ������\n");
            printf("PS:�����ʽ:ϵ�� ָ����������ϵ��Ϊ0ʱ������\n\n");
            printf("��ʼ����ʽ���:\n");
            if (flagg == 1) {
                printf("�ϸ����f(x)=");
                print(f);
            }
            if (flagg == 0) {
                f = creat('f');
                printf("f(x)=");
                print(f);
            }
            g = creat('g');
            printf("g(x)=");
            print(g);
            printf("--------------------\n\n");
            printf("��������ʽ��˽��Ϊ��\n\n");
            printf(" F(x)=f(x)*g(x)=");
            f = multiply(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start = 1;
            getchar();
            printf("\n�Ƿ��Խ��Ϊһ������ʽ��������?(Y/N):");
            scanf("%c", &flag);
            if (flag == ('Y' | 'y')) {
                flagg = 1;//���Ϊ��������
            }
            else if (flag == ('N' | 'n')) {
                flagg = 0;//���Ϊ��������
            }
            printf("\n�Ѽ�¼����ѡ��,�����´β���ʱ��Ч");
            break;
        }
        default: {
            printf("��Чָ��:������ѡ�����!\n");
            system("cls");
            break;
        }
        }
        
    }
    printf("\n\t***********************\n");
    printf("\t*  �����˳�!ллʹ��! *\n");
    printf("\t***********************\n");
    printf("3s���˳�\n");
    Sleep(1000);
    printf("2s���˳�\n");
    Sleep(1000);
    printf("1s���˳�\n");
    Sleep(1000);
    return 1;
}