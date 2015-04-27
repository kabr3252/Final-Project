#include <iostream>
#include "Zombies.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void displayMenu();
void readFile(char * fileName);
void shortestDist();
void shortestPath();
void greeting();
Graph in;
string startName, inName;
string endName, inEnd;
string username, currentCity;
int party = 1;
bool idIn, idx= false;
int main(int argc, char*argv[])
{
    readFile(argv[1]);
    in.findDistricts();
    string title;
    int input;
    bool quit = false;
    greeting();
    while(quit != true)
    {

        displayMenu();
        cin >> input;
        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {

            case 1:
              //displays areas
                in.displayEdges();
                break;

            case 2:
                //looks around area
                in.Look();
                break;

            case 3:
                //travels in car
                in.travelCar();
                //in.Dead();

                break;

            case 4:
                //travels on foot
                in.onFoot();

                break;
            case 5:
                //displays user stats
                in.displayStats();
                break;
            // Quit
            case 6:
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            default:
                //cout << "Invalid Input" << endl;
                //cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }
    return 0;
}

void greeting()
{
    cout<<"Woah, you look pretty banged up. What is your name kid?"<<endl;
    getline(cin,username);
    cout<<"The name's Jon Gi Baptiste, but you can call me John Guy. It's damn good to meet ya,"<<endl;
    cout<<" How many people were with ya before ya passed out?"<<endl;
    cout<<"(1-2=hard; 3-4=medium; 5+=easy)"<<endl;
    string holder;
    getline(cin, holder);
    party=stoi(holder);
    cout<<"Well then, "<<username<<" I'm not sure what yer doing passed out in a church, "<<endl;
    cout<<"and judgin by the look on your face, you don't know either. but if you're one of "<<endl;
    cout<<"them religious types, pray to yer god. Zombies are everywhere, I ain't seen "<<endl;
    cout<<"another livin person in 2 weeks. I suggest you get a weapon "<<endl;
    cout<<"or you wont stay livin for too long. Here they come! I have to go, "<<endl;
    if(party>1){
    cout<<"I hope your friends find you soon ";
    }
    cout<<"Be careful, Goodluck."<<endl<<endl;
    cout<<"John Guy gave you some advice and left. He smelled like whiskey. (Say Goodbye)"<<endl;
    getline(cin, holder);

    in.setUser(username,party);
    in.createItems();
}
void displayMenu()
{
    cout << "=======What Do======" << endl;
    cout << "1. Areas" << endl;
    cout << "2. Look Around" << endl;
    cout << "3. Travel by Car" << endl;
    cout << "4. Travel on Foot" << endl;
    cout << "5. Inventory/Stats" << endl;
    cout << "6. Quit" << endl;
    return;
}

void readFile(char * fileName)
{
    ifstream in_stream;
    //cout << fileName <<"****FILENAME******"<< endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }
    string name, first, next, line, num, second;

    while (!in_stream.eof())
    {
    getline(in_stream, first, ',');
        {
            if(first=="places")
            {
               // cout<<first<<"FIRST***********"<<endl;
                for(int i=0;i<15;i++)
                {
                    if(i==14)
                    {
                        getline(in_stream,name);
                 //       cout<<name<<"NAME*!*!*!*!*!*!*!*!"<<endl;
                    }
                    else
                    {
                    getline(in_stream, name, ',');
                   // cout<<name<<"NAME***************"<<endl;
                    }
                in.addVertex(name);
                }
            }
            else
            {
                getline(in_stream, next);
                if(first!="")
                {
                    //cout<<"Add Edge Needed  "<<first<<endl;
                    //cout<<"edges "<<next<<endl;
                    istringstream instring(next);
                    for(int x=0; x<15; x++)
                    {
                        getline(instring, num, ',');
                        int distance = stoi(num);
                        second=in.findName(x);
                        in.addEdge(first, second, distance);
                    }
                }
            }
        }
    }
}
