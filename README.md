# HoloCureClone

HoloCure Clone Project (C++ / WinAPI)

포트폴리오 용도 / 개인 개발 / WinAPI + C++

이 프로젝트는 Kay Yu의 HoloCure 게임을 기반으로 직접 구현해보는 클론 프로젝트입니다.
C++ 및 WinAPI를 기반으로 게임 루프, 객체 관리, 시스템 매니저 등 게임 개발의 기초부터 직접 구현하며 학습하고자 시작했습니다.

본 프로젝트는 비영리적인 포트폴리오 목적으로만 제작되며, 상업적 사용은 일절 없습니다.
참고 리소스는 일부 원작 리소스를 기반으로 하고 있습니다.

---

## 프로젝트 목적

- WinAPI 기반의 저수준 게임 루프, 렌더링, 입력, 타이밍 직접 구현
- 오브젝트 풀, 상태 머신, 매니저 등 게임 구조 설계 능력 향상
- 실제 게임 구조를 분석하고 C++로 직접 구현하여 이해도 증진
- 스테이지 및 전투 시스템 단계적 구현을 통한 성장

---

## 개발 환경

| 항목 | 내용 |
|------|------|
| **언어** | C++ |
| **플랫폼** | Windows API (WinAPI) |
| **IDE** | Visual Studio 2022 |
| **버전 관리** | Git, SourceTree |

---

## 현재 구현된 기능

- ✔ 오브젝트 풀 시스템 구현
- ✔ 몬스터 자동 스폰 및 위치 랜덤 생성
- ✔ 몬스터 상태 시스템 (Update / Dead 등)
- ✔ 스폰 매니저 설계 및 몬스터 수 제어
- ✔ 기본 씬 구성 및 게임 루프 구조 설계

---

## 향후 계획

- [ ] 보스 몬스터 및 전투 패턴 추가
- [ ] 경험치, 체력 드랍 등 필드 아이템 시스템
- [ ] 인벤토리 및 장비 장착 UI
- [ ] 플레이어 레벨업에 따른 장비 강화 시스템
- [ ] 씬 전환 및 스테이지 완료 조건 구현

---

## 시스템 구조도 (텍스트 기반)

[Main.cpp]
|
[GameManager]
├── [SceneManager]
│ ├── Scene_Title
│ └── Scene_Stage
├── [ObjectManager]
├── [TimeManager]
├── [InputManager]
└── [SpawnManager]

---

## 구조 설계 방향

| 모듈 | 설명 |
|------|------|
| **GameManager** | 게임 루프 및 전역 상태 관리 |
| **SceneManager** | 씬 로딩 및 전환 담당 |
| **ObjectManager** | 모든 게임 오브젝트 업데이트 및 제거 |
| **SpawnManager** | 몬스터 스폰 및 파동 제어 |
| **ObjectPool** | 재사용 가능한 오브젝트(투사체 등) 관리 |
| **TimeManager** | DeltaTime 및 FPS 계산 |
| **InputManager** | 키보드 입력 처리 |
| **ResourceManager** | 이미지/리소스 로딩 관리 |

---

## 구성 모듈 요약

- **Component System**: Transform, SpriteRenderer, Animator, Collider 등
- **Manager System**: Input, Time, Object, Scene, Resource, Collision, Camera
- **Scene System**: 타이틀 화면, 인게임, 종료 화면 등
- **Object Pool**: 투사체 및 반복 생성 객체 재사용
- **Rendering**: BitBlt 및 GDI 기반 2D 렌더링

---

## 게임 루프

Main.cpp
↓
GameManager::Init()
↓
GameManager::Update()
↓
GameManager::Render()

---

## 오브젝트 풀 사용 예시 (폭탄 객체)

```cpp
// 폭탄 객체를 풀에서 꺼내어 위치 설정 후 게임에 추가
BombObj* bomb = ObjectPool::Get()->GetBomb();
bomb->SetPosition(player->GetPosition());
ObjectManager::Get()->AddObject(bomb);

현재 집중 중인 개발 목표

경험치 드롭 및 레벨업 시스템

장비의 세부 기능 및 강화 시스템

참고 출처

원작 게임: HoloCure by Kay Yu

해당 프로젝트는 비영리 목적의 포트폴리오 용도로만 사용됩니다.

개발자
BeomChi

GitHub: https://github.com/BeomChi
