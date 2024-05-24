/*
    gcc -c store.c -o store.o
    gcc -c main.c -o main.o
    gcc store.o main.o -o ./programa
*/

#include "store.h"

int main() {
    char store_name[30];
    Print_Title();
    printf("\n\n\n\nInserte el Nombre de su tienda (30 car max.):\n");
    // fgets para poder leer el nombre de la tienda con espacios
    fgets(store_name, sizeof(store_name), stdin);
    // Elimina el carácter de nueva línea que fgets puede incluir
    store_name[strcspn(store_name, "\n")] = 0;
    
    Store* nstore = New_Store(store_name);
    if (!nstore) {
        printf("\nError de memoria");
        return 1;
    }

    Create_Products(nstore,  355, 32.5, 3, "Cereal", "Cereales ");
    Create_Products(nstore,  456, 15.0, 5, "Leche ", "Lácteos  ");
    Create_Products(nstore,  789, 10.0, 10, " Pan  ", "Panadería");
    
    Stack* cart = Create_Stack();
    if (!cart) {
        printf("\nError de memoria");
        Destroy_Store(&nstore);
        return 1;
    }
    
    bool quit = false;
    int option = 0;
    
    do {
        Print_Menu(nstore->store_name);
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                Printf_Inv(nstore);
                break;
                
            case 2: {
                int codebar, stock;
                float price;
                char name[50], tag[30];
                

                printf("Ingrese el código de barras: ");
                scanf("%d", &codebar);
                printf("Ingrese el precio: ");
                scanf("%f", &price);
                printf("Ingrese la cantidad en stock: ");
                scanf("%d", &stock);
                printf("Ingrese el nombre del producto: ");
                getchar(); // Consume el salto de línea pendiente
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Elimina el salto de línea
                printf("Ingrese la etiqueta del producto: ");
                fgets(tag, sizeof(tag), stdin);
                tag[strcspn(tag, "\n")] = 0; // Elimina el salto de línea
                
                Create_Products(nstore, codebar, price, stock, name, tag);
                break;
            }
            case 3: {
                int id;
                printf("Ingrese el ID del producto a comprar: ");
                scanf("%d", &id);
                Node* current = nstore->first;
                while (current != NULL) {
                    if (current->products->id == id) {
                        Stack_Push(cart, current->products);
                        printf("Producto añadido al carrito.\n");
                        break;
                    }
                    current = current->next;
                }
                if (current == NULL) {
                    printf("El producto con ID %d no existe en el inventario.\n", id);
                }
                Print_Cart(cart);
                Remove_Product(nstore, id);
                break;
            }
            case 4: {
                int id;
                printf("Ingrese el ID del producto a eliminar: ");
                scanf("%d", &id);
                Remove_Product(nstore, id);
                break;
            }
            case 5:
                quit = true;
                break;
                
            default:
                printf("Opción no válida. Por favor, ingrese un número entre 1 y 5.\n");
        }
    } while (!quit);
    
    Destroy_Store(&nstore);
    Destroy_Stack(&cart);
    
    return 0;
}
