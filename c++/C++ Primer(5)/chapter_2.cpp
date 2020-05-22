#include <iostream>
#include <math.h>
#include <typeinfo>
using namespace std;
/*
* 变量和基本类型
*/
void p_3()
{
    unsigned u = 10, u2 = 42;
    cout << u2 - u << endl;
    // 自动加模运算
    cout << u - u2 << endl;
    int i = 10, i2 = 42;
    cout << i2 - i << endl;
    cout << i - i2 << endl;
    cout << i - u << endl;
    cout << u - i << endl;
    // 4,294,967,296
    cout << pow(2, 32) << endl;
}
void p_8()
{
    cout << "2\x4d\012";
    cout << "2M\n";
    cout << "2\tM\n";
}
void p_10()
{
    // default value
    int a;
    string s;
    cout << a << endl; // 0
    cout << s << endl; // ""
}
void p_16()
{
    int i = 1, &r1 = i;
    int d = 10.1, &r2 = d;
    cout << "i= " << i << " &i= " << r1 << endl;
    cout << "d= " << d << " &d= " << r2 << endl;
    // 引用赋值实际上是把值赋给了引用绑定的对象
    r2 = 3.114159;
    cout << "i= " << i << " &i= " << r1 << endl;
    cout << "d= " << d << " &d= " << r2 << endl;
    r2 = r1;
    cout << "i= " << i << " &i= " << r1 << endl;
    cout << "d= " << d << " &d= " << r2 << endl;
    i = r2;
    cout << "i= " << i << " &i= " << r1 << endl;
    cout << "d= " << d << " &d= " << r2 << endl;
    r1 = d;
    cout << "i= " << i << " &i= " << r1 << endl;
    cout << "d= " << d << " &d= " << r2 << endl;
}
void p_18()
{
    int i = 5, j = 10;
    // 指针p指向i的地址
    int *p = &i;
    cout << "p: " << p << " "
         << "*p: " << *p << endl;
    // p 重新指向j的地址，改变之地址
    p = &j;
    cout << "p: " << p << " "
         << "*p: " << *p << endl;
    // 指向的地址值改变，地址未改变
    *p = 20;
    cout << "p: " << p << " "
         << "*p: " << *p << endl;
    // p的地址指向j，j改变，同时*p也会改变
    j = 30;
    cout << "p: " << p << " "
         << "*p: " << *p << endl;
}
void p_20()
{
    int i = 42;
    int *p = &i;
    cout << p << " " << *p << endl;
    *p = *p * *p;
    cout << p << " " << *p << endl;
}
void p_22()
{
    int i = 0;
    int *p = nullptr;
    int *p1 = &i;
    if (!p)
    {
        cout << "p 指向一个空地址\n";
    }
    if (!*p1)
    {
        cout << "p 指向的引用值为0\n";
    }
}
void p_34()
{
    int i = 0, &r = i;
    auto a = r;
    const int ci = i, &cr = ci;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci;
    auto &f = ci;
    cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;
    a = 42, b = 42, c = 42;
    // d e 是指针，f是常量引用
    //d = 42, e = 42, f = 42;
    cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;
}
void p_35()
{
    const int i = 42;
    auto j = i;
    const auto &k = i;
    auto *p = &i;
    const auto j2 = i, &k2 = i;
    cout << typeid(i).name() << endl;
    cout << typeid(j).name() << endl;
    cout << typeid(k).name() << endl;
    cout << typeid(p).name() << endl;
    cout << typeid(j2).name() << endl;
    cout << typeid(k2).name() << endl;
}
void test()
{
    short a = 1;
    int b = 1;
    long l = 1;
    long long ll = 1;
    float c = 1;
    double d = 1;
    char e = 'a';
    bool f = 1;

    //cout<<typedef(a)<<endl;
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(l) << endl;
    cout << sizeof(ll) << endl;
    cout << sizeof(c) << endl;
    cout << sizeof(d) << endl;
    cout << sizeof(e) << endl;
    cout << sizeof(f) << endl;
}
void p_36()
{
    int a = 3, b = 4;
    // 使用不加括号的的变量，c的类型就是a的类型，等同于int c=a
    decltype(a) c = a; 
    // 使用加括号的变量，d的类型为引用，等同于 int &d=a
    decltype((b)) d = a;
    ++c, ++d;
    cout << a << " " << b << " " << c << " " << d << endl;
}
int main()
{
    // p_16();
    // p_18();
    // p_20();
    // p_22();
    // p_34();
    // p_35();
    p_36();
    return 0;
}