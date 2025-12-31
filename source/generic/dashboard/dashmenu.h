void dashsavescreenshot(){
	char filename[256];
	ifstream test;
	int filenumber=1;
	sprintf(filename,"screenshot%d.png",filenumber);
	test.open(filename);test.close();
	if(!test.fail()){
		while(!test.fail()){
			filenumber=filenumber+1;
			sprintf(filename,"screenshot%d.png",filenumber);
			test.open(filename);test.close();
		}
	}
	
	int w=screenw;
	int h=screenh;
	std::vector<unsigned char> image;
	image.resize(w * h * 4);
	for(int y = 0; y < h; y++)for(int x = 0; x < w; x++){
		image[4*w*y+4*x+0] = (unsigned char)dash_background_opengl[4*w*(h-1)-4*w*y+4*x+0];
		image[4*w*y+4*x+1] = (unsigned char)dash_background_opengl[4*w*(h-1)-4*w*y+4*x+1];
		image[4*w*y+4*x+2] = (unsigned char)dash_background_opengl[4*w*(h-1)-4*w*y+4*x+2];
		image[4*w*y+4*x+3] = (unsigned char)255;
		//create encoder and set settings and info (optional)
		LodePNG::Encoder encoder;
		encoder.addText("Comment", "Created with LodePNG");
		encoder.getSettings().zlibsettings.windowSize = 2048;
		//encode and save
		std::vector<unsigned char> buffer;
		encoder.encode(buffer, image.empty() ? 0 : &image[0], w, h);
		LodePNG::saveFile(buffer, filename);
	}
	
}

void setupdashmenu(){

}

void dashmenu(){
	
	int x=screenw/2;
	int y=dashonslide(screenh/2-100,screenh/2-100+screenh);
	
	if(dashbutton(x,y,200,15,1,1,(char*)"Resume"))dashon=0;
	y+=35;
	if(dashbutton(x,y,200,15,1,1,(char*)"Screenshot"))dashsavescreenshot();
	y+=35;
	if(dashbutton(x,y,200,15,1,1,(char*)"Exit"))shutdownprogram=true;
	y+=35;
	
}