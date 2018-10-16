#pragma once

#include <GameObjects/GenericObject.h>

#include <Physics/BulletContactCallback.h>

#include <Ogre.h>
#include <OgreSceneManager.h>

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "BulletCollision/CollisionDispatch/btCollisionObject.h"

namespace Game
{
class GameState;

class GameObject : public Util::GenericObject
{
    public:
    GameObject(Ogre::SceneNode* parent,
               ECS::EventManager* eventManager,
               btDiscreteDynamicsWorld* world,
               Ogre::Entity* entity,
               const Ogre::String& material,
               float scale,
               const btTransform& transform);

    // From GenericObject
    virtual void update(float dt) override;
    virtual void setTransform(const btTransform& newTransform) override;

    virtual void updateTransform();
    virtual void applyImpulse(const btVector3& impulse);

    virtual void handleCollision();

    void addToGame(GameState* gameState);

    protected:
    std::size_t mGameID;
    GameState* mGameState;
    btDiscreteDynamicsWorld* mWorld;
};
} // namespace Game
