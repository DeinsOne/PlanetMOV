#ifndef _PLANET_MOV_CONTROLLER_H
#define _PLANET_MOV_CONTROLLER_H 

#include "LuaScript.h"

class Controller {
    private :
        Controller() { }

        void _encodeArgs(luabridge::LuaRef* planets);

    public :
        static Controller& Get() { static Controller cl; return cl; }

        void onUpdate();

        LuaScript _script;

};


#endif // _PLANET_MOV_CONTROLLER_H 