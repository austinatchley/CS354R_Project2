#include <GameObjects/Ground.h>

namespace Game
{
Ground::Ground (Ogre::SceneManager* scnMgr,
                ECS::EventManager* eventManager,
                btDiscreteDynamicsWorld* world,
                const Ogre::String& material)
: GameObject (scnMgr->getRootSceneNode (),
              eventManager,
              world,
              scnMgr->createEntity (Ogre::SceneManager::PT_PLANE),
              material,
              1000,
              btTransform::getIdentity ())
{
    // set to static
    mInertia.setZero ();
    mMass = 0.f;
    mStatic = true;

    mShape = new btBoxShape (btVector3 (1000, 1000, 10));

    mTransform.setIdentity ();
    mTransform.setRotation (btQuaternion (btVector3 (1, 0, 0), -Ogre::Math::HALF_PI));
}

// void Ground::handleCollision() {}
} // namespace Game
