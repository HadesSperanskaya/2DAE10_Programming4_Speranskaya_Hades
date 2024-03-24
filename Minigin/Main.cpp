
#pragma warning( push)
#pragma warning(disable: 4996)
#include <steam_api.h>
#include <SDL.h>
#include <iostream>
#pragma warning( pop )


#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "GameObject.h"
#include "ResourceOwner.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "InputHandler.h"

#include "Command.h"
#include "CommandsSetPlayer.h"
#include "SubjectComponent.h"
#include "ObserverComponent.h"
#include "TextComponent.h"

#include "EventSetOne.h"

using namespace Engine;

void SetControls(Minigin* engine)
{

	glm::vec2 up{ 0.f, 1.f };
	glm::vec2 down{ 0.f, -1.f };
	glm::vec2 left{ -1.f, 0.f };
	glm::vec2 right{ 1.f, 0.f };

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_s, SDL_PRESSED, new MoveCommand(up));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_s, SDL_RELEASED, new MoveCommand(down));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_w, SDL_PRESSED, new MoveCommand(down));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_w, SDL_RELEASED, new MoveCommand(up));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_a, SDL_PRESSED, new MoveCommand(left));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_a, SDL_RELEASED, new MoveCommand(right));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_d, SDL_PRESSED, new MoveCommand(right));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_d, SDL_RELEASED, new MoveCommand(left));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_x, SDL_PRESSED, new TakeDamage());
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_t, SDL_PRESSED, new GetPoints());


	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadDown, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(up));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadDown, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(down));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadUp, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(down));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadUp, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(up));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadLeft, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(left));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadLeft, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(right));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadRight, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(right));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadRight, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(left));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::B, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new TakeDamage());
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::A, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new GetPoints());

}

void CreateBackground(Minigin* engine, Font* font)
{
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
}

void DisplayControlsInformation(Minigin* engine, Font* font)
{
	auto controlsInfo = new GameObject();
	std::string controlsKeyboard {"WASD to move the monster, X to inflict damage, key T to get points"};
	std::string controlsXbox{ "DPAD to move the other character, button B to inflict damage, button A to get points" };

	controlsInfo->AddTextComponent("KeyboardControls", font, controlsKeyboard);
	controlsInfo->AddTextComponent("XboxControls", font, controlsXbox);

	static_cast<TextComponent*>(controlsInfo->GetComponentByName("XboxControls"))->SetPosition(0, -20);


	controlsInfo->SetLocalPosition(10, 100);
	engine->m_ScenePointer->Add(controlsInfo);


}

void load(Minigin* engine)
{
	SetControls(engine);

	auto font = ResourceOwner::LoadFont("Lingua.otf", 30);
	auto fontSmaller = ResourceOwner::LoadFont("Lingua.otf", 15);

	CreateBackground(engine, font);
	DisplayControlsInformation(engine, fontSmaller);


	auto uiPlayerOneHealth = new GameObject();
	uiPlayerOneHealth->AddUITextComponent("UiPlayerHealth", fontSmaller, "5", "# of lives: ");
	uiPlayerOneHealth->SetLocalPosition(10, 130);
	uiPlayerOneHealth->AddObserverComponent("Health", new UpdateLifeTrackerUI());
	engine->m_ScenePointer->Add(uiPlayerOneHealth);

	auto uiPlayerOnePoints = new GameObject();
	uiPlayerOnePoints->AddUITextComponent("UiPlayerScore", fontSmaller,  "0", "Score: ");
	uiPlayerOnePoints->SetLocalPosition(10, 145);
	uiPlayerOnePoints->AddObserverComponent("Score", new UpdatePointTrackerUI());
	engine->m_ScenePointer->Add(uiPlayerOnePoints);



	auto characterOneObject = new GameObject();
	engine->m_ScenePointer->Add(characterOneObject);
	engine->m_InputHandlerPointer->AssignActorToKeyboard(0, characterOneObject);
	characterOneObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_01.png"));
	characterOneObject->AddLocomotionComponent("Walking", 100.f);
	characterOneObject->SetLocalPosition(0, 200);
	characterOneObject->AddHealthComponent(100, 5);
	characterOneObject->AddScoreTrackerComponent();
	characterOneObject->AddSubjectComponent();

	auto* observerOneHealth = static_cast<ObserverComponent*>(uiPlayerOneHealth->GetComponentByType(COMPONENT_TYPE::ObserverComponent));
	auto* observerOneScore = static_cast<ObserverComponent*>(uiPlayerOnePoints->GetComponentByType(COMPONENT_TYPE::ObserverComponent));

	static_cast<SubjectComponent*>(characterOneObject->GetComponentByType(COMPONENT_TYPE::SubjectComponent))->AddObserver(observerOneHealth, characterOneObject->GetComponentByType(COMPONENT_TYPE::HealthComponent));
	static_cast<SubjectComponent*>(characterOneObject->GetComponentByType(COMPONENT_TYPE::SubjectComponent))->AddObserver(observerOneScore, characterOneObject->GetComponentByType(COMPONENT_TYPE::ScoreTrackerComponent));



	auto uiPlayerTwoHealth = new GameObject();
	uiPlayerTwoHealth->AddUITextComponent("UiPlayerHealth", fontSmaller, "5", "# of lives: ");
	uiPlayerTwoHealth->SetLocalPosition(10, 160);
	uiPlayerTwoHealth->AddObserverComponent("Health", new UpdateLifeTrackerUI());
	engine->m_ScenePointer->Add(uiPlayerTwoHealth);

	auto uiPlayerTwoPoints = new GameObject();
	uiPlayerTwoPoints->AddUITextComponent("UiPlayerScore", fontSmaller, "0", "Score: ");
	uiPlayerTwoPoints->SetLocalPosition(10, 175);
	uiPlayerTwoPoints->AddObserverComponent("Score", new UpdatePointTrackerUI());
	engine->m_ScenePointer->Add(uiPlayerTwoPoints);



	auto characterTwoObject = new GameObject();
	engine->m_ScenePointer->Add(characterTwoObject);
	engine->m_InputHandlerPointer->AssignActorToAllXinputControllers(characterTwoObject);
	characterTwoObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_02.png"));
	characterTwoObject->SetLocalPosition(50, 200);
	characterTwoObject->AddLocomotionComponent("Walking", 100.f);
	characterTwoObject->AddHealthComponent(100, 5);
	characterTwoObject->AddScoreTrackerComponent();


	auto* observerTwoHealth = static_cast<ObserverComponent*>(uiPlayerTwoHealth->GetComponentByType(COMPONENT_TYPE::ObserverComponent));
	auto* observerTwoScore = static_cast<ObserverComponent*>(uiPlayerTwoPoints->GetComponentByType(COMPONENT_TYPE::ObserverComponent));

	static_cast<SubjectComponent*>(characterOneObject->GetComponentByType(COMPONENT_TYPE::SubjectComponent))->AddObserver(observerTwoHealth, characterTwoObject->GetComponentByType(COMPONENT_TYPE::HealthComponent));
	static_cast<SubjectComponent*>(characterOneObject->GetComponentByType(COMPONENT_TYPE::SubjectComponent))->AddObserver(observerTwoScore, characterTwoObject->GetComponentByType(COMPONENT_TYPE::ScoreTrackerComponent));





}



int main(int, char*[]) 
{
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
	}


	Engine::Minigin engine("Data/");
	engine.Run(load);

	SteamAPI_Shutdown();

    return 0;
}