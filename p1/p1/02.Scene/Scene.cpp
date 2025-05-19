#include "../pch.h"
#include "Scene.h"
#include "../01.Manager/ObjectManager.h"
#include "../01.Manager/CollisionManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	
}

void Scene::Init()
{
	
}

void Scene::Update()
{
	GET_SINGLE(ObjectManager)->UpdateAll();
	GET_SINGLE(CollisionManager)->Update();
}

void Scene::Render(HDC hdc)
{
	GET_SINGLE(ObjectManager)->RenderAll(hdc);
}
