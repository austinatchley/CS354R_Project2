#include "Game.h"

#include "Util/Util.h"

#include <limits>

using namespace Ogre;
using namespace OgreBites;

namespace Game {
Game::Game() : ApplicationContext("Project2") {}

Game::~Game() {}

void Game::setup() {
    //////////////////////////////////////////////////////////////////
    // Application Setup
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();

    // register our scene with the RTSS
    mShadergen = RTShader::ShaderGenerator::getSingletonPtr();
    mShadergen->addSceneManager(mScnMgr);

    //////////////////////////////////////////////////////////////////
    // Event Manager
    mEventManager.reset(new ECS::EventManager(std::allocator<void>()));

    TransformEntitySubscriber *moveEntitySub = new TransformEntitySubscriber();
    mEventManager->connect<TransformEntityEvent>(moveEntitySub);

    //////////////////////////////////////////////////////////////////
    // Sound Manager
    mSoundManager = new SoundManager();
    mEventManager->connect<PlaySoundEvent>(mSoundManager);

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

    // this should be pulled out into a util function for calculating correct
    // attenuation constants
    light->setAttenuation(WALL_SIZE * 24.f, 1.f, 4.5f / (WALL_SIZE * 24.f),
                          75.f / (WALL_SIZE * WALL_SIZE * 576.f));

    Ogre::SceneNode *mainLightNode =
        mScnMgr->getRootSceneNode()->createChildSceneNode("MainLight");
    mainLightNode->attachObject(light);
    mainLightNode->setPosition(0, WALL_SIZE - 1.f, 0);
    mainLightNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

    Light *pointLight = mScnMgr->createLight("PointLight");
    pointLight->setType(Light::LT_POINT);
    pointLight->setDiffuseColour(0.85, 0.1, 0.1);
    pointLight->setSpecularColour(0.1, 0.1, 0.1);
    pointLight->setAttenuation(100, 1.0, 0.045, 0.0075);

    SceneNode *pointLightNode =
        mScnMgr->getRootSceneNode()->createChildSceneNode();
    pointLightNode->attachObject(pointLight);
    pointLightNode->setPosition(Vector3(0, WALL_SIZE - 1.f, -WALL_SIZE + 1.f));

    //////////////////////////////////////////////////////////////////
    // Camera
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode("camera");

    // create the camera
    Camera *cam = mScnMgr->createCamera("camera");
    cam->setNearClipDistance(0.1);
    cam->setAutoAspectRatio(true);
    cam->lookAt(Ogre::Vector3::ZERO);

    mCamNode->attachObject(cam);
    mCamNode->setPosition(0, 0, 60);

    // and tell it to render into the main window
    mViewport = getRenderWindow()->addViewport(cam);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.15f));

    cam->setAspectRatio(Real(mViewport->getActualWidth()) /
                        Real(mViewport->getActualHeight()));

    //////////////////////////////////////////////////////////////////
    // Balls
    for (int i = 0; i < NUM_BALLS; ++i) {
        const Vector3 vel(Math::RangeRandom(-20.0, 20.0),
                          Math::RangeRandom(-20.0, 20.0),
                          Math::RangeRandom(-20.0, 20.0));

        Ball ball(mScnMgr, BALL_RADIUS, "Examples/SphereMappedRustySteel", vel);

        mBalls.push_back(ball);

        const Vector3 pos(Math::RangeRandom(-WALL_SIZE, WALL_SIZE),
                          Math::RangeRandom(-WALL_SIZE, WALL_SIZE),
                          Math::RangeRandom(-WALL_SIZE, WALL_SIZE));
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(ball.getNode(), pos));
    }

    //////////////////////////////////////////////////////////////////
    // Planes
    static const std::unordered_map<String, Vector3> planeNameToAxis = {
        {"left", Vector3::UNIT_X},   {"right", Vector3::NEGATIVE_UNIT_X},
        {"ground", Vector3::UNIT_Y}, {"ceil", Vector3::NEGATIVE_UNIT_Y},
        {"back", Vector3::UNIT_Z},   {"front", Vector3::NEGATIVE_UNIT_Z}};

    for (const auto entry : planeNameToAxis) {
        auto name = entry.first;
        auto norm = entry.second;

        Plane plane(norm, -WALL_SIZE);
        MeshManager::getSingleton().createPlane(
            name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            WALL_SIZE * 2.f, WALL_SIZE * 2.f, 20, 20, true, 1, 5, 5,
            norm.perpendicular());

        Entity *planeEntity = mScnMgr->createEntity(name);
        planeEntity->setCastShadows(false);
        planeEntity->setMaterialName("Examples/BeachStones");

        SceneNode *planeNode =
            mScnMgr->getRootSceneNode()->createChildSceneNode(name);
        planeNode->attachObject(planeEntity);

        mWalls.push_back(plane);
    }
}

bool Game::keyPressed(const KeyboardEvent &evt) {
    static const Real mag = Math::HALF_PI / 2.f;
    static const Ogre::Vector3 rightVec = Ogre::Vector3(mag, 0.f, 0.f);
    static const Ogre::Vector3 leftVec = Ogre::Vector3(-mag, 0.f, 0.f);
    static const Ogre::Vector3 upVec = Ogre::Vector3(0.f, mag, 0.f);
    static const Ogre::Vector3 downVec = Ogre::Vector3(0.f, -mag, 0.f);
    static const Ogre::Vector3 backVec = Ogre::Vector3(0.f, 0.f, mag);
    static const Ogre::Vector3 forVec = Ogre::Vector3(0.f, 0.f, -mag);

    switch (evt.keysym.sym) {
    case OgreBites::SDLK_ESCAPE: // Exit the game
        getRoot()->queueEndRendering();
        break;

    case 'w':
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(mCamNode, forVec * 5.f));
        break;
    case 's':
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(mCamNode, backVec * 5.f));
        break;
    case 'a':
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(mCamNode, leftVec * 5.f));
        break;
    case 'd':
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(mCamNode, rightVec * 5.f));
        break;

    case OgreBites::SDLK_PAGEUP:
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(mCamNode, upVec * 5.f));
        break;
    case OgreBites::SDLK_PAGEDOWN: // For some reason the 'End' key seems to
                                   // trigger this keybinding
        mEventManager->event<TransformEntityEvent>(
            new TranslateEntityEvent(mCamNode, downVec * 5.f));
        break;

    case OgreBites::SDLK_UP:
        mEventManager->event<TransformEntityEvent>(
            new RotateEntityEvent(mCamNode, rightVec * 0.25f));
        break;
    case OgreBites::SDLK_DOWN:
        mEventManager->event<TransformEntityEvent>(
            new RotateEntityEvent(mCamNode, leftVec * 0.25f));
        break;
    case OgreBites::SDLK_LEFT:
        mEventManager->event<TransformEntityEvent>(
            new RotateEntityEvent(mCamNode, upVec * 0.25f));
        break;
    case OgreBites::SDLK_RIGHT:
        mEventManager->event<TransformEntityEvent>(
            new RotateEntityEvent(mCamNode, downVec * 0.25f));
        break;

    default:
        return false;
    }

    return true;
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    const Real dt = evt.timeSinceLastFrame;

    // Check each ball for collisions
    for (int i = 0; i < mBalls.size(); ++i) {
        mBalls[i].move(mWalls, mEventManager.get(), dt);
    }

    // Tell the EventManager to dispatch the events in the queue
    mEventManager->update();

    return true;
}

} // namespace Game

int main(int argc, char **argv) {
    try {
        Game::Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const std::exception &e) {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
