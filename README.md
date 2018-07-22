# PlayList

Functions of My Media Player:
Welcome To Mymedia player:>>
No PlayList
1.Create a new Playlist
2.Print all Playlist
3.Print active Playlist
4.Enter the playlist no to start it
5.Add Song To Playlist
6.See songs in Active PlayList
7.Delete the playlist
8.See the modes out of (1 for normal 2 for repeat playlist 3 for shuffle playList)
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
