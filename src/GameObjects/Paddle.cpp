#include <GameObjects/Paddle.h>

namespace Game {
Paddle::Paddle(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f,
               const Ogre::Vector3& pos = Ogre::Vector3::ZERO)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_PLANE, material, scale) {
    mShape = new btBoxShape(btVector3(1, 3, 1));

    mTransform.setIdentity();
    mTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    mMass = 0.f;

    mInertia.setZero();

    mMotionState = new Physics::OgreMotionState(mNode);

    mKinematic = true;
}

void Paddle::handleCollision() {
	//if collide with ball, bounce it

}
} // namespace Game
