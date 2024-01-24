#ifndef CELL_H
#define CELL_H
    
class Cell
{
public:
    Cell();
    void setWall(int index, bool visible);
    void setVisited();
    void setSurrounded();
    bool wasAlreadyVisited();
    bool isSurrounded();
    bool getWall(int index);
private:
    bool visited;
    bool surrounded;
    bool walls[4];
};

// The value is redundant, but was added for clarity
enum Wall { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

#endif
