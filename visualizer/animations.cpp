#include "animations.h"
#include "plants.h"

namespace visualizer
{
	void DrawFadedObject::animate(const float &t, AnimData *d, IGame *game)
	{
		// Set the color to red
		float scalar = t;
		if(m_fade == FadeIn)
		{
			scalar = t;
		}
		else if(m_fade == FadeOut)
		{
			scalar = 1 - t;
		}
		else
		{
			scalar = 1.0f;
		}

		//float color = m_data->fade
		game->renderer->setColor(Color(m_color.r, m_color.g, m_color.b, m_color.a * scalar));
	}

	void DrawQuad::animate( const float& t, AnimData* d, IGame* game )
	{
		DrawFadedObject::animate(t, d, game);

		game->renderer->drawQuad( m_data->x, m_data->y, m_data->width, m_data->height );
	}

	void DrawCircle::animate( const float& t, AnimData* d, IGame* game )
	{
		DrawFadedObject::animate(t, d, game);

		game->renderer->drawCircle( m_data->x, m_data->y, m_data->radius, 1, 100 );
	}

	void DrawTexturedCircle::animate(const float &t, AnimData *d, IGame *game)
	{
		// TODO: move this logic to offset the circle out of here
		static float dt = 0.0f;
		dt += game->timeManager->getDt();

		DrawFadedObject::animate(t, d, game);
		game->renderer->drawTexturedCircle(m_data->x, m_data->y, m_data->radius, 1, 100, m_data->texture, 0.0f, 0.1 * cos(0.02*dt), 0.1 * sin(0.02*dt));
	}

	void DrawSprite::animate( const float& t, AnimData* d, IGame* game )
	{
		DrawFadedObject::animate(t, d, game);

		game->renderer->drawTexturedQuad( m_data->x, m_data->y, m_data->width, m_data->height, 1, m_data->texture );
	}
}
