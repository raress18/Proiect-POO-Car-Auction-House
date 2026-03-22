cmake_minimum_required(VERSION 4.0)
project(proiect_poo)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(SQLiteCpp)

add_executable(proiect_poo main.cpp
        DataOra.h
        DataOra.cpp
        Participant.cpp
        SpecificatiiTehnice.cpp
        SpecificatiiTehnice.h
        Vehicul.cpp
        Vehicul.h
        Licitatie.cpp
        Licitatie.h
        AuctionManager.cpp
        AuctionManager.h
        Derivate.cpp
        Derivate.h
        Exceptii.h
        Microbuz.cpp
        Microbuz.h
        VehiculFactory.cpp
        VehiculFactory.h
        Templates.h
        DatabaseManager.cpp
        DatabaseManager.h)

target_link_libraries(proiect_poo PRIVATE SQLiteCpp sqlite3)