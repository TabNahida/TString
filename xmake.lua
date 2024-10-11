add_rules("plugin.compile_commands.autoupdate", {outputdir = "./"})

add_languages("cxx20")

target("tstring")
    set_kind("headeronly")
    add_headerfiles("include/TString.hpp")
target_end()

target("MainTest")
    set_kind("binary")
    add_files("src/main.cpp")
    add_deps("tstring")
    add_includedirs("include")
target_end()

target("BenchMark")
    set_kind("binary")
    add_files("src/benchmark.cpp")
    add_deps("tstring")
    add_includedirs("include")
target_end()