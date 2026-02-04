#pragma once
#include <string>

namespace ZEngineDemo
{
	/**
	 * @brief Example component with serialization support
	 * This demonstrates how to use the reflection system for serialization
	 *
	 * Usage:
	 *   1. Mark your class with REFLECTION_TYPE(ClassName)
	 *   2. Use CLASS(ClassName, Fields) macro
	 *   3. Add REFLECTION_BODY(ClassName) inside the class
	 *   4. Mark fields with META(...) for serialization
	 *
	 * After building, reflection code will be generated automatically
	 */
	class ExampleComponent
	{
	public:
		float m_health = 100.0f;

		int m_level = 1;

		std::string m_name = "Player";
	};
} // namespace ZEngineDemo

