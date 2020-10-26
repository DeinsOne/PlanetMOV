#ifndef _PLANET_MOV_LABLES_H
#define _PLANET_MOV_LABLES_H


#include <vector>


enum Labels_ {
    Labels_ID = 0,
    Labels_Radius,

    Labels_Pos,

    Labels_VShader,
    Labels_FShader,

    Labels_Script

};

static std::vector<std::pair<const char*, const char*> > Labels = std::initializer_list<std::pair<const char*, const char*> > {
    { "label", "id" },                              // _Labels_ID

    { "radius", "size" },                           // _Labels_Radius

    { "position", "pos" },                          // _Labels_Pos

    { "vertexShader", "vShader" },                  // _Labels_VShader

    { "fragmentShader", "fShader" },                 // _Labels_FShader

    { "script", "luaScript" }

};



#endif // _PLANET_MOV_LABLES_H


