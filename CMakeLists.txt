add_library(nnct-lib STATIC)

target_sources(nnct-lib PRIVATE
    src/nnct/watchdog.cpp
)

target_include_directories(nnct-lib PUBLIC
    include/
)
