#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int printStations(Graph g)
{
    JRB jrb_ptr;
    FILE *f1;
    f1 = fopen("stations.txt", "w");
    jrb_traverse(jrb_ptr, g.vertices)
    {
        fprintf(f1, "%-10s== %s\n", jval_s(jrb_ptr->key), jval_s(jrb_ptr->val));
    }
    fclose(f1);
    return 0;
}

Graph loadGraph(char *filename)
{
    Graph g = createGraph();

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        puts("Can't read file!");
        exit(EXIT_FAILURE);
        return g;
    }

    char buffer[1500052];

    fread(buffer, 1500000, 1, fp);

    // load to graph
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

    fclose(fp);

    return g;
}

void printMenu()
{
    printf("\n\n=======Bus Navigation=======\n\n1 - View list of stations\n2 - Output list of stations to file\n3 - Find the shortest path between 2 stations\n4 - Exit\nChoose: ");
}

void main()
{
    Graph g = loadGraph("data.txt");
    printStations(g);
    /* start menu */
    int choice;
    printMenu();
    scanf("%d", &choice);

    while (choice != 4)
    {
        switch (choice)
        {
        case 1:
            printf("\n\n*View list of stations\n\n");
            JRB jrb_ptr;
            jrb_traverse(jrb_ptr, g.vertices) {
                printf("%s\t==\t%s\n", jval_s(jrb_ptr->key), jval_s(jrb_ptr->val));
            }
            break;
        case 2:
            printf("\n\n*Output list of stations to file\n\n");
			printStations(g);
			printf("Successfully printed stations into \'stations.txt\'\n\n");
            break;
        case 3:
            printf("\n\n*Find the shortest path between 2 stations\n\n");
            char start[ID_LENGTH];
            char stop[ID_LENGTH];

            printf("Enter start station's id: ");
            scanf("%s", start);
            fflush(stdin);

            printf("Enter stop station's id: ");
            scanf("%s", stop);
            fflush(stdin);
            printf("\n");

            /* check shortest path */
            char path[100][ID_LENGTH];
            int length = 0;

            double weight = shortestPath(g, start, stop, &length, path);

            /* check shortestLines */
            Edge edges[EDGES_LENGTH];
            int n_edges = getLinesFromPath(g, path, length, edges);

            /* print lines */
            if(n_edges <= 1) {
                printf("\n\nNo path!\n\n");
                break;
            }

            printf("Current Station -----> #Busline to choose\n");
            printf("=========================================\n\n");

            char *prevLine = NULL;
            for (int i = 0; i < n_edges; i++)
            {
                if (prevLine == NULL)
                {
                    printf("%s -----> %s\n", getVertex(g, edges[i].prev), edges[i].line);
                    prevLine = edges[i].line;
                    continue;
                }
                if (strcmp(prevLine, edges[i].line) != 0)
                {
                    printf("%s -----> %s\n", getVertex(g, edges[i].prev), edges[i].line);
                    prevLine = edges[i].line;
                }
                if (i == n_edges - 1)
                    printf("%s -----> End\n", getVertex(g, edges[i].next));
            }

			printf("\nLength: %.2lf\n", weight);
            break;
        default:
            printf("\n\nPlease enter a number between 1 and 4!\n\n");
            break;
        }
        printMenu();
        scanf("%d", &choice);
    }

    /* end menu */
    printf("\nExit!\n");
}