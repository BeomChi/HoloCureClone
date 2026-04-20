#pragma once
#include <cmath>
#include <windows.h>

class Entity;

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct DamageInfo
{
	Entity* _attacker = nullptr;

	int _finalDamage = 0;

	bool _isCritical = false;
};

// 투사체 공격 장비 정보 구조체
struct ProjectileEquipInfo
{
	int32 _count = 1;							// 생성 갯수
	int32 _pierceCount = 0;						// 최대 관통 수(투사체가 관통할 수 있는 적의 수)

	float _range = 1;							// 공격 크기
	float _coolTime = 0;						// 공격 쿨타임
	float _dmgMultiplier = 1;					// 데미지 배율
};

// 범위 공격 장비 정보 구조체
struct AOEEquipInfo
{
	int32 _count = 1;							// 생성 갯수

	float _range = 1;							// 공격 범위
	float _coolTime = 0;						// 공격 쿨타임
	float _duration = 0;						// 지속 시간
	float _attackDelay = 0;						// 공격 주기
	float _dmgMultiplier = 1;					// 데미지 배율

};


struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	Vector operator*(const Vector& other)
	{
		Vector ret;
		ret.x = x * other.x;
		ret.y = y * other.y;
		return ret;
	}

	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		if (length < 0.00000000001f)
			return;

		x /= length;
		y /= length;
	}

	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}

	float Cross(Vector other)
	{
		return x * other.y - y * other.x;
	}

	float x = 0;
	float y = 0;
};

struct VectorInt
{
	VectorInt() {}
	VectorInt(int32 x, int32 y) : x(x), y(y) {}
	VectorInt(POINT pt) : x((int32)pt.x), y((int32)pt.y) {}

	VectorInt operator+(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	VectorInt operator-(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	VectorInt operator*(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x * other.x;
		ret.y = y * other.y;
		return ret;
	}

	VectorInt operator*(int32 value)
	{
		VectorInt ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	void operator+=(const VectorInt& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const VectorInt& other)
	{
		x -= other.x;
		y -= other.y;
	}


	int Dot(VectorInt other)
	{
		return x * other.x + y * other.y;
	}

	int Cross(VectorInt other)
	{
		return x * other.y - y * other.x;
	}

	int32 x = 0;
	int32 y = 0;
};

using Pos = Vector;
using Vec2 = Vector;
using Vec2Int = VectorInt;

