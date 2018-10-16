#pragma once

#include <Ogre.h>

#include "ECS/EventManager.h"
#include "Util/Util.h"

namespace Util
{
class TestEvent : public ECS::BaseEvent
{
    public:
    TestEvent(int pi, char pc) : i(pi), c(pc)
    {
    }
    ~TestEvent()
    {
    }

    int i;
    char c;
};

class TransformEntityEvent : public ECS::BaseEvent
{
    public:
    TransformEntityEvent(Ogre::SceneNode* e, Ogre::Vector3 t, Ogre::Vector3 r)
    : entityNode(e), translation(t), rotation(r)
    {
    }
    ~TransformEntityEvent()
    {
    }

    Ogre::SceneNode* entityNode;
    Ogre::Vector3 translation;
    Ogre::Vector3 rotation;
};

class RotateEntityEvent : public TransformEntityEvent
{
    public:
    RotateEntityEvent(Ogre::SceneNode* n, Ogre::Vector3 r)
    : TransformEntityEvent(n, Ogre::Vector3::ZERO, r)
    {
    }
};

class TranslateEntityEvent : public TransformEntityEvent
{
    public:
    TranslateEntityEvent(Ogre::SceneNode* n, Ogre::Vector3 t)
    : TransformEntityEvent(n, t, Ogre::Vector3::ZERO)
    {
    }
};

class RotateEvent : public ECS::BaseEvent
{
    public:
    RotateEvent(Ogre::SceneNode* n, const Ogre::Vector3& r, const Ogre::Vector3& l)
    : node(n), rotate(r), lookAt(l)
    {
    }
    ~RotateEvent()
    {
    }

    Ogre::SceneNode* node;
    Ogre::Vector3 rotate;
    Ogre::Vector3 lookAt;
};

class PlaySoundEvent : public ECS::BaseEvent
{
    public:
    PlaySoundEvent(Util::Sound s) : sound(s)
    {
    }

    Util::Sound sound;
};

class ToggleSoundEvent : public ECS::BaseEvent
{
    public:
    ToggleSoundEvent()
    {
    }
};
} // namespace Util
