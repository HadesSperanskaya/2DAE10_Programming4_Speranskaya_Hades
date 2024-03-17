#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"


using namespace Engine;

void load()
{

	auto font = Minigin::m_ResourceManagerPointer->LoadFont("Lingua.otf", 36);


	//while it should Not be possible to create components outside objects, as they must always be owned by an object
	//this is currently not the case in my project yet, as i use composition to create some components
	//and am still thinking about the optimal solution to continue being able to do that while disabling the creation of free floating components in here


	auto fpsObject = new GameObject();
	fpsObject->AddTexture2DComponent("Background2DTexture", Minigin::m_ResourceManagerPointer->LoadTexture("background.tga"));
	fpsObject->AddTextComponent("TextComponentForFPS", font);
	fpsObject->AddFPSComponent(fpsObject->GetComponentByName("TextComponentForFPS"));
	Minigin::m_ScenePointer->Add(fpsObject);


	auto logoObject = new GameObject();
	logoObject->AddTexture2DComponent("LogoTexture", Minigin::m_ResourceManagerPointer->LoadTexture("logo.tga"));
	logoObject->SetPosition(216, 180);
	Minigin::m_ScenePointer->Add(logoObject);


	auto assignmentLabelObject = new GameObject();
	assignmentLabelObject->AddTextComponent("AssignmentLabelTextComponent", font, "Programming 4 Assignment");
	assignmentLabelObject->SetPosition(80, 20);
	Minigin::m_ScenePointer->Add(assignmentLabelObject);


	/*

	auto characterOneObject = std::make_shared<GameObject>();
	characterOneObject->AddTexture2DComponent("CharacterSprite", Engine::ResourceManager::GetInstance().LoadTexture("sprite_01.png"));
	characterOneObject->SetPosition(0, 0);
	scene.Add(characterOneObject);


	auto characterTwoObject = std::make_shared<GameObject>();
	characterTwoObject->AddTexture2DComponent("CharacterSprite", Engine::ResourceManager::GetInstance().LoadTexture("sprite_02.png"));
	characterTwoObject->SetPosition(0, 0);
	scene.Add(characterTwoObject);*/




}



int main(int, char*[]) {
	Engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}