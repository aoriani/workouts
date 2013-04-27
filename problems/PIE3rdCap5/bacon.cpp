
#include <set>
#include <queue>
#include <string>
#include <list>

using std::set;
using std::queue;
using std::string;


/*
ProbLem The game “Six Degrees of Kevin Bacon” involves trying to find the 
shortest connection between an arbitrarily selected actor and Kevin Bacon. 
Two actors are linked if they appeared in the same movie. The goal of the 
game is to connect the given actor to Kevin Bacon using the fewest possible
links.Given a list of all major movies in history and their casts (assume that 
the names of movies and actors are unique identifiers), describe a data 
structure that could be constructed to efficiently solve Kevin Bacon 
problems. Write a routine that uses your data structure to determine the 
Bacon number (the minimum number of links needed to connect to Kevin Bacon)
 for any actor.
*/


class ActorNode{
private:
	string name;
	set<ActorNode*> links;
	list<ActorNode*> path;
	
public:	
	Actor(const string& name):name(name){}
	void linkTo(const ActorNode&);


};