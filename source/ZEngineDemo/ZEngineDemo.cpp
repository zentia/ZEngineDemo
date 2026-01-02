#include "ZEngineDemo.h"
#include "runtime/function/module/module_manager.h"
#include "runtime/core/base/macro.h"
#include "runtime/core/base/SystemRegistry.h"
#include <memory>

namespace ZEngineDemo
{
	// Global module instance
	// This is managed by InitializeLibrary/UninitializeLibrary to avoid static variables
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

// Export functions for DLL initialization/uninitialization
// Using explicit InitializeLibrary/UninitializeLibrary functions instead of static variables
// avoids issues with DLL unloading, as static destructors can prevent proper DLL unload
extern "C"
{
	/**
	 * @brief Initialize the library and register the module
	 * This function should be called after the DLL is loaded
	 * @return true if initialization succeeded, false otherwise
	 */
	bool InitializeLibrary()
	{
		if (ZEngineDemo::g_module_instance != nullptr)
		{
			LOG_WARNING(ZEngine, "ZEngineDemo module already initialized");
			return false;
		}

		// Create and register the module instance
		ZEngineDemo::g_module_instance = std::make_shared<ZEngineDemo::ZEngineDemoModule>();
		GET_SYSTEM(ModuleManager)->registerModule(ZEngineDemo::g_module_instance);

		LOG_INFO(ZEngine, "Successfully initialized ZEngineDemo library");
		return true;
	}

	/**
	 * @brief Uninitialize the library and unregister the module
	 * This function should be called before the DLL is unloaded
	 */
	void UninitializeLibrary()
	{
		if (ZEngineDemo::g_module_instance == nullptr)
		{
			LOG_WARNING(ZEngine, "ZEngineDemo module not initialized, skipping uninitialization");
			return;
		}

		// Shutdown the module if it's still initialized
		if (ZEngineDemo::g_module_instance)
		{
			ZEngineDemo::g_module_instance->shutdown();
		}

		// Clear the module instance
		// Note: The module will be removed from ModuleManager when the shared_ptr is destroyed
		ZEngineDemo::g_module_instance.reset();

		LOG_INFO(ZEngine, "Successfully uninitialized ZEngineDemo library");
	}
}

