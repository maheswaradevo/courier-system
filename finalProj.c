#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_TRUCK 3
#define TRUCK_SIZE 10

typedef struct barang
{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct barang *next;
}barang;

typedef struct barang_list
{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct barang_list *next;
    struct barang_list *prev;
}barang_list;
barang_list *top=NULL;

typedef struct queue
{
    int count;
    barang *front;
    barang *rear;
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
    barang_list *temp = (barang_list*)malloc(sizeof(barang_list));
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
    barang_list *hapus;
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
    barang_list *bantu;
    bantu = top;
    printf("Barang : \n");
    if(isEmpty() == 1){
        printf("--KOSONG--\n");
    }
    else{
        while(bantu!=NULL){
            printf("BARANG\n");
            printf("Nama Pengirim :  %s\n", bantu->pengirim);
            printf("Nama Penerima :  %s\n", bantu->penerima);
            printf("Alamat Penerima :  %s\n", bantu->alamat);
            printf("Berat Barang :  %d\n", bantu->data);
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
        barang *tmp;
        tmp = malloc(sizeof(barang));
        printf("Masukkan nama pengirim : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->pengirim);
        printf("Masukkan nama penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->penerima);
        printf("Masukkan alamat penerima : ");
        fflush(stdin);
        scanf("%[^\n]s", tmp->alamat);
        printf("Masukkan berat : ");
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
        printf("List is full\n");
    }
}

int dequeue(queue *q)
{
    barang *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return(n);
}

void display(barang *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {   
        printf("DATA PENGIRIM DAN PENERIMA\n");
        printf("NAMA PENGIRIM : %s\n", head->pengirim);
        printf("NAMA PENERIMA : %s\n", head->penerima);
        printf("ALAMAT PENERIMA : %s\n", head->alamat);
        printf("BERAT BARANG : %d\n", head -> data);
        printf("===================================\n");
        display(head->next);
    }
}

int main()
{
    int ch;
    queue *q;
    q = malloc(sizeof(queue));
    initialize(q);
    while(1){
        printf("GUDANG JAWA\n");
        printf("1. Input barang ke gudang\n");
        printf("2. Masukkan barang ke truck\n");
        printf("3. Lihat barang di antrian\n");
        printf("4. Lihat barang di truk\n");
        printf("4. Cari barang\n");
        printf("5. Keluar\n");  
        printf("Input : ");
        scanf("%d", &ch);
        if(ch==1){
            printf("Masukkan data dari barang\n");
            enqueue(q);
        }
        if(ch==2){
            barang *bantu;
            bantu = q->front;
            do{
                push(bantu->data, bantu->pengirim, bantu->penerima, bantu->alamat);
                bantu = bantu->next;
            }while(bantu!=NULL);
        }
        else if(ch==3){
            printf("===================================\n");
            display(q->front);
        }
        else if(ch==4){
            display_stack();
        }
        else if(ch==5){
            break;
        }
    }
    return 0;
}