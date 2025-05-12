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
    void NextGeneration();
    const Cell* const* GetBoard() const { return currentBoard; }

    // Memory management
    static Cell** AllocateBoard(int xSize, int ySize);
    static void FreeBoard(Cell** board, int xSize);

private:
    Cell** currentBoard;
    Cell** nextBoard;
    bool isCurrentBoardFirst;
}; 