#include "LuaScript.h"
#include "Logger.h"

/*
https://github.com/CaioIcy/UnLua
https://github.com/EliasD/unnamed_lua_binder
*/

LuaScript::LuaScript(const std::string& filename_) {
    /// @todo Log an error message for different lua error codes.
    this->level = 0;
    this->luaState = luaL_newstate();

    const int loadedFile = luaL_loadfile(this->luaState, filename_.c_str());
    const int calledFunction = lua_pcall(luaState, 0, 0, 0);

    if (loadedFile == LUA_OK && calledFunction == LUA_OK) {
        if(this->luaState != nullptr){
            luaL_openlibs(this->luaState);
        }
    }
    else{
        Log(DEBUG) << "Failed to load (" << filename_ << ")";
        this->luaState = nullptr;
    }

}

LuaScript::~LuaScript() {
    if(this->luaState != nullptr){
        lua_close(this->luaState);
    }
    this->level = 0;
}

std::vector<int> LuaScript::unlua_getIntVector(const std::string& name_) {
    std::vector<int> v;
    unlua_getToStack(name_);

    // If the array is not found
    if(lua_isnil(this->luaState, -1)) {
        return std::vector<int>();
    }

    lua_pushnil(this->luaState);
    while(lua_next(this->luaState, -2)) {
        v.push_back((int)lua_tonumber(this->luaState, -1));
        lua_pop(this->luaState, 1);
    }
    
    unlua_clean();
    return v;
}

std::vector<std::string> LuaScript::unlua_getTableKeys(const std::string& name_) {
    std::string code =
        "function getKeys(name_) "
        "s = \"\""
        "for k, v in pairs(_G[name_]) do "
        "    s = s..k..\",\" "
        "    end "
        "return s "
        "end"; // function for getting table keys

    luaL_loadstring(this->luaState, code.c_str()); // execute code
    lua_pcall(this->luaState, 0, 0, 0);
    lua_getglobal(this->luaState, "getKeys"); // get function
    lua_pushstring(this->luaState, name_.c_str());
    lua_pcall(this->luaState, 1 , 1, 0); // execute function

    const std::string test = lua_tostring(luaState, -1);
    std::vector<std::string> strings;
    std::string temp = "";

    Log(DEBUG) << "TEMP: " << test;

    for(unsigned int i = 0; i < test.size(); i++) {
        if(test.at(i) != ',') {
            temp += test.at(i);
        }
        else {
            strings.push_back(temp);
            temp= "";
        }
    }
    unlua_clean();
    return strings;
}

bool LuaScript::unlua_getToStack(const std::string& variableName_) {
    this->level = 0;
    std::string var = "";
    for(unsigned int i = 0; i < variableName_.size(); i++) {
        if(variableName_.at(i) == '.') {
            if(this->level == 0) {
                lua_getglobal(this->luaState, var.c_str());
            }
            else {
                lua_getfield(this->luaState, -1, var.c_str());
            }

            if(lua_isnil(this->luaState, -1)) {
                Log(ERROR) << "Can't get " << variableName_ << ". " << var << " is not defined.";
                return false;
            }
            else {
                var = "";
                this->level++;
            }
        } else {
            var += variableName_.at(i);
        }
    }

    if(level == 0) {
        lua_getglobal(this->luaState, var.c_str());
    }
    else {
        lua_getfield(this->luaState, -1, var.c_str());
    }

    if(lua_isnil(luaState, -1)) {
        Log(ERROR) << "Can't get " << variableName_ << ". " << var << " is not defined.";
        return false;
    }

    return true;
}

