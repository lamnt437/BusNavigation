#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define ID_LENGTH 50
#define INFINITIVE_VALUE 1000000
// typedef JRB Graph;
typedef struct{
	JRB vertices;
	JRB edges;
}Graph;

Graph createGraph();
int addVertex(Graph graph, char *id, char *name);
char *getVertex(Graph graph, char *id);
int addEdge(Graph graph, char * v1, char * v2, char * lineNo);
// int addEdge(Graph graph, char * v1, char * v2);
int hasEdge(Graph graph, char * v1, char * v2);
int getLines(Graph graph, char *id, int lines[]);
int outdegree(Graph graph, char *v, char output[][ID_LENGTH]);
int indegree(Graph graph, char *v, char output[][ID_LENGTH]);
void DFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *));
void BFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *));
int DAG(Graph graph);
void dropGraph(Graph graph);
void topologicalSort(Graph graph, char output[][ID_LENGTH], int *n);

int getLinesOnEdge(Graph g, char *v1, char *v2, char lines[][ID_LENGTH]);
int getLinesThroughStation(Graph g, char *station_id, char lines[][ID_LENGTH]);
double shortestPath(Graph graph, char *start, char *stop, int *length, char path[][ID_LENGTH]);