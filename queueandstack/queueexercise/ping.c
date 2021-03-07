#define maxsize 1000

typedef struct {
    int *time;
    int head;
    int tail;
} RecentCounter;


RecentCounter* recentCounterCreate() {
    RecentCounter* queue=(RecentCounter*)malloc(sizeof(RecentCounter));
    queue->time=(int*)malloc(sizeof(int*maxsize))
    queue->head=queue->tail=0;
    return queue;    
}

void inqueue(RecentCounter* obj, int t){
    obj->time[obj->tail++]=t;
}

void outqueue(RecentCounter* obj){
    obj->head++;
}

int recentCounterPing(RecentCounter* obj, int t) {
    inqueue(obj,t);
    
    while(t-(obj->time[obj->head])>3000)
        outqueue(obj);

    return obj->tail-obj->head;
}

void recentCounterFree(RecentCounter* obj) {
    free(obj->time);
    free(obj);
}

/**
 * Your RecentCounter struct will be instantiated and called as such:
 * RecentCounter* obj = recentCounterCreate();
 * int param_1 = recentCounterPing(obj, t);
 
 * recentCounterFree(obj);
*/