#include "maze.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>

using namespace std;

DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const
{
    cout << setw(3) << " ";
    for (int j=0; j<ncols; j++) {
        cout << setw(6) << "______";
    }
    for (int i=0; i<nrows; i++) {
        cout << endl;
        cout << setw(3) << "|";
        for (int j=0; j<ncols-1; j++) {
            int val = i*nrows+j;
            cout << setw(3) << val<<setw(3);
            if (noWalls.empty() ||
                (find(noWalls.begin(),noWalls.end(),pair<int,int>(val,val+1)) == noWalls.end() &&
                 find(noWalls.begin(),noWalls.end(),pair<int,int>(val+1,val)) == noWalls.end())
                    )
                cout << "|";
            else
                cout <<" ";
        }
        int val = i*nrows+ncols-1;
        cout << setw(3) << val<<setw(3) << "|";
        cout <<endl;
        cout << setw(3) << " ";
        for (int j=0; j<ncols; j++) {
            int val = i*nrows+j;
            if (i<nrows-1) {
                if ( noWalls.empty() ||
                     (find(noWalls.begin(), noWalls.end(), pair<int, int>(val, val + ncols)) == noWalls.end()
                      && find(noWalls.begin(), noWalls.end(), pair<int, int>(val+ncols, val)) == noWalls.end())
                        )
                    cout << setw(6) << "______";
                else
                    cout << setw(6) << " ";
            } else
                cout << setw(6) << "______";
        }

    }
    cout <<endl << endl;
}



// a implementar

Maze::Maze(int rows, int cols) {
    nrows = rows;
    ncols = cols;
    maze = DisjointSets(rows * cols);
}

vector<int> Maze::getNeighbours(int x) const {
    vector<int> res;
    if(x / nrows != 0) res.push_back(x - nrows); //se não estiver na primeira linha podemos adicionar o que está em cima
    if( x / nrows != nrows -1) res.push_back(x + nrows); //se não estiver na última linha podemos adicionar o que está em baixo
    if(x % ncols != 0) res.push_back(x - 1); //se não estiver na primeira coluna podemos adicionar o que está atrás
    if(x % ncols != ncols -1) res.push_back(x + 1);//se não estiver na última coluna podemos adicionar o que está à frente
    return res;
}

void Maze::buildRandomMaze() {
    int x, y;
    vector<int> temp; //vetor onde se adiciona os numeros que já estão relacionados com outro
    while(maze.getNumberOfSets() != 1){
        x = rand() % (nrows * ncols); // último elemento não tem vizinhos
        vector<int> ngb = getNeighbours(x);
        y = ngb[rand() % ngb.size()];
        if(find(noWalls.begin(), noWalls.end(), make_pair(x, y)) == noWalls.end() &&  find(noWalls.begin(), noWalls.end(), make_pair(y, x)) == noWalls.end() &&  (maze.find(x) != maze.find(y))) {
            noWalls.emplace_back(x, y);
            if(find(temp.begin(), temp.end(), y) == temp.end()) {
                maze.unionSets(x, y);
                temp.push_back(y);
            }
            else {
                maze.unionSets(y, x);
                temp.push_back(x);
            }
        }
    }
}

