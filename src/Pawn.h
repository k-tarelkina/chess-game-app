#pragma once

#include "ChessPiece.h"
#include <vector>
#include <string>

class Pawn : public ChessPiece
{
public:
  Pawn(int x, int y, Color color, Chessboard *chessboard) : ChessPiece(x, y, color, chessboard) {}
  ~Pawn() override;

  std::string getName() override;
  bool canFight(int x, int y) override;

protected:
  std::vector<Coordinates>
  getAllPaths() override;
};
