#include "stdio.h"

//? 定义一个结构体
// foo 被称为结构标识 后续我们可以通过 struct foo 来访问这个结构
struct foo
{
    //任何结构体或者共用体至少要拥有一个成员
    int a;
};

//我们在实际使用的时候也会这样定义
typedef struct
{
    int a;
} foo1;
//? 将一个未命名的结构体定义为foo1
//能省去struct 直接将foo1当作类型名使用
// or
typedef struct s_foo
{
    int a;
} foo11;

// 有时候我们会在声明一个结构体时组合或者聚合其他结构体
//? 这个时候就可能会需要前置声明(Forward Declaring)
//! 但是前置声明只能解决间接引用(即聚合)的问题
struct foo3;

struct foo2
{
    //? 不允许使用不完整的类型
    //? 这是因为此时编译器只知道存在foo3 但是不知道它的大小
    //? 因为组合类型会被直接初始化
    //? 但由于不知道大小便不知道该分配多少内存给他
    // struct foo3 b;

    //? 而聚合类型可以在运行时确定大小，所以类型的大小就不重要了
    struct foo3 *a;
};

struct foo3
{
    struct foo2 a;
};

//--------------------------一些有趣的现象-----------------------------------//

// What is the size of foo4 ?
// what will happen if you access b[3] ?
// what will get when access the struct directly ?s
//? Memory Alignment & C Memory Model
struct foo4
{
    int a;     // size 4
    char b[2]; // size 2
    char c[0]; // size ?
};

struct foo5
{
    int a : 1;
};

int main(int argc, char const *argv[])
{
    //? 使用一个结构体
    struct foo f1;
    //! 此时f1虽然已经被分配到了栈上但其内部成员被没有被正确初始化
    // printf("%d\n", f1.a);
    //? 使用.运算符来访问结构体内的成员
    f1.a = 10;
    // printf("%d\n", f1.a);
    // TODO 一般对于比较复杂的结构，我们会写一些函数来帮助我们初始化一个结构

    struct foo4 lululu = {666, {1, 2}};

    // lululu.c = {32};

    printf("size of foo4: %d\n f4.b[2] = %d\n f4.b[3] = %d\n", sizeof(struct foo4), lululu.b[2], lululu.b[3]);
    printf("f4.b[4] = %d\n", lululu.b[4]);
    printf("%d\n", *(int *)(&lululu));

    // actually you can get c but you can not change it(size of c = 0)

    printf("%p,\n%p,\n%p,\n%p\n", &lululu, &lululu.a, &lululu.b, &lululu.c);

    return 0;
}
