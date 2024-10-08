add_languages("cxx20")

target("Test")
    set_kind("binary")
    add_files("src/main.cpp")
    add_headerfiles("include/TString.hpp")
    add_includedirs("include")
target_end()