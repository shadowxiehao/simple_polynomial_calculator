#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h> 
#include <windows.h>
typedef struct polynomial {   //数据结构  
    float coef;   //系数coefficient  
    int expo;    //指数exponent  
    struct polynomial * next;
}Poly;

void menu() {  //用户菜单选择界面 
    printf("\n"
        "\t*****************************************************************\n"
        "\t********************        请选择操作       ********************\n"
        "\t********                 1.给上个x变量赋值,显示计算结果  ********\n"
        "\t********                 2.一元多项式相加                ********\n"
        "\t********                 3.一元多项式相减                ********\n"
        "\t********                 4.一元多项式相乘                ********\n"
        "\t********                   0.退出计算器                  ********\n"
        "\t*****************************************************************\n"
        "\t                        您需要执行的是：");
}
void insert(Poly *head, Poly *input)//将一个结点按 指数从大到小顺序 插入到一个链表中
{
    Poly *pre, *now;//记录一个结点和它的下一个结点
    int signal = 0;//标记是否结束插入的循环
    pre = head;//先令pre为头链表

    if (pre->next == NULL) {//如果只有头链表
        pre->next = input;//就把input插到头结点的下一个
    }
    else {//非空链表
        now = pre->next;//令now为pre的下一个
        while (signal == 0) {
            if (input->expo < now->expo)//如果要插入的链表的指数小于now的,那么
            {
                if (now->next == NULL) {//如果now的之后没有结点,就把input插到now后面,也就是链表最后
                    now->next = input;
                    signal = 1;//令结束标志成立,从而这次结束退出循环,插入完成
                }
                else {//如果now后有结点,就把pre和now结点各往后移动一个,然后开始一个新的比较
                    pre = now;
                    now = pre->next;
                }
            }
            else if (input->expo > now->expo) {//如果要插入的链表的指数大于now的,那么将input插入到pre和now之间
                input->next = now;
                pre->next = input;
                signal = 1;//令结束标志成立,从而这次结束退出循环,插入完成
            }
            else {//如-果要插入的链表的指数等于now的,那么将input的系数和now的合并
                now->coef = now->coef + input->coef;//合并系数
                signal = 1;//令结束标志成立,从而这次结束退出循环,插入完成
                free(input);//合并后就可以删除input内存,释放空间
                if (now->coef == 0) {//如果系数正负相加抵消,就删除now结点
                    pre->next = now->next;
                    free(now);
                }
            }
        }
    }
}

Poly *creat(char ch) {  //建立多项式 
    Poly *head, *input;//建立头结点和一个输入结点
    float 
x;//暂时存放系数
    int y;//暂时存放指数
    int n = 1;//存放多项式次数
    head = (Poly *)malloc(sizeof(Poly));//分配头结点内存
    head->next = NULL;//初始化next
    //友好化输入提示 给系数和指数赋值
    printf("\n%c(x)的第%d项式系数:", ch, n);
    scanf("%f", &x);//给系数赋值

    while (x != 0) {//如果系数不为0(系数为0即代表结束),就不停地增加新结点并赋值后合并入链表
        //友好化输入提示 给系数和指数赋值
        printf("%c(x)的第%d项式指数:", ch, n++);
        scanf("%d", &y);//给指数赋值
        printf("\n");
        input = (Poly *)malloc(sizeof(Poly));
        input->coef = x;
        input->expo = y;
        input->next = NULL;
        insert(head, input);
        //友好化输入提示 给系数和指数赋值
        printf("%c(x)的第%d项式系数:", ch, n);
        scanf("%f", &x);//给系数赋值
    }
    return head;//返回链表的头结点
}

Poly *add(Poly *head, Poly *pre)  //多项式相加 
{
    Poly *input;
    int flag = 0;
    //下面这段原理是将第二个链表中的结点一个个合并到第一个链表中,即为相加
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
    return head;//返回第一个链表(合并后的链表)的头结点
}
Poly *minus(Poly *head, Poly *pre)  //多项式相减 
{
    Poly *input;
    int flag = 0;
    //这里和相加类似,只是把每个系数取相反数
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
 * @pargm *head1 *head2 两个要相乘的一元多项式链表
 * @return 返回一个相乘结果的一元多项式(乘积)
 */
Poly *multiply(Poly *head1, Poly *head2)  //多项式相乘 
{
    Poly *input, *product, *pre;
    int flag = 0;//flag为是否结束 相乘步骤循环 的判断条件
    product = (Poly *)malloc(sizeof(Poly));//分配乘积 一元多项式 空间
    product->next = NULL;
    head1 = head1->next;//现将第一个链表定位到它的第一个值部分
    pre = head2;
    //相乘原理为:先取第一个链表第一个,然后将第二个链表中的每个和它相乘,将乘积合并入product链表中
    //然后再取第一个链表第二个,重复前面步骤,直至全部结束.
    while (flag == 0) {
        if (head1 == NULL) {//如果第一个链表元素取尽,结束
            flag = 1;
            continue;
        }
        if (pre->next == NULL) {//如果第二个链表元素取尽,第一个链表取下一个,再重乘一遍
            pre = head2;
            head1 = head1->next;
            continue;
        }
        pre = pre->next;
        input = (Poly *)malloc(sizeof(Poly));//分配新结点存储相乘结果,并用于合并入乘积链表
        input->coef = pre->coef*head1->coef;//多项式系数为两系数相乘
        input->expo = pre->expo + head1->expo;//多项式指数为两指数相加
        input->next = NULL;//初始化next
        insert(product, input);//合并入乘积链表
    }
    return product;//返回乘积
}
double calcu(Poly *head, double x) {
    Poly *s; //多项式 
    double sum = 0, n;
    int i;
    s = head->next;//头结点下一个 
    while (1) {
        n = 1;
        for (i = 0; i < s->expo; i++)//指数运算 
            n = n * x;
        sum += n * s->coef;//叠加 
        if (s->next == NULL) {
            return sum;
        }
        else s = s->next;
    }
}

void print(Poly *fun) {//用来输出一元多项式
    Poly *printing; //创立用于遍历链表的结点
    int flag = 0;//判定是否继续print的标记
    float ex0 = 0;//计算常数

    printing = fun->next;
    if (fun->next == NULL) {//如果是空链表,就输出0
        printf("0\n");
        return;
    }
    while (flag == 0) {
        if (printing->coef > 0 && printing->expo != 0 && fun->next != printing)//fun->next != printing用来判断是否为第一个结点
            printf("+");

        if (printing->expo != 0) {
            if (printing->coef == 1);//如果系数是1,就不输出系数
            else if (printing->coef == -1)
                printf("-");//如果系数-1,系数就只输出负号
            else printf("%.3f", printing->coef);//如果不是以上情况,就正常输出系数的值
            if (printing->expo > 0)
                printf("x^%d", printing->expo);//如果指数>0,输出x^ 然后加上指数的值
            else
                printf("x^%d ", printing->expo);//如果指数<0,输出x^ 然后加上指数的值,再加个空格
        }
        else if (printing->expo == 0)//如果指数为0,常数增加
            ex0 += printing->coef;
        if (printing->next == NULL) {
            if (ex0 != 0)
            {
                printf("+%.3f", ex0);//最后输出常数
            }
            flag = 1;
        }
        else printing = printing->next;
    }
    printf("\n");
}
int main() {

    Poly *f, *g;//创立了两个结构体指针
    int sign = -1;//记录选了菜单的第几个
    int start = 0;//记录是否之前进行过计算
    char flag = 'N';//判断是否继续操作
    int flagg = 0;//判断是否继续操作
    system("color f0");
    
    while (sign != 0) {//不是选了退出的话
        menu();//显示开始菜单页面
        scanf("%d", &sign);//记录菜单选择
        switch (sign) {//进入选项的对应功能
        case 0:    break;//0就退出
        case 1: {
            double val = 0;
            if (start!=0) {
                printf("\n请输入上个结果x的值:");
                scanf("%lf", &val);
                val = calcu(f, val);
                printf("\n赋值后上个式子结果是:%lf\n", val);
            }
            else {
                system("cls");
                printf("\n 错误!没有之前运算结果!请先进行一次运算!\n");
                Sleep(1500);
            }
            break;
        }
        case 2: {
            system("cls");
            
            printf("PS:输入格式:系数 指数；当输入系数为0时结束！\n");
            printf("PS:输入格式:系数 指数；当输入系数为0时结束！\n\n");
            printf("开始多项式相加:\n");
            if (flagg == 1) {
                printf("上个结果f(x)=");
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
            printf("两个多项式相加结果为：\n\n");
            printf(" F(x)=f(x)+g(x)=");
            f = add(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start = 1;
            getchar();
            printf("\n是否以结果为一个多项式继续操作?(Y/N):");
            scanf("%c", &flag);
            if (flag == ('Y' | 'y')) {
                flagg = 1;//标记为继续操作
            }
            else if (flag == ('N' | 'n')) {
                flagg = 0;//标记为继续操作
            }
            printf("\n已记录您的选择,将在下次操作时生效");
            break;
        }
        case 3: {
            system("cls");
            
            printf("PS:输入格式:系数 指数；当输入系数为0时结束！\n");
            printf("PS:输入格式:系数 指数；当输入系数为0时结束！\n\n");
            printf("开始多项式相减:\n");
            if (flagg == 1) {
                printf("上个结果f(x)=");
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
            printf("两个多项式相减结果为：\n\n");
            printf(" F(x)=f(x)-g(x)=");
            f = minus(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start = 1;
            getchar();
            printf("\n是否以结果为一个多项式继续操作?(Y/N):");
            scanf("%c", &flag);
            if (flag == ('Y' | 'y')) {
                flagg = 1;//标记为继续操作
            }
            else if (flag == ('N' | 'n')) {
                flagg = 0;//标记为继续操作
            }
            printf("\n已记录您的选择,将在下次操作时生效");
            break;
        }
        case 4: {
            system("cls");
            
            printf("PS:输入格式:系数 指数；当输入系数为0时结束！\n");
            printf("PS:输入格式:系数 指数；当输入系数为0时结束！\n\n");
            printf("开始多项式相乘:\n");
            if (flagg == 1) {
                printf("上个结果f(x)=");
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
            printf("两个多项式相乘结果为：\n\n");
            printf(" F(x)=f(x)*g(x)=");
            f = multiply(f, g);
            print(f);
            printf("\n--------------------\n");
            sign = -1;
            start = 1;
            getchar();
            printf("\n是否以结果为一个多项式继续操作?(Y/N):");
            scanf("%c", &flag);
            if (flag == ('Y' | 'y')) {
                flagg = 1;//标记为继续操作
            }
            else if (flag == ('N' | 'n')) {
                flagg = 0;//标记为继续操作
            }
            printf("\n已记录您的选择,将在下次操作时生效");
            break;
        }
        default: {
            printf("无效指令:请重新选择操作!\n");
            system("cls");
            break;
        }
        }
        
    }
    printf("\n\t***********************\n");
    printf("\t*  即将退出!谢谢使用! *\n");
    printf("\t***********************\n");
    printf("3s后退出\n");
    Sleep(1000);
    printf("2s后退出\n");
    Sleep(1000);
    printf("1s后退出\n");
    Sleep(1000);
    return 1;
}