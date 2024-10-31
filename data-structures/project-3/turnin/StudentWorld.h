#ifndef STUDENTWORLD_INCLUDED
#define STUDENTWORLD_INCLUDED

#include "GameWorld.h"
#include <string>
#include <list>
using namespace std;

class Actor;
class Penelope;

class StudentWorld: public GameWorld
{
public:
    StudentWorld(string assetPath);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    void addActor(Actor* a);
    
    bool checkMove(double x, double y, Actor* actor);
    
    bool isFlameBlockedAt(double x, double y);
    
    bool isZombieVomitTriggerAt(double x, double y) const;
    
      // Is an agent blocked from moving to the indicated location?
    // bool isAgentMovementBlockedAt(double x, double y, Actor* a) const;
    
      // For each actor overlapping a, activate a if appropriate.
    void activateOnAppropriateActors(Actor* a);
    
    bool checkAllCitizensGone();
    
    void recordLevelFinishedIfAllCitizensGone();
    
    bool isLevelFinished();
    
    bool checkOverlap(double x1, double y1, double x2, double y2) const;
    
    double squaredDistanceBetween(double x1, double y1, double x2, double y2) const;
    
    bool doesIntersect(double x1, double y1, double x2, double y2) const;
    
      // Return true if there is a living human within 80 pixels, otherwise false.  If true,
      // otherX, otherY, and distance will be set to the location and distance
      // of the human nearest to (x,y).
    bool locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance);

      // Return true if there is a living zombie or Penelope, otherwise false.
      // If true, otherX, otherY, and distance will be set to the location and
      // distance of the one nearest to (x,y), and isThreat will be set to true
      // if it's a zombie, false if a Penelope.
    bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const;

      // Return true if there is a living zombie, false otherwise.  If true,
      // otherX, otherY and distance will be set to the location and distance
      // of the one nearest to (x,y).
    bool locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const;
    
private:
    list<Actor*> m_Actors;
    Penelope* m_Penelope;
    bool m_levelFinished;
};

#endif // STUDENTWORLD_INCLUDED
