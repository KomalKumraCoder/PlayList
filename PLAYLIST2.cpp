#include<iostream>
#include<climits>
#include<cctype>
#include<time.h>
#include<stdlib.h>
using namespace std;
bool compare(char* one,char* two,int pos=0){
	if(one[pos]=='\0'&&two[pos]=='\0')
		return true;
	if((one[pos]=='\0'&&two[pos]!='\0')||(one[pos]!='\0'&&two[pos]=='\0')||(one[pos]!=two[pos]))
		return false;
	return compare(one,two,pos+1);
}
struct songs{
	char* songName;
	struct songs* nextSong;
};
struct SongNotPlayed{
	char* song;
	struct SongNotPlayed* next;
	bool played;
};
struct playlists{
	int playMode;
	char * listName;
	struct playlists* nextPlayList;
	struct songs* head;
};
class MediaPlayer{
	public:
	struct playlists* start;
	struct playlists* active;
	struct SongNotPlayed * hashTable[10];
	int listCount;
	MediaPlayer(){
		active=NULL;
		listCount=0;
		start=NULL;
		for(int i=0;i<10;i++)
			hashTable[i]=NULL;
	}
	void makeNull(){
		for(int i=0;i<10;i++)
			hashTable[i]=NULL;
	}

	void initHash(struct playlists*);
	void deleteActivePlayList();
	bool isPlayerEmpty();
	void printPlayList();
	bool isPlaylistEmpty();
	void createNewPlayList();
 	void addSongs();
	void setActive(int);
	void peekPlayList();
	void printActivePlayList();
	void deleteSongFromPlayList(int);
	int getSongsCount(struct songs*);
	int hashKey(char*);
	int getFirstSum(char*,int,int);
	void playSongs(int );
	bool isactive();
	void setModeNormal();
	void setModeRepeatPlayList();
	void setShuffle();
	bool isFalsePresent(struct SongNotPlayed*);
	void resetHash();
};
void MediaPlayer::resetHash(){
	makeNull();
	initHash(active);
}
bool MediaPlayer::isFalsePresent(struct SongNotPlayed* start){
	while(start!=NULL){
		if(start->played==false)
			return true;
		start=start->next;
	}
	return false;
}
void MediaPlayer::setShuffle(){
	int limit=getSongsCount(active->head);
	int x;
	while(limit--){
		while(1){
			x=rand()%10;
			if(hashTable[x]!=NULL&&isFalsePresent(hashTable[x]))
				break;
		}
		struct SongNotPlayed* start=hashTable[x];
		while(start!=NULL&&start->played==true)
			start=start->next;
		start->played=true;
		cout<<start->song<<endl;
	}
	for(int i=0;i<10;i++){
		if(hashTable[i]!=NULL){
			struct SongNotPlayed* start=hashTable[i];
			while(start!=NULL){
				start->played=false;
				start=start->next;
			}
		}
	}
}
void MediaPlayer::setModeNormal(){
	for(int i=0;i<10;i++){
		if(hashTable[i]!=NULL){
			struct SongNotPlayed* start=hashTable[i];
			while(start!=NULL){
				cout<<start->song<<endl;
				start=start->next;
			}
		}
	}
}
void MediaPlayer::setModeRepeatPlayList(){
	int i=0;
	int limit=10;
	int countLimit=0;
	while(countLimit<limit){
		if(hashTable[i]!=NULL){
			struct SongNotPlayed* start=hashTable[i];
			while(start!=NULL){
				cout<<start->song<<endl;
				start=start->next;
			}	
		}
		i=(i+1)%10;
		if(i==0)
			countLimit++;
	}
}
bool MediaPlayer::isactive(){
	if(active==NULL){
		cout<<"No Playlist selected"<<endl;
		return false;
	}
	return true;
}
void MediaPlayer::playSongs(int mode){
	if(isactive()){
		active->playMode=mode;
		switch(mode){
			case 1:
				setModeNormal();
				break;
			case 2:
				setModeRepeatPlayList();
				break;
			case 3:
				setShuffle();
				break;
			default:
				cout<<"mode not in service"<<endl;
		}
	}
}
int MediaPlayer::getFirstSum(char* myString,int sum=0,int pos=0){
	if(myString[pos]=='\0')
		return sum;
	if(pos==0||(pos!=0&&!isalpha(myString[pos-1])&&isalpha(myString[pos])))
		sum+=myString[pos];
	return getFirstSum(myString,sum,pos+1);
}
int MediaPlayer::hashKey(char* myString){
	int sum=getFirstSum(myString);
	return sum%10;
}
int MediaPlayer::getSongsCount(struct songs* head){
	int count=0;
	struct songs* temp=head;
	while(temp!=NULL){
		count++;
		temp=temp->nextSong;
	}
	return count;
}
void MediaPlayer::initHash(struct playlists* playlist){
	struct songs* songHead=playlist->head;
	makeNull();
	while(songHead!=NULL){
		int key=hashKey(songHead->songName);
		struct SongNotPlayed* latest=new SongNotPlayed;
		latest->song=songHead->songName;
		latest->played=false;
		latest->next=hashTable[key];
		hashTable[key]=latest;
		songHead=songHead->nextSong;
	}
}
void MediaPlayer::deleteSongFromPlayList(int choice){
	if(active==NULL){
		cout<<"No Playlist selected for now"<<endl;
		return;
	}
	int count=1;
}
void MediaPlayer::printActivePlayList(){
	if(isactive())
	cout<<active->listName<<endl;
}
void MediaPlayer::deleteActivePlayList(){
	if(isactive()){
		makeNull();
		struct playlists* prev=NULL;
		while(prev!=NULL&&prev->nextPlayList!=active)
				prev=prev->nextPlayList;
		if(prev==NULL){
			start=start->nextPlayList;
				delete active;
			}
		else{
			prev->nextPlayList=active->nextPlayList;
			delete active;
		}
		active=NULL;
	}
}
void MediaPlayer::peekPlayList(){
	if(isactive()){
		struct songs* peek=active->head;
		if(peek==NULL){
			cout<<"Sorry no Songs in "<<active->listName<<" PlayList"<<endl;
			return;
		}
		int count=0;
		while(peek!=NULL){
		count++;
			cout<<count<<" "<<peek->songName<<endl;
			peek=peek->nextSong;
		}
	}
}
void MediaPlayer::addSongs(){
	if(isactive()){
		cout<<"Enter Song Name:: "<<endl;
		char* name=new char[100];
		//cin.getline(name,100);
		cin>>name;
		struct songs* latestSong=new songs;
		latestSong->songName=name;
		latestSong->nextSong=active->head;
		active->head=latestSong;
		cout<<"Song SuccessFully Added"<<endl;
		resetHash();
	}
}
bool MediaPlayer::isPlayerEmpty(){
	return start==NULL;
}
void MediaPlayer::printPlayList(){
	if(!isPlayerEmpty()){
		struct playlists* temp=start;
		int count=0;
		while(start!=NULL){
			count++;
			cout<<count<<" "<<start->listName<<endl;
			listCount++;
			start=start->nextPlayList;
		}
		return;
	}
	cout<<"No Playlist"<<endl;
}
bool MediaPlayer::isPlaylistEmpty(){
	return active==NULL;
}
void MediaPlayer::createNewPlayList(){
	cout<<"Enter the Name Of The PlayList"<<endl;
	char* name=new char[100];
	cin>>name;
	struct playlists* latestPlayList=new playlists;
	latestPlayList->listName=name;
	latestPlayList->playMode=1;
	latestPlayList->head=NULL;
	latestPlayList->nextPlayList=start;
	start=latestPlayList;
	active=start;
}
void MediaPlayer::setActive(int _no){
	if(_no<=listCount||_no>0){
		if(active!=NULL)
			makeNull();
		struct playlists* temp=start;
		while(_no!=1){
			temp=temp->nextPlayList;
			_no--;
		}
		active=temp;
		initHash(active);
		return;
	}
	cout<<"Invalid Entry"<<endl;
}
int main(){
	MediaPlayer m;
	cout<<"Welcome to My media Player :>) "<<endl;
	m.printPlayList();
	do{
		int choice;
		int inter;
		//cin>>choice;
		cout<<"1 :- Create a new playlist"<<endl<<"2 :- Print All the PlayLists "<<endl<<"3 :- print the active PlayList"<<" 4 :- Enter the Playlist no. to start it"<<endl<<"5:- add Song to The Playlist"<<endl<<"6 :- See songs in active Playlist"<<endl<<"7:- delete the Playlist"<<endl<<"8:- set modes out of (1 for normal 2 for repeat playlist 3 for shuffle play)"<<endl;
	cin>>choice;
	switch(choice){
		case 1:
			m.createNewPlayList();
			break;
		case 2:
			m.printPlayList();
			break;
		case 3:
			m.printActivePlayList();
			break;
		case 4:
			cin>>inter;
			m.setActive(inter);
			break;
		case 5:
			m.addSongs();
			break;
		case 6:
			m.peekPlayList();
			break;
		case 7:
			m.deleteActivePlayList();
			break;
		case 8:
			cin>>inter;
			m.playSongs(inter);
			break;
	}
	if(choice==0)
		break;
	}while(1);
}
