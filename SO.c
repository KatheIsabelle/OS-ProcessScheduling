#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
char buffer [999];

int main (void){

    int i

    i = open ("tarefas", O_RDONLY);
    write (i, buffer, 999);
    printf("%s", buffer);
    return i;
}