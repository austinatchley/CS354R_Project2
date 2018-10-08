#pragma once

#include <GameObjects/GameObject.h>

namespace Game {
class Ground : public Ground {
	public:
		Ground(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
               const Ogre::String &material, float scale);

    	//void handleCollision() override;
};
}