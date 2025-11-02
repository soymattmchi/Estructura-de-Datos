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
    Proceso* siguiente;
};

struct NodoCola {
    int id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};

struct Bloque {
    string proceso;
    int tamanio;
    Bloque* siguiente;
};

// ============================
// FUNCIONES GENERALES
// ============================

int leerEnteros(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingrese solo numeros positivos." << endl;
        } else if (valor < 0) {
            cin.ignore(10000, '\n');
            cout << "No se permiten numeros negativos." << endl;
        } else {
            cin.ignore(10000, '\n');
            return valor;
        }
    }
}

int leerNumero(string mensaje, int min, int max) {
    int n;
    do {
        n = leerEnteros(mensaje);
        if (n < min || n > max)
            cout << "Valor invalido. (" << min << "-" << max << ")" << endl;
    } while (n < min || n > max);
    return n;
}

void mostrarTitulo(string titulo) {
    cout << "\n--- " << titulo << " ---\n";
}

// ============================
// LISTA ENLAZADA
// ============================

void insertarProceso(Proceso*& cabeza, int id, string nombre, int prioridad) {
    Proceso* aux = cabeza;
    while (aux) {
        if (aux->id == id) {
            cout << "El ID ya existe. Intente con otro." << endl;
            return;
        }
        aux = aux->siguiente;
    }

    Proceso* nuevo = new Proceso{id, nombre, prioridad, NULL};
    if (!cabeza) cabeza = nuevo;
    else {
        aux = cabeza;
        while (aux->siguiente) aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    cout << "Proceso agregado correctamente." << endl;
}

void mostrarProcesos(Proceso* cabeza) {
    if (!cabeza) { cout << "No hay procesos." << endl; return; }
    mostrarTitulo("LISTA DE PROCESOS");
    while (cabeza) {
        cout << "ID: " << cabeza->id << " | Nombre: " << cabeza->nombre
             << " | Prioridad: " << cabeza->prioridad << endl;
        cabeza = cabeza->siguiente;
    }
}

void eliminarProceso(Proceso*& cabeza, int id) {
    if (!cabeza) { cout << "Lista vacia." << endl; return; }
    Proceso* actual = cabeza;
    Proceso* anterior = NULL;
    while (actual && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (!actual) { cout << "No encontrado." << endl; return; }
    if (!anterior) cabeza = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    delete actual;
    cout << "Proceso eliminado." << endl;
}

void modificarPrioridad(Proceso* cabeza, int id, int nueva) {
    while (cabeza) {
        if (cabeza->id == id) {
            cabeza->prioridad = nueva;
            cout << "Prioridad actualizada." << endl;
            return;
        }
        cabeza = cabeza->siguiente;
    }
    cout << "No se encontro el proceso." << endl;
}

// ============================
// COLA DE PRIORIDAD
// ============================

void encolar(NodoCola*& frente, NodoCola*& fin, int id, string nombre, int prioridad) {
    NodoCola* nuevo = new NodoCola{id, nombre, prioridad, NULL};
    if (!frente || prioridad > frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
        if (!fin) fin = nuevo;
    } else {
        NodoCola* aux = frente;
        while (aux->siguiente && aux->siguiente->prioridad >= prioridad)
            aux = aux->siguiente;
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
        if (!nuevo->siguiente) fin = nuevo;
    }
}

void mostrarCola(NodoCola* frente) {
    if (!frente) { cout << "Cola vacia." << endl; return; }
    mostrarTitulo("COLA DE PRIORIDAD");
    while (frente) {
        cout << "ID: " << frente->id << " | Nombre: " << frente->nombre
             << " | Prioridad: " << frente->prioridad << endl;
        frente = frente->siguiente;
    }
}

void desencolar(NodoCola*& frente, NodoCola*& fin) {
    if (!frente) { cout << "No hay procesos." << endl; return; }
    cout << "Ejecutando: " << frente->nombre << endl;
    NodoCola* temp = frente;
    frente = frente->siguiente;
    if (!frente) fin = NULL;
    delete temp;
}

// ============================
// PILA DE MEMORIA (RENOMBRADA)
// ============================

void asignarMemoria(Bloque*& tope, string proceso, int tamanio) {
    tope = new Bloque{proceso, tamanio, tope};
    cout << "Memoria asignada a " << proceso << " (" << tamanio << " MB)" << endl;
}

void liberarMemoria(Bloque*& tope) {
    if (!tope) { cout << "No hay memoria asignada." << endl; return; }
    cout << "Liberando memoria de: " << tope->proceso << endl;
    Bloque* temp = tope;
    tope = tope->siguiente;
    delete temp;
}

void mostrarMemoria(Bloque* tope) {
    if (!tope) { cout << "Sin bloques asignados." << endl; return; }
    mostrarTitulo("ESTADO DE MEMORIA");
    while (tope) {
        cout << "Proceso: " << tope->proceso << " | Tamano: " << tope->tamanio << " MB" << endl;
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
    Proceso* lista = NULL;
    NodoCola* frente = NULL;
    NodoCola* fin = NULL;
    Bloque* tope = NULL;
    int opcion;

    do {
        mostrarMenu();
        opcion = leerEnteros("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                int id, pr;
                string nombre;
                id = leerEnteros("ID: ");
                cout << "Nombre: ";
                getline(cin, nombre);
                pr = leerNumero("Prioridad (1-5): ", 1, 5);
                insertarProceso(lista, id, nombre, pr);
                break;
            }
            case 2: {
                int id = leerEnteros("ID a eliminar: ");
                eliminarProceso(lista, id);
                break;
            }
            case 3: mostrarProcesos(lista); break;
            case 4: {
                int id = leerEnteros("ID: ");
                int nueva = leerNumero("Nueva prioridad (1-5): ", 1, 5);
                modificarPrioridad(lista, id, nueva);
                break;
            }
            case 5: {
                if (!lista) cout << "No hay procesos." << endl;
                else {
                    Proceso* aux = lista;
                    while (aux) {
                        encolar(frente, fin, aux->id, aux->nombre, aux->prioridad);
                        aux = aux->siguiente;
                    }
                    cout << "Procesos encolados." << endl;
                }
                break;
            }
            case 6: mostrarCola(frente); break;
            case 7: desencolar(frente, fin); break;
            case 8: {
                string proc;
                int tam;
                cout << "Proceso: ";
                getline(cin, proc);
                tam = leerNumero("Tamano (MB): ", 1, 9999);
                asignarMemoria(tope, proc, tam);
                break;
            }
            case 9: liberarMemoria(tope); break;
            case 10: mostrarMemoria(tope); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}

