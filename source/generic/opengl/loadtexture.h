GLuint maketexturefromsurface(SDL_Surface *surface,bool mipmap){

	GLuint texture;
	SDL_Surface *optimized = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
	if(!optimized) return 0;

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, optimized->w, optimized->h, GL_RGBA, GL_UNSIGNED_BYTE, optimized->pixels);
	} else {
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,optimized->w,optimized->h,0,
			GL_RGBA,GL_UNSIGNED_BYTE,optimized->pixels);
	}
	
	SDL_FreeSurface(optimized);
	return texture;
}

GLuint loadtexture(char* filename,bool mipmap){

	GLuint texture = 0;
	SDL_Surface *surface;
	
	if((surface = IMG_Load(filename))){ 
		printf("Loaded texture: %s (%dx%d)\n", filename, surface->w, surface->h);
		
		SDL_Surface *optimized = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
		if(optimized) {
			glGenTextures( 1, &texture );
			glBindTexture( GL_TEXTURE_2D, texture );
			
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			
			if(mipmap) {
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, optimized->w, optimized->h, GL_RGBA, GL_UNSIGNED_BYTE, optimized->pixels);
			} else {
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,optimized->w,optimized->h,0,
					GL_RGBA,GL_UNSIGNED_BYTE,optimized->pixels);
			}
			
			SDL_FreeSurface(optimized);
		}
	} else {
		printf("Failed to load texture: %s. SDL_image Error: %s\n", filename, IMG_GetError());
	}
	
	if(surface)SDL_FreeSurface(surface);
	return texture;

}
