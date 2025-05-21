#include "Logic.h"
#include <cassert>
#include <array>

// Conway's Game of Life rules implementation
bool Logic::ConwayRules(bool isAlive, int neighbors)
{
    if (isAlive)
    {
        return (neighbors == 2 || neighbors == 3);
    }
    else
    {
        return (neighbors == 3);
    }
}

Logic::Logic()
    : currentBoard(nullptr)
    , nextBoard(nullptr)
    , currentRules(ConwayRules)  // Default to Conway's rules lambda albo obiekt std::function albo template
{
    InitializeBoard();
}

Logic::~Logic()
{
    ClearBoards();
}

void Logic::InitializeBoard()
{
    ClearBoards();
    currentBoard = AllocateBoard(Board::FrameCountX, Board::FrameCountY);
    nextBoard = AllocateBoard(Board::FrameCountX, Board::FrameCountY);
    tempBoard = AllocateBoard(Board::FrameCountX, Board::FrameCountY);
}

void Logic::ClearBoards()
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
std::array<bool, 9> Logic::GetNeighbors(const Cell* const* board, int x, int y) {
    assert(x >= 0 && x < Board::FrameCountX && y >= 0 && y < Board::FrameCountY);
    std::array<bool, 9> neighbors{ false, false, false, false, false, false, false, false, false, };

    unsigned int n = 0;
    for (int i = -1; i<=1 ; i++)
    {
        if (y == 0 && i == -1)
        {
            n += 3;
            continue;
        }
        if (y == Board::FrameCountY-1 && i == 1)
        {
            n += 3;
            continue;
        }
        for (int j = -1; j <= 1; j++) {
            if (x == 0 && j == -1)
            {
                n++; 
                continue;;
            }
            if (x == Board::FrameCountX-1 && j == 1)
            {
                n++;
                continue;
            }
            neighbors[n] = board[x+j][y+i].isAlive;
            n++;
        }
    }
    
    return neighbors;
}

bool Logic::ApplyRules(bool isAlive, int neighbors) const
{
    return currentRules(isAlive, neighbors);
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

            // Apply rules to determine next state
            bool isAlive = currentBoard[x][y].isAlive;
            nextBoard[x][y].isAlive = ApplyRules(isAlive, neighbors);
            
            // Update age
            if (nextBoard[x][y].isAlive)
            {
                nextBoard[x][y].age = isAlive ? currentBoard[x][y].age + 1 : 1;
            }
            else
            {
                nextBoard[x][y].age = 0;
            }
        }
    }

    // Swap boards
    tempBoard = currentBoard;
    currentBoard = nextBoard;
    nextBoard = tempBoard;
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