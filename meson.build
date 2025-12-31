project('ABM', 'cpp',
  version : '0.1',
  default_options : ['warning_level=1', 'cpp_std=c++11'])

# Find dependencies
sdl2_dep = dependency('sdl2')
sdl2_image_dep = dependency('SDL2_image')
sdl2_mixer_dep = dependency('SDL2_mixer')

# On macOS, use the system OpenGL framework
if host_machine.system() == 'darwin'
  opengl_dep = dependency('appleframeworks', modules : ['OpenGL'])
else
  opengl_dep = dependency('gl')
endif

# Source files
sources = [
  'source/main.cpp'
]

# Include directories - add both source and source/generic
inc = include_directories('source', 'source/generic')

# Executable
executable('ABM',
  sources,
  include_directories : inc,
  dependencies : [sdl2_dep, sdl2_image_dep, sdl2_mixer_dep, opengl_dep],
  install : true)
