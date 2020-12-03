#ifndef _PLANET_MOV_LUA_SHADER_H
#define _PLANET_MOV_LUA_SHADER_H

#include "cinder/gl/GlslProg.h"
#include "ScriptableEntt.h"

class Shader : public ScriptableEntt {
    public : // Functions
        Shader() { }
        Shader(std::string script) { load(script ); }

        ~Shader() { destroy(); }
        virtual void destroy() override;


        virtual Error load(std::string path ) override;

        virtual int bind() override;
        virtual Error check() override;


        void bindArgs(float elapsedTime, float deltaTime );

    public :
        ci::gl::GlslProgRef      _shader;

};


#endif // _PLANET_MOV_LUA_SHADER_H 
 
