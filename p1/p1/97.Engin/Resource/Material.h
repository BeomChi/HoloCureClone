#pragma once
#include "ResourceBase.h"

class Shader;
class Texture;

class Material :    public ResourceBase
{
    using Super = ResourceBase;
public:
    Material();
    virtual ~Material();

    Shader* GetShader() { return _shader; }
    Texture* GetTexture() { return _texture; }

    void SetShader(Shader* shader) { _shader = shader; }
    void SetTexture(Texture* texture) { _texture = texture; }

private:
    Shader* _shader;
    
    Texture* _texture;
};

