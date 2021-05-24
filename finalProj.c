#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define MAX_TRUCK 3
#define TRUCK_SIZE 10

typedef struct barang{
    int data;
    char pengirim[50], penerima[50], alamat[50];
}barang;

typedef struct barang_queue{
    barang data;
    struct barang_queue *next;
}barang_queue;

typedef struct barang_stack{
    barang data2;
    struct barang_stack *next;
    struct barang_stack *prev;
}barang_stack;
barang_stack *top=NULL;

typedef struct queue{
    int count;
    barang_queue *front;
    barang_queue *rear;
}queue;

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
int isEmpty()
{
    if(top==NULL)
        return 1;
    else
        return 0;
}

void hold()
{
    printf("\t Tekan enter untuk melanjutkan\n");
    getch();
}

void push(int berat, char kirim[], char terima[], char alamat[])
{
    barang_stack *temp = (barang_stack*)malloc(sizeof(barang_stack));
    // temp->data2->data = berat;
    temp->data2.data = berat;
    strcpy(temp->data2.pengirim, kirim);
    strcpy(temp->data2.penerima, terima);
    strcpy(temp->data2.alamat, alamat);
    if(isEmpty()==1){
        top = temp;
    }
    else{
        top->next = temp;
        temp->prev = top;
        top = temp;
    }
}

void pop()
{
    barang_stack *hapus;
    hapus = top;
    if(isEmpty()==1){
        printf("\t Tidak ada barang\n");
    }
    else{
        top = top -> prev;
        free(hapus); 
    }
}

void display_stack()
{
    barang_stack *bantu;
    bantu = top;
    printf("\t Barang : \n");
    if(isEmpty() == 1){
        printf("--KOSONG--\n");
    }
    else{
        while(bantu!=NULL){
            printf("\t ===================================\n");
            printf("\t Nama Pengirim :  %s\n", bantu->data2.pengirim);
            printf("\t Nama Penerima :  %s\n", bantu->data2.penerima);
            printf("\t Alamat Penerima :  %s\n", bantu->data2.alamat);
            printf("\t Berat Barang :  %d\n", bantu->data2.data);
            printf("\t ===================================\n");
            bantu=bantu->prev;
        }
    }
}

void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}

void enqueue(queue *q)
{
    if (q->count < TRUCK_SIZE)
    {
        barang_queue *tmp;
        tmp = malloc(sizeof(barang_queue));
        printf("\t Masukkan nama pengirim : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->data.pengirim);
        printf("\t Masukkan nama penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->data.penerima);
        printf("\t Masukkan alamat penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->data.alamat);
        printf("\t Masukkan berat : ");
        scanf("%d", &(tmp->data.data));
        tmp->next = NULL;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
    }
    else
    {
        printf("\t Antrian sudah full!\n");
    }
}

// int dequeue(queue *q)
// {
//     barang_queue *tmp;
//     barang_queue n = q->front->data;
//     tmp = q->front;
//     q->front = q->front->next;
//     q->count--;
//     free(tmp);
//     return(n);
// }

void display(barang_queue *head)
{
    if(head==NULL){
        printf("\n");
    }
    else{
        printf("\t DATA PENGIRIM DAN PENERIMA\n");
        printf("\t NAMA PENGIRIM : %s\n", head->data.pengirim);
        printf("\t NAMA PENERIMA : %s\n", head->data.penerima);
        printf("\t ALAMAT PENERIMA : %s\n", head->data.alamat);
        printf("\t BERAT BARANG : %d\n", head->data.data);
        printf("\t ===================================\n");
        display(head->next);
    }
}

// void sort(barang_stack *unsorted, int banyak_barang) {
//     int banyak_unsorted = banyak_barang;
//     barang_stack temp;
//     for (int i = banyak_unsorted - 1; i > 0;i--) {
//         for(int j = 0 ; j < i ; j++) {
//             if (unsorted[j].data2.data < unsorted[j + 1].data2.data) {
//                 temp = unsorted[j];

//                 unsorted[j] = unsorted[j+1];

//                 unsorted[j+1] = temp;

//             }
//         }
//     }
//     for(int i = 0 ; i <= banyak_barang ; i++){
//         printf("1. Nama Pengirim : %s\n", unsorted[i].data2.pengirim);
//         printf("2. Nama Penerima : %s\n", unsorted[i].data2.penerima);
//         printf("3. Alamat Penerima : %s\n", unsorted[i].data2.alamat);
//         printf("4. Berat Barang : %d\n", unsorted[i].data2.data);
//     }
// }

// void sort (int banyak_barang, queue *q)
// {
//     int nodectr;
//     int ctr;
//     int temp;
//     barang_queue *currentNode;
//     barang_queue *nextNode;

//     for(nodectr = banyak_barang - 2 ; nodectr>=0 ; nodectr--){
//         currentNode = q->front;
//         nextNode = currentNode->next;

//         for(ctr=0;ctr<=nodectr;ctr++){
//             if(currentNode->data.data > nextNode->data.data){
//                 temp = currentNode->data.data;
//                 currentNode->data.data = nextNode->data.data;
//                 nextNode->data.data = temp;
//             }
//         }
//     }
// }

void swap (barang_queue *a, barang_queue *b)
{
    int temp = a->data.data;
    a->data.data = b->data.data;
    b->data.data = temp;
}

void bubble_sort(barang_queue *start)
{
    int swapped, i;
    barang_queue *ptr1;
    barang_queue *lptr = NULL;

    if(start == NULL){
        return;
    }
    do{
        swapped = 0;
        ptr1 = start;
        while(ptr1->next != lptr){
            if(ptr1->data.data > ptr1->next->data.data){
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while(swapped);
}

void search(barang_queue *start, char *dicari)
{
    barang_queue *p;
    int pos = 1;
    p = start;
    while(p!=NULL){
        if(strcmp(p->data.pengirim, dicari)==0){
            printf("\t Barang milik %s ditemukan diposisi %d\n", dicari, pos);
            return;
        }
        p=p->next;
        pos++;
    }
    printf("\t Barang milik %s tidak ditemukan\n", dicari);
}

int main()
{   
    int ch, choice, pos, banyak_barang;
    char item[50];
    char s[50][50];
    barang_stack *list_gudang_bali;
    queue *q;
    barang_queue *bq;
    q = malloc(sizeof(queue));
    initialize(q);
    while(1){
        printf("\t=================================\n");
        printf("\t           GUDANG JAWA           \n");
        printf("\t=================================\n");
        printf("\t 1. Input barang ke gudang\n");
        printf("\t 2. Masukkan barang ke truck\n");
        printf("\t 3. Lihat barang di antrian\n");
        printf("\t 4. Lihat barang di truk\n");
        printf("\t 5. Kirim barang ke Bali\n");
        printf("\t 6. Cari barang\n");
        printf("\t 7. Keluar\n");  
        printf("\t=================================\n");
        printf("\t Input : ");
        scanf("%d", &ch);
        if(ch==1){
            printf("\t Masukkan data dari barang\n");
            enqueue(q);
            banyak_barang++;
        }
        else if(ch==2){
            barang_queue *bantu;
            bantu = q->front;
            do{
                push(bantu->data.data, bantu->data.pengirim, bantu->data.penerima, bantu->data.alamat);
                bantu = bantu->next;
            }while(bantu!=NULL);
            printf("\t Barang berhasil dimasukan ke truk\n");
        }
        else if(ch==3){
            printf("\t ===================================\n");
            display(q->front);
        }
        else if(ch==4){
            display_stack();
        }
        else if(ch==5){
            printf("\t BARANG TELAH DIKIRIM KE BALI\n");
            hold();
            while(1){
                printf("\t=================================\n");
                printf("\t           GUDANG BALI           \n");
                printf("\t=================================\n");
                printf("\t 1. Cek barang di truk\n");
                printf("\t 2. Turunkan barang ke gudang\n");
                printf("\t 3. Urutkan barang\n");
                printf("\t 4. Kirim barang ke pelanggan\n");
                printf("\t 5. Keluar\n");
                printf("\t Input : ");
                scanf("%d", &choice);
                if(choice == 1){
                    display_stack();
                }
                else if(choice == 2){
                    pop();
                }
                else if(choice == 3){
                    bubble_sort(q->front);
                    display(q->front);
                }
                else if(choice == 4){
                    // char penerima_array[banyak_barang];
                    // for(int i=0 ;i<=banyak_barang;i++){
                    //     penerima_array[i] = q->front->data.penerima;
                    //     bq->next == NULL;
                    // }
                    // for(int i=0;i<=banyak_barang;i++){
                    //     printf("%d. %s\n", i+1, penerima_array[i]);
                    // }
                    // char indexing_alamat[banyak_barang+1][50];
                    // for(int i = 0 ; i < banyak_barang ; i++){
                    //     if(i=0){
                    //         strcpy(indexing_alamat[i], "Kantor Kurir");
                    //         continue;
                    //     }
                    //     strcpy(indexing_alamat[i], penerima_array[i]);
                    // }
                    // int matriks_ketetanggaan[banyak_barang+1][banyak_barang+1];
                    // int hubungan;
                    // for(int i = 0 ; i < banyak_barang ; i++){
                    //     printf("\tHubungan alamat %s\n", indexing_alamat[i]);
                    //     printf("\tMasukkan 1 apabila terdapat hubungan, 0 bila tidak\n");
                    //     for(int j = 0 ; j < banyak_barang ; j++){
                    //         if(i == j){
                    //             matriks_ketetanggaan[i][j] = 0;
                    //             continue;
                    //         }
                    //         printf("\tHubungan alamat %s dengan alamat %s : ", indexing_alamat[i], indexing_alamat[j]);
                    //         scanf("%d", &hubungan);
                    //         getchar();
                    //         matriks_ketetanggaan[i][j] = hubungan;
                    //         matriks_ketetanggaan[j][i] = hubungan;
                    //     }
                    // }
                    // Node *solution = hamilton(banyak_barang + 1, matriks_ketetanggaan);
                    // if(solution!=NULL){
                    //     while(solution->next!=NULL){
                    //         printf("%s", indexing_alamat[solution->kota]);
                    //         solution = solution->next;
                    //         if(solution != NULL) printf(" -> ");
                    //     }
                    //     printf("%s", indexing_alamat[solution->kota]);
                    // }
                    // printf("\n");
                    // hold();
                }
                else if(choice == 5){
                    break;
                }
            }
        }
        else if(ch==6){
            printf("\t Masukkan nama pengirim : ");
            fflush(stdin);
            scanf("%[^\n]s", &item);
            search(q->front, item);
        }
        else if(ch==7){
            break;
        }
    }
    return 0;
}