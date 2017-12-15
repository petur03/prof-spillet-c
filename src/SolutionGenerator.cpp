
#include <iostream>
#include <Magick++.h>
#include "piece.h"
#include "SolutionGenerator.h"

using namespace std;
using namespace Magick;


SolutionGenerator::SolutionGenerator() {

    InitializeMagick(nullptr);
    initPieces(pieces);

    loadImages();
    checkSizes();

    genImgPieces();
}

void SolutionGenerator::genImgPieces() {

    Geometry size = Geometry(images[0][0].size().width(), images[0][0].size().height() * 2);
    Image background(size, "white");

    cout << "size: " << size.width() << "x" << size.height() << endl;



    for (int i = 0; i < 16; i++) {
        Piece *current = &pieces[i];

        imgPieces[i].size(size);
        imgPieces[i].composite(background, 0, 0, CompositeOperator::OverCompositeOp);
        imgPieces[i].composite(images[current->down().part][current->down().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
        imgPieces[i].rotate(90.0);
        imgPieces[i].composite(images[current->right().part][current->right().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
        imgPieces[i].rotate(90.0);
        imgPieces[i].composite(images[current->up().part][current->up().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
        imgPieces[i].rotate(90.0);
        imgPieces[i].composite(images[current->left().part][current->left().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
        imgPieces[i].rotate(90.0);
        imgPieces[i].scale(Geometry(outSize, outSize));

        //imgPieces[i].write(resourceDir + "png-target" + kPathSeparator + std::to_string(i) + ".png");
    }


}

void SolutionGenerator::genSolution(Configuration *solution, int num) {

    Geometry size = Geometry(outSize*4, outSize*4);
    Image target(size, "white");


    for (int i = 0; i < 16; i++) {
        //cout << "Piece: " << solution[i].piece << " rotation: " << solution[i].rotation << endl;
        imgPieces[solution[i].piece].rotate(solution[i].rotation*-90);
        target.composite(imgPieces[solution[i].piece], (i%4)*outSize, ((i/4)%4)*outSize, CompositeOperator::OverCompositeOp);
        imgPieces[solution[i].piece].rotate(((4-solution[i].rotation)%4)*-90);
    }

    target.border(Geometry(2,2));
    target.borderColor("black");
    target.write(resourceDir + "png-target" + kPathSeparator + "solution-" + std::to_string(num) + ".png");




}

void SolutionGenerator::checkSizes() {
    size_t width = 0;
    size_t height = 0;
    for (int part = 0; part < NUM_PARTS; part++) {
        for (int color = 0; color < NUM_COLORS; color++) {
            Geometry s = images[part][color].size();
            if (width == 0) {
                height = s.height();
                width = s.width();
                /*
				if (width != height) {
                    cout << "width: " << width << " height: " << height << endl;
					throw exception(); // "Image is not square!"
				}
                 */
            }
            else if (height != s.height() || width != s.width()) {
                printf("Image sizes differ! Part: %s Color: %s\n", to_string(part).c_str(), colors[color].c_str());
                throw exception(); //("Image sizes differ! Part: " + to_string(part) + " Color: " + colors[color]).c_str());
            }

        }
    }
}

void SolutionGenerator::loadImages() {
    for (int part = 0; part < NUM_PARTS; part++) {
        for (int color = 0; color < NUM_COLORS; color++) {
            //printf("loading: %d, %d\n", part, color);
            //printf("%s\n", (resourceDir + "png-source" + kPathSeparator + "person-" + colors[color] +".png").c_str());
            images[part][color].read(resourceDir + "png-source" + kPathSeparator + "person-" + colors[color] +".png");

            if (part == Pants) {
                images[part][color].rotate(180.0);
            }

            Geometry s = images[part][color].size();
            images[part][color].crop(Geometry(s.width(), s.height() / 2, 0, 0));


            //images[part][color].write(resourceDir + "png-target" + kPathSeparator + std::to_string(part) + "-" + colors[color] + ".png");
        }
    }
}
