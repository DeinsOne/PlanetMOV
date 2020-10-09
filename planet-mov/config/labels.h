#ifndef _PLANET_MOV_LABLES_H
#define _PLANET_MOV_LABLES_H


#include <vector>


enum _Labels_ {
    Labels_ID = 0,
    Labels_Radius,
    Labels_Color,

    Labels_Pos,

    Labels_Script,
    Labels_VShader,
    Labels_FShader

};

static std::vector<std::pair<const char*, const char*> > Labels = std::initializer_list<std::pair<const char*, const char*> > {
    { "label", "id" },                              // _Labels_ID

    { "radius", "" },                               // _Labels_Radius

    { "_Labels_Color", "" },                        // _Labels_Color

    { "position", "pos" },                          // _Labels_Pos

    { "scriptExecutable", "script" },               // _Labels_Script

    { "scriptVertexShader", "vShader" },            // _Labels_VShader

    { "scriptFragmentShader", "fShader" }           // _Labels_FShader

};



#endif // _PLANET_MOV_LABLES_H


