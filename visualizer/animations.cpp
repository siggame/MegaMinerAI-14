#include "animations.h"
#include "plants.h"

namespace visualizer
{
  void StartAnim::animate( const float& /* t */, AnimData * /* d */, IGame* /*game*/ )
  {
  }

  void DrawQuad::animate( const float& /*t*/, AnimData * /*d*/, IGame* game )
  {
    // Set the color to red
    game->renderer->setColor( m_data->color);
    // Draw a 2x2 rectangle at (1,1), with the top left corner of the screen being the origin 
    game->renderer->drawQuad( m_data->x, m_data->y, m_data->width, m_data->height );
  }
  
  void DrawCircle::animate( const float& /*t*/, AnimData * /*d*/, IGame* game )
  {
    // Set the color to red
    game->renderer->setColor( m_data->color);
    // Draw a 2x2 rectangle at (1,1), with the top left corner of the screen being the origin 
    game->renderer->drawCircle( m_data->x, m_data->y, m_data->radius, 1, 100 );
  }
  
  void DrawSprite::animate( const float& /*t*/, AnimData * /*d*/, IGame* game )
  {
    // Set the color to red
    game->renderer->setColor( m_data->color);
    // Draw a 2x2 rectangle at (1,1), with the top left corner of the screen being the origin 
    game->renderer->drawTexturedQuad( m_data->x, m_data->y, m_data->width, m_data->height, 1, m_data->texture );
  }

}
