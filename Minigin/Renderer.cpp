#include <stdexcept>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

#include "Texture2D.h"
#include "Renderer.h"
#include "Scene.h"


using namespace Engine;

SDL_Renderer* Renderer::m_SDLRenderer = nullptr;

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

void Renderer::RenderTexture(Texture2D* texture, const float x, const float y) 
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(m_SDLRenderer, texture->GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(Texture2D* texture, const float x, const float y, const float width, const float height)
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(m_SDLRenderer, texture->GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
	return m_SDLRenderer;
};
