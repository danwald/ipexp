#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    if(argc > 1) 
        cout <<"Hello, I will process your images"<<endl;
    else
    {
        cout <<"Hello, can I has your image directory?"<<endl;
        return 1;
    }
    cout <<" Done. Now send me some images"<<endl;
    return 0;
}
