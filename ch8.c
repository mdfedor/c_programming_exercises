#include <stdio.h>
#include <stdlib.h>

/**
 * 8-1 用read,write,open和close系统调用代替标准库中功能等价的函数，重写第7章的cat
 * 程序，并通过实验比较两个版本的相对执行速度
 */
#if 0
int main()
{
    exit(0);
}
#endif

/**
 * 8-2 用字段代替显式的按位操作，重写fopen和_fillbuf函数，比较相应代码的长度和执行速度
*/


/**
 * 8-3 设计并编写函数_flushbuf,fflush和fclose
*/

/**
 * 8-4 标准库函数
 * int fseek(FILE *fp,long offset,int origin)
 * 类似于函数lseek,所不同的是，该函数的fp是一个文件指针而不是文件描述符，且返回值是一个int类型
 * 的状态而非位置值。编写函数fseek,并确保该函数与库中其它函数使用的缓冲能够协同工作
*/


/**
 * 8-6 标准库函数calloc(n,size)返回一个指针，它指向n个长度为size的对象，且所有分配的存储空间都被初始化为0.
 * 通过调用或修改malloc函数来实现calloc函数
*/

/**
 * 8-7 malloc接收对存储空间的请求时，并不检查请求长度的合理性。而free则被认为被释放的块包含一个有效的长度字段。
 * 改进这些函数，使他们具有错误检查功能
*/

/**
 * 8-8 编写函数bfree(p,n),释放一个包含n个字符的任意块p,并将它放入由malloc和free维护的空闲块链表中。通过使用bfree,
 * 用户可以在任意时刻向空闲块链表中添加一个静态或外部数组
*/