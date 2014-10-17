#include "plants.h"
#include "plantsAnimatable.h"
#include "frame.h"
#include "version.h"
#include "animations.h"
#include <utility>
#include <time.h>
#include <list>

namespace visualizer
{
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
  
  // Give the Debug Info widget the selected object IDs in the Gamelog
  list<int> Plants::getSelectedUnits()
  {
    // TODO Selection logic
    return list<int>();  // return the empty list
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
  	  case 7: return "soaker"; break;
  	  default: return "soaker";
  	}
  }
  
  // The "main" function
  void Plants::run()
  {
    
    // Build the Debug Table's Headers
    QStringList header;
    header << "one" << "two" << "three";
    //gui->setDebugHeader( header );
    timeManager->setNumTurns( 0 );

    animationEngine->registerGame(0, 0);

    // Look through each turn in the gamelog
    for(int state = 0; state < (int)m_game->states.size() && !m_suicide; state++)
    {
      Frame turn;  // The frame that will be drawn
      
      for(auto iter : m_game->states[state].plants)
      {
      	 const parser::Plant& plant = iter.second;
      	 
      	 cout << plant.mutation << endl;
      	 
      	 float x = plant.x - plant.range / 2.0;
      	 float y = plant.y - plant.range / 2.0;
      	 
      	 SmartPointer<DrawCircleData> circleData = new DrawCircleData(Color(0.1,0.6,0.8,0.3), plant.x, plant.y, plant.range * 1.2);
      	 circleData->addKeyFrame( new DrawCircle( circleData ) );
     	 turn.addAnimatable( circleData );
     	 
     	 string plantTexture = getPlantFromID(plant.mutation);
      
      	 SmartPointer<DrawSpriteData> spriteData = new DrawSpriteData{Color(1,0.6,0,1), x, y, plant.range, plant.range, plantTexture};
      	 spriteData->addKeyFrame( new DrawSprite( spriteData ) );
     	 turn.addAnimatable( spriteData );
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
