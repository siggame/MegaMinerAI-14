#include "plants.h"
#include "plantsAnimatable.h"
#include "frame.h"
#include "version.h"
#include "animations.h"
#include <utility>
#include <time.h>
#include <list>
#include <glm/glm.hpp>

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
		const Input& input = gui->getInput();

		ProcessInput();

		renderer->push();
		renderer->translate(GRID_OFFSET, GRID_OFFSET);

		// Handle player input here
		renderer->setColor(Color(0.5,0.5,0.5,1));
		renderer->drawQuad(0,0, getWidth(), getHeight());
	}

	void Plants::postDraw()
	{
		if( renderer->fboSupport() )
		{
			#if 0
			renderer->useShader( programs["post"] );
			renderer->swapFBO();
			renderer->useShader( 0 );
			#endif

		}

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

		cout << "Width: " << width << " Height: " << height << endl;
		// Setup the renderer as a 4 x 4 map by default
		// TODO: Change board size to something useful
		renderer->setCamera( 0, 0, width, height );
		renderer->setGridDimensions( width, height );

		start();
	} // Plants::loadGamelog()

	string Plants::getPlantFromID(int id) const
	{
		// TODO: correctly match ids with string
		switch(id)
		{
		case 0: return "mother"; break;
		case 7: return "texture"; break;
		default: return "soaker";
		}
	}

	void Plants::ProcessInput()
	{
		const Input& input = gui->getInput();
		int turn = timeManager->getTurn();
		int unitSelectable = gui->getDebugOptionState("Units Selectable");
		//int tilesSelectable = gui->getDebugOptionState("Tiles Selectable");

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

	std::list<IGUI::DebugOption> Plants::getDebugOptions()
	{
		return std::list<IGUI::DebugOption>({{"Units Selectable", true},
											 {"Tiles Selectable", false}});
	}

	// The "main" function
	void Plants::run()
	{
		timeManager->setNumTurns( 0 );

		animationEngine->registerGame(0, 0);

		std::set<int> spawnedPlants;

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

			for(auto iter : m_game->states[state].plants)
			{
				const parser::Plant& plant = iter.second;

				float x = plant.x - plant.range / 2.0;
				float y = plant.y - plant.range / 2.0;
				bool bSpawned = spawnedPlants.insert(plant.id).second;

				SmartPointer<DrawCircleData> circleData = new DrawCircleData(plant.x, plant.y, plant.range);
				circleData->addKeyFrame( new DrawCircle( circleData, Color(0.1,0.6,0.8,0.2), bSpawned ? FadeIn : None ) );
				turn.addAnimatable( circleData );

				string plantTexture = getPlantFromID(plant.mutation);

				// Coloring plants
				Color plantColor = Color(0.4, 1, .1, 1);
				// If not radpool
				if (plant.mutation != 7)
					plantColor = getPlayerColor(plant.owner);

				SmartPointer<DrawSpriteData> spriteData = new DrawSpriteData(x, y, plant.range, plant.range, plantTexture);
				spriteData->addKeyFrame( new DrawSprite( spriteData, plantColor, bSpawned ? FadeIn : None ) );
				turn.addAnimatable( spriteData );

				// Render animations for this plant
				for(const SmartPointer< parser::Animation >& animation : m_game->states[state].animations[plant.id])
				{
					switch(animation->type)
					{
						case parser::ATTACK:
						{
							const parser::attack& atkAnim = static_cast<const parser::attack&>(*animation);
							//cout << "Attack actingID, targetID: " << atkAnim.actingID << ", " << atkAnim.targetID << endl;
							break;
						}
						case parser::HEAL:
							cout << "Heal" << endl;
							break;
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
