project(MyApp C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/UI.h"
            "src/UI.cpp"
            "src/main.cpp"
            "src/ChessboardCell.cpp"
            "src/Chessboard.fwd.h"  
            "src/ChessPiece.h" 
            "src/ChessboardCell.h"    
            "src/Chessboard.h"  
            "src/Chessboard.cpp"      
            "src/ChessPiece.cpp"   
            "src/ChessboardEnum.h"    
            "src/ChessboardEnum.cpp"    
            "src/ChessPiece.fwd.h"  
            "src/UIObserver.h"
            "src/Queen.h"
            "src/Queen.cpp"
            "src/King.h"
            "src/King.cpp"
            "src/Pawn.h"
            "src/Pawn.cpp"
            "src/Bishop.h"
            "src/Bishop.cpp"
            "src/Knight.h"
            "src/Knight.cpp"
            "src/Rook.h"
            "src/Rook.cpp"
)

add_app("${SOURCES}")

set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets") 

add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/" "${ASSETS_PATH}")