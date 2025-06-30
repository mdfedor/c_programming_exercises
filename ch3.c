#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * 3-1 在上面有关折半查找的例子中，while循环语句内共执行了两次测试，其实只要一次就足够
 * 代价是将更多的测试在循环外执行。重写该函数，使得在循环内部只执行一次测试。比较两种版本
 * 函数的运行时间
 */
#if 0
#define MAXLEN 10000

int binsearch(int x, int v[], int n);

int main()
{
    int num[MAXLEN] = {0};
    for (int i = 0; i < MAXLEN; i++)
        num[i] = i + 1;
    int search = 2989;
    printf("ret is %d\n", binsearch(search, num, MAXLEN));
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        // 在里面只有一个判断时候，核心是卡死一个边界，在目标位置的前一个或后一个位置，
        // 然后不断让另一个逼近这个位置，跳出循环的时候就是要找的值，如果跳出边界没找到，那就是真没这个值
        if (x <= v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (low < n && v[low] == x)
        return low;
    else
        return -1;
}
#endif

/**
 * 3-2 编写一个函数escape(s,t),将字符串t复制到字符串s中，并在复制过程中将换行符，制表符等不可见字符分别转换为\n,\t
 * 等相应的可见的转义字符序列。要求使用switch语句。再编写一个具有相反功能的函数，在复制过程中将转义字符序列转换为实际字符
 */
#if 0
#define MAXLEN 100
void escape(char s[], char t[]);
void descape(char s[], char t[]);

int main()
{
    char s1[MAXLEN] = "";
    char s2[MAXLEN] = "abc\t   defdef\n\n\n\n";
    char s3[MAXLEN] = "";

    while (fgets(s3, sizeof(s3), stdin) != NULL)
        escape(s1, s3);
    descape(s1, s2);
    return 0;
}

void escape(char s[], char t[])
{
    int i = 0;
    int k = 0;
    while (t[i] != '\0')
    {
        switch (t[i])
        {
        case '\t':
        {
            s[k++] = '\\';
            s[k] = 't';
        }
        break;
        case '\n':
        {
            s[k++] = '\\';
            s[k] = 'n';
        }
        break;
        default:
            s[k] = t[i];
            break;
        }
        k++;
        i++;
    }
    s[k] = '\0';
    fputs(s, stdout);
}

void descape(char s[], char t[])
{
    int i = 0;
    while (t[i] != '\0')
    {
        s[i] = t[i];
        i++;
    }
    s[i] = '\0';
    fputs(s, stdout);
}
#endif
/**
 * 插入排序&shell排序
 */
#if 0
void insert_sort(int arr[], int len);
void shllsort(int v[], int n);
void print_arr(int arr[], int n);
int main()
{
    int num[] = {9, 2, 5, 1, 6, 7, 3, 8, 4, 11};
    insert_sort(num, sizeof(num) / sizeof(int));

    int num1[] = {9, 2, 5, 1, 6, 7, 3, 8, 4, 11};
    shllsort(num1, sizeof(num1) / sizeof(int));

    return 0;
}

void insert_sort(int arr[], int len)
{

    printf("insertsort排序前\n");
    print_arr(arr, len);
    int j = 0;
    int key = 0;
    for (int i = 1; i < len; i++)
    {
        key = arr[i]; // 要处理的元素
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j]; // 此时，相当于arr[j]元素已经空了
            j--;
        }
        arr[j + 1] = key; // j最多能减成-1,表示处理的元素小于前面的每一个元素,这里j+1始终表示是空位
    }
    printf("insertsort排序后\n");
    print_arr(arr, len);
}

void shllsort(int v[], int n)
{

    printf("shellsort排序前\n");
    print_arr(v, n);
    int gap, i, j, tmp;
    // 最外层控制粒度
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        // 中间这层是处理某个gap下，到结束部分每个元素
        for (i = gap; i < n; i++)
        {
            tmp = v[i]; // 待处理元素
            // 这一步理解j-gap的意思，j初始是gap,j-gap,就是跨度为gap间的两个元素
            // 进行大小比较，然后位置互换，这是相对于插入排序减少大量移动的关键，因为它直接隔着gap的距离就比较了
            // 再一个，粒度越大，这里交换的次数越少，粒度越小，交换的次数越多，因为j-=gap控制了,gap越大，跳出循环越wa早
            for (j = i; j >= gap && v[j - gap] > tmp; j -= gap)
                v[j] = v[j - gap]; // 前面的大元素直接来后面，前面位置空出来了
            v[j] = tmp;
        }
    }
    printf("shellsort排序后\n");
    print_arr(v, n);
}

void print_arr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
#endif

/**
 * 3-3 编写函数expand(s1,s2),将字符串s1中类似于a-z一类的速记符号在字符串s2中扩展为等价的完整列表abc....xyz
 * 该函数可以处理大小写字母和数字，并可以处理a-b-c,a-z0-9与-a-z等类似情况。作为前导和尾随的-字符原样排印
 */
#if 0
#define MAXLEN 500
char *expand(char s1[], char s2[]);
int main()
{
    char s1[MAXLEN] = "a-b-ca-z0-9-a-z-a-a1111----a---z---";
    char s2[MAXLEN] = "";
    printf("%s\n", expand(s1, s2));
}

char *expand(char s1[], char s2[])
{

    int i = 0;
    int j = 0;
    char c;
    // c记录每个输入的字符
    while ((c = s1[i++]) != '\0')
    {
        if (s1[i] == '-' && i > 0 &&
            ((islower(c) && islower(s1[i + 1])) ||
             (isupper(c) && isupper(s1[i + 1])) ||
             (isdigit(c) && isdigit(s1[i + 1]))) &&
            c < s1[i + 1])
        {
            char end = s1[i + 1];
            while (c <= end)
                s2[j++] = c++;
            i += 2;
        }
        else
            s2[j++] = c;
    }
    return s2;
}
#endif

/**
 * 3-4 在二进制补码表示中，我们写的itoa函数不能正确处理最大的负数
 * 即n=-2^(wordsize-1)的情况。为什么不行
 * 修改你的itoa,让它不管在哪种机器上都能正确打印这个值
 */
#if 0
#define MAXLEN 100
void itoa(int n, char s[]);
char *reverse(char s[]);
int main()
{
    // int 类型最大范围 -2^32~2^31-1
    // 正数最大+2147483647
    // 负数最小-2147483648
    // 所以当n=-n时候，当这个数是最小的-2147483648,它取相反数直接溢出
    // int num = 2147483647;
    int num1 = -2147483648;
    char s[MAXLEN] = "";
    itoa(num1, s);
    return 0;
}
void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;
    do
    {
        s[i++] = abs(n % 10) + '0';
        n /= 10;
    } while (n != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    printf("num: %d -> string: %s\n", sign, reverse(s));
}
char *reverse(char s[])
{
    int len = strlen(s);
    int tmp;
    for (int i = 0, j = len - 1; i < len / 2; i++, j--)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    return s;
}
#endif

/**
 * 3-5 编写函数itob(n,s,b),将整数n转换为b为底的数，并将转换结果以字符的形式保存到字符串s中。
 * 例如，itob(n,s,16)把整数n格式化成十六进制整数保存在s中
 */
#if 0
#define MAXLEN 100
char *itob(int n, char s[], int b);
char *reverse(char s[]);
int main()
{
    int num = 100;
    int b = 16;
    char s[MAXLEN] = "";

    char *ret = itob(num, s, b);
    if (ret)
        printf("num: %d转换为%d进制后的值%s%s\n", num, b, (b == 16) ? "0x" : "", ret);
    return 0;
}

char *itob(int n, char s[], int b)
{
    char table[] = "0123456789ABCDEF";
    int i = 0;
    int sign = 0;
    if (b < 2 || b > 16)
    {
        printf("进制有误,进制数范围2～16\n");
        return NULL;
    }
    if (b == 10)
        sign = n;
    n = abs(n);
    do
    {
        s[i++] = table[(n % b)];
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    return reverse(s);
}
char *reverse(char s[])
{
    int len = strlen(s);
    int tmp;
    for (int i = 0, j = len - 1; i < len / 2; i++, j--)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    return s;
}
#endif

/**
 * 3-6 修改itoa函数，使得该函数可以接收三个参数，其中，第三个参数为最小字段宽度。
 * 为了保证转换后所得的结果至少具有第三个参数指定的最小宽度，在必要时应在所得结果的左边填充一定的空格
 */

#if 0
#define MAXLEN 100
void itoa(int n, char s[], int width);
char *reverse(char s[]);
int main()
{
    int num1 = -2147483648;
    char s[MAXLEN] = "";
    itoa(num1, s, 20);
    return 0;
}
void itoa(int n, char s[], int width)
{
    int i = 0;
    int sign = n;
    do
    {
        s[i++] = abs(n % 10) + '0';
        n /= 10;
    } while (n != 0);
    if (sign < 0)
        s[i++] = '-';
    while (i < width)
    {
        s[i] = ' ';
        i++;
    }
    s[i] = '\0';
    printf("num: %d -> string: %s\n", sign, reverse(s));
}
char *reverse(char s[])
{
    int len = strlen(s);
    int tmp;
    for (int i = 0, j = len - 1; i < len / 2; i++, j--)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    return s;
}

#endif