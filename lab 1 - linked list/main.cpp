#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

// GLOBAL VARIABLES
PlaylistNode *HEAD = nullptr;
PlaylistNode *TAIL = nullptr;

void PrintMenu(string, PlaylistNode*);

int main () {
    string title;
    cout << "Enter playlist's title:" << endl << endl;
    getline(cin, title);
    PlaylistNode *listBegin = new PlaylistNode;
    PrintMenu(title, listBegin);

    return 1;
}

void PrintMenu(string title, PlaylistNode *listBegin) {
    string option;
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
    cin >> option;
    cin.ignore();

    if (option == "q") {
        exit(EXIT_SUCCESS);
    }

    if (option == "o") {
        cout << title << " - OUTPUT FULL PLAYLIST" << endl;
        if (HEAD == nullptr) {
            cout << "Playlist is empty" << endl << endl;
        } else {
            int track = 1;
            for (PlaylistNode *temp = HEAD; temp != nullptr; temp = temp->GetNext()) {
                cout << track << '.' << endl;
                temp->PrintPlaylistNode();
                track++;
                cout << endl;
            }
        }
    }

    if (option == "a") {
        string id;
        string songName;
        string artistName;
        int songLength;

        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        getline(cin, id);
        cout << "Enter song's name:" << endl;
        getline(cin, songName);
        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);
        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;
        cout << endl;

        PlaylistNode *song = new PlaylistNode(id, songName, artistName, songLength);

        if (listBegin->GetID() == "none") {
            listBegin = song;
            HEAD = TAIL = listBegin;
        } else {
            TAIL->InsertAfter(song);
            TAIL = song;
        }
    }

    if (option == "d") {
        string id;
        string name;
        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        cin >> id;

        // if successful (five cases)

        // 1 - the playlist is empty
        if (HEAD == nullptr) {
            PrintMenu(title, listBegin);
        } 

        // 2 - if there is only one song
        else if (HEAD == TAIL) { 
            name = HEAD->GetSongName();
            PlaylistNode temp;
            delete listBegin;
            listBegin = &temp;
            HEAD = TAIL = nullptr;
            cout << "\"" << name << "\"" << " removed" << endl << endl;
        } 
        
        // 3 - if the song is the head
        else if (HEAD->GetID() == id) { 
            name = listBegin->GetSongName();
            PlaylistNode *temp = listBegin;
            temp = HEAD = listBegin->GetNext();
            delete listBegin;
            listBegin = temp;
            cout << "\"" << name << "\"" << " removed" << endl << endl;
        } 
        
        // 4 - if the song is the tail  
        else if (TAIL->GetID() == id) {
            PlaylistNode *temp = HEAD;
            while (temp->GetNext() != TAIL) {
                temp = temp->GetNext();
            }
            PlaylistNode *remove = temp->GetNext();
            temp->SetNext(TAIL->GetNext());
            delete remove;
            TAIL = temp;
        } 

        // 5 - if there's more than one song
        else {
            PlaylistNode *temp = listBegin;
            PlaylistNode *remove = temp->GetNext();
            while (remove != nullptr && remove->GetID() != id) {
                remove = remove->GetNext();
                temp = temp->GetNext();
            }
            if (remove->GetID() == id) {
                name = remove->GetSongName();
                temp->SetNext(remove->GetNext());
            }
            delete remove;
            cout << "\"" << name << "\"" << " removed." << endl << endl;
        }
    }
    
    if (option == "c") {
        int currPos;
        int newPos;
        string name;
        cout << "CHANGE POSITION OF SONG" << endl;
        cout << "Enter song's current position:" << endl;
        cin >> currPos;
        cout << "Enter new position for song:" << endl;
        cin >> newPos;

        int size = 1;
        PlaylistNode *count = HEAD;

        // getting the size of the Playlist
        while (count->GetNext() != nullptr) {
            count = count->GetNext();
            size++;
        }

        // making sure the boundaries of the input exist within the size of the Playlist
        if (newPos <= 0) {
            newPos = 1;
        }

        if (newPos >= size) {
            newPos = size;
        }

        // no move
        if (currPos == newPos) {
            PrintMenu(title, listBegin);
        }

        // moving head to tail
        else if (currPos == 1 && newPos == size) {
            name = HEAD->GetSongName();
            PlaylistNode *newHead = HEAD->GetNext();
            TAIL->InsertAfter(HEAD);
            TAIL = HEAD;
            HEAD = newHead;

            listBegin = HEAD;
        }

        // moving tail to head
        else if (currPos == size && newPos == 1) {
            name = TAIL->GetSongName();
            PlaylistNode *newTail = HEAD;
            while (newTail->GetNext() != TAIL) {
                newTail = newTail->GetNext();
            }
            newTail->SetNext(TAIL->GetNext());

            TAIL->SetNext(HEAD);
            HEAD = TAIL;
            TAIL = newTail;

            listBegin = HEAD;
        }

        // moving the head node
        else if (currPos == 1) {
            name = HEAD->GetSongName();
            PlaylistNode *temp = HEAD;
            for (int i = 1; i < newPos; ++i) {
                temp = temp->GetNext();
            }

            listBegin = listBegin->GetNext();

            temp->InsertAfter(HEAD);

            HEAD = listBegin;
        }

        // moving the tail node
        else if (currPos == size) {
            name = TAIL->GetSongName();
            PlaylistNode *newTail = HEAD;
            while (newTail->GetNext() != TAIL) {
                newTail = newTail->GetNext();
            }

            PlaylistNode *temp = HEAD;
            for (int i = 2; i < newPos; ++i) {
                temp = temp->GetNext();
            }
            
            newTail->SetNext(TAIL->GetNext());
            temp->InsertAfter(TAIL);
            TAIL = newTail;

        }

        // moving to the head
        else if (newPos == 1) {
            PlaylistNode *newHead = HEAD->GetNext();
            PlaylistNode *previous = HEAD;
            for (int i = 2; i < currPos; ++i) {
                previous = previous->GetNext();
                newHead = newHead->GetNext();
            }
            name = newHead->GetSongName();
            previous->SetNext(newHead->GetNext());
            newHead->SetNext(HEAD);
            listBegin = newHead;

            HEAD = listBegin;
        }

        // moving to the tail
        else if (newPos == size) {
            PlaylistNode *newTail = HEAD->GetNext();
            PlaylistNode *previous = HEAD;
            for (int i = 2; i < currPos; ++i) {
                previous = previous->GetNext();
                newTail = newTail->GetNext();
            }
            name = newTail->GetSongName();
            previous->SetNext(newTail->GetNext());
            TAIL->InsertAfter(newTail);

            TAIL = newTail;
        }

        // moving it up the list
        else if (currPos > newPos) {
            PlaylistNode *beforeNew = HEAD;
            for (int i = 2; i < newPos; ++i) {
                beforeNew = beforeNew->GetNext();
            }

            PlaylistNode *beforeCurr = HEAD;
            for (int i = 2; i < currPos; ++i) {
                beforeCurr = beforeCurr->GetNext();
            }
            PlaylistNode *curr = beforeCurr->GetNext();
            name = curr->GetSongName();

            beforeCurr->SetNext(curr->GetNext());
            beforeNew->InsertAfter(curr);
        }

        // moving it down the list
        else if (currPos < newPos) {
            PlaylistNode *beforeCurr = HEAD;
            for (int i = 2; i < currPos; ++i) {
                beforeCurr = beforeCurr->GetNext();
            }
            PlaylistNode *Curr = beforeCurr->GetNext();
            name = Curr->GetSongName();

            PlaylistNode *New = HEAD;
            for (int i = 1; i < newPos; ++i) {
                New = New->GetNext();
            }

            beforeCurr->SetNext(Curr->GetNext());
            New->InsertAfter(Curr);    
        }

        cout << "\"" << name << "\"" << " moved to position " << newPos << endl << endl;

    }

    if (option == "s") {
        string artistName;
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);
        cout << endl;
        int track = 1;
        for (PlaylistNode *temp = listBegin; temp != nullptr; temp = temp->GetNext()) {
            if (temp->GetArtistName() == artistName) {
                cout << track << '.' << endl;
                temp->PrintPlaylistNode();
                cout << endl;
            }
            track++;
        }
    }

    if (option == "t") {
        int length = 0;
        for (PlaylistNode *temp = listBegin; temp != nullptr; temp = temp->GetNext()) {
            length += temp->GetSongLength();
        }
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << length << " seconds" << endl;
        cout << endl;
    }
    PrintMenu(title, listBegin);
}