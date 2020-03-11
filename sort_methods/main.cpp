#include "Sort.h"
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    int A[20];
    srand(time(nullptr));
    for (size_t i = 0; i < 20; i++)
    {
        A[i] = rand() % 1000 + 1;
        cout << A[i] << " ";
    }
    cout << endl;
    
    Sort<int> B(A, 20);
    //B.insert();
    //B.bubble();
    //B.select();
    //B.fast();
    //B.heap();
    //B.count();
    B.merge();
    for (size_t i = 0; i < 20; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
    return 0;
}