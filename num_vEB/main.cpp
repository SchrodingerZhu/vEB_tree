#include <iostream>
#include <veb.h>
using namespace std;

int main()
{   int a;
    vEB tree(1048576);
    tree.insert(1);
    tree.insert(999);
    tree.erase(1);
    tree.erase(999);
    while(cin>>a)cout<<tree.successor(1);

}
