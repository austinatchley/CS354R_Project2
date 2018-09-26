#pragma once

#include <vector>

#include <Ogre.h>

#include "GameObjects/GameObject.h"

#include "ECS/EventManager.h"
#include "Events/Events.h"
#include "Events/EventSubscribers.h"

namespace Game
{
    class Ball
        : public GameObject
    {
    public:
        Ball(
            Ogre::SceneManager* scnMgr,
            float radius, 
            const Ogre::String& material,
            const Ogre::Vector3& velocity
        );
                    
        ~Ball() {}

        Ogre::SceneNode* getNode();
        const Ogre::Vector3& getVelocity();
        void setVelocity(const Ogre::Vector3& newVel);

        void move(const std::vector<Ogre::Plane>& walls, ECS::EventManager* eventManager, const Ogre::Real dt);

    private:
        Ogre::SceneNode* mNode;
        Ogre::Real mRadius;
        Ogre::String mMaterial;
        Ogre::Vector3 mVelocity;
    };
}
