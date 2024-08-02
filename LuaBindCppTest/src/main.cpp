#include <cstdio>
#include <iostream>
#include <string>

extern "C" {
#include <lauxlib.h>
#include <limits.h> // for PATH_MAX
#include <lua.h>
#include <lualib.h>
#include <unistd.h> // for readlink
}

// cpp call lua
std::string getExecutablePath() {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  std::string executableDirectoryPath =
      std::string(result, (count > 0) ? count : 0);
  size_t lastSlashPos = executableDirectoryPath.find_last_of("/\\");
  if (lastSlashPos != std::string::npos) {
    return executableDirectoryPath.substr(0, lastSlashPos);
  }
  return executableDirectoryPath;
}

void CallLuaTest() {
  // 创建lua虚拟机环境
  lua_State *luaState;
  luaState = luaL_newstate();
  luaL_openlibs(luaState);

  // 加载lua文件
  std::string executablePath = getExecutablePath();
  printf("%s\n", executablePath.data());
  std::string fileName = executablePath + "/" + "CppCallLuaTest.lua";
  int isOk = luaL_dofile(luaState, fileName.data());
  if (isOk == 1) {
    printf("run lua fail %s\n", lua_tostring(luaState, -1));
  }

  // 执行lua脚本
  lua_getglobal(luaState, "OnInit");
  lua_pushinteger(luaState, 10086);
  lua_pushfstring(luaState, "hello lua");
  isOk = lua_pcall(luaState, 2, 0, 0);
  if (isOk == 1) {
    printf("run lua fail OnInit %s\n", lua_tostring(luaState, -1));
  }

  lua_getglobal(luaState, "OnExit");
  isOk = lua_pcall(luaState, 0, 0, 0);
  if (isOk == 1) {
    printf("run lua fail OnExit %s\n", lua_tostring(luaState, -1));
  }

  lua_getglobal(luaState, "TestTable");
  if (lua_istable(luaState, -1)) {
    // 获取TestTable.OnCall字段
    lua_getfield(luaState, -1, "OnCall");
    if (lua_isfunction(luaState, -1)) {
      // 调用OnCall函数（这里假设没有参数）
      lua_call(luaState, 0, 0);
    } else {
      std::cerr << "TestTable.OnCall is not a function" << std::endl;
    }
    lua_pop(luaState, 1); // 移除TestTable.OnCall
  } else {
    std::cerr << "TestTable is not a table" << std::endl;
  }

  lua_close(luaState);
}

// lua call cpp
int LuaCallCppTest() {
  // 创建lua虚拟机环境
  lua_State *luaState;
  luaState = luaL_newstate();
  luaL_openlibs(luaState);

  // 加载lua文件
  std::string executablePath = getExecutablePath();
  printf("%s\n", executablePath.data());
  std::string fileName = executablePath + "/" + "LuaCallCppTest.lua";
  int isOk = luaL_dofile(luaState, fileName.data());
  if (isOk == 1) {
    printf("run lua fail %s\n", lua_tostring(luaState, -1));
  }

  // 准备被调用函数
  auto cppFunction = [](lua_State *luaState) -> int {
    int num = lua_gettop(luaState);

    if (lua_isstring(luaState, 1) == 0) {
      lua_pushinteger(luaState, -1);
      return 1;
    }

    size_t len = 0;
    const char *type = lua_tolstring(luaState, 1, &len);
    printf("lua say: %s\n", type);
    lua_pushinteger(luaState, 10086);
    return 1;
  };

  // 注册函数
  static luaL_Reg lualibs[] = {{"CallCpp", cppFunction}, {NULL, NULL}};
  luaL_newlib(luaState, lualibs);
  lua_setglobal(luaState, "cppTest");

  // 执行lua脚本
  lua_getglobal(luaState, "CallCpp");
  isOk = lua_pcall(luaState, 0, 0, 0);
  if (isOk == 1) {
    printf("run lua fail OnExit %s\n", lua_tostring(luaState, -1));
  }

  lua_close(luaState);
  return 1;
}

int main() {
  printf("hello world!\n");
  CallLuaTest();
  LuaCallCppTest();
  return 0;
}