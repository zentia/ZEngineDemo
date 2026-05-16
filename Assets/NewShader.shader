Shader "Custom/NewShader"
{
    Properties
    {
        _BaseColor ("Base Color", Color) = (1, 1, 1, 1)
    }

    SubShader
    {
        Tags
        {
            "RenderPipeline" = "Deferred"
            "Queue" = "Geometry"
            "RenderType" = "Opaque"
        }

        Pass
        {
            Name "ForwardLit"
            Tags { "LightMode" = "ForwardLit" }

            ZWrite On
            ZTest LEqual
            Cull Back

            HLSLPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            cbuffer UnityPerMaterial
            {
                float4 _BaseColor;
            };

            struct Attributes
            {
                float4 position : POSITION;
            };

            struct Varyings
            {
                float4 position : SV_POSITION;
            };

            Varyings vert(Attributes input)
            {
                Varyings output;
                output.position = input.position;
                return output;
            }

            float4 frag(Varyings input) : SV_Target
            {
                return _BaseColor;
            }
            ENDHLSL
        }
    }
}
