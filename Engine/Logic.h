#pragma once

#include "Board.h"

class Logic
{
public:
    Logic();
    ~Logic();
    Logic(const Logic&) = delete;
    Logic& operator=(const Logic&) = delete;

    // Board state management
    void InitializeBoard();
    void ClearBoard();
    void SetCell(int x, int y, int value);
    int GetCell(int x, int y) const;
    void NextGeneration();
    const int* const* const* GetBoard() const { return board; }
    //The change from const int*** to const int* const* const* means:
    //The innermost const prevents modifying the integer values
    //The middle const prevents modifying the pointers to integers
    //The outer const prevents modifying the pointers to pointers
    
    // Memory management
    static int*** AllocateBoard(int xSize, int ySize);
    static void FreeBoard(int*** board, int xSize, int ySize);

private:
    int*** board;
    static const int CELL_STATES = 5; // Number of states per cell
}; 