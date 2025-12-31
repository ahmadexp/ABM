float dashonpercent;
bool dashon;

SDL_Surface *dash_background_sprite = NULL;
SDL_Surface *dash_backgroundblurred_sprite = NULL;

Uint8* dash_background_opengl;

int dashonslide(int onpos,int offpos){
	return(int)((float)onpos*dashonpercent*0.01f+(float)offpos*(1.f-dashonpercent*0.01f));
}

void setupdashonoff(){
	dashonpercent=0;
	dashon=0;
	dash_background_opengl = new Uint8 [4*(int)screenw*(int)screenh];
}

void dashonoff(float dashspeed){

	
	if(keystate[SDL_SCANCODE_ESCAPE]==2){
		if(dashon==0){
			dashon=1;
			if(dashonpercent==0){
				// glReadPixels(0,0,(GLsizei)screenw,(GLsizei)screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);
			}
			
		}else{
			dashon=0;
		}
	}
	
	if(dashonpercent!=0){
		// glDrawPixels is slow and can cause black screen if buffer is uninitialized
		// glDrawPixels(screenw,screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);
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
