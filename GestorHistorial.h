
#ifndef ESTRUCTURASFINAL_GESTORHISTORIAL_H
#define ESTRUCTURASFINAL_GESTORHISTORIAL_H
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <map>
#include "RegistroPaciente.h"
#include "Medico.h"

class GestorHistorial
{
private:
    stack <RegistroPaciente> pilaUltimosAtendidos;

    unordered_map<string, RegistroPaciente> tablaHashPacientes;

    map<string, Medico> arbolMedicos;

public:
    GestorHistorial(){}

    Medico& obtenerORegistrarMedico(const string& nombreMedico)
    {
        if (arbolMedicos.find(nombreMedico)==arbolMedicos.end())
        {
            arbolMedicos[nombreMedico] = Medico(nombreMedico);
        }
        return arbolMedicos[nombreMedico];
    }

    void registrarJornadaMedico(const string& nombreMedico, int turnosTrabajados)
    {
        Medico& med = obtenerORegistrarMedico(nombreMedico);
        med.registrarJornada(turnosTrabajados);
    }
    int cantidadMedicosRegistrados()const
    {
        return static_cast<int>(arbolMedicos.size());
    }

    void limpiarPilaTurnoActual()
    {
        while (!pilaUltimosAtendidos.empty())
        {
            pilaUltimosAtendidos.pop();
        }
    }
void registrarAlta(const Paciente& p, const string& nombreMedico, int turnoActual)
    {
        RegistroPaciente reg(p, "Dado de alta", nombreMedico, turnoActual);

        pilaUltimosAtendidos.push(reg);
        tablaHashPacientes[p.getCedula()]= reg;
        obtenerORegistrarMedico(nombreMedico). incrementarAtendidos();
    }

    void registrarPerdida(const Paciente& p, const string& nombreMedico, int turnoActual)
    {
        RegistroPaciente reg(p, "perdido (tiempo de espera excedido)", nombreMedico, turnoActual);

        tablaHashPacientes[p.getCedula()]= reg;
        obtenerORegistrarMedico(nombreMedico). incrementarPerdidos();
    }
void mostrarPilaUltimosAtendidos(const string& nombreMedico)const
    {
        if (pilaUltimosAtendidos.empty())
        {
            cout << nombreMedico << ",aun no has dado de alta pacientes en este turno \n";
            return;
        }
        cout << nombreMedico<< ", ultimos pacientes dados de alta: \n";
        stack<RegistroPaciente> copiaPila = pilaUltimosAtendidos;
        int posicion = 1;

        while (!copiaPila.empty())
        {
            const RegistroPaciente& reg = copiaPila.top();
            string etiquetaPos;
            if (posicion == 1) etiquetaPos = "ULTIMO  ";
            else if (posicion == 2) etiquetaPos = "PENULTIMO   ";
            else if (posicion == 3) etiquetaPos = "ANTEPENULTIMO   ";
            else etiquetaPos = "[#" + to_string(posicion) + "]   ";

            cout << "> " << etiquetaPos << reg.nombre
            << " (cc" << reg.cedula << ", gravedad " << reg.gravedad << "\n";

            copiaPila.pop();
            posicion++;
        }
    }
     void consultarPacientePorCedula(const string& cedula)const
    {
        auto it = tablaHashPacientes.find(cedula);
        if (it == tablaHashPacientes.end())
        {
            cout << "no se encuentra un paciente con ese cc \n";
            return;
        }
        const RegistroPaciente& reg = it->second;
        cout << "Resultado de bisuqeda: \n";
        cout << "Cedula: " << reg.cedula << "\n";
        cout << "Nombre: " << reg.nombre << "\n";
        cout << "Gravedad: " << reg.gravedad << "\n";
        cout << "Caso: " << reg.condicion << "\n";
        cout << "Estado: " << reg.estadoFinal << "\n";
        cout << "Atendido/Turno:" << reg.medicoAsignado << "turno" << reg.turnoResolucion << "\n";
        cout << "Tiempo de espera:  " << reg.turnosEsperados << "turnos (" << reg.minutosEsperados << "min \n";
    }
void consultarHistorialMedico(const string& nombreMedico)const
    {
        auto it = arbolMedicos.find(nombreMedico);
        if (it == arbolMedicos.end())
        {
            cout << "El medico " << nombreMedico << "no existe en el sistema \n";
            return;
        }
        const Medico& med = it->second;
        const list<int>& jornadas = med.getTurnosPorJornada();

        cout << "\n Historial de joranadas: " << med.getNombre() << "\n";
        cout << "jornadas trabajadas: " << jornadas.size() << "\n";

        int numJornada = 1;
        for (int turnos : jornadas)
        {
            cout << " jornada #" << numJornada << ": " << turnos << "turnos trabajados";
            numJornada++;
        }
        cout << "pacientes dados de alta en total: " << med.getPacientesAtendidosTotal() << "\n";
        cout << "pacientes perdidos en total:" << med.getPacientesPerdidosTotal() << "\n";
    }
    void listarMedicosRegistrados()const
    {
        cout << "Medicos registrados:\n";
        for (const auto& par : arbolMedicos)
        {
            cout << "[" << par.first << "]";
        }
    }
void ejecutarAuditoriaperdidos()const
    {
        cout <<"-Auditoria Pacientes Perdidos-\n";
        int totalPerdidos = 0;

        for (const auto& par : tablaHashPacientes)
        {
            const RegistroPaciente& reg = par.second;
            if (reg.estadoFinal.find("Perido")!= string::npos)
            {
                totalPerdidos++;
                cout << " * Paciente: " << reg.nombre << "CC:" << reg.cedula << "\n"
                << ") Espera: " << reg.turnosEsperados << "turnos"
                << "Medico de turnos:" << reg.medicoAsignado
                << "turno" << reg.turnoResolucion << ")\n";
            }
        }

        if (totalPerdidos == 0)
        {
            cout << "0 pacientes perdidos";
        }
        else
        {
            cout << "total general de pacientes perdidos: " << totalPerdidos << "\n";
            cout << "perdidos por medico: \n";
            for (const auto& par : arbolMedicos)
            {
                if (par.second.getPacientesPerdidosTotal() > 0)
                {
                    std::cout << "  -> " << par.first << ": "
                              << par.second.getPacientesPerdidosTotal() << " paciente(s) perdido(s)\n";
                }
            }

        }
    }

};


#endif //ESTRUCTURASFINAL_GESTORHISTORIAL_H