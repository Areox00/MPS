#include "pipette.h"

#include "../../drawer.h"
#include "../../framemanager.h"
#include "../../colorselector/colorselector.h"
#include "../toolbox.h"

#include "transform.h"
#include "lib/glm.h"
#include <stack>

void Pipette::init(){
    iconName = "pipette";
}

void Pipette::eventMouseMove(int x, int y){
    this->x=x;
    this->y=y;
}

void Pipette::eventMouseDown(){
    int pixel = drawer->getPoint(x, y);
    Uint8 r,g,b;
    SDL_GetRGB(pixel, frameMan->getCurrentFrame()->getOverlay()->format, &r,&g,&b);
    colorselector->setColor(r,g,b);
    toolbox->setCurrentTool(toolbox->getPreviousTool());
}

void Pipette::eventMouseUp(){

}

bool Pipette::pushEvent(SDL_Event * evt){
    bool used=false;

    switch(evt->type){
        case SDL_MOUSEMOTION:{
            mouseX=evt->motion.x;
            mouseY=evt->motion.y;
            isMoved=true;
            break;
        }
    }

    return used;
}
void Pipette::update(){
    if(isMoved){
        opacity+=0.05;
        if(opacity>1.0){
            opacity=1.0;
        }
        scaleMul*=0.7;
    }
}
void Pipette::render(){
    if(isMoved){
        pixel_prev=pixel;
        pixel = drawer->getPoint(x, y);
        Uint8 r,g,b;
        SDL_GetRGB(pixel, frameMan->getCurrentFrame()->getOverlay()->format, &r,&g,&b);
        if(pixel_prev!=pixel){
            scaleMul=0.5;
        }

        glm::mat4 model;
/*
        glBindBuffer(GL_ARRAY_BUFFER, scene->a.square_vert);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, scene->a.square_uv);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

        float scale = 1.0+scaleMul;

        xReset(&model);
        xTranslate(&model, mouseX-34*scale/2,mouseY-34*scale/2-25);
        xScale(&model, 34*scale, 34*scale);
        scene->shGuiColor.select().setM(&model).setUniform("COLOR",0.0,0.0,0.0,opacity);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        xReset(&model);
        xTranslate(&model, mouseX-32*scale/2,mouseY-32*scale/2-25);
        xScale(&model, 32*scale, 32*scale);
        scene->shGuiColor.select().setM(&model).setUniform("COLOR",r/255.0,g/255.0,b/255.0,opacity);

        glDrawArrays(GL_TRIANGLES, 0, 6);*/
    }
}
void Pipette::select(){
    toolbox->setSettingsHeight(0);
    isMoved=false;
    opacity=0.0;
    scaleMul=0.0;
}