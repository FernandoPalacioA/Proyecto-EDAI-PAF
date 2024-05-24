#ifndef STORE_H
#define STORE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief Estructura para representar un producto en la tienda.
 */
typedef struct Products {
    int id; /**< Identificador único del producto */
    int codebar; /**< Código de barras del producto */
    float price; /**< Precio del producto */
    int stock; /**< Stock disponible del producto */
    char name[50]; /**< Nombre del producto */
    char tag[30]; /**< Etiqueta del producto */
} Products;

/**
 * @brief Estructura para representar un nodo en la lista enlazada de productos.
 */
typedef struct Node {
    struct Products* products; /**< Producto almacenado en el nodo */
    struct Node* next; /**< Puntero al siguiente nodo */
    struct Node* prev; /**< Puntero al nodo previo */
} Node;

/**
 * @brief Estructura para representar una tienda.
 */
typedef struct Store {
    Node* cursor; /**< Puntero al nodo actual en la tienda */
    Node* first; /**< Puntero al primer nodo en la tienda */
    Node* last; /**< Puntero al último nodo en la tienda */
    int len; /**< Longitud de la tienda (cantidad de productos) */
    char store_name[30]; /**< Nombre de la tienda */
} Store;

/**
 * @brief Estructura para representar un nodo en la pila de productos del carrito.
 */
typedef struct StackNode {
    struct Products* product; /**< Producto almacenado en el nodo de la pila */
    struct StackNode* next; /**< Puntero al siguiente nodo en la pila */
} StackNode;

/**
 * @brief Estructura para representar un carrito de compras.
 */
typedef struct Stack {
    StackNode* top; /**< Puntero al nodo superior de la pila (último elemento añadido) */
} Stack;

/**
 * @brief Imprime el título del programa.
 */
void Print_Title();

/**
 * @brief Imprime el menú de opciones de la tienda.
 * @param store_name Nombre de la tienda.
 */
void Print_Menu(char* store_name);

/**
 * @brief Crea un nuevo producto en la tienda.
 * @param nstore Puntero a la tienda donde se agregará el producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */
void Create_Products(Store* nstore, int codebar, float price, int stock, const char *name, const char *tag);

/**
 * @brief Crea un nuevo nodo de producto.
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 * @return Puntero al nuevo nodo creado.
 */
static Node* New_Node(int id, int codebar, float price, int stock, const char *name, const char *tag);

/**
 * @brief Crea un nuevo producto.
 * @param p Puntero al producto a crear.
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */
void Create_Node_Products(Products *p, int id, int codebar, float price, int stock, const char *name, const char *tag);

/**
 * @brief Crea una nueva tienda.
 * @param name Nombre de la tienda.
 * @return Puntero a la tienda creada.
 */
Store* New_Store(const char* name);

/**
 * @brief Destruye una tienda y libera memoria.
 * @param store Puntero a la tienda a destruir.
 */
void Destroy_Store(Store** store);

/**
 * @brief Destruye un nodo de producto y libera memoria.
 * @param node Puntero al nodo a destruir.
 */
void Destroy_Product(Node** node);

/**
 * @brief Elimina un producto de la tienda.
 * @param store Puntero a la tienda.
 * @param id Identificador único del producto a eliminar.
 */
void Remove_Product(Store* store, int id);

/**
 * @brief Imprime el inventario de la tienda.
 * @param store Puntero a la tienda.
 */
void Printf_Inv(Store* store);

/**
 * @brief Crea una nueva pila.
 * @return Puntero a la pila creada.
 */
Stack* Create_Stack();

/**
 * @brief Agrega un producto a la pila (carrito de compras).
 * @param stack Puntero a la pila.
 * @param product Puntero al producto a agregar.
 */
void Stack_Push(Stack* stack, Products* product);

/**
 * @brief Quita y devuelve el producto en la cima de la pila.
 * @param stack Puntero a la pila.
 * @return Puntero al producto en la cima de la pila.
 */
Products* Stack_Pop(Stack* stack);

/**
 * @brief Destruye una pila y libera memoria.
 * @param stack Puntero a la pila a destruir.
 */
void Destroy_Stack(Stack** stack);

/**
 * @brief Imprime el contenido del carrito de compras.
 * @param cart Puntero al carrito de compras.
 */
void Print_Cart(Stack* cart);

/**
 * @brief Calcula el total de los productos en el carrito de compras.
 * @param cart Puntero al carrito de compras.
 * @return Total de los productos en el carrito.
 */
float Calculate_Total(Stack* cart);

#endif
