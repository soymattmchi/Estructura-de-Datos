#include <iostream>
#include <string>
using namespace std;

// ============================
// ESTRUCTURAS DE DATOS
// ============================

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso * siguiente;
};

struct NodoCola {
    int id;
    string nombre;
    int prioridad;
    NodoCola * siguiente;
};

struct Bloque {
    string proceso;
    int tamanio;
    Bloque * siguiente;
};

// ============================
// FUNCIONES GENERALES
// ============================

int leerNumero(string mensaje, int min, int max) {
    int n;
    do {
        cout << mensaje;
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Debe ingresar un numero natural.\n";
            continue;
        }
        if (n < min || n > max) {
            cout << "Valor invalido. (" << min << "-" << max << ")\n";
        }
    } while (n < min || n > max);
    return n;
}

int leerID(string mensaje) {
    int id;
    while (true) {
        cout << mensaje;
        cin >> id;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "¡Advertencia! Solo se admiten numeros naturales. Intente nuevamente.\n";
            continue;
        }
        
        if (id <= 0) {
            cout << "¡Advertencia! El ID debe ser un numero natural (mayor que 0). Intente nuevamente.\n";
            continue;
        }
        
        cin.ignore();
        break;
    }
    return id;
}

void mostrarTitulo(string titulo) {
    cout << "\n--- " << titulo << " ---\n";
}

// ============================
// LISTA ENLAZADA
// ============================

void insertarProceso(Proceso*& cabeza, int id, string nombre, int prioridad) {
    Proceso * nuevo = new Proceso{id, nombre, prioridad, NULL};
    if (!cabeza) cabeza = nuevo;
    else {
        Proceso* aux = cabeza;
        while (aux->siguiente) aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    cout << "Proceso agregado.\n";
}

void mostrarProcesos(Proceso* cabeza) {
    if (!cabeza) { cout << "No hay procesos.\n"; return; }
    mostrarTitulo("LISTA DE PROCESOS");
    while (cabeza) {
        cout << "ID: " << cabeza->id << " | Nombre: " << cabeza->nombre
             << " | Prioridad: " << cabeza->prioridad << endl;
        cabeza = cabeza->siguiente;
    }
}

void eliminarProceso(Proceso*& cabeza, int id) {
    if (!cabeza) { cout << "Lista vacia.\n"; return; }
    Proceso * actual = cabeza;
    Proceso * anterior = NULL;
    while (actual && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (!actual) { cout << "No encontrado.\n"; return; }
    if (!anterior) cabeza = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    delete actual;
    cout << "Proceso eliminado.\n";
}

void modificarPrioridad(Proceso* cabeza, int id, int nueva) {
    while (cabeza) {
        if (cabeza->id == id) {
            cabeza->prioridad = nueva;
            cout << "Prioridad actualizada.\n";
            return;
        }
        cabeza = cabeza->siguiente;
    }
    cout << "No se encontro el proceso.\n";
}

// ============================
// COLA DE PRIORIDAD
// ============================

void encolar(NodoCola*& frente, NodoCola*& fin, int id, string nombre, int prioridad) {
    NodoCola * nuevo = new NodoCola{id, nombre, prioridad, NULL};
    if (!frente || prioridad > frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
        if (!fin) fin = nuevo;
    } else {
        NodoCola * aux = frente;
        while (aux->siguiente && aux->siguiente->prioridad >= prioridad)
            aux = aux->siguiente;
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
        if (!nuevo->siguiente) fin = nuevo;
    }
}

void mostrarCola(NodoCola* frente) {
    if (!frente) { cout << "Cola vacia.\n"; return; }
    mostrarTitulo("COLA DE PRIORIDAD");
    while (frente) {
        cout << "ID: " << frente->id << " | Nombre: " << frente->nombre
             << " | Prioridad: " << frente->prioridad << endl;
        frente = frente->siguiente;
    }
}

void desencolar(NodoCola*& frente, NodoCola*& fin) {
    if (!frente) { cout << "No hay procesos.\n"; return; }
    cout << "Ejecutando: " << frente->nombre << endl;
    NodoCola* temp = frente;
    frente = frente->siguiente;
    if (!frente) fin = NULL;
    delete temp;
}

// ============================
// PILA DE MEMORIA
// ============================

void push(Bloque*& tope, string proceso, int tamanio) {
    tope = new Bloque{proceso, tamanio, tope};
    cout << "Memoria asignada a " << proceso << " (" << tamanio << " MB)\n";
}

void pop(Bloque*& tope) {
    if (!tope) { cout << "No hay memoria.\n"; return; }
    cout << "Liberando memoria de: " << tope->proceso << endl;
    Bloque * temp = tope;
    tope = tope->siguiente;
    delete temp;
}

void mostrarMemoria(Bloque* tope) {
    if (!tope) { cout << "Sin bloques asignados.\n"; return; }
    mostrarTitulo("ESTADO DE MEMORIA");
    while (tope) {
        cout << "Proceso: " << tope->proceso << " | Tamanio: " << tope->tamanio << " MB\n";
        tope = tope->siguiente;
    }
}

// ============================
// MENU Y MAIN
// ============================

void mostrarMenu() {
    cout << "\n===== SISTEMA DE GESTION DE PROCESOS =====\n";
    cout << "1. Registrar proceso\n";
    cout << "2. Eliminar proceso\n";
    cout << "3. Mostrar lista de procesos\n";
    cout << "4. Modificar prioridad de proceso\n";
    cout << "5. Planificar ejecucion (encolar)\n";
    cout << "6. Mostrar cola de CPU\n";
    cout << "7. Ejecutar proceso (desencolar)\n";
    cout << "8. Asignar memoria\n";
    cout << "9. Liberar memoria\n";
    cout << "10. Mostrar estado de memoria\n";
    cout << "0. Salir\n";
}

int main() {
    Proceso * lista = NULL;
    NodoCola * frente = NULL;
    NodoCola * fin = NULL;
    Bloque * tope = NULL;
    int opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int id, pr;
                string nombre;
                
                id = leerID("ID: ");
                cout << "Nombre: "; 
                getline(cin, nombre);
                pr = leerNumero("Prioridad (1-5): ", 1, 5);
                insertarProceso(lista, id, nombre, pr);
                break;
            }
            case 2: {
                int id; 
                id = leerID("ID a eliminar: ");
                eliminarProceso(lista, id);
                break;
            }
            case 3: 
                mostrarProcesos(lista); 
                break;
            case 4: {
                int id, nueva;
                id = leerID("ID: ");
                nueva = leerNumero("Nueva prioridad (1-5): ", 1, 5);
                modificarPrioridad(lista, id, nueva);
                break;
            }
            case 5: {
                if (!lista) 
                    cout << "No hay procesos.\n";
                else {
                    Proceso * aux = lista;
                    while (aux) {
                        encolar(frente, fin, aux->id, aux->nombre, aux->prioridad);
                        aux = aux->siguiente;
                    }
                    cout << "Procesos encolados.\n";
                }
                break;
            }
            case 6: 
                mostrarCola(frente); 
                break;
            case 7: 
                desencolar(frente, fin); 
                break;
            case 8: {
                string proc; 
                int tam;
                cin.ignore(); 
                cout << "Proceso: "; 
                getline(cin, proc);
                tam = leerNumero("Tamaño (MB): ", 1, 9999);
                push(tope, proc, tam);
                break;
            }
            case 9: 
                pop(tope); 
                break;
            case 10: 
                mostrarMemoria(tope); 
                break;
            case 0: 
                cout << "Saliendo...\n"; 
                break;
            default: 
                cout << "Opcion invalida.\n";
                cin.clear();
                cin.ignore(10000, '\n');
        }
    } while (opcion != 0);

    return 0;
}
