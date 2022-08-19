#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CONSTANTES, TAMANHO DO NOME DA TAREFA
#define TASK_NAME_LENGTH 2      


//NUMBER ORDER 
enum TypeOrder{CRESCENT, DESCRESCENT};


//ESTRUTURA TAREFAS
typedef struct Task
{
    /* data */
    char    name [TASK_NAME_LENGTH];
    int     time, start, end;
    struct Task *prox;

 
}Task;

    typedef struct TaskList

    {
    /* data */
    int taskLength;
    struct Task *firstTask;


    }TaskList;
    

//PROTOTIPOS
int create_output (TaskList *list, int processorsNumber, enum TypeOrder type);
int add_task_in_TaskList_by_order (TaskList *list, char name[], int time, enum TypeOrder type);
int add_task_in_TaskList (TaskList *list, char name[], int end, int start);
Task* get_last_task_from_TaskList (TaskList *list);
TaskList* create_TaskList();
TaskList* read_file(char arq[], enum TypeOrder type);
void kill_TaskList (TaskList *list);





int main (int argc, char **argv){       //C - valor int quant de args passados pelo prog
                                        //V - vetor de char que contém os args, 1 para cada string passada na linha de comando
    int processorsNumber = atoi(argv[2]);
    int i;
    int hasError;
    TaskList *TaskList_crescente;
    TaskList *TaskList_decrescente;
    enum TypeOrder type;

    if(processorsNumber < 1){
            printf ("TENTE NOVAMENTE...\n\n (ENTRE COM MAIS DE UM PROCESSADOR)\n\n");
    }

    //MENORES PRIMEIRO
    type = CRESCENT;
    TaskList_crescente = read_file(argv[1], type);
    hasError = create_output(TaskList_crescente, processorsNumber, type);
    if(hasError){
        printf("ERRO ENCONTRADO\n");
        return 1;
    }
    kill_TaskList(TaskList_crescente);      //FINALIZA TAREFA



    //MAIORES PRIMEIRO
    type = DESCRESCENT;
    TaskList_decrescente = read_file(argv[1], type);
    if (TaskList_decrescente == NULL){          
        printf("ERRO ENCONTRADO\n");
        return 1;
    }
    hasError = create_output(TaskList_decrescente, processorsNumber, type);
    if(hasError){
        printf("ERRO ENCONTRADO");
        return 1;
    }
    kill_TaskList(TaskList_decrescente);        //FINALIZA TAREFA

}



//TRECHO PARA LEITURA DE ARQUIVO TXT E VERIFICAÇÃO DE ERROS DE LEITURA
TaskList* read_file(char arq[], enum TypeOrder type){
    FILE *input;    
    char name[TASK_NAME_LENGTH];
    int time;

    input = fopen(arq, "r"); //função que lÊ arquivo txt


    //VERIFICAÇÕES
    if(input = NULL){                                   //1. p/ entradas vazias
        printf("ERRO AO ABRIR ESTE ARQUIVO\n");
        return NULL;
    }

    TaskList *list = create_TaskList();                 //2. P/ lista vazia
    if (list == NULL){
        return NULL;
    }

    while(fscanf(input, "%s %d", name, &time)!= EOF){               //ordem para montar o doc caso atenda os paramentos do while
        add_task_in_TaskList_by_order(list, name, time, type);

    }
    fclose(input);
    return list;
}



