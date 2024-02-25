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


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	//while it should Not be possible to create components outside objects, as they must always be owned by an object
	//this is currently not the case in my project yet, as i use composition to create some components
	//and am still thinking about the optimal solution to continue being able to do that while disabling the creation of free floating components in here


	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddTexture2DComponent("Background2DTexture", dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
	fpsObject->AddTextComponent("TextComponentForFPS", font);
	fpsObject->AddFPSComponent(fpsObject->GetComponentByName("TextComponentForFPS"));
	fpsObject->AddComponentPointerToRenderComponentByName("Background2DTexture");
	fpsObject->AddComponentPointerToRenderComponentByName("TextComponentForFPS");


	scene.Add(fpsObject);



	auto logoObject = std::make_shared<dae::GameObject>();
	logoObject->AddTexture2DComponent("LogoTexture", dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	logoObject->SetPosition(216, 180);
	logoObject->AddComponentPointerToRenderComponentByName("LogoTexture");

	scene.Add(logoObject);

	auto assignmentLabelObject = std::make_shared<dae::GameObject>();
	assignmentLabelObject->AddTextComponent("AssignmentLabelTextComponent", font, "Programming 4 Assignment");
	assignmentLabelObject->SetPosition(80, 20);
	assignmentLabelObject->AddComponentPointerToRenderComponentByName("AssignmentLabelTextComponent");

	scene.Add(assignmentLabelObject);



}



int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}