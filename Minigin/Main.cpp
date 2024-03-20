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
	characterOneObject->AddLocomotionComponent("Walking", 100.f);
	characterOneObject->SetLocalPosition(0, 0);
	engine->m_ScenePointer->Add(characterOneObject);


	engine->m_InputHandlerPointer->AssignActorToKeyboard(0, characterOneObject);

	glm::vec2 up{ 0.f, 1.f };
	glm::vec2 down{ 0.f, -1.f };
	glm::vec2 left{ -1.f, 0.f };
	glm::vec2 right{ 1.f, 0.f };

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_s, SDL_PRESSED,  new MoveCommand(up));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_s, SDL_RELEASED, new MoveCommand(down));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_w, SDL_PRESSED, new MoveCommand(down));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_w, SDL_RELEASED, new MoveCommand(up));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_a, SDL_PRESSED, new MoveCommand(left));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_a, SDL_RELEASED, new MoveCommand(right));

	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_d, SDL_PRESSED, new MoveCommand(right));
	engine->m_InputHandlerPointer->AssignCommandToKeyboardInput(SDLK_d, SDL_RELEASED, new MoveCommand(left));


	auto characterTwoObject = new GameObject();
	characterTwoObject->AddTexture2DComponent("CharacterSprite", ResourceOwner::LoadTexture("sprite_02.png"));
	characterTwoObject->SetLocalPosition(0, 100);
	characterTwoObject->AddLocomotionComponent("Walking", 100.f);

	engine->m_ScenePointer->Add(characterTwoObject);

	engine->m_InputHandlerPointer->AssignActorToAllXinputControllers(characterTwoObject);

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadDown, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(up));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadDown, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(down));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadUp, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(down));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadUp, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(up));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadLeft, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(left));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadLeft, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(right));

	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadRight, XINPUT_CONTROLLER_BUTTON_STATE::WasPressed, new MoveCommand(right));
	engine->m_InputHandlerPointer->AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON::DpadRight, XINPUT_CONTROLLER_BUTTON_STATE::WasReleased, new MoveCommand(left));


}



int main(int, char*[]) {
	Engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}