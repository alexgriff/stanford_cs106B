/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "map.h"
#include "random.h"
using namespace std;

/* Node struct is used to associate a location with the relevant 
 * data for finding shortest path. */
struct Node
{
	Color color;
	Loc parent;
	double dist;
};


/* SHORTEST PATH Function Prototypes */
Map<Loc, Node> generateMap(int numRows, int numCols);
Vector<Loc> tracePath(Loc end, Loc start, Map<Loc, Node> worldData);
void setColor(Grid<double>& world, Loc loc, Map<Loc, Node>& worldData, Color color);

/* MAZE Function Prototypes */
void enqueueAllEdges(int numRows, int numCols, TrailblazerPQueue<Edge>& pq);
Map<Loc, int> initLocationMap(int numRows, int numCols, Vector<int> vec);
Vector<int> unionFindVector(int n);
int root(int i, Vector<int>&id);
bool find(int p, int q, Vector<int>& id);
void unite(int p, int q, Vector<int>& id, Vector<int>& size);


/*
 * This file contains work I have done
 * --------------------------------------------------------------------------
 *                          SHORTEST PATH                                 
 * --------------------------------------------------------------------------
 */

/* Function: shortestPath
 *
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited. If no path is found, this function reports an error.
 *
 */
Vector<Loc> shortestPath(Loc start, Loc end,
						 Grid<double>& world,
						 double costFn(Loc from, Loc to, Grid<double>& world),
                         double heuristicFn(Loc from, Loc to, Grid<double>& world))
{
    /* worldData maps each location in the world Grid to the needed data: 
     * (color, parent, dist). */
    Map<Loc, Node> worldData = generateMap(world.numRows(), world.numCols());
    
    /* Color starting location YELLOW. */
    setColor(world, start, worldData, YELLOW);
    
    /* Add the starting location to a Priority Queue. 
     * Use heuristicFn to calcualte priority. */
    TrailblazerPQueue<Loc> locationsQueue;
    locationsQueue.enqueue(start, heuristicFn(start, end, world));
    
    while (!locationsQueue.isEmpty()) {
        /* Dequeue the lowest-cost location */
        Loc curr = locationsQueue.dequeueMin();
        
        /* The dist field of the current location represents the distance of
         * shortest path from the starting location.  Color curr GREEN. */
        setColor(world, curr, worldData, GREEN);
        
        /* Check to see if you are at the destination location */
        if (curr == end) break;
        
        
        /* For all 8 neighboring locations, ensure that each next-location
         * is within the bounds of the world grid by confirming the worldData
         * map contains that location. */
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                Loc nextLoc = makeLoc(curr.row + i, curr.col + j);
                if(worldData.containsKey(nextLoc)) {
                    /* dist is the current distance. */
                    double dist = worldData[curr].dist;
                    /* L is the edge length or cost associated with each nextLoc. */
                    double L = costFn(curr, nextLoc, world);
                    
                    
                    /* If you have not looked at that location yet (i.e. color == GRAY):
                     * Update color to YELLOW, update dist to current dist + L,
                     * update location of parent to curr. Finally, enqueue the location
                     * with a priority determined by dist + the heuristicFn. */
                    if (worldData[nextLoc].color == GRAY) {
                        
                        setColor(world, nextLoc, worldData, YELLOW);
                        worldData[nextLoc].dist = dist + L;
                        worldData[nextLoc].parent = curr;
                        
                        locationsQueue.enqueue(nextLoc, (worldData[nextLoc].dist + heuristicFn(nextLoc, end, world)));
                    }
                    
                    /* Else, if you have looked at that location (i.e. color == YELLOW),
                     * check if it's dist field is greater than the cost associated with 
                     * approaching from current location (current dist + L).  If so, update 
                     * the dist field, update the parent location to curr and update the 
                     * priority using decreaseKey function and the heuristicFn. */
                    else if (worldData[nextLoc].color == YELLOW && worldData[nextLoc].dist > (dist + L)) {
                        
                        worldData[nextLoc].dist = dist + L;
                        worldData[nextLoc].parent = curr;
                        
                        locationsQueue.decreaseKey(nextLoc, worldData[nextLoc].dist + heuristicFn(nextLoc, end, world));
                    }
                }
            }
        }
    }
    
    /* No solution was found */
    if (locationsQueue.isEmpty()) error("No path between the two nodes exists");;
    
    /* Use tracePath to follow back parent locations from end to start. */
    return tracePath(end, start, worldData);
    
}


/* Function: generateMap
 * 
 * Generates a map where each location in the World Grid is associated
 * with a Node that stores the needed data, i.e. location of parent,
 * (useful when tracing back solution path), it's color and a dist field, 
 * which is the cost or cumulative distance from start.
 */
Map<Loc, Node> generateMap(int numRows, int numCols)
{
    Map<Loc, Node> worldData;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            /* Init color of each location to GRAY.
             * It's parent is itself and dist is 0. */
            Loc loc = makeLoc(i,j);
            Node node = {GRAY, loc, 0};
            worldData.put(loc, node);
        }
    }
    return worldData;
}


/* Function: tracePath
 *
 * Begins with the end location and works backward to start following
 * the location in each parent field. Doesn't use path.add, but always
 * path.insert at the 0 index. This allows the vector to read forward 
 * from start to finish when drawing the path.
 */
Vector<Loc> tracePath(Loc end, Loc start, Map<Loc, Node> worldData)
{
    Vector<Loc> path;
    Loc curr = end;
    /* If the parent is itself, we have reached the starting location. */
    while (worldData[curr].parent != curr) {
        path.insert(0, curr);
        curr = worldData[curr].parent;
    }
    
    /* Manually add start. */
    path.insert(0, start);
    return path;
}

/* Function: setColor
 *
 * Setting the color is a two-step process which involves updating the 
 * color field in the Node data structure as well as the graphical display.
 * Use setColor function to avoid errors.
 */
void setColor(Grid<double>& world, Loc loc, Map<Loc, Node>& worldData, Color color)
{
    worldData[loc].color = color;
    colorCell(world, loc, worldData[loc].color);
}



/*
 * --------------------------------------------------------------------------
 *                         MAZE GENERATION
 * --------------------------------------------------------------------------
 */


/* Function: createMaze
 *
 * Uses Kruskal's Algorithm to create a Minimum Spanning Tree from which a maze
 * is constructed by building walls around the branches of the tree. (Walls are
 * constructed in WorldGenerator.cpp). A spanning tree has all Nodes connected but 
 * without any cycling or loops.  This implementation uses a Union-Find Data 
 * Structure to keep track of the clusters using index positions in a vector.
 */

Set<Edge> createMaze(int numRows, int numCols)
{
    Set<Edge> spanningTree;
    
    /* "id" is the main vector in the union-find structure.
     * Each index of the vector identifies a node, the value 
     * at that index refers to the index of the parent node 
     * for the cluster it belongs to.
     *
     * "size" is an auxilliary vector that tracks the size of 
     * clusters and keeps them balanced for quicker runtimes. 
     * 
     * Initially, each node is it's own cluster. */
    int n = numRows * numCols;
    Vector<int> id = unionFindVector(n);
    Vector<int> size (n,1);
    
    /* The location-map "maps" each location in the grid to a 
     * corresponding int, allowing the vector/index based 
     * union-find strategy to be used. */
    Map<Loc, int> locMap = initLocationMap(numRows, numCols, id);
    
    /* Put all the Edges into a Priority Queue. */
    TrailblazerPQueue<Edge> pQueue;
    enqueueAllEdges(numRows, numCols, pQueue);
    
    /* Dequeue all the Edges. A minimum spanning tree always has n-1 edges. */
    while (spanningTree.size() != n-1) {
        Edge edge= pQueue.dequeueMin();
        /* Get the two endpoints of the edge. */
        Loc start = edge.start;
        Loc end = edge.end;
        
        /* Get the corresponding int values for those edges. */
        int startI = locMap[start];
        int endI = locMap[end];
        
        /* The find function returns true if the endpoints are in 
         * the same cluster and share a root.  If true, it would be
         * redundant and create loops in the maze to add that edge
         * to the tree, so ignore.
         *
         * If it returns false, add that edge to the tree, and do 
         * the back-end work of uniting the clusters.
         */
        if (!find(startI, endI, id)) {
            spanningTree.add(edge);
            unite(startI, endI, id, size);
        }
        
    }
    return spanningTree;
}

/* Function: unionFindVector
 *
 * Returns a vector of integers that is the total size of all the Nodes
 * in the maze grid.  Each int is initialized to be identical to it's
 * index position, thus is a singleton cluster.
 */
Vector<int> unionFindVector(int n)
{
    Vector<int> vec(n);
    for (int i = 0; i < n; i++)
        vec[i] = i;
    return vec;
}

/* Function: initLocationMap
 *
 * Initializes a map where every Loc {row, col} is paired to an
 * integer between 0 and n-1 (n is total number of nodes in the graph).
 * Allows easy translation between "locations" and the vector
 * representations used in this implementation.
 */
Map<Loc, int> initLocationMap(int numRows, int numCols, Vector<int> vec)
{
    Map<Loc, int> locMap;
    int vecIndex = 0;
    for(int  i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            Loc loc = makeLoc(i,j);
            locMap.put(loc, vec[vecIndex]);
            vecIndex++;
        }
    }
    
    return locMap;
}

/* Function: enqueueAllEdges
 *
 * Inserts every edge (in the four cardinal directions and within
 * bounds of the graph) into a PriorityQueue with a priority
 * assigned at random.
 */
void enqueueAllEdges(int numRows, int numCols, TrailblazerPQueue<Edge>& pq)
{
    for(int  i = 0; i < numRows; i++)
		for(int j = 0; j < numCols-1; j++)
			pq.enqueue(makeEdge(makeLoc(i,j),makeLoc(i,j+1)), randomInteger(0,100));
	for(int  i = 0; i < numCols; i++)
		for(int j = 0; j < numRows-1; j++)
			pq.enqueue(makeEdge(makeLoc(j, i),makeLoc(j+1, i)), randomInteger(0,100));
}

/* Function: root
 *
 * Takes an integer and the "id" vector. In this data structure,
 * a node would be it's own root if it's index in "id" was itself.
 * "root" traces a node back to it's root node and cleans up a 
 * little on each pass by setting the root to the "grandparent".
 */
int root(int i, Vector<int>&id)
{
    while(i != id[i]) {
        id[i] = id[id[i]]; // grandparent
        i = id[i];
    }
    return i;
}


/* Function: find
 *
 * Returns true if two nodes have the same root, i.e. belong
 * to the same cluster.
 */
bool find(int p, int q, Vector<int>& id)
{
    return (root(p, id) == root(q, id));
}

/* Function: unite
 *
 * The size vector keeps track of the number of children nodes
 * at each index (index identifies a node in the graph). "unite"
 * uses this info to attach the smaller tree to the larger and
 * keeps the overall height of the tree from growing quickly.
 */
void unite(int p, int q, Vector<int>& id, Vector<int>& size)
{
    int i = root(p, id);
    int j = root(q, id);
    
    if (size[i] < size[j]) {
        id[i] = j;
        size[j] += size[i];
    } else {
        id[j] = i;
        size[i] += size[j];
    }
}









