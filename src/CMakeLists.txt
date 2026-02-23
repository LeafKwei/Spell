set(COMMON_SRC
    io/mem/MemIO.cpp
    io/mem/Memory.cpp
    io/reg/RegIO.cpp
    io/dev/DeviceBus.cpp
    io/dev/term/TermDevice.cpp
    io/dev/term/TermDeviceIO.cpp
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