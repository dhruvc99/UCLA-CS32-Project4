/**
 * @file HW4.cpp
 * @author Dhruv Chakraborty
 * @brief Implement song and playlist classes that mimic a music player
 * PIC 10C Homework 4
 */

#include "HW4.h"
#include <iostream>
#include <string>
#include <set>

// ********************
// Song implementations
// ********************

/**
 * @brief Construct a new named Song object
 * 
 * @param n: name of song
 */
Song::Song(std::string n): name(n) 
{}

/**
 * @brief Copy construct a new Song object, appending copy to its name
 * 
 * @param s: song to copy
 */
Song::Song(const Song& s)
{
    name = s.name + " copy";
    for (auto iter = s.playlists.begin(); iter != s.playlists.end(); iter++)
    {
        (*iter)->save(*this); 
        playlists.insert(*iter);
    }
}

/**
 * @brief Destroy Song object
 * 
 */
Song::~Song()
{
    for (auto iter = playlists.begin(); iter != playlists.end(); iter++)
    {
        (*iter)->erase(this);
    }
} 

/**
 * @brief Save song to given playlist
 * 
 * @param p: playlist to save song to
 */
void Song::save(Playlist& p)
{
    p.save(*this);
}

/**
 * @brief Remove song from given playlist
 * 
 * @param p: playlist to remove song from
 */
void Song::remove(Playlist& p)
{
    p.remove(*this);
}

/**
 * @brief Print song information to console
 * 
 */
void Song::display() const
{
    std::cout << "Song \"" << name << "\" appears in " << playlists.size() << " folders." << std::endl;
    int counter = 1;
    for (auto iter = playlists.begin(); iter != playlists.end(); iter++)
    {
        std::cout << "\tPlaylist " << counter << ": " << (*iter)->get_name() << std::endl;
        counter++;
    }
}

/**
 * @brief Returns name of song
 * 
 * @return std::string 
 */
std::string Song::get_name() const
{
    return name;
}

/**
 * @brief Inserts playlist pointer to set of playlists
 * 
 * @param pp: pointer to playlist song is added to
 */
void Song::insert(Playlist* pp)
{
    playlists.insert(pp);
}

/**
 * @brief Erases playlist pointer from set of playlists
 * 
 * @param pp: pointer to playlist song is removed from
 */
void Song::erase(Playlist* pp)
{
    playlists.erase(pp);
}

// ************************
// Playlist implementations
// ************************

/**
 * @brief Construct a new named Playlist object
 * 
 * @param n: name of playlist
 */
Playlist::Playlist(std::string n): name(n)
{} 

/**
 * @brief Copy construct a new Playlist object, appending copy to its name
 * 
 * @param p: playlist to copy
 */
Playlist::Playlist(const Playlist& p)
{
    name = p.name + " copy";
    for (auto iter = p.songs.begin(); iter != p.songs.end(); iter++)
    {
        (*iter)->save(*this);
        songs.insert(*iter);
    }
}

/**
 * @brief Overloaded copy assignment operator for Playlists
 * 
 * @param p: playlist being assigned
 * @return Playlist& 
 */
Playlist& Playlist::operator=(const Playlist& p)
{
    for (auto iter = songs.begin(); iter != songs.end(); iter++)
    {
        (*iter)->erase(this);
    }
    songs.clear();

    name = p.name + " copy";
    for (auto iter = p.songs.begin(); iter != p.songs.end(); iter++)
    {
        (*iter)->save(*this);
        songs.insert(*iter);
    }

    return *this; 
}

/**
 * @brief Destroy Playlist object
 * 
 */
Playlist::~Playlist()
{
    for (auto iter = songs.begin(); iter != songs.end(); iter++)
    {
        (*iter)->erase(this);
    }
}

/**
 * @brief Save given song to playlist
 * 
 * @param s: song to save
 */
void Playlist::save(Song& s)
{
    s.insert(this);
    songs.insert(&s);
}

/**
 * @brief Remove given song from playlist
 * 
 * @param s: song to remove
 */
void Playlist::remove(Song& s)
{
    s.erase(this);
    songs.erase(&s);
}

/**
 * @brief Print playlist information to console
 * 
 */
void Playlist::display() const
{
    std::cout << "Playlist \"" << name << "\" contains " << songs.size() << " songs." << std::endl;
    int counter = 1;
    for (auto iter = songs.begin(); iter != songs.end(); iter++)
    {
        std::cout << "\tSong " << counter << ":     " << (*iter)->get_name() << std::endl;
        counter++;
    }
}

/**
 * @brief Returns playlist name
 * 
 * @return std::string 
 */
std::string Playlist::get_name() const
{
    return name;
}

/**
 * @brief Erases song pointer from set of songs
 * 
 * @param sp: pointer to song being removed from playlist
 */
void Playlist::erase(Song* sp)
{
    songs.erase(sp);
}