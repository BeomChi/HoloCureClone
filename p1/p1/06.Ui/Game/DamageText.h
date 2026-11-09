#include "../Text.h"

class SpriteRenderer;
class Sprite;

class DamageText : public Text
{
	using Super = Text;
public:
	DamageText();
	virtual ~DamageText() override;

	virtual void Init() override;
	virtual void Update() override;
	//virtual void Render(HDC hdc) override;

	void Reset();
	void ShowDamage(float damage,Vec3 pos,bool isCritical);

	void Time();

private:
	Sprite* _sprite[2][10];
	SpriteRenderer* _spriteRenderer;
	int8 _currentSpriteIndex = 0;
	float _duration = 2.f; // 텍스트가 화면에 표시되는 시간
	float _baseDuration = 1.5f; // 텍스트가 화면에 표시되는 시간
};