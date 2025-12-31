SDL_Surface *screen;
SDL_Window *window = NULL;
SDL_GLContext context;

void initopengl(){
	// Initialize SDL Subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        printf("Error: SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
    
    // Set OpenGL Attributes
	if(antialiasing){
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Create the Window - Enable HighDPI for crisp sizing on Mac
    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
	if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow("Kinetica Game Engine", 
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              (int)screenw, (int)screenh, 
                              flags);
    if (!window) { 
        printf("Error: Failed to create window: %s\n", SDL_GetError());
        SDL_Quit(); exit(3); 
    }

    // Create the GL Context
    context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("Error: Failed to create GL context: %s\n", SDL_GetError());
        SDL_Quit(); exit(4);
    }
    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1);
    
    // Stabilize
    SDL_Delay(50);

    printf("OpenGL Initialized: %s\n", glGetString(GL_VERSION));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    
    // For HighDPI: 
    // glViewport needs PIXELS (drawable size)
    // Engine logic needs POINTS (window size) to match input/coordinates
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    screenw = (float)ww; 
    screenh = (float)wh;
    screena = screenw / screenh;

    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);
    
    // Create the "screen" surface for compatibility (using points size)
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
    #else
        rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
    #endif
    screen = SDL_CreateRGBSurface(0, (int)screenw, (int)screenh, 32, rmask, gmask, bmask, amask);

    // Setup projection and viewport
    glViewport(0, 0, (GLsizei)dw, (GLsizei)dh); // PIXELS
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(screenfov, screena, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClearDepth(1000.0);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    if(antialiasing) {
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    }
}

void initvideo(){
	screenfov = 45.0f;
	initopengl();
	
	if(screen) {
		screenw = (float)screen->w;
		screenh = (float)screen->h;
		screena = screenw / screenh;
		screenbpp = screen->format->BitsPerPixel;
	}
	
	SDL_ShowCursor(showcursor ? SDL_TRUE : SDL_FALSE);
}
