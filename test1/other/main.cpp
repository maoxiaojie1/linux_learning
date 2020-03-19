#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <stdio.h>
using namespace std;

void func(string &fileName, int index = 0)
{
    const char *str = "./";
    string str1 = str;
    string str2 = str1 + fileName;
    if (!access(str2.c_str(), F_OK))
    {
        index++;
        string temp = fileName;
        temp[temp.size() - 8] = (char)('1' + index);
        if (index >= 4)
        {
            return;
        }
        func(temp, index);
        rename(fileName.c_str(), temp.c_str());
    }
}

int main(int argc, char *argv[])
{
    string str1 = "01.bbx.gz";
    //str1 = "ppp" + str1;
    cout << str1;
    func(str1, 0);

    return 0;
}
