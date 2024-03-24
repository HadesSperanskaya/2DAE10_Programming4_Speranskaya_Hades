#include <SDL.h>

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
#include "HealthComponent.h"
#include "UITextComponent.h"


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

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_X, SDL_PRESSED, new TakeDamage());
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_e, SDL_PRESSED, new GetPoints());


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
	auto controlsInformation = new GameObject();
	std::string controls {"WASD to move the monster, X to inflict damage, key E to get points \n"};
	controls += "DPAD to move the other character, button B to inflict damage, button A to get points";
	controlsInformation->AddTextComponent("AssignmentLabelTextComponent", font, controls);
	controlsInformation->SetLocalPosition(10, 100);
	engine->m_ScenePointer->Add(controlsInformation);
}

void load(Minigin* engine)
{
	SetControls(engine);

	auto font = ResourceOwner::LoadFont("Lingua.otf", 30);
	auto fontSmaller = ResourceOwner::LoadFont("Lingua.otf", 20);

	CreateBackground(engine, font);
	DisplayControlsInformation(engine, fontSmaller);


	auto healthOne = new GameObject();
	healthOne->AddUITextComponent("AssignmentLabelTextComponent", fontSmaller, "# of lives: ");
	healthOne->SetLocalPosition(10, 130);
	Observer* uiObserverPointerOne = static_cast<Observer*>(static_cast<UITextComponent*>(healthOne->GetComponentByType(COMPONENT_TYPE::UITextComponent)));
	engine->m_ScenePointer->Add(healthOne);



	auto characterOneObject = new GameObject();
	engine->m_ScenePointer->Add(characterOneObject);
	engine->m_InputHandlerPointer->AssignActorToKeyboard(0, characterOneObject);
	characterOneObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_01.png"));
	characterOneObject->AddLocomotionComponent("Walking", 100.f);
	characterOneObject->SetLocalPosition(0, 200);
	characterOneObject->AddHealthComponent(100, 5);

	static_cast<HealthComponent*>(characterOneObject->GetComponentByType(COMPONENT_TYPE::HealthComponent))->AddObserver(uiObserverPointerOne);



	auto healthTwo = new GameObject();
	healthTwo->AddUITextComponent("AssignmentLabelTextComponent", fontSmaller, "# of lives: ");
	healthTwo->SetLocalPosition(10, 150);
	Observer* uiObserverPointerTwo = static_cast<Observer*>(static_cast<UITextComponent*>(healthTwo->GetComponentByType(COMPONENT_TYPE::UITextComponent)));
	engine->m_ScenePointer->Add(healthTwo);



	auto characterTwoObject = new GameObject();
	engine->m_ScenePointer->Add(characterTwoObject);
	engine->m_InputHandlerPointer->AssignActorToAllXinputControllers(characterTwoObject);
	characterTwoObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_02.png"));
	characterTwoObject->SetLocalPosition(50, 200);
	characterTwoObject->AddLocomotionComponent("Walking", 100.f);
	characterTwoObject->AddHealthComponent(100, 5);

	static_cast<HealthComponent*>(characterTwoObject->GetComponentByType(COMPONENT_TYPE::HealthComponent))->AddObserver(uiObserverPointerTwo);





}



int main(int, char*[]) {
	Engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}