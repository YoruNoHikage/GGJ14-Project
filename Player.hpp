#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "SFML/Graphics.hpp"

#include "config.hpp"

#include "SFML/Graphics/Transformable.hpp"

class Player
{
    public:
        Player();
        ~Player();

        sf::Vector2i& getPosition();
        void setPosition(int x, int y);

        void setPosition(sf::Vector2i position);
        void moveInWorld(int x, int y); ///@todo: delete

        Itineraire getPath();

    protected:

    private:
        sf::Vector2i _position;
        Itineraire _path;
};


#endif // PLAYER_HPP
