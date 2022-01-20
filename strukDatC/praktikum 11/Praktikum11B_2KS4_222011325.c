#include <stdio.h>
#include <stdlib.h>

struct item{
    int key;
    int value;
};
struct hashtable_item{
    int flag;
    /* flag = 0 : no data
       flag = 1 : there is data
       flag = 2 : previously there was data */
    struct item *data;
};
struct hashtable_item *array;
int max;

// initializing hash table array
void init_array(){
    int i;
    for (i=0; i<max; i++){
        array[i].flag = 0;
        array[i].data = NULL;
    }
}
// to every key, it will generate a corresponding index
int hashcode(int key){
    return (key % max);
}
int size = 0; // size dari hashtable
int size_of_hashtable(){
    return size;
}
void insert(int key, int value){
    int index = hashcode(key);
    int i = index;
    int h = 1;

    // creating new item to insert in the hash table array
    struct item *new_item = malloc(sizeof(struct item*));
    new_item->key = key;
    new_item->value = value;

    // probing through the array until we reach an empty space
    // QUADRATIC PROBING
    while (array[i].flag==1){
        if (array[i].data->key==key){
            /* case where already existing key 
            matches the given key */
            printf("\n Key already exist, "
                   "hence updating its value.\n");
            array[i].data->value = value;
            return;
        }
        i = (index + (h*h)) % max; // forward h^2 steps, h = 1, 2, ...
        h++;
        if (i==index){
            /* if it has been checked one by one until it returns 
               to the initial index, it means the table is full */
            printf("\n Hashtable is full,cannot insert any more item.\n");
            return;
        }
    }
    if (array[i].flag==2){
        printf("\n The data in this index has been deleted,"
                " cannot be filled again.\n"
                " Updating its index..");
        i = (index + (h*h)) % max;;
    }
    array[i].flag = 1;
    array[i].data = new_item;
    printf("\n Key (%d) has been inserted.\n", key);
    size++;
}
void remove_element(int key){
    int index = hashcode(key);
    int i = index;

    /* probing through array until we reach an empty space where
       not even once an element had been present */
    while (array[i].flag != 0){
        if (array[i].flag==1 && array[i].data->key==key){
            // case when data key matches the given key
            array[i].flag = 2;
            array[i].data = NULL;
            size--;
            printf("\n Key (%d) has been removed.\n", key);
            return;
        }
        i = (i+1) % max;
        if (i==index){
            break;
        }
    }
    printf("\n This key does not exist.\n");
}
// to display all the elements of hash table
void display(){
    int i;
    for (i=0; i<max; i++){
        struct item *current = (struct item*) array[i].data;
        if (current == NULL){
            printf("\n Array [%d] has no elements.", i);
        }
        else {
            printf("\n Array [%d] has elements -: %d (key) and %d"
                   " (value).", i, current->key, current->value);
        }
    }
    printf("\n");
}
int main(){
    int choice, key, value, n, c;
    puts("\nImplementation of Hash Table in C with Quadratic Probing");
    puts("---------------------------------------------------------");
    printf("\nCount of data to be stored: ");
    scanf("%d", &max);
    printf("\n");

    array = malloc(max * sizeof(struct hashtable_item));
    init_array();

    do{
        printf("MENU-:"
                "\n1. Inserting item in the Hashtable"
                "\n2. Removing item from the Hashtable"
                "\n3. Check the size of Hashtable"
                "\n4. Display Hashtable"
                "\n Please enter your choice-: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("\nInserting Element in Hashtable\n");
                printf("Enter key-\t: ");
                scanf("%d", &key);
                printf("Enter value-\t: ");
                scanf("%d", &value);
                insert(key, value);
                break;
            case 2:
                printf("\nDeleting in Hashtable\n"
                       "Enter key to delete-: ");
                scanf("%d", &key);
                remove_element(key);
                break;
            case 3:
                n = size_of_hashtable();
                printf("\nSize of Hashtable is-: %d\n", n);
                break;
            case 4:
                display();
                break;
            default:
                printf("\nWrong input.\n");
        }
        printf("\n Do you want to continue (press 1 for yes)-: ");
        scanf("%d", &c);
        printf("\n");
    } while (c==1);
    getchar();

    return 0;
}