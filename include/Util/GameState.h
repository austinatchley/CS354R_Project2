#pragma once

#include <cstdint>

#include <OgreInput.h>

namespace Util
{
    enum class ScreenShare : std::size_t
    {
        Transparent = 0,
        Shared,
        Full
    };

    class GameState
    {
    public:
        GameState(ScreenShare screenShare = ScreenShare::Transparent) 
            : mScreenShare(screenShare)
        {}

        virtual ~GameState() {}

        virtual void update() = 0;

        virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) = 0;

        ScreenShare mScreenShare; 
    };
}
