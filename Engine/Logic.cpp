#include "Logic.h"
#include <cassert>

Logic::Logic()
    : currentBoard(nullptr), nextBoard(nullptr), isCurrentBoardFirst(true)
{
    InitializeBoard();
}

Logic::~Logic()
{
    ClearBoard();
}

void Logic::InitializeBoard()
{
    ClearBoard();
    currentBoard = AllocateBoard(Board::FrameCountX, Board::FrameCountY);
    nextBoard = AllocateBoard(Board::FrameCountX, Board::FrameCountY);
}

void Logic::ClearBoard()
{
    if (currentBoard)
    {
        FreeBoard(currentBoard, Board::FrameCountX);
        currentBoard = nullptr;
    }
    if (nextBoard)
    {
        FreeBoard(nextBoard, Board::FrameCountX);
        nextBoard = nullptr;
    }
}

void Logic::SetCell(int x, int y, bool value)
{
    assert(x >= 0 && x < Board::FrameCountX && y >= 0 && y < Board::FrameCountY);
    currentBoard[x][y].isAlive = value;
    if (!value)
    {
        currentBoard[x][y].age = 0;
    }
}

bool Logic::GetCell(int x, int y) const
{
    assert(x >= 0 && x < Board::FrameCountX && y >= 0 && y < Board::FrameCountY);
    return currentBoard[x][y].isAlive;
}

void Logic::NextGeneration()
{
    // Calculate next generation
    for (int x = 0; x < Board::FrameCountX; x++)
    {
        for (int y = 0; y < Board::FrameCountY; y++)
        {
            int neighbors = 0;
            
            // Count live neighbors
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0) continue;

                    int nx = (x + dx + Board::FrameCountX) % Board::FrameCountX;
                    int ny = (y + dy + Board::FrameCountY) % Board::FrameCountY;

                    if (currentBoard[nx][ny].isAlive)
                    {
                        neighbors++;
                    }
                }
            }

            // Apply Conway's Game of Life rules
            bool isAlive = currentBoard[x][y].isAlive;
            if (isAlive)
            {
                nextBoard[x][y].isAlive = (neighbors == 2 || neighbors == 3);
                if (nextBoard[x][y].isAlive)
                {
                    nextBoard[x][y].age = currentBoard[x][y].age + 1;
                }
            }
            else
            {
                nextBoard[x][y].isAlive = (neighbors == 3);
                if (nextBoard[x][y].isAlive)
                {
                    nextBoard[x][y].age = 1;
                }
            }
        }
    }

    // Swap boards
    std::swap(currentBoard, nextBoard);
}

Cell** Logic::AllocateBoard(int xSize, int ySize)
{
    Cell** newBoard = new Cell*[xSize];
    for (int x = 0; x < xSize; x++)
    {
        newBoard[x] = new Cell[ySize];
    }
    return newBoard;
}

void Logic::FreeBoard(Cell** board, int xSize)
{
    if (board)
    {
        for (int x = 0; x < xSize; x++)
        {
            delete[] board[x];
        }
        delete[] board;
    }
} 