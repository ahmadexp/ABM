float dashonpercent;
bool dashon;

SDL_Surface *dash_background_sprite = NULL;
SDL_Surface *dash_backgroundblurred_sprite = NULL;

Uint8* dash_background_opengl;
GLuint dash_background_texture = 0;

int dashonslide(int onpos,int offpos){
	return(int)((float)onpos*dashonpercent*0.01f+(float)offpos*(1.f-dashonpercent*0.01f));
}

void setupdashonoff(){
	dashonpercent=0;
	dashon=0;
	// Use window size (points) for buffer
	dash_background_opengl = new Uint8 [4*(int)screenw*(int)screenh];
	
	// Create texture for background
	glGenTextures(1, &dash_background_texture);
	glBindTexture(GL_TEXTURE_2D, dash_background_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void dashonoff(float dashspeed){

	
	if(keystate[SDL_SCANCODE_ESCAPE]==2){
		if(dashon==0){
			dashon=1;
			if(dashonpercent==0){
				// Capture the screen
				glReadPixels(0,0,(int)screenw,(int)screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);
				
				// Upload to texture
				glBindTexture(GL_TEXTURE_2D, dash_background_texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)screenw, (int)screenh, 0, GL_RGBA, GL_UNSIGNED_BYTE, dash_background_opengl);
			}
			
		}else{
			dashon=0;
		}
	}
	
	if(dashonpercent!=0){
		// Background capture disabled - causes camera position issues
		// The menu will display over a clean background instead
		/*
		// Draw the background as a fullscreen textured quad
		GLint oldMatrixMode;
		glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
		
		glPushAttrib(GL_ENABLE_BIT);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, screenw, 0, screenh, -1, 1);
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, dash_background_texture);
		
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2f(0, 0);
			glTexCoord2f(1, 1); glVertex2f(screenw, 0);
			glTexCoord2f(1, 0); glVertex2f(screenw, screenh);
			glTexCoord2f(0, 0); glVertex2f(0, screenh);
		glEnd();
		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		
		// Restore original matrix mode
		glMatrixMode(oldMatrixMode);
		
		glPopAttrib();
		*/
	}
	

	if(dashon){
		dashonpercent+=5.f*dashspeed;
		//if(dashonpercent>100)dashonpercent=100;
	}else{
		dashonpercent-=5.f*dashspeed;
		//if(dashonpercent<0)dashonpercent=0;
	}
	if(dashonpercent>100)dashonpercent=100;
	if(dashonpercent<0)dashonpercent=0;
	if(dashonpercent!=dashonpercent)dashonpercent=0;

}

