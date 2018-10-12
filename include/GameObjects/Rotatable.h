#pragma once

#include <Ogre.h>

#include <ECS/EventManager.h>
#include <Util/Events/EventSubscribers.h>

namespace Game {

// This class is a wrapper for the SceneNode with an attached Rotatable (the
// one provided by Ogre). If you wish to move the camera, attach it to another
// SceneNode and move the parent. This class operates in the local space.
class Rotatable
    : public ECS::EventSubscriber<Util::RotateRotatableEvent>
{
public:
    Rotatable(Ogre::SceneNode* camNode, Ogre::Real radius, ECS::EventManager* eventManager);
    ~Rotatable() {}

    void rotateThis(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll);

    void receive(ECS::EventManager *em, const Util::RotateRotatableEvent& evt) override;

private:
    Ogre::SceneNode* mNode;
    Ogre::Real mRadius;

    //const Ogre::Real maxPitch = Ogre::Math::HALF_PI / 4.f;
};
}
