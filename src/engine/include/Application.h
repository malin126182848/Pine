#pragma once

#include "globel.h"

namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void run();
    };
} // namespace Engine
