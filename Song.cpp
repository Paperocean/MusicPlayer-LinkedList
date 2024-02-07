#include "Song.h"
#include <iomanip>

Song::Song(string name, string artist, int rating)
	:name_{name}, artist_{artist}, rating_{rating}
{
}

string Song::get_name() const{
	return name_;
}

string Song::get_artist() const{
	return artist_;
}

int Song::get_rating() const{
	return rating_;
}

ostream& operator<<(ostream& os, const Song& obj) {
	os << setw(20) << left << obj.name_ << setw(20) << obj.artist_ << setw(10) << right << obj.rating_ << endl;
	return os;
}
