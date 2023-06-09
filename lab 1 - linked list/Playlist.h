#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
using namespace std;

class PlaylistNode {
 public:
    PlaylistNode();
    PlaylistNode(string, string, string, int);
    void InsertAfter(PlaylistNode *);
    void SetNext(PlaylistNode *);
    string const GetID() const;
    string const GetSongName() const;
    string const GetArtistName() const;
    int const GetSongLength() const;
    PlaylistNode *GetNext();
    void PrintPlaylistNode();
    PlaylistNode *HEAD;
    PlaylistNode *TAIL;

 private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode *nextNodePtr;
};
#endif