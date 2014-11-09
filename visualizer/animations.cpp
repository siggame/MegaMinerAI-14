#include "animations.h"
#include "plants.h"
#include <glm/glm.hpp>

namespace visualizer
{
	void DrawFadedObject::animate(const float &t, AnimData *d, IGame *game)
	{
       glm::vec4 vecColor = glm::mix(glm::vec4(m_start.r, m_start.g, m_start.b, m_start.a), glm::vec4(m_end.r, m_end.g, m_end.b, m_end.a), t);
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
        game->renderer->setColor(Color(vecColor.r, vecColor.g, vecColor.b, vecColor.a * scalar));
	}

	void DrawQuad::animate( const float& t, AnimData* d, IGame* game )
	{
		DrawFadedObject::animate(t, d, game);

                game->pushZoomMatrix();
		game->renderer->drawQuad( m_data->x, m_data->y, m_data->width * (1/game->zoomFactor()), m_data->height * (1/game->zoomFactor()) );
                game->popZoomMatrix();
        }
	
	void DrawWinningScreen::animate( const float& t, AnimData* d, IGame* game )
	{
		DrawFadedObject::animate(t, d, game);

                game->renderer->drawQuad( m_data->x, m_data->y, m_data->width, m_data->height );
                game->renderer->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
                game->renderer->drawText( m_data->x + (m_data->width)/2, m_data->y + (m_data->height)/2, "Roboto", m_data->winner, 200.0f, IRenderer::Center);
        }

	void DrawCircle::animate( const float& t, AnimData* d, IGame* game )
	{
		DrawFadedObject::animate(t, d, game);

                game->pushZoomMatrix();
		game->renderer->drawCircle( m_data->x, m_data->y, m_data->radius, 1, 100 );
                game->popZoomMatrix();
        }

	void DrawTexturedCircle::animate(const float &t, AnimData *d, IGame *game)
	{
		// TODO: move this logic to offset the circle out of here
		static float dt = 0.0f;
		dt += game->timeManager->getDt();

		DrawFadedObject::animate(t, d, game);

                game->pushZoomMatrix();
		float dx = 0.3 * cos(0.01*dt);
		float dy = 0.3 * sin(0.01*dt);
		game->renderer->drawTexturedCircle(m_data->x, m_data->y, m_data->radius, 1, 100, m_data->texture, 0.0f, dx, dy);

		dx = 0.1 * cos(0.012*dt);
		dy = 0.1 * sin(0.012*dt);
		game->renderer->drawTexturedCircle(m_data->x, m_data->y, m_data->radius, 1, 100, m_data->texture, 0.0f, 4*dx, 4*dy, -20*dy, -20*dx);
                game->popZoomMatrix();
            
        }

	void DrawSprite::animate( const float& t, AnimData* d, IGame* game )
	{
            DrawFadedObject::animate(t, d, game);
            
            game->pushZoomMatrix();
            float x, y, w, h;
            w = m_data->width * (1/game->zoomFactor());
            h = m_data->height * (1/game->zoomFactor());
            x = m_data->x + ((m_data->width/2) - (w/2));
            y = m_data->y + ((m_data->height/2) - (h/2));            
            game->renderer->drawTexturedQuad(x, y, w, h, 1.0f, m_data->texture, m_data->flip );
            game->popZoomMatrix();
	}

    void DrawAnimatedSprite::animate(const float &t, AnimData *d, IGame *game)
	{
		DrawFadedObject::animate(t, d, game);
                
                game->pushZoomMatrix();
                
                float x,y, w, h;
                w = m_data->width * (1/game->zoomFactor());
                h = m_data->height * (1/game->zoomFactor());
                x = m_data->x + ((m_data->width/2) - (w/2));
                y = m_data->y + ((m_data->height/2) - (h/2));
		int currentFrame = (m_data->endFrame - m_data->startFrame) * t + m_data->startFrame;
		game->renderer->drawAnimQuad(x, y,
                                     w, h,
                                     m_data->texture, m_data->flip, currentFrame);
	
                game->popZoomMatrix();
        }


    void DrawScreenText::animate(const float &t, AnimData *d, IGame *game)
    {
            if(game->options->getNumber("Toggle Plant Talk") > 0.0f)
            {

                DrawFadedObject::animate(t, d, game);

               /* float fontSize = 100.0f * (1/game->zoomFactor());
                string text = m_data->text;
                float textWidth = game->renderer->textWidth("Roboto", text, fontSize);
                textWidth *= (1/game->zoomFactor()); */
                game->pushZoomMatrix();
                float fontSize = 150.0f * (1/game->zoomFactor());
                string text = m_data->text;
                float textWidth = game->renderer->textWidth("Roboto", text, fontSize);
                textWidth *= (1/game->zoomFactor());

               /* float textDisplaceY = m_data->width*(1/game->zoomFactor());
                float x, y;
                x = m_data->x + (textWidth/2); //+ ((m_data->width/2));
                y = m_data->y; //- textDisplaceY; //+ ((m_data->height/2));
                */

                float x,y, w, h;
                w = m_data->width * (1/game->zoomFactor());
                h = m_data->height * (1/game->zoomFactor());
                x = m_data->x + ((m_data->width/2) - (w/2)) - ((textWidth/2) * 40); //(game->renderer->textWidth("Roboto", text, 100.0f)/2);
                y = m_data->y + ((m_data->height/2) - (h/2)) - ((1/game->zoomFactor()) * 40);



                game->renderer->drawText(x, y, "Roboto", text, fontSize);
                //game->renderer->drawTexturedQuad(x, y, w, h, 1.0f, m_data->texture, m_data->flip );
                game->popZoomMatrix();
            }
        }

}
