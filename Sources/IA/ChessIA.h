#pragma once

#include "../Core/ChessGame.h"

#include <omp.h> // Parallelism

#include <chrono> // Chrono for countSubNodes

const int infinity = 1000000; // std::numeric_limits<int>::infinity();

namespace ChessIA
{
    void countSubNodes(ChessGame &root, int depth, bool multiThread);
    int countSubPosition(ChessGame &state, int depth);
    int countSubPositionMT(ChessGame root, int depth);

    int evaluation(const ChessGame &cg);
    int evaluation(const ChessGame &cg, int playerMaximizingIndex);

    Move bestMove(ChessGame &root, int depth, bool verbose);
    Move bestMoveMT(ChessGame root, int depth, bool verbose);

    int minimax(ChessGame &state, int depth, int alpha, int beta, int playerMaximizingIndex);
    int minimax(ChessGame &state, int depth, int playerMaximizingIndex);

}
