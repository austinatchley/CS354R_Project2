#include <GameObjects/Paddle.h>

namespace Game {
Paddle::Paddle(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_PLANE, material, scale) {
    	// define shape, rigid body (a type of btCollisionObject), and set its position
    	mShape = new btBoxShape(btVector3(1, 3, 1));
    	mBody = new btRigidBody();
    	mBody = setCollisionShape(mShape);
    	mTransform.setIdentity();
    	// playerPos is a D3DXVECTOR3 that holds camera position
    	mTransform.setOrigin(btVector3(playerPos.x, playerPos.y, playerPos.z));
    	mBody->setWorldTransform(mTransform);
    	//mPlayerObject->forceActivationState(DISABLE_DEACTIVATION); //unneeded? Object will always respond to forces
    	mWorld->addCollisionObject(mBody);
    }

Paddle::~Paddle() {}

void Paddle::handleCollision() {
	//if collide with ball, bounce it

}
} // namespace Game
