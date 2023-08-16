
//****** Kalyan Chowdhury ***//
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>    //for std::bind     
#include<math.h>        
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>
// 306- goal and dest
using namespace std;
using namespace sf;
#define num 15    //number of cells in a row
//--------dijkstra--------
vector<pair<int,int>> pathD;        //Shortest pathD
float dkLength,aLength;
int flagD=0,flagA=0;
bool sptSet[num][num];      //explored cells
void findmin(float dist[num][num],int& min_x,int& min_y){
    float mini=FLT_MAX;
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            if(sptSet[i][j]==false && dist[i][j]<mini){
                mini=dist[i][j];
                min_x=i;
                min_y=j;
            }
}
void findpath(pair<int,int> previous[num][num],float dist[num][num],int dest_x,int dest_y,int source_x,int source_y){
    //cout<<"\nLength of Dijkstra path is: "<<dist[dest_x][dest_y]<<endl;
    dkLength = dist[dest_x][dest_y];
    while(previous[dest_x][dest_y].first!=source_x || previous[dest_x][dest_y].second!=source_y){  // both simultaneously equal to source coordinates
        sf::sleep(milliseconds(100));        //delay shortest pathD
       // cout<<"go to ->\n("<<previous[dest_x][dest_y].first<<","<<previous[dest_x][dest_y].second<<") ";
        pathD.push_back(make_pair(previous[dest_x][dest_y].first,previous[dest_x][dest_y].second));
        int save_x=dest_x,save_y=dest_y;
        dest_x=previous[save_x][save_y].first;
        dest_y=previous[save_x][save_y].second;
    }
    
}
void dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[num][num]){
    pair<int,int> previous[num][num];
    float dist[num][num];
    bool destFound=false;
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            dist[i][j]=FLT_MAX;
    dist[source_x][source_y]=0.0;
    int found=0;
    for(int i=0;i<num && found==0;i++)
        for(int j=0;j<num && found==0;j++){
            int min_x=1,min_y=1;
            findmin(dist,min_x,min_y);
            sptSet[min_x][min_y]=true;
            if(sptSet[dest_x][dest_y]==true){
                found=1;
                destFound=true;
                break;
            }
            sf::sleep(milliseconds(25));        //delay exploration frame
            //north
            if(grid[min_x-1][min_y]==1 && sptSet[min_x-1][min_y]==false && dist[min_x-1][min_y]>dist[min_x][min_y]+1.0){
                dist[min_x-1][min_y]=dist[min_x][min_y]+1.0;
                previous[min_x-1][min_y]=make_pair(min_x,min_y);
            }
            //south
            if(grid[min_x+1][min_y]==1 && sptSet[min_x+1][min_y]==false && dist[min_x+1][min_y]>dist[min_x][min_y]+1.0){
                dist[min_x+1][min_y]=dist[min_x][min_y]+1.0;
                previous[min_x+1][min_y]=make_pair(min_x,min_y);
            }
            //west
            if(grid[min_x][min_y-1]==1 && sptSet[min_x][min_y-1]==false && dist[min_x][min_y-1]>dist[min_x][min_y]+1.0){
                dist[min_x][min_y-1]=dist[min_x][min_y]+1.0;
                previous[min_x][min_y-1]=make_pair(min_x,min_y);
            }
            //east:i,j+1
            if(grid[min_x][min_y+1]==1 && sptSet[min_x][min_y+1]==false && dist[min_x][min_y+1]>dist[min_x][min_y]+1.0){
                dist[min_x][min_y+1]=dist[min_x][min_y]+1.0;
                previous[min_x][min_y+1]=make_pair(min_x,min_y);
            }
            //north-east:i-1,j+1
            if(grid[min_x-1][min_y+1]==1 && sptSet[min_x-1][min_y+1]==false &&
                dist[min_x-1][min_y+1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x-1][min_y]==0 && grid[min_x][min_y+1]==0)){
                dist[min_x-1][min_y+1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x-1][min_y+1]=make_pair(min_x,min_y);
            }
            //south-east:i+1,j+1
            if(grid[min_x+1][min_y+1]==1 && sptSet[min_x+1][min_y+1]==false &&
                dist[min_x+1][min_y+1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x+1][min_y]==0 && grid[min_x][min_y+1]==0)){
                dist[min_x+1][min_y+1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x+1][min_y+1]=make_pair(min_x,min_y);
            }
            //south-west:i+1,j-1
            if(grid[min_x+1][min_y-1]==1 && sptSet[min_x+1][min_y-1]==false &&
                dist[min_x+1][min_y-1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x+1][min_y]==0 && grid[min_x][min_y-1]==0)){
                dist[min_x+1][min_y-1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x+1][min_y-1]=make_pair(min_x,min_y);
            }
            //north-west:i-1,j-1
            if(grid[min_x-1][min_y-1]==1 && sptSet[min_x-1][min_y-1]==false &&
                dist[min_x-1][min_y-1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x-1][min_y]==0 && grid[min_x][min_y-1]==0)){
                dist[min_x-1][min_y-1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x-1][min_y-1]=make_pair(min_x,min_y);
            }
        }
        if(destFound==false)
        {
        cout<<"Destination cell not found.\n";
        flagD=1;
        }
    else
    findpath(previous,dist,dest_x,dest_y,source_x,source_y);
}

//--------Astar--------
typedef pair<int,int> Pair;
typedef pair<float,pair<int,int>> Ppair;
bool closedList[num][num];
vector<Pair> pathA;
struct cell{
    int parent_x,parent_y;
    float f,g,h;
    cell() : f(FLT_MAX),g(FLT_MAX),h(FLT_MAX),parent_x(-1),parent_y(-1) {};
};
bool isDestination(int row,int col,Pair dest){
    if(row==dest.first && col==dest.second)
        return true;
    else
        return false;
}
float calculateHvalue(int row,int col,Pair dest){
    int dx=abs(dest.first-row);
    int dy=abs(dest.second-col);
    return abs(dx-dy)+sqrt(2)*min(dx,dy);       //Diagonal D=1,D2=sqrt(2)
}
void tracePath(Pair source,Pair dest,cell cellDetails[][num]){
    int i=cellDetails[dest.first][dest.second].parent_x,j=cellDetails[dest.first][dest.second].parent_y;
    while(!(i==source.first && j==source.second)){
        sf::sleep(milliseconds(100));        //delay shortest path
       // cout<<i<<","<<j<<" to -> \n";
        pathA.push_back(make_pair(i,j));
        //pathSum=pathSum+cellDetails[i][j].g;
        int temp_i=i;
        int temp_j=j;
        i=cellDetails[temp_i][temp_j].parent_x;     //Solved substitution bug
        j=cellDetails[temp_i][temp_j].parent_y;
    }
   // cout<<"\nLength of A* path(g) is: "<<cellDetails[dest.first][dest.second].g<<endl;
    aLength= cellDetails[dest.first][dest.second].g; 
}
void Astar(Pair source,Pair dest,int grid[][num]){
    set<Ppair> openList;
    cell cellDetails[num][num];
    int i= source.first,j=source.second;
    cellDetails[i][j].f=0.0;
    cellDetails[i][j].g=0.0;
    cellDetails[i][j].h=0.0;
    cellDetails[i][j].parent_x=i;
    cellDetails[i][j].parent_y=j;
    openList.insert(make_pair(0.0,make_pair(i,j)));
    bool destFound=false;
    while(!openList.empty()){
        Ppair p=*openList.begin();
        openList.erase(openList.begin());
        int i=p.second.first,j=p.second.second;
        closedList[i][j]=true;
        sf::sleep(milliseconds(25));        //delay exploration
        if(isDestination(i,j,dest)==true){
            cout<<"Destination Found\n";
            destFound=true;
            break;      //out of while loop
        }
        // North:i-1,j
        if(grid[i-1][j]==1 && closedList[i-1][j]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i-1,j,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i-1][j].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i-1][j]=successor;
                openList.insert(make_pair(successor.f,make_pair(i-1,j)));
            }
        }
        // East:i,j+1
        if(grid[i][j+1]==1 && closedList[i][j+1]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i,j+1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i][j+1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i][j+1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i,j+1)));
            }
        }
        // South:i+1,j
        if(grid[i+1][j]==1 && closedList[i+1][j]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i+1,j,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i+1][j].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i+1][j]=successor;
                openList.insert(make_pair(successor.f,make_pair(i+1,j)));
            }
        }
        // West:i,j-1
        if(grid[i][j-1]==1 && closedList[i][j-1]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i,j-1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i][j-1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i][j-1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i,j-1)));
            }
        }
        // North-East:i-1,j+1
        if(grid[i-1][j+1]==1 && closedList[i-1][j+1]==false && !(grid[i-1][j]==0 && grid[i][j+1]==0)){      //not simultaneously blocked
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i-1,j+1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i-1][j+1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i-1][j+1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i-1,j+1)));
            }
        }
        // South-East:i+1,j+1
        if(grid[i+1][j+1]==1 && closedList[i+1][j+1]==false && !(grid[i+1][j]==0 && grid[i][j+1]==0)){
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i+1,j+1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i+1][j+1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i+1][j+1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i+1,j+1)));
            }
        }
        // South-West:i+1,j-1
        if(grid[i+1][j-1]==1 && closedList[i+1][j-1]==false && !(grid[i+1][j]==0 && grid[i][j-1]==0)){
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i+1,j-1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i+1][j-1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i+1][j-1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i+1,j-1)));
            }
        }
        // North-West:i-1,j-1
        if(grid[i-1][j-1]==1 && closedList[i-1][j-1]==false && !(grid[i-1][j]==0 && grid[i][j-1]==0)){
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i-1,j-1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i-1][j-1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i-1][j-1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i-1,j-1)));
            }
        }

    }
    if(destFound==false)
        {
        cout<<"Destination cell not found.\n";
        flagA=1;
        }
    else
        tracePath(source,dest,cellDetails);
}
//--------main()--------
int main(){
    int filled[num][num];       //whether cell is colored
    int grid[15][15];       //map with obstacle
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++){
            if(i==0||i==14||j==0||j==14)        //walls ->'0'
                grid[i][j]=0;
            else
                grid[i][j]=1;
        }
     for(int i=0;i<num;i++)
        for(int j=0;j<num;j++){
            sptSet[i][j]=false;     //dijkstra all unexplored
            filled[i][j]=0;     //all uncolored
        }
    int source_x=3,source_y=3,dest_x=11,dest_y=12;      //Origin->Goal
    Thread threadD(std::bind(&dijkstra,source_x,source_y,dest_x,dest_y,grid));
    Thread threadA(std::bind(&Astar,make_pair(source_x,source_y),make_pair(dest_x,dest_y),grid));

    RenderWindow window(VideoMode(700,600),"PPR PROJECT");
    
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text1("Path1-D",font,15);
    text1.setStyle(sf::Text::Bold );
    sf::Text lengthD(" ",font,44);
    lengthD.setStyle(sf::Text::Bold );

    sf::Text text2("Path2-A",font,15);
    text2.setStyle(sf::Text::Bold );
    sf::Text lengthA(" ",font,44);
    lengthA.setStyle(sf::Text::Bold );

    sf::Text lengthDD("Distance-1->",font,15);
    lengthDD.setStyle(sf::Text::Bold );

    sf::Text lengthAD("Distance-2->",font,15);
    lengthAD.setStyle(sf::Text::Bold );

    RectangleShape buttonStartD(Vector2f(75,25));       //button dijkstra
    buttonStartD.setFillColor(Color::Green);
    buttonStartD.setOutlineThickness(4);
    buttonStartD.setOutlineColor(Color::White);

    RectangleShape buttonStartA(Vector2f(75,25));       //button Astar
    buttonStartA.setFillColor(Color::Red);
    buttonStartD.setOutlineThickness(4);
    buttonStartD.setOutlineColor(Color::White);

    RectangleShape displayD(Vector2f(75,55));       //Dijkstra display
    displayD.setFillColor(Color::White);

    RectangleShape displayA(Vector2f(75,25));       //Astar display
    displayA.setFillColor(Color::White);

    RectangleShape rectangle(Vector2f(30,30));      //default box :White
    rectangle.setFillColor(Color::White);

    

    RectangleShape brectangle(Vector2f(30,30));     //Black box
    brectangle.setFillColor(Color::Black);

    RectangleShape grectangle(Vector2f(30,30));     //Green
    grectangle.setFillColor(Color::Green);
    grectangle.setOutlineThickness(2);
    grectangle.setOutlineColor(Color::Cyan);

    RectangleShape mrectangle(Vector2f(30,30));     //Yellow
    mrectangle.setFillColor(Color::Yellow);
    mrectangle.setOutlineThickness(2);
    mrectangle.setOutlineColor(Color::Red);

    RectangleShape blueRectangle(Vector2f(30,30));
    blueRectangle.setFillColor(Color::Blue);
    blueRectangle.setOutlineThickness(2);
    blueRectangle.setOutlineColor(Color::Red);

    RectangleShape rrectangle(Vector2f(30,30));
    rrectangle.setFillColor(Color::Red);
    rrectangle.setOutlineThickness(2);
    rrectangle.setOutlineColor(Color::Green);

    RectangleShape yrectangle(Vector2f(30,30));
    yrectangle.setFillColor(Color(255,153,153));
    yrectangle.setOutlineThickness(2);
    yrectangle.setOutlineColor(Color::White);


    // Display
    
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            
               window.close();
            
            if(event.type==Event::KeyPressed&& event.key.code==Keyboard::Space)
                window.close();
            if(event.type==Event::MouseButtonPressed&&event.mouseButton.button==Mouse::Left){
                int X=event.mouseButton.x;
                int Y=event.mouseButton.y;
                //cout<<X<<" ? "<<Y<<endl;
                int row=Y/40;       //Reversed notion of row & column
                int col=X/40;
                if(grid[row][col]==0&&row<15&&col<15)
                    grid[row][col]=1;
                else if(row<15&&col<15)
                    grid[row][col]=0;
               // cout<<"Cell "<<row<<" , "<<col<<" state is: "<<grid[row][col]<<endl;
                if(X>600&&X<675&&Y>0&&Y<25){
                    threadD.launch();
                   
                }   
                if(X>600&&X<675&&Y>300&&Y<350){
                    threadA.launch();
                }
            }
            
            
        }
        
        window.clear();
        buttonStartD.setPosition(600,0);
        window.draw(buttonStartD);      //Dijkstra launch

        buttonStartA.setPosition(600,300);
        window.draw(buttonStartA);    // A* launch

        text1.setPosition(600,0);
        window.draw(text1); 


        text2.setPosition(600,300);
        window.draw(text2); 

        lengthDD.setPosition(600,75);
        window.draw(lengthDD); 

        lengthAD.setPosition(600,400);
        window.draw(lengthAD); 
        
        stringstream ss1;
        
        if(flagD==1)
        {
        dkLength=-1;
        ss1<<dkLength;  
        lengthD.setString(ss1.str());
        lengthD.setPosition(610,100);
        window.draw(lengthD); 
     
        }
        else
        {
        ss1<<dkLength;   
        lengthD.setString(ss1.str());
        lengthD.setPosition(610,100);
        window.draw(lengthD);
        }
    
        stringstream ss2;
          
        if(flagA==1)
        {
        aLength=-1;
        ss2<<aLength;
        lengthA.setString(ss2.str());
        lengthA.setPosition(610,450);
        window.draw(lengthA);
  
        }
        else
        {
        ss2<<aLength;
        lengthA.setString(ss2.str());
        lengthA.setPosition(610,450);
        window.draw(lengthA); 
        }
        
        
   
         if(!pathA.empty()){
            for(int i=0;i<pathA.size();i++){
                mrectangle.setPosition(pathA[i].second*40,pathA[i].first*40);     //Reversed notion of row & column
                window.draw(mrectangle);        //final pathA
                filled[pathA[i].first][pathA[i].second]=1;
            }
        }

        if(!pathD.empty()){
            for(int i=0;i<pathD.size();i++){
                grectangle.setPosition(pathD[i].second*40,pathD[i].first*40);     //Reversed notion of row & column
                window.draw(grectangle);        //final pathD
                filled[pathD[i].first][pathD[i].second]=1;
            }
        }
        blueRectangle.setPosition(source_y*40,source_x*40);
        window.draw(blueRectangle);     //source
        filled[source_x][source_y]=1;
        rrectangle.setPosition(dest_y*40,dest_x*40);
        window.draw(rrectangle);        //destination
        filled[dest_x][dest_y]=1;
        for(int i=0;i<=590 ;i+=40)
            for(int j=0;j<=590;j+=40){
                if(grid[i/40][j/40]==0){
                    brectangle.setOutlineThickness(2);
                    brectangle.setOutlineColor(Color::Blue);
                    brectangle.setPosition(j,i);
                    window.draw(brectangle);        //User's obstacle
                }
                if(sptSet[i/40][j/40]==true && filled[i/40][j/40]==0){
                    yrectangle.setOutlineThickness(3);
                    yrectangle.setOutlineColor(Color::Blue);
                    yrectangle.setPosition(j,i);
                    window.draw(yrectangle);        // Explored Cells by dijkstra
                }
                if(closedList[i/40][j/40]==true && filled[i/40][j/40]==0){
                    yrectangle.setOutlineThickness(3);
                    yrectangle.setOutlineColor(Color::Red);
                    yrectangle.setPosition(j,i);
                    window.draw(yrectangle);        // Explored  Cells by A*
                }
                if(grid[i/40][j/40]==1 && sptSet[i/40][j/40]==false && closedList[i/40][j/40]==false && filled[i/40][j/40]==0){     //not in dijkstra & A*
                    rectangle.setOutlineThickness(1);
                    rectangle.setOutlineColor(Color::Red);
                    rectangle.setPosition(j,i);
                    window.draw(rectangle);     //default white cells
                }
            }

        window.display();
    }

    return 0;
}
