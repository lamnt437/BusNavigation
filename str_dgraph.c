#include "str_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdlib.h>
#include <string.h>


Graph createGraph(){
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

int addVertex(Graph graph, char *id, char *name){
    JRB node = jrb_find_str(graph.vertices, id);
    if(node == NULL){
        jrb_insert_str(graph.vertices, strdup(id), new_jval_s(strdup(name)));
        return 1;
    }
    return 0;
}

char *getVertex(Graph graph, char *id){
    JRB node = jrb_find_str(graph.vertices, id);
    if(node != NULL)
        return jval_s(node->val);
    return NULL;
}

// int addEdge(Graph graph, char * v1, char * v2){//from v1 to v2
//     // CHECK IF V1 AND V2 EXIST IN Graph's vertice list
//     JRB node = jrb_find_str(graph.vertices, v1);
//     if(node == NULL) return 0;
//     node = jrb_find_str(graph.vertices, v2);
//     if(node == NULL) return 0;

//     // ADD EDGE
//     JRB tree;
//     node = jrb_find_str(graph.edges, v1);
//     if(node == NULL){
//         tree = make_jrb();
//         jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
//     }
//     else{
//         tree = (JRB)jval_v(node->val);
//     }

//     node = jrb_find_str(tree, v2);
//     if(node == NULL){
//         jrb_insert_str(tree, strdup(v2), new_jval_i(1));
//         return 1;
//     }
//     return 0;
// }

// int lineNo => char *lineNo + strdup
int addEdge(Graph graph, char * v1, char * v2, char *lineNo){//from v1 to v2
    // CHECK IF V1 AND V2 EXIST IN Graph's vertice list
    JRB node = jrb_find_str(graph.vertices, v1);
    if(node == NULL) return 0;
    node = jrb_find_str(graph.vertices, v2);
    if(node == NULL) return 0;

    // ADD EDGE
    JRB tree, subtree;

    // search for v1 tree
    node = jrb_find_str(graph.edges, v1);

    // if not exist, then add new
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
    }
    else{
        tree = (JRB)jval_v(node->val);
    }

    // search for v2 on the tree
    node = jrb_find_str(tree, v2);

    // if not exist, then add new
    if(node == NULL){
        subtree = make_jrb();
        jrb_insert_str(tree, strdup(v2), new_jval_v(subtree));
    }
    else {
        subtree = (JRB) jval_v(node->val);
    }

    // search for lineNo on the tree
    node = jrb_find_str(subtree, lineNo);

    // if not exist, then add new
    if(node == NULL) {
        jrb_insert_str(subtree, strdup(lineNo), new_jval_i(1));
        return 1;
    }
    return 0;
}

// /* for node station */
// int addEdge(Graph graph, char *v1, char *v2, int lineNo) {
//     // search for v1, v2
//     JRB tree, node;
//     JRB v1_ptr = jrb_find_str(graph.vertices, v1);
//     if(v1_ptr == NULL) return 0;
//     JRB v2_ptr = jrb_find_str(graph.vertices, v2);
//     if(v2_ptr == NULL) return 0;
    
//     // top down approach
//     // search for v1 tree
//     node = jrb_find_str(graph.edges, v1);
//     // if not exist, then add new
//     if(node == NULL) {
//         tree = make_jrb();
//         jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
//     } else {
//         tree = (JRB) jval_v(node->val);
//     }
//     // search for v2 on the tree
//     // if not exist, then add new
//     node = jrb_find_str(tree, v2);
//     if(node == NULL) {
//         tree = make_jrb();
//         jrb_insert_str(graph.edges, strdup(v2), new_jval_v(tree));
//     } else {
//         tree = (JRB) jval_v(node->val);
//     }
//     // search for lineNo on the tree
//     // if not exist, then add new
//     node = jrb_find_int(tree, lineNo);
//     if(node == NULL) {
//         jrb_insert_int(tree, lineNo, new_jval_i(1));
//         return 1;
//     }
//     return 0;
// }

int hasEdge(Graph graph, char * v1, char * v2){
    JRB node = jrb_find_str(graph.edges, v1);
    if(node == NULL)
        return 0;
    JRB tree = (JRB)jval_v(node->val);
    node = jrb_find_str(tree, v2);
    if(node == NULL)
        return 0;
    return 1;
}

int outdegree(Graph graph, char *v, char output[][ID_LENGTH]){
    int counter = 0;
    JRB node = jrb_find_str(graph.edges, v);
    if(node != NULL){
        JRB tree = (JRB)jval_v(node->val);
        JRB ptr;
        jrb_traverse(ptr, tree){
            // output[counter] = jval_i(ptr->key);
            strcpy(output[counter], jval_s(ptr->key));
            counter++;
        }
    }

    return counter;
}

int indegree(Graph graph, char *v, char output[][ID_LENGTH]){
    JRB ptr, tree, node;
    int counter = 0;
    jrb_traverse(ptr, graph.edges){
        tree = (JRB)jval_v(ptr->val);
        node = jrb_find_str(tree, v);
        if(node != NULL){
            // output[counter] = jval_i(ptr->key);
            strcpy(output[counter], jval_s(ptr->key));
            counter++;
        }
    }
    return counter;
}

void DFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *)){
    JRB visited = make_jrb();
    Dllist stack = new_dllist();
    JRB start_node = jrb_find_str(graph.edges, start);
    if(start_node != NULL){
        dll_prepend(stack, new_jval_s(strdup(start)));
        while(!dll_empty(stack)){
            Dllist node = dll_first(stack);
            char * v = strdup(jval_s(node->val));
            dll_delete_node(node);

            if(jrb_find_str(visited, v) == NULL){
                func(graph, v);
                jrb_insert_str(visited, strdup(v), new_jval_i(1));
            }

            if(strcmp(v, stop) == 0)
                break;

            char output[100][ID_LENGTH];
            int n = outdegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_str(visited, output[i]) == NULL)
                    dll_prepend(stack, new_jval_s(strdup(output[i])));
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(stack);
}

void BFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *)){
    JRB visited = make_jrb();
    Dllist queue = new_dllist();
    JRB start_node = jrb_find_str(graph.edges, start);

    if(start_node != NULL){
        dll_append(queue, new_jval_s(strdup(start)));
        while(!dll_empty(queue)){
            Dllist node = dll_first(queue);
            char *v = strdup(jval_s(node->val));
            dll_delete_node(node);

            if(jrb_find_str(visited, v) == NULL){
                func(graph, v);
                jrb_insert_str(visited, strdup(v), new_jval_i(1));
            }

            if(strcmp(v, stop) == 0)
                break;
            char output[100][ID_LENGTH];
            int n = outdegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_str(visited, output[i]) == NULL)
                    dll_append(queue, new_jval_s(strdup(output[i])));
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(queue);
}

char * dag_start = NULL;
int dag_check = 0;

void dag_visit(Graph g, char * v){
    dag_check = hasEdge(g, v, dag_start);
}

int DAG(Graph graph){
    JRB node;
    dag_check = 0;
    jrb_traverse(node, graph.vertices){
        dag_start = strdup(jval_s(node->key));
        DFS(graph, dag_start, "", dag_visit);
        if(dag_check != 0)
            return 0;
    }
    return 1;
}

void dropGraph(Graph graph){
    //traverse through tree
    JRB ptr;
    jrb_traverse(ptr, graph.vertices){
        //free sub-tree
        free(jval_s(ptr->val));
    }
    jrb_free_tree(graph.vertices);

    jrb_traverse(ptr, graph.edges){
        jrb_free_tree((JRB)jval_v(ptr->val));
    }
    jrb_free_tree(graph.edges);
}

void topologicalSort(Graph graph, char output[][ID_LENGTH], int *n){
    //create indegree table
    JRB indegreeTable = make_jrb();
    Dllist queue = new_dllist();
    
    JRB ptr;
    int inNumber;
    char inList[100][ID_LENGTH];
    int outNumber;
    char outList[100][ID_LENGTH];
    int i;

    jrb_traverse(ptr, graph.vertices){
        char * verticeIndex = strdup(jval_s(ptr->key));
        inNumber = indegree(graph, verticeIndex, inList);
        jrb_insert_str(indegreeTable, strdup(verticeIndex), new_jval_i(inNumber));
        if(inNumber == 0){
            dll_append(queue, new_jval_s(strdup(verticeIndex)));
        }
    }

    //sort
    int counter = 0;
    while(!dll_empty(queue)){
        Dllist dequeuedNode = dll_first(queue);
        char * visitingVertice = strdup(jval_s(dll_val(dequeuedNode)));
        dll_delete_node(dequeuedNode);

        // output[counter] = visitingVertice;
        strcpy(output[counter], visitingVertice);
        counter++;

        outNumber = outdegree(graph, visitingVertice, outList);
        for(i = 0; i < outNumber; i++){
            JRB decreaseIndegreeNode = jrb_find_str(indegreeTable, outList[i]);
            int newIndegree = jval_i(decreaseIndegreeNode->val) - 1;
            decreaseIndegreeNode->val = new_jval_i(newIndegree);

            if(newIndegree == 0)
                dll_append(queue, new_jval_s(strdup(outList[i])));
        }
    }

    *n = counter;
    jrb_free_tree(indegreeTable);
    free_dllist(queue);
}

/* for station */
int getLinesOnEdge(Graph g, char *v1, char *v2, char lines[][ID_LENGTH]) {
    // search v1
    JRB node = jrb_find_str(g.edges, v1);
    if(node == NULL) return 0;
    // search v2
    JRB tree = (JRB) jval_v(node->val);
    node = jrb_find_str(tree, v2);
    if(node == NULL) return 0;
    // get line
    JRB subtree = (JRB) jval_v(node->val);
    JRB ptr;
    int counter = 0;
    jrb_traverse(ptr, subtree) {
        char *line = jval_s(ptr->key);
        strcpy(lines[counter], line);
        counter++;
    }
    return counter;
}

int insertLineNoDup(char arr[][ID_LENGTH], int n, char *line_name) {
    for(int i = 0; i < n; i++) {
        if(strcmp(arr[i], line_name) == 0)
            return 0;
    }
    strcpy(arr[n], line_name);
    return 1;
}

int getLinesThroughStation(Graph g, char *station_id, char lines[][ID_LENGTH]) {
    int counter = 0;
    // get outdegree of this station
    char next_stations[100][ID_LENGTH];
    int n_next = outdegree(g, station_id, next_stations);
    // get all edges from out degree

    // for each edge, get all lines, insert to lines array
    for(int i = 0; i < n_next; i++) {
        char edge_lines[100][ID_LENGTH];
        int n_lines = getLinesOnEdge(g, station_id, next_stations[i], edge_lines);
        for(int j = 0; j < n_lines; j++) {
            int status = insertLineNoDup(lines, counter, edge_lines[j]);
            if(status == 1)
                counter++;
        }
    }

    // get all indegree of this station
    char prev_stations[100][ID_LENGTH];
    int n_prev = indegree(g, station_id, prev_stations);
    // get all edges from in degree

    // for each edge, get all lines, insert to lines array
    for(int i = 0; i < n_prev; i++) {
        char edge_lines[100][ID_LENGTH];
        int n_lines = getLinesOnEdge(g, prev_stations[i], station_id, edge_lines);
        for(int j = 0; j < n_lines; j++) {
            int status = insertLineNoDup(lines, counter, edge_lines[j]);
            if(status == 1)
                counter++;
        }
    }

    return counter;
}

int getStationsOnLine(Graph g, char *line_name, char stations[][ID_LENGTH]) {
    // receive line name
    // return list of stations
}