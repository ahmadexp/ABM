//define some things
#define keycount                    (512)
#define buttoncount                 (20)
#define mousecount                  (10)

//controller input variables
int cursorx[4];
int cursory[4];
int cursorxmov[4];
int cursorymov[4];
bool centercursor=0;

int keystate[keycount] = {0};
int buttonstate[keycount] = {0};
int mousestate[mousecount] = {0};


//recieve input
void updateinput(){
	SDL_Event event;
	// Update 2 -> 1 (just pressed -> held)
	for(int a=0;a<keycount;a++)if(keystate[a]==2)keystate[a]=1;
	
	// SDL2 PeepEvents: use min/max type.
	// event.key.keysym.sym (SDL_Keycode) is problematic for array index. Use scancode.
	
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_KEYDOWN,SDL_KEYDOWN)) {
		if (event.key.keysym.scancode < keycount) {
			keystate[event.key.keysym.scancode]=2;
		}
	}
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_KEYUP,SDL_KEYUP)) {
		if (event.key.keysym.scancode < keycount)
			keystate[event.key.keysym.scancode]=0;
	}

	for(int a=0;a<buttoncount;a++)if(buttonstate[a]==2)buttonstate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_JOYBUTTONDOWN,SDL_JOYBUTTONDOWN))
		buttonstate[event.jbutton.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_JOYBUTTONUP,SDL_JOYBUTTONUP))
		buttonstate[event.jbutton.button]=0;

	for(int a=0;a<mousecount;a++)if(mousestate[a]==2)mousestate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_MOUSEBUTTONDOWN,SDL_MOUSEBUTTONDOWN))
		mousestate[event.button.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_MOUSEBUTTONUP,SDL_MOUSEBUTTONUP))
		mousestate[event.button.button]=0;

	if(centercursor){
		//SDL_WM_GrabInput(SDL_GRAB_ON); // SDL2 uses SDL_SetRelativeMouseMode(SDL_TRUE) usually
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		extern SDL_Window* window; // Needed to reference window
		if(window) SDL_WarpMouseInWindow(window, screenw/2, screenh/2);
		cursorxmov[0]=cursorx[0]-screenw/2;
		cursorymov[0]=cursory[0]-screenh/2;
	}else{
		int oldx=cursorx[0];
		int oldy=cursory[0];
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		cursorxmov[0]=cursorx[0]-oldx;
		cursorymov[0]=cursory[0]-oldy;
	}
}