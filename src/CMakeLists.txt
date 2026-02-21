set(COMMON_SRC
    io/MemIO.cpp
    io/Memory.cpp
    io/RegIO.cpp
    mach/Machine.cpp
)

set(SPELL_SRC
    ${COMMON_SRC}
    main/spell.cpp
)

set(SPELL_DBG_SRC
    ${COMMON_SRC}
    main/spelldbg.cpp
)

include_directories(
    ../include
)

add_executable(spell
    ${SPELL_SRC}
)

add_executable(spelldbg
    ${SPELL_DBG_SRC}
)