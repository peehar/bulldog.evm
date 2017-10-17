#include "map.h"

namespace data {

map::map() : root(nullptr)
{
    
}

PropertyPtr map::find(const wchar_t* key)
{
   node_t *node = find(key, false);
   return node != nullptr ? node->prop : PropertyPtr();
}

map::node_t* map::find(const wchar_t* key, bool create)
{
    if (root == nullptr)
    {
        if (!create)
            return nullptr;
        root = new node_t();
    }

    int index = 0;
    node_t* p = root;
    int i;
    while (i = key[index++])
    {
        try
        {
            p = p->points.find(i);
        }
        catch (CanNotFindException& e)
        {
            if (!create)
                return nullptr;
            auto n = new node_t();
            p->points.insert(i, n);
            p = n;
        }
    }

    return p;
}

PropertyPtr& map::operator[](const wchar_t* key)
{
   node_t* node = find(key, true);
   return node->prop;
}

} // namespace data
