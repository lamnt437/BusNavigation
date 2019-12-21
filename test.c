#include <stdio.h>
#include <string.h>
#include "str_dgraph.h"

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
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
    char buffer[150005];
    // char *ptr5 = NULL;
    // printf("*\n");
    fp = fopen("test12.txt", "r");
    fread(buffer, 150000, 1, fp);
    fclose(fp);
    // printf("*\n");
    // printf("%s", buffer);
    // printf("%d\n", strlen(buffer));

    // /* fgets */

    // FILE *fp;
    // char line[10000];
    // fp = fopen("test12.txt", "r");
    // fgets(line, 9999, fp);
    // line[strlen(line) - 1] = '\0';
    // printf("%s\n", line);

    /* end fgets */
    /* ------------------------------------------------------------------------------------------*/

    /////TACH HAM RIENG TOKENIZE
    char *linesRest;
    char *stringLine = strtok_r(buffer, "\n\n", &linesRest);
    while(stringLine != NULL) {
        // get linename
        char *stationsRest;
        char *lineName = trim(strtok_r(stringLine, ";", &stationsRest), " ");
        
        // printf("lineName: %s\n", lineName);

        // get forward stations + backward stations
        char *backwardStations;
        char *forwardStations = strtok_r(stationsRest, ";", &backwardStations);

        // get stations from forward stations
        char *station,*restStations;
        char *prevStation = NULL;
        station = strtok_r(forwardStations,"-",&restStations);
        while (station != NULL){
            char *stationTrimmed = trim(station, " ");
            stationTrimmed = rtrim(station,".");
            stationTrimmed = rtrim(station,";");
            addVertex(g,station,station);
            if(prevStation != NULL)
                addEdge(g, prevStation, station, lineName);
            prevStation = station;
            station = strtok_r(restStations,"-",&restStations);
        }

        // get stations from backward stations
        prevStation = NULL;
        station = strtok_r(backwardStations,"-",&restStations);
        while (station != NULL){
            char *stationTrimmed = trim(station, " ");
            stationTrimmed = rtrim(station,".");
            stationTrimmed = rtrim(station,";");
            addVertex(g,station,station);
            if(prevStation != NULL)
                addEdge(g, prevStation, station, lineName);
            prevStation = station;
            station = strtok_r(restStations,"-",&restStations);
        }

        /* check edge */
        // printf("hasEdge: %d\n", hasEdge(g, "Ngô Gia Khảm", "Bến xe Gia Lâm"));
        
        // /* traverse vertices */
        // JRB jrb_ptr;
        // jrb_traverse(jrb_ptr, g.vertices) {
        //     printf("vertex: %s\n", jval_s(jrb_ptr->key));
        // }

        stringLine = strtok_r(linesRest, "\n\n", &linesRest);
    }

    char path[100][ID_LENGTH];
    int length = 0;
    char *start = "Bến xe Gia Lâm";
    char *stop = "Nguyễn Văn Linh";
    // char *start = "a";
    // char *stop = "b";
    double weight = shortestPath(g, start, stop, &length, path);
    printf("weight: %lf\n", weight);
    for(int i = 0; i < length; i++) {
        printf("%s\n", path[i]);
    }

    /* ------------------------------------------------------------------------------------------*/
    // char output[100][ID_LENGTH];
    // int n = outdegree(g, "nguyen trai", output);

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%s\n", output[i]);
    // }

    // char lines[100][ID_LENGTH];
    // int n_lines = getLinesThroughStation(g, "nguyen trai", lines);
    // printf("Station: nguyen trai\n");
    // for (int i = 0; i < n_lines; i++)
    // {
    //     printf("%s\n", lines[i]);
    // }

    // // test shortest path
    // char *start = "khuat duy tien";
    // char *stop = "nguyen luong bang";
    // int length = 0;
    // char path[100][ID_LENGTH];

    // double total_weight = shortestPath(g, start, stop, &length, path);

    // printf("\nShortest path's weight: %lf\n", total_weight);
    // for (int i = 0; i < length; i++)
    // {
    //     printf("%s ", path[i]);
    // }
    // printf("\n");

    // // check lines function
    // printf("\nGet lines from path:\n");
    // Edge *edges = NULL;
    // n = getLinesFromPath(g, path, length, &edges);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%s - %s: %s\n", edges[i].prev, edges[i].next, edges[i].line);
    // }
}