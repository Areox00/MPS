#pragma once

#include "tool.hpp"
#include "scenes/editor/gui/valuebox.hpp"

class Eraser : public Tool{
    bool down=false;
    int x,y,prevX,prevY;
    void draw();

	GuiValueBox box;

public:
    void init();
    void eventMouseMove(int x, int y);
    void eventMouseDown();
    void eventMouseUp();
    bool pushEvent(SDL_Event * evt);
    void update();
    void render(float alpha);
    void select();
};
