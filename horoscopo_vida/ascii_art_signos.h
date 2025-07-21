#ifndef ASCII_ART_SIGNOS_H
#define ASCII_ART_SIGNOS_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Arte ASCII para cada signo zodiacal
class ArteSignos {
private:
    static map<string, string> arte_ascii;
    
public:
    static void inicializar_arte() {
        // ARIES - Carnero
        arte_ascii["Aries"] = R"(
    ░░████░░  ░░████░░
  ░░██░░░░██░░██░░░░██░░
 ░██░░░░░░░░██░░░░░░░░██
██░░░░██░░██░░██░░██░░░░██
██░░░░██░░██░░██░░██░░░░██
 ░██░░░░░░░░░░░░░░░░░░██
   ░██░░░░░░░░░░░░░░██
     ░██░░░░░░░░░░██
       ░░████████░░

        ♈ ARIES
)";

        // TAURUS - Toro
        arte_ascii["Taurus"] = R"(
  ░░██░░    ░░██
░░██░░██  ██░░██░░
██░░░░░░██░░░░░░██
██░░░░██████░░░░██
██░░░░██░░██░░░░██
░░██░░░░██░░░░██
  ░░██████████
    ░░░░██░░
      ░░██
        ♉ TAURUS
)";

        // GEMINI - Gemelos
        arte_ascii["Gemini"] = R"(
██░░██  ██░░██
██░░██  ██░░██
██░░██  ██░░██
██████  ██████
██░░██  ██░░██
██░░██  ██░░██
██░░██  ██░░██
██████  ██████
      ♊ GEMINI
)";

        // CANCER - Cangrejo
        arte_ascii["Cancer"] = R"(
░░██████████░░
██░░░░░░░░░░██
██░░██████░░██
██░░██░░██░░██
██░░██████░░██
░░██░░░░░░██
  ░░██████
     ░░
      ♋ CANCER
)";

        // LEO - León
        arte_ascii["Leo"] = R"(
    ░░████░░
  ░░██████░░
░░██░░██░░██░░
██░░░░██░░░░██
██░░██████░░██
██░░░░██░░░░██
░░██░░██░░██
  ░░██████
    ░░██
      ♌ LEO
)";

        // VIRGO - Virgen
        arte_ascii["Virgo"] = R"(
██░░██ ██░░██
██░░██ ██░░██
██░░██ ██░░██
██░░██ ██░░██
██████ ██████
░░░░██ ██
░░░░██ ██░░░░██
░░░░░░ ░░████
       ♍ VIRGO
)";

        // LIBRA - Balanza
        arte_ascii["Libra"] = R"(
  ░░██████░░
░░██░░░░░░██░░
██░░░░██░░░░██
██████████████
░░░░░░██░░░░░░
██████████████
██░░░░░░░░░░██
░░████████████
      ♎ LIBRA
)";

        // SCORPIO - Escorpión
        arte_ascii["Scorpio"] = R"(
██░░██ ██░░██
██░░██ ██░░██
██░░██ ██░░██
██████ ██████
░░░░██ ██
░░░░██ ██░░██
░░░░██ ██░░██░░
░░░░░░ ░░░░░░██
       ♏ SCORPIO
)";

        // SAGITTARIUS - Arquero/Centauro
        arte_ascii["Sagittarius"] = R"(
        ░░██
      ░░██
    ░░██
  ░░██
░░██████████
  ░░██
    ░░██
      ░░██
        ░░██
    ♐ SAGITTARIUS
)";

        // CAPRICORN - Cabra
        arte_ascii["Capricorn"] = R"(
██░░░░░░░░░░██
██░░██████░░██
██░░██░░██░░██
██░░██████░░██
██░░░░░░░░░░██
░░████░░░░██
  ░░██░░██
    ░░██░░░░██
      ░░████
    ♑ CAPRICORN
)";

        // AQUARIUS - Aguador
        arte_ascii["Aquarius"] = R"(
░░██░░██░░██░░
██░░██░░██░░██
░░██░░██░░██░░
██░░██░░██░░██
░░██░░██░░██░░
██░░██░░██░░██
░░░░░░██░░░░░░
      ██
    ♒ AQUARIUS
)";

        // PISCES - Peces
        arte_ascii["Pisces"] = R"(
░░██░░      ░░██░░
██░░██      ██░░██
██░░░░██░░██░░░░██
██░░░░██████░░░░██
██░░░░██░░██░░░░██
██░░██      ██░░██
░░██░░      ░░██░░
      ♓ PISCES
)";
    }
    
    // Función para mostrar el arte de un signo
    static void mostrar_arte_signo(const string& signo) {
        if (arte_ascii.empty()) {
            inicializar_arte();
        }
        
        if (arte_ascii.find(signo) != arte_ascii.end()) {
            cout << "\n" << arte_ascii[signo] << "\n";
        } else {
            cout << "\n✨ " << signo << " ✨\n";
        }
    }
    
    // Función para mostrar arte animado
    static void mostrar_arte_animado(const string& signo) {
        if (arte_ascii.empty()) {
            inicializar_arte();
        }
        
        cout << "\n🌟 Revelando tu signo zodiacal... 🌟\n";
        
        // Efecto de "cargando"
        for (int i = 0; i < 3; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        
        cout << "\n";
        mostrar_arte_signo(signo);
    }
    
    // Función para mostrar todos los signos (modo galería)
    static void mostrar_galeria_signos() {
        if (arte_ascii.empty()) {
            inicializar_arte();
        }
        
        cout << "\n=== GALERÍA DE SIGNOS ZODIACALES ===\n";
        
        vector<string> signos = {
            "Aries", "Taurus", "Gemini", "Cancer",
            "Leo", "Virgo", "Libra", "Scorpio",
            "Sagittarius", "Capricorn", "Aquarius", "Pisces"
        };
        
        for (const string& signo : signos) {
            mostrar_arte_signo(signo);
            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }
};

// Inicialización del mapa estático
map<string, string> ArteSignos::arte_ascii;

#endif // ASCII_ART_SIGNOS_H