/**
 * @file HW4.h 
 * @author Dhruv Chakraborty
 * @brief Define song and playlist classes to mimic a music player
 * PIC 10C Homework 4
 */

#ifndef HW4_H
#define HW4_H

#include <iostream>
#include <string>
#include <set>

class Playlist;

class Song
{
public: 
    Song() = default; // default constructor
    Song(std::string n); // constructor with name parameter
    Song(const Song& s); // copy construtor
    ~Song(); // destructor
    void save(Playlist& p); // adds song to a playlist passed
    void remove(Playlist& p); // removes song from playlist passed
    void display() const; // prints song info to console
    std::string get_name() const; // returns name of song
    void insert(Playlist* pp); // inserts Playlist pointer to playlists
    void erase(Playlist* pp); // erases Playlist pointer from playlists
private:
    std::string name; // stores name of song
    std::set<Playlist*> playlists; // stores playlists where this song appears
};

class Playlist
{
public:
    Playlist() = default; // default constructor
    Playlist(std::string n); // constructor with name parameter
    Playlist(const Playlist& p); // copy constructor
    Playlist& operator=(const Playlist& p); // copy assignment operator
    ~Playlist(); // destructor
    void save(Song& s); // adds song passed to playlist
    void remove(Song& s); // removes song passed from playlist
    void display() const; // prints playlist info to console
    std::string get_name() const; // returns name of playlist
    void erase(Song* sp); // erases Song pointer from songs
private: 
    std::string name; // stores name of playlist
    std::set<Song*> songs; // stores songs appearing in the playlist
};

#endif