project('ABM', 'cpp',
  default_options : ['cpp_std=c++11'])

cpp = meson.get_compiler('cpp')

sdl2 = dependency('sdl2')
sdl2_image = dependency('SDL2_image')
sdl2_mixer = dependency('SDL2_mixer')

if host_machine.system() == 'darwin'
  # On macOS, GL and GLU are part of the OpenGL framework
  gl = dependency('appleframeworks', modules : ['OpenGL'])
  glu = gl # Use the same dependency to avoid linking Mesa
else
  gl = dependency('gl')
  glu = dependency('glu')
endif

inc = include_directories('source', 'source/generic', 'source/projectspecific')

executable('ABM', 'source/main.cpp',
  dependencies : [sdl2, sdl2_image, sdl2_mixer, gl, glu],
  include_directories : inc)
