#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"

// ====================================Actor's implementations:====================================

Actor::Actor(StudentWorld* w, int imageID, double x, double y, int dir, int depth) :
    GraphObject(imageID, x, y, dir, depth), m_world(w), m_dead(false)
{}

StudentWorld* Actor::world() const
{
    return m_world;
}

bool Actor::isDead() const
{
    return m_dead;
}

void Actor::setDead()
{
    m_dead = true;
}

bool Actor::blocksMovement() const
{
    return false;
}

bool Actor::blocksFlame() const
{
    return false;
}

bool Actor::triggersOnlyActiveLandmines() const
{
    return false;
}

bool Actor::triggersZombieVomit() const
{
    return false;
}

bool Actor::threatensCitizens() const
{
    return false;
}

bool Actor::triggersCitizens() const
{
    return false;
}

void Actor::activateIfAppropriate(Actor *a)
{}

void Actor::useExitIfAppropriate()
{}

void Actor::dieByFallOrBurnIfAppropriate()
{}

void Actor::beVomitedOnIfAppropriate()
{}

void Actor::pickUpGoodieIfAppropriate(Goodie* g)
{}

// ====================================Wall's implementations:====================================

Wall::Wall(StudentWorld* w, double x, double y) :
    Actor(w, IID_WALL, x, y, right, 0)
{}

void Wall::doSomething()
{}

bool Wall::blocksMovement() const
{
    return true;
}

bool Wall::blocksFlame() const
{
    return true;
}

// ====================================ActivatingObject's implementations:====================================

ActivatingObject::ActivatingObject(StudentWorld* w, int imageID, double x, double y, int depth, int dir) :
    Actor(w, imageID, x, y, dir, depth)
{}

void ActivatingObject::doSomething() 
{
    if (isDead() == false)
        world()->activateOnAppropriateActors(this);
}

// ====================================Exit's implementations:====================================

Exit::Exit(StudentWorld* w, double x, double y) :
    ActivatingObject(w, IID_EXIT, x, y, 1, right)
{}

// void Exit::doSomething() {}

void Exit::activateIfAppropriate(Actor *a)
{
    a->useExitIfAppropriate();
}

bool Exit::blocksFlame() const
{
    return true;
}

// ====================================Pit's implementations:====================================

Pit::Pit(StudentWorld* w, double x, double y) :
    ActivatingObject(w, IID_PIT, x, y, 0, right)
{}

// void Pit::doSomething() {}

void Pit::activateIfAppropriate(Actor *a)
{
    a->dieByFallOrBurnIfAppropriate();
}

// ====================================Projectile's implementations:====================================

Projectile::Projectile(StudentWorld* w, int imageID, double x, double y, int dir) :
    ActivatingObject(w, imageID, x, y, 0, dir), m_tickCount(2)
{}

void Projectile::doSomething()
{
    if (isDead() == false)
    {
        m_tickCount--;
        if (m_tickCount == 0)
        {
            setDead();
            return;
        }
        world()->activateOnAppropriateActors(this);
    }
}

void Projectile::activateifAppropriate(Actor *a)
{}

// ====================================Flame's implementations:====================================

Flame::Flame(StudentWorld* w, double x, double y, int dir) :
    Projectile(w, IID_FLAME, x, y, dir)
{
    cerr << "flame has been created" << endl;
}

// void Flame::doSomething() {}

void Flame::activateIfAppropriate(Actor *a)
{
    a->dieByFallOrBurnIfAppropriate();
}

// ====================================Vomit's implementations:====================================

Vomit::Vomit(StudentWorld* w, double x, double y, int dir) :
    Projectile(w, IID_VOMIT, x, y, dir)
{}

// void Vomit::doSomething() {}

void Vomit::activateIfAppropriate(Actor *a)
{
    a->beVomitedOnIfAppropriate();
}

// ====================================Landmine's implementations:====================================

Landmine::Landmine(StudentWorld* w, double x, double y) :
    ActivatingObject(w, IID_LANDMINE, x, y, 1, right), m_safetyTicks(30), m_active(false)
{}

void Landmine::doSomething()
{
    if (isDead() == false)
    {
        if (m_active == false)
        {
            m_safetyTicks--;
            if (m_safetyTicks == 0)
                m_active = true;
            return;
        }
        world()->activateOnAppropriateActors(this);
    }
}

void Landmine::activateIfAppropriate(Actor *a)
{
    if (a->triggersOnlyActiveLandmines())
        dieByFallOrBurnIfAppropriate();
}

void Landmine::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_LANDMINE_EXPLODE);
    
    double x = getX() - SPRITE_WIDTH;
    double y = getY() - SPRITE_HEIGHT;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (world()->isFlameBlockedAt(x + i * SPRITE_WIDTH, y + j * SPRITE_HEIGHT))
                world()->addActor(new Flame(world(), (x + i * SPRITE_WIDTH), (y + j * SPRITE_HEIGHT), up));
        }
    }
    
    world()->addActor(new Pit(world(), getX(), getY()));
}

// ====================================Goodie's implementations:====================================

Goodie::Goodie(StudentWorld* w, int imageID, double x, double y) :
    ActivatingObject(w, imageID, x, y, 1, right)
{}

void Goodie::doSomething()
{
    if (isDead() == false)
        world()->activateOnAppropriateActors(this);
}

void Goodie::activateIfAppropriate(Actor *a)
{
    a->pickUpGoodieIfAppropriate(this);
    setDead();
    world()->increaseScore(40);
    world()->playSound(SOUND_GOT_GOODIE);
}

void Goodie::dieByFallOrBurnIfAppropriate()
{
    setDead();
}

// ====================================VaccineGoodie's implementations:====================================

VaccineGoodie::VaccineGoodie(StudentWorld* w, double x, double y) :
    Goodie(w, IID_VACCINE_GOODIE, x, y)
{}

// void VaccineGoodie::doSomething() {}

void VaccineGoodie::pickUp(Penelope *p)
{
    p->increaseVaccines();
}

// ====================================GasCanGoodie's implementations:====================================

GasCanGoodie::GasCanGoodie(StudentWorld* w, double x, double y) :
    Goodie(w, IID_GAS_CAN_GOODIE, x, y)
{}

// void GasCanGoodie::doSomething() {}

void GasCanGoodie::pickUp(Penelope *p)
{
    p->increaseFlameCharges();
}

// ====================================LandmineGoodie's implementations:====================================

LandmineGoodie::LandmineGoodie(StudentWorld* w, double x, double y) :
    Goodie(w, IID_LANDMINE_GOODIE, x, y)
{}

// void LandmineGoodie::doSomething() {}

void LandmineGoodie::pickUp(Penelope *p)
{
    p->increaseLandmines();
}

// ====================================Agent's implementations:====================================

Agent::Agent(StudentWorld* w, int imageID, double x, double y, int dir) :
    Actor(w, imageID, x, y, dir, 0), m_paralyzed(false)
{}

bool Agent::blocksMovement() const
{
    return true;
}

bool Agent::triggersOnlyActiveLandmines() const
{
    return true;
}

void Agent::setParalyzed(bool paralyzed)
{
    m_paralyzed = paralyzed;
}

bool Agent::getParalyzed() const
{
    return m_paralyzed;
}

// ====================================Human's implementations:====================================

Human::Human(StudentWorld* w, int imageID, double x, double y) :
    Agent(w, imageID, x, y, right), m_infected(false), m_infectionCount(0)
{}

void Human::beVomitedOnIfAppropriate()
{
    if (isInfected() == false)
        m_infected = true;
}

bool Human::isInfected() const
{
    return m_infected;
}

bool Human::triggersZombieVomit() const
{
    return true;
}

void Human::clearInfection()
{
    m_infected = false;
}

bool Human::getInfectionDuration()
{
    if (isInfected() == true)
        m_infectionCount++;
    if (m_infectionCount >= 500)
    {
        dieByInfection();
        return true;
    }
    return false;
}

// ====================================Penelope's implementations:====================================

Penelope::Penelope(StudentWorld* w, double x, double y) :
    Human(w, IID_PLAYER, x, y), m_numVaccines(0), m_numFlameCharges(0), m_numLandmines(0)
{}

void Penelope::doSomething()
{
    int key;
    if (world()->getKey(key))
    {
        switch(key)
        {
        case KEY_PRESS_LEFT:
            setDirection(left);
            if (world()->checkMove(getX() - STEP, getY(), this))
                moveTo(getX() - STEP, getY());
            break;

        case KEY_PRESS_RIGHT:
            setDirection(right);
            if (world()->checkMove(getX() + STEP, getY(), this))
                moveTo(getX() + STEP, getY());
            break;

        case KEY_PRESS_UP:
            setDirection(up);
            if (world()->checkMove(getX(), getY() + STEP, this))
                moveTo(getX(), getY() + STEP);
            break;

        case KEY_PRESS_DOWN:
            setDirection(down);
            if (world()->checkMove(getX(), getY() - STEP, this))
                moveTo(getX(), getY() - STEP);
            break;
        
        case KEY_PRESS_SPACE:
            if (getNumFlameCharges() > 0)
            {
                m_numFlameCharges--;
                world()->playSound(SOUND_PLAYER_FIRE);
                
                double targetX = getX();
                double targetY = getY();
                
                Direction d = getDirection();
                cerr << "1" << endl;
                for (int i = 0; i < 3; i++)
                { cerr << "2" << endl;
                    switch(d)
                    {
                        case up:
                            targetY += SPRITE_HEIGHT;
                            break;
                        case right:
                            targetX += SPRITE_WIDTH;
                            break;
                        case down:
                            targetY -= SPRITE_HEIGHT;
                            break;
                        case left:
                            targetX -= SPRITE_WIDTH;
                            break;
                    }
                    cerr << "3" << endl;
                    if (world()->isFlameBlockedAt(targetX, targetY) == false)
                    { cerr << "4" << endl;
                        world()->addActor(new Flame(world(), targetX, targetY, d));
                        }
                    else
                        break;
                }
            }
            break;
        
        case KEY_PRESS_ENTER:
            if (getNumVaccines() > 0)
            {
                clearInfection();
                m_numVaccines--;
            }
            break;
            
        case KEY_PRESS_TAB:
            if (getNumLandmines() > 0)
            {
                world()->addActor(new Landmine(world(), getX(), getY()));
                m_numLandmines--;
            }
        }
    }
}

void Penelope::dieByInfection()
{
    setDead();
    world()->playSound(SOUND_PLAYER_DIE);
}

bool Penelope::triggersCitizens() const
{
    return true;
}

void Penelope::useExitIfAppropriate()
{
    if (world()->checkAllCitizensGone())
    {
        world()->playSound(SOUND_LEVEL_FINISHED);
        world()->recordLevelFinishedIfAllCitizensGone();
    }
}

void Penelope::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_PLAYER_DIE);
}

void Penelope::pickUpGoodieIfAppropriate(Goodie *g)
{
    g->pickUp(this);
}

void Penelope::increaseVaccines()
{
    m_numVaccines++;
}

void Penelope::increaseFlameCharges()
{
    m_numFlameCharges += 5;
}

void Penelope::increaseLandmines()
{
    m_numLandmines += 2;
}

int Penelope::getNumVaccines() const
{
    return m_numVaccines;
}

int Penelope::getNumFlameCharges() const
{
    return m_numFlameCharges;
}

int Penelope::getNumLandmines() const
{
    return m_numLandmines;
}

// ====================================Citizen's implementations:====================================

Citizen::Citizen(StudentWorld* w, double x, double y) :
    Human(w, IID_CITIZEN, x, y)
{}

void Citizen::doSomething()
{

}

void Citizen::useExitIfAppropriate()
{
    setDead();
    world()->increaseScore(500);
    world()->playSound(SOUND_CITIZEN_SAVED);
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->increaseScore(-1000);
    world()->playSound(SOUND_CITIZEN_DIE);
}

void Citizen::dieByInfection()
{
    setDead();
    world()->increaseScore(-1000);
    
    int dumbOrSmart = randInt(0, 9);
    if (dumbOrSmart < 3)
        world()->addActor(new SmartZombie(world(), getX(), getY()));
    else
        world()->addActor(new DumbZombie(world(), getX(), getY()));
    
    world()->playSound(SOUND_ZOMBIE_BORN);
}

void Citizen::beVomitedOnIfAppropriate()
{
    if (isInfected() == false)
    {
        Human::beVomitedOnIfAppropriate();
        world()->playSound(SOUND_CITIZEN_INFECTED);
    }
}
// ====================================Zombie's implementations:====================================

Zombie::Zombie(StudentWorld* w, double x, double y) :
    Agent(w, IID_ZOMBIE, x, y, right)
{}

bool Zombie::triggersCitizens() const
{
    return true;
}

bool Zombie::threatensCitizens() const
{
    return true;
}

// ====================================DumbZombie's implementations:====================================

DumbZombie::DumbZombie(StudentWorld* w, double x, double y) :
    Zombie(w, x, y)
{}

void DumbZombie::doSomething()
{

}

void DumbZombie::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_ZOMBIE_DIE);
    world()->increaseScore(1000);
}

// ====================================SmartZombie's implementations:====================================

SmartZombie::SmartZombie(StudentWorld* w, double x, double y) :
    Zombie(w, x, y)
{}

void SmartZombie::doSomething()
{

}

void SmartZombie::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_ZOMBIE_DIE);
    world()->increaseScore(2000);
}
