add_library(nnct-lib STATIC)

target_sources(nnct-lib PRIVATE
    src/nnct/components/watchdog.cpp
    src/nnct/mocks/can_sender.cpp
)

target_include_directories(nnct-lib PUBLIC
    include/
)
