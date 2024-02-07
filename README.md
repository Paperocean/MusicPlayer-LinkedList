# MusicPlayer-LinkedList
The provided code implements a music player management system using a linked list in C++.

The program begins by attempting to open a file named "Playlist.txt" in read mode. If the file opening fails, it outputs an error message and terminates. It then reads the contents of the file line by line, parsing each line into song attributes (title, artist, and rating) separated by commas. These attributes are used to create Song objects, which are then added to a linked list (std::list<Song>).

Alternatively, there is a commented-out block of code containing a predefined playlist for testing purposes.

After reading the playlist from the file, the program provides a menu-driven interface to interact with the playlist. Users can perform various operations such as displaying the current song, playing the next or previous song, adding a new song, deleting a song, and listing the entire playlist. The menu is displayed iteratively until the user chooses to quit by pressing 'Q' or 'q'.

The playlist is updated dynamically based on the user's actions. After the user quits, the program saves the updated playlist back to the "Playlist.txt" file.

Functions included in the code are:

display_menu(): Displays the menu options for interacting with the playlist.
playing_song(const Song& song): Displays the details of the currently playing song.
use_menu(list<Song>::iterator& current_song, list<Song>& playlist, ofstream& of): Implements the main menu-driven functionality, allowing the user to interact with the playlist.
The code also includes basic error handling, such as checking file opening status and validating user input when adding a new song. If invalid input is provided for the song rating, an error message is displayed, and the user is prompted to enter the rating again.

Overall, the program provides a simple yet effective way to manage and interact with a music playlist through a console-based interface.
