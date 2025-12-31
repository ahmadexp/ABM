bool shutdownprogram = 0;

#include "generic.h"
#include "settings.h"
#include "projectsetup.h"
#include "projectloop.h"

int main(int argc,char **argv){

	loadgenericsettings();
	loadsettings();
	
	// Ensure sane minimums if settings are missing or zero
	if(screenw < 100) screenw = 1280;
	if(screenh < 100) screenh = 720;
	screena = screenw / screenh;

	genericsetup();
	if (window) SDL_RaiseWindow(window);
	
	dashsetup();
	projectsetup();

	// Main Game Loop
	while(!shutdownprogram){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		SDL_PumpEvents();
		updateinput();

		// Update and draw the main project
		if(dashonpercent < 100.f) projectloop();

		// Update and draw the dashboard overlay
		dashloop();

		if(window) SDL_GL_SwapWindow(window);

		// Global event handling
		SDL_Event event;
		while(SDL_PeepEvents(&event,1,SDL_GETEVENT,0,SDL_LASTEVENT)>0) {
			if(event.type==SDL_QUIT) shutdownprogram=1;
		}
	}
	
	clean_up_music();
    SDL_Quit();
    return 0;
}
