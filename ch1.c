#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * 1-3 修改温度转换程序，使之能在转换表的顶部打印一个标题
 */
#if 0
int main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    printf("华氏温度转换摄氏温度转换表\n");
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%5.0f %15.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
#endif

/**
 * 1-4 编写一个程序打印摄氏温度转换为相应华氏温度的转换表
 */
#if 0
// 华氏=摄氏度/(5.0/9.0)+32.0
int main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    celsius = lower;
    printf("摄氏温度转换为华氏温度转换表\n");
    while (celsius <= upper)
    {
        fahr = celsius / (5.0 / 9.0) + 32.0;
        printf("%5.0f %15.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}
#endif

/**
 * 1-5 修改温度转换程序，要求以逆序(即按照从300度到0度的顺序)打印温度转换表
 */
#if 0
int main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    printf("摄氏温度转换为华氏温度转换表(逆序)\n");
    for (celsius = upper; celsius >= lower; celsius -= step)
    {
        fahr = celsius / (5.0 / 9.0) + 32.0;
        printf("%5.0f %15.1f\n", celsius, fahr);
    }
    return 0;
}

#endif

/**
 * 1-6 验证表达式getchar()!=EOF的值是0还是1
 */
#if 0
int main()
{
    /**
     *这里记一个行缓冲模式,标准输入stdin(键盘)默认是行缓冲
     在命令行中输入字符时，不会立刻被getchar()读到
     只有按下回车，输入才会被提交给程序
     在用getcahr()输入时，其实是在从一个缓冲区里拿字符
     而EOF同样在做这个刷新缓冲区的动作，但它主要告诉系统:我的输入流结束了
     */
    int c;
    c = getchar() != EOF;
    printf("c value is %d\n", c);
}
#endif

/**
 * 1-7 编写一个打印EOF值的程序
 */
#if 0
int main()
{
    // 触发EOF  ctrl+d(linux) ctrl+z(windows)
    int c;
    while ((c = getchar()) != EOF)
        ;
    printf("EOF value is %d\n", c);
    return 0;
}
#endif

/**
 * 1-8 编写一个统计空格，制表符与换行符个数的程序
 */
#if 0
/**
 * if和else if的条件判断，
 * if会依次进入，即使有条件满足
 * else if只要有条件满足，就不再会对其他条件再去判断
 * 
*/
int main()
{
    int space_count = 0;
    int tab_count = 0;
    int enter_count = 0;

    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            space_count++;
        else if (c == '\t')
            tab_count++;
        else if (c == '\n')
            enter_count++;
    }
    printf("空格个数:%-d\n制表符个数:%-d\n换行符个数:%-d\n", space_count, tab_count, enter_count);
    return 0;
}
#endif

/**
 * 1-9 编写一个将输入复制到输出的程序，并将其中连续的多个空格用一个空格代替
 */
#if 0
int main()
{
    /**
     * 题目需要将连续多个空格用一个空格代替，getchar()每次从缓冲区读取一个字符
     * 所以不太好判断是否有连续的空格
     * 因此最好是一次读一行，然后再去判断是否有连续的空格，进行替换
     *
     * 再一个注意几个函数的点
     * fgets()读取缓冲区的一行，保留'\n',在字符串末尾自动加'\0'
     * scanf()读取缓冲区,不保留空格和换行
     * getchar()一个字符一个字符处理，自己处理结尾
     */
    char buff[256] = ""; // 注意初始化数组为0
    int index = 0;
    int space_count = 0;
    while (fgets(buff, sizeof(buff), stdin) != NULL)
    {
        index = 0;
        while (buff[index] != '\0')
        {
            if (buff[index] != ' ')
            {
                if (space_count > 0)
                {
                    putchar(' ');
                    space_count = 0;
                }
                putchar(buff[index]);
            }
            else
                space_count++;
            index++;
        }
    }

    return 0;
}
#endif

/**
 * 1-10 编写一个将输入复制到输出的程序，并将其中的制表符替换为\t,把回退符替换为\b,把反斜杠替换为\\
 *  这样可以将制表符和回退符以可见的方式显示出来
 */
#if 0
int main()
{
    // 这里如果不是读文件，\b回退符这个是没法显示的，缓冲区读不到这个字符主要是，以后文件中读取可以试试
    char ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\t')
        {
            putchar('\\');
            putchar('t');
        }
        else if (ch == '\\')
        {
            putchar('\\');
            putchar('\\');
        }
        else
            putchar(ch);
    }

    return 0;
}
#endif

/**
 * 1-12 编写一个程序，以每行一个单词的形式打印其输入
 */
#if 0
int main()
{
    char ch[255] = "";
    int i;
    int space_count = 0;
    while (fgets(ch, sizeof(ch), stdin) != NULL)
    {
        i = 0;
        while (ch[i] != '\0')
        {
            if (ch[i] == ' ' || ch[i] == '\t')
                space_count++;
            else
            {
                if (space_count > 0)
                {
                    putchar('\n');
                    space_count = 0;
                }
                putchar(ch[i]);
            }
            i++;
        }
    }
    return 0;
}

#endif

/**
 * 1-13 编写一个程序，打印输入中单词长度的直方图。水平方向的直方图比较容易绘制，垂直方向的直方图则要困难些
 */
#if 0
#define IN 1
#define OUT 0
#define MAXCOUNT 100 // 单词个数最大数量
#define MAXLEN 255   // buf长度最大值

// 打印垂直直方图
void print_verical_histogram(int i_len[], int word_count)
{
    int max_len = 0;
    // 找出最长单词的高度
    for (int i = 0; i < word_count; ++i)
    {
        if (i_len[i] > max_len)
            max_len = i_len[i];
    }

    // 画出*和空格，每个单词其实高度都是以长度最大的那个单词为基准
    for (int row = max_len; row > 0; --row)
    {
        for (int i = 0; i < word_count; ++i)
        {
            if (i_len[i] >= row)
                printf("  *  ");
            else
                printf("     ");
        }
        printf("\n");
    }

    // 分割线
    for (int i = 0; i < word_count; ++i)
        printf("-----");
    printf("\n");

    for (int i = 0; i < word_count; ++i)
        printf(" %2d  ", i);
    printf("\n");
}

int main()
{
    /**
     * 首先要确认输入是什么样子
     * 可能是“  good bad    sad  ”
     * "good\nbad\nsad\n"
     * 不管哪种形式，我们读入输入后，必须要对其格式进行处理
     * 题目要求打印输入中单词长度
     * 所以首先需要将输入的单词干净地剥离出来，你没办法保证输入者能以空格为间隔去输入单词
     * 所以存储单词需要一个数组,但注意这是一个二维数组
     * 因为要输出每个单词对应的长度，所以又需要一个数组
     * 然后用一个索引，去同时遍历两个数组，这两个数组元素长度是一样的，一个单词，对应一个长度
     */

    /**
     * 之前考虑处理多个空格，是用一个变量去记录空格个数
     * 这里可以借鉴书上的两个状态，IN 和 OUT
     * IN表示当前正在处理一个单词，比如good,当索引在good其中，状态就是IN
     * 一旦索引出了good的范围，遇到空格，制表符，状态都变为了OUT
     * 有这两个状态，就可以在IN的时候，往单词数组中写单词，OUT的状态时，就不去写,并且也不用再去判断当前空格是不是有多个，是不是空格，是不是制表符
     */
    char ch_word[MAXCOUNT][MAXLEN] = {""}; // 单词数组
    int i_len[MAXLEN] = {0};               // 长度数组
    char buf[MAXLEN] = "";                 // 读取输入的buf,用来处理输入
    int i;
    int state = OUT;
    int word_index = 0;       // 记录当前是第几个单词
    int word_write_index = 0; // 单词写入指针
    int word_len_count = 0;   // 单词长度记录
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        i = 0;
        word_write_index = 0;
        word_len_count = 0;
        while (buf[i] != '\0')
        {
            // 状态机的精髓所在,在马上要变为OUT状态时，IN状态结束后需要办的事，保存长度。
            if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
            {
                if (state == IN && word_len_count > 0)
                {
                    i_len[word_index++] = word_len_count;
                    word_write_index = 0; // 写指针清空
                    word_len_count = 0;   // 单词长度清空，均为下一个单词的读取准备
                }
                state = OUT;
            }
            else
            {
                if (state == OUT)
                    state = IN;
                ch_word[word_index][word_write_index++] = buf[i];
                word_len_count++; // 每写入一个字符，单词长度就++
            }
            i++;
        }
    }
    if (state == IN && word_len_count > 0)
    {
        i_len[word_index] = word_len_count;
        word_index++;
    }
    // 打印直方图，水平的
    for (int j = 0; j < word_index; j++)
    {

        printf("%-10s", ch_word[j]);
        for (int k = 0; k < i_len[j]; k++)
            printf("* ");
        // printf("%s->%d\n", ch_word[j], i_len[j]);
        printf("\n");
    }

    // 垂直的
    print_verical_histogram(i_len, word_index);

    return 0;
}
#endif

/**
 *1-14 编写一个程序，打印输入中各个字符出现的频度的直方图
 */
#if 0
// 打印直方图
void print_star(int num)
{
    for (int i = 0; i < num; i++)
        printf(" * ");
    printf("\n");
}
void print_freq(int count[])
{
    const int width = 5;
    for (int i = 0; i < 256; ++i)
    {
        if (count[i] > 0)
        {
            if (i == '\n')
            {
                printf("%*s ", width, "\\n");
                print_star(count[i]);
            }
            else if (i == '\t')
            {
                printf("%*s ", width, "\\t");
                print_star(count[i]);
            }
            else if (i == ' ')
            {
                printf("%*s", width, "space ");
                print_star(count[i]);
            }
            else if (isprint(i))
            {

                printf("%*c ", width, i);
                print_star(count[i]);
            }
            else
            {
                printf("\\x%*x ", width, i);
                print_star(count[i]);
            }
        }
    }
}
int main()
{
    int count[256] = {0};
    int c;
    while ((c = getchar()) != EOF)
        ++count[c];
    for (int i = 0; i < 256; ++i)
    {
        if (count[i] > 0)
        {
            if (i == '\n')
                printf("'\\n': %d\n", count[i]);
            else if (i == '\t')
                printf("'\\t': %d\n", count[i]);
            else if (i == ' ')
                printf("'space': %d\n", count[i]);
            else if (isprint(i))
                printf("'%c': %d\n", i, count[i]);
            else
                printf("'\\x%02x': %d\n", i, count[i]);
        }
    }
    print_freq(count);

    return 0;
}
#endif

/**
 * 1-15 重新编写1.2节中的温度转换程序，使用函数实现温度转换计算
 */
#if 0

#define LOWER 0
#define UPPER 300
#define STEP 20
void print_c2f_table()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = LOWER;
    upper = UPPER;
    step = STEP;
    celsius = lower;
    printf("摄氏温度转换为华氏温度转换表\n");
    while (celsius <= upper)
    {
        fahr = celsius / (5.0 / 9.0) + 32.0;
        printf("%5.0f %15.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

int main()
{
    print_c2f_table();
    return 0;
}
#endif

/**
 * 1-16 修改打印最长文本行的程序的主程序main,使之可以打印任意长度的输入行的长度，并尽可能多地打印文本
 */
#if 0
#define MAXLINE 1000
int pgetline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    char ch;
    int i = 0;
    while ((ch = getchar()) != EOF)
    {
        putchar(ch);
        ++i;
    }
    printf("输入行长度为:%d\n", i);
    return 0;
}

int pgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

#endif

/**
 * 1-17 编写一个程序，打印长度大于80个字符的所有输入行
 */
#if 0
#define MAXLINE 1000
int main()
{
    char buf[MAXLINE] = "";
    int i = 0;
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        i = 0;
        while (buf[i] != '\0')
        {
            ++i;
            if (i > 80)
            {
                fputs(buf, stdout);
                break;
            }
        }
    }
    return 0;
}
#endif

/**
 * 1-18 编写一个程序，删除每个输入行末尾的空格及制表符，并删除完全是空格的行
 */
#if 0
#define MAXLEN 1000

// 删除末尾的空格，或者删除完全是空格的行
void del_space(char buf[])
{
    int len = strlen(buf); // 不包含结尾'\0'
    int index = len - 1;   // 索引，为长度-1
    int n_flag = 0;        // 标记是否有换行符
    if (len > 0 && buf[index] == '\n')
    {
        n_flag = 1;
        buf[index--] = '\0';
    }
    while (len > 0 && (buf[index] == ' ' || buf[index] == '\t'))
        buf[index--] = '\0';
    if (n_flag)
        buf[index + 1] = '\n';
}
// 打印目前字符串
void print_now(char buf[])
{
    int m = 0;
    while (buf[m] != '\0')
    {
        if (buf[m] == ' ')
            putchar(' ');
        else if (buf[m] == '\n')
        {
            printf("\\n");
            putchar(buf[m]);
        }
        else if (buf[m] == '\t')
            printf("\\t");
        else
            putchar(buf[m]);
        m++;
    }
}

int main()
{
    char buf[MAXLEN] = "";
    while ((fgets(buf, sizeof(buf), stdin)) != NULL)
    {
        printf("\n----before-------\n");
        print_now(buf);
        printf("\n----beforeend----\n");
        del_space(buf);
        printf("\n----after-------\n");
        print_now(buf);
        printf("\n----afterend----\n");
    }
    return 0;
}
#endif

/**
 * 1-19 编写函数reverse(s),将字符串s中的字符顺序颠倒过来，使用该函数编写一个程序，每次颠倒一个输入行中的字符顺序
 */
#if 0
#define MAXLEN 100

char *reverse(char s[]);
void printf_str(char s[]);

int main()
{
    char buf[MAXLEN] = "";
    while ((fgets(buf, sizeof(buf), stdin)) != NULL)
    {
        printf_str(buf);
        printf(" reverse is ");
        printf_str(reverse(buf));
        printf("\n");
    }
    return 0;
}

char *reverse(char s[])
{
    int len = strlen(s);
    char tmp;
    int i, j;
    for (i = 0, j = len - 1; i < len / 2; i++, j--)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    return s;
}

void printf_str(char buf[])
{
    int i = 0;
    while (buf[i] != '\0')
    {
        if (buf[i] == '\n')
            printf("\\n");
        else
            putchar(buf[i]);
        i++;
    }
}
#endif

/**
 * 1-20 编写程序detab,将输入中的制表符替换成适当数目的空格，使空格充满到下一个制表符终止位的地方。假设制表符终止位的位置是固定的
 * 比如每隔n列就会出现一个制表符终止位。n应该作为变量还是符号常量呢
 */
#if 0
// 该用常量
#define ENDPOINT 8
#define MAXLEN 100
void show_space_other(char buf[]);
void detab();
void detab()
{
    char buf[MAXLEN] = "";
    int i, current, space_count;
    while ((fgets(buf, sizeof(buf), stdin)) != NULL)
    {
        i = 0;
        current = 0; // 这个变量是记录下一个终止位置的index
        show_space_other(buf);
        while (buf[i] != '\0')
        {
            if (buf[i] == '\t')
            {
                space_count = ENDPOINT - (current % ENDPOINT);
                current += space_count;
                for (int k = 0; k < space_count; k++)
                    printf("*");
            }
            else
            {
                putchar(buf[i]);
                current++;
            }
            i++;
        }
    }
}

// 显式打印空格或制表符
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

int main()
{
    detab();
    return 0;
}
#endif

/**
 * 1-21 编写程序entab,将空格串替换为最少数量的制表符和空格，但要保持单词之间的间隔不变。
 * 假设制表符终止位的位置与练习1-20的detab程序的情况相同。当使用一个制表符或者一个空格都
 * 可以到达下一个制表符终止位时，选用那一种替换字符比较好
 */

#if 0
#define MAXLEN 100
#define ENDOFPOS 8

// 替换为最少数量的制表符和空格，一个制表符或一个空格都可以到达下一个制表符终止位置，用制表符
// 比如 这是七个空格*******，我再来一个tab和一个空格都可以达到制表符终止位
// 但是我用一个tab,整个我就用了一个制表符，如果我用空格，整个可能用8个空格

void entab();
void show_space_other(char buf[]);

int main()
{
    entab();
    return 0;
}
void entab()
{
    char buf[MAXLEN] = "";
    int to_tabstop;  // 到下一个终止位置还需要多大距离
    int spacecount;  // 连续空格数量
    int current_row; // 当前列
    int read;        // 读指针
    int write;       // 写指针

    // 这个题有个隐含的东西
    // 它说是让把空格替换\t,没错，但是要考虑，你写了\t以后，本质是消化了n个空格，这n个空格你需要清除掉的
    // 所以这里就有一种潜在的操作,在处理字符串的时候，一边在写入，一边还在删除
    // 读写指针这里就是清晰思路的重要思想
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
                    to_tabstop = ENDOFPOS - (current_row % ENDOFPOS); // 到下一个end距离
                    if (spacecount >= to_tabstop)                     // 空格长度够到下一个end,换\t
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
 * 1-22 编写一个程序，把较长的输入行"折"成短一些的两行或多行，折行的位置在输入行的第n列之前的最后一个非空格之后。
 * 要保证程序能够智能地处理输入行很长以及在指定的列前没有空格或制表符时的情况
 */

#if 0
#define MAXLINE 1000 // 每行最大输入长度
#define MAX_WIDTH 20 // 最大列宽
#define TAB_WIDTH 8  // 制表符宽度

int main()
{
    // 这个题核心是current这个处理当前列的位置判断
    // 它不同于i下标指的位置
    // 因为i下标指向的可能是普通字符，空格，或制表符
    // 普通字符和空格，i和current都会自增1,但是如果是制表符，i会自增1,但是current会自增到补全到下一个结束符的位置，这就不一定是+1了，所以这个就是关键
    char line[MAXLINE] = "";
    while (fgets(line, sizeof(line), stdin))
    {
        int i = 0;
        int start = 0;   // 处理字符串的起始位置
        int current = 0; // 单独标记当前处理到哪一列了
        int last_blank = -1;
        while (line[i] != '\0')
        {
            char c = line[i];
            // 处理空格
            if (c == ' ' || c == '\t')
                last_blank = i;
            // 处理制表符
            if (c == '\t')
                current += TAB_WIDTH - (current % TAB_WIDTH);
            else
                current++;
            if (current > MAX_WIDTH)
            {
                if (last_blank >= start)
                {
                    for (int j = start; j < last_blank; j++)
                        putchar(line[j]);
                    putchar('\n');
                    i = last_blank + 1;
                    start = i;
                }
                else
                {
                    for (int j = start; j < i; j++)
                        putchar(line[j]);
                    putchar('\n');
                    start = i;
                }
                current = 0;
                last_blank = -1;
                continue;
                // 这里这个continue,i有两种情况，
                // 一种是空格或制表符，会走上面的情况，i会自增到空格指向下一个位置
                // 一种是这里这种情况，i全是普通字符，也就是没有任何空格，直到超过最大宽度
                // 此时i已经指向最大宽度的下一个字符，所以不用再++,清空current和last_blank,进行下一次判断就行
            }
            i++;
        }
        // 最后收尾,因为不确定最后的长度能不能够MAX_WIDTH,所以补一下最后的
        for (int j = start; j < i; j++)
            putchar(line[j]);
        if (i > start)
            putchar('\n');
    }
    return 0;
}

#endif

/**
 * 1-23 编写一个删除C语言程序中所有的注释语句。要正确处理带引号的字符串与字符常量。在c语言中，注释不允许嵌套
 */

#if 0
int main()
{
    // 这两个题涉及到读文件，并且对于注释细节需要了解，后面回头来做
    return 0;
}
#endif

/**
 * 1-24 编写一个程序，查找C语言程序中的基本语法错误，如圆括号，方括号，花括号不配对等。
 * 要正确处理引号(包括单引号和双引号),转义字符序列与注释
 */
#if 0
int main()
{
    return 0;
}
#endif