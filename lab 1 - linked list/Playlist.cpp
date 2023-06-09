#include <iostream>
#include "Playlist.h"

PlaylistNode::PlaylistNode() : 
                     uniqueID("none"),
                     songName("none"),
                     artistName("none"),
                     songLength(0),
                     nextNodePtr(0) { }

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength) :
                            uniqueID(uniqueID),
                            songName(songName),
                            artistName(artistName),
                            songLength(songLength) { }

void PlaylistNode::InsertAfter(PlaylistNode *currPos) {
    currPos->SetNext(this->GetNext());
    this->SetNext(currPos);
}

void PlaylistNode::SetNext(PlaylistNode *list) {
    this->nextNodePtr = list;
}

string const PlaylistNode::GetID() const {
    return this->uniqueID;
}

string const PlaylistNode::GetSongName() const {
    return this->songName;
}

string const PlaylistNode::GetArtistName() const {
    return this->artistName;
}

int const PlaylistNode::GetSongLength() const {
    return this->songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    PlaylistNode *temp = this;
    if (temp->nextNodePtr == nullptr) {
        temp = nullptr;
    } else {
        temp = this->nextNodePtr;
    }
    return temp;
}

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << GetID() << endl;
    cout << "Song Name: " << GetSongName() << endl;
    cout << "Artist Name: " << GetArtistName() << endl;
    cout << "Song Length (in seconds): " << GetSongLength() << endl;
}