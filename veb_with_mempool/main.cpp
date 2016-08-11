#include <iostream>
#include <memory>
#include "veb.hpp"
#include "memorypool.hpp"
#include <random>
using namespace std;

int main(int argc, char *argv[])
{
    random_device dev;
    mt19937_64 eng(dev());
    uniform_int_distribution<int> dist(1,2047);
    vEB_tree v(2048);
    for(int i=0;i<1048576;i++){
        v.insert(dist(eng));
    }
}
