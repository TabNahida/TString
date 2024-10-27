add_languages("cxx20")

option("tcstring")
    set_default(true)
    set_showmenu(true)
    set_description("Enable TCString Support")
option_end()

if has_config("tcstring") then
    add_requires("tcstring")
end

target("tstring")
    set_kind("headeronly")
    set_options("tcstring")

    add_headerfiles("include/TString.hpp")

    if has_config("tcstring") then
        add_packages("tcstring")
    end
target_end()

target("MainTest")
    set_kind("binary")
    set_options("tcstring")

    add_files("src/main.cpp")
    add_includedirs("include")

    add_deps("tstring")
    if has_config("tcstring") then
        add_packages("tcstring")
    end
target_end()

target("BenchMark")
    set_kind("binary")
    set_options("tcstring")

    add_files("src/benchmark.cpp")
    add_includedirs("include")

    add_deps("tstring")
    if has_config("tcstring") then
        add_packages("tcstring")
    end
target_end()
