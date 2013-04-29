#include <iostream>
#include <set>
#include <queue>
#include <string>
#include <list>

using std::set;
using std::list;
using std::queue;
using std::string;
using std::ostream;
using std::cout;
using std::endl;


/*
Problem The game “Six Degrees of Kevin Bacon” involves trying to find the 
shortest connection between an arbitrarily selected actor and Kevin Bacon. 
Two actors are linked if they appeared in the same movie. The goal of the 
game is to connect the given actor to Kevin Bacon using the fewest possible
links.
Given a list of all major movies in history and their casts (assume that 
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
	list<ActorNode*> path; // This should be on a decorator class
	
	void annotatePath(const ActorNode& parent);
	ActorNode(const ActorNode&) {}
	ActorNode& operator=(const ActorNode&){return *this;}
	
public:	
	ActorNode(const string& name):name(name){}
	void linkTo(ActorNode&);
	friend ostream& operator<< (ostream& out, const ActorNode& node);
	void buildPaths();
};

ostream& operator<< (ostream& out, const ActorNode& node){
    out<<"Actor: "<<node.name<<" Bacon#: "<<(node.path.size()-1)<<endl; 
    out<<"Path: [ ";
    for(list<ActorNode*>::const_iterator i = node.path.begin(); i != node.path.end();i++){
        out<<(*i)->name<<">";
    }
    out<<"\b ]";
    return out;
}

void ActorNode::linkTo(ActorNode& actor){
    links.insert((&actor));
    actor.links.insert(this);
}

void ActorNode::annotatePath(const ActorNode& parent){
    path.assign(parent.path.begin(),parent.path.end());
    path.push_back(this);
}

void ActorNode::buildPaths(){
    path.push_back(this);
    queue<ActorNode*> queue;
    queue.push(this);
    
    while(!queue.empty()){
        ActorNode* current = queue.front();queue.pop();
        
        for(set<ActorNode*>::iterator i = current->links.begin(); i != current->links.end(); i++){
            if ((*i)->path.empty()){//Not visited
                (*i)->annotatePath(*current);
                queue.push(*i);
            }
        }     
    }
}


int main(){

    /*
                      
                           |------|
                      KB--KR--BW--MP--JC--SB
                       |       |______|    |         
                       |___________________|                    
    */

    
    ActorNode kb("Kevin Bacon");
    ActorNode kr("Keanu Reeves");
    kr.linkTo(kb);
    ActorNode bw("Bruce Willis");
    bw.linkTo(kr);
    ActorNode mp("Michele Pfeifer");
    mp.linkTo(bw);
    mp.linkTo(kr);
    ActorNode jc("Jackie Cheng");
    jc.linkTo(mp);
    jc.linkTo(bw);
    ActorNode sb("Sandra Bullock");
    sb.linkTo(jc);
    sb.linkTo(kb);
     
    kb.buildPaths();
   
    cout<<kb<<endl<<endl;
    cout<<kr<<endl<<endl;
    cout<<bw<<endl<<endl;
    cout<<mp<<endl<<endl;
    cout<<jc<<endl<<endl;
    cout<<sb<<endl<<endl;
    
    return 0;
}