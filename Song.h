#ifndef _SONG_H_
#define _SONG_H_

#include <iostream>
using namespace std;

class Song {
	friend ostream& operator<<(ostream& os, const Song& obj);
private:
	string name_;
	string artist_;
	int rating_;
public:
	Song() noexcept = default;
	Song(string name = "Unnamed", string artist = "Unknown", int rating = 0);
	~Song() = default;

	string get_name() const;
	string get_artist() const;
	int get_rating() const;

	bool operator<(const Song& s) const {
		return this->rating_ < s.rating_;
	}
	bool operator==(const Song& s) const {
		return this->artist_ == s.artist_ && this->name_ == s.name_;
	}
};

#endif // !_SONG_H_
