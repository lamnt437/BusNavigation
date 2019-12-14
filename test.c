#include <stdio.h>
#include "str_dgraph.h"

void main() {
    Graph g = createGraph();

    addVertex(g, "nguyen trai", "Nguyen Trai");
    addVertex(g, "tay son", "Tay Son");
    addVertex(g, "khuat duy tien", "Khuat Duy Tien");
    addVertex(g, "tran phu", "Tran Phu");

    int status1 = addEdge(g, "nguyen trai", "tay son", "1a");
    int status2 = addEdge(g, "nguyen trai", "tay son", "2");
    int status3 = addEdge(g, "nguyen trai", "tay son", "3");

    addEdge(g, "khuat duy tien", "nguyen trai", "1a");
    addEdge(g, "tran phu", "nguyen trai", "2");

    char output[100][ID_LENGTH];
    int n = outdegree(g, "nguyen trai", output);

    for(int i = 0; i < n; i++) {
        printf("%s\n", output[i]);
    }

    // int lines[100];
    // int linesNumb = getLinesOnEdge(g, "nguyen trai", "tay son", lines);
    // for(int i = 0; i < linesNumb; i++) {
    //     printf("line: %d\n", lines[i]);
    // }

    // printf("%d\n", hasEdge(g, "nguyen trai", "tay son"));
    char lines[100][ID_LENGTH];
    int n_lines = getLinesThroughStation(g, "nguyen trai", lines);
    printf("Station: nguyen trai\n");
    for(int i = 0; i < n_lines; i++) {
        printf("%s\n", lines[i]);
    }
}