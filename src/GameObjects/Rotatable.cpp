#include "GameObjects/Rotatable.h"

#include <cmath>

namespace Game
{
Rotatable::Rotatable (Ogre::SceneNode* camNode, Ogre::Real radius, ECS::EventManager* eventManager)
: mNode (camNode), mRadius (radius)
{

    eventManager->connect<Util::RotateEvent> (this);

    mNode->setPosition (0.f, 0.f, -mRadius);
    mNode->lookAt (Ogre::Vector3 (0.f, 0.f, 0.f), Ogre::SceneNode::TransformSpace::TS_PARENT);
}

void Rotatable::rotateThis (Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll)
{
    const Ogre::Vector3& prevPos = mNode->getPosition ();

    mNode->setPosition (Ogre::Vector3::ZERO);

    mNode->rotate (Ogre::Quaternion (yaw, Ogre::Vector3::UNIT_Y));

    /*
    const auto curPitch = mNode->getOrientation().getPitch();
    if (abs((curPitch + pitch).valueRadians()) > maxPitch) {
        mNode->rotate(Ogre::Quaternion((curPitch.valueRadians() > 0 ? 1 : -1) *
    Ogre::Radian(maxPitch) - curPitch, Ogre::Vector3::UNIT_X));
    }
    else {
        mNode->rotate(Ogre::Quaternion(pitch, Ogre::Vector3::UNIT_X));
    }

    //mNode->rotate(Ogre::Quaternion(roll, Ogre::Vector3::UNIT_Z));
    */

    mNode->translate (mNode->getLocalAxes (), Ogre::Vector3 (0.f, 0.f, mRadius),
                      Ogre::SceneNode::TransformSpace::TS_PARENT);
}

void Rotatable::receive (ECS::EventManager* em, const Util::RotateEvent& event)
{
    if (mNode != event.node)
    {
        return;
    }

    const auto rotate = event.rotate;
    const auto lookAt = event.lookAt;

    const auto yaw = Ogre::Radian (rotate.x);
    const auto pitch = Ogre::Radian (rotate.y);
    const auto roll = Ogre::Radian (rotate.z);

    rotateThis (yaw, pitch, roll);
}
} // namespace Game
