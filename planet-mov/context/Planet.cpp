#include "Planet.h"


void Planet::_transferArgs(Planet* p, Json::Value& value) {
    p->_args = value;
}

luabridge::LuaRef Planet::_bindTable(Planet* p, lua_State* L ) {
    luabridge::LuaRef _args = luabridge::newTable(L );

    for (auto c : p->_args.getMemberNames()) {
        if (p->_args[c.c_str()].isBool())
            _args[c.c_str()] = p->_args[c.c_str()].asBool();
        else if (p->_args[c.c_str()].isInt())
            _args[c.c_str()] = p->_args[c.c_str()].asInt();
        else if (p->_args[c.c_str()].isDouble())
            _args[c.c_str()] = p->_args[c.c_str()].asFloat();
        else if (p->_args[c.c_str()].isString())
            _args[c.c_str()] = p->_args[c.c_str()].asCString();

        else if (p->_args[c.c_str()].isArray()) {
            if (p->_args[c.c_str()].size() <= 2) {
                _args[c.c_str()] = glm::vec2(p->_args[c.c_str()][0].asFloat(), p->_args[c.c_str()][1].asFloat());
            }
            else {
                _args[c.c_str()] = _args.newTable(L);
                if (p->_args[c.c_str()][0].isInt()) {
                    for (int k = 0; k < p->_args[c.c_str()].size(); k++ )
                        _args[c.c_str()][k] = p->_args[c.c_str()][k].asInt();
                }
                else if (p->_args[c.c_str()][0].isDouble()) {
                    for (int k = 0; k < p->_args[c.c_str()].size(); k++ )
                        _args[c.c_str()][k] = p->_args[c.c_str()][k].asFloat();
                }
                else if (p->_args[c.c_str()][0].isBool()) {
                    for (int k = 0; k < p->_args[c.c_str()].size(); k++ )
                        _args[c.c_str()][k] = p->_args[c.c_str()][k].asBool();
                }
                else if (p->_args[c.c_str()][0].isString()) {
                    for (int k = 0; k < p->_args[c.c_str()].size(); k++ )
                        _args[c.c_str()][k] = p->_args[c.c_str()][k].asCString();
                }
            }
        }
    }

    return _args;
}

void Planet::_encodeArgs(Planet* p, luabridge::LuaRef table) {
    table.push(p->_script._luaState);
    luabridge::push(p->_script._luaState, luabridge::Nil());

    while (lua_next(p->_script._luaState, -2)) {
        luabridge::LuaRef key = luabridge::LuaRef::fromStack(p->_script._luaState, -2);
        luabridge::LuaRef val = luabridge::LuaRef::fromStack(p->_script._luaState, -1);
        
        if (val.isBool())
            p->_args[key.tostring().c_str()] = val.cast<bool>();
        else if (val.isNumber())
            p->_args[key.tostring().c_str()] = val.cast<float>();
        else if (val.isString())
            p->_args[key.tostring().c_str()] = val.cast<const char*>();
        else if (val.isInstance<glm::vec2>()) {
            glm::vec2 vector = val.cast<glm::vec2>();
            p->_args[key.tostring().c_str()][0] = vector.x;
            p->_args[key.tostring().c_str()][1] = vector.y;
        }
        else if (val.length() > 0 ) {
            val.push(p->_script._luaState);
            luabridge::push(p->_script._luaState, luabridge::Nil());

            while (lua_next(p->_script._luaState, -2)) {
                luabridge::LuaRef key1 = luabridge::LuaRef::fromStack(p->_script._luaState, -2);
                luabridge::LuaRef val1 = luabridge::LuaRef::fromStack(p->_script._luaState, -1);

                if (val1[key1.cast<int>()].isBool()) {
                    for (int i = 0; i < val1.length(); i++ )
                        p->_args[key1.cast<int>()][i] = val1[key1.cast<int>()].cast<bool>();
                }
                else if (val1[key1.cast<int>()].isNumber()) {
                    for (int i = 0; i < val1.length(); i++ )
                        p->_args[key1.cast<int>()][i] = val1[key1.cast<int>()].cast<float>();
                }
                else if (val1[key1.cast<int>()].isString()) {
                    for (int i = 0; i < val1.length(); i++ )
                        p->_args[key1.cast<int>()][i] = val1[key1.cast<int>()].cast<const char*>();
                }
                else if (val1[key1.cast<int>()].isInstance<glm::vec2>()) {
                    p->_args[key1.cast<int>()][0] = val1[key1.cast<int>()]["x"].cast<float>();
                    p->_args[key1.cast<int>()][0] = val1[key1.cast<int>()]["y"].cast<float>();
                }

                lua_pop(p->_script._luaState, 1);
            }
        }

        lua_pop(p->_script._luaState, 1);
    }
}