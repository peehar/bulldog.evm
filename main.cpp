#include <iostream>
#include "./data/data.h"
#include "./data/object.h"
#include "./utils/avl.h"
#include "./data/map.h"
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace data;

class C
{
public:
    int operator()(string a, string b) {
        return a.compare(b);
    }
};

int main(int argc, char *argv[])
{
//    Data data = Data::newNumber(10.0);
//    Object obj;
//    string pname("aa");
//    obj.putValue(pname, data);
//    cout << obj.getValue(pname).number() <<  endl;
//    cout << "Hello World!" << endl;

    AVLMap<string, int, C> map;

    map.insert("abc", 10);
    map.insert("abdc", 10);
    map.insert("huiv", 10);
    map.insert("uiofwen", 10);
    map.insert("qvgf", 10);
    map.insert("hufrmds", 10);

    map.insert("ubqw", 10);
    map.insert("vmhew", 10);

//    srand((unsigned)time(0));
//    for (int i = 0; i < 10; i++)
//        map.insert(rand() %100, rand() % 100);

    return 0;
}

