#include <iostream>
using namespace std;
int main()
{
    int i;
    char str[] = "hello world";
    const char *ptr = str;
    for(int i = 0;i < 11;i++){
        cout << ptr[i];
    }
    cout << endl;
    //ptr[0] = 's';
    str[0] = 'g';
    for(int i = 0;i < 11;i++){
        cout << ptr[i];
    }
    cout << endl;
}