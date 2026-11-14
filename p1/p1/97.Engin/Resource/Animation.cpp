#include "pch.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation()	: Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
}

void Animation::Save(const wstring& path)
{
}

Vec2 Animation::GetTextureSize()
{
    return _texture->GetSize();
}

const Keyframe& Animation::GetKeyframe(int32 index)
{
    /*cout << "[DEBUG] index : " << index
        << " / size : " << _keyframes.size()
        << endl;*/

    if (_keyframes.size() <= index)
        return _keyframes[0];

    return _keyframes[index];
}

int32 Animation::GetKeyframeCount()
{
    return static_cast<int32>(_keyframes.size());
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
    _keyframes.push_back(keyframe);
}

void Animation::AddKeyframesByCount(Texture* texture, const Keyframe& keyframe, int frameCount, int rowIndex, bool loop)
{
    SetTexture(texture);
    SetLoop(loop);

    float duration = keyframe.time / frameCount;
    for (int i = 0;i < frameCount;i++)
    {
        Keyframe newKeyframe = keyframe;
        newKeyframe.offset.x = keyframe.offset.x + (keyframe.size.x * i);
        newKeyframe.offset.y = keyframe.offset.y + (keyframe.size.y * rowIndex);
        newKeyframe.time = duration;
        AddKeyframe(newKeyframe);
    }
}
