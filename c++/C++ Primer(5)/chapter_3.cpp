#include <iostream>
#include <string>
#include <math.h>
#include <cctype>
#include <ctime>
#include <cstdlib>
using namespace std;
/*
* 字符串、向量、数组
*/
class Salse_data
{
    friend istream &operator>>(istream &, Salse_data &);
    friend ostream &operator<<(ostream &, const Salse_data &);
    friend bool operator<(const Salse_data &, const Salse_data &);
    friend bool operator==(const Salse_data &, const Salse_data &);

public:
    //三种 默认构造函数
    Salse_data() = default;
    Salse_data(const string &book) : bookNo(book) {}
    Salse_data(istream &is) { is >> *this; }

public:
    Salse_data &operator+=(const Salse_data &);
    string isbn() const { return bookNo; }

private:
    string bookNo;              // 书籍编号,隐式初始为空串
    unsigned units_sold = 0;    //销售量
    double selling_price = 0.0; //原价
    double sale_price = 0.0;    //售价
    double discount = 0.0;      //折扣
};
// 比较isbn
inline bool compareIsbn(const Salse_data &lhs, const Salse_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

// +
Salse_data operator+(const Salse_data &, const Salse_data &);

// ==
inline bool operator==(const Salse_data &lhs, const Salse_data &rhs)
{
    return lhs.units_sold == rhs.units_sold && lhs.selling_price == rhs.selling_price && lhs.sale_price == rhs.sale_price && lhs.isbn() == rhs.isbn();
}

inline bool operator!=(const Salse_data &lhs, const Salse_data &rhs)
{
    return !(lhs == rhs);
}

//+=
Salse_data &Salse_data::operator+=(const Salse_data &rhs)
{
    units_sold += rhs.units_sold;
    sale_price = (rhs.sale_price * rhs.units_sold + sale_price * units_sold) / (rhs.units_sold + units_sold);
    if (selling_price != 0)
    {
        discount = sale_price / selling_price;
    }
    return *this;
}

//+
Salse_data operator+(const Salse_data &lhs, const Salse_data &rhs)
{
    Salse_data ret(lhs); // 拷贝lhs到临时变量 ret
    ret += rhs;
    return ret;
}

// cin
istream &operator>>(istream &in, Salse_data &s)
{
    in >> s.bookNo >> s.units_sold >> s.selling_price >> s.sale_price;
    //cout << s.selling_price;
    if (in && s.selling_price != 0)
    {
        /* code */
        s.discount = s.sale_price / s.selling_price;
    }
    else
    {
        s = Salse_data();
    }
    return in;
}
//cout
ostream &operator<<(ostream &out, const Salse_data &s)
{
    out << "isbn\tunits_sold\tselling_price\tsale_price\tdiscount\n";
    out << s.isbn() << "\t" << s.units_sold << "\t" << s.selling_price << "\t" << s.sale_price << "\t" << s.discount;
    return out;
}

int p_1()
{
    Salse_data book;
    cout << "Input records:[bookNo,tunits_sold,tselling_price,tsale_price] \n";
    while (cin >> book)
    {
        cout << book << endl;
    }
    Salse_data r1, r2;
    cout << "Input two same records \n";
    cin >> r1 >> r2;
    if (compareIsbn(r1, r2))
    {
        cout << r1 + r2 << endl;
    }

    Salse_data total, r;
    cout << "Input some the same records: \n";
    if (cin >> total)
    {
        while (cin >> r)
        {
            if (compareIsbn(total, r))
            {
                total += r;
            }
            else
            {
                cout << "The record is different!\n";
                break;
            }
            cout << total << endl;
        }
    }
    else
    {
        cout << "not result!\n";
        return -1;
    }
    return 0;
}

// 从标准输入中读取一行 getline/cin
void p_2()
{

    string line;
    cout << "Input a string: \n";
    // get line 可以读取空格
    while (getline(cin, line))
    {
        cout << line << endl;
        // 读取\n，但不存储
        cout << line.length() << endl;
    }
    // cin 以空格分割
}
// 字符串长度比较
void p_4()
{
    string s1, s2;
    cout << "Input two strings: \n";
    while (cin >> s1 >> s2)
    {
        if (s1 == s2)
        {
            cout << "equals\n";
            cout << "size: " << s1.size() << " length:" << s1.length() << endl;
        }
        else
        {
            // s1.length() return unsigned int
            // 三目运算符不能用？
            cout << "string: " << ((s1 > s2) ? s1 : s2) << endl;
            cout << "size: " << ((s1 > s2) ? s1.length() - s2.length() : s2.length() - s1.length()) << endl;
        }
    }
}

void p_5()
{

    char flag = 'y';
    string str, result;
    cout << "Input the string: \n";
    while (cin >> str)
    {
        if (!result.size())
        {
            result += str;
        }
        else
        {
            result += "->" + str;
        }

        // result += str;
        cout << "continue(Y/N)? \n";
        cin >> flag;
        if (flag == 'N' || flag == 'n')
        {
            break;
        }
    }
    cout << "The result are :" << result << endl;
}
void p_6()
{
    string s;
    cout << "Input the string: \n";
    while (getline(cin, s))
    {
        for (auto &c : s)
        {
            if (c == 'm')
            {
                c = '*';
            }
        }
        cout << s << endl;
    }
}

// 读取空串的首位，我的编译器也没有报错
void p_9()
{
    string s;
    cout << s[0] << endl;
}

//读取字符串，去除标点符号
// cctype ispunct
void p_10()
{
    string s, re;
    cout << "Input the string: \n";
    while (getline(cin, s))
    {
        for (auto &c : s)
        {
            if (!ispunct(c))
            {
                re += c;
            }
        }
        cout << re << endl;
    }
}
void p_11()
{
#include <typeinfo>
    const string s = "get out!";
    for (auto &c : s)
    {
        cout << typeid(c).name() << " " << c << endl;
    }
}

#include <vector>
// vector
void p_14()
{
    vector<int> vInt;
    int i;
    char flag = 'y';
    while (cin >> i)
    {
        vInt.push_back(i);
        // cout << "continue(Y/N)? \n";
        // cin >> flag;
        // if (flag == 'N' || flag == 'n')
        // {
        //     break;
        // }
    }
    for (auto &mem : vInt)
    {
        cout << mem << " ";
    }
    cout << endl;
    // use iterotior
    if (vInt.cbegin() != vInt.cend())
    {
        for (auto it = vInt.cbegin(); it != vInt.cend(); it++)
        {
            /* code */
            cout << *it << "->";
        }
        cout << endl;
    }

    int size = vInt.size();
    for (decltype(vInt.size()) i = 0; i < size / 2; i++)
    {
        cout << vInt[i] + vInt[size - 1 - i] << " ";
    }
    if (size % 2 != 0)
    {
        cout << vInt[size / 2];
    }
    cout << endl;
}

// 迭代器修改
void p_22()
{
    vector<string> text;
    string s;
    while (getline(cin, s))
    {
        text.push_back(s);
    }
    for (auto it = text.begin(); it != text.end() && !it->empty(); it++)
    {
        for (auto i = it->begin(); i != it->end(); i++)
        {
            *i = toupper(*i);
        }
        cout << *it << endl;
    }
}

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
void p_23()
{
    vector<int> numbers;
    int v;
    while (cin >> v)
    {
        numbers.push_back(v);
    }
    for (auto it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it * 2 << " ";
    }
    cout << endl;
}

// array
void p_31()
{

    const int size = 10;
    int a[size];
    for (int i = 0; i < size; i++)
    {
        a[i] = i;
    }
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    for (auto val : a)
    {
        cout << val << " ";
    }
    cout << endl;
}

void p_37()
{
    // const char ca[] = {'h', 'e', 'l', 'l', 'o','\0'};
    // const char ca[] = {'h', 'e', 'l', 'l', 'o'}; 因为没有找到\0没发生异常
    const char ca[] = "hello";
    const char *cp = ca;
    while (*cp)
    {
        cout << *cp << " ";
        ++cp;
    }
    cout << endl;
}
void p_41()
{
    const int size = 10;
    //获得随机vector
    vector<int> nums = getNumbers(size);
    int a[size];
    // vector to array
    auto it = nums.cbegin();
    for (int i = 0; i < nums.size(); i++)
    {
        a[i] = nums[i];
    }
    cout << "Array: " << typeid(a).name() << endl;
    for (auto val : a)
    {
        cout << val << " ";
    }
    cout << endl;
    // array to vector
    vector<int> newNums(begin(a), end(a));
    cout << "Vector: " << typeid(newNums).name() << endl;
    for (auto &v : newNums)
    {
        cout << v << " ";
    }
    cout << endl;
}
void p_43()
{
    int ia[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    cout << "way1: \n";
    for (int(&row)[4] : ia)
    {
        for (int &col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    cout << "way2: \n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << ia[i][j] << " ";
        }
        cout << endl;
    }
    cout << "way3: \n";
    for (int (*p)[4] = ia; p < ia + 3; p++)
    {
        for (int *q = *p; q < *p + 4; q++)
        {
            cout << *q << " ";
        }
        cout << endl;
    }
}
int main()
{
    // p_1();
    // p_2();
    // p_4();
    // p_5();
    // p_6();
    // p_11();
    // p_14();
    // p_22();
    // p_23();
    // p_31();
    // p_37();
    // p_41();
    p_43();
    return 0;
}
