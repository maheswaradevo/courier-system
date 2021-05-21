#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    int kota;
    int hubungan_ketetanggan;
    int node_divisit[100];
} Node;

Node *hamilton(int jumlah_node, int matriks_ketetanggaan[][jumlah_node]) {

    int awal = 0, stop, skip, sol_set_tersedia = 0, node_sebelum = -1;
    int node_dalam_stack; // * keperluan print node saja
    Node *list_temp_solution;
    Node *head;
    Node *tail;
    Node *solution_set = (Node*) malloc (sizeof(Node) * jumlah_node);

    // * list_temp_solution ini maksudnya solutionset yang dibuat jadi LinkedList
    list_temp_solution = (Node*) malloc(sizeof(Node));
    list_temp_solution->hubungan_ketetanggan = 0;
    list_temp_solution->kota = awal;
    list_temp_solution->next = NULL;
    list_temp_solution->prev = NULL;

    // * ini inisialisasi ngasi tau bahwa setiap node BELUM penrah divisit
    // * karena nanti pakai backtracking.
    for (int i = 0; i < jumlah_node; i++) {
        list_temp_solution->node_divisit[i] = 0;
    }

    // * circular doubly linkedlist
    head = list_temp_solution;
    tail = list_temp_solution;

    // * stop kalok misalkan dia kembali ke awal dan semua tetangga ada di solution set (success)
    // * atau kembali ke awal dan semua tetangga sudah di visit, tetapi tidak semua ada di solution set (fail)
    stop = 0;
    // * skip = 0 itu artinya kalau ditemuin tetangga yang belum pernah divisit
    skip = 0;
    while (stop == 0) {

        list_temp_solution = head;
        node_dalam_stack = 1;
        // * ini untuk keperuan ngeprint node saja, ngecek berapa jumlah node didalam linkedlist solution set
        while (list_temp_solution->next != NULL) {
            list_temp_solution = list_temp_solution->next;
            node_dalam_stack++;
        }
        // * reset state skip
        skip = 0;
        // * for loop untuk ngecek tetangga apakah dia sudah pernah divsit oleh node yang sedang ditunjuk
        for (int i = 0; i < jumlah_node; i++) {
            // * kalok ketemu tetangga, dia bukan node awal, belum di skip, brarti gass cek
            if (i != tail->kota && matriks_ketetanggaan[tail->kota][i] > 0 && i != awal && skip == 0) {
                list_temp_solution = head;
                // * node_sebelum = 0 itu artinya node yang ditunjuk belum ada di solution set
                node_sebelum = 0;
                while (list_temp_solution->next != NULL) {
                    list_temp_solution = list_temp_solution->next;
                    if (list_temp_solution->kota == i) {
                        node_sebelum = 1;
                        break;
                    }
                }
                if (list_temp_solution->node_divisit[i] == 1) {
                    node_sebelum = 1;
                }
                // ? kenapa make array?
                if (node_sebelum == 0) {
                    list_temp_solution = (Node*) malloc(sizeof(Node));

                    list_temp_solution->hubungan_ketetanggan = matriks_ketetanggaan[tail->kota][i];
                    list_temp_solution->kota = i;
                    list_temp_solution->prev = tail;
                    tail->next = list_temp_solution;
                    tail->node_divisit[i] = 1;
                    list_temp_solution->next = NULL;
                    tail = list_temp_solution;

                    for (int j = 0; j < jumlah_node; j++) {
                        list_temp_solution->node_divisit[j] = 0;
                    }

                    list_temp_solution = head;

                    skip = 1;
                }
                // * ini else if untuk misalkan solusi ditemukan 
                // * kalok yang lagi diperiksa == awal, dan nodeDalam solution set sama dengan jumlah node
            } 
            else if (i == awal && node_dalam_stack == jumlah_node && matriks_ketetanggaan[tail->kota][i] > 0) {
                list_temp_solution = (Node*) malloc(sizeof(Node));

                list_temp_solution->hubungan_ketetanggan = matriks_ketetanggaan[tail->kota][i];
                list_temp_solution->kota = i;
                list_temp_solution->prev = tail;
                tail->next = list_temp_solution;
                list_temp_solution->next = NULL;
                tail = list_temp_solution;

                list_temp_solution = head;
                skip = 1;
                stop = 1;
            }
        }
        // * atau kalok kembali ke awal tetapi solutionset belum sebanyak jumlah kota
        // * atau jalan buntu tetapi belum kembali ke awal
        if (skip == 0) {
            if (tail->prev != NULL) {
                list_temp_solution = tail->prev;
                list_temp_solution->next = NULL;
                
                free(tail);
                tail = list_temp_solution;
                // * ini kalok gagal
            } else {
                printf("\n\tMohon, maaf. Sistem graph tidak dapat menentukan alamat secara otomatis. Silakan pakai otak Anda sendiri\n");
                stop = 1;
                return NULL;
            }
        }
        printf("\n");
    }
    return head;
}
int main()
{
    
}