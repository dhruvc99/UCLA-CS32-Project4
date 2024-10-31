#include<iostream>
#include"HW4.h"
using namespace std;

int main()
{
    cout << "********************* Create Songs *************************" << endl;
    // create songs
    Song rm("remember me");
    Song lig("let it go");
    Song fh("frozen heart");
    Song laa("lisa and anna");
    // create playlists
    Playlist playlist1("Frozen"); // frozen
    Playlist playlist2("Favorites"); // favorites
    // assign songs to playlists
    lig.save(playlist1); fh.save(playlist1);
    rm.save(playlist2); lig.save(playlist2);
    playlist1.save(laa);
    // print info
    lig.display();
    playlist1.display();
    playlist2.display();
    
    cout << "********************* Create Song Copies *************************" << endl;
    // create some copies
    Song c1(fh);
    //rm = laa; // cause error
    playlist1.display();
    
    cout << "********************* Create Playlist Copies *************************" << endl;
    // create some copies
    Playlist p3(playlist1);
    playlist2 = playlist1;
    p3.display();
    fh.display();
    
    cout << "********************* Remove items *************************" << endl;
    playlist1.remove(lig);
    lig.remove(playlist1);
    playlist1.display();
    playlist2.display();


    return 0;
}

