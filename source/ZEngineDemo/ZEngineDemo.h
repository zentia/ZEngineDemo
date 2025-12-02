#pragma once

#include "runtime/function/module/game_module.h"

namespace ZEngineDemo
{
    /**
     * @brief Main module class for ZEngineDemo
     * This is your game module entry point
     * The module will be automatically registered and initialized by the engine
     */
    class ZEngineDemoModule : public Z::IGameModule
    {
    public:
        ZEngineDemoModule();
        virtual ~ZEngineDemoModule();
        
        // IGameModule interface
        const char* getName() const override;
        void initialize() override;
        void shutdown() override;
        void tick(float delta_time) override;
    };
} // namespace ZEngineDemo

