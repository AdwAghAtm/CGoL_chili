#pragma once

#include "Board.h"
#include <array>

class Logic
{
public:
    Logic();
    ~Logic();
    Logic(const Logic&) = delete;
    Logic& operator=(const Logic&) = delete;

    // Game rules
    static std::array<bool, 9> GetNeighbors(const uint8_t* board, int x, int y);
    static bool ApplyRules(bool isAlive, int neighbors);
    static bool ConwayRules(bool isAlive, int neighbors);

private:
    // Game rules function type
    using RuleFunction = bool(*)(bool isAlive, int neighbors);
    
    // Current rule set
    RuleFunction currentRules;
}; 