//The music that will be played 
//Mix_Music *music = NULL; 

//The sound effects that will be used 
Mix_Chunk *normal = NULL; 
Mix_Chunk *alarm = NULL; 

bool initmusic() { 

	//Initialize SDL_mixer 	
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		return false;  

	//If everything initialized fine 
	return true; 

}

bool load_music_files() { 
	
	/*
	//Load the music 
	music = Mix_LoadMUS((char*)"Media/beat.wav"); 
	
	//If there was a problem loading the music 
	if( music == NULL ) 
		return false;  
	*/

	//Load the sound effects 
	
	normal = Mix_LoadWAV((char*)"Media/beat.wav"); 
	alarm = Mix_LoadWAV((char*)"Media/alarm.wav"); 
	 
	
	//If there was a problem loading the sound effects 
	if( ( normal == NULL ) || ( alarm == NULL ) ) 
		return false;  
	
	//If everything loaded fine 
	return true; 
}

void clean_up_music() { 

	//Free the sound effects 
	Mix_FreeChunk( normal ); 
	Mix_FreeChunk( alarm ); 
	
	//Free the music 
	//Mix_FreeMusic( music ); 
	
	//Quit SDL_mixer 
	Mix_CloseAudio(); 
}