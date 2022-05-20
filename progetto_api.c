#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#define INFM /*2147483647*/ 999999999

int numero;     /*TOGLIERE LA VARIABILE GLOBALE*/
int max[2]={0,0};  //primo valore->somma, secondo valore->numero grafo
int totalNodes=0;
int numeroGrafo=-1;
int k=0;


int atoi_mine( const char * q )
{
    int u = 0;
    while( *q ) {
        u = u*10 + (*q++ - '0');
    }
    return u;
}

void swap(int arr[][2], int a, int b) {
    int temp = arr[a][0];
    arr[a][0] = arr[b][0];
    arr[b][0] = temp;

    temp = arr[a][1];
    arr[a][1] = arr[b][1];
    arr[b][1] = temp;
}

void mine(int arr[][2],int n, int i){
    int max;
    int l=2*i+1;
    int r=2*i+2;
    if(l<=n-1&&arr[l][0]>arr[i][0]){
        max=l;
    }
    /*else if(l<=n-1&&arr[l][0]==arr[i][0]&&arr[l][1]>arr[i][1]){
        max=l;
    }*/
    else{
        max=i;
    }
    if(r<=n-1&&arr[r][0]>arr[max][0]){
        max=r;
    }
    /*else if(r<=n-1&&arr[r][0]>arr[max][0]&&arr[r][1]>arr[i][1]){
        max=r;
    }*/
    if(max!=i){
        swap(arr,i,max);
        mine(arr,n,max);
    }
}

void siftUp(int arr[][2], int n, int i){
    int p;
    p=floor((i-1)/2);
    if(i==0){
        return;
    }
    else if(arr[p][0]>=arr[i][0]){
        return;
    }
    else if(arr[p][0]<arr[i][0]){
        swap(arr,p,i);
        i=p;
        if(i>=0){
            siftUp(arr,n,i);
        }
    }
}


void siftDown(int arr[][2],int n, int i){
    int a=(2*i)+1;
    int b=(2*i)+2;

    if(a>n||b>n){
        return;
    }

    else if((arr[a][0]>arr[b][0])&&(arr[a][0]>arr[i][0])){
        swap(arr,a,i);
        siftDown(arr,n,a);
    }
    else if((arr[a][0]<arr[b][0])&&(arr[b][0]>arr[i][0])){
        swap(arr,b,i);
        siftDown(arr,n,b);
    }
    else if(arr[a][0]==arr[i][0]){
        if(arr[a][1]>arr[i][1]){
            swap(arr,a,i);
            siftDown(arr,n,a);
        }
        else{
            return;
        }
    }
    else if(arr[b][0]==arr[i][0]){
        if(arr[b][1]>arr[i][1]){
            swap(arr,b,i);
            siftDown(arr,n,b);
        }
        else{
            return;
        }
    }
    else{
        return;
    }
}

void deleteMax(int array[][2], int n){       /*funziona*/

  int last = array[n-1][0];
  array[0][0]=last;

  /*siftDown(array,0,n);*/

}

void inserisci(int arr[][2], int n, int elem){
    deleteMax(arr,n);
    arr[0][0]=elem;
    /*siftDown(arr,n,0);*/
    for(int i=k;i>=0;i--){
        mine(arr,k,i);
    }
}

int salvaPercorsi(){        /*salva i primi due int e li mette in ins[0] e k, ritorna ins[0]*/
    char strGrafi[20];
    int numNodi;
    int topK;
    int ins[2];

    if((fgets(strGrafi, sizeof(strGrafi), stdin))!=NULL){
        ins[0]=0;
    }

    char* primo = strtok(strGrafi, " ");
    char* secondo = strtok(NULL, " ");
    

    /*free(strGrafi);*/

    numNodi = atoi(primo);
    topK = atoi(secondo);
    ins[0]=numNodi;
    ins[1]=topK;
    k = ins[1];

    return ins[0];
}

int dijkstra(int arr[numero][numero], int n, int start) {

    int costi[numero][numero]; 
    int pre[numero];
    int distanza[numero];
    int vis[numero];
    int minDistanza,ind;
    int i,j;
    int next=0;
    int somma = 0;


    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(arr[i][j]==0){
                costi[i][j]=INFM;
            }
            else{
                costi[i][j]=arr[i][j];
            }   
        }
    }
    

    for(i=0;i<n;i++){
        distanza[i]=costi[start][i];
        pre[i]=start;
        vis[i]= 0;
    }

    distanza[start]= 0;
    vis[start]=1;
    ind=1;

    while(ind<n-1) {
        minDistanza=INFM;

        for(i=0;i<n;i++){
            if(distanza[i]<minDistanza&&!vis[i]){
                minDistanza=distanza[i];
                next=i;
            }
        }
            

        vis[next]=1;

        for(i=0;i<n;i++){
            if(!vis[i]){
                if(minDistanza+costi[next][i]<distanza[i]){
                    distanza[i]=minDistanza+costi[next][i];
                    pre[i]=next;
                }
            }     
        }
            
        ind++;
    }

    for(i=0;i<n;i++){
        if(i!=start){
            /*printf("distanza da %d: %d\n",i,distanza[i]);*/
            if(distanza[i]!=INFM){
                
                somma=somma+distanza[i];
            }
            /*else{
                somma=somma+distanza[i];
            }*/
        }
    }
    pre[0]=pre[0];
    return somma;
}


int calcolaSomma(int num){      /*calcola la somma di una matrice di adiacenza e la salva in node*/
    int node;
    int riga=0;
    int colonna=0;
    char str[100];
    int n=0;
    char c;
    

    int arr[num][num];

    while((c=getchar_unlocked())){
        if((c!=',')&&(c!='\n')){
            str[n]=c;
            n++;
        }
        else if(c==','){
            str[n]='\0';
            n=0;
            arr[riga][colonna]=atoi_mine(str);
            colonna++;
        }
        else if(c=='\n'){
            str[n]='\0';
            n=0;
            arr[riga][colonna]=atoi_mine(str);
            riga++;
            colonna=0;
            if(riga==num){
                break;
            }
        }

    }

    node = dijkstra(arr,num,0);


    return node;
}

int main(){
    char p;
    char temp1[30];
    int i=0;
    char* q;

    
    numero=salvaPercorsi();

    int heap[k][2];


    for(int j=0;j<2147483647;j++){
        p=getchar_unlocked();
        if(p=='A'){
            q=fgets(temp1,sizeof(temp1),stdin);
            i=calcolaSomma(numero);
            numeroGrafo=numeroGrafo+1;
            if(numeroGrafo<k-1){
                heap[j][0]=i;
                heap[j][1]=numeroGrafo;
                /*printf("inserito: %d quindi %d, j=%d \n",numeroGrafo,heap[j][1],j);*/
            }
            else if(numeroGrafo==(k-1)){
                heap[j][0]=i;
                heap[j][1]=numeroGrafo;
                
                for(int l=k;l>=0;l--){
                    mine(heap,k,l);
                }
            }
            else if(numeroGrafo>k-1){
                /*printf("entrato %d\n",heap[0][0]);*/
                if(i==heap[0][0]-1){
                    deleteMax(heap,k);
                    heap[0][0]=i;
                    heap[0][1]=numeroGrafo;
                }
                

                else if(i<heap[0][0]-1){
                    heap[0][1]=numeroGrafo;
                    inserisci(heap,k,i);
                }
            }
            
            continue;
        }
        else if(p=='T'||p=='o'){
            j--;
            q=fgets(temp1,sizeof(temp1),stdin);
            if(numeroGrafo==-1){
                printf("\n");
            }
            if(numeroGrafo<k){
                /*printf("siamo al  %d\n",numeroGrafo);
                printf("%d\n",heap[1][1]);*/
                for(int i=0;i<=numeroGrafo;i++){
                    if(i==numeroGrafo){
                        printf("%d\n",heap[i][1]);
                    }
                    else{
                        printf("%d ",heap[i][1]);
                    }
                }
            }
            else{
                for(i=0;i<k;i++){
                    if(i==k-1){
                        printf("%d\n",heap[i][1]);
                    }
                    else{
                        printf("%d ",heap[i][1]);
                    }
                }
            }


            continue;
        }
        else if(p==EOF){
            break;
        }
    }

    q=q;

    return 0;
}