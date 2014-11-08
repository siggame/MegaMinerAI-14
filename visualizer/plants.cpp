#include "plants.h"
#include "plantsAnimatable.h"
#include "frame.h"
#include "version.h"
#include "animations.h"
#include <utility>
#include <time.h>
#include <list>
#include <queue>
#include <glm/glm.hpp>
#include <sstream>


namespace visualizer
{
	//ENUMERATION FOR PLANT MUTATIONS
	enum
	{
	   Mother,
	   Spawner,
	   Choker,
	   Soaker,
	   Bumbleweed,
	   Aralia,
	   Titan,
	   Pool
	};

	// Returns true if the circle(center with radius r) intersects with the rectangle R.
	// Todo: move this function somewhere else?
	bool Intersects(const glm::vec2& center, float r, const Plants::Rect& R)
	{
		glm::vec2 closest = glm::vec2(glm::clamp(center.x, (float)R.left, (float)R.right),glm::clamp(center.y, (float)R.top, (float)R.bottom));
		glm::vec2 distance = center - closest;

		// If the distance is less than the circle's radius, an intersection occurs
		return (distance.x * distance.x + distance.y * distance.y) < (r * r);
	}

	const float Plants::GRID_OFFSET = 30.0f;
        const float Plants::PLANT_SIZE = 60.0f;

	Plants::Plants()
	{
                m_zoomFactor = 1;
		m_game = 0;
		m_suicide=false;
	} // Plants::Plants()

	Plants::~Plants()
	{
		destroy();
	}

	void Plants::destroy()
	{
		m_suicide=true;
		wait();
		animationEngine->registerGame(0, 0);

		clear();
		delete m_game;
		m_game = 0;

		// Clear your memory here

		programs.clear();

	} // Plants::~Plants()

	void Plants::preDraw()
	{
		ProcessInput();
                
		renderer->push();
		renderer->translate(GRID_OFFSET, GRID_OFFSET);

		static float d = 0.0f;
		d += timeManager->getDt() * 0.5f;

		renderer->setColor(Color(0.4,0.4,0.4,1));
		renderer->drawRotatedTexturedQuad(-getWidth(), -getHeight(), 3*getWidth(), 3*getHeight(), 1.0f, d, "background");
                
		renderer->setColor(Color(0.9f,0.9f,0.9f,1));
		renderer->drawTexturedQuad(0, 0, getWidth(), getHeight(), 2, "grid");

		//static float offset = 0;
		//offset += timeManager->getDt();
		renderer->setColor(Color(1,1,1,0.2f));
		//renderer->drawSubTexturedQuad(0, 0, getWidth(), getHeight(), offset, offset, getWidth(), getHeight(), "noise");
		renderer->drawTexturedQuad(0, 0, getWidth(), getHeight(), 1, "noise");

		DrawGUI();

		renderer->enableScissor(GRID_OFFSET, getHeight() + GRID_OFFSET, getWidth(), getHeight());
	}

	void Plants::postDraw()
	{
		DrawObjectSelection();

		renderer->disableScissor();
		renderer->pop();

	}


	PluginInfo Plants::getPluginInfo()
	{
		PluginInfo i;
		i.searchLength = 1000;
		i.gamelogRegexPattern = "Plants";
		i.returnFilename = false;
		i.spectateMode = false;
		i.pluginName = "MegaMinerAI: Plants Plugin";


		return i;
	} // PluginInfo Plants::getPluginInfo()

	void Plants::setup()
	{
		gui->checkForUpdate( "Plants", "./plugins/plants/checkList.md5", VERSION_FILE );
		options->loadOptionFile( "./plugins/plants/plants.xml", "plants" );
		resourceManager->loadResourceFile( "./plugins/plants/resources.r" );
	}

	std::list<int> Plants::getSelectedUnits()
	{
		return m_SelectedUnits;
	}

	void Plants::loadGamelog( std::string gamelog )
	{
		if(isRunning())
		{
			m_suicide = true;
			wait();
		}
		m_suicide = false;

		// BEGIN: Initial Setup
		setup();

		delete m_game;
		m_game = new parser::Game;

		if( !parser::parseGameFromString( *m_game, gamelog.c_str() ) )
		{
			delete m_game;
			m_game = 0;
			WARNING(
			"Cannot load gamelog, %s",
			gamelog.c_str()
			);
		}
		// END: Initial Setup

		int width = getWidth();
		int height = getHeight();

                // Setup the renderer as a 4 x 4 map by default
		// TODO: Change board size to something useful
		renderer->setCamera( 0, 0, width, height );
		renderer->setGridDimensions( width, height );
                
                m_zoomPoint.x = width*.5;
                m_zoomPoint.y = height*.5;

		renderer->setCamera( 0, 0, width + GRID_OFFSET, height + 200);
		renderer->setGridDimensions( width + GRID_OFFSET, height + 200);

		start();
	} // Plants::loadGamelog()

    string Plants::getPlantFromID(int id, int owner, int actionState) const
	{
		if(id == 7)
			return "rad_pool";

        std::stringstream stream;
        switch(actionState)
        {
            case parser::ATTACK:
                switch(id)
                {
                   // case 0: stream << "mother"; break;
                   // case 1: stream << "spawner"; break;
                    case 2: stream << "choke_anim"; break;
                   // case 3: stream << "soaker"; break;
                   // case 4: stream << "bumbleweed"; break;
                    case 5: stream << "aralia_anim"; break;
                    case 6: stream << "titan_anim"; break;
                    default: stream << "bumbleweed";

                }
                break;

            case parser::HEAL:
                switch(id)
                {
                    case 4: stream << "bumbleweed"; break;
                }
                break;
            case parser::PLANTTALK:
                switch(id)
                {/*
                    case 0: stream << "mother"; break;
                    case 1: stream << "spawner"; break;
					case 2: stream << "choke"; break;
                    case 3: stream << "soaker"; break;
                    case 4: stream << "bumbleweed"; break;
                    case 5: stream << "aralia"; break;
                    case 6: stream "titan"; break;
                    default: stream << "spawner";
                  */
                }
                break;
            case parser::SOAK:
                switch(id)
                {/*
                    case 0: stream << "mother"; break;
                    case 1: stream << "spawner"; break;
                    case 2: stream << "choke"; break;
                    case 3: stream << "soaker"; break;
                    case 4: stream << "bumbleweed"; break;
                    case 5: stream << "aralia"; break;
                    case 6: stream << "titan"; break;
                    default: stream << "spawner";
                    */
                }
                break;
            case parser::UPROOT:
                switch(id)
                {/*
                    case 0: stream << "mother"; break;
                    case 1: stream << "spawner"; break;
                    case 2: stream << "choke"; break;
                    case 3: stream << "soaker"; break;
                    case 4: stream << "bumbleweed"; break;
                    case 5: stream << "aralia"; break;
                    case 6: stream << "titan"; break;
                    default: stream << "spawner";
                    */
                }
                break;
            default:
                switch(id)
                {
                    case 0: stream << "mother"; break;
                    case 1: stream << "spawner"; break;
                    case 2: stream << "choke"; break;
                    case 3: stream << "soaker"; break;
                    case 4: stream << "bumbleweed"; break;
                    case 5: stream << "aralia"; break;
                    case 6: stream << "titan_anim"; break;
                    default: stream << "spawner";

                }
                break;
        };

		stream << ((owner == 0) ? 1 : 2);
		return stream.str();
	}

	void Plants::ProcessInput()
	{
		const Input& input = gui->getInput();
		int turn = timeManager->getTurn();
		int unitSelectable = gui->getDebugOptionState("Units Selectable");

		if(input.leftRelease && turn < (int) m_game->states.size())
		{
			Rect R;
			GetSelectedRect(R);

			m_SelectedUnits.clear();

			if(unitSelectable)
			{
				for(auto& iter : m_game->states[turn].plants)
				{
					const auto& unit = iter.second;

					if(Intersects(glm::vec2(unit.x, unit.y), unit.range, R))
					{
						m_SelectedUnits.push_back(unit.id);
					}
				}
			}

			gui->updateDebugWindow();
			gui->updateDebugUnitFocus();
		}
	}

	void Plants::pruneSelection()
	  {
		  int turn = timeManager->getTurn();
		  bool changed = false;
		  int focus = gui->getCurrentUnitFocus();

		  if(turn < (int) m_game->states.size())
		  {
			  auto iter = m_SelectedUnits.begin();

			  while(iter != m_SelectedUnits.end())
			  {
				  if(m_game->states[turn].plants.find(*iter) == m_game->states[turn].plants.end())
				  {
					  iter = m_SelectedUnits.erase(iter);
					  changed = true;
				  }
				  else
					  iter++;

				  if(changed == true)
					gui->updateDebugWindow();

				  if(std::find(m_SelectedUnits.begin(), m_SelectedUnits.end(), focus) == m_SelectedUnits.end())
					gui->updateDebugUnitFocus();
			  }
		  }
	  }

	void Plants::GetSelectedRect(Rect &out) const
	{
		const Input& input = gui->getInput();
                
                int viewwidth = (1/m_zoomFactor) * getWidth();
                int viewheight = (1/m_zoomFactor) * getHeight();
            
                int viewx = (m_zoomPoint.x/getWidth()) * viewwidth;
                int viewy = (m_zoomPoint.y/getHeight()) * viewheight;
                
                int width = ((input.sx - input.x)/getWidth()) * viewwidth;
                int height = ((input.sy - input.y)/getHeight()) * viewheight;                
                
                int x = (m_zoomPoint.x - (viewwidth/2)) + ((input.x/getWidth())  * viewwidth);
                int y = (m_zoomPoint.y - (viewheight/2)) + ((input.y/getHeight()) * viewheight);
                
		int right = x + width;
		int bottom = y + height;
              
                std::cout << "x:" << input.x << " y:" << input.y << " sx:" << input.sx << " sy:" << input.sy << std::endl;
                std::cout << "x:" << viewx << " y:" << viewy << " w:" << viewwidth << " h:" << viewheight << std::endl;
                std::cout << "x:" << x << " y:" << y << " w:" << width << " h:" << height << std::endl; 
		out.left = min(x,right);
		out.top = min(y,bottom);
		out.right = max(x,right);
		out.bottom = max(y,bottom);
	}

    void Plants::DrawObjectSelection() const
    {
        int turn = timeManager->getTurn();
        if(turn < (int) m_game->states.size())
        {
            for(auto & iter : m_SelectedUnits)
            {
                if(m_game->states[turn].plants.find(iter) != m_game->states[turn].plants.end())
                {
                    auto & plant = m_game->states[turn].plants.at(iter);
                    DrawQuadAroundObj(parser::Mappable({plant.id, plant.x, plant.y}), glm::vec4(1.0f, 0.4, 0.4, 0.6));
                }
            }

            int focus = gui->getCurrentUnitFocus();
            if(focus >= 0)
            {
                if(m_game->states[turn].plants.find(focus) != m_game->states[turn].plants.end())
                {
                    auto& plant = m_game->states[turn].plants.at(focus);
                    DrawBoxAroundObj(parser::Mappable({plant.id, plant.x, plant.y}), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
                }
            }
        }
    }

    void Plants::DrawBoxAroundObj(const parser::Mappable& obj, const glm::vec4 &color) const
    {
        float w = PLANT_SIZE * (1/m_zoomFactor);
        float h = PLANT_SIZE * (1/m_zoomFactor);
        pushZoomMatrix();
        renderer->setColor(Color(color.r, color.g, color.b, color.a));
        renderer->drawLine(obj.x - (w/2), obj.y - (h/2), obj.x - (w/2), obj.y + (h/2));
        renderer->drawLine(obj.x - (w/2), obj.y + (h/2), obj.x + (w/2), obj.y + (h/2));
        renderer->drawLine(obj.x + (w/2), obj.y + (h/2), obj.x + (w/2), obj.y - (h/2));
        renderer->drawLine(obj.x + (w/2), obj.y - (h/2), obj.x - (w/2), obj.y - (h/2));
        popZoomMatrix();
    }


    void Plants::DrawQuadAroundObj(const parser::Mappable& obj, const glm::vec4 &color) const
    {
        float w = PLANT_SIZE * (1/m_zoomFactor);
        float h = PLANT_SIZE * (1/m_zoomFactor);
        pushZoomMatrix();
        renderer->setColor( Color( color.r, color.g, color.b, color.a) );
        renderer->drawQuad(obj.x- (w/2), obj.y - (h/2),w,h);
        popZoomMatrix();
    }

    void Plants::pushZoomMatrix() const 
    {
            int width = (1/m_zoomFactor) * getWidth();
            int height = (1/m_zoomFactor) * getHeight();
            
            int x = (m_zoomPoint.x/getWidth()) * width;
            int y = (m_zoomPoint.y/getHeight()) * height;
            
            renderer->push();
            renderer->scale(m_zoomFactor, m_zoomFactor);
            renderer->translate( -(m_zoomPoint.x - (width/2)), -(m_zoomPoint.y - (height/2)));
    }
      
    void Plants::popZoomMatrix() const 
    {
            renderer->pop();
    }
    
    void Plants::wheelEvent(int delta)
    {
            m_zoomFactor += ((m_zoomFactor* 0.02) * (delta * 0.02));
    }
    
    void Plants::keyPressEvent(std::string& s)
    {
        if(s == "W")
            m_zoomPoint.y -= 8;
        else if( s == "A")
            m_zoomPoint.x -= 8;
        else if(s == "S")
            m_zoomPoint.y += 8;
        else if(s == "D")
            m_zoomPoint.x += 8;
            
    }
    
	void Plants::DrawGUI() const
	{
		const float x = getWidth() / 2;
		const float y = getHeight() + 2;
		const float boxOffset = 980;
		int currentTurn = timeManager->getTurn();

		renderer->setColor(Color(1, 1, 1, 1));
		renderer->drawTexturedQuad(0, getHeight(), 500, 400, 1, "guibg");
		renderer->drawTexturedQuad(1550, getHeight(), 500, 400, 1, "guibg");

		// Draw Names
		for (int owner : {0,1})
		{
			int namePos = (owner == 0) ? (x - boxOffset) : (x + boxOffset);
			IRenderer::Alignment alignment = (owner == 0) ? IRenderer::Left : IRenderer::Right;
			renderer->setColor(getPlayerColor(owner));

			// Todo: add player time
			std::stringstream stream;
			stream << m_game->states[0].players[owner].playerName;
			renderer->drawText(namePos, y, "Roboto", stream.str(), 200.0f, alignment);
		}

		// Draw Pie chart of spores!
		for (int i : {0,1})
		{
			std::stringstream stream;
			float sporeCount = m_game->states[currentTurn].players[i].spores;
			float xPos = 400 + i * getWidth() * 0.60f;
			float yPos = getHeight() + 50;

			stream << sporeCount;

			renderer->setColor(Color(0.4f, 0.6f, 0.4f, 1.0f));
			renderer->drawCircle(xPos, yPos, 50, 1, 10);
                        
			renderer->setColor(Color(0.3f, 0.9f, 0.3f, 1.0f));
			renderer->drawCircle(xPos, yPos, 50, static_cast<float>(sporeCount) / m_game->states[currentTurn].maxSpores, 10, 90);

			renderer->setColor(Color(0, 0, 0, 1));
			renderer->drawText(xPos, yPos, "Roboto", stream.str(), 150.0f, IRenderer::Center);
		}


                const parser::Plant& plant = m_game->states[currentTurn].plants.at(m_motherPlantID[0]);
                float health = (plant.maxRads - plant.rads) / (float)plant.maxRads;

                renderer->setColor(Color(1.0f, 0.0f, 0.5f, 1.0f));
                renderer->drawTexturedQuad(50, getHeight() + 100, 500.0f, 150.0f, 1.0f, "vine", 0);

                renderer->setColor(Color(0.0f, 1.0f, 1.0f, 1.0f));
                renderer->drawTexturedQuad(50, getHeight() + 100, health * 500.0f, 150.0f, 1.0f, "vine", 0);

                const parser::Plant& plant2 = m_game->states[currentTurn].plants.at(m_motherPlantID[1]);
                health = (plant2.maxRads - plant2.rads) / (float)plant.maxRads;

                renderer->setColor(Color(1.0f, 0.0f, 0.5f, 1.0f));
                renderer->drawTexturedQuad(50 + (getWidth() * 0.7f), getHeight() + 100, 500.0f, 150.0f, 1.0f, "vine", 1);

                renderer->setColor(Color(0.0f, 1.0f, 1.0f, 1.0f));
                renderer->drawTexturedQuad(50 + (getWidth() * 0.7f) + ((1 - health) * 500.0f), getHeight() + 100, health * 500.0f, 150.0f, 1.0f, "vine", 1);

                
                
                
	}

	void Plants::LoadMotherPlants()
	{
		unsigned int counter = 0;
		for(auto& iter : m_game->states[0].plants)
		{
			const parser::Plant& plant = iter.second;
			if(plant.mutation == Mother)
			{
				m_motherPlantID[plant.owner] = plant.id;
				++counter;

				if(counter >= 2)
				{
					break;
				}
			}
		}
	}

	std::list<IGUI::DebugOption> Plants::getDebugOptions()
	{
		return std::list<IGUI::DebugOption>({{"Units Selectable", true},
											 {"Tiles Selectable", true}});
	}

	// The "main" function
	void Plants::run()
	{
		timeManager->setNumTurns( 0 );

		animationEngine->registerGame(0, 0);

		std::set<int> spawnedPlants;
		std::queue<SmartPointer<Animatable>> animationQueue;

		Frame * turn = new Frame;
		Frame * nextTurn = new Frame;

		LoadMotherPlants();

		// Look through each turn in the gamelog
		for(int state = 0; state < (int)m_game->states.size() && !m_suicide; state++)
		{
			// TODO: clean this up
			for(auto iter : m_game->states[state].plants)
            {
				const parser::Plant& plant = iter.second;

                float health = plant.maxRads - plant.rads;
                string plantTexture = getPlantFromID(plant.mutation, plant.owner);
				bool direction = plant.owner;
				bool bSpawned = spawnedPlants.insert(plant.id).second;
				bool bDied = false;
				if(state < m_game->states.size() - 1)
				{
					auto& nextState = m_game->states[state+1];
					auto next = nextState.plants.find(plant.id);

					if(next == nextState.plants.end())
					{
						bDied = true;
					}
				}
				// Coloring plants and radii
                Color plantColor = Color(1, (health/plant.maxRads), (health/plant.maxRads), 1);
                Color radiusColor = getPlayerColor(plant.owner);
                radiusColor.a = .4;

				// Render circle around plants
				if (plant.mutation != 7)
				{
					SmartPointer<DrawCircleData> circleData = new DrawCircleData(plant.x, plant.y, plant.range);
					circleData->addKeyFrame( new DrawCircle( circleData, radiusColor, bSpawned ? FadeIn : None ) );
					turn->addAnimatable( circleData );
				}

                // Only scale the mother plant and the rad pools
                float plantSize = PLANT_SIZE;
				if(plant.mutation == 0 || plant.mutation == 7)
				{
					plantSize = plant.range;
				}

				float x = plant.x - plantSize / 2.0;
				float y = plant.y - plantSize / 2.0;

				SmartPointer<Animatable> anim;
				if (plant.mutation != 7)
				{
                    int endframe;
                    switch(plant.mutation)
                    {
                        case Mother:
                            endframe = 23;
                            break;
                        case Spawner:
                            endframe = 23;
                            break;
                        case Choker:
                            endframe = 5;
                            break;
                        case Soaker:
                            endframe = 23;
                            break;
                        case Bumbleweed:
                            endframe = 23;
                            break;
                        case Aralia:
                            endframe = 7;
                            break;
                        case Titan:
                            endframe = 15;
                            break;

                    }
                    
                    //Show seed sprite when first spawned

                    SmartPointer<DrawSpriteData> spriteData = new DrawSpriteData(x, y, plantSize, plantSize, bSpawned ? "seed" : plantTexture, direction);
					spriteData->addKeyFrame( new DrawSprite( spriteData, plantColor, bSpawned ? FadeIn : bDied ? FadeOut : None ) );
                    anim = spriteData;
                    if(!bSpawned)
                    {
                        if(plant.mutation == Bumbleweed)
                        {
                            SmartPointer<DrawAnimatedSpriteData> idle = new DrawAnimatedSpriteData(0, 7, x, y, plantSize, plantSize,
                                                                                                   plantTexture, direction);
                            idle->addKeyFrame( new DrawAnimatedSprite( idle, plantColor, bSpawned ? FadeIn : None ) );
                            anim = idle;
                        }
                        else if(plant.mutation == Titan)
                        {
                            SmartPointer<DrawAnimatedSpriteData> idle = new DrawAnimatedSpriteData(0, endframe, x, y, plantSize * 1.20f, plantSize * 1.20f,
                                                                                                   plantTexture, direction);
                            idle->addKeyFrame( new DrawAnimatedSprite( idle, plantColor, bSpawned ? FadeIn : None ) );
                            anim = idle;
                        }
                    }

                    //SmartPointer<DrawSpriteData> spriteData = new DrawSpriteData(x, y, plantSize, plantSize, bSpawned ? "seed" : plantTexture, direction);
                    //spriteData->addKeyFrame( new DrawSprite( spriteData, plantColor, bSpawned ? FadeIn : None ) );
                    //anim = spriteData;


                    // Render animations for this plant
                    for(const SmartPointer< parser::Animation >& animation : m_game->states[state].animations[plant.id])
                    {
                        plantTexture = getPlantFromID(plant.mutation, plant.owner, animation->type);
                        switch(animation->type)
                        {

                            case parser::ATTACK:
                            {
                                const parser::attack& atkAnim = static_cast<const parser::attack&>(*animation);

                                if(m_game->states[state].plants[atkAnim.targetID].x < plant.x)
                                    direction = true;
                                else
                                    direction = false;
                                SmartPointer<DrawAnimatedSpriteData> atk = new DrawAnimatedSpriteData(0, endframe, x, y, plantSize, plantSize, plantTexture, direction);
                                atk->addKeyFrame( new DrawAnimatedSprite( atk, plantColor, bSpawned ? FadeIn : None ) );
                                anim = atk;

                                //cout << "Attack actingID, targetID: " << atkAnim.actingID << ", " << atkAnim.targetID << endl;
                                break;
                            }

                            case parser::HEAL:
                            {
                                const parser::heal& healAnim = static_cast<const parser::heal&>(*animation);

                                if(m_game->states[state].plants[healAnim.targetID].x < plant.x)
                                    direction = true;
                                else
                                    direction = false;
                                SmartPointer<DrawAnimatedSpriteData> heal = new DrawAnimatedSpriteData(0, endframe, x, y, plantSize, plantSize, plantTexture, direction);
                                heal->addKeyFrame( new DrawAnimatedSprite( heal, plantColor, bSpawned ? FadeIn : None ) );
                                anim = heal;

                                break;
                            }
                            case parser::PLANTTALK:
							{
								const parser::plantTalk& talkAnim = static_cast<const parser::plantTalk&>(*animation);
								cout <<"Talk: " << talkAnim.message << endl;
                                break;
							}
                            case parser::SOAK:
							{
								const parser::soak& soakAnim = static_cast<const parser::soak&>(*animation);
                                break;
							}
                            case parser::UPROOT:
							{
								const parser::uproot& upRootAnim = static_cast<const parser::uproot&>(*animation);
                                break;
							}
                            default:
                                assert(false && "Unknown animation");
                                break;

                        }
                    }

				}
				else
				{
					SmartPointer<DrawTexturedCircleData> spriteData = new DrawTexturedCircleData(plant.x, plant.y, plantSize, plantTexture);
					spriteData->addKeyFrame( new DrawTexturedCircle( spriteData, Color(1, 1, 1, 0.7), bSpawned ? FadeIn : None ) );

					anim = spriteData;
				}

				animationQueue.push(anim);

				// check for deaths
				if(bDied)
				{

					SmartPointer<DrawAnimatedSpriteData> deathAnim =
							new DrawAnimatedSpriteData(0, 3,
													   x, y,
													   plantSize, plantSize,
													   "death", false);

					deathAnim->addKeyFrame(new DrawAnimatedSprite(deathAnim, Color(1.0f, 1.0f, 1.0f, 1.0f)));
					animationQueue.push(deathAnim);
				}

				(*turn)[plant.id]["id"] = plant.id;
				(*turn)[plant.id]["owner"] = plant.owner;
				(*turn)[plant.id]["X"] = plant.x;
				(*turn)[plant.id]["Y"] = plant.y;
				(*turn)[plant.id]["mutation"] = plant.mutation;
				(*turn)[plant.id]["radiatesLeft"] = plant.radiatesLeft;
				(*turn)[plant.id]["rads"] = plant.rads;
				(*turn)[plant.id]["strength"] = plant.strength;
				(*turn)[plant.id]["uprootsLeft"] = plant.uprootsLeft;
				(*turn)[plant.id]["range"] = plant.range;
				(*turn)[plant.id]["baseStrength"] = plant.baseStrength;
				(*turn)[plant.id]["maxRadiates"] = plant.maxRadiates;
				(*turn)[plant.id]["maxRads"] = plant.maxRads;
				(*turn)[plant.id]["maxStrength"] = plant.maxStrength;
				(*turn)[plant.id]["maxUproots"] = plant.maxUproots;
				(*turn)[plant.id]["minStrength"] = plant.minStrength;
			}

            /*
            for( auto& p : m_game->states[ state ].plants )
            {
                // Player talk
                for( auto& t : m_game->states[state].animations[ p.first ] )
                {
                parser::PLANTTALK &plantTalk = (parser::PLANTTALK&)*t;
                stringstream talkstring;
                talkstring << "(" << state << ") " << plantTalk.message;
                //playerTalks[ player.first ] = talkstring.str();
                turn[-1]["Talk"] = talkstring.str().c_str();
                }
            }
            */

			while(!animationQueue.empty())
			{
				turn->addAnimatable( animationQueue.front() );
				animationQueue.pop();
			}
			
			if(state == (int)m_game->states.size() - 1)
			{
				SmartPointer<DrawWinningData> winningData = new DrawWinningData(0, 0, getWidth(), getHeight(), m_game->winReason);
				winningData->addKeyFrame( new DrawWinningScreen( winningData, Color(0.1,0.6,0.8,0.2), None ) );
				turn->addAnimatable( winningData );
			}

			animationEngine->buildAnimations(*turn);
			addFrame(*turn);

			// Register the game and begin playing delayed due to multithreading
			if(state > 5)
			{
				timeManager->setNumTurns(state - 5);
				animationEngine->registerGame( this, this );
				if(state == 6)
				{
					animationEngine->registerGame(this, this);
					timeManager->setTurn(0);
					timeManager->play();
				}
			}
			delete turn;
			turn = nextTurn;
			nextTurn = new Frame;
		}

		if(!m_suicide)
		{
			timeManager->setNumTurns( m_game->states.size() );
			timeManager->play();
		}

		delete turn;
		delete nextTurn;

	} // Plants::run()

} // visualizer

Q_EXPORT_PLUGIN2( Plants, visualizer::Plants );
