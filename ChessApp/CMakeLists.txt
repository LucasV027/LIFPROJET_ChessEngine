project(ChessApp LANGUAGES CXX)


file(GLOB_RECURSE SOURCES "Sources/*.cpp")
file(GLOB_RECURSE HEADERS "Sources/*.h")

add_executable(ChessApp ${HEADERS} ${SOURCES})

include(FetchContent)

message(STATUS "Fetching SDL2")
FetchContent_Declare(
    sdl2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.30.4
)
FetchContent_MakeAvailable(sdl2)

message(STATUS "Fetching SDL2_image")
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.8.2
)
FetchContent_MakeAvailable(SDL2_image)


target_link_libraries(ChessApp PRIVATE ChessEngine SDL2::SDL2 SDL2::SDL2main SDL2_image)