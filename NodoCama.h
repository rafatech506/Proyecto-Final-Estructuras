#ifndef ESTRUCTURASFINAL_NODOCAMA_H
#define ESTRUCTURASFINAL_NODOCAMA_H
#include <string>
#include "Paciente.h"
using namespace std;

enum class EstadoCama
{
    VACIA,OCUPADA,MANTENIMIENTO
};

class NodoCama
{
public:
    int numeroCama;
    EstadoCama estado;
    Paciente* pacienteActual;
    int turnosMantenimientoRestantes;

    NodoCama* Anterior;
    NodoCama* Siguiente;

    NodoCama(int numero):
    numeroCama(numero),estado(EstadoCama::VACIA),
    pacienteActual(nullptr),turnosMantenimientoRestantes(0),
    Anterior(nullptr),Siguiente(nullptr){}

    ~NodoCama()
    {
        if (pacienteActual != nullptr)
        {
            delete pacienteActual;
            pacienteActual = nullptr;
        }
    }
bool asignarPaciente(Paciente* nuevoPaciente)
    {
        if (estado != EstadoCama::VACIA || nuevoPaciente == nullptr)
        {
            return false;
        }
        pacienteActual = nuevoPaciente;
        estado = EstadoCama::OCUPADA;
        return true;
    }
Paciente* retirarPaciente()
    {
        Paciente* temp = pacienteActual;
        pacienteActual = nullptr;
        estado = EstadoCama::VACIA;
        return temp;
    }

    void activarMantenimiento(int turnos)
    {
        if (estado == EstadoCama::VACIA)
        {
            estado = EstadoCama::MANTENIMIENTO;
            turnosMantenimientoRestantes = turnos;
        }
    }
    void actualizarMantenimiento() {
        if (estado == EstadoCama::MANTENIMIENTO) {
            turnosMantenimientoRestantes--;
            if (turnosMantenimientoRestantes <= 0) {
                turnosMantenimientoRestantes = 0;
                estado = EstadoCama::VACIA;
            }
        }
    }

    std::string obtenerEtiquetaVisual() const {
        std::string etiqueta = "[ #" + std::to_string(numeroCama) + ":";
        if (estado == EstadoCama::VACIA) {
            etiqueta += "V ";
        } else if (estado == EstadoCama::MANTENIMIENTO) {
            etiqueta += "MNT";
        } else if (estado == EstadoCama::OCUPADA && pacienteActual != nullptr) {
            etiqueta += "P" + std::to_string(pacienteActual->getGravedad());
            if (pacienteActual->getGravedad() == 1) {
                etiqueta += "*";
            } else {
                etiqueta += " ";
            }
        }
        etiqueta += "]";
        return etiqueta;
    }



};


#endif //ESTRUCTURASFINAL_NODOCAMA_H