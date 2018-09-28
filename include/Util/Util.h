#pragma once

#include <cstdint>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_audio.h>

namespace Util
{
    enum class Sound : std::size_t
    {
        Ball = 0
    };

    static int Mix_Playing_Sound(Sound s)
    {
        return Mix_Playing(static_cast<int>(s));
    }

    static int Mix_PlayChannel_Sound(Sound s, Mix_Chunk* mc, int i)
    {
        return Mix_PlayChannel(static_cast<int>(s), mc, i);
    }
}
