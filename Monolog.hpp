#ifndef MONOLOG_HPP
#define MONOLOG_HPP

#include <vector>
#include <string>

typedef std::vector<std::string> ArrayString;

class Monolog
{
    public:
        Monolog();
        ~Monolog();

        bool loadFromFile(const std::string& filename);

        bool isLoaded();
    protected:

    private:
        ArrayString _strings;

        bool _isLoaded;
};


#endif // MONOLOG_HPP
