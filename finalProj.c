#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define MAX_TRUCK 3
#define TRUCK_SIZE 10

typedef struct barang_queue{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct barang_queue *next;
}barang_queue;
barang_queue first, *new;

typedef struct barang_stack{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct barang_stack *next;
    struct barang_stack *prev;
}barang_stack;
barang_stack *top=NULL;

typedef struct queue{
    int count;
    barang_queue *front;
    barang_queue *rear;
}queue;

int isEmpty()
{
    if(top==NULL)
        return 1;
    else
        return 0;
}

void push(int berat, char kirim[], char terima[], char alamat[])
{
    barang_stack *temp = (barang_stack*)malloc(sizeof(barang_stack));
    temp->data = berat;
    strcpy(temp->pengirim, kirim);
    strcpy(temp->penerima, terima);
    strcpy(temp->alamat, alamat);
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
        printf("Tidak ada barang\n");
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
    printf("Barang : \n");
    if(isEmpty() == 1){
        printf("--KOSONG--\n");
    }
    else{
        while(bantu!=NULL){
            printf("\tBARANG\n");
            printf("\tNama Pengirim :  %s\n", bantu->pengirim);
            printf("\tNama Penerima :  %s\n", bantu->penerima);
            printf("\tAlamat Penerima :  %s\n", bantu->alamat);
            printf("\tBerat Barang :  %d\n", bantu->data);
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
        printf("\tMasukkan nama pengirim : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->pengirim);
        printf("\tMasukkan nama penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->penerima);
        printf("\tMasukkan alamat penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->alamat);
        printf("\tMasukkan berat : ");
        scanf("%d", &(tmp->data));
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
        printf("\tAntrian sudah full!\n");
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
    return(n);
}

void display(barang_queue *head)
{
    if(head==NULL){
        printf("\tNULL\n");
    }
    else{
        printf("\tDATA PENGIRIM DAN PENERIMA\n");
        printf("\tNAMA PENGIRIM : %s\n", head->pengirim);
        printf("\tNAMA PENERIMA : %s\n", head->penerima);
        printf("\tALAMAT PENERIMA : %s\n", head->alamat);
        printf("\tBERAT BARANG : %d\n", head->data);
        printf("\t===================================\n");
        display(head->next);
    }
}

void sort(barang_queue *unsorted) {
    int banyak_unsorted = 10;
    barang_queue temp;
    for (int i = banyak_unsorted - 1; i > 0;i--) {
        for(int j = 0 ; j < i ; j++) {
            if (unsorted[j].data < unsorted[j + 1].data) {
                temp = unsorted[j];

                unsorted[j] = unsorted[j+1];

                unsorted[j+1] = temp;

            }
        }
    }
}

int search(char item[10], barang_queue **b)
{
    int count = 1;
    *new = **b;
    while(new->next!=NULL){
        if(strcmp(item, new->pengirim)==0){
            break;
        }
        else{
            count++;
            new = new->next;
        }
    }
    return count;
}

// bool search(barang_queue *head, char item[10])
// {
//     if(head==NULL){
//         return false;
//     }
//     if(strcmp(head->pengirim, item)==0){
//         return true;
//     }
//     return search(head->next, item);
// }

// void search(char s, barang *head)
// {
//     barang *p = head;
//     while(p!=NULL){
//         if(strcmp(s, p->pengirim)){
//             printf("Barang ditemukan\n");
//             break;
//         }
//         p->next;
//     }
// }

int main()
{
    int ch, choice, pos;
    char item[50];
    char s[50][50];
    queue *q;
    barang_queue *b;
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
            printf("\tMasukkan data dari barang\n");
            enqueue(q);
        }
        else if(ch==2){
            barang_queue *bantu;
            bantu = q->front;
            do{
                push(bantu->data, bantu->pengirim, bantu->penerima, bantu->alamat);
                bantu = bantu->next;
            }while(bantu!=NULL);
            printf("\tBarang berhasil dimasukan ke truk\n");
        }
        else if(ch==3){
            printf("\t===================================\n");
            display(q->front);
        }
        else if(ch==4){
            display_stack();
        }
        else if(ch==5){
            printf("\tBARANG TELAH DIKIRIM KE BALI\n");
            system("pause");
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
                    sort(b);
                }
                else if(choice == 5){
                    break;
                }
            }
        }
        else if(ch==6){
            printf("Masukan nama pengirim barang yang ingin dicari : ");
            fflush(stdin);
            scanf("%[^\n]s", &item);
            pos = search(item, &b);
            if(pos<=3){
                printf("Barang ada pada posisi ke-%d\n", pos);
            }
            else{
                printf("Barang tidak ditemukan\n");
            }

            // printf("Masukkan nama pengirim : ");
            // ffush(stdin);
            // scanf("%[^\n]s", &s);
            // search(s,b);
        }
        else if(ch==7){
            break;
        }
    }
    return 0;
}