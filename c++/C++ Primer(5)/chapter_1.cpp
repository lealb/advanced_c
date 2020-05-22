#include <iostream>
#include "include/Sales_item.h"
using namespace std;
/*
* 开始
*/
void p_3()
{
    cout << "Input two numbers: \n";
    int v1, v2;
    cin >> v1 >> v2;
    cout << v1 << "*" << v2 << "=" << v1 * v2 << endl;
}
void p_9()
{
    int sum = 0;
    int n = 50;
    while (n <= 100)
    {
        sum += n;
        n++;
    }
    cout << "Result: " << sum << endl;
}
void p_10()
{
    int i = 10;
    while (i)
    {
        cout << i << "->";
        i--;
    }
}
void p_11()
{
    int a, b;
    cout << "Input two numbers: \n";
    cin >> a >> b;
    if (a < b)
    {
        for (int i = a; i <= b; i++)
        {
            cout << i << "->";
        }
    }
    else
    {
        for (int i = a; i >= b; i--)
        {
            cout << i << "->";
        }
    }
}
void p_12()
{
    int sum = 0;
    for (int i = -100; i <= 100; i++)
        sum += i;
    cout << sum << endl;
}
void p_13()
{
    int sum = 0;
    int value;
    cout << "Input some numbers(End as Ctrl+Z): \n";
    while (cin >> value)
    {
        sum += value;
    }
    cout << sum << endl;
}
void p_20()
{
    Sales_item book;
    cout << "Input: \n";
    while (cin >> book)
    {
        cout << "Output: " << book << endl;
        //cout << "ISBN: " << book.isbn << "Avg price: " << book.avg_price << endl;
    }
}
void p_21()
{
    Sales_item item1, item2;
    cout << "Input ISBN, nums, price\n";
    cin >> item1;
    cin >> item2;
    if (compareIsbn(item1, item2))
    {
        cout << "sum result is :\n";
        cout << item1 + item2 << endl;
    }
    else
    {
        cout << "the sales record is different!\n";
    }
}
int p_22()
{
    Sales_item item, total;
    cout << "Input ISBN, nums, price\n";
    if (cin >> total)
    {
        while (cin >> item)
        {
            if (compareIsbn(total, item))
            {
                total += item;
            }
            else
            {
                cout << "the sales record is different!\n";
                return -1;
            }
            cout << "sum result is :\n"
                 << total << endl;
        }
    }
    else
    {
        cout << "no result!";
    }
    return 0;
}
int p_23()
{
    Sales_item item1, item2;
    cout << "Input ISBN, nums, price\n";
    int num = 1;
    if (cin >> item1)
    {
        while (cin >> item2)
        {
            // same isbn
            if (compareIsbn(item1, item2))
            {
                num++;
            }
            else
            {
                cout << item1.isbn() << " Has " << num << " records\n";
                item1 = item2;
                //num = 1;
            }
            cout << item1.isbn() << " Has " << num << " records\n";
        }
    }
    else
    {
        cout << "not result\n";
        return -1;
    }
    return 0;
}
int main()
{
    cout << "Hello, World" << endl;
    //p_3();
    // p_9();
    // p_10();
    // p_11();
    // p_12();
    // p_13();
    // p_14();
    p_23();
    return 0;
}