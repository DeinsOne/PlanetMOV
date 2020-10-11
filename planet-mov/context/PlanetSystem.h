#ifndef _PLANET_MOV_PLANET_SYSTEM_H
#define _PLANET_MOV_PLANET_SYSTEM_H

#include <string>
#include <cinder/gl/GlslProg.h>

// const std::string _PLANET_MOV_VERTEX_SHADER_DEF = "";


class Planet {
    public :
        glm::vec2               _pos;
        float                   _size;

        Planet(glm::vec2 pos, float size) { _pos = pos; _size = size; }

        std::string             _pathToFragmentShader;
        std::string             _fragmentShaderText;
        ci::gl::GlslProgRef     _shader;
};



#endif // _PLANET_MOV_PLANET_SYSTEM_H