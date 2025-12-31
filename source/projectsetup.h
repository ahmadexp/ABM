void bumpintoworld(float *posx,float *posy,float radius,bool touchwater);
bool touchworld(float posx,float posy,float radius,bool touchwater);

#define gamestate_mainmenu		(0)
#define gamestate_pausemenu		(1)
#define gamestate_offlineplay	(2)
#define gamestate_serverlobby	(3)
#define gamestate_clientlobby	(4)
#define gamestate_serverplay	(5)
#define gamestate_clientplay	(6)

int gamestate=0;

float camx=0;
float camy=0;
float camz=0;

#define maxplayercount (4)
int playercount=0;

float aimx[maxplayercount];
float aimy[maxplayercount];
float aiminworldx[maxplayercount];
float aiminworldy[maxplayercount];

float shootwait[maxplayercount];
float healwait[maxplayercount];
float energy[maxplayercount];
float energyregenwait[maxplayercount];

int zombieskilled=0;

int mostzombieskilled=0;

int status=0; //to state the Alarm condition

int mode=1;

int updateturn=0;

#define mapsizex (20)
#define mapsizey (20)
//#define smallmapsizex (mapsizex/5-1)
//#define smallmapsizey (mapsizey/5-1)
#define smallmapsizex (1)
#define smallmapsizey (1)

int map[mapsizex][mapsizey];
int maprotation[mapsizex][mapsizey];
int watergrid[smallmapsizex][smallmapsizey];
int streetgrid[smallmapsizex][smallmapsizey];

#include "projectspecific/textures.h"
#include "projectspecific/text.h"
#include "projectspecific/genworldgrid.h"
#include "projectspecific/entities/wall.h"
#include "projectspecific/entities/person.h"
#include "projectspecific/entities/object.h"
#include "projectspecific/bumpintoworld.h"
#include "projectspecific/entities/rocket.h"
#include "projectspecific/entities/explosion.h"
#include "projectspecific/entities/decal.h"
#include "projectspecific/entities/shot.h"
#include "projectspecific/startnewgame.h"
#include "projectspecific/saveandload.h"
#include "projectspecific/menuandhud.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	sprintf(dash_bars_gamename,"%s","Agent Based Modeling");
	dash_bars_gameversion=0.1;

	setuptextures();
	load_music_files();
	setuptext();
	loadstats();

}
