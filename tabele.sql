CREATE TABLE Participanti (
    id INTEGER PRIMARY KEY,
    nume TEXT NOT NULL,
    email TEXT NOT NULL,
    sold REAL NOT NULL CHECK (sold >= 0)
);

CREATE TABLE Vehicule (
    vin TEXT PRIMARY KEY,
    marca TEXT NOT NULL,
    model TEXT NOT NULL,
    an_fabricatie INTEGER NOT NULL,
    kilometraj INTEGER NOT NULL,
    pret_initial REAL NOT NULL,
    observatii TEXT,

    -- Specificatii Tehnice
    spec_capacitate INTEGER NOT NULL,
    spec_putere INTEGER NOT NULL,
    spec_combustibil INTEGER NOT NULL, -- 0=Benzina, 1=Diesel, 2=Electric, 3=Hibrid, 4=GPL
    spec_cutie INTEGER NOT NULL,       -- 0=Manuala, 1=Automata
    spec_tractiune INTEGER NOT NULL,   -- 0=Fata, 1=Spate, 2=Integrala

    tip_vehicul TEXT NOT NULL,         -- Valori: 'Auto', 'Duba', 'Moto', 'Microbuz'

    e_coupe INTEGER,        -- 1 (True) sau 0 (False). Doar pentru Autoturism
    masa_maxima REAL,       -- Doar pentru Autoutilitara
    tip_moto INTEGER,       -- 0=Cruiser, 1=Sport, 2=Touring etc. Doar pt Motocicleta
    nr_locuri INTEGER       -- Doar pentru Microbuz
);

CREATE TABLE Licitatii (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    vehicul_vin TEXT NOT NULL,

    castigator_id INTEGER,

    pret_curent REAL NOT NULL,
    data_start TEXT NOT NULL,
    durata_minute INTEGER NOT NULL,
    descriere TEXT,

    FOREIGN KEY(vehicul_vin) REFERENCES Vehicule(vin),
    FOREIGN KEY(castigator_id) REFERENCES Participanti(id)
);

INSERT INTO Participanti (id, nume, email, sold) VALUES
(101, 'Ion Tiriac', 'ion@biz.ro', 1500000),
(102, 'Student', 'stud@fmi.ro', 500);

INSERT INTO Vehicule (vin, marca, model, an_fabricatie, kilometraj, pret_initial, observatii, spec_capacitate, spec_putere, spec_combustibil, spec_cutie, spec_tractiune, tip_vehicul, e_coupe)
VALUES ('BMW-X6-001', 'BMW', 'X6', 2021, 45000, 30000, 'Impecabila', 3000, 400, 0, 1, 2, 'Auto', 1);

INSERT INTO Vehicule (vin, marca, model, an_fabricatie, kilometraj, pret_initial, observatii, spec_capacitate, spec_putere, spec_combustibil, spec_cutie, spec_tractiune, tip_vehicul, masa_maxima)
VALUES ('FORD-TR-002', 'Ford', 'Transit', 2018, 250000, 12000, 'Rugina', 2200, 130, 1, 0, 0, 'Duba', 3.5);

INSERT INTO Licitatii (vehicul_vin, castigator_id, pret_curent, data_start, durata_minute, descriere)
VALUES ('BMW-X6-001', NULL, 30000, '2026-03-20 12:00:00', 60, 'Licitatie de primavara');

