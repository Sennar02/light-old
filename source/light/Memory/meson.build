light_memory = static_library('light-memory',
    include_directories: [light_header],
    sources: [
        'Origin/BaseOrigin.cpp',
        'Origin/KernOrigin.cpp',
        'Origin/PoolOrigin.cpp',
        # 'Origin/TreeOrigin.cpp',
        'Origin/ArenaOrigin.cpp',
        # 'Origin/StackOrigin.cpp',
        'Origin/EmptyOrigin.cpp',
        'Layout/FixedLayout.cpp',
        'util.cpp',
    ],
)

light_define = light_define + light_memory
