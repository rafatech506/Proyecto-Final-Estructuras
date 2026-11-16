// Rafael Salamanca
#ifndef ESTRUCTURASFINAL_PACIENTE_H
#define ESTRUCTURASFINAL_PACIENTE_H
#include <string>
using namespace std;

class Paciente{
private:
    string cedula;
    string nombre;
    int gravedad;
    string condicion;
    int turnoLlegada;
    int turnosEnCola;
    int tiempoEspera;
    int turnosTratamientoTotales;
    int turnosTratamientoRestantes;

public:
    Paciente(string cedula, string nombre, int gravedad, string condicion,int turnoLlegada):
    cedula(cedula),nombre(nombre),gravedad(gravedad),condicion(condicion),turnoLlegada(turnoLlegada),turnosEnCola(0),
    tiempoEspera(0)
    {
        this -> turnosTratamientoTotales = 6 - gravedad;
        this -> turnosTratamientoRestantes = this->turnosTratamientoTotales;
    }

    string getCedula() const {return cedula;}
    string getNombre() const {return nombre;}













};
#endif //ESTRUCTURASFINAL_PACIENTE_H