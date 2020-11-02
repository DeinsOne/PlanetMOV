#include "Shader.h"
#include "cinder/Log.h"

void Shader::destroy() {
    _pathSEntt.clear();
    _textSEntt.clear();

    _shader.reset();
}


int Shader::bind() {
    if (_shader )
        _shader->bind();
}

void Shader::bindArgs(float elapsedTime, float deltaTime ) {
    if (_shader ) {
        _shader->uniform("elapsedTime", elapsedTime);
        _shader->uniform("deltaTime", deltaTime);
    }
}

Error Shader::load(std::string path ) {
    _pathSEntt = path;

    try {
        _shader = ci::gl::GlslProg::create(
            ci::loadFile("assets/shaders/default.vs.glsl" ),
            ci::loadFile(_pathSEntt )
        );

        std::ifstream ifs(_pathSEntt );
        _textSEntt = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        ifs.close();
    } catch (std::exception& e ) {
        CI_LOG_EXCEPTION("", e);

        return Error(ErrorType::Error_Shader, "Shader", e.what() );
    }

    return Error(ErrorType::Error_None, "", "" );
}



int Shader::check() {
    return 0;
}
