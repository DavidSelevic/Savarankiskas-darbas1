#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>

class Studentas {
public:
    // Kintamieji
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egzaminas;
    double galutinis;

    // Konstruktoriai
    Studentas() : vardas(""), pavarde(""), egzaminas(0), galutinis(0.0) {}

    // Trijų taisyklė
    Studentas(const Studentas& kitas)
        : vardas(kitas.vardas), pavarde(kitas.pavarde), namuDarbai(kitas.namuDarbai), egzaminas(kitas.egzaminas), galutinis(kitas.galutinis) {}

    Studentas& operator=(const Studentas& kitas) {
        if (this == &kitas) return *this;
        vardas = kitas.vardas;
        pavarde = kitas.pavarde;
        namuDarbai = kitas.namuDarbai;
        egzaminas = kitas.egzaminas;
        galutinis = kitas.galutinis;
        return *this;
    }

    ~Studentas() {}

    // Metodai
    void ivestiDuomenis() {
        std::cout << "Įveskite studento vardą: ";
        std::cin >> vardas;
        std::cout << "Įveskite studento pavardę: ";
        std::cin >> pavarde;

        int nd;
        std::cout << "Įveskite namų darbų rezultatus (kai baigsite, įveskite -1): " << std::endl;
        while (true) {
            std::cin >> nd;
            if (nd == -1) break;
            namuDarbai.push_back(nd);
        }

        std::cout << "Įveskite egzamino rezultatą: ";
        std::cin >> egzaminas;

        galutinis = skaiciuotiGalutini();
    }

    void spausdintiDuomenis() const {
        std::cout << std::left << std::setw(15) << pavarde
                  << std::left << std::setw(15) << vardas
                  << std::fixed << std::setprecision(2) << galutinis << std::endl;
    }

    double skaiciuotiGalutini(bool naudotiMediana = false) const {
        double ndRezultatas = naudotiMediana ? skaiciuotiMediana() : skaiciuotiVidurki();
        return 0.4 * ndRezultatas + 0.6 * egzaminas;
    }

private:
    double skaiciuotiVidurki() const {
        return std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0.0) / namuDarbai.size();
    }

    double skaiciuotiMediana() const {
        std::vector<int> temp = namuDarbai;
        std::sort(temp.begin(), temp.end());
        if (temp.size() % 2 == 0)
            return (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2.0;
        else
            return temp[temp.size() / 2];
    }
};

int main() {
    std::vector<Studentas> studentai;
    char testi = 't';

    while (testi == 't') {
        Studentas s;
        s.ivestiDuomenis();
        studentai.push_back(s);

        std::cout << "Ar norite įvesti kitą studentą? (t/n): ";
        std::cin >> testi;
    }

    std::cout << "Pavardė         Vardas          Galutinis (Vid.)" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    for (const auto& s : studentai) {
        s.spausdintiDuomenis();
    }

    return 0;
}
