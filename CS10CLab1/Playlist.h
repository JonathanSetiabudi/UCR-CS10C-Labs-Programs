#pragma once



#include <iostream>
using namespace std;

//I'm going to define the playlistNode class in here to make the playlist.cpp file cleaner.

class PlaylistNode {
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  //using inline declarations except for the pointer to be safe.
  PlaylistNode():
    uniqueID("none"),
    songName("none"),
    artistName("none"),
    songLength(0)
  {nextNodePtr = 0;}

  PlaylistNode(const string& ID,const string& name, const string& artist, int length):
    uniqueID(ID),
    songName(name), 
    artistName(artist), 
    songLength(length)
  {nextNodePtr = 0;}

  void InsertAfter(PlaylistNode* newNode) {
   PlaylistNode* tmpNext = nullptr;
   tmpNext = this->nextNodePtr;    // Remembers next
   this->nextNodePtr = newNode;    // sets next node of this to be newNode
   newNode->nextNodePtr = tmpNext; // sets next of newNode to be this's old next
  }
  
  void SetNext(PlaylistNode* nextNode){nextNodePtr = nextNode;}
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength <<endl;
  }
};

class Playlist {
  PlaylistNode* head = nullptr;
  PlaylistNode* tail = nullptr;
public:
  Playlist()
    : head(nullptr),tail(nullptr)
  {}
  ~Playlist(){ this->clear(); }
  Playlist(const Playlist& copy);
  Playlist& operator=(const Playlist& copy);
  void clear();
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const string& song, const string& artist, int length);
  void RemoveSong(const string& id);
  void ChangePositionSong(int oldPos,int newPos);
  void OutputSongsByArtist(const string& artist) const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

