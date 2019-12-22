#include <stdio.h>
#include <string.h>
#include "str_dgraph.h"

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL)
    {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0)
    {
        size_t len = strlen(str);
        if (totrim == len)
        {
            str[0] = '\0';
        }
        else
        {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL)
    {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL)
    {
        str[i] = '\0';
        i--;
    }
    return str;
}

char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

void main()
{
    /* fread */
    Graph g = createGraph();
    FILE *fp;
    char buffer[1500052];
    // char *ptr5 = NULL;
    // printf("*\n");
    fp = fopen("test111.txt", "r");
    fread(buffer, 1500000, 1, fp);
    fclose(fp);

    /* ------------------------------------------------------------------------------------------*/

    /////TACH HAM RIENG TOKENIZE
    char *linesRest;
    char *stringLine = strtok_r(buffer, "\n", &linesRest);
    while (stringLine != NULL)
    {
        // get linename
        char *stationsRest;
        char *lineName = strtok_r(stringLine, ";", &stationsRest);

        // get forward stations + backward stations
        char *backwardStations;
        char *forwardStations = strtok_r(stationsRest, ";", &backwardStations);

        // get stations from forward stations
        char *station, *restStations, *stationName;
        char *prevStation = NULL;
        station = strtok_r(forwardStations, "__", &restStations);
        while (station != NULL)
        {
            char *stationId = strtok_r(station, "::", &stationName);
            addVertex(g, stationId, stationName);
            if (prevStation != NULL)
                addEdge(g, prevStation, station, lineName);
            prevStation = stationId;
            station = strtok_r(restStations, "__", &restStations);
        }

        // get stations from backward stations
        prevStation = NULL;
        station = strtok_r(backwardStations, "__", &restStations);
        while (station != NULL)
        {
            char *stationId = strtok_r(station, "::", &stationName);
            addVertex(g, stationId, stationName);
            if (prevStation != NULL)
                addEdge(g, prevStation, station, lineName);
            prevStation = stationId;
            station = strtok_r(restStations, "__", &restStations);
        }

        stringLine = strtok_r(linesRest, "\n", &linesRest);
    }
    // JRB jrb_ptr;
    // jrb_traverse(jrb_ptr, g.vertices)
    // {
    //     printf("vertex: %s - %s\n", jval_s(jrb_ptr->key), jval_s(jrb_ptr->val));
    // }

    /* check shortest path */
    char path[100][ID_LENGTH];
    int length = 0;
    char *start = "3614";
    char *stop = "1670";

    double weight = shortestPath(g, start, stop, &length, path);

    /* check shortestLines */
    Edge edges[EDGES_LENGTH];
    int n_edges = getLinesFromPath(g, path, length, edges);

    /* print lines */
    char *prevLine = NULL;
    for(int i = 0; i < n_edges; i++) {
        if(prevLine == NULL) {
            printf("%s: %s\n", getVertex(g, edges[i].prev), edges[i].line);
            prevLine = edges[i].line;
            continue;
        }
        if(strcmp(prevLine, edges[i].line) != 0) {
            printf("%s: %s\n", getVertex(g, edges[i].prev), edges[i].line);
            prevLine = edges[i].line;
        }
    }
}