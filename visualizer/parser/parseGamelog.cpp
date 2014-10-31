#include "parser.h"
#include "sexp/sexp.h"
#include "sexp/parser.h"
#include "sexp/sfcompat.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

namespace parser
{

char *ToLower( char *str )
{
  for( int i = 0; i < strlen( str ); i++ )
  {
    str[ i ] = tolower( str[ i ] );
  }
  return str;
}


static bool parsePlayer(Player& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.playerName = new char[strlen(sub->val)+1];
  strncpy(object.playerName, sub->val, strlen(sub->val));
  object.playerName[strlen(sub->val)] = 0;
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.time = atof(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.spores = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parseMappable(Mappable& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
    return false;
  }

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
    return false;
  }

  object.y = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parsePlant(Plant& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.mutation = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.rads = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxRads = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.radiatesLeft = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxRadiates = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.range = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.uprootsLeft = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxUproots = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.strength = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.minStrength = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.baseStrength = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlant.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxStrength = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parseMutation(Mutation& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.name = new char[strlen(sub->val)+1];
  strncpy(object.name, sub->val, strlen(sub->val));
  object.name[strlen(sub->val)] = 0;
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.type = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.spores = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxRadiates = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxRads = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.range = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxUproots = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.minStrength = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.baseStrength = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMutation.\n Parsing: " << *expression << endl;
    return false;
  }

  object.maxStrength = atoi(sub->val);
  sub = sub->next;

  return true;

}

static bool parseSoak(soak& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = SOAK;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parsesoak.\n Parsing: " << *expression << endl;
    return false;
  }
  object.actingID = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parsesoak.\n Parsing: " << *expression << endl;
    return false;
  }
  object.targetID = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseUproot(uproot& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = UPROOT;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseuproot.\n Parsing: " << *expression << endl;
    return false;
  }
  object.actingID = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseuproot.\n Parsing: " << *expression << endl;
    return false;
  }
  object.fromX = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseuproot.\n Parsing: " << *expression << endl;
    return false;
  }
  object.fromY = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseuproot.\n Parsing: " << *expression << endl;
    return false;
  }
  object.toX = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseuproot.\n Parsing: " << *expression << endl;
    return false;
  }
  object.toY = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseHeal(heal& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = HEAL;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseheal.\n Parsing: " << *expression << endl;
    return false;
  }
  object.actingID = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseheal.\n Parsing: " << *expression << endl;
    return false;
  }
  object.targetID = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parsePlantTalk(plantTalk& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = PLANTTALK;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseplantTalk.\n Parsing: " << *expression << endl;
    return false;
  }
  object.actingID = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseplantTalk.\n Parsing: " << *expression << endl;
    return false;
  }
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;

}
static bool parseAttack(attack& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = ATTACK;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseattack.\n Parsing: " << *expression << endl;
    return false;
  }
  object.actingID = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseattack.\n Parsing: " << *expression << endl;
    return false;
  }
  object.targetID = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseGerminate(germinate& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = GERMINATE;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parsegerminate.\n Parsing: " << *expression << endl;
    return false;
  }
  object.actingID = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parsegerminate.\n Parsing: " << *expression << endl;
    return false;
  }
  object.x = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parsegerminate.\n Parsing: " << *expression << endl;
    return false;
  }
  object.y = atoi(sub->val);
  sub = sub->next;
  return true;

}

static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  if( !expression ) return false;
  expression = expression->list;
  if( !expression ) return false;
  if(expression->val != NULL && strcmp(expression->val, "status") == 0)
  {
    GameState gs;
    while(expression->next != NULL)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(sub->val) == "game")
      {
          sub = sub->next;
          if ( !sub ) return false;
          gs.mapWidth = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.mapHeight = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.turnNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.maxPlants = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.playerID = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.gameNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.bumbleweedSpeed = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.poolDamage = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.poolBuff = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.titanDebuff = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.sporeRate = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.maxSpores = atoi(sub->val);
          sub = sub->next;
      }
      else if(string(sub->val) == "Player")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Player object;
          flag = parsePlayer(object, sub);
          gs.players[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Mappable")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Mappable object;
          flag = parseMappable(object, sub);
          gs.mappables[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Plant")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Plant object;
          flag = parsePlant(object, sub);
          gs.plants[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Mutation")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Mutation object;
          flag = parseMutation(object, sub);
          gs.mutations[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
    }
    game.states.push_back(gs);
  }
  else if(string(expression->val) == "animations")
  {
    std::map< int, std::vector< SmartPointer< Animation > > > animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(ToLower( sub->val ) ) == "soak")
      {
        SmartPointer<soak> animation = new soak;
        if ( !parseSoak(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "uproot")
      {
        SmartPointer<uproot> animation = new uproot;
        if ( !parseUproot(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "heal")
      {
        SmartPointer<heal> animation = new heal;
        if ( !parseHeal(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "plant-talk")
      {
        SmartPointer<plantTalk> animation = new plantTalk;
        if ( !parsePlantTalk(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "attack")
      {
        SmartPointer<attack> animation = new attack;
        if ( !parseAttack(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "germinate")
      {
        SmartPointer<germinate> animation = new germinate;
        if ( !parseGerminate(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
    }
    game.states[game.states.size()-1].animations = animations;
  }
  else if(string(expression->val) == "ident")
  {
    expression = expression->next;
    if ( !expression ) return false;
    sub = expression->list;
    while(sub)
    {
      subsub = sub->list;
      if ( !subsub ) return false;
      int number = atoi(subsub->val);
      if(number >= 0)
      {
        subsub = subsub->next;
        if ( !subsub ) return false;
        subsub = subsub->next;
        if ( !subsub ) return false;
        game.players[number] = subsub->val;
      }
      sub = sub->next;
    }
  }
  else if(string(expression->val) == "game-winner")
  {
    expression = expression->next;
    if ( !expression ) return false;
    expression = expression->next;
    if ( !expression ) return false;
    expression = expression->next;
    if ( !expression ) return false;
    game.winner = atoi(expression->val);
		expression = expression->next;
		if( !expression ) return false;
		game.winReason = expression->val;
  }

  return true;
}


bool parseFile(Game& game, const char* filename)
{
  //bool value;
  FILE* in = fopen(filename, "r");
  //int size;
  if(!in)
    return false;

  parseFile(in);

  sexp_t* st = NULL;

  while((st = parse()))
  {
    if( !parseSexp(game, st) )
    {
      while(parse()); //empty the file, keep Lex happy.
      fclose(in);
      return false;
    }
    destroy_sexp(st);
  }

  fclose(in);

  return true;
}


bool parseGameFromString(Game& game, const char* string)
{

  parseString( string );

  sexp_t* st = NULL;

  while((st = parse()))
  {
    if( !parseSexp(game, st) )
    {
      while(parse()); //empty the file, keep Lex happy.
      return false;
    }
    destroy_sexp(st);
  }

  return true;
}

} // parser
