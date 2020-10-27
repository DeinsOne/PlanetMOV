#ifndef _PLANET_MOV_PLANET_H
#define _PLANET_MOV_PLANET_H

#include <string>
#include <cinder/gl/GlslProg.h>

#include "LuaScript.h"

class Planet {
    public :
        glm::vec2               _pos;
        float                   _size;

        Planet(glm::vec2 pos, float size);

        std::string             _pathToFragmentShader;
        std::string             _fragmentShaderText;
        ci::gl::GlslProgRef     _shader;

        LuaScript               _script;


        void BindShader(float elapsedTime, float deltaTime );
        void printFields() { printf("pos = { %f, %f }  |  size = %f\n", _pos.x, _pos.y, _size ); }


        int bindCoreVariables();

        int callOnSetup();
        int callOnUpdate();
        int callOnRender();
        

};


#endif // _PLANET_MOV_PLANET_H