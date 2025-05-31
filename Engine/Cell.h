#pragma once

struct Cell
{
    bool isAlive;
    uint8_t age;
    uint8_t state;
    uint8_t nextState;
    uint8_t tempState;

    Cell() : isAlive(false), age(0), state(0), nextState(0), tempState(0) {}
}; 