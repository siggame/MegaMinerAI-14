#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "plantsAnimatable.h"

namespace visualizer
{

    struct StartAnim: public Anim
    {
      public:
        void animate( const float& t, AnimData *d, IGame* game );

    };

#define DRAW_OBJECT(nameClass, dataClass) \
	class nameClass: public Anim \
    { \
        public: \
            nameClass( dataClass* data ) { m_data = data; } \
            void animate( const float& t, AnimData* d, IGame* game ); \
            float controlDuration() const \
            { return 0; } \
            float totalDuration() const \
            { return 0; } \
        private: \
            dataClass *m_data; \
    };
  
    DRAW_OBJECT(DrawQuad, DrawQuadData)
    DRAW_OBJECT(DrawCircle, DrawCircleData)
    DRAW_OBJECT(DrawSprite, DrawSpriteData)
}

#endif // ANIMATION_H
