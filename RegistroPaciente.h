


#ifndef ESTRUCTURASFINAL_REGISTROPACIENTE_H
#define ESTRUCTURASFINAL_REGISTROPACIENTE_H
#include <string>
#include "Paciente.h"
using namespace std;

struct RegistroPaciente
{
string cedula;
    string nombre;
    int gravedad;
    string condicion;
    string estadoFinal;
    string medicoAsignado;
    int turnoResolucion;
    int turnosEsperados;
    int minutosEsperados;

    RegistroPaciente() : gravedad(0), turnoResolucion(0), turnosEsperados(0), minutosEsperados(0){}

     RegistroPaciente(const Paciente& p, string estado, string medico, int turno):
    cedula(p.getCedula()),nombre(p.getNombre()),gravedad(p.getGravedad()),
    condicion(p.getCondicion()),estadoFinal(estado),medicoAsignado(medico),
    turnoResolucion(turno),turnosEsperados(p.getTurnosEnCola()),
    minutosEsperados(p.getTiempoEspera()){}

};

#endif //ESTRUCTURASFINAL_REGISTROPACIENTE_H