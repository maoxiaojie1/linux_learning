#include <iostream>

using namespace std;

int price[10] = {1,5,8,9,10,17,17,20,24,30};

/* 自下而上 */
int cut_rod(int *p, int n)
{
    int *r = new int[n]();
    int q = 0;
    for (size_t i = 1; i < n; i++)
    {
        q = p[i];
        for (size_t j = 0; j < i; j++)
        {
            q = max(q, p[j] + r[i - j-1]);
        }
        r[i] = q;
    }
    int temp = r[n-1];
    delete []r;
    return temp;
}

/* 自顶而下 */

int cut_up_rod(int *p, int *r, int n)
{
    if (n < 1)
    {
        return 0;
    }
    
    if (r[n - 1] > 0)
    {
        return r[n - 1];
    }

    int q = 0;
    for (size_t i = 0; i < n; i++)
    {
        q = max(q, p[i] + cut_up_rod(p, r, n - i - 1));
    }
    r[n-1] = q;
    return q;
}

int main()
{
    int n;
    cin >> n;
    cout << cut_rod(price, n)<<endl;

    int *r = new int[n]();
    cout << cut_up_rod(price, r, n)<<endl;
    delete []r;
    return 0;
}