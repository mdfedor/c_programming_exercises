#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

/**
 * 4-1 编写函数strindex(s,t),它返回字符串t在s中最右边出现的位置，如果s中不包含t,则返回-1
 */
#if 0
#define MAXLEN 100
int strindex(char s[], char t[]);

int main()
{
    char s1[MAXLEN] = "abcdefgh";
    // char s2[MAXLEN] = "mmfk";
    char s3[MAXLEN] = "bcdef";
    int ret = strindex(s1, s3);
    if (ret != -1)
        printf("'%s' in '%s' appears first index is %d\n", s3, s1, ret);
    else
        printf("'%s' don't have substr '%s'\n", s1, s3);
    return 0;
}

int strindex(char s[], char t[])
{
    // abcdefgh
    //     mmfk
    int s_len = strlen(s);
    int t_len = strlen(t);
    if (s_len < t_len)
        return -1;
    int j;
    for (int i = s_len - t_len; i > 0; i--)
    {
        for (j = 0; j < t_len; j++)
        {
            if (s[i + j] != t[j])
                break;
        }
        if (j == t_len)
            return i;
    }
    return -1;
}
#endif

/**
 * 4-2 对atof函数进行扩充，使它可以处理形如123.45e-6的科学表示法，其中，浮点数后面可能会紧跟一个e或E以及一个指数(可能有正负号)
 */
#if 0
#define MAXLEN 100
double atof(char s[]);

int main()
{
    // char ch[MAXLEN] = "123.456e+3";
    char ch[MAXLEN] = "-55.245E-3";
    printf("%f\n", atof(ch));
    return 0;
}

double atof(char s[])
{
    // 扫描式处理字符串,有没有发现，这个程序扫描每个字符就用了一个指针i
    // 但是感觉并不会乱,而且他这个递增控制的也很好
    double val, power;
    int i, sign;
    // 跳过前面所有空格
    for (i = 0; isspace(s[i]); i++)
        ;
    // 记录符号正负
    sign = (s[i] == '-' ? -1 : 1);
    // 跳过符号部分
    if (s[i] == '+' || s[i] == '-')
        i++;
    // 读取整数部分
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    // 小数点
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        // 小数部分当整数部分读取
        val = 10.0 * val + (s[i] - '0');
        // 读取一位，因为按的是整数在读，那就相当于*10,最后读完后需要除掉这个小数部分
        power *= 10;
    }
    double ret = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        // 记录科学计数的符kj号
        int exp_sign = 1;
        if (s[i] == '-')
        {
            exp_sign = -1;
            i++;
        }
        else if (s[i] == '+')
            i++;
        // 记录指数
        int exp = 0;
        while (isdigit(s[i]))
            exp = 10 * exp + (s[i++] - '0');
        if (exp_sign == 1)
            ret *= pow(10, exp);
        else
            ret /= pow(10, exp);
    }
    return ret;
}
#endif

/**
 * base version
 */
#if 0
#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() + pop());
            break;
        case '-':
        {
            op2 = pop();
            push(pop() - op2);
        }
        break;
        case '/':
        {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() - op2);
            else
                printf("error: zero divisor\n");
        }
        break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error:unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// 栈操作函数
#define MAXVAL 100
int sp = 0;
double val[MAXVAL] = {0};

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:stack full,can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
// 获取输入内容
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 是操作符号
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    // 整数部分
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    // 小数部分
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

//
#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#endif
/**
 * 4-3在该程序中加入取模(%)运算符，并注意考虑负数的情况。
 */
#if 0
#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP] = "";
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
        {
            op2 = pop();
            push(pop() - op2);
        }
        break;
        case '/':
        {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        }
        case '%':
        {
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
        }
        break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error:unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// 栈操作函数
#define MAXVAL 100
int sp = 0;
double val[MAXVAL] = {0};

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:stack full,can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
// 获取输入内容
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 是操作符号
    i = 0;
    if (!isdigit(c) && c != '.')
    {
        if (c == '-')
        {
            // 取下一个字符看下是不是数字或者小数点
            int next = getch();
            if (!isdigit(next) && next != '.')
            {
                // 说明这就是个减号,刚才取出来的东西放缓冲区，下一次去处理
                ungetch(next);
                return c;
            }
            s[++i] = next;
            c = next; // 这里s[0]已经保存了-,刚才取出了可能是数字或小数点,所以让c保存下次去处理,这样负号也存起来了
        }
        else
            return c;
    }
    // 整数部分
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    // 小数部分
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

//
#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#endif

/**
 * 4-4 在栈操作中添加几个命令，分别用于在不弹出元素的情况下打印栈顶元素，复制栈顶元素;交换栈顶元素的值
 * 另外增加一个命令用于清空栈
 */
#if 0
#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top_two(void);
void clear_stack(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP] = "";
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
        {
            op2 = pop();
            push(pop() - op2);
        }
        break;
        case '/':
        {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        }
        case '%':
        {
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
        }
        break;
        case '?':
            print_top();
            break;
        case 'd':
            duplicate_top();
            break;
        case 's':
            swap_top_two();
            break;
        case 'c':
            clear_stack();
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error:unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// 栈操作函数
#define MAXVAL 100
int sp = 0;
double val[MAXVAL] = {0};

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("op push error: stack full,can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("op pop error: stack empty\n");
        return 0.0;
    }
}

void print_top(void)
{
    int tmp = 0;
    if (sp > 0)
    {
        tmp = sp - 1;
        printf("top value is: %g\n", val[tmp]);
    }
    else
        printf("stack is empty~~~\n");
}

void duplicate_top(void)
{
    int tmp;
    if (sp > 0 && sp < MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp] = tmp;
        sp++;
    }
}

void swap_top_two(void)
{
    int tmp;
    if (sp > 1 && sp <= MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = tmp;
    }
}
void clear_stack(void)
{
    sp = 0;
}

// 获取输入内容
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 是操作符号
    i = 0;
    if (!isdigit(c) && c != '.')
    {
        if (c == '-')
        {
            // 取下一个字符看下是不是数字或者小数点
            int next = getch();
            if (!isdigit(next) && next != '.')
            {
                // 说明这就是个减号,刚才取出来的东西放缓冲区，下一次去处理
                ungetch(next);
                return c;
            }
            s[++i] = next;
            c = next; // 这里s[0]已经保存了-,刚才取出了可能是数字或小数点,所以让c保存下次去处理,这样负号也存起来了
        }
        else
            return c;
    }
    // 整数部分
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    // 小数部分
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

//
#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#endif

/**
 * 4-5 给计算器程序增加访问sin,exp与pow等库函数的操作。
 */
#if 0
#define MAXOP 100
#define NUMBER '0'
#define NAME '1'

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top_two(void);
void clear_stack(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP] = "";
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NAME:
        {
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0)
            {
                double op2 = pop();
                double op1 = pop();
                push(pow(op1, op2));
            }
            else
                printf("error: unknown function %s\n", s);
        }
        break;
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
        {
            op2 = pop();
            push(pop() - op2);
        }
        break;
        case '/':
        {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        }
        case '%':
        {
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
        }
        break;
        case '?':
            print_top();
            break;
        case 'd':
            duplicate_top();
            break;
        case 's':
            swap_top_two();
            break;
        case 'c':
            clear_stack();
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error:unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// 栈操作函数
#define MAXVAL 100
int sp = 0;
double val[MAXVAL] = {0};

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("op push error: stack full,can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("op pop error: stack empty\n");
        return 0.0;
    }
}

void print_top(void)
{
    int tmp = 0;
    if (sp > 0)
    {
        tmp = sp - 1;
        printf("top value is: %g\n", val[tmp]);
    }
    else
        printf("stack is empty~~~\n");
}

void duplicate_top(void)
{
    int tmp;
    if (sp > 0 && sp < MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp] = tmp;
        sp++;
    }
}

void swap_top_two(void)
{
    int tmp;
    if (sp > 1 && sp <= MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = tmp;
    }
}
void clear_stack(void)
{
    sp = 0;
}

// 获取输入内容
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 是操作符号
    i = 0;
    if (!isdigit(c) && c != '.')
    {
        if (c == '-')
        {
            // 取下一个字符看下是不是数字或者小数点
            int next = getch();
            if (!isdigit(next) && next != '.')
            {
                // 说明这就是个减号,刚才取出来的东西放缓冲区，下一次去处理
                ungetch(next);
                return c;
            }
            s[++i] = next;
            c = next; // 这里s[0]已经保存了-,刚才取出了可能是数字或小数点,所以让c保存下次去处理,这样负号也存起来了
        }
        else if (isalpha(c))
        {
            while (isalpha(c))
            {
                c = getch();
                s[++i] = c;
            }
            s[i] = '\0';
            if (c != EOF)
                ungetch(c);
            return NAME;
        }
        else
            return c;
    }
    // 整数部分
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    // 小数部分
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

//
#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#endif

/**
 * 4-6 给计算器程序增加处理变量的命令,增加一个变量存放最近打印的值
 * r打印最近的值，A-Z作为变量 例如3 5 + A=   把3+5的值保存到A
 * A A +结果就是8+8=16
 */
#if 0
#define MAXOP 100
#define NUMBER '0'
#define NAME '1'

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top_two(void);
void clear_stack(void);
// 获取输入内容
int getch(void);
// 回退字符
void ungetch(int);

int main()
{
    int type;
    double op2;
    char s[MAXOP] = "";
    double recent = 0.0;
    char c;
    double variables[26] = {0};
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NAME:
        {
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0)
            {
                double op2 = pop();
                double op1 = pop();
                push(pow(op1, op2));
            }
            else
                printf("error: unknown function %s\n", s);
        }
        break;
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
        {
            op2 = pop();
            push(pop() - op2);
        }
        break;
        case '/':
        {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        }
        case '%':
        {
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
        }
        break;
        case '?':
            print_top();
            break;
        case 'd':
            duplicate_top();
            break;
        case 's':
            swap_top_two();
            break;
        case 'c':
            clear_stack();
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'X':
        case 'Y':
        case 'Z':
        {
            double val;
            c = getch();
            if (c == '=')
            {
                val = pop();
                variables[type - 'A'] = val;
                push(val);
            }
            else
            {
                ungetch(c);
                push(variables[type - 'A']);
            }
        }
        break;
        case '\n':
        {
            recent = pop();
            printf("\t%.8g\n", recent);
        }
        break;
        case 'r':
            push(recent);
            break;
        default:
            printf("error:unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// 栈操作函数
#define MAXVAL 100
int sp = 0;
double val[MAXVAL] = {0};

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("op push error: stack full,can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("op pop error: stack empty\n");
        return 0.0;
    }
}

void print_top(void)
{
    int tmp = 0;
    if (sp > 0)
    {
        tmp = sp - 1;
        printf("top value is: %g\n", val[tmp]);
    }
    else
        printf("stack is empty~~~\n");
}

void duplicate_top(void)
{
    int tmp;
    if (sp > 0 && sp < MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp] = tmp;
        sp++;
    }
}

void swap_top_two(void)
{
    int tmp;
    if (sp > 1 && sp <= MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = tmp;
    }
}
void clear_stack(void)
{
    sp = 0;
}

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 是操作符号
    i = 0;
    if (!isdigit(c) && c != '.')
    {
        if (c == '-')
        {
            // 取下一个字符看下是不是数字或者小数点
            int next = getch();
            if (!isdigit(next) && next != '.')
            {
                // 说明这就是个减号,刚才取出来的东西放缓冲区，下一次去处理
                ungetch(next);
                return c;
            }
            s[++i] = next;
            c = next; // 这里s[0]已经保存了-,刚才取出了可能是数字或小数点,所以让c保存下次去处理,这样负号也存起来了
        }
        else if (isalpha(c))
        {
            while (isalpha(c))
            {
                c = getch();
                s[++i] = c;
            }
            s[i] = '\0';
            if (c != EOF)
                ungetch(c);
            if (strcmp(s, "sin") == 0 || strcmp(s, "exp") == 0 || strcmp(s, "pow") == 0)
                return NAME;
            else
                return s[0];
        }
        else
            return c;
    }
    // 整数部分
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    // 小数部分
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

//
#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#endif

/**
 * 4-7 编写一个函数ungets(s),将整个字符串s压回到输入中
 * ungets函数需要使用buf和bufp吗。它能否仅仅使用ungetch函数
 */
#if 0
void ungets(char s[]);
int main()
{
    return 0;
}

#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
void ungets(char s[])
{
    int len = strlen(s); // 包括'\0'
    for (int i = strlen(s); i > 0; i--)
        ungetch(s[i]);
}

#endif

/**
 * 4-8 假设最多只压回一个字符，请相应地修改getch与ungetch这两个函数
 * 4-9 考虑压回EOF时应该如何处理
 */
#if 0
int main()
{
    return 0;
}
int buf = EOF;
int getch(void)
{
    int c;
    if (buf != EOF)
    {
        c = buf;
        buf = EOF;
    }
    else
        c = getchar();
    return c;
}
void ungetch(int c)
{
    if (buf != EOF)
        printf("full can't store character\n");
    else if (c != EOF)
        buf = c;
}
#endif

/**
 * 4-10 另一种方法是通过getline函数读入整个输入行，这种情况下可以不使用getch和ungetch函数
 * 4-11 修改getop函数，使其不必使用ungetch函数
 */
#if 0
#define MAXOP 100
#define NUMBER '0'
#define NAME '1'

static char line[MAXOP] = "";
static int pos = 0;

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top_two(void);
void clear_stack(void);
// 获取输入内容
int getch(void);
// 回退字符
void ungetch(int);

int main()
{
    int type;
    double op2;
    char s[MAXOP] = "";
    double recent = 0.0;
    char c;
    double variables[26] = {0};
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NAME:
        {
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0)
            {
                double op2 = pop();
                double op1 = pop();
                push(pow(op1, op2));
            }
            else
                printf("error: unknown function %s\n", s);
        }
        break;
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
        {
            op2 = pop();
            push(pop() - op2);
        }
        break;
        case '/':
        {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        }
        case '%':
        {
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
        }
        break;
        case '?':
            print_top();
            break;
        case 'd':
            duplicate_top();
            break;
        case 's':
            swap_top_two();
            break;
        case 'c':
            clear_stack();
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'X':
        case 'Y':
        case 'Z':
        {
            double val;
            c = line[pos++];
            if (c == '=')
            {
                val = pop();
                variables[type - 'A'] = val;
                push(val);
            }
            else
            {
                pos--;
                push(variables[type - 'A']);
            }
        }
        break;
        case '\n':
        {
            recent = pop();
            printf("\t%.8g\n", recent);
        }
        break;
        case 'r':
            push(recent);
            break;
        default:
            printf("error:unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// 栈操作函数
#define MAXVAL 100
int sp = 0;
double val[MAXVAL] = {0};

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("op push error: stack full,can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("op pop error: stack empty\n");
        return 0.0;
    }
}

void print_top(void)
{
    int tmp = 0;
    if (sp > 0)
    {
        tmp = sp - 1;
        printf("top value is: %g\n", val[tmp]);
    }
    else
        printf("stack is empty~~~\n");
}

void duplicate_top(void)
{
    int tmp;
    if (sp > 0 && sp < MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp] = tmp;
        sp++;
    }
}

void swap_top_two(void)
{
    int tmp;
    if (sp > 1 && sp <= MAXVAL)
    {
        tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = tmp;
    }
}
void clear_stack(void)
{
    sp = 0;
}

int getop(char s[])
{
    int c;
    int i = 0;

    if (line[pos] == '\0')
    {
        if (fgets(line, sizeof(line), stdin) == NULL)
            return EOF;
        pos = 0;
    }
    // 这里就是把line处理完毕
    while ((c = line[pos++]) != '\0')
    {
        // 跳过空格部分
        if (c == ' ' || c == '\t')
            continue;
        // 始终要记住，这里是第一手的字符，从line中一个一个读取出来的
        // c赋值是为了下面的好判断,s第一时间会存储c,并补'\0'
        // 那么下一个s[i++]的时候，一定要想清楚，应该属于下一个字符了
        s[i++] = c;
        s[i] = '\0';

        // 非数字类型
        if (!isdigit(c) && c != '.')
        {
            // 判断是减号还是负号
            if (c == '-')
            {
                int next = line[pos++];
                // 如果-后面不是数字或者小数点,那就是单纯一个减号，返回就行
                if (!isdigit(next) && next != '.')
                {
                    // 如果不是数字或小数点，说明pos多读了，pos--
                    pos--;
                    return c;
                }
                else
                // 这里要想清楚，next是点还是数字,不管点还是数字，首先是数字的一部分，要加到s中去
                // next已经是pos多读了一个的位置
                // 那么这里c不应该再返回去从line中读，再读就会漏掉这个next的值
                // 所以，c就需要在这里赋值成next,继续下面流程判断，字符不会被漏掉
                {
                    s[i++] = next;
                    c = next;
                }
            }
            // 字母
            else if (isalpha(c))
            {
                // c又递增了一个
                c = line[pos++];
                while (isalpha(c))
                {
                    s[i++] = c;
                    c = line[pos++];
                }
                s[i] = '\0'; // 字符后补'\0'
                pos--;       // 相当与多读出来的,走这里，说明已经不是字母，刚才c = line[pos++];已经多读了一个字符
                if (strcmp(s, "sin") == 0 || strcmp(s, "exp") == 0 || strcmp(s, "pow") == 0)
                    return NAME; // 字符串
                else
                    return s[i - 1]; // 单字母
            }
            else
                return s[i - 1]; // 非字母其他单字符
        }
        // 数字部分
        if (isdigit(c))
        {
            // 如果当前字符是数字，直接循环读取后续，直到不是数字为止
            while (isdigit(c = line[pos++]))
                s[i++] = c;
            // 跳出循环后，注意pos已经处于多读了一个字符的状态,并且已经赋值给了c
        }
        // 小数点部分
        if (c == '.')
        {
            while (isdigit(c = line[pos++]))
                s[i++] = c;
        }
        // 结尾补充0
        s[i] = '\0';
        // 这里出来的，pos都已经是多读了一个字符的状态,但可以确定此刻处理的字符串一定是一个数字
        // 至于说line[pos]此时是什么，留给下一次循环中去判断
        pos--;
        return NUMBER;
    }
    return -1;
}

//
#define BUFSIZE 100
char buf[BUFSIZE] = "";
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#endif

/**
 * 快速排序
 */
#if 0
void quicksort(int num[], int left, int right);
void quciksort1(int num[], int left, int right);
void swap(int *a, int *b);

int main()
{
    int a[] = {1, 6, 2, 7, 4, 8};
    int b[] = {7, 3, 2, 5, 6, 8, 9};
    quicksort(a, 0, 5);

    printf("-------q0--------\n");
    for (int i = 0; i < (sizeof(a) / sizeof(int)); i++)
        printf("%d ", a[i]);
    printf("\n");

    printf("-------q1--------\n");
    quciksort1(b, 0, 6);
    for (int i = 0; i < (sizeof(b) / sizeof(int)); i++)
        printf("%d ", b[i]);
    printf("\n");

    return 0;
}

void swap(int *i, int *j)
{
    int tmp;
    tmp = *i;
    *i = *j;
    *j = tmp;
}

void quicksort(int num[], int left, int right)
{
    if (left >= right)
        return;
    int pivot = num[left]; // 保存了一个标杆
    int i = left + 1;      // 除去标杆开始
    int j = right;         // 从尾部开始
    while (1)
    {
        while (i <= right && num[i] <= pivot)
            i++;
        while (j >= left + 1 && num[j] >= pivot)
            j--;

        if (i > j)
            break;
        swap(&num[i], &num[j]);
    }
    swap(&num[left], &num[j]);
    quicksort(num, left, j - 1);
    quicksort(num, j + 1, right);
}

void quciksort1(int num[], int left, int right)
{
    int last = 0; // 维护一个最小区域结束边界的指针
    int i;
    if (left >= right)
        return;
    swap(&num[left], &num[(left + right) / 2]);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if (num[i] < num[left])
            swap(&num[++last], &num[i]);
    }
    swap(&num[left], &num[last]);
    quciksort1(num, left, last - 1);
    quciksort1(num, last + 1, right);
}
#endif

/**
 * 4-12 运用printd函数的设计思想编写一个递归版本的itoa函数，即通过递归调用把整数转换为字符串
 */
#if 0
#define MAXLEN 100
void itoa(int num, char s[], int *i);
int main()
{
    char s[MAXLEN] = "";
    int i = 0;
    itoa(12, s, &i);
    s[i] = '\0';
    printf("%s\n", s);
    return 0;
}

void itoa(int num, char s[], int *i)
{
    int ret = 0;
    if (num == 0)
        return;
    ret = num % 10;
    itoa(num / 10, s, i);
    s[(*i)++] = ret + '0';
}
#endif

/**
 * 4-13 编写一个递归版本的reverse(s)函数，以将字符串s倒置
 */
#if 0
#define MAXLEN 100
void reverse(char s[], char ret[], int *start, int *end);

int main()
{
    char s[MAXLEN] = "abcdefg\n";
    char ret[MAXLEN] = "";
    int i = 0;
    int j = strlen(s) - 1;
    reverse(s, ret, &i, &j);
    printf("%s", ret);
    return 0;
}

void reverse(char s[], char ret[], int *start, int *end)
{
    if ((*start == strlen(s)))
        return;
    ret[(*start)++] = s[(*end)--];
    reverse(s, ret, start, end);
}

#endif

/**
 * 4-14 定义宏swap(t,x,y)以交换t类型的两个参数
 */
#if 0
#define swap(t, x, y) \
    {                 \
        t = x;        \
        x = y;        \
        y = t;        \
    }
int main()
{
    int a = 3;
    int b = 4;
    int tmp;
    swap(tmp, a, b);
    printf("a=%d b=%d\n", a, b);
    return 0;
}
#endif