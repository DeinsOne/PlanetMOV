#ifndef _PLANET_MOV_SCRIPTABLE_ENTT_H
#define _PLANET_MOV_SCRIPTABLE_ENTT_H

#include <string>
#include <fstream>

#include "Error.h"


class ScriptableEntt {
    public :
        std::string _pathSEntt;
        std::string _textSEntt;

        virtual Error reload() { return load(_pathSEntt ); }
        virtual void destroy() { }


        // Should be overide
        virtual int bind() = 0;
        virtual Error check() = 0;

        virtual Error load(std::string path ) = 0;

};


#endif // _PLANET_MOV_SCRIPTABLE_ENTT_H
