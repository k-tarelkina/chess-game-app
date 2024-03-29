#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "ChessboardCell.h"
#include "ChessPiece.fwd.h"
#include "Chessboard.fwd.h"
#include "UI.h"
#include "UIObserver.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"

class Chessboard : public UIObserver
{
public:
  explicit Chessboard(UI *ui);

  void initializeBoard();
  void initializePieces();

  void onCellClicked(int x, int y) override;
  void onStartGame() override;
  void onStartGameOver() override;
  void onUiReady() override;
  void onAddWhitePiecesUser(const std::string &username) override;
  void onAddBlackPiecesUser(const std::string &username) override;

  ChessPiece *putPiece(int x, int y, ChessPiece *piece);
  ChessPiece *getPiece(int x, int y);
  void clearCell(int x, int y);

  bool hasPiece(int x, int y);
  bool isUnderThreat(int x, int y, ChessPiece *checkFor);

  void addDeadPiece(ChessPiece *piece);

private:
  std::vector<std::vector<ChessboardCell>> cells_;
  std::vector<ChessPiece *> pieces_;

  King *whiteKing_;
  King *blackKing_;

  std::string whitePiecesUser_;
  std::string blackPiecesUser_;

  ChessboardCell *selectedCell_;
  UI *ui_;
  Color currentColorTurn_ = Color::White;

  bool gameInProgress = false; // TODO add underscore

  void addNewPiece(int x, int y, ChessPiece *piece);
  void highlightCells(const std::vector<Coordinates> &coordinates);
  void highlightSelectedCell(int x, int y);
  void clearCellsHighlight();
  void switchColorTurn();

  bool usersEntered();
};
