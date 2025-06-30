#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/**
 * 5-1 上面例子中，如果符号+或-的后面紧跟的不是数字，getint函数将把符号视为数字0的有效表达方式。
 * 修改该函数，将这种形式的+或-符号重新写回到输入流中
 */
#if 0
#define MAXLEN 100
int getch(void);
void ungetch(int ch);

int getint(int *pn);

int main()
{
    int num = 0;
    getint(&num);
    printf("num is %d\n", num);
    return 0;
}

int buff[MAXLEN] = {0};
int bp = 0;
int getch(void)
{
    return (bp > 0) ? buff[--bp] : getchar();
}
void ungetch(int ch)
{
    if (bp >= MAXLEN)
    {
        printf("buff already full...\n");
        return;
    }
    buff[bp++] = ch;
}

int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        // 保存+或者-
        int tmp = c;
        // 多读一个
        c = getch();
        if (!isdigit(c))
        {
            ungetch(c);
            ungetch(tmp);
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return 1;
}

#endif

/**
 * 5-2 模仿函数getint的实现方法，编写一个读取浮点数的函数getfloat
 * getfloat函数的返回值应该是什么类型
 */
#if 0
#define MAXLEN 100
int getch(void);
void ungetch(int ch);

int getfloat(double *pn);

int main()
{
    double num = 0.0;
    getfloat(&num);
    printf("double num :%.10lf\n", num);
    return 0;
}

int buff[MAXLEN] = {0.0};
int bp = 0;
int getch(void)
{
    return (bp > 0) ? buff[--bp] : getchar();
}
void ungetch(int ch)
{
    if (bp >= MAXLEN)
    {
        printf("buff already full...\n");
        return;
    }
    buff[bp++] = ch;
}

int getfloat(double *pn)
{
    int c;
    int sign;
    double power = 1.0;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        // 保存+或者-
        int tmp = c;
        // 多读一个
        c = getch();
        if (!isdigit(c) && c != '.')
        {
            ungetch(c);
            ungetch(tmp);
            return 0;
        }
    }

    double val = 0.0;
    // 整数部分
    while (isdigit(c))
    {
        val = 10.0 * val + (c - '0');
        c = getch();
    }
    // 小数部分
    if (c == '.')
    {
        power = 1.0;
        c = getch();
        while (isdigit(c))
        {
            val = 10.0 * val + (c - '0');
            power *= 10.0;
            c = getch();
        }
    }
    *pn = sign * val / power;

    if (c != EOF)
        ungetch(c);
    return 1;
}

#endif

/**
 * 5-3 用指针方式实现第二章中的函数strcat
 * 函数strcat(s,t)将t指向的字符串复制到s指向的字符串的尾j部
 */
#if 0
#define MAXLEN 100
void mystrcat(char *s, char *t);
int main()
{
    // 必须保证s有足够大的空间容纳t
    char s[MAXLEN] = "abcdefg";
    char t[MAXLEN] = "hello,world\n";
    mystrcat(s, t);
    printf("now str s is: '%s\n'", s);
    return 0;
}

void mystrcat(char *s, char *t)
{
    int len = strlen(s);
    char *now = s + len;
    while ((*now++ = *t++) != '\0')
        ;
}
#endif

/**
 * 5-4 编写函数strend(s,t),如果字符串t出现在字符串s的尾部，该函数返回1,否则返回0
 */
#if 0
#define MAXLEN 100
int strend(char *s, char *t);
int main()
{
    char s[MAXLEN] = "abcedfghi";
    char t[MAXLEN] = "ghi";
    printf("%d\n", strend(s, t));
    return 0;
}

int strend(char *s, char *t)
{
    int t_len = strlen(t);
    int s_len = strlen(s);
    if (s_len < t_len)
        return 0;

    int i = 0;
    char *s_end = s + (s_len - t_len);
    char *t_ini = t;

    while (s_end >= s)
    {
        t_ini = t;
        i = 0;
        while (*t_ini != '\0')
        {
            if (*(s_end + i) == *t_ini++)
                i++;
            else
                break;
        }
        if (i == t_len)
            return 1;
        s_end--;
    }

    return 0;
}
#endif

/**
 * 5-5 实现库函数strncpy,strncat,strncmp,它们最多对参数字符串中的前n个字符
 * 进行操作.例如，函数strncpy(s,t,n)将t中最多前n个字符复制到s中。
 */
#if 0
#define MAXLEN 100
char *my_strncpy(char *s, char *t, int n);
char *my_strncat(char *s, char *t, int n);
char *my_strncmp(const char *s, const char *t, int n);

int main()
{
    char dst[MAXLEN] = "";
    // char src[MAXLEN] = "hello,world!\n";

    char src_short[MAXLEN] = "hell\t1";
    printf("dst str is : %s", my_strncpy(dst, src_short, 2));
    return 0;
}

char *my_strncpy(char *s, char *t, int n)
{
    int t_len = strlen(t);
    char *t_end = NULL; // 拷贝结束的下标
    char *t_start = t;
    char *s_init = s;

    // 源字符串空的
    if (t == NULL || t_len == 0)
        return NULL;

    if (n < t_len)
        t_end = t + n;
    else
        t_end = t + t_len;

    while (t_start != t_end)
        *s_init++ = *t_start++;
    *s_init = '\0';
    return s;
}

char *my_strncat(char *s, char *t, int n)
{
    char *start = s;
    while (*s)
        s++;
    while (n-- > 0 && (*s++ = *t++))
        ;
    *s = '\0';
    return start;
}

char *my_strncmp(const char *s, const char *t, int n)
{
    for (; n > 0; s++, t++, n--)
    {
        if (*s != *t)
            return *s - *t;
        if (*s == '\0')
            return 0;
    }
    return 0;
}

#endif

/**
 * 5-6 采用指针而非数组索引方式改写前面章节和练习中的某些程序
 */
/**
 * 5-7 重写函数readlines,将输入的文本行存储到由main函数提供的一个数组中，而不是存储到调用alloc
 * 分配的存储空间中，该函数的运行速度比改写前快多少
 */

/**
 * 5-8 函数day_of_year和month_day中没有进行错误检查，请解决该问题
 */
#if 0
int main()
{
}
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day)
{
    int i, leap;
    if (year <= 0 || month < 0 || month > 12)
        return -1;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    int realYear = 0;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    realYear = leap ? 365 : 366;
    if (year < 0 || yearday > realYear && leap == 0 || yearday > realYear && leap == 1)
        return -1;

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

#endif

/**
 * 5-9 用指针方式代替数组下标方式改写函数day_of_year和month_day
 */
#if 0
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
int main()
{
    int year = 2025;
    int month = 6;
    int day = 19;
    printf("%d年%d月%d日是%d年的第%d天\n", year, month, day, year, day_of_year(year, month, day));
}
static char *daytab[] = {
    (char[]){0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    (char[]){0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day)
{
    int i, leap;
    if (year <= 0 || month < 0 || month > 12)
        return -1;
    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    printf("%d\n", leap);
    for (i = 1; i < month; i++)
        // day += daytab[leap][i];
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    int realYear = 0;
    leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);

    realYear = leap ? 365 : 366;
    if (year < 0 || (yearday > realYear && leap == 0) || (yearday > realYear && leap == 1))
        return;

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
#endif

/**
 * find
 */

#if 0
#define MAXLINE 1000

int pgetline(char *line, int max);
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while ((c = *++argv[0]) != '\0')
        {
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                return 1;
            }
        }
    }
    if (argc != 1)
    {
        printf("Usage: find -x -n pattern\n");
        return 1;
    }
    while (pgetline(line, MAXLINE) > 0)
    {
        lineno++;
        if ((strstr(line, *argv) != NULL) != except)
        {
            if (number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }
    return found;
}
int pgetline(char *s, int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
#endif

/**
 * 练习5-10 编写程序expr,以计算从命令行输入的逆波兰表达式的值，其中每个运算符或操作数用一个单独的参数表示
 * 例如命令
 * expr 2 3 4 + *
 * 将计算表达式2*（3+4）的值
 */
#if 0

void push(double num);
int pop(double *num);
int isEmpty();

int main(int argc, char *argv[])
{
    char *arg = NULL;
    double val;
    double op2 = 0.0;
    double op1 = 0.0;
    int arg_wrong = 0;
    while (--argc > 0)
    {
        arg = *++argv;
        if (sscanf(arg, "%lf", &val) == 1)
            push(val);
        else if (strcmp(arg, "+") == 0)
        {
            if (pop(&op2) && pop(&op1))
                push(op1 + op2);
            else
                arg_wrong = 1;
        }
        else if (strcmp(arg, "*") == 0)
        {
            if (pop(&op2) && pop(&op1))
                push(op1 * op2);
            else
                arg_wrong = 1;
        }
        else if (strcmp(arg, "-") == 0)
        {
            if (pop(&op2) && pop(&op1))
                push(op1 - op2);
            else
                arg_wrong = 1;
        }
        else if (strcmp(arg, "/") == 0)
        {
            if (pop(&op2) && pop(&op1))
            {
                if (op2 != 0.0)
                    push(op1 / op2);
                else
                    printf("zero div\n");
            }
            else
                arg_wrong = 1;
        }
        else if (arg_wrong)
            printf("miss arg,expr is wrong\n");
        else
            printf("error command%s\n", arg);
    }
    if (pop(&op1) && isEmpty())
        printf("\t%.8g\n", op1);
    else
        printf("wrong expr\n");
    return 0;
}

#define MAXLEN 100
int bp = 0; // 指向下一个空位也就是栈顶的位置
double stackbuf[MAXLEN] = {0};
void push(double num)
{
    if (bp >= MAXLEN)
    {
        printf("push faild,stack is full\n");
        return;
    }
    stackbuf[bp++] = num;
}
int pop(double *num)
{
    if (bp == 0)
    {
        printf("pop faild,stack is empyt\n");
        return 0;
    }
    else
        *num = stackbuf[--bp];
    return 1;
}
int isEmpty()
{
    return bp == 0;
}
#endif

/**
 * 5-11 修改程序entab和decab,使它们接受一组作为参数的制表符停止位，如果启动程序时不带参数，则使用默认的制表符停止位设置
 */

#if 0
#define MAXLEN 200
#define ENDOFPOS 8
// 替换为最少数量的制表符和空格，一个制表符或一个空格都可以到达下一个制表符终止位置，用制表符
// 比如 这是七个空格*******，我再来一个tab和一个空格都可以达到制表符终止位
// 但是我用一个tab,整个我就用了一个制表符，如果我用空格，整个可能用8个空格

void entab(int *arr, int len);
void detab(int *arr, int len);
void show_space_other(char buf[]);

int main(int argc, char *argv[])
{
    int stopArr[MAXLEN] = {0};
    char *arg = NULL;
    int val = 0;
    int i = 0;

    while (--argc > 0)
    {
        arg = *++argv;
        if (sscanf(arg, "%d", &val) == 1)
            stopArr[i++] = val;
    }
    // entab(stopArr, i);
    detab(stopArr, i);
    return 0;
}
void entab(int *arr, int len)
{
    char buf[MAXLEN] = "";
    int to_tabstop;  // 到下一个终止位置还需要多大距离
    int spacecount;  // 连续空格数量
    int current_row; // 当前列
    int read;        // 读指针
    int write;       // 写指针

    while ((fgets(buf, sizeof(buf), stdin)) != NULL)
    {
        show_space_other(buf);
        read = 0;
        write = 0;
        spacecount = 0;
        current_row = 0;
        while (buf[read] != '\0')
        {
            if (buf[read] == ' ')
            {
                // 读连续空格
                while (buf[read] == ' ')
                {
                    spacecount++;
                    read++;
                }
                while (spacecount > 0)
                {
                    // to_tabstop = ENDOFPOS - (current_row % ENDOFPOS); // 到下一个end距离
                    if (len == 0)
                        to_tabstop = ENDOFPOS - (current_row % ENDOFPOS); // 到下一个end距离
                    else
                    {
                        to_tabstop = 0;
                        for (int i = 0; i < len; i++)
                        {
                            if (current_row < arr[i])
                            {
                                to_tabstop = arr[i] - current_row;
                                break;
                            }
                        }
                        if (to_tabstop == 0)
                        {
                            buf[write++] = ' ';
                            current_row++;
                            spacecount--;
                            continue;
                        }
                    }

                    if (spacecount >= to_tabstop) // 空格长度够到下一个end,换\t
                    {
                        buf[write++] = '\t';
                        current_row += to_tabstop;
                        spacecount -= to_tabstop;
                    }
                    else // 不够，原样写空格，注意这里，已经是空格被\t后，剩余空格的数量,最终保证处理后的字符串和原来的对齐
                    {
                        buf[write++] = ' ';
                        current_row++;
                        spacecount--;
                    }
                }
            }
            else
            {
                buf[write++] = buf[read++];
                current_row++;
            }
        }
        buf[write] = '\0';
        fputs(buf, stdout);
        show_space_other(buf);
    }
}

void detab(int *arr, int len)
{
    char buf[MAXLEN] = "";
    char buf_out[MAXLEN] = "";
    int current, space_count;
    int read, write;
    while ((fgets(buf, sizeof(buf), stdin)) != NULL)
    {
        current = 0; // 这个变量是记录下一个终止位置的index
        read = 0;
        write = 0;
        show_space_other(buf);
        while (buf[read] != '\0')
        {
            if (buf[read] == '\t')
            {
                if (len == 0)
                    space_count = ENDOFPOS - (current % ENDOFPOS);
                else
                {
                    space_count = 0;
                    for (int i = 0; i < len; i++)
                    {
                        if (current < arr[i])
                        {
                            space_count = arr[i] - current;
                            break;
                        }
                    }
                    if (space_count == 0)
                        space_count = ENDOFPOS - (current % ENDOFPOS);
                }

                current += space_count;
                for (int k = 0; k < space_count; k++)
                    buf_out[write++] = ' ';
                read++;
            }
            else
            {
                buf_out[write++] = buf[read++];
                current++;
            }
        }
        buf_out[write] = '\0';
        fputs(buf_out, stdout);
        show_space_other(buf_out);
    }
}

void show_space_other(char buf[])
{
    int i;
    i = 0;
    while (buf[i] != '\0')
    {
        if (buf[i] == ' ')
            printf("'_'");
        else if (buf[i] == '\t')
            printf("\\t");
        else
            putchar(buf[i]);
        ++i;
    }
}
#endif

/**
 * 5-12 对程序entab和detab的功能做一些扩充，以接受下列缩写的命令
 */

#if 0
#endif

/**
 * 5-13 编写程序tail,将其输入中的最后n行打印出来。默认情况下，n的值为10，但可通过一个可选参数改变n的值
 * 因此命令 tail -n将打印其输入的最后n行。无论输入或n的值是否合理，该程序都应该能正常运行。
 */
#if 0
#define MAXLEN 100
void tail(int num);
int main(int argc, char *argv[])
{
    int val = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        if (sscanf(++argv[0], "%d", &val) != 1 || val < 0)
        {
            fprintf(stderr, "参数无效,使用默认参数10\n");
            val = 10;
        }
    }
    tail(val);
    return 0;
}

void tail(int num)
{
    char *buf[MAXLEN] = {NULL};
    char str[MAXLEN] = "";

    int i = 0;
    int start = 0;
    while (i < MAXLEN && fgets(str, sizeof(str), stdin) != NULL)
    {

        buf[i] = malloc(strlen(str) + 1);
        if (buf[i] == NULL)
        {
            fprintf(stderr, "内存分配失败\n");
            return;
        }
        strcpy(buf[i], str);
        i++;
    }

    start = i > num ? (i - num) : 0;

    for (int j = start; j < i; j++)
        printf("%s", buf[j]);

    for (int j = 0; j < i; j++)
        free(buf[j]);
}
#endif

/**
 * new sort function
 */
#if 0

#define MAXLINES 5000
#define MAXLEN 1000
char *lineptr[MAXLINES];

int my_getline(char *s, int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

void swap(void *v[], int, int);
int numcmp(char *s1, char *s2);

int numcmp_wrapper(void *a, void *b);
int strcmp_wrapper(void *a, void *b);

void clean(int len);

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int retNum = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp_wrapper : strcmp_wrapper));
        writelines(lineptr, nlines);
    }
    else
    {
        printf("input too big to sort\n");
        retNum = 1;
    }
    clean(nlines);
    return retNum;
}

void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    my_qsort(v, left, last - 1, comp);
    my_qsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int my_getline(char *s, int lim)
{
    int c;
    char *start = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = my_getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
            return -1;
        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void clean(int len)
{
    for (int i = 0; i < len; i++)
    {
        if (lineptr[i] != NULL)
            free(lineptr[i]);
    }
}

int numcmp_wrapper(void *a, void *b)
{
    return numcmp((char *)a, (char *)b);
}
int strcmp_wrapper(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

#endif

/**
 * 5-14 修改排序程序，使它能处理-r标记。该标记表明，以逆序(递减)方式排序。要保证-r和-n能够组合在一起使用
 * 5-15 增加选项-f,使得排序过程不考虑字母大小写之间的区别。例如，比较a和A时认为它们相等
 * 5-16 增加选项-d，(代表目录顺序)。该选项表明，只对字母，数字和空格进行比较。要保证该选项可以和-f组合在一起使用。
 * 5-17 增加字段处理功能，以使得排序程序可以根据行内的不同字段进行排序，每个字段按照一个单独的选项集合进行排序。
 */
#if 0
#define MAXLINES 5000
#define MAXLEN 1000
char *lineptr[MAXLINES];
typedef struct sort_option
{
    int numeric;   //-n
    int reverse;   //-r
    int fold_case; //-f
    int directory; //-d
    int field;     //-k
} st_so;

int my_getline(char *s, int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int, int);

// 自定义比较函数
int compare(const char *s1, const char *s2, const st_so *opt);
// 桥接函数
int wrapper(const void *a, const void *b, const st_so *opt);
// 排序函数
void my_qsort(void *lineptr[], int left, int right, int (*comp)(const void *, const void *, const st_so *), const st_so *opt);
// 忽略大小写比较
int charcmp(const char *s1, const char *s2, const st_so *opt);
// 过滤字符参数
int filtered_char(const char **p, const st_so *opt);

// 跳过指定字段
const char *skip_to_field(const char *line, int field);

void clean(int len);

int main(int argc, char *argv[])
{
    st_so option = {0};
    int nlines;
    int retNum = 0;
    char c;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while ((c = *++argv[0]))
        {
            switch (c)
            {
            case 'n':
                option.numeric = 1;
                break;
            case 'r':
                option.reverse = 1;
                break;
            case 'f':
                option.fold_case = 1;
                break;
            case 'd':
                option.directory = 1;
                break;
            case 'k':
                sscanf(++argv[0], "%d", &option.field);
                break;
            default:
                break;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        my_qsort((void **)lineptr, 0, nlines - 1, wrapper, &option);
        writelines(lineptr, nlines);
    }
    else
    {
        printf("input too big to sort\n");
        retNum = 1;
    }
    clean(nlines);
    return retNum;
}

void my_qsort(void *lineptr[], int left, int right, int (*comp)(const void *, const void *, const st_so *), const st_so *opt)
{
    int i, last;
    if (left >= right)
        return;
    swap(lineptr, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if ((*comp)(lineptr[i], lineptr[left], opt) < 0)
            swap(lineptr, ++last, i);
    }
    swap(lineptr, left, last);
    my_qsort(lineptr, left, last - 1, comp, opt);
    my_qsort(lineptr, last + 1, right, comp, opt);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int my_getline(char *s, int lim)
{
    int c;
    char *start = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = my_getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
            return -1;
        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void clean(int len)
{
    for (int i = 0; i < len; i++)
    {
        if (lineptr[i] != NULL)
            free(lineptr[i]);
    }
}

int compare(const char *s1, const char *s2, const st_so *opt)
{
    int result = 0;
    const char *a = s1;
    const char *b = s2;

    if (opt->field > 0)
    {
        a = skip_to_field(s1, opt->field);
        b = skip_to_field(s2, opt->field);
    }

    if (opt->numeric)
    {
        double v1 = atof(a);
        double v2 = atof(b);
        result = (v1 < v2) ? -1 : ((v1 > v2) ? 1 : 0);
    }
    else
    {
        result = charcmp(a, b, opt);
    }
    if (opt->reverse)
        result = -result;
    return result;
}
// wrapper函数目的是为了给myqsort把compare函数传过去,
int wrapper(const void *a, const void *b, const st_so *opt)
{
    return compare((char *)a, (char *)b, opt);
}

int charcmp(const char *s1, const char *s2, const st_so *opt)
{
    char c1, c2;
    do
    {
        c1 = filtered_char(&s1, opt);
        c2 = filtered_char(&s2, opt);
        if (c1 != c2)
            return c1 - c2;
    } while (c1 != '\0' && c2 != '\0');
    return c1 - c2;
}

int filtered_char(const char **p, const st_so *opt)
{
    char c;
    do
    {
        c = *(*p)++;
    } while (opt->directory && !isalnum(c) && c != ' ' && c != '\0');
    if (opt->fold_case)
        c = tolower((unsigned char)c);
    return c;
}

const char *skip_to_field(const char *line, int field)
{
    while (field-- > 0)
    {
        while (*line != ' ' && *line != '\t' && *line != '\0')
            line++;
        while (*line == ' ' && *line == '\t')
            line++;
    }
    return line;
}

#endif

/**
 * 5-18 修改dlc程序，使它能够处理输入中的错误
 * 5-19 修改undcl程序，使它在把文字描述转换为声明的过程中不会生成多余的圆括号
 * 5-20 扩展dcl程序的功能，使它能够处理包含其它成分的声明，例如带有函数参数类型的声明，带有类似于const限定符的声明等
 * 未完成
 */
#if 0
#define MAXTOKEN 100
#define MAXLEN 1000
enum
{
    NAME,
    BRACKETS
};

int dcl(void);
int dirdcl(void);

int getch(void);
void ungetch(int c);
int gettoken(void);
int tokentype; // token类型
char token[MAXTOKEN];
char name[MAXTOKEN];     // 存储变量名
char datatype[MAXTOKEN]; // 存储基本类型,int char
char out[MAXLEN];        // 输出字符串

int main()
{
    // char temp[MAXTOKEN + MAXLEN] = "";
    // while (gettoken() != EOF)
    // {
    //     strcpy(datatype, token);
    //     out[0] = '\0';
    //     gettoken();
    //     while ((tokentype) != '\n')
    //     {
    //         if (tokentype == PARENS || tokentype == BRACKETS)
    //             strcat(out, token);
    //         else if (tokentype == '*')
    //         {
    //             snprintf(temp, sizeof(temp), "(*%s)", out);
    //             strcpy(out, temp);
    //         }
    //         else if (tokentype == NAME)
    //         {
    //             strcpy(name, token);
    //             snprintf(temp, sizeof(temp), "%s %s", token, out);
    //             strcpy(out, temp);
    //         }
    //         else
    //             printf("invalid input at %s\n", token);
    //         gettoken();
    //     }
    //     printf("%s: %s %s\n", name, datatype, out);
    // }

    while (gettoken() != EOF)
    {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

int dcl(void)
{
    int ns;
    while (tokentype == '*')
    {
        ns++;
        gettoken();
    }

    if (dirdcl() != 0)
        return 1;
    while (ns-- > 0)
    {
        char temp[1100];
        sprintf(temp, "pointer to %s", out);
        strcpy(out, temp);
    }
    return 0;
}

int dirdcl(void)
{
    if (tokentype == '(')
    {
        gettoken();
        if (dcl() != 0)
            return -1;
        if (tokentype != ')')
        {
            printf("error:missing )\n");
            return -1;
        }
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
    {
        printf("error:expected name or (dcl)\n");
        return -1;
    }
    while (gettoken(), tokentype = '(' || tokentype == BRACKETS)
    {
        if (tokentype == '(')
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
    return 0;
}
int gettoken(void)
{
    int c;
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(' || c == ')')
    {
        *p++ = c;
        *p = '\0';
        return tokentype = c;
    }
    // 完整匹配[]
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']' && p < (token + MAXTOKEN - 1);)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) // 针对字母,也就是变量名
    {
        // isalnum匹配数字和字母
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
    {
        *p++ = c;
        *p = '\0';
        return tokentype = c;
    }
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
#endif
