#include <iostream>
#include "include/chapter_6.h"
#include <string>
using namespace std;
/*
 * 函数
*/
int fact(int val)
{
    if (val < 0)
    {
        return -1;
    }
    int result = 1;
    while (val)
    {
        result *= val;
        --val;
    }
    return result;
}
// 递归写法
int fact_1(int val)
{
    int result = 1;
    if (val < 0)
    {
        return -1;
    }
    else if (val == 0 || val == 1)
    {
        result = 1;
    }
    else
    {
        result = val * fact_1(val - 1);
    }
    return result;
}
#include <cmath>
double uAbs(double num)
{
    return num >= 0 ? num : -num;
}

double uAdd(double v1, double v2)
{
    double result = v1 + v2;
    static unsigned iCnt = 0;
    ++iCnt;
    cout << "exec :" << iCnt << endl;
    return result;
}
void p_6()
{
    double num1, num2;
    while (cin >> num1 >> num2)
    {
        cout << uAdd(num1, num2) << endl;
    }
}
// 使用指针交换变量
void swap(int *p, int *q)
{
    int t = *p;
    *p = *q;
    *q = t;
}
/**
 * 使用引用交换变量
 * 与指针两笔，形式上更简单，无须额外声明指针变量，避免拷贝指针的值
 * */
void swap1(int &i, int &j)
{
    int tmp = i;
    i = j;
    j = tmp;
}
void p_10()
{
    int a = 5, b = 10;
    int *r = &a, *s = &b;
    cout << "before: " << a << " " << b << endl;
    swap(r, s);
    cout << "after: " << a << " " << b << endl;
}
void reset(int &i)
{
    i = 0;
}
void p_11()
{
    int num = 10;
    cout << num << endl; //10
    reset(num);
    cout << num << endl; //0
}
/**
 * 引用传递& 和值传递
 * 引用传递，形参对应是实参的别名，形参绑定到初始化它的对象
 * 值传递，形参获得是实参拷贝的值，它们是两个独立的变量
 * */
void byRef(int &i)
{
    ++i;
}
void byVal(int i)
{
    --i;
}
void p_13()
{
    int a = 1, b = 1;
    byRef(a);
    byVal(b);
    cout << a << " " << b; // 2 1
}

bool hasUpper(const string &str)
{
    for (auto &c : str)
    {
        if (isupper(c))
        {
            return true;
        }
    }
    return false;
}
void changeToLower(string &str)
{
    for (auto &c : str)
    {
        c = tolower(c);
    }
}
void p_17()
{
    string str;
    while (cin >> str)
    {
        if (hasUpper(str))
        {
            changeToLower(str);
            cout << "After the transformation: " << str << endl;
        }
        else
        {
            cout << "Does not contain uppercase, no conversion is required!\n";
        }
    }
}
/**
 * value 和指针所指的对象比较
 **/
int uCompare(const int val, const int *p)
{
    return (val > *p) ? val : *p;
}

//以值传递的方式使用指针，所有改变仅限于指针内部
void swapPoint1(int *p, int *q)
{
    // 临时指针变量
    int *t = p;
    p = q;
    q = t;
}
//该函数实现两个值的交换，交换指针所指的内容
void swapPoint2(int *p, int *q)
{
    // 临时变量拷贝指针
    int t = *p;
    *p = *q;
    *q = t;
}
//交换指针本身的值，即交换指针所指的内存地址
void swapPoint3(int *&p, int *&q)
{
    int *t = p;
    p = q;
    q = t;
}
void p_22()
{
    int a = 1, b = 2;
    int *pa = &a, *pb = &b;
    cout << a << " " << b << endl;
    cout << pa << " " << pb << endl;
    swapPoint1(pa, pb);
    cout << a << " " << b << endl;
    cout << pa << " " << pb << endl;
    swapPoint2(pa, pb);
    cout << a << " " << b << endl;
    cout << pa << " " << pb << endl;
    swapPoint3(pa, pb);
    cout << a << " " << b << endl;
    cout << pa << " " << pb << endl;
}
//打印整数常量指针
void print(const int *p)
{
    cout << *p << endl;
}
// 打印维度内的整数
void print(const int *p, const int size)
{
    int i = size;
    while (i)
    {
        cout << *p++ << " ";
        --i;
    }
    cout << endl;
}
// 通过首位边界打印
void print(const int *b, const int *e)
{
    for (auto q = b; q < e; ++q)
    {
        cout << *q << " ";
    }
    cout << endl;
}
void p_23()
{
    int i = 0, j[2] = {10, 11};
    print(&i);
    print(j);
    print(j, 1);
    print(j, sizeof(j) / sizeof(*j));
    print(begin(j), end(j));
}

int uSum(initializer_list<int> list)
{
    int sum = 0;
    // int value
    // 当对象的元素是类类型或容器类型，避免拷贝，需要使用引用7法国、j
    for (const auto v : list)
    {
        sum += v;
    }
    return sum;
}
void p_27()
{
    cout << uSum({1, 2, 3, 4}) << endl;
    cout << uSum({1, 2, 3, 4, 5, 6, 7}) << endl;
    cout << uSum({1, 2, 3, 4, 6, 7, 8, 9, 10}) << endl;
}

// 函数返回引用-- 如果函数所引的是函数开始之前就已经存在的对象，则返回该引用是有效的；对局部变量无效，随着函数的生命周期会消亡
// 当不希望返回的对象被修改时，返回对常量的引用
int &getArrayValue(int *array, int index)
{
    // if (index < 0 || index > sizeof(array) / sizeof(*array))
    // {
    //     throw runtime_error("index out of range!");
    // }
    return array[index];
}

void p_32()
{
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        getArrayValue(a, i) = i;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
}
#include <vector>
void print(vector<int> nums, unsigned index)
{
    unsigned size = nums.size();
    if (!nums.empty() && index < size)
    {
        cout << nums[index] << " ";
        print(nums, index + 1);
    }
}

double add(int a, int b)
{
    return a + b;
}
double subtract(int a, int b)
{
    return a - b;
}
double multiply(int a, int b)
{
    return a * b;
}
double divide(int a, int b)
{
    try
    {
        return static_cast<double>(a) / b;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void compute(int a, int b, double (*p)(int, int))
{
    cout << p(a, b) << endl;
}
void p_55()
{
    int i = 5, j = 10;
    decltype(add) *p1 = add, *p2 = subtract, *p3 = multiply, *p4 = divide;
    vector<decltype(add) *> vF = {p1, p2, p3, p4};
    for (auto p : vF)
    {
        compute(i, j, p);
    }
}
int main(int argc, char **argv)
{
    // cout << fact(0) << endl;
    // cout << fact_1(5) << endl;
    // cout << uAbs(0) << " " << abs(0) << endl;
    // cout << uAbs(1) << " " << abs(1) << endl;
    // cout << uAbs(-1) << " " << abs(-1) << endl;
    // p_6();
    // p_10();
    // p_13();
    // p_17();
    // int i = 1, a[10] = {3, 10};
    // cout << uCompare(2, a) << endl;
    // p_22();
    // p_23();
    string str;
    for (int i = 0; i < argc; ++i)
    {
        // cout << argv[i] << endl;
        str += argv[i];
    }
    cout << str << endl;
    // p_27();
    // p_32();
    // vector<int>v={1,2,3,5,6,3};
    // print(v,0);
    p_55();
    return 0;
}