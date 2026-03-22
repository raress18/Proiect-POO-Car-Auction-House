#include "DatabaseManager.h"
#include "Derivate.h"
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager()
    : db("auction.db", SQLite::OPEN_READWRITE) {
    db.exec("PRAGMA foreign_keys = ON;");
}

void DatabaseManager::incarcaParticipanti(AuctionManager& manager) const {
    try {
        SQLite::Statement query(db, "SELECT id, nume, email, sold FROM Participanti");
        int count = 0;

        while (query.executeStep()) {
            int id = query.getColumn(0);
            string nume = query.getColumn(1).getString();
            string email = query.getColumn(2).getString();
            double sold = query.getColumn(3).getDouble();

            manager.inregistrareParticipant(Participant(id, nume, email, sold));
            count++;
        }
        cout << " Incarcati " << count << " participanti.\n";
    } catch (std::exception& e) {
        cerr << "Eroare Participanti " << e.what() << endl;
    }
}

void DatabaseManager::incarcaVehicule(AuctionManager& manager) const {
    try {
        SQLite::Statement query(db, "SELECT * FROM Vehicule");
        int count = 0;

        while (query.executeStep()) {
            string vin = query.getColumn("vin").getString();
            string marca = query.getColumn("marca").getString();
            string model = query.getColumn("model").getString();
            int an = query.getColumn("an_fabricatie").getInt();
            int km = query.getColumn("kilometraj").getInt();
            double pret = query.getColumn("pret_initial").getDouble();
            string obs = query.getColumn("observatii").isNull() ? "" : query.getColumn("observatii").getString();

            SpecificatiiTehnice spec(
                query.getColumn("spec_capacitate").getInt(),
                query.getColumn("spec_putere").getInt(),
                static_cast<TipCombustibil>(query.getColumn("spec_combustibil").getInt()),
                static_cast<TipCutie>(query.getColumn("spec_cutie").getInt()),
                static_cast<Tractiune>(query.getColumn("spec_tractiune").getInt())
            );

            string tipVehicul = query.getColumn("tip_vehicul").getString();
            DataOra dataAzi = DataOra::obtineOraCurenta();

            if (tipVehicul == "Auto") {
                bool eCoupe = query.getColumn("e_coupe").getInt();
                manager.adaugaVehiculInParc(VehiculFactory::creeazaAutoturism(vin, marca, model, an, km, pret, spec, dataAzi, obs, eCoupe));
            }
            else if (tipVehicul == "Duba") {
                double masa = query.getColumn("masa_maxima").getDouble();
                manager.adaugaVehiculInParc(VehiculFactory::creeazaAutoutilitara(vin, marca, model, an, km, pret, spec, dataAzi, obs, masa));
            }

            count++;
        }
        cout << "[DB] Incarcate " << count << " vehicule in inventar.\n";
    } catch (std::exception& e) {
        cerr << "[Eroare DB Vehicule] " << e.what() << endl;
    }
}

void DatabaseManager::salveazaVehicul(Vehicul* v) const {
    try {
        SQLite::Statement query(db,
            "INSERT INTO Vehicule (vin, marca, model, an_fabricatie, kilometraj, pret_initial, observatii, "
            "spec_capacitate, spec_putere, spec_combustibil, spec_cutie, spec_tractiune, "
            "tip_vehicul, e_coupe, masa_maxima, tip_moto, nr_locuri) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

        query.bind(1, v->getVIN());
        query.bind(2, v->getMarca());
        query.bind(3, v->getModel());
        query.bind(4, v->getAnFabricatie());
        query.bind(5, v->getKilometraj());
        query.bind(6, v->getPretInitial());
        query.bind(7, v->getObservatii());

        SpecificatiiTehnice spec = v->getSpecificatii();
        query.bind(8, spec.getCapacitate());
        query.bind(9, spec.getPutere());
        query.bind(10, static_cast<int>(spec.getCombustibil()));
        query.bind(11, static_cast<int>(spec.getCutie()));
        query.bind(12, static_cast<int>(spec.getTractiune()));

        if (auto* autoPtr = dynamic_cast<Autoturism*>(v)) {
            query.bind(13, "Auto");
            query.bind(14, autoPtr->getECoupe() ? 1 : 0);
        }
        else if (auto* dubaPtr = dynamic_cast<Autoutilitara*>(v)) {
            query.bind(13, "Duba");
            query.bind(15, dubaPtr->getMasaMaxima());
        }
        else if (auto* motoPtr = dynamic_cast<Motocicleta*>(v)) {
            query.bind(13, "Moto");
            query.bind(16, static_cast<int>(motoPtr->getTipMoto()));
        }
        else {
            query.bind(13, "Altul");
        }

        query.exec();

    } catch (std::exception& e) {
        cerr << "Eroare Salvare Vehicul" << e.what() << endl;
    }
}

void DatabaseManager::actualizeazaSoldParticipant(int idParticipant, double sumaAdaugata) const {
    try {
        SQLite::Statement query(db, "UPDATE Participanti SET sold = sold + ? WHERE id = ?");
        query.bind(1, sumaAdaugata);
        query.bind(2, idParticipant);
        query.exec();

    } catch (std::exception& e) {
        cerr << "Eroare Update Sold " << e.what() << endl;
    }
}

void DatabaseManager::stergeVehicul(const std::string& vin) const {
    try {
        SQLite::Statement query(db, "DELETE FROM Vehicule WHERE vin = ?");
        query.bind(1, vin);

        int randuriAfectate = query.exec();

        if (randuriAfectate > 0) {
            cout << "Vehiculul cu VIN-ul '" << vin << "' a fost sters definitiv din baza de date!\n";
        } else {
            cout << " Eroare: Nu s-a gasit niciun vehicul cu acest VIN in baza de date.\n";
        }
    } catch (std::exception& e) {
        cerr << "Eroare Stergere " << e.what() << endl;
    }
}
