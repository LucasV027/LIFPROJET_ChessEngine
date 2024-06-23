project(ChessApp LANGUAGES CXX)


file(GLOB_RECURSE SOURCES "Sources/*.cpp")
file(GLOB_RECURSE HEADERS "Sources/*.h")

add_executable(ChessApp ${HEADERS} ${SOURCES})

add_subdirectory(Vendor/SDL)
add_subdirectory(Vendor/SDL_image)

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/Assets)
add_definitions(-DASSETS_PATH="${ASSETS_DIR}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Bin)
target_link_libraries(ChessApp PRIVATE ChessEngine SDL3_image::SDL3_image SDL3::SDL3)