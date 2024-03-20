#include <stdexcept>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

#include "Texture2D.h"
#include "Renderer.h"
#include "Scene.h"
#include "Spritesheet.h"
#include "TransformComponent.h"


using namespace Engine;

SDL_Renderer* Renderer::m_SDLRenderer = nullptr;
int Renderer::m_GlobalTextureScale = 1;

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
};


Renderer::Renderer(SDL_Window* window)
{
	m_Window = window;
	if (m_SDLRenderer == nullptr)
	{
		m_SDLRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	}

	if (m_SDLRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

};

Renderer::~Renderer()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();


	if (m_SDLRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_SDLRenderer);
		m_SDLRenderer = nullptr;
	}
};

void Renderer::Render(Scene* scene)
{
	SDL_SetRenderDrawColor(m_SDLRenderer, m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	SDL_RenderClear(m_SDLRenderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	scene->Render();
	scene->RenderUI();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_SDLRenderer);
};

void Renderer::RenderTexture(Texture2D* texture, const Transform& transform)
{
	SDL_Rect destinationRect{};
	destinationRect.x = static_cast<int>(transform.position.x) * m_GlobalTextureScale;
	destinationRect.y = static_cast<int>(transform.position.y) * m_GlobalTextureScale;
	SDL_QueryTexture(texture->GetSDLTexture(), nullptr, nullptr, &destinationRect.w, &destinationRect.h);
	SDL_RenderCopyEx(m_SDLRenderer, texture->GetSDLTexture(), nullptr, &destinationRect, transform.rotation, nullptr, SDL_FLIP_NONE);
}

void Renderer::RenderSprite(Spritesheet* sprite, const Transform& transform, int animationIndex, int frame)
{
	SDL_Rect destinationRect{};
	destinationRect.x = static_cast<int>(transform.position.x);
	destinationRect.y = static_cast<int>(transform.position.y);
	destinationRect.w = sprite->GetWidth() * m_GlobalTextureScale;
	destinationRect.h = sprite->GetHeight() * m_GlobalTextureScale;

	SDL_Rect sourceRect{};

	sourceRect.x = sprite->GetAnimationInformation(animationIndex)->startColumn * sprite->GetWidth() + frame * sprite->GetWidth();
	sourceRect.y = sprite->GetAnimationInformation(animationIndex)->startRow * sprite->GetHeight();
	sourceRect.w = sprite->GetWidth();
	sourceRect.h = sprite->GetHeight();


	SDL_RenderCopyEx(m_SDLRenderer, sprite->GetSDLTexture(), &sourceRect, &destinationRect, transform.rotation, nullptr, SDL_FLIP_NONE);
}

