//types
#define decaltype_corpse		(0)
#define decaltype_blood			(1)

//struct info
typedef struct decal{
	int type;
	float posx,posy,angle;
}decal;

//keep a list of every one
#define maxdecalcount (500)
struct decal decallist[maxdecalcount];
int decalcount=0;

//helpfull function for removing one from the list
void removedecalfromlist(int num){
	if(num!=decalcount)
		for(int b=num;b<decalcount;b++)
			decallist[b]=decallist[b+1];
	decalcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makedecal(int type,float posx,float posy,float angle){
	if(decalcount==maxdecalcount)removedecalfromlist(0);
	decallist[decalcount].type=type;
	decallist[decalcount].posx=posx;
	decallist[decalcount].posy=posy;
	decallist[decalcount].angle=angle;
	decalcount+=1;
}
