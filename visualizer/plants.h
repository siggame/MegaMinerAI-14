#ifndef PLANTS_H
#define PLANTS_H

#include <QObject>
#include <QThread>
#include "igame.h"
#include "animsequence.h"
#include <map>
#include <string>
#include <list>
#include <glm/glm.hpp>

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
		    struct Rect
		    {
			    int left;
			    int top;
			    int right;
			    int bottom;
		    };
                    

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
    
            void wheelEvent(int delta);
            
            void keyPressEvent(std::string& s);
            
            map<string, int> programs;
            
            list<int> getSelectedUnits();

			void ProcessInput();
			void pruneSelection();

            void pushZoomMatrix() const;
            void popZoomMatrix() const;
            
            float zoomFactor() {return m_zoomFactor;}
            
            Point zoomPoint() {return m_zoomPoint;}
            
            int getWidth() const { return m_game->states[0].mapWidth; }
            int getHeight() const { return m_game->states[0].mapHeight; }

            
        private:
            parser::Game *m_game;  // The Game Object from parser/structures.h that is generated by the Codegen
            bool m_suicide;
			list<int> m_SelectedUnits;

			int m_motherPlantID[2];

			static const float GRID_OFFSET;
			static const float PLANT_SIZE;


			Color getPlayerColor(int id) const { return (id == 1) ? Color(0.9,0.5,0.5,1) : Color(0.5,0.5,0.9,1); }
            string getPlantFromID(int id, int owner, int actionState = -1) const;

			void GetSelectedRect(Rect &out) const;
			std::list<IGUI::DebugOption> getDebugOptions();

			void DrawObjectSelection() const;
			void DrawBoxAroundObj(const parser::Mappable& obj, const glm::vec4& color) const;
			void DrawQuadAroundObj(const parser::Mappable& obj, const glm::vec4& color) const;

            float m_zoomFactor;
            Point m_zoomPoint;
			void DrawGUI() const;

			void LoadMotherPlants();

	};

} // visualizer

#endif // PLANTS_H
