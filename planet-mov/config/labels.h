#ifndef _PLANET_MOV_LABLES_H
#define _PLANET_MOV_LABLES_H


#include <vector>


enum Labels_ {
    Labels_ID = 0,
    Labels_Radius,

    Labels_Pos,

    Labels_VShader,
    Labels_FShader,

    Labels_Script,

    Labels_OnSetup,
    Labels_OnUpdate

};

static std::vector<std::pair<const char*, const char*> > Labels = std::initializer_list<std::pair<const char*, const char*> > {
    // Tags
    { "label", "id" },                              // _Labels_ID

    { "radius", "size" },                           // _Labels_Radius

    { "position", "pos" },                          // _Labels_Pos

    // Files
    { "vertexShader", "vShader" },                  // _Labels_VShader

    { "fragmentShader", "fShader" },                // _Labels_FShader

    { "script", "luaScript" },                      // Labels_Script

    // Function names
    { "onSetup", "" },                              // Labels_OnSetup

    { "onUpdate", "" }                              // Labels_OnSetup


};



#endif // _PLANET_MOV_LABLES_H


