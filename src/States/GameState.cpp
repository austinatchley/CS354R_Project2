#include <States/GameState.h>

#include <GameObjects/Ball.h>
#include <GameObjects/Ground.h>
#include <GameObjects/Paddle.h>

#include <Util/DebugDrawer.h>
#include <Util/Events/EventSubscribers.h>
#include <Util/Events/Events.h>

using namespace Ogre;
using namespace OgreBites;

namespace Game
{
GameState::GameState(ECS::EventManager* eventManager,
                     Root* root,
                     Ogre::RenderWindow* renderWindow,
                     OgreBites::TrayManager* trayMgr,
                     Ogre::OverlaySystem* OverlaySystem)
: State(ScreenShare::Full), mEventManager(eventManager), mRoot(root), mRenderWindow(renderWindow),
  mTrayMgr(trayMgr), mOverlaySystem(OverlaySystem)
{
}

void GameState::setup()
{
    // get a pointer to the already created root
    mScnMgr = mRoot->createSceneManager();

    mScnMgr->addRenderQueueListener(mOverlaySystem);

    // register our scene with the RTSS
    mShadergen = RTShader::ShaderGenerator::getSingletonPtr();
    mShadergen->addSceneManager(mScnMgr);

    //////////////////////////////////////////////////////////////////
    // Lighting
    mScnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
    mScnMgr->setSkyBox(true, "Examples/TrippySkyBox");
    mScnMgr->setAmbientLight(AMBIENT_LIGHT);

    Ogre::Light* light = mScnMgr->createLight("MainLight");
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);
    light->setType(Light::LT_SPOTLIGHT);
    light->setSpotlightRange(Degree(0), Degree(90));
    Util::setNaturalAttenuation(light, 50.f);

    Ogre::SceneNode* mainLightNode =
    mScnMgr->getRootSceneNode()->createChildSceneNode("MainLight");
    mainLightNode->attachObject(light);
    mainLightNode->setPosition(0, 45.f, 0);
    mainLightNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

    Light* pointLight = mScnMgr->createLight("PointLight");
    pointLight->setType(Light::LT_POINT);
    pointLight->setDiffuseColour(0.85, 0.1, 0.1);
    pointLight->setSpecularColour(0.1, 0.1, 0.1);
    pointLight->setAttenuation(100, 1.0, 0.045, 0.0075);

    SceneNode* pointLightNode = mScnMgr->getRootSceneNode()->createChildSceneNode();
    pointLightNode->attachObject(pointLight);
    pointLightNode->setPosition(Vector3(0, 45.f, -25.f));

    //////////////////////////////////////////////////////////////////
    // GUI
    Button* b = mTrayMgr->createButton(TL_TOPLEFT, "DemoButton", "Exit Game");
    Button* c = mTrayMgr->createButton(TL_TOPLEFT, "SoundButton", "Toggle Sound");

    scorestr = "Score: 0";
    score = 0;
    scr = mTrayMgr->createTextBox(TL_BOTTOMRIGHT, "Score", scorestr, 120.f, 35.f);

    // mTrayMgr->hideCursor();

    //////////////////////////////////////////////////////////////////
    // Bullet init
    mCollisionConfig = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfig);
    mOverlappingPairCache = new btDbvtBroadphase();
    mSolver = new btSequentialImpulseConstraintSolver();

    mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mOverlappingPairCache, mSolver, mCollisionConfig);

    mDynamicsWorld->setGravity(btVector3(0, 0, -10));

    Ogre::SceneNode* root = mScnMgr->getRootSceneNode()->createChildSceneNode("root");
    root->setPosition(0, 40, 0);

    //////////////////////////////////////////////////////////////////
    // Camera
    mCamRootNode = root->createChildSceneNode("cameraRoot");

    mCamNode = mCamRootNode->createChildSceneNode("camera");
    mCamNode->setInheritScale(false);

    // create the camera
    Ogre::Camera* cam = mScnMgr->createCamera("camera");
    cam->setNearClipDistance(0.1);
    cam->setAutoAspectRatio(true);

    cam->lookAt(Ogre::Vector3::ZERO);

    mCamNode->attachObject(cam);

    mCamera = new Rotatable(mCamRootNode, 60.f, Ogre::Radian(Ogre::Math::HALF_PI), mEventManager);

    // and tell it to render into the main window
    mViewport = mRenderWindow->addViewport(cam);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.15f));

    cam->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

    //////////////////////////////////////////////////////////////////
    // create initial game objects
    mGround = new Ground(mScnMgr, mEventManager, mDynamicsWorld, "Examples/BeachStones");
    mGround->addToGame(this);

    mPaddleTrans.setIdentity();
    mPaddleTrans.setOrigin(btVector3(0, -20, -7.5));
    mPaddleTrans.setRotation(btQuaternion(Ogre::Math::HALF_PI, 0, 0));
    mPaddle = new Paddle(mScnMgr, mCamNode, mEventManager, mDynamicsWorld,
                         "Examples/SphereMappedRustySteel", PADDLE_SCALE, mPaddleTrans);

    mPaddle->addToGame(this);

    //DEBUG draw
    isDebugging = false;
    if(isDebugging){
        DebugDrawer* mDebugDrawer = new DebugDrawer(mScnMgr);
        // mDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        mDynamicsWorld->setDebugDrawer(mDebugDrawer);
    }
}

GameState::~GameState()
{
    delete mDynamicsWorld;
    delete mSolver;
    delete mOverlappingPairCache;
    delete mDispatcher;
    delete mCollisionConfig;
}

void GameState::scoreinc()
{
    score += 1;
}

void GameState::update(const Ogre::FrameEvent& evt)
{
    const Real dt = evt.timeSinceLastFrame;

    mDynamicsWorld->stepSimulation(dt);

    // DEBUG drawer
    if(isDebugging)
    {
        mDynamicsWorld->debugDrawWorld();
    }

    for(int i = 0; i < mObjects.size(); ++i)
    {
        GameObject* obj = mObjects[i];

        obj->update(dt);
    }

    ballTimer += dt;

    (void)ballTimer;
    if(ballTimer > BALL_TIMER)
    {
        btTransform ballTrans;
        ballTrans.setIdentity();

        static const auto rand = std::bind(Ogre::Math::RangeRandom, 0, NUM_BALLS);
        ballTrans.setOrigin(
        btVector3(Ogre::Math::Sin(rand() * Ogre::Math::HALF_PI / NUM_BALLS) * BALL_RING_RADIUS,
                  Ogre::Math::Cos(rand() * Ogre::Math::HALF_PI / NUM_BALLS) * BALL_RING_RADIUS, 40));

        Ball* ball = new Ball(mScnMgr, nullptr, mEventManager, mDynamicsWorld, "Examples/Chrome",
                              BALL_RADIUS, ballTrans);
        ball->addToGame(this);

        ball->applyImpulse(BALL_SPEED * (Util::makeBulletVector3(mPaddle->getNode()->_getDerivedPosition()) -
                                     ballTrans.getOrigin()));

        ballTimer = 0.f;

        mEventManager->event<Util::PlaySoundEvent>(new Util::PlaySoundEvent(Util::Sound::Launch));
    }

    scorestr = "Score: " + score;
    scr->setText(scorestr);


}

void GameState::frameEnded(const Ogre::FrameEvent& evt) {

}

bool GameState::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    static const Real mag = Math::HALF_PI / 2000.f;
    static const Ogre::Vector3 rightVec = Ogre::Vector3(mag, 0.f, 0.f);
    static const Ogre::Vector3 leftVec = Ogre::Vector3(-mag, 0.f, 0.f);
    static const Ogre::Vector3 upVec = Ogre::Vector3(0.f, mag, 0.f);
    static const Ogre::Vector3 downVec = Ogre::Vector3(0.f, -mag, 0.f);
    static const Ogre::Vector3 backVec = Ogre::Vector3(0.f, 0.f, mag);
    static const Ogre::Vector3 forVec = Ogre::Vector3(0.f, 0.f, -mag);

    switch(evt.keysym.sym)
    {
    case OgreBites::SDLK_ESCAPE: // Exit the game
        mRoot->queueEndRendering();
        break;

    case 'w':
        mEventManager->event<Util::TransformEntityEvent>(new Util::TranslateEntityEvent(mCamNode, forVec * 5.f));
        break;
    case 's':
        mEventManager->event<Util::TransformEntityEvent>(new Util::TranslateEntityEvent(mCamNode, backVec * 5.f));
        break;
    case 'a':
        mEventManager->event<Util::TransformEntityEvent>(new Util::TranslateEntityEvent(mCamNode, leftVec * 5.f));
        break;
    case 'd':
        mEventManager->event<Util::TransformEntityEvent>(new Util::TranslateEntityEvent(mCamNode, rightVec * 5.f));
        break;

    case OgreBites::SDLK_PAGEUP:
        mEventManager->event<Util::TransformEntityEvent>(new Util::TranslateEntityEvent(mCamNode, upVec * 5.f));
        break;
    case OgreBites::SDLK_PAGEDOWN: // For some reason the 'End' key seems to
                                   // trigger this keybinding
        mEventManager->event<Util::TransformEntityEvent>(new Util::TranslateEntityEvent(mCamNode, downVec * 5.f));
        break;

    case OgreBites::SDLK_UP:
        mEventManager->event<Util::TransformEntityEvent>(new Util::RotateEntityEvent(mCamNode, rightVec * 0.25f));
        break;
    case OgreBites::SDLK_DOWN:
        mEventManager->event<Util::TransformEntityEvent>(new Util::RotateEntityEvent(mCamNode, leftVec * 0.25f));
        break;
    case OgreBites::SDLK_LEFT:
        mEventManager->event<Util::TransformEntityEvent>(new Util::RotateEntityEvent(mCamNode, upVec * 0.25f));
        break;
    case OgreBites::SDLK_RIGHT:
        mEventManager->event<Util::TransformEntityEvent>(new Util::RotateEntityEvent(mCamNode, downVec * 0.25f));
        break;

    default:
        return false;
    }

    return false;
}

bool GameState::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
    bool res = false;
    if(mTrayMgr->mousePressed(evt))
    {
        res = true;
    }

    return res;
}
bool GameState::mouseReleased(const OgreBites::MouseButtonEvent& evt)
{
    bool res = true;
    if(mTrayMgr->mouseReleased(evt))
    {
        res = true;
    }

    return res;
}

bool GameState::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    static const Real mag = Ogre::Math::PI / 200.f;
    static const Ogre::Vector3 rightVec = Ogre::Vector3(mag, 0.f, 0.f);
    static const Ogre::Vector3 leftVec = Ogre::Vector3(-mag, 0.f, 0.f);
    static const Ogre::Vector3 upVec = Ogre::Vector3(0.f, mag, 0.f);
    static const Ogre::Vector3 downVec = Ogre::Vector3(0.f, -mag, 0.f);
    static const Ogre::Vector3 backVec = Ogre::Vector3(0.f, 0.f, mag);
    static const Ogre::Vector3 forVec = Ogre::Vector3(0.f, 0.f, -mag);

    bool res = false;

    if(evt.type == OgreBites::MOUSEMOTION)
    {
        mEventManager->event<Util::RotateEvent>(
        new Util::RotateEvent(mCamRootNode, (leftVec * evt.xrel) + (downVec * evt.yrel), Ogre::Vector3::ZERO));

        res = true;
    }

    if(mTrayMgr->mouseMoved(evt)) {
        res = true;
    }

    return res;
}
void GameState::buttonHit(OgreBites::Button* button)
{
    if(button->getName() == "DemoButton")
        mRoot->queueEndRendering();
    if(button->getName() == "SoundButton")
        mEventManager->event<Util::ToggleSoundEvent>(new Util::ToggleSoundEvent());

}

std::size_t GameState::addObject(GameObject* obj)
{
    mObjects.push_back(obj);
    return mObjects.size();
}
} // namespace Game
