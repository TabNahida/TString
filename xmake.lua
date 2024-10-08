add_languages("cxx20")

target("tstring")
    set_kind("static")
    add_headerfiles("include/TString.hpp")
    add_includedirs("include")
target_end()

target("Test")
    set_kind("binary")
    add_files("src/main.cpp")
    add_deps("tstring")
    add_includedirs("include")
target_end()