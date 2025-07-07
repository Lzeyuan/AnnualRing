add_rules("mode.debug", "mode.release")
set_project("LuaBindCppTestXMake")
set_version("1.0.0")

set_languages("c++17")

set_installdir("bin")

includes("3rd/**/xmake.lua")

target("LuaBindCppTestXMake")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("lua");
    add_installfiles("(service/*.lua)", {prefixdir = "bin"})

    after_build(function (target)
      print("before_build")
      print("copying resource " .." to " .. target:targetdir())
      os.cp("$(projectdir)/service/*.lua", target:targetdir())
    end)