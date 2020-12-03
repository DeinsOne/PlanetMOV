#ifndef _PLANET_MOV_PLANET_H
#define _PLANET_MOV_PLANET_H

#include <string>

#include "LuaScript.h"
#include "Shader.h"

class Planet {
    public :
        glm::vec2               _pos;
        float                   _size;
        float                   _mass;

        Shader                  _shader;
        LuaScript               _script;


        Planet(glm::vec2 pos, float size) : _pos(pos), _size(size), _mass(1.0) {
        }


        void printFields() { printf("pos = { %f, %f }  |  size = %f  |  mass = %f\n", _pos.x, _pos.y, _size, _mass ); }


        void onSetup();
        void onUpdate();

};


#endif // _PLANET_MOV_PLANET_H