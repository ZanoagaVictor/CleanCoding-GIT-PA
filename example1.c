#include <stdio.h>
#include <stdlib.h>

/// structura unui nod din lista de adiacenta (pentru fiecare restaurant)
typedef struct Node {
    int data;
    struct Node* next;
} NODE;

/// structura grafului: v = nr de noduri, vis = vector de vizitare, alst = listele de adiacenta
typedef struct Graph {
    int v;
    int* vis;
    NODE** alst;
} GPH;

/// functie care creeaza un nod nou cu valoarea data
NODE* create_node(int v) {
    NODE* nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

/// functie care adauga muchie intre doua noduri (graf neorientat)
void add_edge(GPH* g, int src, int dest) {
    NODE* nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

/// functie care initializeaza graful cu n noduri
GPH* create_g(int v) {
    GPH* g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE*) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

/// parcurgere in adancime dintr-un nod dat
void DFS(GPH* g, int v) {
    g->vis[v] = 1;

    NODE* aux = g->alst[v];
    while (aux != NULL) {
        int con_ver = aux->data;
        if (!g->vis[con_ver])
            DFS(g, con_ver);
        aux = aux->next;
    }
}

/// functie care "reseteaza" vectorul de vizitare inainte de o noua parcurgere
void wipe(GPH* g) {
    for (int i = 0; i < g->v; i++)
        g->vis[i] = 0;
}

/// verifica daca exista drum intre doua restaurante (noduri)
int path_exists(GPH* g, int src, int dest) {
    wipe(g); // resetam vectorul de vizitare
    DFS(g, src); // pornim DFS din restaurantul sursa
    return g->vis[dest]; // daca restaurantul destinatie a fost vizitat, exista drum
}

/// functie pentru citirea muchiilor de la tastatura
void insert_edges(GPH* g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, g->v - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

int main() {
    int nrv, edg_nr;
    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH* g = create_g(nrv); // cream graful

    insert_edges(g, edg_nr); // adaugam muchiile

    int src, dest;
    printf("Introdu cele doua restaurante (noduri) intre care vrei sa verifici existenta unui drum: ");
    scanf("%d%d", &src, &dest);

    /// afisam rezultatul in functie de vizitarea prin DFS
    if (path_exists(g, src, dest))
        printf("Exista drum intre %d si %d.\n", src, dest);
    else
        printf("NU exista drum intre %d si %d.\n", src, dest);

    return 0;
}
