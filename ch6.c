#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * 6-1 编写一个更完善的getword函数，正确处理下划线，字符串常量，注释以及预处理器控制指令
 */
#if 0
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key
{
    char *word;
    int count;
} keytab[] = {{"auto", 0},
              {"break", 0},
              {"case", 0},
              {"char", 0},
              {"const", 0},
              {"continue", 0},
              {"default", 0},
              {"unsigner", 0},
              {"void", 0},
              {"volatile", 0},
              {"while", 0}};
int getword(char *, int);
int binsearch(char *, struct key *, int);

int getch(void);
void ungetch(int c);
int main()
{
    // int n;
    char word[MAXWORD] = "";
    getword(word, MAXWORD);
    printf("%s\n", word);

    // while (getword(word, MAXWORD) != EOF)
    // {
    //     if (isalpha(word[0]))
    //     {
    //         if ((n = binsearch(word, keytab, NKEYS)) >= 0)
    //             keytab[n].count++;
    //     }
    // }
    // for (n = 0; n < NKEYS; n++)
    // {
    //     if (keytab[n].count > 0)
    //         printf("%4d %s\n", keytab[n].count, keytab[n].word);
    // }
    return 0;
}

int binsearch(char *word, struct key *tab, int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
// int getword(char *word, int lim)
// {
//     int c;
//     char *w = word;
//     while (isspace(c = getch()))
//         ;
//     if (c != EOF)
//         *w++ = c;
//     // 不是字母，直接返回
//     if (!isalpha(c) && c != '_')
//     {
//         *w = '\0';
//         return c;
//     }
//     // 不是数字或字母，直接返回
//     for (; --lim > 0; w++)
//     {
//         if (!isalnum(*w = getch()) && *w != '_')
//         {
//             ungetch(*w);
//             break;
//         }
//     }
//     *w = '\0';
//     return word[0];
// }
int getword(char *word, int lim)
{
    int c;
    char *w = word;
    // 跳过开头空格
    while (isspace(c = getch()) || c == '\t')
        ;
    // 结束符
    if (c == EOF)
        return EOF;
    *w++ = c;
    // 变量名首位只能是字母下划线
    if (isalpha(c) || c == '_')
    {
        // 数字字母下划线
        while ((--lim > 0) && (isalnum(c = getch()) || c == '_'))
            *w++ = c;
        // 多读了一个不符合当前情况的字符，还回去
        ungetch(c);
    }
    else if (c == '"') // 常量字符串
    {
        // 这里面换行，会接着让输入下一行字，直到遇到"或者EOF
        while (--lim > 0)
        {
            c = getch();
            *w++ = c;
            if (c == '\\')
            {
                c = getch();
                *w++ = c;
            }
            else if (c == '"')
                break;
            else if (c == EOF)
            {
                ungetch(c);
                w--;
                break;
            }
        }
    }
    else if (c == '/') // 注释处理
    {
        int d = getch();
        if (d == '/')
        {
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        }
        else if (d == '*')
        {
            while (1)
            {
                c = getch();
                if (c == EOF)
                    break;
                if (c == '*')
                {
                    if ((c = getch()) == '/')
                        break;
                    else
                        ungetch(c);
                }
            }
            return getword(word, lim);
        }
        else
            ungetch(d);
    }
    else if (c == '#')
    {
        while ((c = getch()) == ' ' || c == '\t')
            ;
        if (isalpha(c))
        {
            *w++ = c;
            while (isalnum(c = getch()))
                *w++ = c;
            if (c != EOF)
                ungetch(c);
        }
    }

    // 结束处理
    *w = '\0';
    return word[0];
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

/**
 * 6-2 编写一个程序，用以读入一个C语言程序，并按字母表顺序分组打印变量名，要求每一组内各变量名的前
 * 6个字符相同，其余字符不同。字符串和注释中的单词不予考虑。请将6作为一个可在命令行中设定的参数
 */
#if 1
int main()
{
    return 0;
}
#endif

/**
 * 6-3 编写一个交叉引用程序，打印文档中所有单词的列表，并且每个单词还有一个列表，记录出现过该单词的行号
 * 对the,and等非实义单词不予考虑
 */
#if 1
int main()
{
    return 0;
}
#endif

/**
 * 6-4 编写一个程序，根据单词的出现频率按降序打印输入的各个不同单词，并在每个单词的前面标上它的出现次数
 */
#if 1
int main()
{
    return 0;
}
#endif