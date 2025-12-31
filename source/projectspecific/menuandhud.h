void drawtileblack(float posx1,float posy1,float posx2,float posy2){
	draw2dquad(
		posx1,posy1,
		posx2-posx1,posy2-posy1,
		wallbordertexturecoords,
		0,0.f);
}

void drawtilebright(float posx1,float posy1,float posx2,float posy2){
	glBindTexture(GL_TEXTURE_2D,tilebrighttexture);
	float scale=1.f/64.f;
	float temptexturecoords[] = {
		posx1*scale,posy2*scale,
		posx2*scale,posy2*scale,
		posx2*scale,posy1*scale,
		posx1*scale,posy1*scale,};
	draw2dquad(posx1,posy1,posx2-posx1,posy2-posy1,temptexturecoords,0,0.f);
	
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
}

void drawtiledark(float posx1,float posy1,float posx2,float posy2){
	glBindTexture(GL_TEXTURE_2D,tiledarktexture);
	float scale=1.f/64.f;
	float temptexturecoords[] = {
		posx1*scale,posy2*scale,
		posx2*scale,posy2*scale,
		posx2*scale,posy1*scale,
		posx1*scale,posy1*scale,};
	draw2dquad(posx1,posy1,posx2-posx1,posy2-posy1,temptexturecoords,0,0.f);
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
}

void drawprogressbar(float posx1,float posy1,float posx2,float posy2,float border,float progress){
	drawtileblack(posx1-border,posy1-border,posx2+border,posy2+border);
	drawtiledark(posx1,posy1,posx2,posy2);
	progress=posx2*progress+posx1*(1.f-progress);
	drawtilebright(posx1,posy1,progress,posy2);
}

void drawingamehud(){

	//set the camera: left, right, bottom, top
	set2dcamera(-400.f*screena,400.f*screena,400.f,-400.f);

	//draw the red borders	
	glBindTexture(GL_TEXTURE_2D,borderbloodtexture);
		
	float scale=(personlist[0].health*0.0025f*5.92f+1.f);
	if(scale<1.f)scale=1.f;
	draw2dquad(0.f,0.f,scale*800.f*screena,scale*800.f,borderbloodtexturecoords,1,0.f);

	//draw the black borders
	glBindTexture(GL_TEXTURE_2D,borderdarknesstexture);	
	draw2dquad(0.f,0.f,800.f*screena,800.f,borderdarknesstexturecoords,1,0.f);

	//reset the texture
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);

	char temptext[100];
	float textx=-400.f*screena+50.f;
	float texty=-350.f;

	sprintf(temptext,"%s","Press 's' to trigger the Alarm");
	drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	
	if(status)sprintf(temptext,"%s","Alarm ON");
	else sprintf(temptext,"%s","Alarm OFF");
	drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;

	sprintf(temptext,"%s%i","AI Mode : ", mode);
	drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
}

int menustate=0;
int menustaterendering=0;

bool menuitem(char* text,bool select){
	float textx=0.f;
	float texty=-80.f+45.f*(float)menustaterendering;
	if(menustaterendering==menustate)
		drawtilebright(-250.f,texty,250.f,texty+40.f);
	drawtextcenteraligned(textx,texty,text,1.0f);
	menustaterendering+=1;
	if(menustaterendering==menustate+1){
		return select;
	}else{
		return 0;
	}
}

void menu(){
	//set the camera: left, right, bottom, top
	set2dcamera(-400.f*screena,400.f*screena,400.f,-400.f);

	drawtiledark(-400.f*screena,-400.f,400.f*screena,400.f);

	// Centered logo
	draw2dquad(0,-220.f,175.f*4.f,175.f,logotexturecoords,1,0.f);

	bool up=0,down=0,select=0;

	if(keystate[SDL_SCANCODE_W]==2||keystate[SDL_SCANCODE_UP]==2)up=1;
	if(keystate[SDL_SCANCODE_S]==2||keystate[SDL_SCANCODE_DOWN]==2)down=1;
	if(keystate[SDL_SCANCODE_SPACE]==2||keystate[SDL_SCANCODE_RETURN]==2)select=1;
	

	menustaterendering=0;

	if(gamestate==1)if(menuitem((char*)"Resume",select)){
		gamestate=gamestate_offlineplay;}
	if(menuitem((char*)"Start Simulation",select)){
		playercount=1;
		startnewgame();
		gamestate=gamestate_offlineplay;}

	if(up)menustate-=1;
	if(down)menustate+=1;
	if(menustate<0)menustate=0;
	if(menustate>menustaterendering-1)menustate=menustaterendering-1;
}
