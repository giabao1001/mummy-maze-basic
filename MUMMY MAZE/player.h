#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

class abstractMove {
    virtual void Move() = 0;
};

class player : abstractMove {
private:
    int x ;
    int y ;
public:
    int getX
    {
        return x;
    }
    int getY
    {
        return y;
    }
    void Move (int newX, int newY) {
        x = newX;
        y = newY;
    }
};

#endif // PLAYER_MOVEMENT_H
