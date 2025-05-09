#include "Logic.h"
#include <cassert>

Logic::Logic()
    : board(nullptr)
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
    board = AllocateBoard(Board::FrameCountX, Board::FrameCountY);
}

void Logic::ClearBoard()
{
    if (board)
    {
        FreeBoard(board, Board::FrameCountX);
        board = nullptr;
    }
}

void Logic::SetCell(int x, int y, bool value)
{
    assert(x >= 0 && x < Board::FrameCountX && y >= 0 && y < Board::FrameCountY);
    board[x][y].isAlive = value;
    if (!value)
    {
        board[x][y].age = 0;
    }
}

bool Logic::GetCell(int x, int y) const
{
    assert(x >= 0 && x < Board::FrameCountX && y >= 0 && y < Board::FrameCountY);
    return board[x][y].isAlive;
}

void Logic::NextGeneration()
{
    // Create a temporary board to store the next generation
    Cell** nextBoard = AllocateBoard(Board::FrameCountX, Board::FrameCountY);

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

                    if (board[nx][ny].isAlive)
                    {
                        neighbors++;
                    }
                }
            }

            // Apply Conway's Game of Life rules
            bool isAlive = board[x][y].isAlive;
            if (isAlive)
            {
                nextBoard[x][y].isAlive = (neighbors == 2 || neighbors == 3);
                if (nextBoard[x][y].isAlive)
                {
                    nextBoard[x][y].age = board[x][y].age + 1;
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

    // Free old board and update to new generation
    FreeBoard(board, Board::FrameCountX);
    board = nextBoard;
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