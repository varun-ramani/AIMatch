#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Arrow = 0,
			Life = 1,
			Particle = 2,

			Count,
		};
	}

	inline const char *GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Arrow:
			return "images.png";
		case eTexture::Life:
			return "bird.png";
		case eTexture::Particle:
			return "circle_02.png";
		default:
			return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager *GetInstance()
		{
			if (!sm_instance)
				sm_instance = new TextureManager();
			return sm_instance;
		}
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture *GetTexture(eTexture::type texture) const
		{
			return m_textures[(int)texture];
		}

	private:
		TextureManager();
		static TextureManager *sm_instance;

		sf::Texture *m_textures[eTexture::Count];
	};
} // namespace GameEngine

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}
