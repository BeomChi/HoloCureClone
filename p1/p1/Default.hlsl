
struct VS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
   // float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    //float4 color : COLOR;
};

cbuffer TransformData : register(b0)
{
    row_major matrix matWorld;

}

cbuffer CameraData : register(b1)
{
    row_major matrix matView;
    row_major matrix matProjection;
}

cbuffer AnimationData : register(b2)
{
    float2 spriteOffset;
    float2 spriteSize;
    float2 textureSize;
    float useAnimation;
}


// VS
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    
    output.position = position;
    output.uv = input.uv;
    //output.color = input.color;
    
    if(useAnimation == 1.0f)
    {
        output.uv *= spriteSize / textureSize;
        output.uv += spriteOffset / textureSize;
    }
    
    return output;
}

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = texture0.Sample(sampler0, input.uv);
    //color *= input.color;
    
    return color;
}