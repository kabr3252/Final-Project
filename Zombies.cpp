#include "Zombies.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

Graph::Graph()
{
    user u={};
}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2, int weight){
    //cout<<"adding edge of distance "<<weight<<" between "<<v1<<" and "<<v2<<endl;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
                //cout<<"Found "<<vertices[i].name<<endl;
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    //cout<<"found "<<vertices[j].name<<endl;
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
   // cout<<"in add vertex"<<endl;
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);
    }
}
void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
  // cout<<"surprise"<<vertices.size()<<"<<Vertices.size   adj size>>>"<<vertices[1].adj.size()<<endl;
    for(int i = 0; i < vertices.size(); i++){
    //    cout<<"in for"<<endl;
        int num=0;
        int hold=0;
        cout<<vertices[i].id<<":"<<vertices[i].name<<"-->";
        for(int x = 0; x<vertices[x].adj.size(); x++)
        {
            if(vertices[i].adj[x].weight>0)
            {
                num++;
            }
        }
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(vertices[i].adj[j].weight>0){
            cout<<vertices[i].adj[j].v->name;
                if(hold<num-1)
                {
                    cout<<"***";
                    hold++;
                }
            }
      //    cout<<"distance to "<<vertices[i].adj[j].weight <<endl;
        }
        cout<<endl;
    }
}
vertex Graph::findVertex(int index){
        return vertices[index];
    }
string Graph::findName(int index){
        return vertices[index].name;
    }
bool Graph::idCheck()
{
    //ensures IDs are set
    if(vertices[0].id<0)
    {
        cout<<"Please identify the districts before checking distances"<<endl;
        return false;
    }
    if(vertices[0].id>0)
    {
        return true;
    }
}
int Graph::shortestDistance(string start, string ending)
{
    // used to return distance in miles from next location for traveling with car
     bool check = false;
     int distTot;
    check = idCheck();
    if(check==false)
    {
        return -1;
    }
    else
    {
    bool foundS=false;
    bool foundE=false;
    for(int u=0; u<vertices.size(); u++)
    {
        if(vertices[u].name==start)
        {
            foundS=true;
        }
        if(vertices[u].name==ending)
        {
            foundE=true;
        }
    }
    if(foundS==false or foundE==false)
    {
        cout<<"One or more Areas doesn't exist"<<endl;
    }

    for(int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==start)
        {
            int startingIndex=i;
            for(int j=0; j<vertices.size(); j++)
            {
                if(vertices[j].name==ending)
                {
                    int endI=j;
                    if(vertices[i].id!=vertices[j].id)
                    {
                        cout<<"No safe path between Areas"<<endl;
                        return -1;
                    }
                    else
                    {
                        for(int r=0; r<vertices.size(); r++)
                        {
                            vertices[r].visited=false;
                            vertices[r].distance=0;
                            vertices[r].path.clear();
                        }
                       // cout<<"calculating"<<endl;
                        queue<vertex*> Q;
                        vector<vertex*> path;
                        queueVertex qu;
                        vertex v, p;
                        vertices[i].visited = true;
                        vertices[i].distance=0;
                        distTot=0;
                        int mini = 0;
                        path.push_back(&vertices[i]);
                        vertices[i].path.push_back(&vertices[i]);
                        Q.push(&vertices[i]);
                        while (vertices[j].visited==false) {
                            int minDistance = 100000;
                            //cout<<"in while "<<endl;
                            v = *Q.front();
                            Q.pop();
                            for(int x=0;x<path.size();x++)
                            {
                                for(int z=0;z<v.adj.size();z++)
                                {
                                    if (v.adj[z].v->visited==false && v.adj[z].weight>0)
                                    {

                                       // cout<<"3"<<endl;
                                        v.adj[z].v->distance=v.adj[z].weight+v.distance;
                                        v.adj[z].v->path.swap(v.path);
                                        //cout<<v.path[0]<<"path first"<<endl;
                                        v.adj[z].v->path.push_back(v.adj[z].v);
                                        if(v.adj[z].v->distance<minDistance)
                                        {
                                           // cout<<"4"<<endl;
                                            minDistance=v.adj[z].v->distance;
                                            p = *v.adj[z].v;
                                            mini=z;
                                        }
                                        v.adj[z].v->visited=true;
                                        if(v.adj[z].v->name==ending &&v.adj[z].weight>0&&v.name==start)
                                        {
                                            v.adj[z].v->path.clear();
                                            v.adj[z].v->path.push_back(&v);
                                            v.adj[z].v->path.push_back(v.adj[z].v);

                                        }
                                        Q.push(v.adj[z].v);
                                        path.push_back(v.adj[mini].v);

                                    }

                                }

                            }
                            //cout<<"5"<<endl;
                            path.push_back(v.adj[mini].v);
                            distTot=p.distance;
                        }
                        cout<<distTot<<" miles.";
                        for(int e =0;e<vertices[endI].path.size(); e++)
                        {
                           // cout<<vertices[endI].path[e]->name;
                            //cout<<vertices[endI].path.size();
                            if(e<vertices[endI].path.size()-1)
                            {
                              //  cout<<"-->";
                            }
                        }
                        cout<<endl;
                    }
                }
            }
        }

    }
    }
    return distTot;
}
void Graph::travelCar()
{
 //allows user to travvel by car, first checks that car is in inventory, has gas, and that car is usable (battery in)
    bool truckFound=false;
    for(int i=0;i<u.items.size();i++)
    {
        if(u.items[i].name=="Pickup Truck")
        {
            truckFound=true;
            if(u.items[i].usable==false)
            {
                cout<<"The Pickup Truck needs a battery before you can travel with it"<<endl;
                return;
            }
            if(u.items[i].usable==true)
            {
                if(u.items[i].loc!=u.currentArea)
                {
                    cout<<"The truck is not in this area"<<endl;
                    return;
                }
                else if(u.items[i].loc==u.currentArea)
                {
                    if(u.items[i].uses<=0)
                    {
                        cout<<"No gas! cant travel unless you find some"<<endl;
                        return;
                    }
                    //
                    
                    cout<<"You are currently at "<<u.currentArea->name<<endl;
                    cout<<"You can travel to "<<endl<<endl;;
                    for(int i = 0; i < vertices.size(); i++)
                    {
						cout << vertices[i].name << endl;
					}
					cout<<endl;
					//
					
                    cout<<"What area do you want to go to?"<<endl;
                    string inCity;
                    getline(cin,inCity);
                    bool validIn=false;
                    for(int e=0;e<vertices.size();e++)
                    {
                        if(vertices[e].name==inCity)
                        {
                            validIn=true;
                        }
                    }
                    if(validIn==false)
                    {
                        cout<<"Not a valid entry"<<endl;
                        return;
                    }
                    cout<<"The shortest distance to "<<inCity<<" is: ";
                    //calls shortestDistance to find the amount of gas that will be used
                    int miles=shortestDistance(u.currentArea->name,inCity);
                    cout<<"Travel?(y/n)"<<endl;
                    string cmd;
                    cin>>cmd;
                    if(cmd=="y")
                    {
                        if(miles>u.items[i].uses)
                        {
                            cout<<"Trip is "<<miles<<" miles, you only have "<<u.items[i].uses<<" miles of gas left. Better find fuel!"<<endl;
                            return;
                        }
                        cout<<"Driving to "<<inCity<<"..."<<endl;
                        u.currentArea=findV(inCity);
                        u.items[i].loc=u.currentArea;
                        u.items[i].uses-=miles;
                        cout<<u.items[i].uses<<" miles of gas left"<<endl;
                        fightZombies();  //calls fightZombies based on location.

                    }
                    if(cmd=="n")
                    {
                        cout<<"Ok, happy hunting."<<endl;
                    }

                }
            }
        }
    }
    if(truckFound==false)
    {
        cout<<"You havn't fixed up a truck yet."<<endl;
    }
}
void Graph::shortestPath(string start, string ending)
{
    //Unused, left over from Assignment 8
    bool check = false;
    check = idCheck();
    if(check==false)
    {
        return;
    }

    if(start==ending)
    {
        cout<<"same city"<<endl;
    }
    bool foundS=false;
    bool foundE=false;
    for(int u=0; u<vertices.size(); u++)
    {
        if(vertices[u].name==start)
        {
            foundS=true;
        }
        if(vertices[u].name==ending)
        {
            foundE=true;
        }
    }
    if(foundS==false or foundE==false)
    {
        cout<<"One or more cities doesn't exist"<<endl;
    }
    for(int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==start)
        {
            int startingIndex=i;
            for(int j=0; j<vertices.size(); j++)
            {
                if(vertices[j].name==ending)
                {
                    if(vertices[i].id!=vertices[j].id)
                    {
                        cout<<"No safe path between cities"<<endl;
                        return;
                    }
                    else
                    {
                        for(int r=0; r<vertices.size(); r++)
                        {
                            vertices[r].visited=false;
                            vertices[r].distance=0;
                            vertices[r].path.clear();
                        }
                      //  cout<<"calculating"<<endl;
                        queue<vertex*> Q;
                        vector<vertex> path;
                        vertex v;
                        vertices[i].visited = true;
                        Q.push(&vertices[i]);
                        vertices[i].path.push_back(&vertices[i]);
                        while (!Q.empty()) {
                       // cout<<"Queue not empty"<<endl;
                        v = *Q.front();
                        Q.pop();
                            for(i=0;i<v.adj.size();i++) {
                                cout<<"in for"<<endl;
                                if (v.adj[i].v->visited==false && v.adj[i].weight>0) {
                                    cout<<"in if"<<endl;
                                    v.adj[i].v->distance=v.distance+1;
                                    v.adj[i].v->path.swap(v.path);
                                    v.adj[i].v->path.push_back(v.adj[i].v);
                                    if(v.adj[i].v->name==ending)
                                    {

                                        cout<<v.adj[i].v->distance<<",";
                                        if(v.adj[i].v->name==ending &&v.adj[i].weight>0&&v.name==start)
                                        {
                                            cout<<"enter here"<<endl;
                                            cout<<v.name<<" path "<<v.adj[i].v->name<<endl;
                                            v.adj[i].v->path.clear();
                                            v.adj[i].v->path.push_back(&v);
                                            v.adj[i].v->path.push_back(v.adj[i].v);

                                        }
                                        for(int e=0;e<v.adj[i].v->path.size();e++)
                                        {
                                            cout<<v.adj[i].v->path[e]->name;
                                            if(e<v.adj[i].v->path.size()-1)
                                            {
                                                cout<<",";
                                            }

                                        }
                                        cout<<endl;
                                        return;
                                    }
                                    else
                                    {
                                        v.adj[i].v->visited = true;
                                        Q.push(v.adj[i].v);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void Graph::findDistricts()
{
    //used to set the two districts, districts change after the car is found b/c highway then connects to mall.
    for(int z=0;z<vertices.size();z++)
    {
       vertices[z].visited==false;
    }

    queue<vertex*> Q;
    int dist = 1;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].visited == false) {
            Q.push(&vertices[i]);
            while(!Q.empty())
            {
               int x= 0;
               vertex p= *Q.front();
               Q.pop();
               p.visited=true;
               p.id=dist;
               //cout<<p.name<<" Popped in dist"<< p.id<<endl;
               for (int j = 0; j < p.adj.size(); j++) {
                    if (p.adj[j].weight > 0) {
                        if(p.adj[j].v->visited==true)
                        {
                            p.adj[j].v->id=dist;
                        }
                        else {
                             p.adj[j].v->visited=true;
                             p.adj[j].v->id=dist;
                             Q.push(p.adj[j].v);
                        }
                    }
               }
            }
            dist++;
        }
    }
    for(int z=0; z<vertices.size(); z++)
    {
      // cout<<vertices[z].name<<" district "<<vertices[z].id<<endl;
    }
}
void Graph::onFoot()
{
    //This allows the user to travel on foot to only adjacent areas.
   cout<<"You are currently at "<<u.currentArea->name<<endl;
   cout<<"You can travel to "<<endl<<endl;;
   for(int i=0;i<u.currentArea->adj.size();i++)
   {
       if(u.currentArea->adj[i].weight>0)
       {
           //adjacent areas
           cout<<u.currentArea->adj[i].v->name<<endl;
       }
   }
   cout<<endl;
   cout<<"Where would you like to go?"<<endl;
   string command;
   getline(cin,command);
   bool commandTrue=false;
   bool adjTrue=false;
   for(int j=0;j<vertices.size(); j++)
   {
       if(command==vertices[j].name)
       {
           for(int a=0;a<u.currentArea->adj.size();a++)
           {
               if(u.currentArea->adj[a].weight>0&&u.currentArea->adj[a].v->name==command)
               {
                   u.currentArea=findV(command); //sets users area to the place user wishes to travel.
                   commandTrue=true;
                   adjTrue=true;
                   fightZombies();
               }
           }
           if(adjTrue==false)
           {
               commandTrue=true;
               cout<<"Area inaccessible from here"<<endl;
           }
       }
   }
   if(commandTrue==false)
   {
       cout<<"Area not found."<<endl;
   }
}
void Graph::setUser(string name, int pty)
{
    //sets user information
    u.name=name;
    u.party=pty+1;
    u.health=100;
    u.currentArea=&vertices[0]; //starts in church
}
void Graph::displayStats()
{
    //This is option 5 in the menu, it displays health, number of party members, kills, and inventory
    //it further displays the location of the car, and allows the user to utilize found items.
    cout<<endl;
    cout<<u.name<<"'s health is at "<<u.health<<"%"<<endl;
    cout<<"KILLS: "<<u.kills<<endl;
    cout<<"PARTY MEMBERS: "<<u.party<<endl;
    if(u.health<50)
    {
        cout<<"You might wanna find a health pack or something..."<<endl;
    }
    cout<<"Current Area: "<<u.currentArea->name<<endl<<endl;
    if(!u.items.empty())
    {
        cout<<"*****Items Available*****"<<endl;
        cout<<"--#ATTACK#--"<<endl;
        for(int i=0;i<u.items.size();i++)
        {
            if(u.items[i].uses>0&&u.items[i].type=="Attack")
            {
            cout<<u.items[i].name<<" ";
            cout<<"USES: "<<u.items[i].uses<<"| ";
            }
        }
        cout<<endl;
        cout<<"--#UTILITY#--"<<endl;
        for(int a=0;a<u.items.size();a++)
        {
            if(u.items[a].uses>0&&u.items[a].type=="Utility")
            {

            cout<<u.items[a].name<<" ";
            cout<<"USES: "<<u.items[a].uses<<"| ";
            }
        }
        cout<<endl;
        cout<<"---#HEALTH#---"<<endl;
        for(int s=0;s<u.items.size();s++)
        {
            if(u.items[s].uses>0&&u.items[s].type=="Health")
            {
            cout<<u.items[s].name<<" ";
            cout<<"USES: "<<u.items[s].uses<<"| ";
            }
        }
        cout<<endl<<endl;
        for(int o=0;o<u.items.size();o++)
        {
            //special case with car and cure
            if(u.items[o].name=="Pickup Truck"&&u.items[o].usable==true)
            {
                cout<<u.items[o].name<<" is at the "<<u.items[o].loc->name<<" with "<<u.items[o].uses<<" miles left!"<<endl;
            }
            if(u.items[o].name=="Cure")
            {
                cout<<"You have the cure! Get it to the Campus."<<endl;
            }
        }
        cout<<endl;
        cout<<"#FULLY USED ITEMS: ";
        for(int x=0;x<u.items.size();x++)
        {
             if(u.items[x].uses<=0)
            {
                cout<<u.items[x].name<<" ";
            }
        }
        cout<<endl;
        cout<<"----------------------------------------------"<<endl;
        string in;
        cout<<"Would you like to use an item?(y/n)"<<endl;
        getline(cin,in);
        if(in=="y")
        {
            bool legit=false;
            string itemIn;
            cout<<"Which item would you like to use?"<<endl;
            getline(cin, itemIn);
            //each item that can possibly be used in the game and the respective outcome.
            if(itemIn=="Fuel")
            {
                for(int q=0;q<u.items.size();q++)
                {
                    if(u.items[q].name=="Pickup Truck")
                    {
                        if(u.items[q].loc!=u.currentArea)
                        {
                            cout<<"You left the truck in the "<<u.items[q].loc->name<<"! Cant refuel!"<<endl;
                            return;
                        }
                    }
                }
                for(int i=0;i<u.items.size();i++)
                {
                    if(u.items[i].name=="Fuel")
                    {
                        legit=true;
                        if(u.items[i].uses>0)
                        {
                            bool itemFound=false;
                            cout<<"This refills your car, each use is 1 mile"<<endl;
                            cout<<"How many miles do you want to fill out of "<<u.items[i].uses<<"?"<<endl;
                            int miles;
                            cin>>miles;
                            for(int z=0;z<u.items.size();z++)
                            {
                                //issue loading gun
                                if(u.items[z].name=="Pickup Truck")
                                {

                                    if(u.items[z].uses<40)
                                    {
                                       bool filled=false;
                                       int miLeft= 40-u.items[z].uses;
                                       if(miLeft>=miles)
                                       {
                                           filled=true;
                                           u.items[z].uses+=miles;
                                           u.items[i].uses-=miles;
                                           cout<<"Filled "<<miles<<" miles of gas"<<endl;
                                       }
                                       else if(miLeft<miles&&filled==false)
                                       {
                                           cout<<"Cant fill more than 40 miles worth of gas into truck."<<endl;
                                           miles=miLeft;
                                           u.items[z].uses=40;
                                           u.items[i].uses-=miles;
                                           cout<<"Filled "<<miles<<" miles into truck"<<endl;
                                       }
                                    }

                                    else if(u.items[z].uses=40)
                                    {
                                        cout<<"Truck Full"<<endl;
                                    }

                                }
                            }
                        }
                        else if(u.items[i].uses==0);
                        {
                            cout<<u.items[i].uses<<" miles left for "<<u.items[i].name<<endl;
                        }
                    }
                }
            }
            if(itemIn=="Health Pack")
            {
                for(int i=0;i<u.items.size();i++)
                {
                    if(u.items[i].name=="Health Pack")
                    {
                        legit=true;
                        if(u.items[i].uses>0)
                        {
                            int restored = 20;
                            int hold=0;
                            if(u.health<=80)
                            {
                                u.health+=restored;
                                cout<<"Health restored by "<<restored<<"%"<<endl;
                                cout<<"Health is "<<u.health<<"%"<<endl;
                                u.items[i].uses-=1;
                            }
                            else if(u.health>80&&u.health!=100)
                            {
                                restored=100-u.health;
                                u.health=100;
                                cout<<"Health restored by "<<restored<<"%"<<endl;
                                cout<<"Health is "<<u.health<<"%"<<endl;
                                u.items[i].uses-=1;
                            }
                            else if(u.health==100)
                            {
                                cout<<"You dont need to heal up right now."<<endl;
                            }

                        }
                        else if(u.items[i].uses==0);
                        {
                            cout<<u.items[i].uses<<" uses left for "<<u.items[i].name<<endl;
                        }
                    }
                }
            }
            if(itemIn=="Valium")
            {
                for(int i=0;i<u.items.size();i++)
                {
                    if(u.items[i].name=="Valium")
                    {
                        legit=true;
                        if(u.items[i].uses>0)
                        {
                            int restored = 25;
                            int hold=0;
                            if(u.health<=75)
                            {
                                u.health+=restored;
                                cout<<"Health restored by "<<restored<<"%"<<endl;
                                cout<<"Health is "<<u.health<<"%"<<endl;
                                u.items[i].uses-=1;
                            }
                            else if(u.health>75&&u.health!=100)
                            {
                                restored=100-u.health;
                                u.health=100;
                                cout<<"Health restored by "<<restored<<"%"<<endl;
                                cout<<"Health is "<<u.health<<"%"<<endl;
                                u.items[i].uses-=1;
                            }
                            else if(u.health==100)
                            {
                                cout<<"You dont need to heal up right now."<<endl;
                            }

                        }
                        else if(u.items[i].uses==0);
                        {
                            cout<<u.items[i].uses<<" uses left for "<<u.items[i].name<<endl;
                        }
                    }
                }
            }
            if(itemIn=="Liquor")
            {
                for(int i=0;i<u.items.size();i++)
                {
                    if(u.items[i].name=="Liquor")
                    {
                        legit=true;
                        if(u.items[i].uses>0)
                        {
                            int restored = 25;
                            int hold=0;
                            if(u.health<=75)
                            {
                                u.health+=restored;
                                cout<<"Health restored by "<<restored<<"%"<<endl;
                                cout<<"Health is "<<u.health<<"%"<<endl;
                                u.items[i].uses-=1;
                            }
                            else if(u.health>75&&u.health!=100)
                            {
                                restored=100-u.health;
                                u.health=100;
                                cout<<"Health restored by "<<restored<<"%"<<endl;
                                cout<<"Health is "<<u.health<<"%"<<endl;
                                u.items[i].uses-=1;
                            }
                            else if(u.health==100)
                            {
                                cout<<"You dont need to heal up right now."<<endl;
                            }

                        }
                        else if(u.items[i].uses==0);
                        {
                            cout<<u.items[i].uses<<" uses left for "<<u.items[i].name<<endl;
                        }
                    }
                }

            }
            if(itemIn=="Repair Pack")
            {
                for(int i=0;i<u.items.size();i++)
                {
                    if(u.items[i].name=="Repair Pack")
                    {
                        legit=true;
                        if(u.items[i].uses>0)
                        {
                            int rpr=20;
                            bool itemFound=false;
                            cout<<"This adds 20 uses to a melee attack item"<<endl;
                            cout<<"Which item would you like to use it on?"<<endl;
                            string itmMele;
                            getline(cin, itmMele);
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name==itmMele&&u.items[j].type=="Attack"&&(u.items[j].name!="Rottweiler" or
                                u.items[j].name!="John Guy's Cologne" or u.items[j].name!="Gun"))
                                {
                                    itemFound=true;
                                    u.items[j].uses+=rpr;
                                    u.items[i].uses-=1;
                                    cout<<"Item: "<<u.items[j].name<<" uses increased by "<<rpr<<" to "<<u.items[j].uses<<endl;
                                }
                            }
                            if(itemFound==false)
                            {
                                cout<<"Item cannot be repaired"<<endl;
                            }
                        }
                        else if(u.items[i].uses==0);
                        {
                            cout<<u.items[i].uses<<" uses left for "<<u.items[i].name<<endl;
                        }
                    }
                }
            }
            if(itemIn=="Ammo")
            {
                for(int i=0;i<u.items.size();i++)
                {
                    if(u.items[i].name=="Ammo")
                    {
                        legit=true;
                        if(u.items[i].uses>0)
                        {
                            bool itemFound=false;
                            cout<<"This reloads your gun, each use is 1 bullet"<<endl;
                            cout<<"How many bullets would you like to reload out of "<<u.items[i].uses<<"?"<<endl;
                            int bullets;
                            cin>>bullets;
                            for(int z=0;z<u.items.size();z++)
                            {
                                //issue loading gun
                                if(u.items[z].name=="Gun")
                                {

                                    if(u.items[z].uses<18)
                                    {
                                        bool loaded=false;
                                       int emptyRounds= 18-u.items[z].uses;
                                       if(emptyRounds>=bullets)
                                       {
                                           loaded=true;
                                           u.items[z].uses+=bullets;
                                           u.items[i].uses-=bullets;
                                           cout<<"Loaded "<<bullets<<" rounds into gun"<<endl;
                                           cout<<"Gun has "<<u.items[z].uses<<" rounds left"<<endl;
                                       }
                                       else if(emptyRounds<bullets&&loaded==false)
                                       {
                                           cout<<"Cant load the gun past 18 rounds"<<endl;
                                           bullets=emptyRounds;
                                           u.items[z].uses=18;
                                           u.items[i].uses-=bullets;
                                           cout<<"Loaded "<<bullets<<" rounds into gun"<<endl;
                                           cout<<"Gun has "<<u.items[z].uses<<" rounds left"<<endl;
                                       }
                                    }

                                    else if(u.items[z].uses=18)
                                    {
                                        cout<<"Gun fully loaded"<<endl;
                                    }

                                }
                            }
                        }
                        else if(u.items[i].uses==0);
                        {
                            cout<<u.items[i].uses<<" uses left for "<<u.items[i].name<<endl;
                        }
                    }
                }
            }
            if(itemIn=="Car Battery")
            {
                legit=true;
                if(u.currentArea!=findV("Car Dealership"))
                {
                    cout<<"There is no car here"<<endl;
                }
                else if(u.currentArea==findV("Car Dealership"))
                {
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].name=="Car Battery")
                        {
                            u.items[i].uses-=1;
                        }
                        if(u.items[i].name=="Pickup Truck")
                        {
                            if(u.items[i].usable==true)
                            {
                                cout<<"You already put a battery in the truck, its ready to go!"<<endl;
                                return;
                            }
                            u.items[i].usable=true;
                            cout<<"You put the battery in the car. It works now!"<<endl;
                            cout<<"You can now use the highway to travel to other places!"<<endl;
                            addEdge("Highway","Mall",5);
                            addEdge("Mall","Highway",5);
                            for(int c=0;c<vertices.size();c++)
                            {
                                vertices[c].id=1;
                            }
                        }
                    }
                }
            }
            if(itemIn=="Gun" or itemIn=="Rottweiler" or itemIn=="Axe" or itemIn=="Shattered Bottle" or itemIn=="Pledge Paddle"
               or itemIn=="John Guy's Cologne" or itemIn=="Grenade")
            {
                legit=true;
                cout<<"Attack items cant be used without zombies around! Go find some if you wanna use that."<<endl;
            }
            else if(legit==false)
            {
                cout<<"Item not found"<<endl;
            }
        }
        else if(in!="y")
        {
            cout<<"Ok, come back when you need to use something."<<endl;
        }
    }
    else
    {
        cout<<"No items"<<endl;
    }
}
vertex *Graph::findV(string n)
{
    //returns pointer vertex when given string name of vertex
    for(int i=0;i<vertices.size();i++)
    {
        if(vertices[i].name==n)
        {
            return &vertices[i];
        }
    }
}
void Graph::createItems()
{
    //This creates items, gives them a type, and places them in the proper area
    itm Gun;
    Gun.name="Gun";
    Gun.uses = 18;
    Gun.loc = findV("Restaurant");
    Gun.type = "Attack";
    Gun.found=false;
    Gun.usable=true;
    allItems.push_back(Gun);
    vertices[8].it.push_back(Gun);

    itm Rottweiler;
    Rottweiler.name="Rottweiler";
    Rottweiler.uses = 100000;
    Rottweiler.loc = findV("Prison");
    Rottweiler.type = "Attack";
    Rottweiler.found=false;
    Rottweiler.usable=true;
    allItems.push_back(Rottweiler);
    vertices[13].it.push_back(Rottweiler);

    itm Fuel;
    Fuel.name="Fuel";
    Fuel.uses = 30;
    Fuel.loc = findV("Highway");
    Fuel.found=false;
    Fuel.usable=true;
    Fuel.type = "Utility";
    allItems.push_back(Fuel);
    vertices[14].it.push_back(Fuel);
    vertices[10].it.push_back(Fuel);

    itm Axe;
    Axe.name="Axe";
    Axe.uses = 100;
    Axe.loc = findV("Church");
    Axe.found=false;
    Axe.usable=true;
    Axe.type = "Attack";
    allItems.push_back(Axe);
    vertices[0].it.push_back(Axe);

    //Battery
    itm Battery;
    Battery.name="Car Battery";
    Battery.uses= 1;
    Battery.found=false;
    Battery.usable=true;
    Battery.type="Utility";
    Battery.loc = findV("Country Club");
    allItems.push_back(Battery);
    vertices[9].it.push_back(Battery);

    itm Cure;
    Cure.name="Cure";
    Cure.uses= 1;
    Cure.found=false;
    Cure.usable=true;
    Cure.type="Cure";
    Cure.loc = findV("Hospital");
    allItems.push_back(Cure);
    vertices[11].it.push_back(Cure);

    itm Grenade;
    Grenade.name="Grenade";
    Grenade.uses= 1;
    Grenade.found=false;
    Grenade.usable=true;
    Grenade.type="Attack";
    Grenade.loc = findV("Church");
    allItems.push_back(Grenade);
    vertices[0].it.push_back(Grenade);
    vertices[12].it.push_back(Grenade);
    vertices[2].it.push_back(Grenade);


    itm Liquor;
    Liquor.name="Liquor";
    Liquor.uses= 1;
    Liquor.found=false;
    Liquor.usable=true;
    Liquor.type="Health";
    Liquor.loc = findV("Restaurant");
    allItems.push_back(Liquor);
    vertices[8].it.push_back(Liquor);
    vertices[1].it.push_back(Liquor);

    itm Valium;
    Valium.name="Valium";
    Valium.uses= 2;
    Valium.found=false;
    Valium.usable=true;
    Valium.type="Health";
    Valium.loc = findV("Church");
    allItems.push_back(Valium);
    vertices[11].it.push_back(Valium);


    itm JgC;
    JgC.name="John Guy's Cologne";
    JgC.uses= 1;
    JgC.found=false;
    JgC.usable=true;
    JgC.type="Attack";
    JgC.loc = findV("Church");
    allItems.push_back(JgC);
    vertices[1].it.push_back(JgC);

    itm Car;
    Car.name="Pickup Truck";
    Car.uses=20;
    Car.found=false;
    Car.usable=false;
    Car.type = "Travel";
    Car.loc = findV("Car Dealership");
    allItems.push_back(Car);
    vertices[3].it.push_back(Car);

    itm HealthPk;
    HealthPk.name="Health Pack";
    HealthPk.uses=1;
    HealthPk.found=false;
    HealthPk.usable=true;
    HealthPk.type="Healing";
    HealthPk.loc=findV("Hospital");
    allItems.push_back(HealthPk);
    vertices[5].it.push_back(HealthPk);

    itm Ammo;
    Ammo.name ="Ammo";
    Ammo.uses =20;
    Ammo.found=false;
    Ammo.usable=false;
    Ammo.type = "Utility";
    Ammo.loc=findV("Theater");
    allItems.push_back(Ammo);
    vertices[7].it.push_back(Ammo);
    vertices[2].it.push_back(Ammo);
    vertices[11].it.push_back(Ammo);

    itm Bttl;
    Bttl.name="Shattered Bottle";
    Bttl.uses=30;
    Bttl.found=false;
    Bttl.usable=true;
    Bttl.type = "Attack";
    Bttl.loc=findV("Church");
    allItems.push_back(Bttl);
    vertices[1].it.push_back(Bttl);

    itm Paddle;
    Paddle.name="Pledge Paddle";
    Paddle.uses=15;
    Paddle.found=false;
    Paddle.usable=true;
    Paddle.type = "Attack";
    Paddle.loc=findV("Frat House");
    allItems.push_back(Paddle);
    vertices[4].it.push_back(Paddle);

    itm Repair;
    Repair.name="Repair Pack";
    Repair.uses=1;
    Repair.found=false;
    Repair.usable=true;
    Repair.type="Utility";
    Repair.loc=findV("Whole Foods");
    vertices[6].it.push_back(Repair);





}
void Graph::Look()
{
    //looks around area to find items
    bool itemsIn=false;
    cout<<"You are looking around in the "<<u.currentArea->name<<"."<<endl;
    if(u.currentArea->name=="Church"&&u.currentArea->userVisit==false) //special case for church
    {
        cout<<"Thank God, your friends just showed up!"<<endl;
        u.currentArea->userVisit=true;
    }
    int carIndex;
    bool carIn=false;
    bool bttry=false;
    cout<<"You search and find..."<<endl;
    string command;
    for(int e=0;e<u.items.size();e++)
    {
        //figures out if car or battery were found /special case
        if(u.items[e].name=="Pickup Truck"&&u.items[e].usable==false)
        {
            carIn=true;
            carIndex=e;
        }
        if(u.items[e].name=="Car Battery")
        {
            bttry=true;
        }

    }
    if(u.currentArea==findV("Car Dealership")&&carIn==true) //for finding car, gives instructions on how to fix
    {
        cout<<"the Pickup Truck, it needs a battery."<<endl;
        if(bttry==true)
        {
            cout<<"You have one in your inventory! Use it by going to the inventory screen."<<endl;
        }
    }
    else if(u.currentArea->it.empty())
    {
        cout<<"Nothing. That sucks. "<<endl;
        itemsIn=false;
    }
    else
    {
        bool fFound=false;
        for(int i=0;i<u.currentArea->it.size();i++)
        {
            if(u.currentArea->it[i].found==false)
            {
                cout<<u.currentArea->it[i].name<<endl;
                itemsIn=true;
            }
            else
            {
                fFound = true;
            }
        }
        if(fFound==true)
            {
                cout<<"Nothing. That sucks."<<endl;
                itemsIn = false;
            }
    }
    if(itemsIn==true)
    {
        cout<<"Would you like to pick up these items?(y/n)"<<endl;
        getline(cin,command);
        bool mele=false;
        bool utilt=false;
        bool heal=false;
        bool cure=false;
        bool foundBfore=false;
        bool truck=false;
        if(command=="y")
        {
            for(int j=0;j<u.currentArea->it.size();j++)
            {
                if(u.currentArea->it[j].name!="Pickup Truck")
                {
                    cout<<u.currentArea->it[j].name<<" was picked up"<<endl;
                }
                if(u.currentArea->it[j].name=="Pickup Truck")  //cant pick up car, character is not superman. special case
                {
                    cout<<u.currentArea->it[j].name<<" is ready to be fixed."<<endl;
                }
                u.currentArea->it[j].found=true;
                for(int r=0;r<u.items.size();r++)
                {
                    if(u.currentArea->it[j].name==u.items[r].name)
                    {
                        foundBfore=true;
                        u.items[r].uses+=u.currentArea->it[j].uses;
                    }
                }
                if(foundBfore==false)
                {
                    u.items.push_back(u.currentArea->it[j]);
                }
                    if(u.currentArea->it[j].name=="Axe" or u.currentArea->it[j].name=="Pledge Paddle" or u.currentArea->it[j].name=="Shattered Bottle")
                    {
                        mele=true;
                    }
                    if(u.currentArea->it[j].type=="Health")
                    {
                        heal=true;
                    }
                    if(u.currentArea->it[j].type=="Utility")
                    {
                        utilt=true;
                    }
                    if(u.currentArea->it[j].name=="Cure")
                    {
                        cure=true;
                    }
                    if(u.currentArea->it[j].name=="Pickup Truck")
                    {
                        truck=true;
                    }

            }
            //this part gives directions on how to use each type of item based on bools above.
            if(mele==true or utilt==true or heal==true or cure==true)
            {
                cout<<endl;
                cout<<"John Guy's Advice:"<<endl;
            }
            if(mele==true)
            {
                cout<<"'Remember, Melee weapons will make you tired if you swing too many times at once'"<<endl;
            }
            if(utilt==true)
            {
                cout<<"'Utility type items repair, reload or refuel. use em in the inventory/stats screen'"<<endl;
            }
            if(heal==true)
            {
                cout<<"'Healin items heal you. Check your health and heal up at the inventory/stats screen so you dont die!"<<endl;
            }
            if(cure==true)
            {
                cout<<"'Take the cure to the campus, you'll need a car to get there for sure."<<endl;
            }
            if(truck==true)
            {
                cout<<"'You found a truck! gotta fix it up with a battery tho, if you have find a Car Battery go to your inventory and use it!'"<<endl;
            }

        }
        if(command=="n")
        {
            cout<<"Come back when you wanna pick this stuff up."<<endl;
        }
        else if(command=="")
        {
            cout<<"Invalid Input"<<endl;
        }
    }
}
void Graph::fightZombies()
{

    bool validArea=false;
    //this function has a variant of fights depending on area.  Each one is coded with all the weapons that can be used
    //once the zombies are dead, they exit out.
    // it is possible to enter Dead(); function, which exits the game cause the character is dead.
    if(u.currentArea==findV("Restaurant"))
    {
        validArea=true;
        string cmnd;
        int numZombies=0;
        if(u.currentArea->userVisit==false)
        {
        cout<<endl;
        cout<<"John Guy's Advice:"<<endl;
        cout<<"'Hey kid, spellin is still importn't in the zombie apocalypse."<<endl;
        cout<<"Be sure to type exactly what yer lookin to do."<<endl;
        cout<<endl;
        numZombies = 10;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", they are eating chicken marinara"<<endl;
        cout<<" this could get messy."<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we killed most of the zombies, so its safe to wander for a bit."<<endl;
            cout<<"There are probably a few more around here tho. Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 3;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" of those fools."<<endl;
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;
            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    cout<<endl;
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }

                    else if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! The zombies swarmed and killed one of your party members!"<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }
                                }
                                else if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"John Guy's Advice: 'Grenades are fun!'"<<endl;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast... Idiot..."<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save the Grenade for later"<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later"<<endl;
                                    }
                                }
                                if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                         //WHAT IF NOT NUMBER????

                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the church"<<endl;
                u.currentArea=findV("Church");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... be very quiet..."<<endl<<endl;
                u.health-=15;
                cout<<"You put your hand on a shard of glass and cut it. Health = "<<u.health<<"%"<<endl<<endl;
                Dead();
                return;
            }
        }
    }
    if(u.currentArea==findV("Theater"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 15;
        cout<<endl;
        cout<<"John Guy's Advice:"<<endl;
        cout<<"'Heard there was a cure in one of these areas, if you find it get it to the Campus, there are researchers round there.'"<<endl<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", they were watching The Notebook!"<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we killed most of the zombies, so its safe to wander for a bit."<<endl;
            cout<<"We could always see if any other ones are watching romantic comedies... Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 6;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"watching Shrek 5 in 3D...  Looks like a terrible movie.";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! The zombies heard you disturbing their movie and killed one of your party members!"<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"John Guy's Advice: 'Grenades are fun!'"<<endl;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast... He didn't even get to see the ending"<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, A theater is no place for a grenade."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies); //needds to be above because conditional can change
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }      //WHAT IF NOT NUMBER????
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0 )
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    else if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the church"<<endl;
                u.currentArea=findV("Church");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... be quiet and watch the movie..."<<endl<<endl;
                cout<<"You put your hand in melted chocolate... Gross..."<<endl<<endl;
                Dead();
                return;
            }
        }
    }
    if(u.currentArea==findV("Car Dealership"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 20;
        cout<<endl;
        cout<<"John Guy's Advice:"<<endl;
        cout<<"'If yer needin to heal up, refuel, or reload, check the inventory menu and use an item."<<endl;
        cout<<"yah know, you can check your health and the location of your car from the inventory menu too.'"<<endl<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", they are racing cars!"<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we killed most of the zombies, so we can chill out for a while."<<endl;
            cout<<"We could always see if there are any zombies trying to sell cars or something... "<<endl;
            cout<<"Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 4;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"they were enjoying a few beers in the back office... weird...";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! The zombies saw you and killed one of your party members"<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.health>80)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast... Atleast the sweet cars are ok"<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, itd be a shame to grenade these awesome cars."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);      //WHAT IF NOT NUMBER????
                                    if(shot>numZombies);
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the church"<<endl;
                u.currentArea=findV("Church");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... The zombies are talking about proper sales techniques..."<<endl<<endl;
                cout<<"You accidentally pushed on the horn of a car!   Maybe they didnt hear us... stay quiet."<<endl<<endl;
                 cout << "=======What Do======" << endl;
                cout << "1. Areas" << endl;
                cout << "2. Look Around" << endl;
                cout << "3. Travel by Car" << endl;
                cout << "4. Travel on Foot" << endl;
                cout << "5. Inventory/Stats" << endl;
                cout << "6. Quit" << endl;
                string ign;
                cin>>ign;
                cin.ignore();
                cout<<"NO! the zombies heard the car horn! They knocked you out and stole your money!"<<endl;
                cout<<"Health -10"<<endl;
                cout<<"You wake up hours later to the sound of crows."<<endl;
                u.health-=10;
                Dead();
                return;
            }
        }
    }
    if(u.currentArea==findV("Whole Foods"))
    {
        validArea=true;
        cout<<endl;
        cout<<"You are in "<<u.currentArea->name<<", the zombies here are vegan, so you can roam around without worry."<<endl<<endl;
        cout<<"John Guy's Advice:"<<endl;
        cout<<"'Never trust a carnivore that don't eat meat'"<<endl;
        cout<<"... what the hell does that mean?"<<endl<<endl;
    }
    if(u.currentArea==findV("Frat House"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 12;
        cout<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombie brothers in the "<<u.currentArea->name<<", it sounds like"<<endl;
        cout<<"they are moaning 'Who do you know here'"<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"There are solo cups all over the floor, and ping pong balls on the table. seems empty tho."<<endl;
            cout<<"We could always see if there are any zombies playing drinking games or something... "<<endl;
            cout<<"Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 8;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"they were playing beer pong and rocking out to electronic dance music.  Radical...";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! You interrupted the zombies fraternity chant!"<<endl;
                                            cout<<"They killed one of your party members in a fit of roid rage."<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast..."<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, no need to be a party pooper."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);      //WHAT IF NOT NUMBER????
                                    if(shot>numZombies);
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the mall"<<endl;
                u.currentArea=findV("Mall");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... You hear one zombie yell to another 'Come at me Bro' "<<endl<<endl;
                cout<<"The other zombies hold him back."<<endl<<endl;
                Dead();
                return;
            }
        }
    }
    if(u.currentArea==findV("Hospital"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 25;
        cout<<endl;
        cout<<"John Guy's Advice:"<<endl;
        cout<<"'The hospital is the most likely place to find a cure.'"<<endl<<endl;
        cout<<"Oh no! there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", its overrun!"<<endl;
        cout<<"A group of people are screaming for help! What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we killed most of the zombies, so its safe to wander for a bit."<<endl;
            cout<<"We could always see if there are any still lurking around... Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 6;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"they were in the morgue dancing to thriller.";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! The zombies heard the trigger click and swarmed! They killed one of your party members!"<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"John Guy's Advice: 'Grenades are fun!'"<<endl;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast... He didn't stand a chance"<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, A hospital is no place for a grenade."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>4)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies); //needds to be above because conditional can change
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }      //WHAT IF NOT NUMBER????
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0 )
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    else if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>2)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the church"<<endl;
                u.currentArea=findV("Church");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... be very quiet..."<<endl<<endl;
                cout<<"You can walk around, just be careful so they dont hear you."<<endl<<endl;
                Dead();
                return;
            }
        }
        cout<<"Doctors: 'Thanks for saving us! We owe you our lives. We have been working on a cure here for a long time. ";
        cout<<"Its on one of the tables around here, please look around and take it. There is a research lab on Campus that ";
        cout<<"will probably want that so they can figure out a way to distribute it."<<endl<<endl;
        cout<<"One of them decided to come with you."<<endl;
        u.party+=1;

    }
    if(u.currentArea==findV("Campus"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 30;
        cout<<endl;
        cout<<"John Guy's Advice:"<<endl;
        cout<<"'Those smart kids at the Campus will know what to do with the cure.'"<<endl<<endl;
        cout<<"Oh no! there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<"!"<<endl;
        cout<<"It looks like there is a safe building on the other side of campus! What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we killed most of the zombies, so its safe to wander for a bit."<<endl;
            cout<<"We could always see if there are any still lurking around... Wanna go hunting? (y/n)"<<endl;
            getline(cin,cmnd);
            if(cmnd=="n")
            {
                Victory();
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 8;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"they were in the UMC eating Dominos.";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! The zombies heard the trigger click and swarmed! They killed one of your party members!"<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"John Guy's Advice: 'Grenades are fun!'"<<endl;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast... He didn't stand a chance"<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, grenades are wild."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>1)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies); //needds to be above because conditional can change
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }      //WHAT IF NOT NUMBER????
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0 )
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    else if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                Dead();
                if(u.party>2)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }

                cout<<"You are in the Mall"<<endl;
                u.currentArea=findV("Mall");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... be very quiet..."<<endl<<endl;
                cout<<"You are hiding in a classroom. Looks like zombies were working on calculus in here."<<endl<<endl;
                Dead();
                return;
            }
        }
        bool Curein=false;
        for(int a=0;a<u.items.size();a++)
        {
            if(u.items[a].name=="Cure")
            {
               // cout<<"There is shouting beyond one of the doors. What do you wanna say?"<<endl;
                cin.ignore();
                Victory();
                Curein=true;
            }
        }
        if(Curein==false)
        {
            cout<<"Researcher: 'Hello "<<u.name<<" it was rumored you were looking for the cure. ";
            cout<<"Apparently you havn't found it yet. Bring it to us when you do."<<endl;
        }

    }
    if(u.currentArea==findV("Prison"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 9;
        cout<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<"."<<endl;
        cout<<"they look pretty mean and angry."<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we cleaned the place out."<<endl;
            cout<<"We could always see if there are any zombies around though... "<<endl;
            cout<<"Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 4;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"they were comparing gang tattoos.";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! The zombies started a prison riot"<<endl;
                                            cout<<"They killed one of your party members in the chaos."<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast..."<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, prisons and grenades dont mix well."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);      //WHAT IF NOT NUMBER????
                                    if(shot>numZombies);
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the mall"<<endl;
                u.currentArea=findV("Mall");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... John Guy would be so disappointed "<<endl<<endl;
                cout<<"you kneeled down on a prison shank.  Health -30"<<endl<<endl;
                u.health-=30;
                Dead();
                return;
            }
        }
    }
    if(u.currentArea==findV("Mall"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 12;
        cout<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", "<<endl;
        cout<<"They are checking out the clearence section in Nordstrom Rack."<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we cleared the place out"<<endl;
            cout<<"We could always see if there are any zombies still shopping... "<<endl;
            cout<<"Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 6;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"one of the zombies was trying on shoes... weird...";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! You runed the zombies shopping spree"<<endl;
                                            cout<<"They killed one of your party members in a fit of black friday rage."<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast..."<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save that for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);      //WHAT IF NOT NUMBER????
                                    if(shot>numZombies);
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the mall"<<endl;
                u.currentArea=findV("Mall");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"..."<<endl<<endl;
                cout<<"Your probably gunna die."<<endl<<endl;
                Dead();
                return;
            }
        }
    }
    if(u.currentArea==findV("Bar"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 18;
        cout<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", "<<endl;
        cout<<"They were having some shots after a long days work"<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we cleared the place out"<<endl;
            cout<<"We could always see if any other zombies are trying to get wild. "<<endl;
            cout<<"Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 5;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"One was trying to light a table on fire.";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun! You runed their pre shot toast"<<endl;
                                            cout<<"They killed one of your party members in a drunken rage."<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast..."<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save that for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);      //WHAT IF NOT NUMBER????
                                    if(shot>numZombies);
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the mall"<<endl;
                u.currentArea=findV("Mall");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"..."<<endl<<endl;
                cout<<"Stay quiet."<<endl<<endl;
                Dead();
                return;
            }
        }
        cout<<endl<<"John Guy is here!"<<endl<<endl;
        cout<<"'Way to handle those zombies kid, reminds me alot of myself when I was young. I'm glad I found ya again, ";
        cout<<"there is something on the table over there for ya.  Happy hunting kiddo.'"<<endl;
    }
    if(u.currentArea==findV("Country Club"))
    {
        validArea=true;
        string cmnd;
        int numZombies;
        if(u.currentArea->userVisit==false)
        {
        numZombies = 12;
        cout<<endl;
        cout<<"Oh crap, there are "<<numZombies<<" zombies in the "<<u.currentArea->name<<", "<<endl;
        cout<<"They were just about to head out for a round of golf."<<endl;
        cout<<"What do you wanna do?"<<endl;
        }
        if(u.currentArea->userVisit==true)
        {

            cout<<"Last time we were here we cleared the place out"<<endl;
            cout<<"We could always see if there are any wallstreet zombies around... "<<endl;
            cout<<"Wanna go hunting? (y/n)"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                return;
            }
            if(cmnd=="y")
            {
            numZombies = 6;
              cout<<"You wander around for a while looking for some undead to beat up on, you find "<<numZombies<<" zombies"<<endl;
              cout<<"They were checking their stock portfolio.";
              cout<<"What do you wanna do?"<<endl;

            }
        }
        while(numZombies>0)
        {
            cout<<"w = weapons"<<endl;
            cout<<"r = run"<<endl;
            cout<<"h = hide"<<endl;
            cin>>cmnd;
            if(cmnd=="n")
            {
                u.kills=numZombies;
                numZombies=0;
                cout<<"Zombies Nuked"<<endl;

            }
            if(cmnd=="w")
            {
                if(u.items.empty())
                {
                    cout<<"You dont have any items"<<endl;
                }
                else
                {
                    bool attkItms = false;
                    for(int i=0;i<u.items.size();i++)
                    {
                        if(u.items[i].type=="Attack")
                        {
                        cout<<u.items[i].name<<" can be used "<<u.items[i].uses<<" more times"<<endl;
                        attkItms=true;
                        }
                    }
                    if(attkItms==false)
                    {
                        cout<<"No weapons in inventory"<<endl;
                    }
                    cout<<endl;
                    if(attkItms==true)
                    {
                        cout<<"Which one would you like to use?"<<endl;
                        cin.ignore();
                        getline(cin,cmnd);
                        bool validEntry = false;
                        if(cmnd=="Gun")
                        {
                            validEntry=true;
                            bool foundGun=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Gun")
                                {
                                    if(u.items[j].uses==0)
                                    {
                                        if(u.party>1)
                                        {
                                            cout<<"There are no bullets in the gun!"<<endl;
                                            cout<<"They killed one of your party members with a golf club."<<endl;
                                            u.party-=1;
                                        }
                                        else if(u.party=1)
                                        {
                                            cout<<"There are no bullets in the gun! You tried to fire and a zombie wounded you!"<<endl;
                                            cout<<u.name<<"'s health reduced by 30%"<<endl;
                                            u.health-=30;
                                            Dead();
                                        }
                                    }
                                    else
                                    {
                                        foundGun=true;
                                        string shots;
                                        int shot;
                                        cout<<"How many times do you want to shoot?"<<endl;
                                        cin>>shots;
                                        shot=stoi(shots);
                                        if(cin.fail())
                                        {
                                            cin.ignore();
                                            cout<<"That is not a number"<<endl;
                                        }
                                        if(shot>u.items[j].uses)
                                        {
                                            cout<<"You dont have that many bullets in the gun!"<<endl;
                                        }
                                        else
                                        {
                                            if(shot<=numZombies)
                                            {
                                                cout<<"You used the Gun "<<shot<<" times!"<<endl;
                                                numZombies-=shot;
                                                u.kills+=shot;
                                                cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                                u.items[j].uses-=shot;
                                            }
                                            else
                                            {
                                                cout<<"Don't waste ammo!"<<endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(cmnd=="Axe")
                        {
                            validEntry=true;
                            bool foundAxe=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Axe"&&u.items[j].uses>0)
                                {
                                    foundAxe=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to chop them up?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Axe "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got fatigued. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                if(u.items[j].name=="Axe"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Grenade")
                        {
                            validEntry=true;
                            bool foundGrenade=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Grenade" && u.items[j].uses>0)
                                {
                                    foundGrenade=true;
                                    int shot=15;
                                    string inStr;
                                    cout<<"These can be dangerous, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You used the Grenade!"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           killed=shot;
                                           numZombies-=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        u.health-=35;
                                        cout<<"You got hit by the blast. Health = "<<u.health<<"%"<<endl;
                                        Dead();
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died in the blast..."<<endl;
                                            u.party-=1;
                                            cout<<"Party is down to "<<u.party<<" members."<<endl;
                                        }

                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save that for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="Grenade" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="John Guy's Cologne")
                        {
                            validEntry=true;
                            bool foundJgC=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="John Guy's Cologne"&&u.items[j].uses>0)
                                {
                                    foundJgC=true;
                                    int shot=50;
                                    string inStr;
                                    cout<<"John Guy's Cologne is the most potent substance on earth, are you sure?(y/n)"<<endl;
                                    cin>>inStr;
                                    if(inStr=="y")
                                    {
                                        cout<<"You sprayed John Guy's Cologne"<<endl;
                                        int killed=0;
                                        if(numZombies>=shot)
                                        {
                                           numZombies-=shot;
                                           killed=shot;
                                        }
                                        else if(numZombies<shot)
                                        {
                                            killed=numZombies;
                                            numZombies=0;
                                        }
                                        u.kills+=killed;
                                        cout<<"Wow, John Guy's Cologne killed all of them..."<<endl;
                                        if(u.party>2)
                                        {
                                            cout<<"One of your party members died from asphyxiation..."<<endl;
                                            u.party-=1;
                                            cout<<"Your party is down to "<<u.party<<" members."<<endl;
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left."<<endl;
                                        u.items[j].uses-=1;
                                    }
                                    else
                                    {
                                        cout<<"Good choice, save John Guy's Cologne for later."<<endl;
                                    }
                                }
                                else if(u.items[j].name=="John Guy's Cologne" && u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<u.items[j].name<<endl;
                                }
                            }
                        }
                        if(cmnd=="Rottweiler")
                        {
                            validEntry=true;
                            bool foundRottweiler=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Rottweiler"&&u.items[j].uses>0)
                                {
                                    foundRottweiler=true;
                                    int kills=0;
                                    cout<<"RELEASE THE HOUNDS!"<<endl;
                                    cout<<"..."<<endl;
                                    if(numZombies>4)
                                    {
                                        cout<<"Your dog killed 4 zombies!"<<endl;
                                        numZombies-=4;
                                        u.kills+=4;
                                    }
                                    else if(numZombies<4)
                                    {
                                        kills=numZombies;
                                        numZombies=0;
                                        u.kills+=kills;
                                        cout<<"Your dog killed "<<kills<<" zombies!"<<endl;
                                    }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=4;
                                }
                                else if(u.items[j].name=="Rottweiler"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<"he's too tired"<<endl;
                                }
                            }
                        }
                        if(cmnd=="Pledge Paddle")
                        {
                            validEntry=true;
                            bool foundPaddle=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses>0)
                                {
                                    foundPaddle=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to haze these zombies?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);      //WHAT IF NOT NUMBER????
                                    if(shot>numZombies);
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Pledge Paddle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=5;
                                            cout<<"You got tired. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Pledge Paddle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use "<<cmnd<<endl;
                                }
                            }
                        }
                        if(cmnd=="Shattered Bottle")
                        {
                            validEntry=true;
                            bool foundBttl=false;
                            for(int j=0;j<u.items.size();j++)
                            {
                                if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses>0)
                                {
                                    foundBttl=true;
                                    int shot;
                                    string shots;
                                    cout<<"How many times do you want to slice these fools?"<<endl;
                                    cin>>shots;
                                    shot=stoi(shots);
                                    if(shot>numZombies)
                                    {
                                        cout<<"You dont need to swing that many times"<<endl;
                                    }
                                    if(shot<=numZombies)
                                    {
                                        cout<<"You used the Bottle "<<shot<<" times!"<<endl;
                                        numZombies-=shot;
                                        u.kills+=shot;
                                        if(shot>5)
                                        {
                                            u.health-=10;
                                            cout<<"You accidentally sliced yourself. Health; "<<u.health<<"%"<<endl;
                                            Dead();
                                        }
                                        cout<<"There are "<<numZombies<<" zombies left"<<endl;
                                        u.items[j].uses-=shot;
                                    }

                                }
                                else if(u.items[j].name=="Shattered Bottle"&&u.items[j].uses<=0)
                                {
                                    cout<<"Cant use Shattered Bottle"<<endl;
                                }
                            }
                        }
                        else if(validEntry==false)
                        {
                            cout<<"What? Thats not a weapon."<<endl;
                        }
                        u.currentArea->userVisit=true;
                    }
                }
            }
            if(cmnd=="r")
            {
                u.health-=10;
                cout<<"You have fled like a coward"<<endl;
                cout<<"You have ran for so long that you are exhausted, Health="<<u.health<<"%"<<endl;
                if(u.party>3)
                {
                    cout<<"You left one of your party members behind, lord have mercy..."<<endl;
                    u.party-=1;
                    cout<<"Only "<<u.party<<" group members left"<<endl;
                }
                Dead();
                cout<<"You are back in the mall"<<endl;
                u.currentArea=findV("Mall");
                return;
            }
            if(cmnd=="h")
            {
                cout<<"You are hiding in the "<<u.currentArea->name<<"... "<<endl<<endl;
                cout<<"The smell of money hangs in the air"<<endl<<endl;
                Dead();
                return;
            }
        }
    }

    if (validArea==false)
    {
        cout<<"No zombies here. SWEET!"<<endl;
    }
}
void Graph::Dead()
{
    //for when characters health reaches 0
    if(u.health<=0)
    {
        cout<<"You are dead. At least the dead don't stay dead for long these days..."<<endl;
        exit(0);
    }
}
void Graph::Victory()
{
    //for when character gets cure to campus
string vic="y";
     if(u.victory==true)
    {
        //you hav already visited campus and given cure.
        cout<<"Researcher: 'Hello again "<<u.name<<" we are working on the cure and will have it distributed within the week!"<<endl;
        cout<<"While your here I'll make sure your healed up all the way.'"<<endl;
        u.health=100;
    }
    else if (u.victory==false)
    {
        //havnt yet given cure, first time at the campus

        u.victory=true;
        cout<<"You got the cure to the researchers! Congratulations! Soon the cure will be distributed to all people ";
        cout<<"So the zombies cant infect anyone anymore. If you'd like to just stay here where its safe you can, you've ";
        cout<<"earned it. Or you can go back out and hunt the remaining zombies. The world wont stay in anarchy forever."<<endl;
        cout<<"Would you like to go explore again?(y/n)"<<endl;

        getline(cin,vic);
        if(vic=="y")
        {
            //if you choose to keep playing
            cout<<"Researcher: 'Thank you for your assistance, "<<u.name<<" your name will live on forever'"<<endl;
            cout<<"You go to the bar, seems like a good place to relax. Your health is restored.";
            cout<<"You received a sample of the cure, itll prevent you from being bitten by zombies.";
            cout<<"You have also learned how to nuke zombies, press 'n' from the 'What Do' screen to nuke em."<<endl;

            u.health=100;
            u.currentArea=findV("Bar");
        }
        if(vic=="n")
        {
            //if you choose not to, game ends
            cout<<"Resesarcher:  Thank you for your help, "<<u.name<<" you are welcome to stay with us for as long as you would like."<<endl;
            cout<<"You decided to take a nap, being a hero is hard work.  See you next time the world is ending!"<<endl;
            exit(0);
        }
        else if(vic!="n"&&vic!="y")
        {
            //if you say anything other than y or n. lol game ends
            cout<<"Huh? That wasn't a valid answer, maybe your turning into a zombie..."<<endl;
            cout<<"The researcher shot you in the head and took the cure."<<endl;
            u.health=0;
            Dead();
        }
    }
}
