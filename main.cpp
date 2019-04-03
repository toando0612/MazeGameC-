//C++ Assignment 1
//Do Quoc Toan - s3652979
#include <iostream>
#include <array>
#include <vector>
#include <type_traits>
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
    public:
    //methods actions on the attributes
        void creatingMaze(){
        //1st draw of maze
            currentLocation = {1,1};
            vector<vector<Cell>> temp_maze;
            for (auto i = 0; i < width; i++)
            {
                vector<Cell> colums;
                for (auto j = 0; j < height; j++)
                {
                    array<edge, 4> temp_edges;
                    temp_edges.at(0) = {i,j,i+1,j};
                    temp_edges.at(1) = {i+1,j,i+1,j+1};
                    temp_edges.at(2) = {i+1,j+1,i,j+1};
                    temp_edges.at(3) = {i,j+1,i,j};
                    Cell cell;
                    cell.setedge_list(temp_edges);
                    cell.setvisited(false);
                    cell.setcoord({i,j});
                    colums.push_back(cell);
                }
                temp_maze.push_back(colums);
            }
            setmaze(temp_maze);
            int x = currentLocation[0];
            int y = currentLocation[1];
            cout << "x,y = " << x <<",";
            cout << y << endl;
            //become of maze
//            if (x == 0 ){
//                if (y == 0){
//                    //top left corner
//                } else if(y == height-1){
//                    //bottom left corner
//                } else {
//                    // left edge
//                }
//            } else if (y == 0)
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
    mazeGame.creatingMaze();
    mazeGame.toCoord();





    return 0;
}