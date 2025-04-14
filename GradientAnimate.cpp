/*
AUTHOR: DEXTER KONG 4/14/25
this is an inclass programming assigment regarding the use of the
empirical library and continuous cell automata.
*/
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"
#include <algorithm> // for std::clamp

emp::web::Document doc{"target"};

const int width = 50;
const int height = 50;
const int cubewidth = 10;
const int cubeheight = 10;
std::vector<std::vector<float>> cells;
emp::Random rng(1);

class GradientAnimator : public emp::web::Animate {
    emp::web::Canvas canvas{width * cubewidth, height * cubeheight, "canvas"};
public:
    GradientAnimator() {
        //add all necessary elements to the doc
        cells.resize(width, std::vector<float>(height, 0.5));
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        doc << canvas;
    }

    void DoFrame() override {
        //clear canvas at first
        canvas.Clear();
        //loop over every cell and for each one...
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                //find a random change for it's color value and modify it
                cells[x][y] += rng.GetRandNormal(0, 0.02);
                cells[x][y] = std::clamp(cells[x][y], 0.0f, 1.0f); // Clamp between 0 and 1
                //draw the rectangle, where its location is based on its index
                canvas.Rect(
                    cubewidth * x, cubeheight * y,
                    cubewidth, cubeheight,
                    //define the color based on the float stored in the list
                    emp::ColorHSV(240 * (1.0 - cells[x][y]), 1.0, 1.0),
                    "black"
                );            }
        }
    }
};

GradientAnimator animator;

int main() {
    animator.Step();  // Use animator.Start(); for continuous animation
}