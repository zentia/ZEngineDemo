Shader "Custom/KeywordSmoke"
{
    Properties
    {
        _BaseColor ("Base Color", Color) = (1, 1, 1, 1)
    }

    SubShader
    {
        Tags { "RenderPipeline" = "StandardLit" "Queue" = "Geometry" }

        Pass
        {
            Name "GBuffer"
            Tags { "LightMode" = "GBuffer" }

            HLSLPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma multi_compile _ USE_FOG
            #pragma shader_feature _ DEBUG_VIEW

            cbuffer UnityPerMaterial { float4 _BaseColor; };

            struct Attributes { float4 position : POSITION; };
            struct Varyings { float4 position : SV_POSITION; };

            Varyings vert(Attributes input)
            {
                Varyings o;
                o.position = input.position;
                return o;
            }

            float4 frag(Varyings input) : SV_Target
            {
            #if defined(USE_FOG)
                return float4(0.2, 0.5, 0.9, 1) * _BaseColor;
            #elif defined(DEBUG_VIEW)
                return float4(1, 0, 1, 1);
            #else
                return _BaseColor;
            #endif
            }
            ENDHLSL
        }
    }
}