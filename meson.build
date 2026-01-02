project('ABM', 'cpp',
  version : '0.1',
  default_options : ['warning_level=1', 'cpp_std=c++11', 'default_library=static'])

# Find dependencies
sdl2_dep = dependency('SDL2', fallback: ['sdl2', 'sdl2_dep'])
sdl2_image_dep = dependency('SDL2_image', fallback: ['sdl2_image', 'sdl2_image_dep'])
sdl2_mixer_dep = dependency('SDL2_mixer', fallback: ['sdl2_mixer', 'sdl2_mixer_dep'])

# On Windows, also need SDL2main for WinMain entry point
if host_machine.system() == 'windows'
  sdl2main_dep = dependency('SDL2main', fallback: ['sdl2', 'sdl2main_dep'])
else
  sdl2main_dep = dependency('', required: false)
endif

# On macOS, use the system OpenGL framework
if host_machine.system() == 'darwin'
  opengl_dep = dependency('appleframeworks', modules : ['OpenGL'])
  glu_dep = opengl_dep
elif host_machine.system() == 'windows'
  # On Windows, use OpenGL from Windows SDK
  opengl_dep = dependency('gl')
  glu_dep = dependency('glu', required: false)
  if not glu_dep.found()
    # GLU is typically included with OpenGL on Windows
    cc = meson.get_compiler('cpp')
    glu_dep = cc.find_library('glu32', required: false)
    if not glu_dep.found()
      # Fallback to OpenGL if GLU is not found separately
      glu_dep = opengl_dep
    endif
  endif
else
  opengl_dep = dependency('gl')
  glu_dep = dependency('glu')
endif

# Source files
sources = [
  'source/main.cpp'
]

# Include directories - add source/generic only
# Note: 'source' directory is not included because it contains outdated SDL headers
# The SDL2 headers from the subproject will be used instead
inc = include_directories('source/generic')

# Executable
all_deps = [sdl2_dep, sdl2_image_dep, sdl2_mixer_dep, opengl_dep, glu_dep]
if host_machine.system() == 'windows'
  all_deps += sdl2main_dep
endif

executable('ABM',
  sources,
  include_directories : inc,
  dependencies : all_deps,
  install : true)
