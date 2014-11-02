#ifndef PLANTS_ANIMATABLE_H
#define PLANTS_ANIMATABLE_H

//#include "plantsAnimatable.h"
#include "irenderer.h"
#include "parser/structures.h"

#include "math.h"
#include <glm/glm.hpp>

namespace visualizer
{
	enum FadeFlag
	{
		FadeIn,
		FadeOut,
		None
	};

    struct DrawQuadData : public Animatable
    {
		DrawQuadData(float x, float y, float width, float height) :
			x(x), y(y), width(width), height(height) {}
    
    	float x, y;
    	float width, height;
    };
    
    struct DrawSpriteData : public Animatable
    {
		DrawSpriteData(float x, float y, float width, float height, string texture) :
			x(x), y(y), width(width), height(height), texture(texture) {}
    
    	float x, y;
    	float width, height;
    	string texture;
    };
    
    struct DrawCircleData : public Animatable
    {
		DrawCircleData(float x, float y, float radius) :
			x(x), y(y), radius(radius) {}
    
    	float x, y;
    	float radius;
    	
    };

} // visualizer

#endif // PLANTS_ANIMATABLE_H
