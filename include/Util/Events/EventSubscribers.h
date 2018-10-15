#pragma once

#include "ECS/EventManager.h"
#include "Events.h"

namespace Util
{
class TransformEntitySubscriber : public ECS::EventSubscriber<TransformEntityEvent>
{
    public:
    virtual ~TransformEntitySubscriber()
    {
    }

    virtual void receive(ECS::EventManager* eventManager, const TransformEntityEvent& event) override
    {
        Ogre::SceneNode* node = event.entityNode;

        // Translate
        const Ogre::Vector3 translatedPosition = node->getPosition() + event.translation;
        node->setPosition(translatedPosition);

        // Rotate
        node->rotate(Ogre::Vector3::UNIT_X, Ogre::Radian(event.rotation.x));
        node->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(event.rotation.y));
        node->rotate(Ogre::Vector3::UNIT_Z, Ogre::Radian(event.rotation.z));
    }
};

class TestSubscriber : public ECS::EventSubscriber<TestEvent>
{
    public:
    virtual ~TestSubscriber()
    {
    }

    virtual void receive(ECS::EventManager* eventManager, const TestEvent& event) override
    {
        std::cout << "TestEvent was emitted with i = " << event.i << ", c = " << event.c << " " << std::endl;
    }
};

class PlaySoundSubscriber : public ECS::EventSubscriber<PlaySoundEvent>
{
    public:
    virtual ~PlaySoundSubscriber()
    {
    }

    virtual void receive(ECS::EventManager* eventManager, const PlaySoundEvent& event) override
    {
        (void)event.sound;
    }
};

class RotateSubscriber : public ECS::EventSubscriber<RotateEvent>
{
    public:
    virtual ~RotateSubscriber()
    {
    }

    virtual void receive(ECS::EventManager* eventManager, const RotateEvent& event) override
    {
        auto rotate = event.rotate;
        auto node = event.node;
        auto lookAt = event.lookAt;

        auto yaw = Ogre::Radian(rotate.x);
        auto pitch = Ogre::Radian(rotate.y);

        auto orientation = node->getOrientation();

        const Ogre::Radian prevYaw = orientation.getYaw();
        const Ogre::Radian prevPitch = orientation.getPitch();

        node->setPosition(lookAt);
        node->setOrientation(Ogre::Quaternion::IDENTITY);

        node->yaw(-1 * yaw + prevYaw);
        node->pitch(-1 * pitch + prevPitch);

        node->translate(0.f, 0.f, 100.f, Ogre::SceneNode::TransformSpace::TS_LOCAL);
    }
};
} // namespace Util
