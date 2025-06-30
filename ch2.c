#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <string.h>

/**
 * 2-1 编写一个程序以确定分别由signed及unsigned限定的char,short,int 与long类型
 * 变量的取值范围。采用打印标准头文件中的相应值以及直接计算两种方式实现。
 */
#if 0
int main()
{
    printf("=== <limits.h> ===\n");
    printf("CHAR_BIT    =%10d\n", CHAR_BIT);
    printf("SCHAR_MIN   =%10d\n", SCHAR_MIN);
    printf("SCHAR_MAX   =%10d\n", SCHAR_MAX);
    printf("UCHAR_MAX   =%10d\n", UCHAR_MAX);
    printf("CHAR_MIN    =%10d\n", CHAR_MIN);
    printf("CHAR_MAX    =%10d\n", CHAR_MAX);

    printf("SHRT_MIN    =%10d\n", SHRT_MIN);
    printf("SHRT_MAX    =%10d\n", SHRT_MAX);
    printf("USHRT_MAX   =%10u\n", USHRT_MAX);

    printf("INT_MIN     =%15d\n", INT_MIN);
    printf("INT_MAX     =%15d\n", INT_MAX);
    printf("UINT_MAX    =%15u\n", UINT_MAX);

    printf("LONG_MIN    =%24ld\n", LONG_MIN);
    printf("LONG_MAX    =%24ld\n", LONG_MAX);
    printf("ULONG_MAX   =%24lu\n", ULONG_MAX);

#ifdef LLONG_MAX
    printf("LLONG_MIN   =%24lld\n", LLONG_MIN);
    printf("LLONG_MAX   =%24lld\n", LLONG_MAX);
    printf("ULLONG_MAX  =%24llu\n", ULLONG_MAX);

#endif
    printf("\n=== <float.h> ===\n");
    printf("FLT_MIN     =%20.10e\n", FLT_MIN);
    printf("FLT_MAX     =%20.10e\n", FLT_MAX);
    printf("FLT_EPSILON =%20.10e\n", FLT_EPSILON);
    printf("FLT_DIG     =%5d\n", FLT_DIG);

    printf("DBL_MIN     =%21.10e\n", DBL_MIN);
    printf("DBL_MAX     =%21.10e\n", DBL_MAX);
    printf("DBL_EPSILON =%20.10e\n", DBL_EPSILON);
    printf("DBL_DIG     =%6d\n", DBL_DIG);

    return 0;
}
#endif

/**
 * 2-2 在不使用运算符&&或||的条件下编写一个与上面for循环语句等价的循环语句
 */
#if 0
#define LIM 100
int main()
{
    int i = 0;
    char c;
    char s[LIM] = "";
    while (i < LIM - 1)
    {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c;
        i++;
    }
    fputs(s, stdout);
    return 0;
}
#endif

/**
 * 2-3 编写函数htoi(s),把由十六进制数字组成的字符串(包含可选的前缀0x或0X)
 * 转换为与之等价的整型值。字符串中允许包含的数字包括:0~9,a~f以及A~F
 */

#if 0
#define MAXLEN 20
#define VALUE 55 // A-F换算成十进制差值
long htoi(char s[]);
int main()
{
    char s1[MAXLEN] = "";
    while ((fgets(s1, sizeof(s1), stdin)) != NULL)
    {
        int i = 0;
        while (s1[i] != '\0')
        {
            if (s1[i] == '\n')
            {
                s1[i] = '\0';
                break;
            }
            i++;
        }
        printf("%s转换成十进制的值:%ld\n", s1, htoi(s1));
    }
    return 0;
}
long htoi(char s[])
{
    int len = strlen(s);
    char s_tower[MAXLEN] = "";
    long n = 0;  // 累加十六进制计算结果
    int tmp = 0; // 计算字母转换成数字的值，A->10

    // 变大写
    for (int i = 0; i < len; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'f')
            s_tower[i] = s[i] - 'a' + 'A';
        else
            s_tower[i] = s[i];
    }

    for (int i = len - 1, index = 0; i >= 0; i--, index++)
    {
        if (i == 0 && s_tower[i] == '0')
            continue;
        if ((i == 1 && s_tower[i] == 'x') || (i == 1 && s_tower[i] == 'X'))
            continue;

        if (s_tower[i] >= 'A' && s_tower[i] <= 'F')
        {
            tmp = s_tower[i] - VALUE;
            n = n + tmp * (1 << (4 * index));
        }
        else if (s_tower[i] >= '0' && s_tower[i] <= '9')
        {
            tmp = s_tower[i] - '0';
            n = n + tmp * (1 << (4 * index));
        }
        else
        {
            printf("字符串格式有误,请输入格式为0x{a-f}{A-F}{0-9}格式的字符串\n");
            break;
        }
    }
    return n;
}
#endif

/**
 * 2-4 squeeze(s1,s2),将字符串s1中任何与字符串s2中字符匹配的字符都删除
 */
#if 0
#define MAXLEN 256
void squeeze(char s1[], char s2[]);

int main()
{
    char s1[MAXLEN] = "hello,world\n";
    char s2[MAXLEN] = "hello";
    squeeze(s1, s2);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    int table[MAXLEN] = {0};
    int i = 0;
    int j = 0;
    while (s2[i] != '\0')
    {
        table[(unsigned char)s2[i]] = 1;
        i++;
    }
    i = 0;
    while (s1[i] != '\0')
    {
        if (!table[(unsigned char)s1[i]])
            s1[j++] = s1[i];
        i++;
    }
    s1[j] = '\0';
    fputs(s1, stdout);
}
#endif

/**
 * 2-5 编写函数any(s1,s2),将字符串s2中的任一字符在字符串s1中第一次出现的位置作为结果返回。
 * 如果s1中不包含s2中的字符，则返回-1.
 */
#if 0
#define MAXLEN 256

int any(char s1[], char s2[]);
int main()
{
    char s1[MAXLEN] = "abcdefgh";
    // char s2[MAXLEN] = "mmmdddeeeee";
    char s3[MAXLEN] = "sssskkkkmmmm";
    printf("pos is:%d\n", any(s1, s3));
    return 0;
}

int any(char s1[], char s2[])
{
    int table[MAXLEN] = {0};
    for (int i = 0; s2[i] != '\0'; i++)
        table[(unsigned char)s2[i]] = 1;
    for (int i = 0; s1[i] != '\0'; i++)
        if (table[(unsigned char)s1[i]])
            return i;
    return -1;
}
#endif

/**
 * 2-6 编写一个函数setbits(x,p,n,y),该函数返回对x执行下列操作后的结果值:
 * 将x中从第p位开始的n个(二进制)位设置为y中最右边n位的值，x的其余各位保持不变
 */
#if 0
unsigned setbits(unsigned x, int p, int n, unsigned y);
int main()
{
    unsigned x = 170;
    unsigned y = 240;
    printf("%d\n", setbits(x, 4, 3, y));
    return 0;
}
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    // 准备y右边n位,同时高位清零
    unsigned y_bit = y & ~(~0 << n);
    // 把这n位，移动到x要设置的指定位置上,说白了，x从右数p位开始的n个，
    // 笼统理解就是x中间掏空一部分，让你把空的这部分用y的那部分填充
    unsigned y_ready = y_bit << (p + 1 - n);
    // 准备掩码，用来清空x那部分需要替换位的值，但别的位不能动
    //(1<<n)-1,设置最右边n位为1,然后一样向左移动到p位置上，对齐,然后取反，对齐的部分掩码值为全0
    // 其余位为全1,达到清除制定部分，不影响剩余部分
    unsigned mask = ~(((1 << n) - 1) << (p + 1 - n));
    // 和掩码与，清空位置，然后和y准备的值与，改掉指定部分
    return (x & mask) | y_ready;
}
#endif

/**
 * 2-7 编写一个函数invert(x,p,n),该函数返回对x执行下列操作后的结果值:将x中从第p位开始的
 * n个(二进制)位求反(即，1变成0,0变成1),x的其余各位保持不变
 */
#if 0
unsigned invert(unsigned x, int p, int n);

int main()
{
    // 00000001
    // 00011100 <-这是mask
    // 00011101
    unsigned x = 1;
    printf("%u\n", invert(x, 4, 3));
    return 0;
}
unsigned invert(unsigned x, int p, int n)
{
    // n个位置求反，就是这n个位与1亦或
    // 还是老套路，构造掩码,同时移动到指定位置
    // 当然这次不用求反的,指定位全1,剩余全0,0和任何数亦或都是那个数自己
    unsigned mask = ((1 << n) - 1) << (p + 1 - n);
    return x ^ mask;
}
#endif

/**
 * 编写一个函数rightrot(x,n),该函数返回将x循环右移(即从最右端移出的位将从最左端移入)n(二进制)位后所得到的值
 */
#if 0
unsigned rightrot(unsigned x, int n);
int main()
{
    unsigned x = 1;
    printf("%u\n", rightrot(x, 4));
    return 0;
}
unsigned rightrot(unsigned x, int n)
{
    unsigned width = sizeof(x) * 8;
    printf("width%u\n", width);
    return (x >> n) | (x << (width - n));
}
#endif

/**
 * 2-9 在求对二的补码时，表达式x &= (x-1)可以删除x中最右边值为1的一个二进制位。请解释这样做的道理。
 * 用这一方法重写bitcount函数，以加快其执行速度
 */
#if 0
int bitcount(unsigned x);

int main()
{
    // x&(x-1)清最右边的1,因为x-1的时候，x最右边的1会变成0,它右边的所有位会变成1
    // 这样与的时候，最右边那个1就会被清掉
    unsigned x = 78;
    printf("%u has %u bit 1\n", x, bitcount(x));
    return 0;
}

int bitcount(unsigned x)
{
    int b;
    // 这个程序是为了计算x里面有多少个1
    for (b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}
#endif

/**
 * 2-10 重新编写将大写字母转换为小写字母的函数lower,并用条件表达式替代其中的if-else结j构
 */
#if 0
#define MAXLEN 100
char *lower(char s[]);
int main()
{
    char s[MAXLEN] = "AcKK,kkasdDDMKJLLLLJLJKJLJLL";
    printf("%s\n", lower(s));
    return 0;
}
char *lower(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] - 'A' + 'a' : s[i];
        i++;
    }
    return s;
}
#endif