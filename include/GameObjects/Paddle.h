#pragma once

#include <Ogre.h>
#include <OgreVector3.h>

#include "ECS/EventManager.h"

#include "Util/Events/EventSubscribers.h"
#include "Util/Events/Events.h"

#include "GameObject.h"

namespace Game
{
class Paddle : public GameObject
{
    public:
    Paddle (Ogre::SceneManager* scnMgr,
            Ogre::SceneNode* parent,
            ECS::EventManager* eventManager,
            btDiscreteDynamicsWorld* world,
            const Ogre::String& material,
            float scale,
            const btTransform& pos);

    ~Paddle ()
    {
    }

    void handleCollision () override;
};
} // namespace Game
