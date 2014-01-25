#ifndef CONFIG_HPP
#define CONFIG_HPP

#define WORLD_WIDTH 50
#define WORLD_HEIGHT 50

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

#define VIEW_WIDTH 1280
#define VIEW_HEIGHT 720

#define PATH_WIDTH 50
#define PATH_HEIGHT 50

typedef enum Direction
{
    TOP, BOT, LEFT, RIGHT
} Direction;

typedef std::vector<Direction> Itineraire;


#endif // CONFIG_HPP
