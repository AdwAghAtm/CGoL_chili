#pragma once

#include "Board.h"
#include "Cell.h"

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
    void SetCell(int x, int y, bool value);
    bool GetCell(int x, int y) const;
    static std::array<bool, 9> GetNeighbors(const Cell* const* board, int x, int y);
    void NextGeneration();
    const Cell* const* GetCurrentBoard() const { return currentBoard; }
    //The innermost const prevents modifying the Cell values
    //The middle const prevents modifying the pointers to Cells
    //The outer const prevents modifying the pointers to pointers

    // Memory management

private:
    static Cell** AllocateBoard(int xSize, int ySize);
    static void FreeBoard(Cell** board, int xSize);
    // Game rules function type
    using RuleFunction = bool(*)(bool isAlive, int neighbors);
    
    // Current implementation of Conway's Game of Life rules
    static bool ConwayRules(bool isAlive, int neighbors);
    
    // Apply the current rules to a cell
    bool ApplyRules(bool isAlive, int neighbors) const;
    
    // Board management
    void ClearBoards();
    
    // Two boards for double buffering
    Cell** currentBoard;
    Cell** nextBoard;
    Cell** tempBoard;
    
    // Current rule set
    RuleFunction currentRules;
}; 