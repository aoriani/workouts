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
	void updatePath(const ActorNode* newParent);
	
	
public:	
	ActorNode(const string& name):name(name){}
	void linkTo(ActorNode&);
	friend ostream& operator<< (ostream& out, const ActorNode& node);
	void buildPaths();
};

ostream& operator<< (ostream& out, const ActorNode& node){
    out<<"Actor: "<<node.name<<" Bacon#: "<<(node.path.size()-1)<<endl;
    out<<"Connected to: [ ";
    for(set<ActorNode*>::const_iterator i = node.links.begin(); i != node.links.end();i++){
        out<<(*i)->name<<" ";
    }
    out<<"\b ]"<<endl;
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
    
    if(path.size() > 0){ //We already build the paths
        updatePath(&actor);
    }
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

void ActorNode::updatePath(const ActorNode* newParent){
    if((newParent->path.size() + 1) < path.size()){
        //We now know a shorter route
        annotatePath(*newParent);
        
        //Propagate change
        for(set<ActorNode*>::iterator i = links.begin(); i != links.end(); i++){
            (*i)->updatePath(this);
        }
    }
}


int main(){
    list<ActorNode*> allNodes;

    ActorNode kb("Kevin Bacon");
    allNodes.push_back(&kb);
    
    ActorNode kr("Keanu Reeves");
    allNodes.push_back(&kr);
    kr.linkTo(kb);
    
    ActorNode bw("Bruce Willis");
    allNodes.push_back(&bw);
    bw.linkTo(kr);
    
    ActorNode mp("Michele Pfeifer");
    allNodes.push_back(&mp);
    mp.linkTo(bw);
    mp.linkTo(kr);
    
    ActorNode jc("Jackie Cheng");
    allNodes.push_back(&jc);
    jc.linkTo(mp);
    jc.linkTo(bw);
    
    ActorNode sb("Sandra Bullock");
    allNodes.push_back(&sb);
    sb.linkTo(jc);
    sb.linkTo(kb);

    ActorNode ss("Sylvester Stalone");
    allNodes.push_back(&ss);
    ss.linkTo(bw);

    ActorNode rw("Reese Witherspoon");
    allNodes.push_back(&rw);
    rw.linkTo(ss);
  
    ActorNode sl("Sophia Loren");
    allNodes.push_back(&sl);
    sl.linkTo(rw);
  
    kb.buildPaths();
    
    cout<<"Before"<<endl;
    cout<<"------"<<endl<<endl;
    
    for(list<ActorNode*>::const_iterator it= allNodes.begin(); it != allNodes.end(); it++){
        cout<<(**it)<<endl<<endl;
    }
    
    rw.linkTo(kb);
    
    cout<<"After"<<endl;
    cout<<"-----"<<endl<<endl;

    for(list<ActorNode*>::const_iterator it= allNodes.begin(); it != allNodes.end(); it++){
        cout<<(**it)<<endl<<endl;
    }

    return 0;
}