#include "Logic.h"
#include <cstdlib>

Logic::Logic()
    : board(nullptr)
{
    InitializeBoard();
}

Logic::~Logic()
{
    if (board != nullptr)
    {
        FreeBoard(board, Board::FrameCountX + 2, Board::FrameCountY + 2);
        board = nullptr;
    }
}

void Logic::InitializeBoard()
{
    board = AllocateBoard(Board::FrameCountX + 2, Board::FrameCountY + 2);
    ClearBoard();
}

void Logic::ClearBoard()
{
    for (int i = 0; i < Board::FrameCountX + 2; i++)
    {
        for (int j = 0; j < Board::FrameCountY + 2; j++)
        {
            board[i][j][0] = 0;
        }
    }
}

void Logic::SetCell(int x, int y, int value)
{
    if (x >= 0 && x < Board::FrameCountX + 2 && y >= 0 && y < Board::FrameCountY + 2)
    {
        board[x][y][0] = value;
    }
}

int Logic::GetCell(int x, int y) const
{
    if (x >= 0 && x < Board::FrameCountX + 2 && y >= 0 && y < Board::FrameCountY + 2)
    {
        return board[x][y][0];
    }
    return 0;
}

void Logic::NextGeneration()
{
    auto newBoard = AllocateBoard(Board::FrameCountX + 2, Board::FrameCountY + 2);

    for (int x = 1; x < Board::FrameCountX + 1; x++)
    {
        for (int y = 1; y < Board::FrameCountY + 1; y++)
        {
            int liveNeighbors = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0) continue;
                    if (board[x + dx][y + dy][0] == 1)
                    {
                        liveNeighbors++;
                    }
                }
            }

            if (board[x][y][0] == 1)
            {
                newBoard[x][y][0] = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
            }
            else
            {
                newBoard[x][y][0] = (liveNeighbors == 3) ? 1 : 0;
            }
        }
    }

    FreeBoard(board, Board::FrameCountX + 2, Board::FrameCountY + 2);
    board = newBoard;
}

int*** Logic::AllocateBoard(int xSize, int ySize)
{
    int*** p = (int***)malloc(xSize * sizeof(int**));
    if (p == nullptr)
    {
        return nullptr;
    }

    for (int i = 0; i < xSize; i++)
    {
        p[i] = nullptr;
    }

    for (int i = 0; i < xSize; i++)
    {
        p[i] = (int**)malloc(ySize * sizeof(int*));
        if (p[i] == nullptr)
        {
            FreeBoard(p, xSize, ySize);
            return nullptr;
        }

        for (int j = 0; j < ySize; j++)
        {
            p[i][j] = nullptr;
        }

        for (int j = 0; j < ySize; j++)
        {
            p[i][j] = (int*)malloc(CELL_STATES * sizeof(int));
            if (p[i][j] == nullptr)
            {
                FreeBoard(p, xSize, ySize);
                return nullptr;
            }
        }
    }

    return p;
}

void Logic::FreeBoard(int*** board, int xSize, int ySize)
{
    if (board == nullptr)
    {
        return;
    }

    for (int i = 0; i < xSize; i++)
    {
        if (board[i] != nullptr)
        {
            for (int j = 0; j < ySize; j++)
            {
                if (board[i][j] != nullptr)
                {
                    free(board[i][j]);
                }
            }
            free(board[i]);
        }
    }
    free(board);
} 