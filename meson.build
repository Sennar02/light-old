project('light', 'cpp',
    default_options: [
        'cpp_std=c++17',
        'warning_level=3',
        'werror=true',
    ],
    version: '0.1.0',
    license: 'MIT',
)

light_header = include_directories('header')
light_depend = []
light_define = []

subdir('source/light/Base')
subdir('source/light/Memory')
subdir('source/light/Algo')

executable('light-main',
    sources: [
        'source/light-main.cpp',
    ],
    include_directories: [light_header],
    dependencies:        [light_depend,
        dependency('sfml-graphics'),
    ],
    link_with:           [light_define],
    link_args:           ['-lm'],
)

executable('light-test',
    sources: [
        'source/light-test.cpp',
    ],
    include_directories: [light_header],
    dependencies:        [light_depend,
        dependency('cpputest'),
    ],
    link_with:           [light_define],
    link_args:           ['-lm'],
)
