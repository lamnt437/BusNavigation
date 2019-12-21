// char *token;
    // char *rest = buffer;
    // printf("*\n");
    // while((token = strtok_r(rest, "\n\n", &rest)))
    //     printf("%s\n", token);
    // return 0;
    // printf("buffer: %s\n", buffer);
    char *token = strtok_r(buffer, "\n\n", &ptr5);
    printf("test: %s\n", token);
    // return 0;
    while (token != NULL)
    {
        char *ptr, *ptr2,*rest;
        char *line = strtok_r(token0, ";", &rest);
        char *busline;
        busline = strdup(line);
        busline = trim(busline, " ");
        char *forward = strtok_r(line, ";", &ptr2);
        char *stations = strtok_r(forward, "-", &ptr2);
        while (stations != NULL)
                {
                    // printf("token2: %s\n", token2);
                    char *vertex1 = trim(stations, " ");
                    addVertex(g, vertex1, vertex1);
                    char *vertex2 = strdup(vertex1);
                    vertex1 = strtok_r(NULL, "-", &ptr2);
                    vertex1 = trim(vertex1, " ");
                    addVertex(g, vertex1, vertex1);
                    addEdge(g, vertex2, vertex1, busline);
                }
        char *backward = strtok_r(line, ";", &rest);
        printf("%s\n",line);

        // int j=0;
        // while (token1 != NULL)
        // {
        //     printf("test %s\n\ndd %s", token1,ptr);
        //     j++;
        //     char *busline;
        //     if (j == 1)
        //     {
        //         busline = strdup(token1);
        //         busline = trim(busline, " ");
        //     }
        //     //printf("busline: %s\n", busline);
        //     if (j >= 2)
        //     {
        //         char *token2 = strtok_r(token1, "-", &ptr2);
        //         while (token2 != NULL)
        //         {
        //             // printf("token2: %s\n", token2);
        //             token2 = trim(token2, " ");
        //             addVertex(g, token2, token2);
        //             char *token2_1 = strdup(token2);
        //             token2 = strtok_r(NULL, "-", &ptr2);
        //             token2 = trim(token2, " ");
        //             addVertex(g, token2, token2);
        //             addEdge(g, token2_1, token2, busline);
        //             // printf("token21: %s\n", token2);
                    
        //             // /* print vertices */
        //             // JRB jrb_ptr;
        //             // jrb_traverse(jrb_ptr, g.vertices) {
        //             //     printf("v: %s\n", jval_s(jrb_ptr->key));
        //             // }
        //             // printf("hasEdge: %d\n", hasEdge(g, "Bến xe Gia Lâm", "Ngô Gia Khảm"));
        //             // break;
        //         }
        //     }
        //     token1 = strtok_r(NULL, ";", &ptr);
        //     //printf("%s\n", token1);
        // }
        //printf(" data: %s\n", token);
        token = strtok_r(NULL, "\n\n", &ptr5);
    }