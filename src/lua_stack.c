#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

void stackDump(lua_State *L) ;

int main() {
    lua_State *L = luaL_newstate();
    lua_pushboolean(L, 1);
    lua_pushinteger(L, 100);
    lua_pushnumber(L, 3.14);
    lua_pushstring(L, "hello world");
    lua_pushnil(L);
    stackDump(L);

    lua_close(L);

    return 0;
}
// cc -o lua_stack lua_stack.c -I/opt/homebrew/include/lua -L/opt/homebrew/lib -llua
void stackDump(lua_State *L) {
    int i;
    int top = lua_gettop(L);

    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);

        switch (t)
        {
        case LUA_TNIL:
            printf("nil");
            break;

        case LUA_TBOOLEAN:
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        
        case LUA_TSTRING:
            printf("%s", lua_tostring(L, i));
            break;
        default:
            printf("%s", lua_typename(L, t));
            break;
        }
        printf(" ");
    }
    printf("\n\n");
}