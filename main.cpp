#include <iostream>
#include <fstream>
#include <map>
#include "Edges.h"
#include "Graph.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }
    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    ifstream infile(argv[1]);
    ofstream myfile;
    int a,b;
    int x;
    int diff = -1;
    infile>>a;
    infile>>b;
    multimap <int, Edges> diffmap;
    int vertices[b];

    for(int i=0; i<b; i++){
    vertices[i]=-1;
    }

    for(int k=0;k<a;k++) {
        for (int i = 0; i < b; i++) {
            infile >> x;
            if (k!=0) {

                    diff = vertices[i] - x;
                    vertices[i] = x;
                    if (diff < 0) {
                        diff = -diff;
                    }

                    Edges *edges = new Edges((b * (k-1)) + i, (b * (k-1)) + b + i);
                    diffmap.insert(pair<int, Edges>(diff, *edges));

            }
            vertices[i] = x;

        }
        for (int j = 0; j < b - 1; j++) {
            diff = vertices[j] - vertices[j + 1];
            if (diff < 0) {
                diff = -diff;
            }

            Edges *edges = new Edges(k * b + j, k * b + j + 1);
            diffmap.insert(pair<int, Edges>(diff, *edges));
        }
    }

    multimap <int,Edges> :: iterator itr;

    int numQueries,fromX,fromY,toX,toY;
    Graph g(a*b);
    bool quit;
    int last_;
    infile>>numQueries;
    int start[numQueries],end[numQueries];
    int gone=0;
    int div;
    int last_2;
    int diffSize;
    myfile.open (argv[2]);
    for(int i = 0;i<numQueries;i++) {
        infile >> fromX;
        infile >> fromY;
        infile >> toX;
        infile >> toY;

        start[i] = (fromX - 1) * b + fromY - 1;
        end[i] = (toX - 1) * b + toY - 1;

        itr = diffmap.begin();
        gone = 0;
        last_=-1;
        last_2 = -1;
        div = 2;
        quit = true;
        for (; quit; ++itr) {
            g.addEdge(itr->second.from, itr->second.to);
            gone++;
            if (itr->second.from == start[i] || itr->second.to == start[i]) {
                quit = false;
                last_ = itr->first;
                ++itr;
                while (last_ == itr->first) {
                    g.addEdge(itr->second.from, itr->second.to);
                    ++itr;
                    gone++;
                }
            }

        }


        diffSize = diffmap.size()-gone;
        while (g.BFS(start[i], end[i]) == false) {
            for (int i = 0; i < diffSize / div; i++) {

                g.addEdge(itr->second.from, itr->second.to);

                last_ = itr->first;
                ++itr;
            }
            if (diffSize / div != 1) {
                div = div * 2;
            }
            while (g.BFS(start[i], end[i]) == true) {
                for (int i = 0; i < diffSize / div; i++) {
                    --itr;
                    g.removeEdge(itr->second.from, itr->second.to);
                    last_2 = itr->first;

                }
                if (diffSize / div != 1) {
                    div = div * 2;
                }
            }

                if (last_ == last_2) {
                break;
            }

        }
        myfile << last_<< endl;
        g.~Graph();
    }
    myfile.close();


    return 0;
}