cmake_minimum_required(VERSION 4.1)
project(Estructurasfinal)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Estructurasfinal
        Paciente.h
        RegistroPaciente.h
        Medico.h
        NodoCama.h
        SalaUrgencias.h
        ColaTriage.h
        GestorHistorial.h
        Simulador.h
        main.cpp
)
