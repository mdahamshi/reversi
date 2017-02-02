#include "player.h"

int Player::getType() const
{
    return type;
}

void Player::setType(int value)
{
    type = value;
}

int Player::getDepth() const
{
    return depth;
}

void Player::setDepth(int value)
{
    depth = value;
}

int Player::getAlg() const
{
    return alg;
}

void Player::setAlg(int value)
{
    alg = value;
}

int Player::getColor() const
{
    return color;
}

void Player::setColor(int value)
{
    color = value;
}

Player::Player()
{

}
Player::Player(int type, int alg, int depth,int color)
{
    this->type = type;
    this->alg = alg;
    this->depth = depth;
    this->color = color;
}
