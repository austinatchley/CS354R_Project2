#include <GameObjects/Paddle.h>

#define THICKNESS 1.f / 6.f

namespace Game
{
Paddle::Paddle (Ogre::SceneManager* scnMgr,
                Ogre::SceneNode* parent,
                ECS::EventManager* eventManager,
                btDiscreteDynamicsWorld* world,
                const Ogre::String& material = "Examples/"
                                               "SphereMappedRustySteel",
                float scale = 1.f,
                const btTransform& trans = btTransform::getIdentity ())
: GameObject (parent ? parent : scnMgr->getRootSceneNode (),
              eventManager,
              world,
              scnMgr->createEntity (Ogre::SceneManager::PT_CUBE),
              material,
              scale,
              trans)
{
    mNode->setScale (scale * THICKNESS / 100.f, scale / 100.f, scale / 100.f);
    mShape = new btBoxShape (btVector3 (scale * THICKNESS, scale, scale));

    mMass = 0.f;
    mInertia.setZero ();

    mKinematic = true;
}

void Paddle::handleCollision ()
{
    // if collide with ball, bounce it
}
} // namespace Game
