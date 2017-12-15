#pragma once

#include <Magick++.h>
#include "board.h"

using namespace std;
using namespace Magick;

class SolutionGenerator {
private:

    Piece pieces[16];
    Image imgPieces[16];

    size_t outSize = 200;
    Image images[NUM_PARTS][NUM_COLORS];

    const char kPathSeparator =
    #ifdef _WIN32
            '\\';
    #else
            '/';
    #endif

    string colors[4] = { "blue", "purple", "brown", "green" };

    //string resourceDir = "C:\\stuff\\games\\prof-spillet-c\\resources\\";
    //string resourceDir = "../resources/";
    string resourceDir = "/home/petur/stuff/games/prof-spillet-c/resources/";
    void loadImages();
    void checkSizes();
    void genImgPieces();

public:
    SolutionGenerator();
    void genSolution(Configuration *solution, int num);
};
