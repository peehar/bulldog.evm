#ifndef DATA_MAP_H
#define DATA_MAP_H

#include <memory>
#include "../utils/avl.h"
#include "property.h"


namespace data {

class map
{
    struct node_t
    {
        AVLMap<wchar_t, node_t*> points;
        PropertyPtr prop;
    };

public:
    map();
    PropertyPtr find(const wchar_t* key);
    PropertyPtr& operator[](const wchar_t* key);

private:
    node_t* find(const wchar_t* key, bool create);


private:
    node_t* root;
};

} // namespace data

#endif // DATA_MAP_H
