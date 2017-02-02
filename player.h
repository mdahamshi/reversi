#ifndef PLAYER_H
#define PLAYER_H


class Player
{
private:
    int type;
    int depth;
    int alg;
    int color;
public:
    Player();
    Player(int type, int alg, int depth ,int color);
    int getType() const;
    void setType(int value);
    int getDepth() const;
    void setDepth(int value);
    int getAlg() const;
    void setAlg(int value);
    int getColor() const;
    void setColor(int value);
};

#endif // PLAYER_H
