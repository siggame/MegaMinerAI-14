#ifndef PLANTS_ANIMATABLE_H
#define PLANTS_ANIMATABLE_H

//#include "plantsAnimatable.h"
#include "irenderer.h"
#include "parser/structures.h"

#include "math.h"

namespace visualizer
{
    struct DrawQuadData : public Animatable
    {
    	DrawQuadData(Color color, float x, float y, float width, float height) :
    		color(color), x(x), y(y), width(width), height(height) {}
    
    	Color color;
    	float x, y;
    	float width, height;
    };
    
    struct DrawSpriteData : public Animatable
    {
    	DrawSpriteData(Color color, float x, float y, float width, float height, string texture) :
    		color(color), x(x), y(y), width(width), height(height), texture(texture) {}
    
    	Color color;
    	float x, y;
    	float width, height;
    	string texture;
    };
    
    struct DrawCircleData : public Animatable
    {
    	DrawCircleData(Color color, float x, float y, float radius) :
    		color(color), x(x), y(y), radius(radius) {}
    
    	Color color;
    	float x, y;
    	float radius;
    	
    };

} // visualizer

#endif // PLANTS_ANIMATABLE_H
