# HoloCure Clone Project

WinAPI와 C++를 기반으로 제작한 HoloCure 클론 프로젝트입니다.

게임 루프, Scene 관리, Object Pool, Signal(Event) 시스템 등을 직접 구현하며
게임 프레임워크 구조와 객체 생명주기 관리에 대한 이해를 목표로 진행하였습니다.

## 주요 목표

- WinAPI 기반 게임 프레임워크 제작
- Scene 기반 객체 관리
- Object Pool 구현
- Signal(Event) 시스템 구현
- UI Framework 제작

## 기술 스택

- C++
- WinAPI
- GDI
- STL

## 디자인 패턴

- Singleton
- Observer Pattern
- Component Pattern
- Object Pooling

## 프로젝트 구조

![구조도 이미지(main)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-메인%20구조도.drawio.png)

### Scene System

ObjectManager 중심의 객체 관리 구조를 Scene 중심 구조로 변경하였다.

Scene이 객체의 생성 / 삭제 / 생명주기를 관리하며
씬 전환 시 불필요한 객체 순회를 방지하였다.

#### 개선 전

![ObjectManager](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-ObjectManager%20To%20Scene_1.drawio.png)

#### 개선 후

![ObjectManager](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-ObjectManager%20To%20Scene_2.drawio.png)


### Equipment System

#### 초기 설계

초기에는 Unity Component 구조를 참고하여 조합하는 구조를 고려하였다.

![초기 설계 구조도 이미지](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Equipment_1.drawio.png)

장비 데이터를 독립 컴포넌트로 분리하고, 필요한 기능을 조합하여 
재사용 가능한 구조를 목표로 하였다.

#### 문제

장비별로 다음과 같은 차이가 존재하였다.

- 공격 판정( 투사체 / 범위 공격)
- 특수 효과
- 레벨 효과
- 넉백 및 추가 공격 효과

프로젝트 진행 과정에서 장비별 요구 기능 차이가 증가하였다.

공통 컴포넌트만으로 처리할 경우
컴포넌트 수와 조합 복잡도가 증가하였고,
현재 프로젝트 규모에서는 관리 비용이 더 커질 것으로 판단하였다.

#### 변경 후

장비별 기능 차이를 고려하여 상속 기반 구조로 변경하였다.

![구조도 이미지(장비 현재)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Equipment_2.drawio.png)

각 장비는 고유한 능력치와 동작을 직접 구현하도록 설계하였다.
그 결과 장비 종류별 전용 클래스가 존재하는 구조가 되었다.

#### 고찰점

초기에는 범용성과 재사용성을 우선하여 컴포넌트 기반 구조를 생각하였지만,
현재 프로젝트 규모와 구조에서는 장비별 차이가 커 상속 기반 구조가 더 적합하다고 판단하였다.
향후에는 데이터 기반 설계와 기능 모듈화를 적용하여 재사용 가능 구조를 검토할 예정이다.

#### 향후 개선 방향

현재는 장비별 개별 구현 방식을 사용하였다.

향후에는 공격 방식, 상태 이상, 특수 효과를 독립 기능으로 분리하여 :

- 회전 공격
- 방향 지정 공격
- 지속 피해
- 추가 공격 (연속 공격)

등을 조합 가능한 구조로 개선하는 것을 검토하고 있다.



### 장비 선택 UI

#### 의도

플레이어 레벨업 시 무작위 장비 후보를 생성하고,
이를 UI에 표시하여 플레이어가 장비를 선택할 수 있도록 설계하였다.

![장비선택](./p1/이미지%20작업파일/ReadMe_Image/SelectEquipment.gif)

UI는 기능 단위별 Panel로 구성하였다.

![구조도 이미지(UI Panel)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-UI%20Panel_1.drawio.png)

![구조도 이미지(UI Panel)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-UI%20Panel_2.drawio.png)


#### 동작 방식

1. 플레이어 레벨업 발생
2. EquipmentManager에서 장비 후보 벡터를 생성
3. UI Panel에 데이터를 전달
4. 선택 시 해당 장비 장착 또는 해당 장비를 가지고 있는 경우 업그레이드를 진행

이미 보유한 장비일 경우 다음 레벨 효과를 표시하도록 구성하였다.

#### 특징

장비를 랜덤으로 리스트를 만들어서 UI에 정보를 넘겨주고 선택된 장비가
착용 또는 업그레이드가 진행이 되도록 하였다.

### FSM

![구조도 이미지(UI Panel)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-FSM_1.drawio.png)

#### 문제

상태 전환 시 애니메이션 변경 코드가 여러 곳에 흩어져 있었고
상태 변경 시 애니메이션 갱신이 누락되는 경우가 발생하였다.

#### 해결

상태를 변경해 주는 함수를 도입하였다.
```
SetState(State state);
```

상태 전환은 해당 함수로만 이루어지게 하였고
상태 변경 시 상태가 갱신이 되고 애니메이션 교체를 수행하도록 하였다.

SetState 호출시

![구조도 이미지(UI Panel)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-FSM_2.drawio.png)

1. 현재 상태와 새로운 상태가 같은지 판별
2. 상태가 다를 경우 상태 변경
3. 애니메이션 변경

을 수행하도록 하였다.


#### 결과

- 애니메이션 전환 누락 방지
- 호출 코드 단순화
- 디버깅 용이성 향상

### Collider

#### 의도
게임 로직과 충돌 처리를 분리하기 위해 Collider 시스템 제작

![구조도 이미지(SceneUpdate)](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Scene%20개선_2.drawio.png)

#### 구현

![AABB](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-AABB.drawio.png)

충돌 판정에는 AABB(Axis-Aligned Bounding Box)를 사용하였다.

각 객체의 중심 좌표와 크기를 기반으로
축 정렬 사각형 간 겹침 여부를 계산하여 충돌 판정하였다.

#### 고찰
프로젝트 규모상 Unity 같은 상용엔진 수준으로 세분화의 필요성을 느끼지 않아
게임 로직 / 충돌 처리 정도로 단순 분리하였다.


### Camera

#### 의도

맵 크기가 화면보다 크기에 플레이어 이동 시 카메라 추적 기능이 필요하였다.
카메라 위치 기준으로 월드 좌표를 화면 좌표로 변환하여 렌더링하였다.

#### 구현

초기에는 Component 구조를 고려하였다.
그러나 카메라를 독립적인 객체로 관리하는 것이
역할과 책임을 명확히 분리하는 데 더 적합하다고 판단하였다.

카메라가 GameObject를 상속 받은 형태로 변경하였다.

#### 기능

- Target 추적
- 자유 이동
- World -> Screen 변환 혹은 Screen -> World

```
Vec2 SceneManager::WorldToScreen(Vec2 pos)
{
	return pos - _cameraPos + Vec2(GWinSizeX / 2, GWinSizeY / 2);
}

Vec2 SceneManager::ScreenToWorld(Vec2 pos)
{
	return pos + _cameraPos - Vec2(GWinSizeX / 2, GWinSizeY / 2);
}
```

#### 구조
SceneManager가 현재 Scene의 Camera 위치를 관리한다.
렌더 시

![Camera](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Camera.drawio.png)

변환을 수행한다.

### Object Pool

#### 의도

투사체나 몬스터 등 반복적으로 많이 사용되는 객체가 많아
이걸 일일이 생성 및 삭제가 이루어지는 비용이 들어
동적 할당 및 해제 비용을 줄이기 위해
생성된 객체를 재사용하는 Object Pool 구조를 적용하였다.
미리 만들어 놓은 스톡이 부족한 경우 추가 생성하도록 구성을 하였다.

#### 문제

비활성 객체를 씬 내에서 들고 필요할 때마다 뒤에서부터 활성화 하였다.
부족하면 새로이 만들고 하여 삭제 비용을 최소화하려고 하였으나
비활성 객체가 씬에 계속 누적이 되며 순회하는 비용이 증가 하였다.

#### 해결

Object Pool을 만들어서 비활성화된 객체를 씬에서 제거하고
풀로 옮겨주고 씬의 순회 비용을 감소 시켜주었고

![Pool](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Pool.drawio.png)

반대로 풀에 있던 객체를 꺼내서 씬에 다시 넣어줌으로써 객체를 새로 만드는 것이 아닌
기존에 있던 객체를 Reset 함수를 호출하여 초기화를 시켜주고 재사용하였다.

#### 결과

- 몬스터 재사용 가능
- 투사체 재사용 가능
- 동적 할당 감소

#### 특징

- 비활성 객체 재사용
- 기본 UI는 예외처리(BaseUI or 게임 종료 같은 상황이나 씬전환 같은 상황시 비활성화 되는 애들은 제외)
- Scene 반환 구조

### Signal

#### 의도

기존에는 클래스간 서로 들고 있어서 의존성이 높은 상태였는데
의존성 해결을 위해 객체 간 직접 참조를 줄이고 의존성을 완화하기 위해 Signal(Event) 시스템을 도입하였다.
이벤트를 발행하면 구독 중인 객체가 이를 수신하는 구조로 설계를 변경 하는 것이 의존성 해결에 좋다고 생각하였다.

![Signal](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Signal.drawio.png)

##### 사용 사례
- HP 갱신
- EXP 갱신
- 레벨업 UI
- Game Over
- 장비 선택 UI

#### 특징

- Observer Pattern 기반
- Connection 구독 관리
- 자동 Disconnect
- 객체 결합도 감소

### EditScene

#### 원인

UI 배치 수정 시 좌표 수정 후 실행 후 확인
반복 작업이 발생,
이를 해결하고자 도입하였다.

#### 해결

EditScene을 만들어 Scene 내에서 UI를 선택하여 이동이 가능하게 하고

![uiSelect](./p1/이미지%20작업파일/ReadMe_Image/uiSelect.gif)

해당 UI의 좌표와 키 값을 저장하여 UI 초기화를 할 때 저장된 키 값을 기반으로 UI 정보를 로드하도록 구현하였다.

![uiLoad](./p1/이미지%20작업파일/ReadMe_Image/uiLoad.gif)

#### 결과

- UI 배치 작업 효율 증가
- 런타임 중 위치 수정 가능
- UI 레이아웃 데이터 저장 가능

#### 기능

- 위치 조정
- 저장, 불러오기

## 트러블 슈팅

### Scene

#### 문제

업데이트 중 객체 추가 / 삭제가 발생하면 문제가 발생하였다.

![이전 로직 구조도](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Scene%20개선_1.drawio.png)


객체 제거 이후 이미 제거된 객체 접근이나 잘못된 포인터로 접근하여 크래시가 발생하였다.

#### 해결

예약 시스템 도입

![현재 SceneUpdate 로직 구조도](./p1/이미지%20작업파일/ReadMe_Image/HoloCureCloneMain1-Scene%20개선_2.drawio.png)

즉시 추가 / 삭제를 수행하지 않고 로직 수행 후로 미루는 방식으로 처리하였다.

#### 결과

- Iterator 무효화 방지
- 생명 주기 안정화
- Update 중 안전한 생성 / 삭제 가능
- Scene 전환 시 객체 정리 단순화
- 객체 생명주기 관리 분리

### Signal

#### 문제

Signal 구독 시스템 구현 중 이벤트가 즉시 해제되는 문제가 발생

```
_expConn = std::move( player->OnExpChanged += ...	);

```

구독 직후 이벤트가 비정상적으로 끊어짐

#### 원인 분석

초기 구현은 Connection 이동 생성자가 실제 상태 이전을 수행하지 않았다.
```
Connection(Connection&&) noexcept
	{
		cout << "[DEBUG] Connection 이동 생성" << endl;
	}
```
이동 생성자 호출 여부를 확인하기 위해 디버그 로그만 남겨두고 실제 이전 로직을 구현하지 않았다.
operator += 결과로 생성된 임시 Connection 객체가 이동 후 소멸되며
결과적으로 
```
~Connection() { Disconnect(); }
```
호출하게 되어 구독이 제거가 되었다.

#### 해결

- Move semantics 수정
- Connection 생명주기 재설계
- shared_ptr<Node>, weak_ptr<Node> 도입
- Signal 파괴 시 dangling pointer 방지

#### 배운 점

처음에는 smart pointer 도입으로 문제가 해결 되었다고 판단했으나,
이후 분석 과정에서 실제 원인이 Move semantics와 객체 생명주기 관리였음을 확인하였다.
이 경험을 통해 포인터 종류보다 소유권과 객체 생명주기 설계의 중요함을 학습하였다.

### 월드 좌표 / 스크린 좌표 문제

#### 문제

DamageText가 카메라 이동 시 비정상적인 위치에 출력되는 문제가 발생하였다.

#### 원인

월드 좌표와 화면 좌표를 혼합하여 사용하고 있었다.
카메라 이동 시 월드 좌표와 화면 좌표 간 오차가 누적되었다.

#### 해결

렌더링 시 카메라 기준 좌표 변환을 적용하였다.


#### 고찰점

GDI의 TextOut이 무거워서 프레임 방어가 어렵다.
그래서 숫자 비트맵을 통해서 데미지를 출력하는 방식으로 변경하였다.

### 레벨업 중 비정상적 공격 발생

#### 문제

게임 정지 상태(LevelUp UI)에서도 공격 객체가 생성되는 문제가 발생하였다.

#### 증상

- 게임이 UI를 제외한 게임 로직은 정지 상태여야 하지만 장비는 계속 동작하였다.
- 장비 선택을 하지 않고 일정 시간 대기 후 선택하면, 그동안 생성된 투사체들이 한 번에 활성화되며
다수의 피해가 발생하였다.
- 일부 상황에서는 정상적인 쿨타임 규칙을 벗어나 동일한 공격 객체가 여러 개 존재하는 현상이 발생하였다.

#### 원인

EquipmentManager Update에서 게임 상태를 확인하지 않고 장비 업데이트를 수행하고 있었다.

그 결과 레벨업 UI로 게임이 정지된 상태에서도 장비 쿨타임이 계속 진행되었고, 공격 객체가 생성되고 있었다.

#### 해결

```
if (GET_SINGLE(GameManager)->GetState() != GameState::Playing)
	return;

```

게임 상태가 Playing 일 때만 장비 업데이트가 수행되도록 수정하였다.

#### 결과

- 레벨업 중 공격 객체 생성 방지
- 의도하지 않은 투사체 누적 제거
- 게임 정지 상태와 실제 시스템 동작 일치

#### 배운 점

게임 상태(State)를 도입하는 것만으로는 충분하지 않으며,

각 시스템이 현재 상태에서 동작해야 하는지, 정지해야 하는지 명확히 정의하는 것의
중요함을 배웠다.

또한 객체 자체의 버그보다 상위 게임 상태 관리가 예상치 못한 문제의 원인이 될 수 있다는
점을 경험하였다.


## Retrospective

프로젝트를 진행하며 Scene 기반 객체 관리,
Object Pool, Signal(Event) 시스템 등을 직접 구현하면서
객체 생명주기와 의존성 관리의 중요성을 학습할 수 있었다.

특히 Signal 시스템 구현 과정에서 발생한 Move Semantics 문제를 분석하며
스마트 포인터 자체보다 객체의 소유권과 생명주기 설계가 더 중요하다는 점을 경험하였다.

향후에는 Engine / Content Layer를 더욱 명확히 분리하고
데이터 기반 장비 시스템을 도입하여 확장성을 개선할 예정이다.

프로젝트 초반에는 기능 구현에 집중하였으나,
개발이 진행될수록 객체 생명주기 관리와 시스템 간 의존성 관리가
프로젝트 안전성에 큰 영향을 준다는 점을 경험하였다.

특히, Scene, Object Pool, Signal 시스템을 직접 구현하고
관련 문제를 디버깅하는 과정에서
단순 기능 구현보다 설계와 책임 분리가 중요하다는 점을 학습할 수 있었다.

