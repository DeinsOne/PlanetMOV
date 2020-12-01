#ifndef _PLANET_MOV_PLANET_H
#define _PLANET_MOV_PLANET_H

#include <string>

#include "LuaScript.h"
#include "Shader.h"

class Planet {
    public :
        glm::vec2               _pos;
        float                   _size;

        Shader                  _shader;
        LuaScript               _script;


        Planet(glm::vec2 pos, float size) : _pos(pos), _size(size) {
        }


        void printFields() { printf("pos = { %f, %f }  |  size = %f\n", _pos.x, _pos.y, _size ); }


        void onSetup();
        void onUpdate();

};


#endif // _PLANET_MOV_PLANET_H