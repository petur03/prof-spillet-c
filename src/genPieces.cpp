
#include <iostream> 
#include <string>
#include <Magick++.h>
#include "piece.h"

using namespace std;
using namespace Magick;

void loadImages(Image images[NUM_PARTS][NUM_COLORS]);
void checkSizes(Image images[NUM_PARTS][NUM_COLORS]);

string colors[4] = { "blue", "purple", "brown", "green" };

int main(int argc, const char *argv[]) {

	InitializeMagick(*argv);
	Piece pieces[16];
	initPieces(pieces);
	size_t outSize = 200;

	Image images[NUM_PARTS][NUM_COLORS];

	loadImages(images);
	checkSizes(images);

	Geometry size = Geometry(images[0][0].size().width(), images[0][0].size().height() * 2);
	Image background(size, "white");

	cout << "size: " << size.width() << "x" << size.height() << endl;


	
	for (int i = 0; i < 16; i++) {
		Piece *current = &pieces[i];

		Image target(background);
		target.composite(images[current->down().part][current->down().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
		target.rotate(90.0);
		target.composite(images[current->right().part][current->right().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
		target.rotate(90.0);
		target.composite(images[current->up().part][current->up().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
		target.rotate(90.0);
		target.composite(images[current->left().part][current->left().color], 0, size.height() / 2, CompositeOperator::OverCompositeOp);
		target.rotate(90.0);
		target.scale(Geometry(outSize, outSize));

		target.write("C:\\stuff\\games\\prof-spillet-c\\resources\\png-target\\" + std::to_string(i) + ".png");
	}

	cout << "Done" << endl;
	cin.get();
	return 0;
}

void checkSizes(Image images[NUM_PARTS][NUM_COLORS]) {
	size_t width = 0;
	size_t height = 0;
	for (int part = 0; part < NUM_PARTS; part++) {
		for (int color = 0; color < NUM_COLORS; color++) {
			Geometry s = images[part][color].size();
			if (width == 0) {
				height = s.height();
				width = s.width();
				if (width != height) {
					throw new exception("Image is not square!");
				}
			}
			else if (height != s.height() || width != s.width()) {
				throw new exception(("Image sizes differ! Part: " + to_string(part) + " Color: " + colors[color]).c_str());
			}

		}
	}
}

void loadImages(Image images[NUM_PARTS][NUM_COLORS]) {
	for (int part = 0; part < NUM_PARTS; part++) {
		for (int color = 0; color < NUM_COLORS; color++) {
			images[part][color].read("C:\\stuff\\games\\prof-spillet-c\\resources\\png-source\\person-" + colors[color] +".png");

			if (part == Pants) {
				images[part][color].rotate(180.0);
			}

			Geometry s = images[part][color].size();
			images[part][color].crop(Geometry(s.width, s.height / 2, 0, 0));


			images[part][color].write("C:\\stuff\\games\\prof-spillet-c\\resources\\png-target\\" + std::to_string(part) + "-" + colors[color] + ".png");
		}
	}
}
