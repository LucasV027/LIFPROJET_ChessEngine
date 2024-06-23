#include "IA/ChessIA.h"

namespace ChessIA
{
    void countSubNodes(ChessGame &root, int maxDepth, bool multiThread)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Counting sub-nodes, " << (multiThread ? "multi-threaded" : "single-threaded") << " version :" << std::endl;

        for (size_t depth = 1; depth < maxDepth + 1; depth++)
        {
            ChessGame copy(root);
            auto start1 = std::chrono::high_resolution_clock::now();
            int sum = (multiThread ? ChessIA::countSubPositionMT(copy, depth) : ChessIA::countSubPosition(copy, depth));
            auto end1 = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> minimax_duration = end1 - start1;

            std::cout << "Depth : " << depth << " -> Calculation time : " << minimax_duration.count() << " seconds. Number of sub-positions : " << sum << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> total_time = end - start;
        std::cout << "Total time : " << total_time.count() << " seconds." << std::endl;
    }

    int countSubPosition(ChessGame &state, int depth)
    {
        if (depth <= 1)
        {
            return state.getAllPossibleMoves().size();
        }

        int childNodes = 0;
        for (const Move &move : state.getAllPossibleMoves())
        {
            state.makeAMove(move, false);

            childNodes += countSubPosition(state, depth - 1);

            state.undoMove();
        }

        return childNodes;
    }

    int countSubPositionMT(ChessGame root, int depth)
    {
        if (depth <= 1)
            return (countSubPosition(root, 1));

        int sum = 0;
#pragma omp parallel for
        for (const Move &move : root.getAllPossibleMoves())
        {
            ChessGame nextNode(root);
            nextNode.makeAMove(move, false);
            int result = countSubPosition(nextNode, depth - 1);

#pragma omp critical(sum_accession)
            sum += result;
        }

        return sum;
    }

    int evaluation(const ChessGame &cg)
    {
        int sum = 0;

        for (const std::vector<ChessPiece> &row : cg.chessBoard)
        {
            for (const ChessPiece piece : row)
            {
                if (piece.playerIndex == cg.turnIndex)
                {
                    sum += piece.getValue();
                }
                else
                {
                    sum -= piece.getValue();
                }
            }
        }

        return sum;
    }

    int evaluation(const ChessGame &cg, int playerMaximizingIndex)
    {
        int sum = 0;

        for (const std::vector<ChessPiece> &row : cg.chessBoard)
        {
            for (const ChessPiece piece : row)
            {
                if (piece)
                {
                    if (piece.playerIndex == playerMaximizingIndex)
                    {
                        sum += piece.getValue();
                    }
                    else
                    {
                        sum -= piece.getValue();
                    }
                }
            }
        }
        return sum;
    }

    Move bestMove(ChessGame &root, int depth, bool verbose)
    {
        int playerMaximizingIndex = root.turnIndex;

        int bestMoveIndex = 0;
        int bestMinimaxResult = -infinity;

        auto moves = root.getAllPossibleMoves();

        std::cout << std::endl;

        for (size_t moveIndex = 0; moveIndex < moves.size(); moveIndex++)
        {
            ChessGame nextNode(root);
            nextNode.makeAMove(moves[moveIndex], false);
            int minimaxResult = minimax(nextNode, depth - 1, -infinity, infinity, playerMaximizingIndex);
            // int minimaxResult = minimax(nextNode, depth - 1, playerMaximizingIndex);

            if (verbose)
            {
                moves[moveIndex].from.print();
                std::cout << " -> ";
                moves[moveIndex].to.print();
                std::cout << "-> Value = " << minimaxResult << "\n";
            }

            if (minimaxResult > bestMinimaxResult)
            {
                bestMinimaxResult = minimaxResult;
                bestMoveIndex = moveIndex;
            }
        }

        if (verbose)
        {
            std::cout << "Best value found : " << bestMinimaxResult << std::endl;
        }

        return moves[bestMoveIndex];
    }

    Move bestMoveMT(ChessGame root, int depth, bool verbose)
    {
        int playerMaximizingIndex = root.turnIndex;

        std::vector<int> minimaxResults;
        auto moves = root.getAllPossibleMoves();
        minimaxResults.reserve(moves.size());

#pragma omp parallel for
        for (size_t moveIndex = 0; moveIndex < moves.size(); moveIndex++)
        {
            ChessGame nextNode(root);
            nextNode.makeAMove(moves[moveIndex], false);
            int minimaxResult = minimax(nextNode, depth - 1, -infinity, infinity, playerMaximizingIndex);

#pragma omp critical(accessing_the_vector)
            minimaxResults[moveIndex] = minimaxResult;
        }

        int maxMoveIndex = minimaxResults[0];
        for (size_t i = 1; i < minimaxResults.size(); ++i)
        {
            if (minimaxResults[i] > maxMoveIndex)
            {
                maxMoveIndex = minimaxResults[i];
            }
        }
        return moves[maxMoveIndex];
    }

    int minimax(ChessGame &state, int depth, int alpha, int beta, int playerMaximizingIndex)
    {
        if (depth == 0 || state.isOver())
        {
            return evaluation(state, playerMaximizingIndex);
        }

        if (state.turnIndex == playerMaximizingIndex) // Maxmimizing
        {
            int maxEval = -infinity;
            for (const Move &move : state.getAllPossibleMoves())
            {

                state.makeAMove(move, false);
                int eval = minimax(state, depth - 1, alpha, beta, playerMaximizingIndex);
                state.undoMove();

                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return maxEval;
        }
        else // Minimizing
        {
            int minEval = infinity;
            for (const Move &move : state.getAllPossibleMoves())
            {
                state.makeAMove(move, false);
                int eval = minimax(state, depth - 1, alpha, beta, playerMaximizingIndex);
                state.undoMove();

                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return minEval;
        }
    }

    int minimax(ChessGame &state, int depth, int playerMaximizingIndex)
    {
        if (depth == 0 /*|| state.isOver()*/)
        {
            return evaluation(state, playerMaximizingIndex);
        }

        if (state.turnIndex == playerMaximizingIndex)
        {
            int maxEval = -infinity;
            for (const Move &move : state.getAllPossibleMoves())
            {

                state.makeAMove(move, false);
                int eval = minimax(state, depth - 1, playerMaximizingIndex);
                state.undoMove();

                maxEval = std::max(maxEval, eval);
            }
            return maxEval;
        }
        else // Minimizing
        {
            int minEval = infinity;
            for (const Move &move : state.getAllPossibleMoves())
            {
                state.makeAMove(move, false);
                int eval = minimax(state, depth - 1, playerMaximizingIndex);
                state.undoMove();

                minEval = std::min(minEval, eval);
            }
            return minEval;
        }
    }
}