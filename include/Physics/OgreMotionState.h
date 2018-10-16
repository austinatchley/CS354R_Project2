#pragma once

#include <iostream>

#include <Util/Util.h>

#include <Ogre.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace Physics
{
class OgreMotionState : public btMotionState
{
    public:
    OgreMotionState(const btTransform& trans, Ogre::SceneNode* node) : mNode(node)
    {
		Ogre::Vector3 position = mNode->_getDerivedPosition( );
		Ogre::Quaternion quaternion = mNode->_getDerivedOrientation( );
		mTrans.setOrigin(btVector3( position.x, position.y, position.z ) );
		mTrans.setRotation(btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w )); 
    }

    virtual ~OgreMotionState()
    {
    }

    virtual void getWorldTransform(btTransform& trans) const
    {
        trans = mTrans;
    }

    virtual void setWorldTransform(const btTransform& trans)
    {
        if(!mNode)
        {
            return;
        }

        mTrans = trans;

        btQuaternion orientation = mTrans.getRotation();
        btVector3 position = mTrans.getOrigin();

        mNode->setPosition(Util::makeOgreVector3(position));

        mNode->setOrientation(
        Ogre::Quaternion(orientation.w(), orientation.x(), orientation.y(), orientation.z()));
    }

    // Use the OgreKinematicMotionState instead if you are trying to use this
    virtual void setKinematicTransform(btTransform& trans)
    {
        assert(false);
    }

    protected:
    Ogre::SceneNode* mNode;
    btTransform mTrans;
};
} // namespace Physics
