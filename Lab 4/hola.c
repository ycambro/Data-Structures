/*
Lab #4, #5 y #6

Implementación de una lista simple

- Individual
- Tomar un tema de los que indicó que interesaban al inicio del semestre
- Implementar una lista simple enlazada en C que este relacionada a este tema.
- Debe implementar los siguientes algoritmos: Insertar al final, imprimir, Borrar toda la lista
- Debe incluir un menú en terminal.
- Debe hacer uso de calloc y free
- Duración: 10 días hábiles.

- Entrega: Un archivo .c en el formulario de entrega de ejercicios
Temas que yo envia
nutricion y condicion social
deporte
conocimiento propio
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
struct nodo_lista{
    char* valor;
    struct nodo_lista* siguiente;
};
/*
* Recibe un puntero hacia el primer nodo de una lista
* Imprime los valores de la lista
*/
char* string_indefinido(){
    char* buffer = calloc(88,sizeof(char));
    // recibir el string
    
    scanf("%s",buffer);
    printf("%s\n",buffer);
    long unsigned int tamanno= strlen(buffer);
    printf("tamanno es %lu \n ",tamanno);
    char* entrada= calloc(tamanno+1,sizeof(char));
    strcpy(entrada,buffer);
    printf("Longitud %lu\n",strlen(entrada));
    free(buffer);
    return entrada;
}
void insertar_al_final(struct nodo_lista* primer_nodo,char* valor_a_agregar){
    struct nodo_lista* actual=primer_nodo;
    if (actual->valor==NULL){
        actual->valor=valor_a_agregar;
        return;
    }
    while (actual->siguiente!=NULL)
    {
        actual=actual->siguiente;
    }
    actual -> siguiente= calloc(1,sizeof(struct nodo_lista));
    actual = actual->siguiente;
    actual->valor=valor_a_agregar;
    
    
    
}
void borrar_lista(struct nodo_lista* primer_nodo){
    struct nodo_lista* actual=primer_nodo;
    struct nodo_lista* siguiente=actual->siguiente;
    primer_nodo->valor=NULL;
    primer_nodo->siguiente=NULL;
    while (siguiente!=NULL)
    {
        actual=siguiente;
        siguiente= siguiente->siguiente;
        free(actual);
        
        
    }
    //free(actual);
    free(siguiente);
    
    actual=NULL;
    siguiente=NULL;
    


}
void imprimir_lista(struct nodo_lista* primer_nodo){
    int contador=1;
    if (primer_nodo->valor==NULL){
        printf("Lista Vacia\n\n\n");
        return;
    }
    struct nodo_lista* actual=primer_nodo;
    while (actual->siguiente!=NULL)
    {
        printf("Elemento %d %s \n",contador,actual->valor);
        actual=actual->siguiente;
        contador++;
    }
    printf("Elemento %d %s \n\n\n\n",contador,actual->valor);
    
    //free(actual);
    actual=NULL;
    
    

}
int main()
{
    printf("Bienvenido al sistema de conocimiento propio\n");
    //clrscr();
    struct nodo_lista* primer_nodo=calloc(1,sizeof(struct nodo_lista));
    int opcion;
    int exit=0;
    char* valor;
    while (!exit)
    {
        printf("Seleccione una opcion\n"
        "1.Insertar a la lista de aspectos personales en los que trabajar\n"
        "2.Imprimir lista de trabajo\n"
        "3.Borrar la lista de trabajo\n"
        "4.Salir\n");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1:
            printf("Digite el nuevo aspecto en que trabajara\n");
            valor=string_indefinido();
            printf("%s\n",valor);
            insertar_al_final(primer_nodo,valor);
            clrscr();
            printf("ELemento annadido \n\n\n");
            break;
        case 2:
            clrscr();
            imprimir_lista(primer_nodo);
            
            break;
        case 3:
            borrar_lista(primer_nodo);
            clrscr();
            printf("Lista eliminada\n\n\n");
            break;
        case 4:
            exit=1;
            clrscr();
            printf("Tenga usted un excelente dia\n");
            break;
        
        default:
            clrscr();
            printf("Digite una opcion valida\n");
            break;
        }

        
    }
    
    
    

    
    



    return 0;
}
