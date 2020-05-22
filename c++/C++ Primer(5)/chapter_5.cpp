#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
* 语句
*/

//统计字符个数
void p_11()
{
    unsigned aCut = 0, oCut = 0, eCut = 0, iCut = 0, uCut = 0;
    unsigned spaceCut = 0, tabCut = 0, newlineCut = 0;
    char ch;
    cout << "Input: \n";
    while (cin.get(ch))
    {
        switch (ch)
        {
        case 'A':
        case 'a':
            aCut++;
            break;
        case 'O':
        case 'o':
            oCut++;
            break;
        case 'I':
        case 'i':
            iCut++;
            break;
        case 'E':
        case 'e':
            eCut++;
            break;
        case 'U':
        case 'u':
            uCut++;
            break;
        case ' ':
            spaceCut++;
            break;
        case '\t':
            tabCut++;
            break;
        case '\n':
            newlineCut++;
            break;

        default:
            break;
        }
    }
    cout << "a:\t" << aCut << endl;
    cout << "e:\t" << eCut << endl;
    cout << "i:\t" << iCut << endl;
    cout << "o:\t" << oCut << endl;
    cout << "u:\t" << uCut << endl;
    cout << "space:\t" << spaceCut << endl;
    cout << "tab:\t" << tabCut << endl;
    cout << "new line:\t" << newlineCut << endl;
}
void p_14()
{
    string currString, preString = "", maxString;
    cout << "Input some string:\n";
    int currCut = 1, maxCut = 1;
    while (cin >> currString)
    {
        if (currString == preString)
        {
            ++currCut;
            if (currCut > maxCut)
            {
                maxCut = currCut;
                maxString = currString;
            }
        }
        else
        {
            currCut = 1;
        }
        //每一次遍历，更新
        preString = currString;
    }
    if (maxCut > 1)
    {
        cout << "MaxString is: " << maxString << ", Count is: " << maxCut;
    }
    else
    {
        cout << "not find MaxString\n";
    }
}
void p_17()
{
    vector<int> s1 = {0, 1, 1, 3};
    vector<int> s2 = {0, 1, 2, 3, 2, 1};
    auto it1 = s1.cbegin();
    auto it2 = s2.cbegin();
    while (it1 != s1.cend() && it2 != s2.cend())
    {
        if (*it1 != *it2)
        {
            cout << "not\n";
            break;
        }
        ++it1;
        ++it2;
    }
    if (it1 == s1.cend())
    {
        cout << "s1->s2\n";
    }
    if (it2 == s2.cend())
    {
        cout << "s2->s1\n";
    }
}

void p_20()
{
    string currString, preString;
    bool flag = true;
    while (cin >> currString)
    {
        //islower isupper
        if (islower(currString[0]))
        {
            continue;
        }
        if (currString == preString)
        {
            cout << "the same word is :" << currString << endl;
            flag = false;
            break;
        }
        preString = currString;
    }
    if (flag)
    {
        cout << "not same word\n";
    }
}
void p_23()
{
    int a, b;
    // cin >> a >> b;
    while (cin >> a >> b)
    {
        if (!b)
        {
            throw runtime_error("b is not zero\n");
        }

        try
        {
            cout << static_cast<float>(a) / b << endl;
        }
        catch (runtime_error err)
        {
            cout << "zero\n";
            cout << err.what() << '\n';
        }
    }
}
int main()
{
    // p_11();
    // p_14();
    // p_17();
    // until 5-20
    // p_20();
    p_23();
    return 0;
}
