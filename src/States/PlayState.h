#pragma once

#include <OgreInput.h>

#include "Util/GameState.h"

namespace Game {
// The game state where you actually play the game
// This should handle all game-specific logic
class PlayState : public Util::GameState {
  public:
    PlayState();
    virtual ~PlayState() {}

    void update(const Ogre::FrameEvent& evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;

  private:
    Root *mRoot;
    SceneManager *mScnMgr;
    RTShader::ShaderGenerator *mShadergen;

    Ogre::SceneNode *mCamNode;
    Ogre::Viewport *mViewport;

    std::vector<Ball> mBalls;
    std::vector<Ogre::Plane> mWalls;

};
}
