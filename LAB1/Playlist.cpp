#include "Playlist.h"
//Copy constructor
Playlist::Playlist(const Playlist& copy){
  PlaylistNode* newNode = copy.head;
  while(newNode != nullptr){
    AddSong(newNode->GetID(),newNode->GetSongName(),newNode->GetArtistName(),newNode->GetSongLength());
    newNode = newNode->GetNext();
  }
}

//Copy assignment operator
Playlist& Playlist::operator=(const Playlist& copy){
  clear();
  PlaylistNode* newNode = copy.head;
  while(newNode != nullptr){
    AddSong(newNode->GetID(),newNode->GetSongName(),newNode->GetArtistName(),newNode->GetSongLength());
    newNode = newNode->GetNext();
  }
  return *this;
}

void Playlist::PrintMenu(const string& title) const {
  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;

  cout << '\n' << "Choose an option:" << endl;
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  //Declaring new Node;
  PlaylistNode* newSong = new PlaylistNode(id,song,artist,length);
  //Case if the playlist is empty
  if(head == nullptr && tail == nullptr){
    head = newSong;
    tail = newSong;
  }
  //For other regular cases
  else{
    tail->SetNext(newSong);
    tail = newSong;
  }
}
    
void Playlist::RemoveSong(const string& id) {
  //Only commits if list isn't empty
  if(head != nullptr){
    PlaylistNode* prevNode = head;
    PlaylistNode* currNode = head->GetNext();
    //Case if song to be removed is the only song in the playlist
    if(head->GetNext() == nullptr && head->GetID() == id){
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    //Case if song to be removed is first in playlist
    else if(prevNode->GetID() == id){
      cout << "\"" <<prevNode->GetSongName() << "\" removed.\n" << endl;
      delete head;
      head = currNode;
    }
    //other cases
    else{
      //While loop runs until either song id is found or reaches end of playlist
      while(currNode != tail){
        if(currNode->GetID() == id){
          prevNode->SetNext(currNode->GetNext());
          cout << "\"" <<currNode->GetSongName() << "\" removed.\n" << endl;
          delete currNode;
          currNode = prevNode->GetNext();
        }
        else{
          currNode = currNode->GetNext();
          prevNode = prevNode->GetNext();
        }

      }
      //Next few lines will deal with what happens when song to be removed is @ end of playlist
      if(tail->GetID() == id){
        cout << "\"" <<currNode->GetSongName() << "\" removed.\n" << endl;
        delete tail;
        currNode = nullptr;
        tail = prevNode;
      }
    }
  }
}
    
void Playlist::ChangePositionSong(int oldPos,int newPos) {
  //Checks whether or not it can run the function
  if(oldPos > 0 && oldPos != newPos){
    //Helper nodes and variables
    PlaylistNode* currNode = head->GetNext();
    PlaylistNode* prevNode = head;
    PlaylistNode* nodeToMove = nullptr;
    int playListLength = 1;
    while(prevNode != nullptr){
      prevNode = prevNode->GetNext();
      ++playListLength;
    }
    prevNode = head;
    //the case if song to be moved is the head
    if(oldPos == 1){
      nodeToMove = head;
      head = head->GetNext();
      prevNode = head;
      currNode = prevNode->GetNext();
    }
    //the case if the song to be moved is the tail
    else if(oldPos >= playListLength){
      while(currNode != tail){
        prevNode = prevNode->GetNext();
        currNode = currNode->GetNext();
      }
      nodeToMove = currNode;
      tail = prevNode;
      prevNode->SetNext(nullptr);
      prevNode = head;
      currNode = head->GetNext();
    }
    //General cases for if it isn't the head or tail
    else{
      int pos = 2;
      while(pos < oldPos && pos < playListLength){
        prevNode = prevNode->GetNext();
        currNode = currNode->GetNext();
        ++pos;
      }
      nodeToMove = currNode;
      prevNode->SetNext(currNode->GetNext());
      prevNode = head;
      currNode = prevNode->GetNext();
    }
    
    //Starting here is where code related to relocating the old song will be.

    //Case if we are moving the new song to head.
    if(newPos <= 1){
      nodeToMove->SetNext(head);
      head = nodeToMove;
      cout << "\"" << nodeToMove->GetSongName() << "\" moved to position 1" << endl;
    }
    //Case if we are moving the new song to tail.
    else if(newPos >= playListLength){
      tail->InsertAfter(nodeToMove);
      tail = nodeToMove;
      cout << "\"" << nodeToMove->GetSongName() << "\" moved to position " << playListLength << endl;
    }
    //General cases
    else{
      int currPos = 1;
      while(currPos < newPos-1){
        prevNode = prevNode->GetNext();
        ++currPos;
      }
      prevNode->InsertAfter(nodeToMove);
      cout << "\"" << nodeToMove->GetSongName() << "\" moved to position " << newPos << "\n" << endl;
    }
  }
}

//Outputs songs done by a specific artist and their position within the playlist. 
void Playlist::OutputSongsByArtist(const string& artist) const {
  int count = 1;
  PlaylistNode* currNode = head;
  while(currNode != nullptr){
    //Only outputs if it has same artist name
    if(currNode->GetArtistName() == artist){
      cout << count << "." << endl;
      currNode->PrintPlaylistNode();
      cout << endl;
    }
    currNode = currNode->GetNext();
    ++count;
  }
}
    
void Playlist::OutputTotalTime() const {
  int totalTime = 0;
  //counts total time
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    totalTime += curr->GetSongLength();
  }
  //output
  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  cout << "Total time: " << totalTime << " seconds\n" << endl;
}

//Outputs the playlist with their position number.
void Playlist::OutputFullPlaylist() const {
  if(head != nullptr){
    int count = 1;
    PlaylistNode* curr = head;
    while(curr != nullptr){
      cout << count << "." << endl;
      curr->PrintPlaylistNode();
      cout << '\n';
      ++count;
      curr = curr->GetNext();
    }
  }
  else{
    cout << "Playlist is empty\n" << endl;
  }
}

// Clear function for ease of use. Can use for rule of three.
void Playlist::clear() {
  //Node to be deleted
  PlaylistNode* nodeTBD = head;
  while(nodeTBD != nullptr){
    head = head->GetNext();
    delete nodeTBD;
    nodeTBD = head;
  }
}

