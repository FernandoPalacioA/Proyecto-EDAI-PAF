#include"store.h"

static Node* New_Node(int id, int codebar, float price, int stock, const char *name, const char *tag) 
{
    Node* n = (Node*) malloc(sizeof(Node));
    if (n) {
        n->next = n->prev = NULL;
        n->products = (Products*) malloc(sizeof(Products));
        if (n->products) {
            Create_Node_Products(n->products, id, codebar, price, stock, name, tag);
        } else {
            free(n);
            n = NULL;
        }
    }
    return n;
}

void Create_Node_Products(Products *p, int id, int codebar, float price, int stock, const char *name, const char *tag)
{
    p->id = id;
    p->codebar = codebar;
    p->price = price;
    p->stock = stock;
    strcpy(p->name, name);
    strcpy(p->tag, tag);
}

void Create_Products(Store* nstore, int codebar, float price, int stock, const char *name, const char *tag) {
    Node* n = New_Node(nstore->len, codebar, price, stock, name, tag);
    if (!n) {
        printf("Error\n");
        exit(1);
    }
    if (nstore->len == 0) {
        nstore->first = nstore->last = n;
    } else {
        nstore->last->next = n;
        n->prev = nstore->last;
        nstore->last = n;
    }
    nstore->len++;
}

Store* New_Store(const char* name)
{
    Store* s =(Store*) malloc(sizeof(Store));
    if(s)
    {
        s->cursor = s->first = s->last = NULL;
        s->len = 0;
        strcpy(s->store_name,name);
    }
    return s;
}

void Destroy_Store(Store** store) {
    if (store && *store) {
        Node* current = (*store)->first;
        Node* next_node;
        while (current != NULL) {
            next_node = current->next;
            Destroy_Product(&current);
            current = next_node;
        }
        free(*store);
        *store = NULL;
    }
}

void Destroy_Product(Node** node) {
    if (node && *node) {
        free((*node)->products);
        free(*node);
        *node = NULL;
    }
}

void Remove_Product(Store* store, int id) {
    Node* current = store->first;
    while (current != NULL) {
        if (current->products->id == id) {
            if (current == store->first) {
                store->first = current->next;
                if (store->first != NULL) {
                    store->first->prev = NULL;
                }
            } else if (current == store->last) {
                store->last = current->prev;
                store->last->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            store->cursor=current->next;
            while(store->cursor!=NULL)
            {
                store->cursor->products->id--;
                store->cursor=store->cursor->next;
            }
            free(current->products);
            free(current);
            store->len--;
            printf("Producto eliminado del inventario.\n");
            return;
        }
        current = current->next;
    }
    printf("El producto con ID %d no existe en el inventario.\n", id);
}

void Print_Title(){
    printf("\033[38;5;82m\n               _     _\n              | |   (_)\n  ___ __ _ ___| |__  _  ___ _ __ \n / __/ _` / __| '_ \\| |/ _ \\ '__|\n |(_| (_| \\__ \\ | | | |  __/ | \n \\___\\__,_|___/_| |_|_|\\___|_|  \033[0m");
    /*" Imprime lo siguiente:
               _     _           
              | |   (_)          
  ___ __ _ ___| |__  _  ___ _ __ 
 / __/ _` / __| '_ \| |/ _ \ '__|
| (_| (_| \__ \ | | | |  __/ |   
 \___\__,_|___/_| |_|_|\___|_|   
                               
     "*/
}

void Print_Menu(char* store_name)
{
    printf("\n%s\n\n\n(1) Ver Inventario\n(2) Añadir Producto\n(3) Vender Producto\n(4) Remover Producto\n(5) Salir\n",store_name);
}

void Printf_Inv(Store* store)
{
    Node* s=store->first;
    printf("\n|  id   |codebar|  name  |  price | stock  |    tag    |\n");
    while(s!=NULL)
    {
        printf("| %05d |%07d| %s | $%.2f |   %02d   | %s |\n",s->products->id, s->products->codebar, s->products->name, s->products->price, s->products->stock, s->products->tag);
        s=s->next;
    }
}

Stack* Create_Stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack) {
        stack->top = NULL;
    }
    return stack;
}

void Stack_Push(Stack* stack, Products* product) {
    StackNode* n = (StackNode*)malloc(sizeof(StackNode));
    if (n) {
        n->product = (Products*)malloc(sizeof(Products));
        if (n->product) {
            *n->product = *product;
            n->next = stack->top;
            stack->top = n;
        } else {
            free(n);
        }
    }
}

Products* Stack_Pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    StackNode* temp = stack->top;
    Products* product = temp->product;
    stack->top = temp->next;
    free(temp);
    return product;
}

void Destroy_Stack(Stack** stack) {
    if (stack && *stack) {
        StackNode* current = (*stack)->top;
        StackNode* next_node;
        while (current != NULL) {
            next_node = current->next;
            free(current->product);
            free(current);
            current = next_node;
        }
        free(*stack);
        *stack = NULL;
    }
}

void Print_Cart(Stack* cart) {
    StackNode* current = cart->top;
    if (current == NULL) {
        printf("El carrito está vacío.\n");
        return;
    }
    printf("\nCarrito de compras:\n|  id   |codebar|  name  |  price | stock  |    tag    |\n");
    while (current != NULL) {
        printf("| %05d |%07d| %s | $%.2f |   %02d   | %s |\n", current->product->id, current->product->codebar, current->product->name, current->product->price, current->product->stock, current->product->tag);
        current = current->next;
    }
    printf("\nTotal en el carrito: $%.2f\n", Calculate_Total(cart));
}

float Calculate_Total(Stack* cart) {
    float total = 0.0;
    StackNode* current = cart->top;
    while (current != NULL) {
        total += current->product->price;
        current = current->next;
    }
    return total;
}