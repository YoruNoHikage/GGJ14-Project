#ifndef TILE_HPP
#define TILE_HPP

/** \brief Representing one tile (as an obstacle or event)
 *         Abstract class
 */
class Tile
{
    public:
        Tile();
        ~Tile();
        bool alreadyVisited();
        void visit();
        void forgot();
    protected:

    private:
        bool _visited;
};


#endif // TILE_HPP
