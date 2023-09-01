/*
Realizar un programa C++ que simule una Cola (Queue).
Una Cola (Queue) es una estructura de datos en donde el primero en entrar es el
primero en salir. Para nuestro caso, haremos el problema un poco mas complejo
añadiéndole lo que se conoce como prioridad. En los casos en que una Cola tiene
prioridad se considera esta al momento de insertar un nuevo nodo a la
estructura.

RESTRICCIONES:
A. La Cola debe poder realizar las operaciones Enqueue y Dequeue.
B. Las prioridades van de 0 a 16. En los casos que el usuario decida una
prioridad más alta que 16 se considerara la default, y se insertara el nuevo
nodo al final de la estructura. C. El programa deberá tener un menu con las
opciones para Enqueue y Dequeue, además de poder desplegar todos los elementos
de la cola, provocando Dequeue de toda la estructura Cola. D. Las entradas de
datos del usuario deben ser debidamente validas. E. El programas debe ser lo
suficientemente especializado para informar al usuario cuando la cola esta vacía
*/

#include <iostream>
#include <limits>

using namespace std;

// Struct de cola
struct Queue {
    int dato;
    int priority;
    Queue* next;
};

void Enqueue(Queue*&, Queue*&, int, int);
void Dequeue(Queue*&, Queue*&);
bool empty_queue(Queue*);
void sortPriority(Queue*&, Queue*&);
void addQueue(Queue*&, Queue*&, int, int);
int assignPriority(Queue*, int);
void readInt(int&);

void Enqueue(Queue*& first, Queue*& last, int n, int pr) {
    Queue* newQueue = new Queue();
    newQueue->dato = n;
    newQueue->priority = pr;
    newQueue->next = NULL;
    if (empty_queue(first)) {
        first = newQueue;
    }
    else {
        last->next = newQueue;
    }
    last = newQueue;
}

void sortPriority(Queue*& first, Queue*& last) {
    Queue* aux1, * aux2;
    int nAux, prAux;
    aux1 = first;

    while (aux1->next != NULL) {
        aux2 = aux1->next;

        while (aux2 != NULL) {

            if (aux1->priority >= aux2->priority) {
                prAux = aux1->priority;
                nAux = aux1->dato;

                aux1->priority = aux2->priority;
                aux1->dato = aux2->dato;

                aux2->priority = prAux;
                aux2->dato = nAux;
            }

            aux2 = aux2->next;
        }
        aux1 = aux1->next;
    }
}

void addQueue(Queue*& first, Queue*& last, int n, int pr) {

    Enqueue(first, last, n, pr);
    sortPriority(first, last);
}

void Dequeue(Queue*& first, Queue*& last, int& n, int& pr) {
    n = first->dato;
    pr = first->priority;
    Queue* aux = first;
    if (first == last) {
        first = NULL;
        last = NULL;
    }
    else {
        first = first->next;
    }
    cout << n << endl;
    delete aux;
}

bool empty_queue(Queue* first) { return (first == NULL) ? true : false; }

int assignPriority(Queue* last, int priority) {
    if (priority > 16 || priority < 0) {
            priority = last->priority + 1;
    }

    return priority;
}

void readInt(int& value) {
    while (!(cin >> value)) {
        cout << "Por favor, ingrese un valor entero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void menu() {
    cout << "\n\t Colas con prioridad" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Desplegar elementos (dequeue completo)" << endl;
    cout << "4. Salir" << endl;
    cout << "\n Ingrese la opcion que desee: ";
}

int main() {

    Queue* first = NULL;
    Queue* last = NULL;

    int dato, priority, op;

    do {
        menu();
        readInt(op);

        switch (op) {
        case 1:
            cout << "Digite un numero: ";
            readInt(dato);
            cout << "Digite su prioridad de 0 a 16: ";
            readInt(priority);
            priority = assignPriority(last, priority);
            addQueue(first, last, dato, priority);
            break;

        case 2:
            if (empty_queue(first)) {
                cout << "La cola esta vacia" << endl;
                break;
            }
            else {
                cout << "Dequeue del elemento";
                cout << "Dequeue del elemento con mayor prioridad:" << endl;
                int n, pr;
                Dequeue(first, last, n, pr);
                break;
            }

        case 3:
            if (empty_queue(first)) {
                cout << "La cola esta vacia" << endl;
                break;
            }
            else {
                // Eliminar todos los elementos de la cola
                cout << "Despliegue (dequeue) de todos los elementos de la cola:"
                    << endl;
                while (!empty_queue(first)) {
                    int n, pr;
                    Dequeue(first, last, n, pr);
                }
                break;
            }

        case 4:
            cout << "Saliendo del sistema" << endl;
            break;

        default:
            cout << "Opción no valida" << endl;
            break;
        }

    } while (op != 4);

    return 0;
}