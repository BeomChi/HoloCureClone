#include "../../pch.h"
#include "Animator.h"
#include "Texture.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}

Vec2 Animator::GetPivot()
{
	return _info.texture->GetPivot();
}
