void clearscreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern SDL_Window* window;
void drawscreen(){
	if(window) SDL_GL_SwapWindow(window);
}
