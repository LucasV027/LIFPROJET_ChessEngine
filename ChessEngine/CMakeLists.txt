project(ChessEngine LANGUAGES CXX)

# ------- Sources ------- #
file(GLOB_RECURSE MAIN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)
file(GLOB_RECURSE MAIN_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Includes/*.h)

# ------- CORE ------- #
set(CHESS_ENGINE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
add_library(ChessEngine STATIC ${MAIN_SOURCES} ${MAIN_HEADERS})
target_compile_options(ChessEngine PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(ChessEngine PUBLIC ${CHESS_ENGINE_INCLUDE_DIRS})
target_link_libraries(ChessEngine PRIVATE ${ChessEngine})