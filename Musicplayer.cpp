#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <iterator>
#include <exception>
#include <limits>
#include <fstream>
#include <sstream>
#include "Song.h"

using namespace std;

void display_menu();
void playing_song(const Song& song);
void use_menu(list<Song>::iterator& current_song, list<Song>& playlist, ofstream& of);

int main()
{
    ifstream i_file{ "Playlist.txt" };
    
    if (!i_file) {
        cerr << "Error with file path" << endl;
        return 1;
    }

    list<Song> playlist{};
    string line{};
    while (getline(i_file, line)) {
        string title{}, artist{};
        int rating{};
        stringstream ss{ line };
        getline(ss, title, ',');
        getline(ss, artist, ',');
        if (!(ss >> rating))
            rating = 0;
        playlist.push_back(Song{ title, artist, rating });
    }

    /*list<Song> playlist{
        {"Last Orders" , "Nothing But Thieves", 4},
        {"If I Get High" , "Nothing But Thieves", 5},
        {"Need It" , "Half Moon Run", 4},
        {"Hearts A Mess" , "Gotye", 5},
        {"in your arms" , "Sombr", 5},
    };*/


    ofstream o_file{ "Playlist.txt" };

    // Current song
    list<Song>::iterator current_song = playlist.begin();
    use_menu(current_song, playlist, o_file);

    // Saving file
    for (const auto& p : playlist) {
        o_file << p.get_name() << "," << p.get_artist() << "," << p.get_rating() << endl;
    }

    i_file.close();
    o_file.close();
    return 0;
}

void display_menu() {
    cout << "C - Show current song" << endl;
    cout << "F - Play First song" << endl;
    cout << "N - Play Next song" << endl;
    cout << "P - Play Previous song" << endl;
    cout << "A - Add and play a new song at current location" << endl;
    cout << "D - Delete current and play first song" << endl;
    cout << "L - List the current playlist" << endl;
    cout << "===============================================" << endl;
    cout << "Enter a selection (Q to quit): ";
}

void playing_song(const Song& song) {
    cout << setw(25) << setfill('=') << " Playing " << setw(26) << "" << endl;
    cout << setfill(' ') << "";
    cout << song << endl;
}

void use_menu(list<Song>::iterator& current_song, list<Song>& playlist, ofstream& of) {
    char c;
    string song_name, song_artist;
    int song_rating;

    do {
        display_menu();
        cin >> c;
        system("cls");

        switch (c) {
        case 'C':
        case 'c':
            cout << endl << setw(30) << setfill('=') << " Showing current song.... " << setw(20) << "" << endl;
            cout << setfill(' ') << "";
            cout << *current_song << endl;
            break;
        case 'F':
        case 'f':
            cout << "\nPlaying First Song...." << endl;
            current_song = playlist.begin();
            playing_song(*current_song);
            break;
        case 'N':
        case 'n':
            cout << "\nPlaying Next Song...." << endl;
            if (current_song == --playlist.end()) {
                current_song = playlist.begin();
                playing_song(*current_song);
            }
            else {
                playing_song(*(++current_song));
            }
            break;
        case 'P':
        case 'p':
            cout << "\nPlaying Previous Song...." << endl;
            if (current_song == playlist.begin()) {
                current_song = --playlist.end();
                playing_song(*current_song);
            }
            else {
                playing_song(*(--current_song));
            }
            break;
        case 'A':
        case 'a':
            cout << endl << setw(25) << setfill('=') << " Adding new song " << setw(26) << "" << endl;
            cout << setfill(' ') << "";
            cout << "Type song name: ";
            cin.ignore();
            getline(cin, song_name);
            cout << "Type song artist: ";
            getline(cin, song_artist);
            do {
                try {
                    cout << "Type song rating: ";
                    cin >> song_rating;
                    if (cin.fail()) throw runtime_error{ "Invalid input. Please enter a number." };
                    break;
                }
                catch (const exception& ex) {
                    cerr << "Error: " << ex.what() << endl;
                    // Clear the input stream to remove the invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            } while (true);
            //playlist.push_back(Song{ song_name, song_artist, song_rating });
            //playlist.emplace_back(song_name, song_artist, song_rating);
            playlist.insert(current_song, Song{ song_name,song_artist,song_rating });
            playing_song(*(--current_song));
            break;
        case 'D':
        case 'd':
            cout << endl << setw(25) << setfill('X') << " Deleting song " << setw(26) << "" << endl;
            cout << setfill(' ') << "";
            cout << *current_song << endl;
            playlist.erase(current_song);
            current_song = playlist.begin();
            // Saving in main()
            break;
        case 'L':
        case 'l':
            cout << endl << setw(25) << setfill('=') << " Playlist " << setw(26) << "" << endl;
            cout << setfill(' ') << "";
            cout << setw(20) << left << "TITLE" << setw(20) << "ARTIST" << setw(10) << right << "RATING" << endl;
            for (const auto& s : playlist)
                cout << s;
            /*for (auto it = playlist.begin(); it != --playlist.end(); ++it) {
                cout << *it;
            }*/
            cout << endl;
            break;
        case 'Q':
        case 'q':
            cout << "\nQuiting...." << endl;
            break;
        default:
            cout << "\nInvalid option!" << endl;
        }
    } while (c != 'q' && c != 'Q');
}
