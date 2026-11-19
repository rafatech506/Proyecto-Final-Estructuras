cmake_minimum_required(VERSION 4.1)
project(Estructurasfinal)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Estructurasfinal
        Paciente.cpp
        Paciente.h
        RegistroPaciente.cpp
        RegistroPaciente.h
        Medico.cpp
        Medico.h
        NodoCama.cpp
        NodoCama.h
        SalaUrgencias.cpp
        SalaUrgencias.h
        ColaTriage.cpp
        ColaTriage.h)
