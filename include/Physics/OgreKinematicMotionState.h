#pragma once

#include <Physics/OgreMotionState.h>

namespace Physics {
class OgreKinematicMotionState : public OgreMotionState {
public:
    OgreKinematicMotionState(const btTransform& trans, Ogre::SceneNode* node)
        : OgreMotionState(trans, node) {}

    void setKinematicTransform(btTransform& trans) override { mTrans = trans; }
};
}
