
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(prof prof.cpp piece.cpp board.cpp ../include/SolutionGenerator.h SolutionGenerator.cpp)


find_program(MAGICK_CONFIG "Magick++-config")
execute_process(COMMAND "${MAGICK_CONFIG}" "--cxxflags" OUTPUT_VARIABLE MAGICK_CXX_FLAGS)
execute_process(COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS)

string(STRIP "${MAGICK_CXX_FLAGS}" MAGICK_CXX_FLAGS)
string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAGICK_CXX_FLAGS} ${MAGICK_LD_FLAGS}")

add_executable(genPieces genPieces.cpp piece.cpp)
TARGET_LINK_LIBRARIES(genPieces Magick++)
TARGET_LINK_LIBRARIES(prof Magick++)

