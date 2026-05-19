#include "../Text.h"

class DamageText : public Text
{
	using Super = Text;
public:
	DamageText();
	virtual ~DamageText() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Reset();
	void ShowDamage(float damage,Vec2 pos,bool isCritical);

private:
	float _duration = 2.f; // 텍스트가 화면에 표시되는 시간
	float _baseDuration = 1.5f; // 텍스트가 화면에 표시되는 시간
};