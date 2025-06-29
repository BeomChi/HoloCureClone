#include "pch.h"
#include "SpriteRenderer.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../01.Manager/SceneManager.h"
#include "../../03.Object/GameObject.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Init()
{
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::Render(HDC hdc)
{
	// 스프라이트가 없으면 그리지 않음
	if (_sprite == nullptr)
		return;

	// 스프라이트의 원본 사이즈 가져오기 (픽셀 단위)
	Vec2Int size = _sprite->GetSize();

	// 오브젝트의 월드 좌표
	Vec2 pos = _owner->GetPos();

	// 오브젝트의 스케일 (크기 배율)
	Vec2 scale = _owner->GetScale();

	// 실제 렌더링될 가로/세로 크기 계산 (스프라이트 크기에 배율 곱함)
	float renderSizeX = (float)size.x * scale.x;
	float renderSizeY = (float)size.y * scale.y;

	// 월드 좌표 → 스크린 좌표로 변환 (카메라에 따라 보정됨)
	Vec2 screenPos = GET_SINGLE(SceneManager)->WorldToScreen(pos);

	// 피벗 보정: 예를 들어 피벗이 (0.5, 0.5)면 중심 정렬, (0, 0)이면 좌상단 기준
	screenPos.x -= _sprite->GetPivot().x * renderSizeX;
	screenPos.y -= _sprite->GetPivot().y * renderSizeY;

	// 투명 블리팅으로 스프라이트 그리기
	::TransparentBlt(
		hdc,                          // 그릴 대상 HDC
		(int32)screenPos.x,           // 화면상 x좌표
		(int32)screenPos.y,           // 화면상 y좌표
		renderSizeX,                  // 그릴 너비
		renderSizeY,                  // 그릴 높이
		_sprite->GetDC(),             // 스프라이트가 그려진 메모리 DC
		_sprite->GetPos().x,          // 원본 이미지에서의 x 좌표 (부분 추출용, 보통 0)
		_sprite->GetPos().y,          // 원본 이미지에서의 y 좌표
		_sprite->GetSize().x,         // 원본 이미지에서의 너비
		_sprite->GetSize().y,         // 원본 이미지에서의 높이
		_sprite->GetTransparent());   // 투명색 (보통 RGB 값)

	// 디버깅용: 화면상에 그려지는 시작점에 원을 그림 (중심 확인용)
	Utils::DrawCircle(hdc, { screenPos.x, screenPos.y }, 5);
}
