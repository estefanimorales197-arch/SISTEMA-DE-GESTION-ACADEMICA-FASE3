#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct NodoEstudiante {
    string codigoEstudiante;
    string nombreEstudiante;
    NodoEstudiante* siguiente;
};

struct NodoAsignatura {
    string codigoAsignatura;
    string nombreAsignatura;
    NodoAsignatura* siguiente;
};

struct NodoNota {
    string codigoEstudiante;
    string codigoAsignatura;
    float notaFinal;
    NodoNota* siguiente;
};

class SistemaAcademico {
private:
    NodoEstudiante* listaEstudiantes;
    NodoAsignatura* listaAsignaturas;
    NodoNota* listaNotas;

public:
    SistemaAcademico() {
        listaEstudiantes = nullptr;
        listaAsignaturas = nullptr;
        listaNotas = nullptr;
    }

    ~SistemaAcademico() {
        while (listaEstudiantes != nullptr) {
            NodoEstudiante* nodoBorrar = listaEstudiantes;
            listaEstudiantes = listaEstudiantes->siguiente;
            delete nodoBorrar;
        }
        while (listaAsignaturas != nullptr) {
            NodoAsignatura* nodoBorrar = listaAsignaturas;
            listaAsignaturas = listaAsignaturas->siguiente;
            delete nodoBorrar;
        }
        while (listaNotas != nullptr) {
            NodoNota* nodoBorrar = listaNotas;
            listaNotas = listaNotas->siguiente;
            delete nodoBorrar;
        }
    }

    bool verificarVacioEstudiantes() {
        return listaEstudiantes == nullptr;
    }

    bool verificarVacioAsignaturas() {
        return listaAsignaturas == nullptr;
    }

    bool verificarVacioNotas() {
        return listaNotas == nullptr;
    }

    NodoEstudiante* buscarEstudiante(string codigo) {
        NodoEstudiante* auxiliar = listaEstudiantes;
        while (auxiliar != nullptr) {
            if (auxiliar->codigoEstudiante == codigo) {
                return auxiliar;
            }
            auxiliar = auxiliar->siguiente;
        }
        return nullptr;
    }

    void agregarEstudiante(string codigo, string nombre) {
        if (buscarEstudiante(codigo) != nullptr) {
            cout << "El estudiante ya existe.\n";
            return;
        }
        NodoEstudiante* nuevoNodo = new NodoEstudiante();
        nuevoNodo->codigoEstudiante = codigo;
        nuevoNodo->nombreEstudiante = nombre;
        nuevoNodo->siguiente = listaEstudiantes;
        listaEstudiantes = nuevoNodo;
        cout << "Estudiante registrado con exito.\n";
    }

    void modificarEstudiante(string codigo, string nuevoNombre) {
        NodoEstudiante* estudianteEncontrado = buscarEstudiante(codigo);
        if (estudianteEncontrado != nullptr) {
            estudianteEncontrado->nombreEstudiante = nuevoNombre;
            cout << "Estudiante modificado con exito.\n";
        } else {
            cout << "Estudiante no encontrado.\n";
        }
    }

    void eliminarEstudiante(string codigo) {
        if (verificarVacioEstudiantes()) return;

        if (listaEstudiantes->codigoEstudiante == codigo) {
            NodoEstudiante* nodoBorrar = listaEstudiantes;
            listaEstudiantes = listaEstudiantes->siguiente;
            delete nodoBorrar;
            eliminarNotasPorEstudiante(codigo);
            cout << "Estudiante eliminado con exito.\n";
            return;
        }

        NodoEstudiante* auxiliar = listaEstudiantes;
        while (auxiliar->siguiente != nullptr && auxiliar->siguiente->codigoEstudiante != codigo) {
            auxiliar = auxiliar->siguiente;
        }

        if (auxiliar->siguiente != nullptr) {
            NodoEstudiante* nodoBorrar = auxiliar->siguiente;
            auxiliar->siguiente = nodoBorrar->siguiente;
            delete nodoBorrar;
            eliminarNotasPorEstudiante(codigo);
            cout << "Estudiante eliminado con exito.\n";
        } else {
            cout << "Estudiante no encontrado.\n";
        }
    }

    void eliminarNotasPorEstudiante(string codigo) {
        while (listaNotas != nullptr && listaNotas->codigoEstudiante == codigo) {
            NodoNota* nodoBorrar = listaNotas;
            listaNotas = listaNotas->siguiente;
            delete nodoBorrar;
        }

        NodoNota* auxiliar = listaNotas;
        while (auxiliar != nullptr && auxiliar->siguiente != nullptr) {
            if (auxiliar->siguiente->codigoEstudiante == codigo) {
                NodoNota* nodoBorrar = auxiliar->siguiente;
                auxiliar->siguiente = nodoBorrar->siguiente;
                delete nodoBorrar;
            } else {
                auxiliar = auxiliar->siguiente;
            }
        }
    }

    NodoAsignatura* buscarAsignatura(string codigo) {
        NodoAsignatura* auxiliar = listaAsignaturas;
        while (auxiliar != nullptr) {
            if (auxiliar->codigoAsignatura == codigo) {
                return auxiliar;
            }
            auxiliar = auxiliar->siguiente;
        }
        return nullptr;
    }

    void agregarAsignatura(string codigo, string nombre) {
        if (buscarAsignatura(codigo) != nullptr) {
            cout << "La asignatura ya existe.\n";
            return;
        }
        NodoAsignatura* nuevoNodo = new NodoAsignatura();
        nuevoNodo->codigoAsignatura = codigo;
        nuevoNodo->nombreAsignatura = nombre;
        nuevoNodo->siguiente = listaAsignaturas;
        listaAsignaturas = nuevoNodo;
        cout << "Asignatura registrada con exito.\n";
    }

    void modificarAsignatura(string codigo, string nuevoNombre) {
        NodoAsignatura* asignaturaEncontrada = buscarAsignatura(codigo);
        if (asignaturaEncontrada != nullptr) {
            asignaturaEncontrada->nombreAsignatura = nuevoNombre;
            cout << "Asignatura modificada con exito.\n";
        } else {
            cout << "Asignatura no encontrada.\n";
        }
    }

    void eliminarAsignatura(string codigo) {
        if (verificarVacioAsignaturas()) return;

        if (listaAsignaturas->codigoAsignatura == codigo) {
            NodoAsignatura* nodoBorrar = listaAsignaturas;
            listaAsignaturas = listaAsignaturas->siguiente;
            delete nodoBorrar;
            eliminarNotasPorAsignatura(codigo);
            cout << "Asignatura eliminada con exito.\n";
            return;
        }

        NodoAsignatura* auxiliar = listaAsignaturas;
        while (auxiliar->siguiente != nullptr && auxiliar->siguiente->codigoAsignatura != codigo) {
            auxiliar = auxiliar->siguiente;
        }

        if (auxiliar->siguiente != nullptr) {
            NodoAsignatura* nodoBorrar = auxiliar->siguiente;
            auxiliar->siguiente = nodoBorrar->siguiente;
            delete nodoBorrar;
            eliminarNotasPorAsignatura(codigo);
            cout << "Asignatura eliminada con exito.\n";
        } else {
            cout << "Asignatura no encontrada.\n";
        }
    }

    void eliminarNotasPorAsignatura(string codigo) {
        while (listaNotas != nullptr && listaNotas->codigoAsignatura == codigo) {
            NodoNota* nodoBorrar = listaNotas;
            listaNotas = listaNotas->siguiente;
            delete nodoBorrar;
        }

        NodoNota* auxiliar = listaNotas;
        while (auxiliar != nullptr && auxiliar->siguiente != nullptr) {
            if (auxiliar->siguiente->codigoAsignatura == codigo) {
                NodoNota* nodoBorrar = auxiliar->siguiente;
                auxiliar->siguiente = nodoBorrar->siguiente;
                delete nodoBorrar;
            } else {
                auxiliar = auxiliar->siguiente;
            }
        }
    }

    NodoNota* buscarNota(string codEstudiante, string codAsignatura) {
        NodoNota* auxiliar = listaNotas;
        while (auxiliar != nullptr) {
            if (auxiliar->codigoEstudiante == codEstudiante && auxiliar->codigoAsignatura == codAsignatura) {
                return auxiliar;
            }
            auxiliar = auxiliar->siguiente;
        }
        return nullptr;
    }

    void agregarNota(string codEstudiante, string codAsignatura, float calificacion) {
        if (buscarEstudiante(codEstudiante) == nullptr) {
            cout << "El estudiante no existe.\n";
            return;
        }
        if (buscarAsignatura(codAsignatura) == nullptr) {
            cout << "La asignatura no existe.\n";
            return;
        }
        if (calificacion < 0.0f || calificacion > 5.0f) {
            cout << "La calificacion debe estar entre 0.0 y 5.0.\n";
            return;
        }

        if (buscarNota(codEstudiante, codAsignatura) != nullptr) {
            cout << "Ya existe una nota para este estudiante y asignatura.\n";
            return;
        }

        NodoNota* nuevoNodo = new NodoNota();
        nuevoNodo->codigoEstudiante = codEstudiante;
        nuevoNodo->codigoAsignatura = codAsignatura;
        nuevoNodo->notaFinal = calificacion;
        nuevoNodo->siguiente = listaNotas;
        listaNotas = nuevoNodo;
        cout << "Nota registrada con exito.\n";
    }

    void modificarNota(string codEstudiante, string codAsignatura, float nuevaCalificacion) {
        if (nuevaCalificacion < 0.0f || nuevaCalificacion > 5.0f) {
            cout << "La calificacion debe estar entre 0.0 y 5.0.\n";
            return;
        }
        NodoNota* notaEncontrada = buscarNota(codEstudiante, codAsignatura);
        if (notaEncontrada != nullptr) {
            notaEncontrada->notaFinal = nuevaCalificacion;
            cout << "Nota modificada con exito.\n";
        } else {
            cout << "Registro de nota no encontrado.\n";
        }
    }

    void eliminarNota(string codEstudiante, string codAsignatura) {
        if (verificarVacioNotas()) return;

        if (listaNotas->codigoEstudiante == codEstudiante && listaNotas->codigoAsignatura == codAsignatura) {
            NodoNota* nodoBorrar = listaNotas;
            listaNotas = listaNotas->siguiente;
            delete nodoBorrar;
            cout << "Nota eliminada con exito.\n";
            return;
        }

        NodoNota* auxiliar = listaNotas;
        while (auxiliar->siguiente != nullptr && 
               !(auxiliar->siguiente->codigoEstudiante == codEstudiante && auxiliar->siguiente->codigoAsignatura == codAsignatura)) {
            auxiliar = auxiliar->siguiente;
        }

        if (auxiliar->siguiente != nullptr) {
            NodoNota* nodoBorrar = auxiliar->siguiente;
            auxiliar->siguiente = nodoBorrar->siguiente;
            delete nodoBorrar;
            cout << "Nota eliminada con exito.\n";
        } else {
            cout << "Registro de nota no encontrado.\n";
        }
    }

    void listarEstudiantesAprobados(string codAsignatura) {
        NodoAsignatura* asignaturaEncontrada = buscarAsignatura(codAsignatura);
        if (asignaturaEncontrada == nullptr) {
            cout << "La asignatura no existe.\n";
            return;
        }

        cout << "\n=============================================\n";
        cout << " ESTUDIANTES APROBADOS - " << asignaturaEncontrada->nombreAsignatura << "\n";
        cout << "=============================================\n";

        NodoNota* auxiliar = listaNotas;
        bool hayAprobados = false;

        while (auxiliar != nullptr) {
            if (auxiliar->codigoAsignatura == codAsignatura && auxiliar->notaFinal >= 3.0f) {
                NodoEstudiante* estudianteEncontrado = buscarEstudiante(auxiliar->codigoEstudiante);
                if (estudianteEncontrado != nullptr) {
                    cout << "Codigo: " << estudianteEncontrado->codigoEstudiante 
                         << " | Nombre: " << estudianteEncontrado->nombreEstudiante 
                         << " | Nota: " << fixed << setprecision(1) << auxiliar->notaFinal << "\n";
                    hayAprobados = true;
                }
            }
            auxiliar = auxiliar->siguiente;
        }

        if (!hayAprobados) {
            cout << "No hay estudiantes aprobados en esta asignatura.\n";
        }
    }

    void listarEstudiantesReprobados(string codAsignatura) {
        NodoAsignatura* asignaturaEncontrada = buscarAsignatura(codAsignatura);
        if (asignaturaEncontrada == nullptr) {
            cout << "La asignatura no existe.\n";
            return;
        }

        cout << "\n=============================================\n";
        cout << " ESTUDIANTES REPROBADOS - " << asignaturaEncontrada->nombreAsignatura << "\n";
        cout << "=============================================\n";

        NodoNota* auxiliar = listaNotas;
        bool hayReprobados = false;

        while (auxiliar != nullptr) {
            if (auxiliar->codigoAsignatura == codAsignatura && auxiliar->notaFinal < 3.0f) {
                NodoEstudiante* estudianteEncontrado = buscarEstudiante(auxiliar->codigoEstudiante);
                if (estudianteEncontrado != nullptr) {
                    bool puedeHabilitar = (auxiliar->notaFinal >= 2.0f);
                    cout << "Codigo: " << estudianteEncontrado->codigoEstudiante 
                         << " | Nombre: " << estudianteEncontrado->nombreEstudiante 
                         << " | Nota: " << fixed << setprecision(1) << auxiliar->notaFinal 
                         << " | Habilita: " << (puedeHabilitar ? "SI" : "NO") << "\n";
                    hayReprobados = true;
                }
            }
            auxiliar = auxiliar->siguiente;
        }

        if (!hayReprobados) {
            cout << "No hay estudiantes reprobados en esta asignatura.\n";
        }
    }
};

int main() {
    SistemaAcademico sistema;
    int opcion;

    do {
        cout << "\n=============================================\n";
        cout << "     SISTEMA DE GESTION ACADEMICA (FASE 3)  \n";
        cout << "=============================================\n";
        cout << "1.  Agregar Estudiante\n";
        cout << "2.  Modificar Estudiante\n";
        cout << "3.  Eliminar Estudiante\n";
        cout << "4.  Buscar Estudiante\n";
        cout << "5.  Agregar Asignatura\n";
        cout << "6.  Modificar Asignatura\n";
        cout << "7.  Eliminar Asignatura\n";
        cout << "8.  Buscar Asignatura\n";
        cout << "9.  Registrar Nota\n";
        cout << "10. Modificar Nota\n";
        cout << "11. Eliminar Nota\n";
        cout << "12. Reporte: Estudiantes Aprobados\n";
        cout << "13. Reporte: Estudiantes Reprobados\n";
        cout << "0.  Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == 1) {
            string cod, nom;
            cout << "Ingrese codigo del estudiante: ";
            getline(cin, cod);
            cout << "Ingrese nombre del estudiante: ";
            getline(cin, nom);
            sistema.agregarEstudiante(cod, nom);
        } else if (opcion == 2) {
            string cod, nom;
            cout << "Ingrese codigo del estudiante a modificar: ";
            getline(cin, cod);
            cout << "Ingrese nuevo nombre: ";
            getline(cin, nom);
            sistema.modificarEstudiante(cod, nom);
        } else if (opcion == 3) {
            string cod;
            cout << "Ingrese codigo del estudiante a eliminar: ";
            getline(cin, cod);
            sistema.eliminarEstudiante(cod);
        } else if (opcion == 4) {
            string cod;
            cout << "Ingrese codigo del estudiante a buscar: ";
            getline(cin, cod);
            NodoEstudiante* estudianteEncontrado = sistema.buscarEstudiante(cod);
            if (estudianteEncontrado != nullptr) {
                cout << "Estudiante encontrado -> Codigo: " << estudianteEncontrado->codigoEstudiante 
                     << " | Nombre: " << estudianteEncontrado->nombreEstudiante << "\n";
            } else {
                cout << "Estudiante no encontrado.\n";
            }
        } else if (opcion == 5) {
            string cod, nom;
            cout << "Ingrese codigo de la asignatura: ";
            getline(cin, cod);
            cout << "Ingrese nombre de la asignatura: ";
            getline(cin, nom);
            sistema.agregarAsignatura(cod, nom);
        } else if (opcion == 6) {
            string cod, nom;
            cout << "Ingrese codigo de la asignatura a modificar: ";
            getline(cin, cod);
            cout << "Ingrese nuevo nombre: ";
            getline(cin, nom);
            sistema.modificarAsignatura(cod, nom);
        } else if (opcion == 7) {
            string cod;
            cout << "Ingrese codigo de la asignatura a eliminar: ";
            getline(cin, cod);
            sistema.eliminarAsignatura(cod);
        } else if (opcion == 8) {
            string cod;
            cout << "Ingrese codigo de la asignatura a buscar: ";
            getline(cin, cod);
            NodoAsignatura* asignaturaEncontrada = sistema.buscarAsignatura(cod);
            if (asignaturaEncontrada != nullptr) {
                cout << "Asignatura encontrada -> Codigo: " << asignaturaEncontrada->codigoAsignatura 
                     << " | Nombre: " << asignaturaEncontrada->nombreAsignatura << "\n";
            } else {
                cout << "Asignatura no encontrada.\n";
            }
        } else if (opcion == 9) {
            string codEst, codAsig;
            float cal;
            cout << "Ingrese codigo del estudiante: ";
            getline(cin, codEst);
            cout << "Ingrese codigo de la asignatura: ";
            getline(cin, codAsig);
            cout << "Ingrese calificacion (0.0 a 5.0): ";
            cin >> cal;
            sistema.agregarNota(codEst, codAsig, cal);
        } else if (opcion == 10) {
            string codEst, codAsig;
            float cal;
            cout << "Ingrese codigo del estudiante: ";
            getline(cin, codEst);
            cout << "Ingrese codigo de la asignatura: ";
            getline(cin, codAsig);
            cout << "Ingrese nueva calificacion (0.0 a 5.0): ";
            cin >> cal;
            sistema.modificarNota(codEst, codAsig, cal);
        } else if (opcion == 11) {
            string codEst, codAsig;
            cout << "Ingrese codigo del estudiante: ";
            getline(cin, codEst);
            cout << "Ingrese codigo de la asignatura: ";
            getline(cin, codAsig);
            sistema.eliminarNota(codEst, codAsig);
        } else if (opcion == 12) {
            string codAsig;
            cout << "Ingrese el codigo de la asignatura para consultar aprobados: ";
            getline(cin, codAsig);
            sistema.listarEstudiantesAprobados(codAsig);
        } else if (opcion == 13) {
            string codAsig;
            cout << "Ingrese el codigo de la asignatura para consultar reprobados: ";
            getline(cin, codAsig);
            sistema.listarEstudiantesReprobados(codAsig);
        } else if (opcion != 0) {
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}
