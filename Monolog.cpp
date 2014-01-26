#include <iostream>

#include "lib/XMLNode.hpp"&
#include "Monolog.hpp"

Monolog::Monolog() : _isLoaded(false)
{

}

Monolog::~Monolog()
{

}

bool Monolog::loadFromFile(const std::string& filename)
{
    std::cout << "Monolog : loading " << filename << std::endl;
    XMLNode root;

    try
    {
        root.loadFromFile(filename);

        std::vector<Node*> lines = root.getChildren("line");
        for(std::vector<Node*>::iterator itr = lines.begin() ; itr != lines.end() ; ++itr)
        {
            _strings.push_back((*itr)->getValue());
            std::cout << (*itr)->getValue() << std::endl;
        }

        _isLoaded = true;

    }
    catch(std::exception const& e)
    {
        _strings.push_back(e.what());
        std::cout << e.what() << std::endl;
    }

    return true;
}

bool Monolog::isLoaded()
{
    return _isLoaded;
}

