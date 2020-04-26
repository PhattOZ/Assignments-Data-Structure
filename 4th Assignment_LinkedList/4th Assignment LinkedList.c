#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

int running = 1;
int count = 0;
int sorted = 0;

typedef struct node{

    double data;
    struct node *next;

}linkedList;

linkedList *first, *last;

//Add data to linked list
void add(double data){

    linkedList *ptr;

    ptr = (linkedList*)malloc(sizeof(linkedList));

    ptr->next = NULL;
    ptr->data = data;

    if(first == NULL){

        first = last = ptr;
    }
    else{

        last->next = ptr;
        last = ptr;
    }

    count++;
}

void push(double x){

    linkedList *ptr;

    ptr = (linkedList*)malloc(sizeof(linkedList));
    ptr->data = x;
    ptr->next = NULL;

    if(first == NULL){

        first = last = ptr;
    }
    else{

        ptr->next = first;
        first = ptr;
    }

    count++;
}

//Display all elements currently in the list
void printLinkedList(){

    linkedList *ptr;

    if(first == NULL){

        printf("NULL");
    }
    else{

        ptr = first;

        while(ptr != NULL){

            printf("%.2lf ", ptr->data);
            ptr = ptr->next;
        }
    }

    printf("\n");
}

linkedList* search_unordered(double key){

    linkedList *ptr;

    ptr = first;

    while((ptr != NULL) && (ptr->data != key)){

        ptr = ptr->next;
    }

    return ptr;
}

void scanSort(){

    linkedList *ptr_i, *ptr_j;

    double temp;

    ptr_i = first;

    while(ptr_i->next != NULL){

        ptr_j = ptr_i->next;

        while(ptr_j != NULL){

            if(ptr_j->data < ptr_i->data){

                temp = ptr_j->data;
                ptr_j->data = ptr_i->data;
                ptr_i->data = temp;
            }

            ptr_j = ptr_j->next;
        }

        ptr_i = ptr_i->next;
    }
}

void deleteNode(linkedList *prev, linkedList *ptr){

    if((ptr == first) && (first == last)){

        first = last = NULL;
    }
    else if(ptr == first){

        first = first->next;
    }
    else if(ptr == last){

        last = prev;
        prev->next = NULL;
    }
    else{

        prev->next = ptr->next;
    }

    free(ptr);
}

int deleteConfermation(double key){

    char confirm[32];

    printf("%.2lf found! Confirmation required (y to confirm)\n", key);
    scanf("%s", confirm);


    if(strcmp(confirm, "y") == 0){

        rewind(stdin);
        return 1;
    }
    else{

        rewind(stdin);
        return 0;
    }
}
/*
int searchAndDeleteNode(double key){

    linkedList *prev, *ptr;

    ptr = first;

    if(ptr->data == key){

        if(deleteConfermation(key) == 1){

            first = first->next;
            free(ptr);
            count--;
            return 1;
        }
    }
    else{

        while((ptr != NULL) && (ptr->data != key)){

            prev = ptr;
            ptr = ptr->next;
        }

        if(ptr != NULL){

            if(deleteConfermation(key) == 1){

                if(ptr == last){

                    last = prev;
                }

                prev->next = ptr->next;
                free(ptr);
                count--;
            }
            return 1;
        }
        else{

            return 0;
        }
    }
}
*/

int searchAndDeleteNode(double key){

    linkedList *ptr, *prev;
    int i, found = 0, delCount = 0;

    ptr = first;
    prev = NULL;

    for(i = 0; i < count && ptr != NULL; i++){

        if(ptr->data == key && deleteConfermation(key) == 1){

            deleteNode(prev, ptr);
            delCount++;
        }
        else if(ptr->data == key){

            found = 1;
        }

        prev = ptr;
        ptr = ptr->next;
    }

    if(delCount > 0 || found == 1){

        count -= delCount;
        return 1;
    }
    else{

        return 0;
    }
}

void search(double key){

    linkedList *ptr;
    int i;

    ptr = first;

    for(i = 0; i < count; i++){

        if(ptr->data == key){

            printf("Element %.2lf found\n", key);
            return;
        }

        ptr = ptr->next;
    }

    printf("Cannot find element %.2lf in the list\n", key);
}

void peek(int index){

    int i;

    if(index == 0){

        printf("First data of the list is %.2lf\n", first->data);
    }
    else if(index == -1){

        printf("Last data of the list is %.2lf\n", last->data);
    }
    else{

        linkedList *ptr;
        ptr = first;

        for(i = 0; i < index; i++){

            ptr = ptr->next;
        }

        printf("The element at index[%d] is %.2lf\n", index, ptr->data);
    }
}

//Check if the string is
//Check whether or not the element is a real number
int isRealNumber(char something[]){

    double number;
    char *end;

    number = strtod(something, &end);               //Extract number from the string

    if(strcmp(end, "") == 0){

        return 1;
    }
    else{

        return 0;
    }
}

int isNoParaCommand(char command[]){

    // Index of particular command  0      1       2      3       4       5      6      7      8     9    10   11   12
    char commandList [13][16] = {"list", "end", "sort", "pop", "help", "sqrt", "rec", "neg", "pow", "+", "-", "*", "/"};
    int i;

    for(i = 0; i < 13; i++){

        if(strcmp(command, commandList[i]) == 0){

            return i;
        }
    }

    return -1;
}

int isOneParaCommand(char command[]){

    //Index of the command          0         1        2       3
    char commandList [4][16] = {"delete", "search", "peek", "push"};
    int i;

    for(i = 0; i < 13; i++){

        if(strcmp(command, commandList[i]) == 0){

            return i;
        }
    }

    return -1;
}

int getCommand(){

    char userInput[32];
    char command[16];
    char parameter[8][16];
    char *token;
    int paraCount = -1;
    int i;

    gets(userInput);

    printf("\n");

    //Split string by (SPACE) using STRTOK
    token = strtok(userInput, " ");

    while(token != NULL){

        if(paraCount == -1){

            strcpy(command, token);
            strlwr(command);
            paraCount++;
            token = strtok(NULL, " ");
        }
        else{

            strcpy(parameter[paraCount], token);
            paraCount++;
            token = strtok(NULL, " ");
        }
    }

    if(paraCount == 0 && 0 <= isNoParaCommand(command) && isNoParaCommand(command) <= 12){

        if(isNoParaCommand(command) == 0){                  //Display all elements

            printLinkedList();
        }
        else if(isNoParaCommand(command) == 1){             //Terminate the program

            running = 0;
        }
        else if(isNoParaCommand(command) == 2){             //Sort the list

            if(count == 0){

                printf("No element to be sorted\n");
            }
            else{

                scanSort();
                sorted = 1;
            }
        }
        else if(isNoParaCommand(command) == 3 && count > 0){             //Delete the first element

            deleteNode(NULL, first);
            count--;
        }
        else if(isNoParaCommand(command) == 4){             //Instruction to all commands

            printf("List of commands\n");
            printf("1)ADD [list] add data to the list\n");
            printf("2)INSERT [list] add sorted input to the list, sorted list required\n");
            printf("3)PUSH [n] insert an element to the first index of the list\n");
            printf("4)PEEK [n] display the element at [n] index\n");
            printf("5)DELETE [n] search and delete the element, deletion will required a permission, multiple deletion can be performed\n");
            printf("6)SEARCH [n] search and display the element\n");
            printf("7)SQRT calculate square root of the first element\n");
            printf("8)REC calculate an inverse fraction of the first element\n");
            printf("9)NEG calculate a negative value of the first element\n");
            printf("10)+ - * / add subtract multiply or divide 2nd element by the 1st one\n");
            printf("11)POW raise the 2nd element to the power of 1st element\n");
            printf("12)LIST display all elements in the list\n");
            printf("13)SORT sort the list\n");
            printf("14)HELP display the command list\n");
            printf("15)END terminate the program\n");
        }
        else if(isNoParaCommand(command) == 5){             //Square root of the first data

            if(count == 0){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = sqrt(first->data);
            }
        }
        else if(isNoParaCommand(command) == 6){

            if(count == 0){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = 1 / (first->data);
            }
        }
        else if(isNoParaCommand(command) == 7){

            if(count == 0){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = -(first->data);
            }
        }
        else if(isNoParaCommand(command) == 8){

            if(count < 2){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = pow(((first->next)->data), first->data);
                deleteNode(first, first->next);
                count--;
            }
        }
        else if(isNoParaCommand(command) == 9){

            if(count < 2){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = ((first->next)->data) + (first->data);
                deleteNode(first, first->next);
                count--;
            }
        }
        else if(isNoParaCommand(command) == 10){

            if(count < 2){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = ((first->next)->data) - (first->data);
                deleteNode(first, first->next);
                count--;
            }
        }
        else if(isNoParaCommand(command) == 11){

            if(count < 2){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = ((first->next)->data) * (first->data);
                deleteNode(first, first->next);
                count--;
            }
        }
        else if(isNoParaCommand(command) == 12){

            if(count < 2){

                printf("No element to be calculated!\n");
            }
            else{

                first->data = ((first->next)->data) / (first->data);
                deleteNode(first, first->next);
                count--;
            }
        }
        else{

            printf("Error\n");
        }
    }
    else if(paraCount == 1 && 0 <= isOneParaCommand(command) && isOneParaCommand(command) <= 3){

        if(isRealNumber(parameter[0]) != 1){

            printf("Parameter format is not correct\n");
            return -1;
        }
        else{

            if(isOneParaCommand(command) == 0 && count != 0){           //delete

                int c = searchAndDeleteNode(strtod(parameter[0], NULL));

                if(c == 0){

                    printf("%s not found\n", parameter[0]);
                }
            }
            else if(isOneParaCommand(command) == 1 && count != 0){      //Search

                search(strtod(parameter[0], NULL));
                printf("\n");
            }
            else if(isOneParaCommand(command) == 2 && count != 0){      //peek

                if(strtod(parameter[0], NULL) > (count - 1)){

                    printf("Error. List contains only %d elements\n", count);
                    printf("Only maximum index of [%d] allowed\n", count - 1);
                }
                else if(strtod(parameter[0], NULL) < -1){

                    printf("Parameter format is not correct\n");
                }
                else{

                    peek(strtod(parameter[0], NULL));
                }
            }
            else if(isOneParaCommand(command) == 3){      //Push

                    push(strtod(parameter[0], NULL));
            }
            else{

                printf("The list contains no element. Action cannot be performed\n");
            }
        }
    }
    else if(paraCount != 0 && (strcmp(command, "add") == 0 || strcmp(command, "insert") == 0)){

        for(i = 0; i < paraCount; i ++){

            if(isRealNumber(parameter[i]) != 1){

                printf("Parameter format is not correct\n");
                return -1;
            }
        }

        if(strcmp(command, "add") == 0){

            for(i = 0; i < paraCount; i++){

                add(strtod(parameter[i], NULL));
                sorted = 0;
            }
        }
        else if(strcmp(command, "insert") == 0 && (sorted == 1 || count <= 1)){

            char holder[16];
            int j;

            for(i = 0; i < paraCount; i++){             //Sort the input

                for(j = i + 1; j < paraCount; j++){

                    if(strtod(parameter[i], NULL) > strtod(parameter[j], NULL)){

                        strcpy(holder, parameter[i]);
                        strcpy(parameter[i], parameter[j]);
                        strcpy(parameter[j], holder);
                    }
                }
            }

            for(i = 0; i < paraCount; i++){

                add(strtod(parameter[i], NULL));
                scanSort();
            }

            sorted = 1;
        }
        else if(strcmp(command, "insert") == 0 && sorted != 1){

            printf("Error, Current list hasn't been sorted\n");
        }
    }
    else if((0 <= isOneParaCommand(command) && isOneParaCommand(command) <= 3 && (strcmp(command, "add") == 0 || strcmp(command, "insert") == 0) && 0 <= isNoParaCommand(command) && isNoParaCommand(command) <= 12)){

        printf("Syntax error\n");
    }
    else{

        printf("Error\n");
        return -1;
    }
}

int main(){

    while(running == 1){

        //Use ternary operation to efficiently display the number of elements
        count != 0 ? (printf("Current list contains %d elements> ", count)):(printf("Current list contains no element> ", count));
        printLinkedList();
        printf("\nCommand>");
        getCommand();
        printf("\n");
    }

    printf("Have a nice day!\n");
}


