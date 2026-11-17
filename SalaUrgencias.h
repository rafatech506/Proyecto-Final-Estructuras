
#ifndef ESTRUCTURASFINAL_SALAURGENCIAS_H
#define ESTRUCTURASFINAL_SALAURGENCIAS_H
#include <iostream>
#include <string>
#include "NodoCama.h"
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
    }




};


#endif //ESTRUCTURASFINAL_SALAURGENCIAS_H

