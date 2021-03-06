#ifndef XMLNODE_HPP
#define XMLNODE_HPP

#include "node.hpp"

#include <algorithm>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

/** \brief Proxy for rapidxml to use easily and properly in the game
 */
class XMLNode : public Node
{
    public:
        XMLNode();
        XMLNode(const XMLNode* parent);
        ~XMLNode();

        void loadFromFile(const std::string& filename);
        void parse(rapidxml::xml_node<>* node);

    private:
        const XMLNode* _parent;
};

template <typename T>
struct Deallocator
{
    void operator()(const T* p) const
    {
        delete p;
    }
};

#endif // XMLNODE_HPP
