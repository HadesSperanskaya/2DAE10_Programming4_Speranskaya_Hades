#include <SDL.h>
#include <Windows.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "ResourceOwner.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "InputHandler.h"



using namespace Engine;

void load(Minigin* engine)
{

	auto font = ResourceOwner::LoadFont("Lingua.otf", 36);


	//while it should Not be possible to create components outside objects, as they must always be owned by an object
	//this is currently not the case in my project yet, as i use composition to create some components
	//and am still thinking about the optimal solution to continue being able to do that while disabling the creation of free floating components in here


	auto fpsObject = new GameObject();
	fpsObject->AddTexture2DComponent("Background2DTexture", ResourceOwner::LoadTexture("background.tga"));
	fpsObject->AddTextComponent("TextComponentForFPS", font);
	fpsObject->AddFPSComponent(fpsObject->GetComponentByName("TextComponentForFPS"));
	engine->m_ScenePointer->Add(fpsObject);


	auto logoObject = new GameObject();
	logoObject->AddTexture2DComponent("LogoTexture", ResourceOwner::LoadTexture("logo.tga"));
	logoObject->SetLocalPosition(216, 180);
	engine->m_ScenePointer->Add(logoObject);


	auto assignmentLabelObject = new GameObject();
	assignmentLabelObject->AddTextComponent("AssignmentLabelTextComponent", font, "Programming 4 Assignment");
	assignmentLabelObject->SetLocalPosition(80, 20);
	engine->m_ScenePointer->Add(assignmentLabelObject);


	auto characterOneObject = new GameObject();
	characterOneObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_01.png"));
	characterOneObject->SetLocalPosition(0, 0);
	engine->m_ScenePointer->Add(characterOneObject);
	engine->m_InputHandlerPointer->AssignActorToKeyboard(1, characterOneObject);


	auto characterTwoObject = new GameObject();
	characterTwoObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_02.png"));
	characterTwoObject->SetLocalPosition(0, 0);
	engine->m_ScenePointer->Add(characterTwoObject);


	engine->m_InputHandlerPointer->AssignActorToFirstFreeXinputController(characterTwoObject);


}



int main(int, char*[]) {
	Engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}