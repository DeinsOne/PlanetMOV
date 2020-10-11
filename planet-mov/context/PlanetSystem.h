#ifndef _PLANET_MOV_PLANET_SYSTEM_H
#define _PLANET_MOV_PLANET_SYSTEM_H

#include <string>
#include <cinder/gl/GlslProg.h>



class Planet {
    public :
        glm::vec2               _pos;
        float                   _size;

        Planet(glm::vec2 pos, float size);

        std::string             _pathToFragmentShader;
        std::string             _fragmentShaderText;
        ci::gl::GlslProgRef     _shader;

        void BindShader(float elapsedTime, float deltaTime );


};



#endif // _PLANET_MOV_PLANET_SYSTEM_H