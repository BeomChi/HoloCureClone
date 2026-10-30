#pragma once
#include "97.Engin/Component/Component.h"

enum class ProjectionType
{
    Perspective,
    Orthographic,
};

class Camera : public Component
{
    using Super = Component;
public:
    Camera();
    virtual ~Camera();

    virtual void Update() override;

    void SetProjectionType(ProjectionType type) { _type = type; }
    ProjectionType GetProjectionType() { return _type; }

    void UpdateMatrix();
private:
    ProjectionType _type = ProjectionType::Orthographic;

public:
    static Matrix s_matView;
    static Matrix s_matProjection;
};

