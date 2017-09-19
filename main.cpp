#include <iostream>
#include "./data/data.h"
#include "./data/object.h"

using namespace std;
using namespace data;

int main(int argc, char *argv[])
{
    Data data = Data::newNumber(10.0);
    Object obj;
    string pname("aa");
    obj.Put(pname, data, true);
    cout << obj.Get(pname).number() <<  endl;
    cout << "Hello World!" << endl;
    return 0;
}
