#include <iostream>
#include <limits>
#include <vector>
#include <memory>

#include "AuctionManager.h"
#include "Derivate.h"
#include "DataOra.h"
#include "SpecificatiiTehnice.h"
//#include "Exceptii.h"
#include "VehiculFactory.h"
#include "Templates.h"
#include "DatabaseManager.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

SpecificatiiTehnice citesteSpecificatii() {
    int cap, putere, comb, cutie, trac;
    cout << "   [Spec] Capacitate (cmc): "; cin >> cap;
    cout << "   [Spec] Putere (CP): "; cin >> putere;
    cout << "   [Spec] Combustibil (0-Benzina, 1-Diesel, 2-Electric): "; cin >> comb;
    cout << "   [Spec] Cutie (0-Manuala, 1-Automata): "; cin >> cutie;
    cout << "   [Spec] Tractiune (0-Fata, 1-Spate, 2-Integrala): "; cin >> trac;
    return {cap, putere, static_cast<TipCombustibil>(comb), static_cast<TipCutie>(cutie), static_cast<Tractiune>(trac)};
}

void demoTemplates(const AuctionManager& manager) {
    cout << "\n============================================\n";
    cout << "   DEMO CERINTE: TEMPLATES & SPECIALIZARE   \n";
    cout << "============================================\n";

    cout << "\n1. Testare Clasa Template (ColectieGenerica):\n";

    ColectieGenerica<string> logActiuni("Audit Log User");
    logActiuni += "Utilizatorul a deschis aplicatia";
    logActiuni += "S-au incarcat vehiculele prin Factory";
    logActiuni += "S-a accesat meniul de template-uri";
    logActiuni.afiseaza();

    ColectieGenerica<double> istoricPreturi("Istoric Preturi Vanzare");
    istoricPreturi += 15000.50;
    istoricPreturi += 3200.00;
    istoricPreturi += 1000000.00;
    istoricPreturi.afiseaza();


    cout << "\n2. Testare Functie Template:\n";

    afiseazaVectorCuTitlu(manager.getListaParticipanti(), "Lista Participanti (Format Standard)");

    afiseazaVectorCuTitlu(manager.getListaLicitatii(), "Lista Licitatii (Format Standard)");

    std::vector<double> comisioane = { 250.50, 1200.00, 45.75, 5500.00 };
    afiseazaVectorCuTitlu(comisioane, "Comisioane Incasate (Format Specializat)");
}


void simuleazaBidWar() {
    cout << "\n==========================================================\n";
    cout << "   SCENARIU SPECIAL: 'THE FERRARI F40' BID WAR \n";
    cout << "==========================================================\n";

    try {
        AuctionManager& manager = AuctionManager::getInstance();
        DataOra dataAcum = DataOra::obtineOraCurenta();
        SpecificatiiTehnice specSuper(6500, 800, BENZINA, AUTOMATA, SPATE);

        manager.adaugaVehiculInParc(
            VehiculFactory::creeazaAutoturism(
                "FERRARI-F40-WAR", "Ferrari", "F40", 1990, 5000, 1500000,
                specSuper, dataAcum, "Colectie Muzeu", true
            )
        );

        manager.inregistrareParticipant(Participant(901, "Seic Petrol", "oil@dubai.ae", 15000000));
        manager.inregistrareParticipant(Participant(902, "Tech CEO", "ceo@silicon.com", 14500000));

        Participant* pSeic = manager.getParticipantById(901);
        Participant* pCEO = manager.getParticipantById(902);

        cout << "[System] Se deschide licitatia pentru Ferrari F40...\n";
        manager.creeazaLicitatie("FERRARI-F40-WAR", dataAcum, 60, "Duelul Titanilor");

        Licitatie* lic = nullptr;
        for(int i=1; i<100; i++) {
             Licitatie* temp = manager.getLicitatieById(i);
             if(temp && temp->getVehicul()->getVIN() == "FERRARI-F40-WAR") {
                 lic = temp;
                 break;
             }
        }

        if (lic && pSeic && pCEO) {
            lic->inscrieParticipant(pSeic);
            lic->inscrieParticipant(pCEO);

            cout << "\n--- START DUEL ---\n";
            cout << "-> Seicul deschide cu 2.0 Milioane!\n";
            lic->plaseazaOferta(pSeic, 2000000);

            cout << "-> CEO raspunde cu 5.0 Milioane!\n";
            lic->plaseazaOferta(pCEO, 5000000);

            cout << "-> Seicul se enerveaza: 10.0 Milioane!\n";
            lic->plaseazaOferta(pSeic, 10000000);

            cout << "-> CEO incearca 15.0 Milioane (dar are 14.5)...\n";
            try {
                lic->plaseazaOferta(pCEO, 15000000);
            } catch (const exception& e) {
                cout << "   [EXCEPTION PRINS]: " << e.what() << "\n";
                cout << "   -> CEO s-a retras.\n";
            }

            cout << "\n--- STATUS FINAL ---\n";
            cout << *lic;
        } else {
            cout << "Eroare: Nu s-a putut initializa duelul.\n";
        }

    } catch (const exception& e) {
        cout << "Eroare in timpul simularii: " << e.what() << endl;
    }
    cout << "==========================================================\n";
}

int main() {
    cout << "===============================================\n";
    cout << "=== SISTEM DE GESTIUNE LICITATII AUTO (v5.0) ===\n";
    cout << "   Patterns: Singleton, Factory, Templates + SQLite \n";
    cout << "===============================================\n\n";

    try {
        AuctionManager& manager = AuctionManager::getInstance("Royal Auction House");

        DatabaseManager dbManager;
        dbManager.incarcaParticipanti(manager);
        dbManager.incarcaVehicule(manager);

        bool running = true;
        int optiune = 0;

        while(running) {
            cout << "\n---------------- MENU ----------------\n";
            cout << "1. Afiseaza Inventar Complet\n";
            cout << "2. Filtreaza (Auto / Moto / Utilitare / Microbuze)\n";
            cout << "3. Creeaza Licitatie (Standard)\n";
            cout << "4. Participa la Licitatie\n";
            cout << "5. SCENARIU COMPLEX: Bid War Ferrari\n";
            cout << "6. Adauga manual un vehicul (Factory)\n";
            cout << "7. DEMO TEMPLATES (Colectie Generica & Specializare)\n";
            cout << "8. Sterge Vehicul COMPLET\n";
            cout << "0. Iesire\n";
            cout << "Selectati: ";

            if (!(cin >> optiune)) {
                cout << "Input invalid!\n";
                clearInput();
                continue;
            }

            switch(optiune) {
                case 1:
                    manager.afiseazaInventar();
                    break;
                case 2:
                    manager.afiseazaAutoturism();
                    cout << "---\n";
                    manager.afiseazaMotocicleta();
                    cout << "---\n";
                    manager.afiseazaAutoutilitara();
                    cout << "---\n";
                    manager.afiseazaMicrobuz();
                    break;
                case 3: {
                    string vin, desc; int durata;
                    cout << "VIN: "; cin >> vin;
                    cout << "Durata (min): "; cin >> durata;
                    cout << "Descriere: "; cin >> desc;
                    try {
                        manager.creeazaLicitatie(vin, DataOra::obtineOraCurenta(), durata, desc);
                    } catch (const exception& e) { cout << e.what() << endl; }
                    break;
                }
                case 4: {
                    int idLic, idPart;
                    cout << "ID Licitatie: "; cin >> idLic;
                    Licitatie* lic = manager.getLicitatieById(idLic);
                    if(!lic) { cout << "Licitatie negasita!\n"; break; }

                    cout << *lic;
                    cout << "ID Participant: "; cin >> idPart;
                    if(Participant* p = manager.getParticipantById(idPart)) {
                        double suma;
                        lic->inscrieParticipant(p);
                        cout << "Suma oferta: "; cin >> suma;
                        lic->plaseazaOferta(p, suma);
                    } else { cout << "Participant negasit!\n"; }
                    break;
                }
                case 5:
                    simuleazaBidWar();
                    break;
                case 6: {
                    cout << "\n>>> ADAUGARE CU FACTORY <<<\n";
                    cout << "Tip (1-Auto, 2-Moto, 3-Duba): ";
                    int tip; cin >> tip;

                    string vin, marca, mod, obs;
                    int an, km, pret;


                    cout << "VIN: "; cin >> ws; getline(cin, vin);
                    cout << "Marca: "; cin >> ws; getline(cin, marca);
                    cout << "Model: "; cin >> ws; getline(cin, mod);

                    cout << "An: "; cin >> an;
                    cout << "KM: "; cin >> km;
                    cout << "Pret: "; cin >> pret;

                    cout << "Obs: "; cin >> ws; getline(cin, obs);


                    SpecificatiiTehnice spec = citesteSpecificatii();

                    try {
                        std::unique_ptr<Vehicul> vNou = nullptr;

                        if(tip == 1) {
                            bool c; cout << "Coupe (0/1): "; cin >> c;
                            vNou = VehiculFactory::creeazaAutoturism(vin, marca, mod, an, km, pret, spec, DataOra::obtineOraCurenta(), obs, c);
                        } else if (tip == 2) {
                            int t; cout << "Tip Moto (0-4): "; cin >> t;
                            vNou = VehiculFactory::creeazaMotocicleta(vin, marca, mod, an, km, pret, spec, DataOra::obtineOraCurenta(), obs, static_cast<TipMotocicleta>(t));
                        } else if (tip == 3) {
                            double masa; cout << "Masa max: "; cin >> masa;
                            vNou = VehiculFactory::creeazaAutoutilitara(vin, marca, mod, an, km, pret, spec, DataOra::obtineOraCurenta(), obs, masa);
                        }

                        if (vNou != nullptr) {
                            dbManager.salveazaVehicul(vNou.get());

                            manager.adaugaVehiculInParc(std::move(vNou));

                            cout << "Vehicul creat si salvat in baza de date!\n";
                        }
                    } catch (const exception& e) {
                        cout << "Eroare creare: " << e.what() << endl;
                    }
                    break;
                }
                case 7:
                    demoTemplates(manager);
                    break;
                case 8: {
                    cout << "\n>>> STERGERE VEHICUL <<<\n";
                    cout << "Introdu VIN-ul vehiculului pe care vrei sa il stergi: ";
                    string vinSters;
                    cin >> ws; getline(cin, vinSters);

                    dbManager.stergeVehicul(vinSters);

                    manager.stergeVehiculDinParc(vinSters);

                    break;
                }
                case 0:
                    running = false;
                    break;
                default:
                    cout << "Optiune invalida.\n";
            }
        }
    }
    catch (const std::exception& e) {
        cerr << "\nCRITICAL ERROR: " << e.what() << endl;
    }

    return 0;
}