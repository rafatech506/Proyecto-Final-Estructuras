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
    int getGravedad() const {return gravedad;}
    string getCondicion() const {return condicion;}
    int getTurnoLlegada() const {return turnoLlegada;}
    int getTurnosEnCola()const {return turnosEnCola;}
    int getTiempoEspera() const {return tiempoEspera;}
    int getTurnosTratamientoTotales() const {return turnosTratamientoTotales;}
    int getTurnnosTratamientoRestantes() const {return turnosTratamientoRestantes;}
    int getTurnosTratamientoCompletados() const{
        return turnosTratamientoTotales - turnosTratamientoRestantes;
    }
void avanzarTurnoRnCola()
    {
        turnosEnCola++;
        tiempoEspera+= 5;
    }
void aplicarTratamiento()
    {
        if (turnosTratamientoRestantes > 0)
        {
            turnosTratamientoRestantes--;
        }
    }
bool listoAlta() const
    {
        return turnosTratamientoRestantes == 0;
    }
bool riesgoCritico()const
    {
        return gravedad == 1 && turnosEnCola >= 5;
    }

bool muerto() const
    {
        return gravedad == 1 && turnosEnCola > 6;
    }

string getTextoGravedad() const
    {
        switch (gravedad)
        {
            case 1: return "CRITICO";
            case 2: return "SEVERO";
            case 3: return "MODERADO";
            case 4: return "LEVE";
            case 5: return "CONSULTA";
            case 6: return "DESCONOCIDO";
        }
    }

};
#endif //ESTRUCTURASFINAL_PACIENTE_H