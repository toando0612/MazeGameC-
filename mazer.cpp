//C++ Assignment 1
//Do Quoc Toan - s3652979
#include <iostream>
#include <array>
#include <vector>
#include <type_traits>
#include <cstdlib>
#include <fstream>
#include<time.h>
#include <stdexcept>

using namespace std;

typedef array<int, 4> edge;
const string GENERATE = "--g";
const string SAVE_BIN = "--sb";
const string SAVE_SVG = "--sv";

unsigned seed;
unsigned width;
unsigned height;
string current = "";
string nextseg = "";
//out of range
int at(int index) {
    if(index < 1 || index >= 101)
        throw out_of_range("1233333");
}
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
        bool killed;
    public://method or action on the attribubtes
        void setedge_list(array<edge, 4> new_edge_list){edge_lists = new_edge_list;}
        void setvisited(bool status){visited = status;}
        void setkilled(bool status){killed = status;}
        void setcoord(array<int, 2> newCoord){coord = newCoord;}
        array<edge, 4> getedge_list(){return edge_lists;}
        bool getvisited(){return visited;}
        bool getkilled(){return killed;}
        array<int, 2> getcoord(){return coord;}


};
class MazeGame {
    private:
        vector <vector<Cell> > maze;
        array<int, 2> currentLocation;
        vector<int> neighbours;
        int height;
        int width;
        int cells;
    public:
    //methods actions on the attributes
        void constructor(int h, int w ){setheight(h);setwidth(w);}
        void setmaze(vector<vector<Cell> > newMaze){maze = newMaze;}
        vector<vector<Cell> > getmaze(){return maze;}
        void setheight(int h){height = h;}
        void setwidth(int w){width = w;}
        int getheight(){return height;}
        int getwidth(){return width;}
        int getcells(){return cells;}
        int creatingMaze(int seed){
            srand(seed);
        //1st draw of maze
            cells = 1;
            currentLocation[0] = 0;         //set starting point to draw at (0,0)
            currentLocation[1] = 0;
            vector<vector<Cell> > temp_maze;
            for (auto i = 0; i < width; i++)
            {
                vector<Cell> colums;
                for (auto j = 0; j < height; j++)
                {
                    array< array<int, 4> , 4> temp_edges;
                    //
                    temp_edges[0][0] = i+1;     //
                    temp_edges[0][1] = j;
                    temp_edges[0][2] = i+1;
                    temp_edges[0][3] = j+1;
                    //
                    temp_edges[1][0] = i+1;
                    temp_edges[1][1] = j+1;
                    temp_edges[1][2] = i;
                    temp_edges[1][3] = j+1;
                    //
                    temp_edges[2][0] = i;
                    temp_edges[2][1] = j+1;
                    temp_edges[2][2] = i;
                    temp_edges[2][3] = j;
                    //
                    temp_edges[3][0] = i;
                    temp_edges[3][1] = j;
                    temp_edges[3][2] = i+1;
                    temp_edges[3][3] = j;


                    Cell cell;
                    if (i==0 && j == 0){
                        cell.setedge_list(temp_edges);
                        cell.setvisited(true);
                        cell.setkilled(false);
                        array<int, 2> temp_arr;
                        temp_arr[0] = i;
                        temp_arr[1] = j;
                        cell.setcoord(temp_arr);
                    }else{
                        cell.setedge_list(temp_edges);
                        cell.setvisited(false);
                        cell.setkilled(false);
                        array<int, 2> temp_arr;
                        temp_arr[0] = i;
                        temp_arr[1] = j;
                        cell.setcoord(temp_arr);
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
                    rand();
                    int ran = rand() % neighbours.size();
                    int move = neighbours[ran];
                    neighbours.clear();
                    if (move == 0){ //go to right
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x+1][y].getedge_list();
                        temp_edges1.at(0)[2] = temp_edges1.at(0)[0];
                        temp_edges1.at(0)[3] = temp_edges1.at(0)[1];
                        temp_edges2[2][2] = temp_edges2[2][0];
                        temp_edges2[2][3] = temp_edges2[2][1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x+1][y].setedge_list(temp_edges2);
                        currentLocation[0] = x+1;
                        currentLocation[1] = y;
                        maze[x+1][y].setvisited(true);
                        maze[x+1][y].setkilled(true);

                        cells++;
                    }else if (move == 1){ //go to bottom
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x][y+1].getedge_list();
                        temp_edges1.at(1)[2] = temp_edges1.at(1)[0];
                        temp_edges1.at(1)[3] = temp_edges1.at(1)[1];
                        temp_edges2.at(3)[2] = temp_edges2.at(3)[0];
                        temp_edges2.at(3)[3] = temp_edges2.at(3)[1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x][y+1].setedge_list(temp_edges2);
                        currentLocation[0] = x;
                        currentLocation[1] = y+1;
                        maze[x][y+1].setvisited(true);
                        maze[x][y+1].setkilled(true);

                        cells++;
                    }else if (move == 2){ //go to left
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x-1][y].getedge_list();
                        temp_edges1.at(2)[2] = temp_edges1.at(2)[0];
                        temp_edges1.at(2)[3] = temp_edges1.at(2)[1];
                        temp_edges2.at(0)[2] = temp_edges2.at(0)[0];
                        temp_edges2.at(0)[3] = temp_edges2.at(0)[1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x-1][y].setedge_list(temp_edges2);
                        currentLocation[0] = x-1;
                        currentLocation[1] = y;
                        maze[x-1][y].setvisited(true);
                        maze[x-1][y].setkilled(true);

                        cells++;
                    }else if (move == 3){ //go to top
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x][y-1].getedge_list();
                        temp_edges1.at(3)[2] = temp_edges1.at(3)[0];
                        temp_edges1.at(3)[3] = temp_edges1.at(3)[1];
                        temp_edges2.at(1)[2] = temp_edges2.at(1)[0];
                        temp_edges2.at(1)[3] = temp_edges2.at(1)[1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x][y-1].setedge_list(temp_edges2);
                        currentLocation[0] = x;
                        currentLocation[1] = y-1;
                        maze[x][y-1].setvisited(true);
                        maze[x][y-1].setkilled(true);
                        cells++;
                    } else{
                        cout <<"error path!" <<endl;
                    }
                }else if(!maze[x][y].getkilled()){
                    if (inRange(0, width-1, x+1) && inRange(0, height -1, y)){ //check east neighbor
                        neighbours.push_back(0);
                    }
                    if (inRange(0, width-1, x) && inRange(0, height -1, y + 1)){//check south neighbor
                        neighbours.push_back(1);
                    }
                    if (inRange(0, width-1, x-1) && inRange(0, height -1, y)){//check west neighbor
                        neighbours.push_back(2);
                    }
                    if (inRange(0, width-1, x) && inRange(0, height -1, y - 1)){//check north  neighbor
                        neighbours.push_back(3);
                    }
                    srand(clock());
                    int ran = rand() % neighbours.size();
                    int move = neighbours[ran];
                    neighbours.clear();
                    if (move == 0){ //go to right
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x+1][y].getedge_list();
                        temp_edges1.at(0)[2] = temp_edges1.at(0)[0];
                        temp_edges1.at(0)[3] = temp_edges1.at(0)[1];
                        temp_edges2[2][2] = temp_edges2[2][0];
                        temp_edges2[2][3] = temp_edges2[2][1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x+1][y].setedge_list(temp_edges2);
                    }else if (move == 1){ //go to bottom
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x][y+1].getedge_list();
                        temp_edges1.at(1)[2] = temp_edges1.at(1)[0];
                        temp_edges1.at(1)[3] = temp_edges1.at(1)[1];
                        temp_edges2.at(3)[2] = temp_edges2.at(3)[0];
                        temp_edges2.at(3)[3] = temp_edges2.at(3)[1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x][y+1].setedge_list(temp_edges2);
                    }else if (move == 2){ //go to left
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x-1][y].getedge_list();
                        temp_edges1.at(2)[2] = temp_edges1.at(2)[0];
                        temp_edges1.at(2)[3] = temp_edges1.at(2)[1];
                        temp_edges2.at(0)[2] = temp_edges2.at(0)[0];
                        temp_edges2.at(0)[3] = temp_edges2.at(0)[1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x-1][y].setedge_list(temp_edges2);
                    }else if (move == 3){ //go to top
                        array<edge, 4> temp_edges1 = maze[x][y].getedge_list();
                        array<edge, 4> temp_edges2 = maze[x][y-1].getedge_list();
                        temp_edges1.at(3)[2] = temp_edges1.at(3)[0];
                        temp_edges1.at(3)[3] = temp_edges1.at(3)[1];
                        temp_edges2.at(1)[2] = temp_edges2.at(1)[0];
                        temp_edges2.at(1)[3] = temp_edges2.at(1)[1];
                        maze[x][y].setedge_list(temp_edges1);
                        maze[x][y].setkilled(true);
                        maze[x][y-1].setedge_list(temp_edges2);
                    } else{
                        cout <<"error path!" <<endl;
                    }
                } else if(cells == height*width) {
                        cout << "Your seed is: " << seed << endl;
                        return 0;
                        }else{
                            int y_loop = 0;
                            bool condition = true;
                            while (y_loop < height && condition){
                                for (int x_loop = 0; x_loop < width; x_loop++) {
                                    if(!maze[x_loop][y_loop].getvisited()){
                                        currentLocation[0] = x_loop;
                                        currentLocation[1] = y_loop;
                                        maze[x_loop][y_loop].setvisited(true);
                                        cells++;
                                        condition = false;
                                        break;
                                    }
                                }
                                y_loop++;
                            }
                        }
            }
        }
};
// Generation of the two segments
void genSvg(MazeGame maze, string filename) {
    ofstream svgFile(filename, ofstream::out);
    svgFile << "<svg"<< " viewBox="<< "\"0 0 100 100\""<< " width" << "=" <<"\"500\""<<" height=\"" << 500 << "\""
         << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svgFile << "<rect width =" <<"\'100\' " << "height=\'" << "100" << "\' " << "style=\'" << "fill: black\' " << "/>" << endl;
    for (int i = 0; i < maze.getwidth(); ++i) {
        for (int j = 0; j < maze.getheight(); ++j) {
            for (int k = 0; k < 4; ++k) {
                int x1 =  maze.getmaze()[i][j].getedge_list()[k][0];
                int y1 =  maze.getmaze()[i][j].getedge_list()[k][1];
                int x2 =  maze.getmaze()[i][j].getedge_list()[k][2];
                int y2 =  maze.getmaze()[i][j].getedge_list()[k][3];
                svgFile << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.4\'" << " x1=\'" << x1 << "\' y1=\'" << y1
                     << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
            }
        }
    }
    svgFile << "</svg>" << endl;
    svgFile.close();
}
void genBin(MazeGame mazeGame, string filename){
    std::fstream output(filename,std::fstream::out | std::fstream::binary | std::fstream::trunc);
//     Write headers
    const int cells = mazeGame.getcells();
    const int height = mazeGame.getheight();
    const int width = mazeGame.getwidth();
    output.write((char*)&width, sizeof(width));
    output.write((char*)&height, sizeof(height));
    output.write((char*)&cells, sizeof(cells));

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int x1 =  mazeGame.getmaze()[i][j].getcoord()[0];
            int y1 =  mazeGame.getmaze()[i][j].getcoord()[1];
            int x2 =  mazeGame.getmaze()[i][j].getcoord()[2];
            int y2 =  mazeGame.getmaze()[i][j].getcoord()[3];
            /* x1 */
            output.write((char*)&x1, sizeof(x1));
            /* y1 */
            output.write((char*)&y1, sizeof(y1));
            /* x2 */
            output.write((char*)&x2, sizeof(x2));
            /* y2 */
            output.write((char*)&y2, sizeof(y2));
        }
    }
    output.close();
};
void input(int height, int width){
    cout << "./maze";


}
int main(int argc, char* argv[]) {
//    cout << "argc:" << argc << endl;
    if (argc <= 1){
        cout << "./mazer --lb filename.maze --sv filename.svg # load binary file and save svg file\n"
                "./mazer --g seed width height --sb filename.maze # generate with seed value, save binary file\n"
                "./mazer --g seed width height --sv filename.svg # generate with seed value, save svg file\n"
                "./mazer --g seed width height --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg\n";
        return 0;
    }
    try {
        for (int i = 1; i < argc; ++i) {
            nextseg = argv [i+1];
            if (argc == 7 ){ //have seed
                //collect seed
                try {
                    seed = stol(argv [i+1]);
                }catch (const invalid_argument){
                    cout << "Seed must be a number" <<endl;
                    return 1;
                }catch (const out_of_range) {
                    cout << "Seed must be lower than: " << UID_MAX << endl;
                    return 1;
                }

                //collect height
                try {
                    width = stol(argv [i+2]);
                    height = stol(argv [i+3]);

                }catch (const invalid_argument &e){
                    cout << "Height and width must be numbers" <<endl;
                    at(width);
                    at(height);
                    e.what();
                }catch (int n) {
                    cout << n << "out of range" << endl;
                    return 1;
                }
                if (argv[i+4] == SAVE_SVG){
                    string filename = argv[i+5];
                    MazeGame mazeGame;
                    mazeGame.constructor(height,width);
                    cout << mazeGame.creatingMaze(seed)<< endl;
                    genSvg(mazeGame, filename);
                }else if(argv[i+4] == SAVE_BIN){
                    string filename = argv[i+5];
                    MazeGame mazeGame;
                    mazeGame.constructor(height,width);
                    cout << mazeGame.creatingMaze(seed)<< endl;
                    genBin(mazeGame, filename);
                }
            } else if(argc == 6){ //no seed
                seed = 10; //default
                try {
                    width = stol(argv [i+2]);
                    height = stol(argv [i+3]);
                }catch (const invalid_argument &e){
                    cout << "Height and width must be numbers" <<endl;
                    at(width);
                    at(height);
                    e.what();
                }catch (int n) {
                    cout << n << "out of range" << endl;
                    return 1;
                }
                if (argv[i+4] == SAVE_SVG){
                    string filename = argv[i+5];
                    MazeGame mazeGame;
                    mazeGame.constructor(height,width);
                    cout << mazeGame.creatingMaze(seed)<< endl;
                    genSvg(mazeGame, filename);
                }else if(argv[i+4] == SAVE_BIN){
                    string filename = argv[i+5];
                    MazeGame mazeGame;
                    mazeGame.constructor(height,width);
                    cout << mazeGame.creatingMaze(seed)<< endl;
                    genBin(mazeGame, filename);
                }

            } else if(argv[i] == GENERATE){
                //save binary
                //save svg
//                "./mazer --g seed width height --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg\n";
                if(argc==9){
                    //have seed

                    //collect seed
                    try {
                        seed = stol(argv [i+1]);
                    }catch (const invalid_argument){
                        cout << "Seed must be a number" <<endl;
                        return 1;
                    }catch (const out_of_range) {
                        cout << "Seed must be lower than: " << UID_MAX << endl;
                        return 1;
                    }

                    //collect height
                    try {
                        width = stol(argv [i+2]);
                        height = stol(argv [i+3]);

                    }catch (const invalid_argument &e){
                        cout << "Height and width must be numbers" <<endl;
                        at(width);
                        at(height);
                        e.what();
                    }catch (int n) {
                        cout << n << "out of range" << endl;
                        return 1;
                    }
                    string filenameB = argv[i+5];
                    string filenameS = argv[i+7];
                    MazeGame mazeGame;
                    mazeGame.constructor(height,width);
                    cout << mazeGame.creatingMaze(seed)<< endl;
                    genSvg(mazeGame, filenameS);
                    genBin(mazeGame, filenameB);
                }
            }
        }
            
        }catch (char const* param)
        {
            cout << param << ".\nMissing generated maze." << endl;
        }


    return 0;
}