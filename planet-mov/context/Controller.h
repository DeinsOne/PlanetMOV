#ifndef _PLANET_MOV_CONTROLLER_H
#define _PLANET_MOV_CONTROLLER_H 

#include "LuaScript.h"

class Controller {
    private :
        Controller() { }

    public :
        static Controller& Get() { static Controller cl; return cl; }

        LuaScript       _script;


    public :
        void check();
        bool empty();

        void onUpdate();

};


#endif // _PLANET_MOV_CONTROLLER_H 
