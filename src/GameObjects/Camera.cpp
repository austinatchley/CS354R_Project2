#include "GameObjects/Camera.h"

namespace Game {
Camera::Camera(Ogre::SceneNode* camNode, Ogre::Real radius, ECS::EventManager* eventManager)
    : mNode(camNode), mRadius(radius) {
    eventManager->connect<Util::RotateCameraEvent>(this);

    mNode->setPosition(0.f, 0.f, -mRadius);
}

void Camera::rotateThis(Ogre::Radian pitch, Ogre::Radian yaw, Ogre::Radian roll) {
    Ogre::Vector3 prevPos = mNode->getPosition();

    mNode->setPosition(Ogre::Vector3::ZERO);
    
    mNode->yaw(yaw);
    mNode->pitch(pitch);
    mNode->roll(roll);

    mNode->translate(0.f, 0.f, -mRadius, Ogre::SceneNode::TransformSpace::TS_LOCAL);

    Ogre::Vector3 postPos = mNode->getPosition();

    std::cout << "Prev Position: " << prevPos << "\nPost Position: " << postPos << std::endl;
}

void Camera::receive(ECS::EventManager *em, const Util::RotateCameraEvent& event) {
    if (mNode != event.node) {
        return;
    }

    const auto rotate = event.rotate;
    const auto lookAt = event.lookAt;

    const auto yaw = Ogre::Radian(rotate.x);
    const auto pitch = Ogre::Radian(rotate.y);

    rotateThis(pitch, yaw, Ogre::Radian());
}
}
