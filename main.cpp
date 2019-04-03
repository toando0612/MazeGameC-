//C++ Assignment 1
//Do Quoc Toan - s3652979
#include <iostream>
#include <array>
#include <vector>
#include <type_traits>
#include <cstdlib>
using namespace std;

typedef array<int, 4> edge;

// Returns true if x is in range [low..high], else false
bool inRange(unsigned low, unsigned high, unsigned x)
{
    return  ((x-low) <= (high-low));
}


class Cell {
    private:
        bool visited;
        array<edge, 4> edge_lists;
        array<int, 2> coord;
    public://method or action on the attribubtes
        void setedge_list(array<edge, 4> new_edge_list){edge_lists = new_edge_list;}
        void setvisited(bool status){visited = status;}
        void setcoord(array<int, 2> newCoord){coord = newCoord;}
        auto getedge_list(){return edge_lists;}
        bool getvisited(){return visited;}







};
class MazeGame {
    private:
        vector<vector<Cell>> maze;
        array<int, 2> currentLocation;
        vector<int> neighbours;
        int height;
        int width;
        int cells;
    public:
    //methods actions on the attributes
        int creatingMaze(){
        //1st draw of maze
            cells = 1;
            currentLocation = {0,0};
            vector<vector<Cell>> temp_maze;
            for (auto i = 0; i < width; i++)
            {
                vector<Cell> colums;
                for (auto j = 0; j < height; j++)
                {
                    array<edge, 4> temp_edges;
                    temp_edges.at(0) = {i+1,j,i+1,j+1};
                    temp_edges.at(1) = {i+1,j+1,i,j+1};
                    temp_edges.at(2) = {i,j+1,i,j};
                    temp_edges.at(3) = {i,j,i+1,j};

                    Cell cell;
                    if (i==0 && j == 0){
                        cell.setedge_list(temp_edges);
                        cell.setvisited(true);
                        cell.setcoord({i,j});
                    }else{
                        cell.setedge_list(temp_edges);
                        cell.setvisited(false);
                        cell.setcoord({i,j});
                    }
                    colums.push_back(cell);
                }
                temp_maze.push_back(colums);
            }
            setmaze(temp_maze);
            //become of maze, make the Path

            while (true){
                int x = currentLocation[0];
                int y = currentLocation[1];
                if (inRange(0, width-1, x+1) && inRange(0, height -1, y) && maze[x+1][y].getvisited() == false){ //check east neighbor
                    neighbours.push_back(0);
                }
                if (inRange(0, width-1, x) && inRange(0, height -1, y + 1) && maze[x][y+1].getvisited()== false){//check south neighbor
                    neighbours.push_back(1);
                }
                if (inRange(0, width-1, x-1) && inRange(0, height -1, y) && maze[x-1][y].getvisited()== false){//check west neighbor
                    neighbours.push_back(2);
                }
                if (inRange(0, width-1, x) && inRange(0, height -1, y - 1) && maze[x][y-1].getvisited()== false){//check north  neighbor
                    neighbours.push_back(3);
                }

                //random move
                if (!neighbours.empty()){
                    srand(time(NULL));
                    int ran = rand() % neighbours.size();
                    int move = neighbours[ran];
                    neighbours.clear();
                    if (move == 0){ //go to right
                        maze[x][y].getedge_list().at(0)[2] = maze[x][y].getedge_list().at(0)[0];
                        maze[x][y].getedge_list().at(0)[3] = maze[x][y].getedge_list().at(0)[1];
                        maze[x+1][y].getedge_list()[2][2] = maze[x+1][y].getedge_list()[2][0];
                        maze[x+1][y].getedge_list()[2][3] = maze[x+1][y].getedge_list()[2][1];
                        currentLocation[0] = x+1;
                        currentLocation[1] = y;
                        maze[x+1][y].setvisited(true);
                        cells++;
                    }else if (move == 1){ //go to bottom
                        maze[x][y].getedge_list().at(1)[2] = maze[x][y].getedge_list().at(1)[0];
                        maze[x][y].getedge_list().at(1)[3] = maze[x][y].getedge_list().at(1)[1];
                        maze[x][y+1].getedge_list().at(3)[2] = maze[x][y+1].getedge_list().at(3)[0];
                        maze[x][y+1].getedge_list().at(3)[3] = maze[x][y+1].getedge_list().at(3)[1];
                        currentLocation[0] = x;
                        currentLocation[1] = y+1;
                        maze[x][y+1].setvisited(true);
                        cells++;
                    }else if (move == 2){ //go to left
                        maze[x][y].getedge_list().at(2)[2] = maze[x][y].getedge_list().at(2)[0];
                        maze[x][y].getedge_list().at(2)[3] = maze[x][y].getedge_list().at(2)[1];
                        maze[x-1][y].getedge_list().at(0)[2] = maze[x-1][y].getedge_list().at(0)[0];
                        maze[x-1][y].getedge_list().at(0)[3] = maze[x-1][y].getedge_list().at(0)[1];
                        currentLocation[0] = x-1;
                        currentLocation[1] = y;
                        maze[x-1][y].setvisited(true);
                        cells++;
                    }else if (move == 3){ //go to top
                        maze[x][y].getedge_list().at(3)[2] = maze[x][y].getedge_list().at(3)[0];
                        maze[x][y].getedge_list().at(3)[3] = maze[x][y].getedge_list().at(3)[1];
                        maze[x][y-1].getedge_list().at(1)[2] = maze[x][y-1].getedge_list().at(1)[0];
                        maze[x][y-1].getedge_list().at(1)[3] = maze[x][y-1].getedge_list().at(1)[1];
                        currentLocation[0] = x;
                        currentLocation[1] = y-1;
                        maze[x][y-1].setvisited(true);
                        cells++;
                    } else{
                        cout <<"error path!" <<endl;
                    }
                }else if(cells==height*width) {
                    return 0;
                }else{
                    int colum = 0;
                    while (colum < height){
                        for (int i = 0; i < width; ++i) {
                            if(maze[i][colum].getvisited() == false){
                                currentLocation[0] = i;
                                currentLocation[1] = colum;
                                break;
                            }
                        }
                        colum++;
                    }
                }
            }
        }
        void toCoord(){
            for (int i = 0; i < width ; ++i) {
                for (int j = 0; j < height; ++j) {
                    int edgeN = 0;
                    array<edge, 4> edges = maze[i][j].getedge_list();
                    for (auto itEdge = edges.begin(); itEdge != edges.end(); itEdge++)
                    {
                        int coord = 0;
                        cout << "Edge: " << edgeN;
                        for (auto itCoord = edges.at(edgeN).begin(); itCoord != edges.at(edgeN).end(); itCoord++)
                        {
                            if (coord == 0){
                                cout << "(" << *itCoord << ",";
                            }else if (coord == 1 || coord == 2){
                                cout << *itCoord << ",";
                            } else if (coord == 3){
                                cout << *itCoord << ")" << endl;
                            }
                            coord++;
                        }
                        edgeN++;
                        cout << endl;
                    }
                }
            }
            for(int k = 0; k < neighbours.size() ; ++k) {
                cout << neighbours[k];
            }
            neighbours = {};

        }
        void constructor(int h, int w ){setheight(h);setwidth(w);}
        void setmaze(vector<vector<Cell>> newMaze){maze = newMaze;}
        auto getmaze(){return maze;}
        void setheight(int h){height = h;}
        void setwidth(int w){width = w;}
        int getheight(){return height;}
        int getwidth(){return width;}
};
int main() {
    int width;
    int height;
    cout << "Enter the width of the maze: " << endl;
    cin >> width;
    cout << "Enter the height of the maze: " << endl;
    cin >> height;
    MazeGame mazeGame;
    mazeGame.constructor(height,width);
    cout << "GGEZ!"<< mazeGame.creatingMaze();
//    mazeGame.toCoord();





    return 0;
}