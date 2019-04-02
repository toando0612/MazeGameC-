//C++ Assignment 1
//Do Quoc Toan - s3652979
#include <iostream>
#include <array>
#include <vector>
using namespace std;

typedef array<int, 4> edge;


class Cell {
    private:
        bool visited;
        array<edge, 4> edge_lists;
        array<int, 2> coord;
    public://method or action on the attribubtes
        void setedge_list(array<edge, 4> new_edge_list){edge_lists = new_edge_list;}
        auto getedge_list(){return edge_lists;}
        void setvisited(bool status){visited = status;}
        void setcoord(array<int, 2> newCoord){coord = newCoord;}



};
class MazeGame {
    private:
        vector<vector<Cell>> maze;
        array<int, 2> currentLocation;
        int height;
        int width;
    public:
    //methods actions on the attributes
        void creatingMaze(){
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