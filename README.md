#  AuctionHouse - Sistem de Licitații Auto

Acest proiect este o aplicație consolă de gestiune a unui parc auto care vinde vehicule prin licitație. Aplicația simulează întregul proces: de la listarea mașinilor și înregistrarea participanților, până la simularea unui "Bid War", plasarea ofertelor și determinarea câștigătorului.

Proiectul a fost dezvoltat pentru a pune în practică concepte avansate de **Programare Orientată pe Obiecte (OOP)**, **C++ Modern** și integrarea cu o bază de date relațională (**SQLite**).

##  Tehnologii și Concepte Evidențiate

* **C++ Modern (C++11/14/17):**
  * Managementul memoriei folosind **Smart Pointers** (`std::unique_ptr`).
  * Utilizarea funcțiilor **Lambda** și a algoritmilor STL.
* **Design Patterns:**
  * **Singleton:** Aplicat pe clasa `AuctionManager` pentru a avea un singur punct central de control al aplicației.
  * **Factory Method:** Folosit (`VehiculFactory`) pentru crearea polimorfică a vehiculelor la runtime (Autoturisme, Utilitare, Motociclete).
* **OOP Avansat:** Polimorfism (`dynamic_cast`, funcții virtuale), clase abstracte și încapsulare strictă.
* **Templates:** Implementarea de clase și funcții șablon (inclusiv specializări) pentru gestionarea colecțiilor generice de date.
* **Baze de Date (SQLite):**
  * Persistența datelor folosind librăria `SQLiteCpp`.
  * Operațiuni CRUD complete (Create, Read, Update, Delete) sincronizate automat cu memoria RAM.
  * Folosirea interogărilor SQL parametrizate.

## ⚙️ Funcționalități Principale

1. **Gestiunea Inventarului:** Adăugarea vehiculelor (citire cu suport pentru spații), afișarea filtrată pe categorii și ștergerea lor definitivă .
2. **Sistem de Licitații:** Crearea de licitații cu durată și preț de pornire.
3. **Participanți:** Înregistrarea utilizatorilor cu sold (buget) și actualizarea acestuia în timp real după plasarea ofertelor.
4. **Scenariu Complex (Bid War):** O simulare automată a unei licitații intense între doi participanți pentru o mașină de colecție, demonstrând logica de validare a fondurilor.

<img width="577" height="555" alt="image" src="https://github.com/user-attachments/assets/2c7dcd01-7d2a-455d-9abd-cec0d9f25d3a" />


##  Cum se rulează

Proiectul folosește **CMake** pentru build. Ai nevoie de un compilator C++ (GCC/MinGW sau MSVC).
Baza de date `auction.db` este inclusă direct în proiect, fiind gata populată cu date de test.
