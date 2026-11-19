
#ifndef ESTRUCTURASFINAL_COLATRIAGE_H
#define ESTRUCTURASFINAL_COLATRIAGE_H
#include <queue>
#include <list>
#include <iostream>
#include <iomanip>
#include "Paciente.h"
#include <deque>
using namespace std;

struct ComparadorPaciente
{
    bool operator()(const Paciente* a, const Paciente* b) const{
        if (a->getGravedad() != b->getGravedad()){
    }
    return a->getTurnoLlegada() > b->getTurnoLlegada();
}
};

    class ColaTriage {
    private:
        priority_queue<Paciente*, deque<Paciente*>,ComparadorPaciente>colaPrioridad;

    public:
        ColaTriage() {}
        ~ColaTriage()
        {
            while (!colaPrioridad.empty())
            {
                Paciente* p = colaPrioridad.top();
                colaPrioridad.top();
                delete p;
            }
        }
        bool estaVacia()const
        {
            return colaPrioridad.empty();
        }
int cantidadPacientes() const
        {
            return static_cast<int>(colaPrioridad.size());
        }
void encolarPaciente(Paciente* p)
        {
            if (p != nullptr)
            {
                colaPrioridad.push(p);
            }
        }
        Paciente* extraerSiguiente()
        {
            if (colaPrioridad.empty())
            {
                return nullptr;
            }
            Paciente* siguiente = colaPrioridad.top();
            colaPrioridad.pop();
            return siguiente;
        }
        list <Paciente*> avanzarTurnoEnEspera()
        {
            queue<Paciente*> colaAuxiliar;
            list<Paciente*> pacientesPerdidos;

        while (!colaPrioridad.empty())
        {
            Paciente* p = colaPrioridad.top();
            colaPrioridad.pop();

            p->avanzarTurnoRnCola();

            if (p->muerto())
            {
                pacientesPerdidos.push_back(p);
            }else
            {
                colaAuxiliar.push(p);
            }
        }
        while (!colaAuxiliar.empty())
        {
            colaPrioridad.push(colaAuxiliar.front());
            colaAuxiliar.pop();
        }
        return pacientesPerdidos;
        }
        void imprimirResumenCola()
        {
            if (colaPrioridad.empty())
            {
                cout << "Cola de prioridad vacia\n";
                return;
            }
            cout << "cola de prioridad (resumen):\n";
            queue<Paciente*> colaAuxiliar;

            int cantG1 = 0, turnosG1 = 0, maxEsperaG1 = 0;
            int cantG2 = 0, turnosG2 = 0;
            int cantG3 = 0, turnosG3 = 0;
            int cantG4 = 0, turnosG4 = 0;
            int cantG5 = 0, turnosG5 = 0;

            while (!colaPrioridad.empty())
            {
                Paciente* p = colaPrioridad.top();
                colaPrioridad.pop();
                colaAuxiliar.push(p);

                int g = p->getGravedad();
                int t = p->getTurnosEnCola();

                if (g == -1)
                {
                    cantG1++;
                    turnosG1 += t;
                    if (t > maxEsperaG1) maxEsperaG1 = t;
                }else if (g == 2)
                {
                    cantG2++;
                    turnosG2 += t;
                }else if (g == 3)
                {
                    cantG3++;
                    turnosG3 += t;
                }else if (g == 4)
                {
                    cantG4++;
                    turnosG4 += t;
                }else if (g == 5){
                    cantG5++;
                    turnosG5 += t;
                }
            }

            while (!colaAuxiliar.empty()){
                colaPrioridad.push(colaAuxiliar.front());
                colaAuxiliar.pop();
            }
            if (cantG1 > 0)
            {
                cout <<"  - "<< cantG1 << (cantG1 == 1 ? " paciente" : " Pacientes")
                << " gravedad 1 (max. esperando " << maxEsperaG1 << "turnos)";
                if (maxEsperaG1 >= 5)
                {
                    cout << "ALERTA CRITICA";
                }
                cout <<"\n";
            }
            if (cantG2 > 0)
            {
                cout << "  - " << cantG2 << (cantG2 == 1 ? " paciente" : " Pacientes")
                << " gravedad 2 (esperando" << fixed << setprecision(1)
                <<(static_cast<double>(turnosG2) / cantG2) << "turnos prom.)\n";
            }
            if (cantG3 > 0)
            {
                cout << "  - " << cantG3 << (cantG3 == 1 ? " paciente" : " Pacientes")
                << " gravedad 3 (esperando" << fixed << setprecision(1)
                <<(static_cast<double>(turnosG3) / cantG3) << "turnos prom.)\n";
            }
            if (cantG4 > 0)
            {
                cout << "  - " << cantG4 << (cantG4 == 1 ? " paciente" : " Pacientes")
                << " gravedad 4 (esperando" << fixed << setprecision(1)
                << (static_cast<double>(turnosG4)/cantG4)<< "turnos prom.)\n";
            }
            if (cantG5 > 0)
            {
                cout << "  - " << cantG5 << (cantG5 == 1 ? " paciente" : " Pacientes")
                << " gravedad 5 (esperando" << fixed << setprecision(1)
                << (static_cast<double>(turnosG5)/cantG5)<< "turnos prom.)\n";
            }


        }





    };



#endif //ESTRUCTURASFINAL_COLATRIAGE_H