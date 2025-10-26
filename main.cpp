#include <iostream>
#include <string>
using namespace std;


// ============================
// ESTRUCTURAS DE DATOS
// ============================

// ----- LISTA ENLAZADA -----
struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
};

// ----- COLA DE PRIORIDAD -----
struct NodoCola {
    int id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};

// ----- PILA DE MEMORIA -----
struct Bloque {
    string proceso;
    int tamanio;
    Bloque* siguiente;
};

// ============================
// FUNCIONES DE LISTA ENLAZADA
// ============================

void insertarProceso(Proceso*& cabeza, int id, string nombre, int prioridad) {
    Proceso* nuevo = new Proceso{id, nombre, prioridad, NULL};

    if (cabeza == NULL)
        cabeza = nuevo;
    else {
        Proceso* aux = cabeza;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    cout << "? Proceso agregado correctamente.\n";
}

void mostrarProcesos(Proceso* cabeza) {
    if (cabeza == NULL) {
        cout << "?? No hay procesos registrados.\n";
        return;
    }
    cout << "\n--- LISTA DE PROCESOS ---\n";
    Proceso* aux = cabeza;
    while (aux != NULL) {
        cout << "ID: " << aux->id
             << " | Nombre: " << aux->nombre
             << " | Prioridad: " << aux->prioridad << endl;
        aux = aux->siguiente;
    }
}

void eliminarProceso(Proceso*& cabeza, int id) {
    if (cabeza == NULL) {
        cout << "?? No hay procesos para eliminar.\n";
        return;
    }

    Proceso* actual = cabeza;
    Proceso* anterior = NULL;

    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "? No se encontró el proceso con ID " << id << ".\n";
        return;
    }

    if (anterior == NULL)
        cabeza = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    delete actual;
    cout << "??? Proceso eliminado correctamente.\n";
}

void modificarPrioridad(Proceso* cabeza, int id, int nuevaPrioridad) {
    Proceso* aux = cabeza;
    while (aux != NULL) {
        if (aux->id == id) {
            aux->prioridad = nuevaPrioridad;
            cout << "?? Prioridad actualizada correctamente.\n";
            return;
        }
        aux = aux->siguiente;
    }
    cout << "? No se encontró el proceso con ID " << id << ".\n";
}

// ============================
// FUNCIONES DE COLA DE PRIORIDAD
// ============================

void encolar(NodoCola*& frente, NodoCola*& fin, int id, string nombre, int prioridad) {
    NodoCola* nuevo = new NodoCola{id, nombre, prioridad, NULL};

    if (frente == NULL || prioridad > frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
        if (fin == NULL) fin = nuevo;
    } else {
        NodoCola* aux = frente;
        while (aux->siguiente != NULL && aux->siguiente->prioridad >= prioridad)
            aux = aux->siguiente;
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
        if (nuevo->siguiente == NULL)
            fin = nuevo;
    }
    cout << "?? Proceso encolado con prioridad " << prioridad << ".\n";
}

void mostrarCola(NodoCola* frente) {
    if (frente == NULL) {
        cout << "?? La cola está vacía.\n";
        return;
    }
    cout << "\n--- COLA DE PRIORIDAD ---\n";
    while (frente != NULL) {
        cout << "ID: " << frente->id
             << " | Nombre: " << frente->nombre
             << " | Prioridad: " << frente->prioridad << endl;
        frente = frente->siguiente;
    }
}

void desencolar(NodoCola*& frente, NodoCola*& fin) {
    if (frente == NULL) {
        cout << "?? No hay procesos en la cola.\n";
        return;
    }
    NodoCola* temp = frente;
    cout << "?? Ejecutando proceso: " << temp->nombre << endl;
    frente = frente->siguiente;
    if (frente == NULL) fin = NULL;
    delete temp;
}

// ============================
// FUNCIONES DE PILA DE MEMORIA
// ============================

void push(Bloque*& tope, string proceso, int tamanio) {
    Bloque* nuevo = new Bloque{proceso, tamanio, tope};
    tope = nuevo;
    cout << "?? Memoria asignada al proceso " << proceso << " (" << tamanio << " MB)\n";
}

void pop(Bloque*& tope) {
    if (tope == NULL) {
        cout << "?? No hay memoria para liberar.\n";
        return;
    }
    Bloque* temp = tope;
    cout << "?? Liberando memoria del proceso: " << temp->proceso << endl;
    tope = tope->siguiente;
    delete temp;
}

void mostrarMemoria(Bloque* tope) {
    if (tope == NULL) {
        cout << "?? No hay bloques de memoria asignados.\n";
        return;
    }
    cout << "\n--- ESTADO DE MEMORIA ---\n";
    while (tope != NULL) {
        cout << "Proceso: " << tope->proceso
             << " | Tamaño: " << tope->tamanio << " MB\n";
        tope = tope->siguiente;
    }
}

// ============================
// FUNCIONES AUXILIARES
// ============================

void pausa() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void limpiarPantalla() {
    // En Dev-C++ puede no limpiar siempre, pero no da error
    system("cls");
}

// ============================
// PROGRAMA PRINCIPAL
// ============================

int main() {
	
	setlocale(LC_CTYPE,"Spanish");
	
    Proceso* lista = NULL;
    NodoCola* frente = NULL;	
    NodoCola* fin = NULL;
    Bloque* tope = NULL;

    int opcion;

    do {
        limpiarPantalla();
        cout << "===== SISTEMA DE GESTIÓN DE PROCESOS =====\n";
        cout << "1. Registrar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Mostrar lista de procesos\n";
        cout << "4. Modificar prioridad de proceso\n";
        cout << "5. Planificar ejecución (encolar)\n";
        cout << "6. Mostrar cola de CPU\n";
        cout << "7. Ejecutar proceso (desencolar)\n";
        cout << "8. Asignar memoria\n";
        cout << "9. Liberar memoria\n";
        cout << "10. Mostrar estado de memoria\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                int id, prioridad;
                string nombre;
                cout << "ID: "; cin >> id;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Prioridad (1-5): "; cin >> prioridad;
                insertarProceso(lista, id, nombre, prioridad);
                pausa();
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese el ID del proceso a eliminar: ";
                cin >> id;
                eliminarProceso(lista, id);
                pausa();
                break;
            }
            case 3:
                mostrarProcesos(lista);
                pausa();
                break;
            case 4: {
                int id, nueva;
                cout << "ID del proceso: "; cin >> id;
                cout << "Nueva prioridad: "; cin >> nueva;
                modificarPrioridad(lista, id, nueva);
                pausa();
                break;
            }
            case 5: {
                if (lista == NULL) {
                    cout << "No hay procesos registrados.\n";
                } else {
                    Proceso* aux = lista;
                    while (aux != NULL) {
                        encolar(frente, fin, aux->id, aux->nombre, aux->prioridad);
                        aux = aux->siguiente;
                    }
                    cout << "Procesos encolados según prioridad.\n";
                }
                pausa();
                break;
            }
            case 6:
                mostrarCola(frente);
                pausa();
                break;
            case 7:
                desencolar(frente, fin);
                pausa();
                break;
            case 8: {
                string proc;
                int tam;
                cout << "Proceso: "; getline(cin, proc);
                cout << "Tamaño (MB): "; cin >> tam;
                push(tope, proc, tam);
                pausa();
                break;
            }
            case 9:
                pop(tope);
                pausa();
                break;
            case 10:
                mostrarMemoria(tope);
                pausa();
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción no válida.\n";
                pausa();
        }
    } while (opcion != 0);

    return 0;
}

