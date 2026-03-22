//
// Created by Rares Ionita on 18-Mar-26.
//

#ifndef PROIECT_POO_DATABASEMANAGER_H
#define PROIECT_POO_DATABASEMANAGER_H

#include <SQLiteCpp/SQLiteCpp.h>
#include "AuctionManager.h"
#include "VehiculFactory.h"

class DatabaseManager {
private:
    SQLite::Database db;

public:
    DatabaseManager();

    void incarcaParticipanti(AuctionManager& manager) const;
    void incarcaVehicule(AuctionManager& manager) const;
    void stergeVehicul(const std::string& vin) const;

    void salveazaVehicul(Vehicul* v) const;
    void actualizeazaSoldParticipant(int idParticipant, double sumaAdaugata) const;

};

#endif //PROIECT_POO_DATABASEMANAGER_H