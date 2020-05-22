#include <iostream>
#include "include/chapter_6.h"
using namespace std;
/**
 * 分离测试文件
 * 测试不成功？
 * C:\Users\leal\AppData\Local\Temp\cciKNbg4.o:chapter_6_1.cpp:(.text+0xf7): undefined reference to `uAbs(int)'
collect2.exe: error: ld returned 1 exit status
 */
int main()
{
    cout << fact(0) << endl;
    cout << fact(5) << endl;
    cout << uAbs(0) << " " << abs(0) << endl;
    cout << uAbs(1) << " " << abs(1) << endl;
    cout << uAbs(-1) << " " << abs(-1) << endl;
    
    return 0;
}