#pragma once

namespace ZEngineDemo
{
    /**
     * @brief Main module class for ZEngineDemo
     * This is your game module entry point
     */
    class ZEngineDemoModule
    {
    public:
        ZEngineDemoModule();
        ~ZEngineDemoModule();
        
        /**
         * @brief Initialize the module
         */
        void initialize();
        
        /**
         * @brief Shutdown the module
         */
        void shutdown();
    };
} // namespace ZEngineDemo
