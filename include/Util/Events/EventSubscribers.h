#pragma once

#include "ECS/EventManager.h"
#include "Events.h"

namespace Util {
class TransformEntitySubscriber
    : public ECS::EventSubscriber<TransformEntityEvent> {
  public:
    virtual ~TransformEntitySubscriber() {}

    virtual void receive(ECS::EventManager *eventManager,
                         const TransformEntityEvent &event) override {
        Ogre::SceneNode *node = event.entityNode;

        // Translate
        const Ogre::Vector3 translatedPosition =
            node->getPosition() + event.translation;
        node->setPosition(translatedPosition);

        // Rotate
        node->rotate(Ogre::Vector3::UNIT_X, Ogre::Radian(event.rotation.x));
        node->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(event.rotation.y));
        node->rotate(Ogre::Vector3::UNIT_Z, Ogre::Radian(event.rotation.z));
    }
};

class TestSubscriber : public ECS::EventSubscriber<TestEvent> {
  public:
    virtual ~TestSubscriber() {}

    virtual void receive(ECS::EventManager *eventManager,
                         const TestEvent &event) override {
        std::cout << "TestEvent was emitted with i = " << event.i
                  << ", c = " << event.c << " " << std::endl;
    }
};

class PlaySoundSubscriber : public ECS::EventSubscriber<PlaySoundEvent> {
  public:
    virtual ~PlaySoundSubscriber() {}

    virtual void receive(ECS::EventManager *eventManager,
                         const PlaySoundEvent &event) override {
        (void)event.sound;
    }
};

class RotateCameraSubscriber : public ECS::EventSubscriber<RotateCameraEvent> {
  public:
    virtual ~RotateCameraSubscriber() {}

    virtual void receive(ECS::EventManager *eventManager,
                         const RotateCameraEvent &event) override {
        auto rotate = event.rotate;
        auto node = event.node;
        auto lookAt = event.lookAt;

        auto yaw = rotate.x;
        auto pitch = rotate.y;

        auto orientation = node->getOrientation();

        const auto prevYaw = Ogre::Degree(orientation.getYaw());
        const auto prevPitch = Ogre::Degree(orientation.getPitch());

        node->setPosition(lookAt);
        node->setOrientation(Ogre::Quaternion::IDENTITY);

        //std::cout << "yaw " << yaw << ", pitch " << pitch << std::endl;
        node->yaw(Ogre::Degree(yaw) + prevYaw);
        node->pitch(Ogre::Degree(pitch) + prevPitch);

        node->translate(0.f, 0.f, 100.f,
                        Ogre::SceneNode::TransformSpace::TS_LOCAL);
    }
};
}
