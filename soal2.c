/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2024/2025
 *   Modul               : Foundation of Algorithm
 *   Hari dan Tanggal    : Senin, 11 Mei 2026
 *   Nama (NIM)          : Nadine Gabe Ulina Sianturi
 *   Nama File           : soal2.c
 *   Deskripsi           : menentukan apakah susunan prasyarat yang diberikan masih memungkinkan semua misi dijalankan.dengan syarat ada N misi dan 
 * M pasangan yang terdiri dari a dan b dimana a bergantung pada b, tetapi tidak boleh ada cycle dalam graph ini.(simplenya tuh setangkep aku kayak dia boleh ada panah bolak balik antara dua node tapi gaboleh bikin cycle)
TIDAK BISA (ini outputnya). rencana penyelesaiannya itu bikin dua buah graph yang salah satunya dependan ke graph yang lain lalu cek jika ada nilai graph a yang berakhir ke dirinya sendiri maka dia membentuk cycle).
 * rencananya bikin graph dulu, trus tambahin edge, baru gunain dfs buat cek graphnya(pakai int supaya ngereturn hasil jangan void)
 * source : https://www.geeksforgeeks.org/compiler-design/dependency-graph-in-compiler-design/ ; https://rkgiitbh.github.io/data-structures.github.io/HTML/graphImplementation.html ; https://software.land/dependency-graph/
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;

typedef struct Graph {
    int N;
    Node** head;
}Graph;


Graph* createGraph(int N) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));

    graph->N = N;
    graph->head = (Node**) malloc(N * sizeof(Node*));

    for (int i = 0; i < N; i++) {
        graph->head[i] = NULL;
    }
    return graph;
}


void addEdge(Graph* graph, int src, int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = graph->head[src];
    graph->head[src] = newNode;
}

int dfsCycle(Graph* graph, int v, int state[]) {
    state[v] = 1;

    Node* temp = graph->head[v];

    while (temp != NULL) {
        int next = temp->data;
        if (state[next] == 1) {
            return 1;
        }

        if (state[next] == 0) {
            if (dfsCycle(graph, next, state)) {
                return 1;
            }
        }
        temp = temp->next;
    }

    state[v] = 2;
    return 0;
}

int main() {
    int N, M;

    scanf("%d %d", &N, &M);

    Graph* graph = createGraph(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        addEdge(graph, a, b);
    }

    int state[N];

    for (int i = 0; i < N; i++) {
        state[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        if (state[i] == 0) {
            if (dfsCycle(graph, i, state)) {
                printf("TIDAK BISA\n");
                return 0;
            }
        }
    }

    printf("BISA\n");

    return 0;
}
