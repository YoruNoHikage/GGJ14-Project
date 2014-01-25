#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "config.hpp"

#include "SFML/Graphics/Transformable.hpp"

class Player
{
    public:
        Player();
        ~Player();

        sf::Vector2i& getPosition();
        void setPosition(int x, int y);

        void moveInWorld(int x, int y);
    protected:

    private:
        sf::Vector2i _position;
};


#endif // PLAYER_HPP
