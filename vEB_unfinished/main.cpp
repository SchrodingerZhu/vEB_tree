File Edit Options Buffers Tools C++ Help                                        
#include <iostream>
#include <veb.h>
using namespace std;

int main()
{
    vEB<int> tree(1024);
    tree.insert(0,1024);
    tree.insert(1,1);
    tree.erase(1);
    cout<<tree.max.second;

}
