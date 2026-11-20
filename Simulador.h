
#ifndef ESTRUCTURASFINAL_SIMULADOR_H
#define ESTRUCTURASFINAL_SIMULADOR_H
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cctype>
#include "SalaUrgencias.h"
#include "ColaTriage.h"
#include "GestorHistorial.h"
using namespace std;

class Simulador
{
private:
    SalaUrgencias sala;
    ColaTriage triage;
    GestorHistorial historial;

    string medicoActual;
    int turnoActual;
    const int max_turnos = 50;
    int turnoGlobalSimulacion;
    int consecutivoCedula;

    int totalPacientesRecibidos;
    int totalPacientesDadosDeAlta;
    int totalPacientesPerdidos;
    int sumaTurnosEsperaRecibidos;
    int sumaMinutosEsperaRecibidos;

    int recibidosTurnoActual;
    int altasTurnoActual;
    int perdidosTurnoActual;

    list <string> nombresBase;
    list <string> apellidosBase;
    list <string> condicionesCriticas;
    list <string> condicionesSeveras;
    list <string> condicionesModeradas;
    list <string> condicionesLeves;
    list <string> condicionesConsulta;

    void inicializarBancoDatos() {
        nombresBase = {"Rafael", "Juan", "Esteban", "Sebastian", "Sofía", "Laura", "Camila", "Andres", "Valentina", "Mateo", "Isabella", "Santiago"};
        apellidosBase = {"Salamanca", "Ruiz", "Mejia", "Velez", "Gomez", "Castro", "Rojas", "Mendoza", "Ortiz", "Silva", "Vargas", "Morales"};

        condicionesCriticas = {"Paro cardiorrespiratorio", "Trauma craneoencefalico severo", "Infarto agudo de miocardio", "Hemorragia interna activa"};
        condicionesSeveras = {"Fractura abierta de femur", "Crisis asmatica grave", "Apendicitis aguda complicada", "Quemadura de segundo grado extensa"};
        condicionesModeradas = {"Dolor abdominal agudo", "Fiebre alta persistente", "Luxacion de hombro", "Deshidratacion moderada"};
        condicionesLeves = {"Esguince de tobillo", "Herida superficial en brazo", "Otitis aguda", "Reaccion alergica leve"};
        condicionesConsulta = {"Control de presion arterial", "Dolor lumbar cronico", "Certificado medico", "Revision de sutura"};
    }

    string obtenerAleatorioDeLista(const list<string>& lista) const
    {
        if (lista.empty()) return "Paciente general";
        int indice = std::rand() % lista.size();
        auto it = lista.begin();
        advance(it, indice);
        return *it;
    }
    void generarPacienreRandom(int gravedadForzada = 0)
    {
        int gravedad = gravedadForzada;
        if (gravedad == 0)
        {
            int dado = (rand() % 100)+1;
            if (dado <= 18) gravedad = 1;
            else if (dado <= 40) gravedad = 2;
            else if (dado <= 68) gravedad = 3;
            else if (dado <= 88) gravedad = 4;
            else gravedad = 5;
        }
        string nombreCompleto = obtenerAleatorioDeLista(nombresBase) + " " + obtenerAleatorioDeLista(apellidosBase);
        string condicion;
        switch (gravedad)
        {
        case 1: condicion = obtenerAleatorioDeLista(condicionesCriticas); break;
        case 2: condicion = obtenerAleatorioDeLista(condicionesSeveras); break;
        case 3: condicion = obtenerAleatorioDeLista(condicionesModeradas); break;
        case 4: condicion = obtenerAleatorioDeLista(condicionesLeves); break;
        default: condicion = obtenerAleatorioDeLista(condicionesConsulta); break;
        }
        string cedula = to_string(consecutivoCedula++);
        Paciente* nuevo = new Paciente(cedula, nombreCompleto, gravedad, condicion,turnoGlobalSimulacion);
        triage.encolarPaciente(nuevo);
    }
    void reiniciarContadoresJornada()
    {
        turnoActual = 1;
        recibidosTurnoActual = 0;
        altasTurnoActual = 0;
        perdidosTurnoActual = 0;
    }
    void procesarFinDeTurno()
    {
        sala.avanzarTurnoCamas();
        list <Paciente*> perdidos = triage.avanzarTurnoEnEspera();
        for (Paciente* p : perdidos)
        {
            cout << "\n El paciente critico" << p->getNombre() << "CC:" << p->getCedula() << "Supero 6 turnos en cola y ha muerto.";
            historial.registrarPerdida(*p,medicoActual,turnoActual);
            totalPacientesPerdidos++;
            perdidosTurnoActual++;
            delete p;
        }

        turnoGlobalSimulacion++;
        if ((rand() % 100) < 65)
        {
            generarPacienreRandom();
        }
        if ((rand() % 100) < 5)
        {
            int camaRandom = (rand() % 10) +1;
            sala.ponerCamaEnMantenimiento(camaRandom, 3);
        }
        turnoActual++;
    }
    void imprimirReporteMedicoFinturno(int turnosUsados)const
    {
        cout << "-Reporte de turno-" << medicoActual << "\n";
        cout << "Pacientes recibidos: " << recibidosTurnoActual << "\n";
        cout << "Pacientes dados de alta: " << altasTurnoActual << "\n";
        cout << "Pacientes perdidos: " << perdidosTurnoActual << "\n";
        cout << "turnos usados:" << turnosUsados << "/" << max_turnos << "\n";
    }
    void imprimirMetricasGlobale()const
    {
        cout << "METRICAS GLOBALES";
        cout << "Total pacientes recibidos en cama: " << totalPacientesRecibidos << "\n";
        cout << "Total pacientes dados de alta: " << totalPacientesDadosDeAlta << "\n";
        cout << "Total pacientes perdidos: " << totalPacientesPerdidos << "\n";

        if (totalPacientesRecibidos > 0)
        {
            double promTurnos = static_cast<double>(sumaTurnosEsperaRecibidos)/totalPacientesRecibidos;
            double promMinutos = static_cast<double>(sumaMinutosEsperaRecibidos)/totalPacientesRecibidos;
            cout << "  Tiempo promedio de espera:         " << fixed << setprecision(1)
                          << promTurnos << " turnos (" << promMinutos << " min)\n";
        } else
        {
            cout << "  Tiempo promedio de espera:         0 turnos (0 min)\n";
        }
        cout << "  Camas desocupadas al finalizar: " << sala.contarCamasDesocupadas() << "/10\n";
        cout << "  Cantidad de medicos participantes: " << historial.cantidadMedicosRegistrados() << "\n";

    }
public:
    Simulador() : sala(10),turnoActual(1),turnoGlobalSimulacion(1),consecutivoCedula(1010),
    totalPacientesRecibidos(0),totalPacientesDadosDeAlta(0),totalPacientesPerdidos(0),
    sumaMinutosEsperaRecibidos(0),sumaTurnosEsperaRecibidos(0),
    recibidosTurnoActual(0),altasTurnoActual(0),perdidosTurnoActual(0)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        inicializarBancoDatos();

        generarPacienreRandom(1);
        generarPacienreRandom(3);
        generarPacienreRandom(4);
    }
    void iniciarJornada(const string& nombreMedico)
    {
        medicoActual = nombreMedico;
        historial.obtenerORegistrarMedico(medicoActual);
        historial.limpiarPilaTurnoActual();
        sala.reiniciarPosicionMedico();
        reiniciarContadoresJornada();

        string lineaEntrada;
        while (turnoActual <= max_turnos)
        {
            cout << "\n--------------------------------------------------------------------------------\n";
            cout << medicoActual << "Turno: " << turnoActual << "/" << max_turnos
                      << "Pacientes en cola: " << triage.cantidadPacientes() << "\n";
            cout << "--------------------------------------------------------------------------------\n";

            sala.imprimirMapaSala();
            cout << "\n";
            sala.imprimirDetalleCamaActual();
            cout << "\n";
            triage.imprimirResumenCola();

            cout << "\n Acciones: [A] Izq  [D] Der  [R] Recibir  [T] Tratar  [X] Alta  [U] Ultimos  [C cedula] Consultar  [O] Cambiar Medico  [E] Terminar\n";
            cout << "Ingrese la accion: ";

            getline(cin, lineaEntrada);
            if (lineaEntrada.empty())continue;

            stringstream ss(lineaEntrada);
            string comando;
            ss >> comando;

            char accion = static_cast<char>(toupper(comando[0]));
            if (accion == 'A')
            {
                if (sala.moverIzquierda())
                {
                    procesarFinDeTurno();
                }else{
                    cout << "Te encuentras en la cama 1 ";
                }
            }
            else if (accion == 'D')
            {
                if (sala.moverDerecha())
                {procesarFinDeTurno();}else
                {
                    cout << "Te encuentras en la cama 10 ";
                }
            }
            else if (accion == 'R')
            {
                NodoCama* cama = sala.getCamaActual();
                if (cama->estado != EstadoCama::VACIA)
                {
                    cout << "No puedes recibir aqui, la cama esta ocupada";
                }else if (triage.estaVacia())
                {
                    cout << "No hay pacientes en cola de prioridad";
                }else
                {
                    Paciente* p = triage.extraerSiguiente();
                    cama->asignarPaciente(p);
                    totalPacientesRecibidos++;
                    recibidosTurnoActual++;
                    sumaMinutosEsperaRecibidos += p->getTurnosEnCola();
                    sumaMinutosEsperaRecibidos += p->getTiempoEspera();

                    cout << "Paciente " << p-> getNombre()<< " (Gravedad" << p->getGravedad()
                    << ") asignado a la cama #" << cama->numeroCama << "\n";
                    procesarFinDeTurno();
                }
            }
            else if (accion == 'T')
            {
                NodoCama* cama = sala.getCamaActual();
                if (cama->estado != EstadoCama::OCUPADA || cama->pacienteActual == nullptr)
                {
                    cout << "No hay ningun paciente en la cama actual para tratar \n";
                }else if (cama->pacienteActual->listoAlta())
                {
                    cout << "El tratamiento fue completado, dalo de alta con [X]";
                }else
                {
                    cama->pacienteActual->aplicarTratamiento();
                    cout << "Tratamiento aplicado a " << cama->pacienteActual->getNombre()
                    << " (" << cama->pacienteActual->getTurnosTratamientoCompletados()
                    << "/" << cama->pacienteActual->getTurnosTratamientoTotales() << ")\n";
                    procesarFinDeTurno();
                }
            }
            else if (accion == 'X')
            {
                NodoCama* cama = sala.getCamaActual();
                if (cama->estado != EstadoCama::OCUPADA||cama->pacienteActual == nullptr)
                {
                    cout << "No hay pacientes en esta cama para dar de alta \n";
                }else if (!cama->pacienteActual->listoAlta())
                {
                    cout << "Aun faltan" << cama->pacienteActual->getTurnnosTratamientoRestantes()
                    << "turnos de tratamiento para dar de alta \n";

                }else
                {
                    Paciente* p = cama->retirarPaciente();
                    historial.registrarAlta(*p, medicoActual,turnoActual);
                    totalPacientesDadosDeAlta++;
                    altasTurnoActual++;

                    cout <<"Alta medica exitosa para " << p->getNombre()
                    << "CC:" << p->getCedula();
                    delete p;
                    procesarFinDeTurno();
                }
            }
            else if (accion == 'U')
            {
                cout <<"\n";
                historial.mostrarPilaUltimosAtendidos(medicoActual);
            }
            else if (accion == 'C')
            {
                string cedulaBuscada;
                ss >> cedulaBuscada;
                if (cedulaBuscada.empty())
                {
                    cout << "Error al buscar la cedula";
                }else
                {
                    cout <<"\n";
                    historial.consultarPacientePorCedula(cedulaBuscada);
                }
            }
            else if (accion == 'O')
            {
                int turnosTrabajados = turnoActual -1;
                historial.registrarJornadaMedico(medicoActual,turnosTrabajados);
                imprimirReporteMedicoFinturno(turnosTrabajados);

                string nuevoMedico;
                cout << "Ingresa el nombre del nuevo medico: ";
                getline(cin, nuevoMedico);
                if (nuevoMedico.empty()) nuevoMedico = "Dr Rafael";

                medicoActual = nuevoMedico;
                historial.obtenerORegistrarMedico(medicoActual);
                historial.limpiarPilaTurnoActual();
                sala.reiniciarPosicionMedico();
                reiniciarContadoresJornada();
                cout << "Turno iniciado para " << medicoActual;
            }
            else if (accion == 'E')
            {
                int turnosTrabajados = turnoActual -1;
                historial.registrarJornadaMedico(medicoActual,turnosTrabajados);
                imprimirReporteMedicoFinturno(turnosTrabajados);
                return;
            }
            else
            {
                cout << "Comando no reconocido";
            }
        }
            historial.registrarJornadaMedico(medicoActual, max_turnos);
            imprimirReporteMedicoFinturno(max_turnos);
        }

void ejecutarMenuPrincipal()
    {
        cout << "\n ---MENU PRINCIPAL---";

        string nombreInicial;
        cout << "Ingrese el nombre del medico inicial: ";
        getline(cin, nombreInicial);
        if (nombreInicial.empty()) nombreInicial = "Dr Rafael";
    iniciarJornada(nombreInicial);

        string opcion;
        while (true)
        {
            cout << "\n---MENU DE ADMINISTRACION---\n";
            cout << "1. Ver metricas globales del programa\n";
            cout << "2. Consultar historial de jornadas de un medico\n";
            cout << "3. Ejecutar auditoria de pacientes perdidos\n";
            cout << "4. Consultar paciente por cedula en Tabla Hash\n";
            cout << "5. Iniciar nueva jornada con un medico\n";
            cout << "0. Salir del simulador\n";
            cout << "> Seleccione una opcion: ";

            getline(cin, opcion);
            if (opcion == "1")
            {
                imprimirMetricasGlobale();
            }else if (opcion == "2")
            {
                historial.listarMedicosRegistrados();
                cout << "Ingrese el nombre exacto del medico: ";
                string med;
                getline(std::cin, med);
                historial.consultarHistorialMedico(med);
            }else if (opcion == "3")
            {
                historial.ejecutarAuditoriaperdidos();
            }else if (opcion == "4")
            {
                cout << "Ingrese la cedula del paciente: ";
                string ced;
                getline(std::cin, ced);
                historial.consultarPacientePorCedula(ced);
            }else if (opcion == "5")
            {
                cout << "Ingrese el nombre del medico para la nueva jornada:";
                string nuevoMed;
                getline(std::cin, nuevoMed);
                if (nuevoMed.empty()) nuevoMed = "Dr Rafael2";
                iniciarJornada(nuevoMed);
            }else if (opcion == "0")
            {
                imprimirMetricasGlobale();
                cout <<"Cerrando simulador";
                break;
            }else
            {
                cout << "Opcion invalida";
            }
        }
    }

};


#endif //ESTRUCTURASFINAL_SIMULADOR_H