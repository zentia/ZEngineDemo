#include "ZEngineDemo.h"
#include "runtime/function/module/module_manager.h"
#include "runtime/core/base/macro.h"
#include <memory>

namespace ZEngineDemo
{
    // Global module instance
    static std::shared_ptr<ZEngineDemoModule> g_module_instance = nullptr;

    ZEngineDemoModule::ZEngineDemoModule()
    {
    }
    
    ZEngineDemoModule::~ZEngineDemoModule()
    {
    }
    
    const char* ZEngineDemoModule::getName() const
    {
        return "ZEngineDemo";
    }
    
    void ZEngineDemoModule::initialize()
    {
        LOG_INFO(ZEngine, "Initializing ZEngineDemo module...");
        // Initialize your game module here
        // You can access engine systems through g_runtime_global_context
    }
    
    void ZEngineDemoModule::shutdown()
    {
        LOG_INFO(ZEngine, "Shutting down ZEngineDemo module...");
        // Shutdown your game module here
    }
    
    void ZEngineDemoModule::tick(float delta_time)
    {
        // Optional: Implement per-frame updates here
        // This is called every frame by the engine
    }
} // namespace ZEngineDemo

// Auto-register the module when the library is loaded
// This uses a static initializer to register the module before main()
namespace
{
    struct ZEngineDemoModuleRegistrar
    {
        ZEngineDemoModuleRegistrar()
        {
            // Create and register the module instance
            ZEngineDemo::g_module_instance = std::make_shared<ZEngineDemo::ZEngineDemoModule>();
            Z::ModuleManager::getInstance().registerModule(ZEngineDemo::g_module_instance);
        }
    };
    
    // Static instance ensures registration happens at library load time
    static ZEngineDemoModuleRegistrar g_ZEngineDemo_registrar;
}
