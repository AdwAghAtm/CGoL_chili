#include "Logic.h"
#include <cassert>
#include <array>

Logic::Logic()
{
}

Logic::~Logic()
{
}

std::array<bool, 9> Logic::GetNeighbors(const uint8_t* board, int x, int y)
{
    std::array<bool, 9> neighbors;
    int index = 0;
    
    // Check all 8 surrounding cells
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
            {
                neighbors[index++] = false; // Skip the center cell
                continue;
            }
            
            int nx = x + dx;
            int ny = y + dy;
            
            // Check bounds
            if (nx >= 0 && nx < Board::FrameCountX && ny >= 0 && ny < Board::FrameCountY)
            {
                neighbors[index++] = board[ny * Board::FrameCountX + nx] != 0;
            }
            else
            {
                neighbors[index++] = false;
            }
        }
    }
    
    return neighbors;
}
std::array<bool, 9> Logic::GetNeighbors2(const uint8_t* board, int x, int y)
{
    std::array<bool, 9> neighbors;
    int index = 0;

    // Check all 8 surrounding cells
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == dy)
            {
                neighbors[index++] = false; // Skip the center cell
                continue;
            }

            int nx = x + dx;
            int ny = y + dy;

            // Check bounds
            if (nx >= 0 && nx < Board::FrameCountX && ny >= 0 && ny < Board::FrameCountY)
            {
                neighbors[index++] = board[ny * Board::FrameCountX + nx] != 0;
            }
            else
            {
                neighbors[index++] = false;
            }
        }
    }

    return neighbors;
}

bool Logic::ApplyRules(bool isAlive, int neighbors)
{
    return ConwayRules2(isAlive, neighbors);
}

bool Logic::ConwayRules(bool isAlive, int neighbors)
{
    // Conway's Game of Life rules
    if (isAlive)
    {
        // Any live cell with fewer than two live neighbors dies (underpopulation)
        // Any live cell with more than three live neighbors dies (overpopulation)
        return neighbors == 2 || neighbors == 3;
    }
    else
    {
        // Any dead cell with exactly three live neighbors becomes alive (reproduction)
        return neighbors == 3;
    }
} 

bool Logic::ConwayRules2(bool isAlive, int neighbors)
{
    // Conway's Game of Life rules
    if (isAlive)
    {
        // Any live cell with fewer than two live neighbors dies (underpopulation)
        // Any live cell with more than three live neighbors dies (overpopulation)
        return neighbors == 2 || neighbors == 3;
    }
    else
    {
        // Any dead cell with exactly three live neighbors becomes alive (reproduction)
        return neighbors == 3;
    }
}