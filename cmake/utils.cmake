macro(set_strict_compiler_warnings TARGET)
    target_compile_options(${TARGET}
        PRIVATE
        $<$<C_COMPILER_ID:Clang>:-Wcast-align
                                 -Wcast-qual
                                 -Wconversion
                                 -Wexit-time-destructors
                                 -Wglobal-constructors
                                 -Wmissing-noreturn
                                 -Wmissing-prototypes
                                 -Wno-missing-braces
                                 -Wold-style-cast
                                 -Wshadow
                                 -Wweak-vtables
                                 -Wall
                                 -Wextra
                                 -Wpedantic
                                 -Wstack-exhausted
                                 -Wconversion
                                 #-Werror
                                 >
        $<$<C_COMPILER_ID:GNU>:-Waddress
                               -Waggregate-return
                               -Wformat-nonliteral
                               -Wformat-security
                               -Wformat
                               -Winit-self
                               -Wconversion
                               -Wmissing-include-dirs
                               -Wmultichar
                               -Wparentheses
                               -Wtype-limits
                               -Wunused-parameter
                               -Wunused-function
                               -Wunreachable-code
                               -Wwrite-strings
                               -Wpointer-arith
                               -Wall
                               -Wextra
                               -Wpedantic
                               -Wcast-qual
                               -Wconversion
                               -Wstringop-truncation
                               -Werror
                                >
        $<$<CXX_COMPILER_ID:MSVC>:W4>
        )

endmacro()

macro(disable_static_check TARGET)
set_target_properties(
        ${TARGET}
        PROPERTIES
        C_CLANG_TIDY "")
endmacro()