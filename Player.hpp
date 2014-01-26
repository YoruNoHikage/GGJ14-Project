#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "SFML/Graphics.hpp"

#include "config.hpp"

class Player
{
    public:
        Player();
        ~Player();

        sf::Vector2i getPosition();
        void setPosition(int x, int y);

        void setPosition(sf::Vector2i position);
        void registerPath(int x, int y);

        Itineraire getPath();

        int getIdEventTarget();
        void setIdEventTarget(int id);

    protected:

    private:
        sf::Vector2i _position;
        Itineraire _path;

        int _idEventTarget;
};


#endif // PLAYER_HPP
