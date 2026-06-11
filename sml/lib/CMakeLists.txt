
add_library(SMLlib
        INTERFACE
        Instructions.h
        Interpreter.h
        Method.h
        # this states that this is header-only library (no preprocessed/compiled files)
)

target_include_directories(SMLlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})