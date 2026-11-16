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
    int pacientesAtendidos;
    int PacientesPerdidos;

public:
    Medico() : nombre(""), pacientesAtendidos(0), PacientesPerdidos(0){}
    Medico(string nombre):
    nombre(nombre),pacientesAtendidos(0), PacientesPerdidos(0){}

    string getNombre() const{return nombre;}
    const list<int>&getTurnosPorJornada()const{return turnosPorJornada;}
    int getPacientesAtendidos()const{return pacientesAtendidos;}
    int getPacientesPerdidos()const{return PacientesPerdidos;}

    void registrarJornada(int turnosTrabajados)
    {
        turnosPorJornada.push_back(turnosTrabajados);
    }

};


#endif //ESTRUCTURASFINAL_MEDICO_H