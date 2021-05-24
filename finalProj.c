#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define MAX_TRUCK 3
#define TRUCK_SIZE 7

bool eulerPath = true;
bool eulerCircuit = true;
bool directed = false;
int start, finish, vertex, startNode, finishNode;
void title();
void name();
typedef struct barang_queue
{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct barang_queue *next;
} barang_queue;

typedef struct barang_stack
{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct barang_stack *next;
    struct barang_stack *prev;
} barang_stack;
barang_stack *top = NULL;

typedef struct queue
{
    int count;
    barang_queue *front;
    barang_queue *rear;
} queue;

int isEmpty()
{
    if (top == NULL)
        return 1;
    else
        return 0;
}

void push(int berat, char kirim[], char terima[], char alamat[])
{
    barang_stack *temp = (barang_stack *)malloc(sizeof(barang_stack));
    temp->prev = NULL;
    temp->next = NULL;
    temp->data = berat;
    strcpy(temp->pengirim, kirim);
    strcpy(temp->penerima, terima);
    strcpy(temp->alamat, alamat);
    if (isEmpty() == 1)
    {
        top = temp;
    }
    else
    {
        top->next = temp;
        temp->prev = top;
        top = temp;
    }
}

void pop()
{
    barang_stack *hapus;
    hapus = top;
    if (isEmpty() == 1)
    {
        printf("Tidak ada barang\n");
    }
    else
    {
        top = top->prev;
        free(hapus);
    }
}

void display_stack()
{
    barang_stack *bantu;
    bantu = top;
    printf("\t Barang : \n");
    if (isEmpty() == 1)
    {
        printf("--KOSONG--\n");
    }
    else
    {
        while (bantu != NULL)
        {
            printf("\t ===================================\n");
            printf("\t Nama Pengirim :  %s\n", bantu->pengirim);
            printf("\t Nama Penerima :  %s\n", bantu->penerima);
            printf("\t Alamat Penerima :  %s\n", bantu->alamat);
            printf("\t Berat Barang :  %d\n", bantu->data);
            printf("\t ===================================\n");
            bantu = bantu->prev;
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
        scanf("%[^\n]s", tmp->pengirim);
        printf("\t Masukkan nama penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->penerima);
        printf("\t Masukkan alamat penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->alamat);
        printf("\t Masukkan berat : ");
        scanf("%d", &(tmp->data));
        tmp->next = NULL;
        if (!isempty(q))
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

int dequeue(queue *q)
{
    barang_queue *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return (n);
}

void display(barang_queue *head)
{
    if (head == NULL)
    {
        printf("\t Tidak Ada Barang Lagi\n");
    }
    else
    {
        printf("\t DATA PENGIRIM DAN PENERIMA\n");
        printf("\t NAMA PENGIRIM : %s\n", head->pengirim);
        printf("\t NAMA PENERIMA : %s\n", head->penerima);
        printf("\t ALAMAT PENERIMA : %s\n", head->alamat);
        printf("\t BERAT BARANG : %d\n", head->data);
        printf("\t ===================================\n");
        display(head->next);
    }
}

void swap(barang_queue *a, barang_queue *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void bubble_sort(barang_queue *start)
{
    int swapped, i;
    barang_queue *ptr1;
    barang_queue *lptr = NULL;

    if (start == NULL)
    {
        return;
    }
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void display_sort(barang_queue *head)
{
    if (head == NULL)
    {
        printf(" ");
    }
    else
    {
        printf("\t --%d\n", head->data);
        display_sort(head->next);
    }
}

void search(barang_queue *start, char *dicari)
{
    barang_queue *p;
    int pos = 1;
    p = start;
    while (p != NULL)
    {
        if (strcmp(p->pengirim, dicari) == 0)
        {
            printf("\t Barang yang dikirim oleh %s ditemukan diposisi %d\n", dicari, pos);
            return;
        }
        p = p->next;
        pos++;
    }
    printf("\t Barang yang dikirim oleh %s tidak ditemukan\n", dicari);
}

void hasEulerPath(int node[vertex][vertex], int in[vertex], int out[vertex])
{
    int odd = 0;
    int even = 0;
    if (vertex < 2)
    {
        eulerCircuit = false;
        eulerPath = false;
    }
    else if (vertex == 2 && (node[0][1] == 1 || node[1][0] == 1))
    {
        eulerCircuit = false;
        eulerPath = true;
        if (node[0][1] == 1 && node[1][0] == 0)
            startNode = 0;
        else
            startNode = 1;
    }
    else
    {
        if (directed == false)
        {
            for (int i = 0; i < vertex; i++)
            {
                if (in[i] % 2 != 0)
                {
                    odd++;
                    if (odd == 1)
                        startNode = i;
                    if (odd == 2)
                        finishNode = i;
                    if (odd > 2)
                    {
                        eulerCircuit = false;
                        eulerPath = false;
                        break;
                    }
                }
            }
            if (odd == 0)
            {
                startNode = 0;
                finishNode = 0;
            }
            if (odd > 2 || odd == 1)
                eulerPath = false;
            if (odd > 0)
                eulerCircuit = false;
        }

        else
        {
            for (int i = 0; i < vertex; i++)
            {
                if (out[i] - in[i] == 1)
                {
                    start++;
                    if (start = 1)
                        startNode = i;

                    if (start > 1)
                    {
                        eulerPath = false;
                        eulerCircuit = false;
                        break;
                    }
                }
                if (in[i] - out[i] == 1)
                {
                    finish++;
                    if (finish == 1)
                        finishNode = i;

                    if (finish > 1)
                    {
                        eulerPath = false;
                        eulerCircuit = false;
                        break;
                    }
                }
                if (in[i] == out[i])
                    even++;
                if (even != vertex && start == 1)
                    eulerCircuit = false;
            }
        }
    }
    if (eulerPath == true)
    {
        printf("\t Jalur Euler Ditemukan\n");
        printf("\t Start Node : %d\n", startNode + 1);
        printf("\t Finish Node: %d\n", finishNode + 1);
    }
    else
        printf("\t Jalur Euler Tidak Ditemukan\n");
    if (eulerCircuit == true)
        printf("\t Sirkuit Euler Ditemukan\n");
    else
        printf("\t Sirkuit Euler Tidak Ditemukan\n");
}

int main()
{
    int ch, choice, pos, i, j;
    int banyak_truk = 1;
    int banyak_barang = 1;
    char item[50];
    queue *q;
    q = malloc(sizeof(queue));
    initialize(q);
    title();
    name();
    while (banyak_truk <= MAX_TRUCK)
    {
        printf("\t=================================\n");
        printf("\t           GUDANG JAWA           \n");
        printf("\t=================================\n");
        printf("\t 1. Input barang ke gudang\n");
        printf("\t 2. Hapus barang dari antrian\n");
        printf("\t 3. Masukkan barang ke truck\n");
        printf("\t 4. Lihat barang di antrian\n");
        printf("\t 5. Lihat barang di truk\n");
        printf("\t 6. Kirim barang ke Bali\n");
        printf("\t 7. Cari barang\n");
        printf("\t 8. Keluar\n");
        printf("\t=================================\n");
        printf("\t Input : ");
        scanf("%d", &ch);
        if (ch == 1)
        {
            while (banyak_barang <= TRUCK_SIZE)
            {
                printf("\t Masukkan data dari barang\n");
                enqueue(q);
                banyak_barang++;
                printf("\t=================================\n");
            }
        }
        else if (ch == 2)
        {
            dequeue(q);
        }
        else if (ch == 3)
        {
            barang_queue *bantu;
            bantu = q->front;
            do
            {
                push(bantu->data, bantu->pengirim, bantu->penerima, bantu->alamat);
                bantu = bantu->next;
            } while (bantu != NULL);
            printf("\t Barang berhasil dimasukan ke truk\n");
        }
        else if (ch == 4)
        {
            printf("\t ===================================\n");
            display(q->front);
        }
        else if (ch == 5)
        {
            display_stack();
        }
        else if (ch == 6)
        {
            if ((banyak_barang = TRUCK_SIZE) && (banyak_truk <= 3))
            {
                printf("\t BARANG TELAH DIKIRIM KE BALI\n");
                banyak_truk++;
                while (1)
                {
                    printf("\t=================================\n");
                    printf("\t           GUDANG BALI           \n");
                    printf("\t=================================\n");
                    printf("\t 1. Cek barang di truk\n");
                    printf("\t 2. Urutkan barang\n");
                    printf("\t 3. Kirim barang ke pelanggan\n");
                    printf("\t 4. Keluar\n");
                    printf("\t Input : ");
                    scanf("%d", &choice);
                    if (choice == 1)
                    {
                        display_stack();
                    }
                    else if (choice == 2)
                    {
                        bubble_sort(q->front);
                        printf("\t Sort Barang Berdasarkan Berat\n");
                        display_sort(q->front);
                    }
                    else if (choice == 3)
                    {
                        int allVisited = 0;
                        vertex = TRUCK_SIZE;
                        int node[vertex][vertex];
                        printf("\t Masukkan 1 apabila terhubung \n");
                        printf("\t Masukkan 0 jika tidak terhubung \n");
                        for (i = 0; i < vertex; i++)
                        {
                            for (j = 0; j < vertex; j++)
                            {
                                if (i != j)
                                {
                                    printf("\t Alamat ke-%d dan alamat ke-%d: ", i + 1, j + 1);
                                    scanf("%d", &node[i][j]);
                                }
                                else
                                {
                                    node[i][j] = 0;
                                }
                            }
                        }
                        printf("\t Tampilan Matriks : \n");
                        for (i = 0; i < vertex; i++)
                        {
                            for (j = 0; j < vertex; j++)
                            {
                                printf("\t %d ", node[i][j]);
                            }
                            printf("\n");
                        }
                        if (vertex < 2)
                            printf("\t Tidak Ada Graph yang terbentuk!\n");
                        else
                        {
                            int outdegree[vertex];
                            for (i = 0; i < vertex; i++)
                            {
                                outdegree[i] = 0;
                                for (j = 0; j < vertex; j++)
                                {
                                    if (node[i][j] == 1)
                                    {
                                        outdegree[i]++;
                                    }
                                }
                            }
                            int indegree[vertex];
                            for (j = 0; j < vertex; j++)
                            {
                                indegree[j] = 0;
                                for (i = 0; i < vertex; i++)
                                {
                                    if (node[i][j] == 1)
                                    {
                                        indegree[j]++;
                                    }
                                }
                            }
                            if (directed == true)
                                printf("\t Berarah!\n");
                            else
                                printf("\t Tidak Berarah!\n");
                            hasEulerPath(node, indegree, outdegree);
                            if (eulerPath == true)
                            {
                                printf("\n\t Rute Euler:\n");
                                j = startNode;
                                while (allVisited != 1)
                                {
                                    for (i = vertex - 1; i >= 0; i--)
                                    {
                                        if (node[j][i] == 1)
                                        {
                                            if (startNode > -1)
                                            {
                                                printf("%d -> %d", j + 1, i + 1);
                                                startNode = -1;
                                            }
                                            else
                                                printf(", %d -> %d", j + 1, i + 1);
                                            node[j][i] = 0;
                                            node[i][j] = 0;
                                            j = i;
                                            break;
                                        }
                                        else if (j == finishNode && i == 0 && node[j][i] == 0)
                                        {
                                            allVisited = 1;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (choice == 4)
                    {
                        exit(1);
                    }
                }
            }
        }
        else if (ch == 7)
        {
            printf("\t Masukkan nama pengirim : ");
            fflush(stdin);
            scanf("%[^\n]s", &item);
            search(q->front, item);
        }
        else if (ch == 8)
        {
            break;
        }
    }
    return 0;
}
void title()
{
    printf("\t +--------------------------------------------------------------------------------+\n");
    printf("\t |                         FINAL PROJECT STRUKTUR DATA                            |\n");
    printf("\t |                               COURIER SYSTEM                                   |\n");
    printf("\t +--------------------------------------------------------------------------------+\n");
}

void name()
{
    printf("\t |OLEH: PANDE PUTU DEVO PUNDA MAHESWARA                                2008561107 |\n");
    printf("\t |      MADE KRISNA DWIPA JAYA                                         2008561106 |\n");
    printf("\t |      RONALDITO JUAN BANTARAS TARIGAN                                2008561108 |\n");
    printf("\t |      I DEWA GDE PUTRA ANGA BIARA                                    2008561105 |\n");
    printf("\t +--------------------------------------------------------------------------------+\n");
    printf("\n");
}