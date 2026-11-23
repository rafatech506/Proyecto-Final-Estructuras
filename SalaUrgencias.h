//cantidad de camas y posicion de medico
#ifndef ESTRUCTURASFINAL_SALAURGENCIAS_H
#define ESTRUCTURASFINAL_SALAURGENCIAS_H
#include <iostream>
#include <string>
#include "NodoCama.h"
using namespace std;
class SalaUrgencias
{
private:
    NodoCama* cabeza;
    NodoCama* cola;
    NodoCama* posicionMedico;

public:
    SalaUrgencias(int totalCamas = 10): cabeza(nullptr), cola(nullptr),posicionMedico(nullptr)
    {
        for (int i = 1; i <= totalCamas; i++)
        {
            NodoCama* nuevaCama = new NodoCama(i);
            if (cabeza == nullptr)
            {
                cabeza = nuevaCama;
                cola = nuevaCama;
            }else
            {
                cola->Siguiente = nuevaCama;
                nuevaCama->Anterior = cola;
                cola = nuevaCama;
            }
        }


        posicionMedico = cabeza;
    }
    ~SalaUrgencias ()
    {
        NodoCama* actual = cabeza;
        while (actual != nullptr)
        {
            NodoCama* siguienteNodo = actual->Siguiente;
            delete actual;
            actual = siguienteNodo;
        }
        cabeza = nullptr;
        cola = nullptr;
        posicionMedico = nullptr;

    }

    void reiniciarPosicionMedico()
    {
        posicionMedico = cabeza;
    }
    bool moverIzquierda()
    {
        if (posicionMedico != nullptr && posicionMedico->Anterior != nullptr)
        {
            posicionMedico = posicionMedico->Anterior;
            return true;
        }
        return false;
    }

    bool moverDerecha()
    {
        if (posicionMedico != nullptr && posicionMedico->Siguiente != nullptr)
        {
            posicionMedico = posicionMedico->Siguiente;
            return true;
        }
        return false;
    }
    NodoCama* getCamaActual()const
    {
        {return posicionMedico;}
    }

    void avanzarTurnoCamas()
    {
        NodoCama* actual = cabeza;
        while (actual != nullptr)
        {
            actual->actualizarMantenimiento();
            actual = actual->Siguiente;
        }

    }
    void ponerCamaEnMantenimiento(int numeroCama, int turnos)
    {
        NodoCama* actual = cabeza;
        while (actual != nullptr)
        {
            if (actual->numeroCama == numeroCama)
            {
                actual->activarMantenimiento(turnos);
                return;
            }
            actual = actual->Siguiente;
        }
    }
    int contarCamasDesocupadas()const
    {
        int vacias = 0;
        NodoCama* actual = cabeza;
        while (actual != nullptr)
        {
            if (actual->estado== EstadoCama::VACIA)
            {
                vacias++;
            }
            actual = actual->Siguiente;
        }
        return vacias;
    }
    void imprimirMapaSala()const
    {
        NodoCama* actual = cabeza;
        string lineaCamas ="";
        string lineaMedico ="";

        while (actual != nullptr)
        {
            string etiqueta = actual->obtenerEtiquetaVisual();
            lineaCamas += etiqueta;

            int mitad = etiqueta.length() /2;
            if (actual == posicionMedico)
            {
                lineaMedico += string(mitad, ' ') + "M" + string(etiqueta.length() - mitad - 1,' ');
            } else
            {
                lineaMedico += string(etiqueta.length(),' ');
            }
            if (actual->Siguiente != nullptr)
            {
                lineaCamas += "=";
                lineaMedico += " ";
            }
            actual = actual->Siguiente;
        }
        cout << lineaCamas << "\n";
        cout << lineaMedico << "\n";
    }
    void imprimirDetalleCamaActual()const
    {
        if (posicionMedico == nullptr)return;

        cout <<"cama actual: #"<< posicionMedico->numeroCama << " ";
        if (posicionMedico->estado == EstadoCama::VACIA)
        {
            cout <<"(vacia)\n";
        }else if (posicionMedico->estado == EstadoCama::MANTENIMIENTO) {
            cout <<"En manteminiento -"<< posicionMedico->turnosMantenimientoRestantes<< "turnos resntantes)\n";
           } else if (posicionMedico->estado == EstadoCama::OCUPADA && posicionMedico->pacienteActual != nullptr){
             Paciente* p = posicionMedico->pacienteActual;
               cout << p->getNombre() << "(CC: " << p->getCedula()
               << ", gravedad " << p->getGravedad() << ", " << p->getTextoGravedad() << ")\n";
               cout <<" caso: " << p->getCondicion() << "\n";
               cout << "Tratamiento " << p->getTurnosTratamientoCompletados()
               << "/" << p->getTurnosTratamientoTotales() << "turnos completados \n";
        }
    }


    };



#endif //ESTRUCTURASFINAL_SALAURGENCIAS_H

