#include <States/GameState.h>

#include <GameObjects/Ball.h>
#include <GameObjects/Ground.h>
#include <GameObjects/Paddle.h>

#include <Util/Events/EventSubscribers.h>
#include <Util/Events/Events.h>

using namespace Ogre;
using namespace OgreBites;

namespace Game {
GameState::GameState(ECS::EventManager *eventManager, Root *root,
                     Ogre::RenderWindow *renderWindow,
                     OgreBites::TrayManager *trayMgr)
    : State(ScreenShare::Full), mEventManager(eventManager), mRoot(root),
      mRenderWindow(renderWindow), mTrayMgr(trayMgr) {}

void GameState::setup() {
    // get a pointer to the already created root
    mScnMgr = mRoot->createSceneManager();

    // register our scene with the RTSS
    mShadergen = RTShader::ShaderGenerator::getSingletonPtr();
    mShadergen->addSceneManager(mScnMgr);

    //////////////////////////////////////////////////////////////////
    // Lighting
    mScnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
    mScnMgr->setSkyBox(true, "Examples/TrippySkyBox");
    mScnMgr->setAmbientLight(AMBIENT_LIGHT);

    Ogre::Light *light = mScnMgr->createLight("MainLight");
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);
    light->setType(Light::LT_SPOTLIGHT);
    light->setSpotlightRange(Degree(0), Degree(90));
    Util::setNaturalAttenuation(light, 50.f);

    Ogre::SceneNode *mainLightNode =
        mScnMgr->getRootSceneNode()->createChildSceneNode("MainLight");
    mainLightNode->attachObject(light);
    mainLightNode->setPosition(0, 45.f, 0);
    mainLightNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

    Light *pointLight = mScnMgr->createLight("PointLight");
    pointLight->setType(Light::LT_POINT);
    pointLight->setDiffuseColour(0.85, 0.1, 0.1);
    pointLight->setSpecularColour(0.1, 0.1, 0.1);
    pointLight->setAttenuation(100, 1.0, 0.045, 0.0075);

    SceneNode *pointLightNode =
        mScnMgr->getRootSceneNode()->createChildSceneNode();
    pointLightNode->attachObject(pointLight);
    pointLightNode->setPosition(Vector3(0, 45.f, -25.f));

    //////////////////////////////////////////////////////////////////
    // Camera
    mCamRootNode = mScnMgr->getRootSceneNode()->createChildSceneNode("cameraRoot");
    mCamRootNode->setPosition(0.f, 30.f, 10.f);

    mCamNode = mCamRootNode->createChildSceneNode("camera");

    // create the camera
    Ogre::Camera *cam = mScnMgr->createCamera("camera");
    cam->setNearClipDistance(0.1);
    cam->setAutoAspectRatio(true);

    cam->lookAt(Ogre::Vector3::ZERO);

    mCamNode->attachObject(cam);

    mCamera = new Camera(mCamNode, 60.f, mEventManager);

    // and tell it to render into the main window
    mViewport = mRenderWindow->addViewport(cam);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.15f));

    cam->setAspectRatio(Real(mViewport->getActualWidth()) /
                        Real(mViewport->getActualHeight()));

    //////////////////////////////////////////////////////////////////
    // GUI
    Button *b = mTrayMgr->createButton(TL_TOPLEFT, "DemoButton", "Exit Game");

    score = 0;
    mTrayMgr->createTextBox(TL_BOTTOMRIGHT, "Score", "" + score, 0.1f, 0.1f);

    //mTrayMgr->hideCursor(); 

    //////////////////////////////////////////////////////////////////
    // Bullet init
    mCollisionConfig = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfig);
    mOverlappingPairCache = new btDbvtBroadphase();
    mSolver = new btSequentialImpulseConstraintSolver();

    mDynamicsWorld = new btDiscreteDynamicsWorld(
        mDispatcher, mOverlappingPairCache, mSolver, mCollisionConfig);

    mDynamicsWorld->setGravity(btVector3(0, 0, -10));

    //////////////////////////////////////////////////////////////////
    // create initial game objects
    Ground *ground = new Ground(mScnMgr, mEventManager, mDynamicsWorld, "Examples/BeachStones");
    ground->addToGame(this); 
    
    mPaddleTrans.setIdentity();
    mPaddleTrans.setOrigin(btVector3(0, 10, 20));
    Paddle *paddle = new Paddle(mScnMgr, mEventManager, mDynamicsWorld,
                                "Examples/SphereMappedRustySteel", PADDLE_SCALE,
                                mPaddleTrans);
    paddle->addToGame(this);
}

GameState::~GameState() {
    delete mDynamicsWorld;
    delete mSolver;
    delete mOverlappingPairCache;
    delete mDispatcher;
    delete mCollisionConfig;
}

void GameState::update(const Ogre::FrameEvent &evt) {
    const Real dt = evt.timeSinceLastFrame;

    mDynamicsWorld->stepSimulation(dt);

    for (int i = 0; i < mObjects.size(); ++i) {
        GameObject *obj = mObjects[i];
      
        obj->update(dt);

        std::cout << obj->getNode()->getPosition() << std::endl;
    }

    ballTimer += dt;

    (void)ballTimer;
    if (ballTimer > BALL_TIMER) {
        std::cout << " SPAWNED BALL " << std::endl;
        btTransform ballTrans;
        ballTrans.setIdentity();

        static const auto rand = std::bind(Ogre::Math::RangeRandom, 0, NUM_BALLS);
        ballTrans.setOrigin(btVector3(
                    Ogre::Math::Sin(rand() * Ogre::Math::TWO_PI / NUM_BALLS) * BALL_RING_RADIUS,
                    Ogre::Math::Cos(rand() * Ogre::Math::TWO_PI / NUM_BALLS) * BALL_RING_RADIUS,
                    40));

        Ball *ball = new Ball(mScnMgr, mEventManager, mDynamicsWorld,
                              "Examples/Chrome", BALL_RADIUS,
                              ballTrans);
        ball->addToGame(this);

        ball->applyImpulse(1000.f * (mPaddleTrans.getOrigin() - ballTrans.getOrigin()));

        ballTimer = 0.f;
    }
}

bool GameState::keyPressed(const OgreBites::KeyboardEvent &evt) {
    static const Real mag = Math::HALF_PI / 2000.f;
    static const Ogre::Vector3 rightVec = Ogre::Vector3(mag, 0.f, 0.f);
    static const Ogre::Vector3 leftVec = Ogre::Vector3(-mag, 0.f, 0.f);
    static const Ogre::Vector3 upVec = Ogre::Vector3(0.f, mag, 0.f);
    static const Ogre::Vector3 downVec = Ogre::Vector3(0.f, -mag, 0.f);
    static const Ogre::Vector3 backVec = Ogre::Vector3(0.f, 0.f, mag);
    static const Ogre::Vector3 forVec = Ogre::Vector3(0.f, 0.f, -mag);

    switch (evt.keysym.sym) {
    case OgreBites::SDLK_ESCAPE: // Exit the game
        mRoot->queueEndRendering();
        break;

    case 'w':
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::TranslateEntityEvent(mCamNode, forVec * 5.f));
        break;
    case 's':
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::TranslateEntityEvent(mCamNode, backVec * 5.f));
        break;
    case 'a':
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::TranslateEntityEvent(mCamNode, leftVec * 5.f));
        break;
    case 'd':
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::TranslateEntityEvent(mCamNode, rightVec * 5.f));
        break;

    case OgreBites::SDLK_PAGEUP:
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::TranslateEntityEvent(mCamNode, upVec * 5.f));
        break;
    case OgreBites::SDLK_PAGEDOWN: // For some reason the 'End' key seems to
                                   // trigger this keybinding
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::TranslateEntityEvent(mCamNode, downVec * 5.f));
        break;

    case OgreBites::SDLK_UP:
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::RotateEntityEvent(mCamNode, rightVec * 0.25f));
        break;
    case OgreBites::SDLK_DOWN:
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::RotateEntityEvent(mCamNode, leftVec * 0.25f));
        break;
    case OgreBites::SDLK_LEFT:
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::RotateEntityEvent(mCamNode, upVec * 0.25f));
        break;
    case OgreBites::SDLK_RIGHT:
        mEventManager->event<Util::TransformEntityEvent>(
            new Util::RotateEntityEvent(mCamNode, downVec * 0.25f));
        break;

    default:
        return false;
    }

    return false;
}

bool GameState::mousePressed(const OgreBites::MouseButtonEvent &evt) {
    if (mTrayMgr->mousePressed(evt)) {
        return true;
    }

    return true;
}
bool GameState::mouseReleased(const OgreBites::MouseButtonEvent &evt) {
    if (mTrayMgr->mouseReleased(evt)) {
        return true;
    }

    return true;
}

bool GameState::mouseMoved(const OgreBites::MouseMotionEvent &evt) {
    static const Real mag = Ogre::Math::PI / 200.f;
    static const Ogre::Vector3 rightVec = Ogre::Vector3(mag, 0.f, 0.f);
    static const Ogre::Vector3 leftVec = Ogre::Vector3(-mag, 0.f, 0.f);
    static const Ogre::Vector3 upVec = Ogre::Vector3(0.f, mag, 0.f);
    static const Ogre::Vector3 downVec = Ogre::Vector3(0.f, -mag, 0.f);
    static const Ogre::Vector3 backVec = Ogre::Vector3(0.f, 0.f, mag);
    static const Ogre::Vector3 forVec = Ogre::Vector3(0.f, 0.f, -mag);

    if (evt.type == OgreBites::MOUSEMOTION) {
        mEventManager->event<Util::RotateCameraEvent>(
            new Util::RotateCameraEvent(mCamNode, (leftVec * evt.xrel) +
                                                      (downVec * evt.yrel),
                                        Ogre::Vector3::ZERO));

        return true;
    }

    if (mTrayMgr->mouseMoved(evt))
        return true;

    return false;
}
void GameState::buttonHit(OgreBites::Button *button) {
    if (button->getName() == "DemoButton")
        mRoot->queueEndRendering();
}

std::size_t GameState::addObject(GameObject *obj) {
    mObjects.push_back(obj);
    return mObjects.size();
}
}
