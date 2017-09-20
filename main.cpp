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
    obj.put(pname, data, true);
    cout << obj.get(pname).number() <<  endl;
    cout << "Hello World!" << endl;
    return 0;
}
