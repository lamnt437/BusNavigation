#include "str_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_edges = 0;
int number_of_vertices = 0;

Graph loadGraph(FILE *input){
	Graph graph = createGraph();

	//read line by line
	char line[100];
	while(fgets(line, 99, input) != NULL){
		char *current_subject = strdup(strtok(line, " :"));
		number_of_vertices += addVertex(graph, current_subject, current_subject);

		char *required_subject;
		while((required_subject = strtok(NULL, " :\n")) != NULL){
			number_of_vertices += addVertex(graph, required_subject, required_subject);
			number_of_edges += addEdge(graph, required_subject, current_subject);
		}
	}

	return graph;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		puts("Wrong number of arguments!");
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	if(input == NULL){
		puts("Input file doesn't exist!");
		return 2;
	}

	Graph graph = loadGraph(input);
	fclose(input);

	int choice;

	printf("MENU:\n\n1 - In so nut, so canh\n2 - Kiem tra chu trinh\n3 - Number of prerequisite subjects\n4 - Khong co gi\n5 - Danh sach mon hoc\n6 - In trinh tu\n7 - Len lich hoc ki\n8 - exit...");
	scanf("%d", &choice);

	while(choice != 8){

		switch(choice){
			case 1:
				printf("\n==In so nut, so canh==\n\n");
				printf("So dinh: %d\n", number_of_vertices);
				printf("So canh: %d\n\n", number_of_edges);
				break;

			case 2:
				printf("\n==Kiem tra chu trinh==\n\n");
				if(DAG(graph))
					printf("Do thi hop le (khong co chu trinh)!\n\n");
				else{
					printf("Do thi khong hop le!\n\n");
					return 3;
				}
				break;
			case 3:
				printf("\n==Number of prerequisite subjects==\n\n");
				int repeat_choice;
				do{
					printf("Nhap ma mon: ");
					char name[100];
					
					scanf("%s", name);

					JRB jrb_ptr = jrb_find_str(graph.vertices, name);
					if(jrb_ptr == NULL)
						printf("Ma mon hoc khong co trong chuong trinh!\n");
					else{
						char inList[100][ID_LENGTH];
						int number_of_required_subjects = indegree(graph, name, inList);
						printf("So mon phai hoc truoc la: %d\n", number_of_required_subjects);
						for(int i = 0; i < number_of_required_subjects; i++){
							printf("%s ", inList[i]);
						}
						printf("\n");
					}
					
					printf("Co muon tim tiep khong?(1 - co, 0 - khong)...");
					scanf("%d", &repeat_choice);
				}while(repeat_choice != 0);

			case 5:
				printf("\n==Danh sach mon hoc==\n\n");
				JRB jrb_ptr;
				char inList2[100][ID_LENGTH];
				jrb_traverse(jrb_ptr, graph.vertices){
					int number = indegree(graph, jval_s(jrb_ptr->val), inList2);
					if(number == 0)
						printf("%s ", jval_s(jrb_ptr->val));
				}
				printf("\n");
				jrb_traverse(jrb_ptr, graph.vertices){
					int number = indegree(graph, jval_s(jrb_ptr->val), inList2);
					if(number == 1)
						printf("%s ", jval_s(jrb_ptr->val));
				}
				printf("\n");
				jrb_traverse(jrb_ptr, graph.vertices){
					int number = indegree(graph, jval_s(jrb_ptr->val), inList2);
					if(number == 2)
						printf("%s ", jval_s(jrb_ptr->val));
				}
				printf("\n\n");
				break;

			case 6:
				printf("\n==In trinh tu==\n\n");
				int number_of_subjects;
				char output[100][ID_LENGTH];
				topologicalSort(graph, output, &number_of_subjects);
				for(int i = 0; i < number_of_subjects; i++){
					if(i < number_of_subjects - 1)
						printf("%s => ", output[i]);
					else{
						printf("%s\n", output[i]);
					}
				}
				printf("\n");
				break;
			case 7:
				printf("\n==Len lich hoc ki==\n\n");
				int hocky_counter = 0;
				int number_of_subjects2;
				char output2[100][ID_LENGTH];
				topologicalSort(graph, output2, &number_of_subjects2);
				for(int i = 0; i < number_of_subjects; i++){
					if(i % 4 == 0){
						hocky_counter++;
						printf("*Hoc ki %d:\n", hocky_counter);
					}
					printf("%s\n", output[i]);
				}
				printf("\n");

			default:
				break;
		}

		printf("MENU:\n\n1 - In so nut, so canh\n2 - Kiem tra chu trinh\n3 - Number of prerequisite subjects\n4 - Khong co gi\n5 - Danh sach mon hoc\n6 - In trinh tu\n7 - Len lich hoc ki\n8 - exit...");
		scanf("%d", &choice);
	}

	return 0;
}