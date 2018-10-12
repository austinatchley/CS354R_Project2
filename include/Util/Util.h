#pragma once

#include <cstdint>

#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

#include <OgreVector3.h>
#include <OgreLight.h>

#include <btBulletDynamicsCommon.h>

namespace Util {
enum class Sound : std::size_t { Ball = 0 };

static int Mix_Playing_Sound(Sound s) {
    return Mix_Playing(static_cast<int>(s));
}

static int Mix_PlayChannel_Sound(Sound s, Mix_Chunk *mc, int i) {
    return Mix_PlayChannel(static_cast<int>(s), mc, i);
}

static Ogre::Vector3 makeOgreVector3(const btVector3 &btVector) {
    return Ogre::Vector3(btVector.x(), btVector.z(), btVector.y());
}

static btVector3 makeBulletVector3(const Ogre::Vector3 &ogreVector) {
    return btVector3(ogreVector.x, ogreVector.z, ogreVector.y);
}

static void setNaturalAttenuation(Ogre::Light* light, Ogre::Real range) {
    light->setAttenuation(range , 1.f, 4.5f / range, 75.f / (range*range));
}
}
