#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
/**
 * IO库
 * 多熟悉iostream\fstream \sstream
 * */
istream &f(istream &in)
{
    string v;
    // 遇到文件结束符，IO错误，读入无效数据方能退出循环
    while (in >> v, !in.eof())
    {
        if (in.bad())
        {
            throw runtime_error("IO stream error");
        }
        if (in.fail())
        {
            cerr << "data error! please retry\n";
            in.clear();
            in.ignore(100, '\n');
            continue;
        }
        cout << v << endl;
    }

    return in;
}
void getFile(string fileName)
{
    ifstream in(fileName);
    if (!in)
    {
        cerr << "Can't open the file!\n";
        return;
    }
    string line;
    vector<string> words;
    // getline 读取一行，以\n
    // cin 读取以空格拆分
    while (getline(in, line))
    {
        words.push_back(line);
    }
    in.close();
    //print vector
    // for (auto &w : words)
    // {
    //     cout << w << endl;
    // }
    // 文件很大时，使用迭代器
    cout << "read file by iterator:\n";
    vector<string>::const_iterator w = words.cbegin();
    while (w < words.cend())
    {
        cout << *w << endl;
        ++w;
    }
    // read file by istringstream
    cout << "\nread file by istringstream:\n";
    vector<string>::const_iterator w2 = words.cbegin();
    while (w2 < words.cend())
    {
        istringstream line_str(*w2);
        string word;
        while (line_str >> word)
        {
            cout << word << " ";
        }
        cout << endl;
        ++w2;
    }
}
void p_9()
{
    ostringstream msg;
    msg << "C++ Primer 第五啊" << endl;
    istringstream in(msg.str());
    f(in);
}
int main()
{
    // f(cin);
    // getFile("include/chapter_6.h");
    p_9();
    return 0;
}