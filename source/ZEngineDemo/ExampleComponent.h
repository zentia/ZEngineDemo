#pragma once

#include "runtime/core/meta/reflection/reflection.h"

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
    REFLECTION_TYPE(ExampleComponent)
    CLASS(ExampleComponent, Fields)
    {
        REFLECTION_BODY(ExampleComponent)
    public:
        META(Editable, Visible)
        float m_health = 100.0f;

        META(Editable, Visible)
        int m_level = 1;

        META(Editable, Visible)
        std::string m_name = "Player";
    };
} // namespace ZEngineDemo
