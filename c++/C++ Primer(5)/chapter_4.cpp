#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
/*
* 表达式
*/
// get random numbers by n
vector<int> getNumbers(int n)
{

    vector<int> numbers;
    //get random seed
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        numbers.push_back(rand() % 1000);
    }

    return numbers;
}

void p_2()
{

    vector<int> nums = getNumbers(10);
    cout << "Vectos: \n";
    for (auto &v : nums)
    {
        cout << v << " ";
    }
    cout << endl;
    cout << "check: \n";
    cout << *nums.begin() << endl;
    cout << *nums.begin() + 1 << endl;
}
bool p_6(int i)
{
    return (i % 2 == 0) ? true : false;
}
void p_7()
{
    // warning: integer overflow in expression of type 'int' results in '-2147483648' [-Woverflow]
    // int a = 2147483647 + 1;
    // int b = -100000 * 300000;
    // int c = 2019 * 2019 * 2019;
    // cout << a << " " << b << " " << c << " ";
}
void p_9()
{

    int i;
    vector<int> nums;
    cout << "Input some numbers:\n";
    while (cin >> i && i != 42)
    {
        // if (i == 42)
        // {
        //     break;
        // }
        nums.push_back(i);
    }
    for (auto &v : nums)
    {
        cout << v << " ";
    }
    cout << endl;
}
void p_11()
{
    int a, b, c, d;
    cout << "Input four numbers:\n";
    cin >> a >> b >> c >> d;
    if (a > b && b > c && c > d)
    {
        cout << a << " " << b << " " << c << " " << d;
    }
}
void p_15()
{
    double d;
    int i;
    int *p;
    d = i = 0;
    p = 0;
    cout << d << " " << i << " " << p;
}
void p_21()
{
    vector<int> nums = getNumbers(10);
    for (auto &v : nums)
    {
        cout << v << " ";
    }
    cout << endl;
    // 查找奇数
    for (auto &v : nums)
    {
        v = (v % 2) ? v : v * 2;
        cout << v << " ";
    }
    cout << endl;
}
//sizeof
void p_28()
{

    cout << "bool:\t" << sizeof(bool) << endl;
    cout << "char:\t" << sizeof(char) << endl;
    cout << "wchar_t:\t" << sizeof(wchar_t) << endl;
    cout << "char16_t:\t" << sizeof(char16_t) << endl;
    cout << "char32_t:\t" << sizeof(char32_t) << endl;
    cout << "short:\t" << sizeof(short) << endl;
    cout << "int:\t" << sizeof(int) << endl;
    cout << "long:\t" << sizeof(long) << endl;
    cout << "long long:\t" << sizeof(long long) << endl;
    cout << "float:\t" << sizeof(float) << endl;
    cout << "double:\t" << sizeof(double) << endl;
    cout << "long double:\t" << sizeof(long double) << endl;
}

void p_29()
{

    int a[10];
    int *p = a;
    cout << sizeof(a) << " / " << sizeof(*a) << " = " << sizeof(a) / sizeof(*a) << endl; //40 / 4 = 10
    cout << sizeof(p) << " / " << sizeof(*p) << " = " << sizeof(p) / sizeof(*p) << endl; //8 / 4 = 2 pointer/int
}
void p_32()
{
    constexpr int size = 5;
    int ia[size] = {1, 2, 3, 4, 5};
    // as python enumerate
    for (int *ptr = ia, ix = 0; ix < size && ptr < ia + size; ++ix, ++ptr)
    {
        cout << ix << "\t" << *ptr << endl;
    }
}
void p_36()
{
    int i = 10;
    double d = 0.2;
    cout << i * d << endl;
    cout << i * static_cast<int>(d);
}
int main()
{
    // p_2();
    // cout << p_6(3) << endl;
    // p_7();
    // p_9();
    // p_11();
    // p_15();
    // p_21();
    // cout << (~'q' << 6);
    // p_28();
    // p_29();
    // p_32();
    // cout << ((2 % 2) ? 1 : 0);
    p_36();
    return 0;
}
