#ifndef ESTRUCTURASFINAL_MEDICO_H
#define ESTRUCTURASFINAL_MEDICO_H
#include <string>
#include <list>
using namespace std;
class Medico
{
private:
    string nombre;
    list<int> turnosPorJornada;
    int pacientesAtendidosTotal;
    int PacientesPerdidosTotal;

public:
    Medico() : nombre(""), pacientesAtendidosTotal(0), PacientesPerdidosTotal(0){}
    Medico(string nombre):
    nombre(nombre),pacientesAtendidosTotal(0), PacientesPerdidosTotal(0){}

    string getNombre() const{return nombre;}
    const list<int>&getTurnosPorJornada()const{return turnosPorJornada;}
    int getPacientesAtendidosTotal()const{return pacientesAtendidosTotal;}
    int getPacientesPerdidosTotal()const{return PacientesPerdidosTotal;}

    void registrarJornada(int turnosTrabajados)
    {
        turnosPorJornada.push_back(turnosTrabajados);
    }
    void incrementarAtendidos() { pacientesAtendidosTotal++; }
    void incrementarPerdidos() { PacientesPerdidosTotal++; }


};


#endif //ESTRUCTURASFINAL_MEDICO_H