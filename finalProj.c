#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_TRUCK 3
#define TRUCK_SIZE 10

struct STACK{
    int top;
    int berat[TRUCK_SIZE];
};
struct STACK tumpuk;

void inisialisasi()
{
    tumpuk.top=-1;
}

int isFull()
{
    if(tumpuk.top == TRUCK_SIZE-1){
        return 1;
    }
    else if(tumpuk.top < TRUCK_SIZE-1){
        return 0;
    }
    return 0;
}

int isEmpty()
{
    if(tumpuk.top == -1){
        return 1;
    }
    else{
        return 0;
    }
    return 0;
}
struct node
{
    int data;
    char pengirim[50], penerima[50], alamat[50];
    struct node *next;
};
typedef struct node node;

struct queue
{
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;

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
        node *tmp;
        tmp = malloc(sizeof(node));
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
    node *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return(n);
}

void display(node *head)
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

void push(queue *q)
{
    if(isFull())
        printf("Truk sudah penuh!\n");
    else{
        tumpuk.top++;
        tumpuk.berat[tumpuk.top] = q->front;
    }
}

void displayStack()
{
    if(isEmpty())
        printf("Tidak ada barang!\n");
    else{
        printf("Barang di truck : \n");
        for(int i=tumpuk.top;i>=0;i--){
            printf("- %d\n", tumpuk.berat[i]);
        }
    }
}

int main()
{
    int ch;
    queue *q;
    q = malloc(sizeof(queue));
    inisialisasi();
    initialize(q);
    while(1){
        printf("GUDANG BALI\n");
        printf("1. Input barang ke gudang\n");
        printf("2. Masukkan barang ke truck\n");
        printf("3. Display barang di truck\n");
        printf("4. Keluar\n");  
        printf("Input : ");
        scanf("%d", &ch);
        if(ch==1){
            printf("Masukkan data dari barang\n");
            enqueue(q);
        }
        if(ch==2){
            while(q->count<0){
                push(q->front);
                dequeue(q);
            }
            displayStack();
        }
        else if(ch==3){
            printf("===================================\n");
            display(q->front);
        }
        else if(ch==4){
            break;
        }
    }
    return 0;
}