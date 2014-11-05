#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "plantsAnimatable.h"

namespace visualizer
{

	class DrawFadedObject : public Anim
	{
	public:
		DrawFadedObject(const Color& color, FadeFlag fade) : m_color(color), m_fade(fade) {}

		void animate(const float &t, AnimData *d, IGame *game);
	private:
		Color m_color;
		FadeFlag m_fade;
	};

#define DRAW_OBJECT(nameClass, dataClass) \
	class nameClass: public DrawFadedObject \
    { \
        public: \
			nameClass( dataClass* data, const Color& color, FadeFlag fade = None ) : DrawFadedObject(color, fade) { m_data = data; } \
            void animate( const float& t, AnimData* d, IGame* game ); \
        private: \
            dataClass *m_data; \
    };
  
    DRAW_OBJECT(DrawQuad, DrawQuadData)
    DRAW_OBJECT(DrawWinningScreen, DrawWinningData)
    DRAW_OBJECT(DrawCircle, DrawCircleData)
    DRAW_OBJECT(DrawSprite, DrawSpriteData)
	DRAW_OBJECT(DrawTexturedCircle, DrawTexturedCircleData)
}

#endif // ANIMATION_H
