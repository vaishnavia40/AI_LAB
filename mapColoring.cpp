#include<iostream>
using namespace std;
#define V 4
bool graph[V][V] = {
   {0, 1, 1, 0},
   {1, 0, 1, 1},
   {1, 1, 0, 1},
   {0, 1, 1, 0},
};
bool isValid(int v,int color[], int c){   //check whether putting a color valid for v
   for (int i = 0; i < V; i++)
      if (graph[v][i] == 1 && c == color[i])
         return false;
   return true;
}
bool mColoring(int colors, int color[], int vertex){
   if (vertex == V) //when all vertices are considered
      return true;
   for (int col = 1; col <= colors; col++) {
      if (isValid(vertex,color, col)) { //check whether color col is valid or not
         color[vertex] = col;
         if (mColoring (colors, color, vertex+1) == true) //go for additional vertices
            return true;
         color[vertex] = 0;
      }
   }
   return false; //when no colors can be assigned
}
int main(){
   int colors = 3; // Number of colors
   int color[V]; //make color matrix for each vertex
   for (int i = 0; i < V; i++)
      color[i] = 0; //initially set to 0
   if (mColoring(colors, color, 0) == false) { //for vertex 0 check graph coloring
      cout << "Solution does not exist.";
   }
   cout << "Assigned Colors are: \n";
   for (int i = 0; i < V; i++)
      cout << color[i] << " ";
   return 0;
}