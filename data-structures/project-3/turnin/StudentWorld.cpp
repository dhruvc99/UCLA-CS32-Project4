#include "StudentWorld.h"
#include "GameConstants.h"
#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <list>

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

//

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_Penelope(nullptr), m_levelFinished(false)
{}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    m_levelFinished = false;

    Level level(assetPath());
    
    ostringstream levelStream;
    levelStream << "level";
    levelStream.fill('0');
    levelStream << setw(2) << getLevel() << ".txt";
    string levelFile = levelStream.str();
    
    Level::LoadResult loadResult = level.loadLevel(levelFile);
    
    if (loadResult == Level::load_fail_file_not_found || getLevel() > 99)
    {
        cerr << "You have won the game OR we were not able to find given level file: " << levelFile << endl;
        return GWSTATUS_PLAYER_WON;
    }
    else if (loadResult == Level::load_fail_bad_format)
    {
        cerr << "Your level was improperly formatted" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (loadResult == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        
        for (int y = 0; y < LEVEL_HEIGHT; y++)
        {
            for (int x = 0; x < LEVEL_WIDTH; x++)
            {
                Level::MazeEntry ge = level.getContentsOf(x, y);
                
                switch(ge)
                {
                    case Level::empty:
                        break;
                    case Level::player:
                        m_Penelope = new Penelope(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y);
                        break;
                    case Level::smart_zombie:
                        m_Actors.push_back(new SmartZombie(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::dumb_zombie:
                        m_Actors.push_back(new DumbZombie(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::citizen:
                        m_Actors.push_back(new Citizen(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::exit:
                        m_Actors.push_back(new Exit(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::wall:
                        m_Actors.push_back(new Wall(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::pit:
                        m_Actors.push_back(new Pit(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::vaccine_goodie:
                        m_Actors.push_back(new VaccineGoodie(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::gas_can_goodie:
                        m_Actors.push_back(new GasCanGoodie(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    case Level::landmine_goodie:
                        m_Actors.push_back(new LandmineGoodie(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                }
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_Penelope->doSomething();
    
    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->isDead() == false)
            (*it)->doSomething();
        
        if (m_Penelope->isDead())
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        
        if (isLevelFinished())
            return GWSTATUS_FINISHED_LEVEL;
        
        it++;
    }
    
    list<Actor*>::iterator it_removeDead = m_Actors.begin();
    while (it_removeDead != m_Actors.end())
    {
        if ((*it_removeDead)->isDead())
        {
            delete(*it_removeDead);
            it_removeDead = m_Actors.erase(it_removeDead);
        }
        else
            it_removeDead++;
    }
    
    ostringstream statText;
    statText << "Score: ";
    statText.fill('0');
    if (getScore() < 0)
        statText << "-" << setw(5) << abs(getScore());
    else
        statText << setw(6) << getScore();
    statText << "  Level: " << getLevel();
    statText << "  Lives: " << getLives();
    statText << "  Vaccines: " << m_Penelope->getNumVaccines();
    statText << "  Flames: " << m_Penelope->getNumFlameCharges();
    statText << "  Mines: " << m_Penelope->getNumLandmines();
    statText << "  Infected: " << m_Penelope->getInfectionDuration();
    setGameStatText(statText.str());
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if (m_Penelope != nullptr)
        delete m_Penelope;
    m_Penelope = nullptr;
    
    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        delete(*it);
        it = m_Actors.erase(it); // erase returns it++
    }
}

void StudentWorld::addActor(Actor* a)
{
    m_Actors.push_back(a);
}

bool StudentWorld::isFlameBlockedAt(double x, double y)
{
    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->blocksFlame() && (*it)->isDead() == false)
        {
            if (doesIntersect((*it)->getX(), (*it)->getY(), x, y))
                return true;
        }
        it++;
    }
    
    return false;
}

bool StudentWorld::isZombieVomitTriggerAt(double x, double y) const
{
    if(checkOverlap(x, y, m_Penelope->getX(), m_Penelope->getY()))
        return true;
    
    list<Actor*>::const_iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->isDead() == false && (*it)->triggersZombieVomit())
        {
            if (checkOverlap(x, y, (*it)->getX(), (*it)->getY()))
                return true;
        }
        it++;
    }
    
    return false;
}

bool StudentWorld::checkMove(double x, double y, Actor* actor)
{
    if (actor != m_Penelope) // if agent is not Penelope, make sure agent's target is not Penelope's location
    {
        if (doesIntersect(x, y, m_Penelope->getX(), m_Penelope->getY()) == true)
            return false;
    }

    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->blocksMovement() && (*it)->isDead() == false && (*it) != actor)
        {
            double actor_x = (*it)->getX();
            double actor_xmax = actor_x + SPRITE_WIDTH - 1;
            double actor_y = (*it)->getY();
            double actor_ymax = actor_y + SPRITE_HEIGHT - 1;
        
            if ((x >= actor_x && x <= actor_xmax) && (y >= actor_y && y <= actor_ymax))
                return false;
            if (((x + SPRITE_WIDTH - 1) >= actor_x && (x + SPRITE_WIDTH - 1) <= actor_xmax) && (y >= actor_y && y <= actor_ymax))
                return false;
            if ((x >= actor_x && x <= actor_xmax) && ((y + SPRITE_HEIGHT - 1) >= actor_y && (y + SPRITE_HEIGHT - 1) <= actor_ymax))
                return false;
            if (((x + SPRITE_WIDTH - 1) >= actor_x && (x + SPRITE_WIDTH - 1) <= actor_xmax) &&
                ((y + SPRITE_HEIGHT - 1) >= actor_y && (y + SPRITE_HEIGHT - 1) <= actor_ymax))
                return false;
        }
        it++;
    }
    
    return true;
}

void StudentWorld::activateOnAppropriateActors(Actor* a)
{
    if(checkOverlap(a->getX(), a->getY(), m_Penelope->getX(), m_Penelope->getY()) == true && m_Penelope->isDead() == false)
        a->activateIfAppropriate(m_Penelope);
    
    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if (checkOverlap(a->getX(), a->getY(), (*it)->getX(), (*it)->getY()) == true && (*it)->isDead() == false && (*it) != a)
            a->activateIfAppropriate(*it);
        it++;
    }
}

bool StudentWorld::checkAllCitizensGone()
{
    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->isDead() == false && (*it)->triggersZombieVomit())
            return false;
        it++;
    }
    return true;
}

void StudentWorld::recordLevelFinishedIfAllCitizensGone()
{
    m_levelFinished = true;
}

bool StudentWorld::isLevelFinished()
{
    return m_levelFinished;
}

double StudentWorld::squaredDistanceBetween(double x1, double y1, double x2, double y2) const
{
    return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
}

bool StudentWorld::checkOverlap(double x1, double y1, double x2, double y2) const
{
    return squaredDistanceBetween(x1, y1, x2, y2) <= 100;
}

bool StudentWorld::doesIntersect(double x1, double y1, double x2, double y2) const
{
    if (abs(x1 - x2) < SPRITE_WIDTH && abs(y1 - y2) < SPRITE_HEIGHT)
        return true;
    else
        return false;
}


bool StudentWorld::locateNearestVomitTrigger(double x, double y, double &otherX, double &otherY, double &distance)
{
    Actor* nearestActor = m_Penelope;
    double nearestDist = sqrt(squaredDistanceBetween(x, y, nearestActor->getX(), nearestActor->getY()));
    
    list<Actor*>::iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->isDead() == false && (*it)->triggersZombieVomit())
        {
            double distToHuman = sqrt(squaredDistanceBetween(x, y, (*it)->getX(), (*it)->getY()));
            if (distToHuman < nearestDist)
            {
                nearestActor = (*it);
                nearestDist = distToHuman;
            }
        }
        it++;
    }
    
    if (nearestDist <= 80)
    {
        otherX = nearestActor->getX();
        otherY = nearestActor->getY();
        distance = nearestDist;
        return true;
    }
    
    return false;
}

bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double &otherX, double &otherY, double &distance, bool &isThreat) const
{
    double distToPenelope = 80;
    if (m_Penelope != nullptr)
        distToPenelope = sqrt(squaredDistanceBetween(x, y, m_Penelope->getX(), m_Penelope->getY()));
    
    double nearestZombieX = 0;
    double nearestZombieY = 0;
    double distToNearestZombie = 0;
    
    if (locateNearestCitizenThreat(x, y, nearestZombieX, nearestZombieY, distToNearestZombie) == true)
    {
        if (distToNearestZombie <= distToPenelope)
        {
            otherX = nearestZombieX;
            otherY = nearestZombieY;
            distance = distToNearestZombie;
            isThreat = true;
            return true;
        }
    }
    
    if (m_Penelope != nullptr)
    {
        otherX = m_Penelope->getX();
        otherY = m_Penelope->getY();
        distance = distToPenelope;
        isThreat = false;
        return true;
    }
    
    return false;
}

bool StudentWorld::locateNearestCitizenThreat(double x, double y, double &otherX, double &otherY, double &distance) const
{
    Actor* nearestActor = nullptr;
    double nearestDist = 10000000;
    
    list<Actor*>::const_iterator it = m_Actors.begin();
    while (it != m_Actors.end())
    {
        if ((*it)->isDead() == false && (*it)->triggersCitizens())
        {
            double distToZombie = sqrt(squaredDistanceBetween(x, y, (*it)->getX(), (*it)->getY()));
            if (distToZombie < nearestDist)
            {
                nearestActor = (*it);
                nearestDist = distToZombie;
            }
        }
        it++;
    }
    
    if (nearestActor != nullptr)
    {
        otherX = nearestActor->getX();
        otherY = nearestActor->getY();
        distance = nearestDist;
        return true;
    }
    
    return false;
}
