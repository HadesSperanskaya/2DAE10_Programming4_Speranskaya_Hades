#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"


using namespace Engine;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	//while it should Not be possible to create components outside objects, as they must always be owned by an object
	//this is currently not the case in my project yet, as i use composition to create some components
	//and am still thinking about the optimal solution to continue being able to do that while disabling the creation of free floating components in here


	auto fpsObject = std::make_shared<GameObject>();
	fpsObject->AddTexture2DComponent("Background2DTexture", ResourceManager::GetInstance().LoadTexture("background.tga"));
	fpsObject->AddTextComponent("TextComponentForFPS", font);
	fpsObject->AddFPSComponent(fpsObject->GetComponentByName("TextComponentForFPS"));
	scene.Add(fpsObject);


	auto logoObject = std::make_shared<GameObject>();
	logoObject->AddTexture2DComponent("LogoTexture", Engine::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	logoObject->SetPosition(216, 180);
	scene.Add(logoObject);


	auto assignmentLabelObject = std::make_shared<GameObject>();
	assignmentLabelObject->AddTextComponent("AssignmentLabelTextComponent", font, "Programming 4 Assignment");
	assignmentLabelObject->SetPosition(80, 20);
	scene.Add(assignmentLabelObject);


	auto orbitTargetObject = std::make_shared<GameObject>();
	orbitTargetObject->SetPosition(100, 100);
	scene.Add(orbitTargetObject);


	auto characterOneObject = std::make_shared<GameObject>();
	characterOneObject->AddTexture2DComponent("CharacterSprite", Engine::ResourceManager::GetInstance().LoadTexture("sprite_01.png"));
	characterOneObject->SetPosition(0, 0);
	characterOneObject->AddRotatorComponent("Rotator");
	characterOneObject->SetParent(std::weak_ptr<GameObject>(orbitTargetObject));
	scene.Add(characterOneObject);


	auto characterTwoObject = std::make_shared<GameObject>();
	characterTwoObject->AddTexture2DComponent("CharacterSprite", Engine::ResourceManager::GetInstance().LoadTexture("sprite_02.png"));
	characterTwoObject->SetPosition(0, 0);
	characterTwoObject->AddRotatorComponent("Rotator");
	characterTwoObject->SetParent(std::weak_ptr<GameObject>(characterOneObject));
	scene.Add(characterTwoObject);


}



int main(int, char*[]) {
	Engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}