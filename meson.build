project('ABM', 'cpp',
  version : '0.1',
  default_options : ['warning_level=1', 'cpp_std=c++11'])

# Find dependencies
sdl2_dep = dependency('SDL2', fallback: ['sdl2', 'sdl2_dep'])
sdl2_image_dep = dependency('SDL2_image', fallback: ['sdl2_image', 'sdl2_image_dep'])
sdl2_mixer_dep = dependency('SDL2_mixer', fallback: ['sdl2_mixer', 'sdl2_mixer_dep'])

# On macOS, use the system OpenGL framework
if host_machine.system() == 'darwin'
  opengl_dep = dependency('appleframeworks', modules : ['OpenGL'])
  glu_dep = opengl_dep
else
  opengl_dep = dependency('gl')
  glu_dep = dependency('glu')
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
  dependencies : [sdl2_dep, sdl2_image_dep, sdl2_mixer_dep, opengl_dep, glu_dep],
  install : true)
