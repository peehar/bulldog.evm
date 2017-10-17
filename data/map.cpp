#include "map.h"

namespace data {

//PropertyPtr map::find(const char* key)
//{
//    auto node = find(key, false);
//    return node != nullptr ? node->prop : PropertyPtr();
//}

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
    while (i = key[index])
    {
        try
        {
            p = p->points.find(i);
        }
        catch (CanNotFindException& e)
        {
            if (create)
            auto n = new node_t();
            p->points.insert(i, n);
            p = n;
        }
    }

    return p;
}

//PropertyPtr& map::operator[](const char* key)
//{
//    auto node = find(key, true);
//    return node->prop;
//}

} // namespace data
