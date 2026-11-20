#ifndef ESTRUCTURASFINAL_COLATRIAGE_H
#define ESTRUCTURASFINAL_COLATRIAGE_H

#include <list>
#include <iostream>
#include <iomanip>
#include "Paciente.h"

using namespace std;

class ColaTriage {
private:
    list<Paciente*> fila;

public:
    ColaTriage() {}

    ~ColaTriage() {
        for (Paciente* p : fila) {
            delete p;
        }
        fila.clear();
    }

    bool estaVacia() const {
        return fila.empty();
    }

    int cantidadPacientes() const {
        return static_cast<int>(fila.size());
    }

    void encolarPaciente(Paciente* nuevo) {
        if (nuevo == nullptr) return;

        auto it = fila.begin();
        while (it != fila.end() && (*it)->getGravedad() <= nuevo->getGravedad()) {
            ++it;
        }
        fila.insert(it, nuevo);
    }

    Paciente* extraerSiguiente() {
        if (fila.empty()) return nullptr;
        Paciente* siguiente = fila.front();
        fila.pop_front();
        return siguiente;
    }

    list<Paciente*> avanzarTurnoEnEspera() {
        list<Paciente*> perdidos;
        auto it = fila.begin();

        while (it != fila.end()) {
            Paciente* p = *it;
            p->avanzarTurnoRnCola();

            if (p->muerto()) {
                perdidos.push_back(p);
                it = fila.erase(it);
            } else {
                ++it;
            }
        }
        return perdidos;
    }

    void imprimirResumenCola() const {
        if (fila.empty()) {
            cout << "Cola de prioridad vacia\n";
            return;
        }
        cout << "Cola de prioridad (resumen):\n";

        int cantG1 = 0, turnosG1 = 0, maxEsperaG1 = 0;
        int cantG2 = 0, turnosG2 = 0;
        int cantG3 = 0, turnosG3 = 0;
        int cantG4 = 0, turnosG4 = 0;
        int cantG5 = 0, turnosG5 = 0;

        for (const Paciente* p : fila) {
            int g = p->getGravedad();
            int t = p->getTurnosEnCola();

            if (g == 1) {
                cantG1++;
                turnosG1 += t;
                if (t > maxEsperaG1) maxEsperaG1 = t;
            } else if (g == 2) {
                cantG2++;
                turnosG2 += t;
            } else if (g == 3) {
                cantG3++;
                turnosG3 += t;
            } else if (g == 4) {
                cantG4++;
                turnosG4 += t;
            } else if (g == 5) {
                cantG5++;
                turnosG5 += t;
            }
        }

        if (cantG1 > 0) {
            cout << "  - " << cantG1 << (cantG1 == 1 ? " paciente" : " pacientes")
                 << " gravedad 1 (max. esperando " << maxEsperaG1 << " turnos)";
            if (maxEsperaG1 >= 5) {
                cout << " [ALERTA CRITICA]";
            }
            cout << "\n";
        }
        if (cantG2 > 0) {
            cout << "  - " << cantG2 << (cantG2 == 1 ? " paciente" : " pacientes")
                 << " gravedad 2 (esperando " << fixed << setprecision(1)
                 << (static_cast<double>(turnosG2) / cantG2) << " turnos prom.)\n";
        }
        if (cantG3 > 0) {
            cout << "  - " << cantG3 << (cantG3 == 1 ? " paciente" : " pacientes")
                 << " gravedad 3 (esperando " << fixed << setprecision(1)
                 << (static_cast<double>(turnosG3) / cantG3) << " turnos prom.)\n";
        }
        if (cantG4 > 0) {
            cout << "  - " << cantG4 << (cantG4 == 1 ? " paciente" : " pacientes")
                 << " gravedad 4 (esperando " << fixed << setprecision(1)
                 << (static_cast<double>(turnosG4) / cantG4) << " turnos prom.)\n";
        }
        if (cantG5 > 0) {
            cout << "  - " << cantG5 << (cantG5 == 1 ? " paciente" : " pacientes")
                 << " gravedad 5 (esperando " << fixed << setprecision(1)
                 << (static_cast<double>(turnosG5) / cantG5) << " turnos prom.)\n";
        }
    }
};

#endif //ESTRUCTURASFINAL_COLATRIAGE_H