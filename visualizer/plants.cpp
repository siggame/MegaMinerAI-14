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
	// Returns true if the circle(center with radius r) intersects with the rectangle R.
	// Todo: move this function somewhere else?
	bool Intersects(const glm::vec2& center, float r, const Plants::Rect& R)
	{
		glm::vec2 closest = glm::vec2(glm::clamp(center.x, (float)R.left, (float)R.right),glm::clamp(center.y, (float)R.top, (float)R.bottom));
		glm::vec2 distance = center - closest;

		// If the distance is less than the circle's radius, an intersection occurs
		return (distance.x * distance.x + distance.y * distance.y) < (r * r);
	}

	const float Plants::GRID_OFFSET = 20.0f;
    const float Plants::PLANT_SIZE = 60.0f;
	Plants::Plants()
	{
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
                const float x = getWidth() / 2;
                const float y = getHeight() + 2;
                const float boxOffset = 980;
                const float boxWidth = 0;

		const Input& input = gui->getInput();

		ProcessInput();
                
		renderer->push();
		renderer->translate(GRID_OFFSET, GRID_OFFSET);
                
		renderer->setColor(Color(0.9f,0.9f,0.9f,1));
		renderer->drawTexturedQuad(0, 0, getWidth(), getHeight(), 2, "grid");

		//static float offset = 0;
		//offset += timeManager->getDt();
		renderer->setColor(Color(1,1,1,0.2f));
		//renderer->drawSubTexturedQuad(0, 0, getWidth(), getHeight(), offset, offset, getWidth(), getHeight(), "noise");
		renderer->drawTexturedQuad(0, 0, getWidth(), getHeight(), 1, "noise");

                // Draw Names
                for (int owner : {0,1})
                {
                    int namePos = (owner == 0) ? (x - boxOffset) : (x + boxOffset);
                    IRenderer::Alignment alignment = (owner == 0) ? IRenderer::Left : IRenderer::Right;
                    renderer->setColor(getPlayerColor(owner));

                    std::stringstream stream;
                                stream << m_game->states[0].players[owner].playerName << " Spores: " << m_game->states[timeManager->getTurn()].players[owner].spores;
                    renderer->drawText(namePos, y, "Roboto", stream.str(), 200.0f, alignment);
                }

		renderer->enableScissor(GRID_OFFSET, getHeight() + GRID_OFFSET, getWidth(), getHeight());
	}

	void Plants::postDraw()
	{
		renderer->disableScissor();
		renderer->pop();
        
        DrawObjectSelection();

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

		cout << "Width: " << width << " Height: " << height << endl;
		// Setup the renderer as a 4 x 4 map by default
		// TODO: Change board size to something useful
		renderer->setCamera( 0, 0, width, height );
		renderer->setGridDimensions( width, height );

                m_zoomRect.left = 0;
                m_zoomRect.top = 0;
                m_zoomRect.right = width;
                m_zoomRect.bottom = height;
                
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
                cout << "Heal" << endl;
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
                cout << "Talk" << endl;
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
                cout << "Soak" << endl;
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
                cout << "UpRoot" << endl;
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

			// todo: this causes the game to hang
			//renderer->setCamera( R.left, R.top, R.right, R.bottom );

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

		int x = input.x - GRID_OFFSET;
		int y = input.y - GRID_OFFSET;
		int width = input.sx - x - GRID_OFFSET;
		int height = input.sy - y - GRID_OFFSET;

		int right = x + width;
		int bottom = y + height;

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
        float posFix = 1.3;
        
        //push the zoom matrix here
        renderer->setColor(Color(color.r, color.g, color.b, color.a));
        renderer->drawLine(obj.x, obj.y, obj.x + 50+posFix, obj.y);
        renderer->drawLine(obj.x, obj.y, obj.x, obj.y + 50+posFix);
        renderer->drawLine(obj.x + 50+posFix, obj.y, obj.x + 50+posFix, obj.y + 50+posFix);
        renderer->drawLine(obj.x, obj.y + 50+posFix, obj.x + 50+posFix, obj.y + 50+posFix);
    
        // pop the zoom matrix here
    }


    void Plants::DrawQuadAroundObj(const parser::Mappable& obj, const glm::vec4 &color) const
    {
        float posFix = 60;
        
        // push the zoom matrix here
        renderer->setColor( Color( color.r, color.g, color.b, color.a) );
        renderer->drawQuad(obj.x + .5*posFix, obj.y + .5*posFix, 1,1);
        // pop the zoom matrix here
        
    }

	std::list<IGUI::DebugOption> Plants::getDebugOptions()
	{
		return std::list<IGUI::DebugOption>({{"Units Selectable", true},
											 {"Tiles Selectable", false}});
	}
	
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


	// The "main" function
	void Plants::run()
	{
		timeManager->setNumTurns( 0 );

		animationEngine->registerGame(0, 0);

		std::set<int> spawnedPlants;
		std::queue<SmartPointer<Animatable>> animationQueue;

		// Look through each turn in the gamelog
		for(int state = 0; state < (int)m_game->states.size() && !m_suicide; state++)
		{
			Frame turn;  // The frame that will be drawn

			for(auto iter : m_game->states[state].players)
			{
				const parser::Player& player = iter.second;


				// Render animations for this player
				for(const SmartPointer< parser::Animation >& animation : m_game->states[state].animations[player.id])
				{
					switch(animation->type)
					{
						case parser::GERMINATE:
							cout << "Germinate" << endl;
							break;
						default:
							assert(false && "Unknown animation");
					}
				}
			}
			
			// TODO: clean this up
			for(auto iter : m_game->states[state].plants)
            {
				const parser::Plant& plant = iter.second;
				bool bSpawned = spawnedPlants.insert(plant.id).second;
                bool direction = plant.owner;
                float health = plant.maxRads - plant.rads;
                string plantTexture = getPlantFromID(plant.mutation, plant.owner);

				// Coloring plants
                Color plantColor = Color(1, (health/plant.maxRads), (health/plant.maxRads), 1);

				// Render circle around plants
				if (plant.mutation != 7)
				{

                    //Plant Radius Color
                    Color radiusColor = getPlayerColor(plant.owner);
                    radiusColor.a = .4;

					SmartPointer<DrawCircleData> circleData = new DrawCircleData(plant.x, plant.y, plant.range);
					circleData->addKeyFrame( new DrawCircle( circleData, radiusColor, bSpawned ? FadeIn : None ) );
					turn.addAnimatable( circleData );
				}

                // Only scale the mother plant and the rad pools
                float plantSize = PLANT_SIZE;
				if(plant.mutation == 0 || plant.mutation == 7)
				{
					plantSize = plant.range;
				}

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

                    float x = plant.x - plantSize / 2.0;
					float y = plant.y - plantSize / 2.0;

                    SmartPointer<DrawSpriteData> spriteData = new DrawSpriteData(x, y, plantSize, plantSize, bSpawned ? "seed" : plantTexture, direction);
                    spriteData->addKeyFrame( new DrawSprite( spriteData, plantColor, bSpawned ? FadeIn : None ) );
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

                                cout << "Heal" << endl;
                                break;
                            }
                            case parser::PLANTTALK:
                                cout << "Talk" << endl;
                                break;
                            case parser::SOAK:
                                cout << "Soak" << endl;
                                break;
                            case parser::UPROOT:
                                cout << "UpRoot" << endl;
                                break;
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

				turn[plant.id]["id"] = plant.id;
				turn[plant.id]["X"] = plant.x;
				turn[plant.id]["Y"] = plant.y;
				turn[plant.id]["mutation"] = plant.mutation;
				turn[plant.id]["radiatesLeft"] = plant.radiatesLeft;
				turn[plant.id]["rads"] = plant.rads;
				turn[plant.id]["strength"] = plant.strength;
				turn[plant.id]["uprootsLeft"] = plant.uprootsLeft;
				turn[plant.id]["range"] = plant.range;
				turn[plant.id]["baseStrength"] = plant.baseStrength;
				turn[plant.id]["maxRadiates"] = plant.maxRadiates;
				turn[plant.id]["maxRads"] = plant.maxRads;
				turn[plant.id]["maxStrength"] = plant.maxStrength;
				turn[plant.id]["maxUproots"] = plant.maxUproots;
				turn[plant.id]["minStrength"] = plant.minStrength;

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
				turn.addAnimatable( animationQueue.front() );
				animationQueue.pop();
			}
			
			if(state == (int)m_game->states.size() - 1)
			{
				SmartPointer<DrawWinningData> winningData = new DrawWinningData(0, 0, getWidth(), getHeight(), m_game->winReason);
				winningData->addKeyFrame( new DrawWinningScreen( winningData, Color(0.1,0.6,0.8,0.2), None ) );
				turn.addAnimatable( winningData );
			}

			animationEngine->buildAnimations(turn);
			addFrame(turn);

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
		}

		if(!m_suicide)
		{
			timeManager->setNumTurns( m_game->states.size() );
			timeManager->play();
		}

	} // Plants::run()

} // visualizer

Q_EXPORT_PLUGIN2( Plants, visualizer::Plants );
