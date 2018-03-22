#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int size;
int command_size;


struct Stack {
    int *arr;
    int top,size,max_size;
};

struct queue{
	int *arr;
	int front,rear,max_size;
};

struct client{
	int id;
	int queue_size;
	int stack_size;
	int log_counter;
	struct Stack *client_stack;
	struct queue *client_queue;
	struct Stack *client_history;
};

struct server{
	int id;
	int queue_size;
	int stack_size;
	int log_counter;
	struct Stack *server_stack;
	struct queue *server_queue;
	struct Stack *server_history;
};
struct server server_arr[1];


struct Stack *stack_creator(int stack_size) {
    struct Stack *s =(struct Stack*)malloc(sizeof(struct Stack));
    s->arr = (int*)malloc(sizeof(int)*stack_size);
    s->top = -1;
    s->max_size= stack_size;
    s->size = 0;
    return s;
}

struct queue *queue_creator(int queue_size){
	struct queue *q=(struct queue*)malloc(sizeof(struct queue));
	q->arr = (int*)malloc(sizeof(int)*queue_size);
	q->front=-1;
	q->rear=-1;
	q->max_size=queue_size;
	return q;
}

struct server server_creator(int ** real_arr){
	struct server *new_server;
	new_server= (struct server*)malloc(sizeof(struct server));
	new_server->id=real_arr[n-1][0];
	new_server->queue_size=real_arr[n-1][1];
	new_server->stack_size=real_arr[n-1][2];
	new_server->server_stack=stack_creator(new_server->stack_size);
	new_server->server_queue=queue_creator(new_server->queue_size);
	new_server->server_history=stack_creator(1000);
	new_server->log_counter=0;
	server_arr[0]=*new_server;
	return *new_server;
}

struct client client_creator(int ** real_arr,struct client *client_array,int size){
	struct client *new_client;
	new_client= (struct client*)malloc(sizeof(struct client));
	int i=size;
	for(i=0;i<size;i++){
		new_client->id=real_arr[i][0];
		new_client->queue_size=real_arr[i][1];
		new_client->stack_size=real_arr[i][2];
		new_client->client_stack=stack_creator(new_client->stack_size);
		new_client->client_queue=queue_creator(new_client->queue_size);
		new_client->log_counter=0;
		new_client->client_history=stack_creator(1000);
		client_array[i]=*new_client;
	}
}

int is_stack_full(struct Stack *s) {
    return s->size == s->max_size;
}

int is_stack_empty(struct Stack *s) {
    return s->size == 0;
}

void push(struct Stack *s, char element) {
    if(is_stack_full(s)){
    	printf("Stack full hata mesaji *2*\n");
	}
	else{
	    s->arr[++(s->top)] = element;
	    s->size++;
	}
}

void pop(struct Stack *s) {
    if(is_stack_empty(s)) {
        printf("Empty stack!\n");
        return;
    }
    char element = s->arr[(s->top)--];
    s->size--;
    //printf("%c popped!\n",element);
    
}

int is_queue_full(struct queue *q)
{
    if( (q->front == (q->rear) + 1) || (q->front == 0 && q->rear == (q->max_size)-1)){
    	return 1;
	}
    return 0;
}

int is_queue_empty(struct queue *q){
	if(q->front == -1){
		return 1;
	}
	return 0;
}

void enQueue(struct queue *q,char element){
    if(is_queue_full(q)){
    	return ;
	}
    else
    {
        if(q->front == -1){
        	q->front = 0;	
		} 
        q->rear = (q->rear + 1) % q->max_size;
        q->arr[q->rear] = element;
        
    }
}


int deQueue(struct queue *q){
    char element;
    if(is_queue_empty(q)) {
        return(-1);
    } else {
        element = q->arr[q->front];
        if (q->front == q->rear){
            q->front = -1;
            q->rear = -1;
        }
        else {
            q->front = (q->front + 1) % q->max_size;
            
        }
        return(element);
    }
}


void n_finder(char * arr){  
   	FILE *p;
   	p = fopen(arr,"r");
   	char ch;
   	ch=getc(p);
   	n=ch-48;
   	size=2*n+1;
}

void command_finder(char *arr){
	int a=0,x=0,y=0,z=0;
	FILE *f=fopen(arr, "r");		
    while(fscanf(f, "%d",&a) > 0){
		command_size=a;
	}
}

void command_builder(char *arr,char **com_arr){
	int a=0,x=0,y=0,z=0,i=0;
	FILE *f=fopen(arr, "r");
    while(fscanf(f, "%d",&a) > 0){
		
	}
	while(fscanf(f, "%s %s %s ", &x,&y,&z) > 0){
		com_arr[i][0]=x;
		com_arr[i][1]=y;
		com_arr[i++][2]=z;
	}
}


void begin(int *arr,int** ax){
	int y=1;
	int i=0;
    for(y=1,i=0;y<size,i<n;y=y+2,i++){
    	ax[i][0]=i+1;                    	    
    	ax[i][1]=arr[y];
    	ax[i][2]=arr[y+1];
	}
}



void commander(char **command_array,struct client *client_array){
	int i=0;
	int index;
	for(i=0;i<command_size;i++){
		if(command_array[i][0] == 'A'){
			char element=command_array[i][2];
			index=((command_array[i][1])-'0')-1;
			if(is_queue_full(client_array[index].client_queue)){
				push(client_array[index].client_history,'1');
				client_array[index].log_counter++;
			}
			else{
				enQueue(client_array[index].client_queue,command_array[i][2]);
			}
			
		}
		
		 else if(command_array[i][0]== 'I'){ // add element in a stack
			char element=command_array[i][2];
			index=((command_array[i][1])-'0')-1;
			if(index<n-1){ // for client
				if(is_stack_full(client_array[index].client_stack)){ // if client's stack is full
					push(client_array[index].client_history,'2');
					client_array[index].log_counter++;
				}
				else{
					push(client_array[index].client_stack,element);
				}
			}else{ //for server
				if(is_stack_full(server_arr[0].server_stack)){
					//printf("dolu ");
					push(server_arr[0].server_history,'2');
					server_arr[0].log_counter++;
				}
				else{
					push(server_arr[0].server_stack,element);
				}
			}
		}
		
		else if(command_array[i][0]== 'S'){
			char element;
			index=((command_array[i][1])-'0')-1;
			if(!is_stack_empty(client_array[index].client_stack)){
				element= client_array[index].client_stack->arr[client_array[index].client_stack->top];
				pop(client_array[index].client_stack);
				push(client_array[index].client_history,element);
				client_array[index].log_counter++;
				if(is_queue_full(server_arr[0].server_queue)){
					push(server_arr[0].server_history,'1');
					server_arr[0].log_counter++;
				}
				else{
					enQueue(server_arr[0].server_queue,element);
					//push(server_arr[0].server_history,element);
					//server_arr[0].log_counter++;
				}
			}
			else if(!is_queue_empty(client_array[index].client_queue)){
				element=client_array[index].client_queue->arr[client_array[index].client_queue->front];
				deQueue(client_array[index].client_queue);
				push(client_array[index].client_history,element);
				client_array[index].log_counter++;
				
				if(is_queue_full(server_arr[0].server_queue)){
					push(server_arr[0].server_history,'1');
					server_arr[0].log_counter++;
				}
				else{
					enQueue(server_arr[0].server_queue,element);
					//push(server_arr[0].server_history,element);
					//server_arr[0].log_counter++;
				}
			}
			else{
				push(client_array[index].client_history,'3');
				client_array[index].log_counter++;
			}
			

		}
		
		
		else if(command_array[i][0]== 'O'){
			char element;
			if(!is_stack_empty(server_arr[0].server_stack)){
				element=server_arr[0].server_stack->arr[server_arr[0].server_stack->top];
				pop(server_arr[0].server_stack);
				push(server_arr[0].server_history,element);
				server_arr[0].log_counter++;
			}
			else if(!is_queue_empty(server_arr[0].server_queue)){
				element=server_arr[0].server_queue->arr[server_arr[0].server_queue->front];
				deQueue(server_arr[0].server_queue);
				push(server_arr[0].server_history,element);
				server_arr[0].log_counter++;
			}
			else{
				push(server_arr[0].server_history,'3');
				server_arr[0].log_counter++;
			}
		}
		
	}
}

void write_to_file(char *out,struct client *client_array ){
	FILE *f = fopen(out, "w");
	int i=0,j=0,k=0;
	if (f == NULL){
	    fprintf(f,"Error opening file!\n");
	    exit(1);
	}
	
	for(j=0;j<n-1;j++){
		for(i=0;i<client_array[j].log_counter;i++){
			fprintf(f,"%c",client_array[j].client_history->arr[i]);
			
			if(i!=client_array[j].log_counter-1){
				fprintf(f," ");
			}
			else{
				fprintf(f,"\n");
			}
		}
	}
	
	for(k=0;k<server_arr[0].log_counter;k++){
		fprintf(f,"%c",server_arr[0].server_history->arr[k]);
		if(k!=server_arr[0].log_counter-1){
			fprintf(f," ");
		}
		else{
			fprintf(f,"\n");
		}
	}
	fclose(f);
}


int main(int argc, char *argv[])
{
		n_finder(argv[1]);
		int num_row = n, num_col = 3;
		int x=0,y=0,i=0,z=0,c=0;
		int *array;
		array=(int*)malloc(sizeof(int)*size);
		FILE *f=fopen(argv[1], "r");		
    	while( fscanf(f, "%d", &x) > 0 ){
	    	array[i++] = x;
	    }
    	fclose(f);
    	int **real_array;
		real_array=(int **) malloc(n*sizeof(int *));
		for(z=0;z<n;z++){
			real_array[z]=(int *) malloc(num_col*sizeof(int));
		}
		
		struct client client_array[size];
		
		begin(array,real_array);
		server_creator(real_array);
		client_creator(real_array,client_array,n-1);
		
		command_finder(argv[2]);
		
		char **command_array = malloc(command_size * sizeof(char *));
		for(c = 0; c < command_size; c++){
	  	command_array[c] = malloc(3 * sizeof(char)); 
		}
		
		command_builder(argv[2],command_array);
		commander(command_array,client_array);
		
		write_to_file(argv[3],client_array);		
		
    	free(array);
    	free(real_array);
    	free(command_array);
}
