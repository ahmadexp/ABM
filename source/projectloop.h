void projectloop(){
	
	//prep for drawing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
	
	

	//adjust the speed of the game based on the frame rate
	float gamespeed=60.f/dash_framerate;
	
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	int startinggamestate=gamestate;

	if(gamestate==gamestate_mainmenu){
		menu();
	}else if(gamestate==gamestate_pausemenu){
		menu();
	}else if(gamestate==gamestate_offlineplay){
		play(gamespeed);
		drawworld();
	}

	if(gamestate!=startinggamestate)menustate=0;
	dashusecursors=0;
	//float fullcoords[]={0,1,1,1,1,0,0,0,};
	//set2dcamera(-100,screenh,-100,screenw);
	//draw2dquad(0,0,screenw,screenh,fullcoords);

	//done drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

}
