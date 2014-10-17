#ifndef PLANTS_H
#define PLANTS_H

#include <QObject>
#include <QThread>
#include "igame.h"
#include "animsequence.h"
#include <map>
#include <string>
#include <list>

// The Codegen's Parser
#include "parser/parser.h"
#include "parser/structures.h"

using namespace std;

namespace visualizer
{
    class Plants: public QThread, public AnimSequence, public IGame
    {
        Q_OBJECT;
        Q_INTERFACES( visualizer::IGame );
        public: 
            Plants();
            ~Plants();

            PluginInfo getPluginInfo();
            void loadGamelog( std::string gamelog );

            void run();
            void setup();
            void destroy();

            void preDraw();
            void postDraw();

            void addCurrentBoard();
    
            map<string, int> programs;
            
            list<int> getSelectedUnits();
        private:
            parser::Game *m_game;  // The Game Object from parser/structures.h that is generated by the Codegen
            bool m_suicide;
            
            int getWidth()const { return m_game->states[0].mapWidth; }
            int getHeight()const { return m_game->states[0].mapHeight; }
            string getPlantFromID(int id) const;
    }; 

} // visualizer

#endif // PLANTS_H
