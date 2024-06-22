#pragma once

#include "Core/Player.h"
#include <string>

namespace Demo
{
    struct DemoGame
    {
        std::vector<std::string> board;
        std::vector<Player> players;
        unsigned int turnIndex;

        DemoGame(std::vector<std::string> _board, std::vector<Player> _players, unsigned int _turnIndex) : board(_board), players(_players), turnIndex(_turnIndex) {}
    };

    const DemoGame getDemoGame(int x);

    const std::vector<std::string> demoDefaultBoard{"R1 N1 B1 Q1 K1 B1 N1 R1",
                                                    "P1 P1 P1 P1 P1 P1 P1 P1",
                                                    "__ __ __ __ __ __ __ __",
                                                    "__ __ __ __ __ __ __ __",
                                                    "__ __ __ __ __ __ __ __",
                                                    "__ __ __ __ __ __ __ __",
                                                    "P0 P0 P0 P0 P0 P0 P0 P0",
                                                    "R0 N0 B0 Q0 K0 B0 N0 R0"};

    const std::vector<Player> demoDefaultPlayers{
        Player("Player 0 (White)", 0, Direction::North, Vec3Int(Color::White)),
        Player("Player 1 (Black)", 1, Direction::South, Vec3Int(Color::Black)),
    };

    const std::vector<std::string> demoBoard1{"__ __ __ R2 N2 B2 K2 Q2 B2 N2 R2 __ __ __",
                                              "__ __ __ P2 P2 P2 P2 P2 P2 P2 P2 __ __ __",
                                              "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
                                              "R3 P3 __ __ __ __ __ __ __ __ __ __ P1 R1",
                                              "N3 P3 __ __ __ __ __ __ __ __ __ __ P1 N1",
                                              "B3 P3 __ __ __ __ __ __ __ __ __ __ P1 B1",
                                              "Q3 P3 __ __ __ __ __ __ __ __ __ __ P1 K1",
                                              "K3 P3 __ __ __ __ __ __ __ __ __ __ P1 Q1",
                                              "B3 P3 __ __ __ __ __ __ __ __ __ __ P1 B1",
                                              "N3 P3 __ __ __ __ __ __ __ __ __ __ P1 N1",
                                              "R3 P3 __ __ __ __ __ __ __ __ __ __ P1 R1",
                                              "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
                                              "__ __ __ P0 P0 P0 P0 P0 P0 P0 P0 __ __ __",
                                              "__ __ __ R0 N0 B0 Q0 K0 B0 N0 R0 __ __ __"};

    const std::vector<Player> demoPlayers1{
        Player("Player 0", 0, Direction::North, Vec3Int(Color::Red)),
        Player("Player 1", 1, Direction::West, Vec3Int(Color::Yellow)),
        Player("Player 2", 2, Direction::South, Vec3Int(Color::Green)),
        Player("Player 3", 3, Direction::Est, Vec3Int(Color::Blue)),
    };

    const std::vector<std::string> demoBoard2{
        "__ K7 __ K8 __ K9 __ __ __ __ __ __ __ __",
        "__ P7 __ P8 __ P9 __ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __ __ Q0 Q1 Q2 __ __",
        "__ __ __ __ __ __ __ __ __ Q3 Q4 Q5 __ __",
        "__ __ __ __ __ __ __ __ __ Q6 Q7 Q8 __ __",
        "__ __ __ __ __ __ __ __ __ __ Q9 __ __ __",
        "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
        "__ __ __ __ __ __ __ __ __ __ __ __ __ __",
        "P0 __ P1 __ P2 __ P3 __ P4 __ P5 __ P6 __",
        "K0 __ K1 __ K2 __ K3 __ K4 __ K5 __ K6 __",
    };

    const std::vector<Player> demoPlayers2{
        Player("Player 0", 0, Direction::North, Vec3Int(255, 0, 0)),   // Red
        Player("Player 1", 1, Direction::North, Vec3Int(255, 255, 0)), // Yellow
        Player("Player 2", 2, Direction::North, Vec3Int(0, 255, 0)),   // Green
        Player("Player 3", 3, Direction::North, Vec3Int(0, 0, 255)),   // Blue
        Player("Player 4", 4, Direction::North, Vec3Int(255, 0, 255)), // Magenta
        Player("Player 5", 5, Direction::North, Vec3Int(255, 165, 0)), // Orange
        Player("Player 6", 6, Direction::North, Vec3Int(0, 255, 255)),
        Player("Player 7", 7, Direction::South, Vec3Int(128, 0, 128)), // Purple
        Player("Player 8", 8, Direction::South, Vec3Int(128, 128, 0)),
        Player("Player 9", 9, Direction::South, Vec3Int(Color::White))};

}