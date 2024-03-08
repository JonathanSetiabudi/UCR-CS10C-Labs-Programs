#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {
  string title;
  cout << "Enter playlist's title:\n" << endl;
  getline(cin, title);

  if(cin.eof()){
    throw runtime_error("File was empty here.");
  }
  else if(cin.bad()){
    throw runtime_error("File was bad here.");
  }
  else if(cin.fail()){
    throw runtime_error("File failed here.");
  }

  // Build a playlist which we will use to execute the commands
  // in the loop below
  Playlist P;

  while(true) {
    P.PrintMenu(title);

    string command;
    if (!(cin >> command)) break;

    if (command == "a") {
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      string id;
      if(!(cin >> id)){
        throw runtime_error("Incorrect input for ID");
      }

      //clearing whitespace left in cin
      cin.ignore();

      //Code below takes input while constantly checking for errors with cin
      // before taking the input to add a new song to the playlist
    
      string name;
      cout << "Enter song's name:" << endl;
      getline(cin, name);
      if(cin.eof()){
        throw runtime_error("File was empty here.");
      }
      else if(cin.bad()){
        throw runtime_error("File was bad here.");
      }
      else if(cin.fail()){
        throw runtime_error("File failed here.");
      }

      string artist;
      cout << "Enter artist's name:" << endl;
      getline(cin,artist);
      if(cin.eof()){
        throw runtime_error("File was empty here.");
      }
      else if(cin.bad()){
        throw runtime_error("File was bad here.");
      }
      else if(cin.fail()){
        throw runtime_error("File failed here.");
      }

      int length;
      cout << "Enter song's length (in seconds):" << endl;
      if(!(cin >> length)){
        throw runtime_error("Incorrect input for Song length");
      }
      cout << endl;
      cin.ignore();

      P.AddSong(id,name,artist,length);
    } else if (command == "d") {
      //Takes input with cin while checking for any failures with cin
      //before taking input to remove song with id given
      cout << "REMOVE SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      string removedID;
      if(!(cin >> removedID)){
        throw runtime_error("Incorrect input for ID to be removed");
      }
      P.RemoveSong(removedID);
      cin.ignore();
    } else if (command == "c") {
      //Prompts user for current position of song to be moved and new position of song
      //while checking if cin fails at any point
      cout << "CHANGE POSITION OF SONG" << endl;
      cout << "Enter song's current position:" << endl;
      int currPos;
      if(!(cin >> currPos)){
        throw runtime_error("Incorrect input for current position");
      }

      cout << "Enter new position for song:" << endl;
      int newPos;
      if(!(cin >> newPos)){
        throw runtime_error("Incorrect input for new position");
      }
      cin.ignore();

      P.ChangePositionSong(currPos,newPos);
    } else if (command == "s") {
      cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      //Asks for artist's name
      cin.ignore();
      cout << "Enter artist's name:" << endl;
      string artist;
      getline(cin, artist);
      cout << endl;
      //Checks for errors with cin
      if(cin.eof()){
        throw runtime_error("File was empty here.");
      }
      else if(cin.bad()){
        throw runtime_error("File was bad here.");
      }
      else if(cin.fail()){
        throw runtime_error("File failed here.");
      }
      P.OutputSongsByArtist(artist);
    } else if (command == "t") {
      P.OutputTotalTime();
    } else if (command == "o") {
      cout << title << " - OUTPUT FULL PLAYLIST" << endl;
      P.OutputFullPlaylist();
    } else if (command == "q") {
      break;
    }
  }

  // If cin is in an error state (even end-of-file), then
  // something went wrong
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}
