#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cmath>
#include <iomanip>
#include "astrologia.h"
#include "analisis_ascendente.h"
#include "ascii_art_signos.h" 
#include "colors.h"
using namespace std;

// Definición de BOLD para texto en negrita en consola
#define BOLD "\033[1m"


map<string, string> frases_por_signo = {
    {"Aries", "🔥 La energia que tienes rompe cualquier limite."},
    {"Taurus", "🌱 Tu constancia construye futuros solidos."},
    {"Gemini", "🌟 Tu curiosidad te lleva por caminos fascinantes."},
    {"Cancer", "🌙 Tu sensibilidad es tu mayor fuerza."},
    {"Leo", "☀️ Naciste para brillar, no lo olvides."},
    {"Virgo", "📋 El orden que traes al mundo es vital."},
    {"Libra", "⚖️ Tu equilibrio inspira a otros."},
    {"Scorpio", "🦂 Tu intensidad transforma realidades."},
    {"Sagittarius", "🏹 Tu espiritu libre ilumina nuevos caminos."},
    {"Capricorn", "🏔️ Tu disciplina logra lo imposible."},
    {"Aquarius", "💧 Tu originalidad cambia el mundo."},
    {"Pisces", "🐟 Sueñas con fuerza y eso te hace imparable."}
};


void contar_vida_restante(int anios) {
    for (int i = anios; i >= 0; --i) {
        cout << "[⏳ Te quedan: " << i << " años...]" << endl;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "[🌟 Disfruta cada instante]" << endl;
}

int calcular_esperanza_vida(string sexo) {
    transform(sexo.begin(), sexo.end(), sexo.begin(), ::tolower);
    if (sexo[0] == 'h') return 75;
    if (sexo[0] == 'm') return 81;
    return 78; // Valor por defecto
}


void mostrar_grafico_barras(int edad_actual, int esperanza_total) {
    cout << "\n📊 GRÁFICO DE BARRAS - ESPERANZA DE VIDA:\n";
    cout << "═══════════════════════════════════════\n";
    
    for (int edad = 0; edad <= 100; edad += 5) {
        int vida_restante = max(esperanza_total - edad, 0);
        cout << "Edad " << setw(2) << edad << ": ";
        
        // Usar diferentes caracteres para diferentes rangos
        char barra = '█';
        if (vida_restante < 20) barra = '▓';
        else if (vida_restante < 40) barra = '▒';
        
        for (int i = 0; i < vida_restante / 2; ++i) cout << barra;
        
        if (edad == (edad_actual / 5) * 5) {
            cout << MAGENTA << " ← 👤 Cerca de tu edad" << RESET;
        }
        cout << endl;
    }
}

void mostrar_grafico_pastel(int edad, int restante) {
    int total = edad + restante;
    double por_vivida = (double)edad / total * 100;
    double por_restante = 100 - por_vivida;

    cout << "\n🥧 GRÁFICO DE PASTEL - PROPORCIÓN DE VIDA:\n";
    cout << "═══════════════════════════════════════\n";
    cout << "📈 Años vividos     : " << GREEN << fixed << setprecision(1) << por_vivida << "% " << RESET;
    
    // Mostrar barras visuales
    int barras_vividas = (int)(por_vivida / 5);
    for (int i = 0; i < barras_vividas; i++) cout << "■";
    cout << "\n";
    
    cout << "⏰ Esperanza restante: " << RED << fixed << setprecision(1) << por_restante << "% " << RESET;
    int barras_restantes = (int)(por_restante / 5);
    for (int i = 0; i < barras_restantes; i++) cout << "□";
    cout << "\n";
}

// -----------------------------
// Funciones auxiliares
// -----------------------------
double obtener_hora_nacimiento() {
    int hora, minuto;
    cout << "⏰ Hora de nacimiento (0-23): ";
    cin >> hora;
    cout << "⏰ Minutos de nacimiento (0-59): ";
    cin >> minuto;
    
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        cout << "⚠️ Hora invalida, usando 12:00 por defecto.\n";
        return 12.0;
    }
    
    return hora + minuto / 60.0;
}

void obtener_coordenadas(double& lat, double& lon) {
    cout << "🗺️ ¿Conoces las coordenadas de tu lugar de nacimiento? (s/n): ";
    char respuesta;
    cin >> respuesta;
    
    if (respuesta == 's' || respuesta == 'S') {
        cout << "📍 Latitud (ej: 4.6097 para Bogotá): ";
        cin >> lat;
        cout << "📍 Longitud (ej: -74.0817 para Bogotá): ";
        cin >> lon;
        
        if (!validar_coordenadas(lat, lon)) {
            cout << "⚠️ Coordenadas inválidas, usando Bogotá por defecto.\n";
            lat = 4.6097;
            lon = -74.0817;
        }
    } else {
        cout << "🏙️ Usando coordenadas de Bogotá por defecto.\n";
        lat = 4.6097;
        lon = -74.0817;
    }
}

// -----------------------------
// Función mejorada para mostrar resultados astrológicos
// -----------------------------
void mostrar_resultados_astrologicos(const DateTime& dt, double lat, double lon) {
    try {
        // 1. Convertir a UTC y calcular JD
        double jd = julian_date(dt);

        // 2. Calcular Tiempo Sidéreo en Greenwich
        double TSG = greenwich_sidereal_time(jd);

        // 3. Calcular casas y ascendente
        vector<Casa> casas;
        string ascendente;
        calcular_casas(TSG, lat, lon, casas, ascendente);

        // 4. Calcular posiciones planetarias
        vector<CelestialBody> planetas;
        calcular_posicion_planetas(jd, planetas);

        // Mostrar resultados 
        cout << "\n✨═══════════════════════════════════════════✨\n";
        cout << "🌟          CARTA ASTRAL COMPLETA           🌟\n";
        cout << "✨═══════════════════════════════════════════✨\n";
        
        cout << "📅 Fecha: " << dt.getYear() << "-" << setfill('0') << setw(2) << dt.getMonth() 
             << "-" << setw(2) << dt.getDay() << " " << fixed << setprecision(2) 
             << dt.getHours() << " horas (UTC" << (dt.toUTC() >= 0 ? "+" : "") << dt.toUTC() << ")\n";
        cout << "🗺️ Ubicación: Lat " << fixed << setprecision(4) << lat << "°, Lon " << lon << "°\n";
        cout << "🌌 Día Juliano: " << fixed << setprecision(2) << jd << "\n";
        
        cout << "\n🌟──── SIGNOS PRINCIPALES ────🌟\n";
        
        // Mostrar signo solar 
        string signo_solar = calcular_signo_solar(dt);
        cout << "☀️ SIGNO SOLAR: " << CYAN << signo_solar << RESET << " (tu esencia)\n";
        ArteSignos::mostrar_arte_signo(signo_solar); // ← Mostrar arte aquí
        
        cout << "\n🔮 ASCENDENTE: " << YELLOW << ascendente << RESET << " (como te ven los demás)\n";
        if (ascendente != signo_solar) {
            ArteSignos::mostrar_arte_signo(ascendente); // ← Mostrar arte del ascendente también
        }

        // Mostrar análisis detallado del ascendente
        mostrar_analisis_ascendente(ascendente);

        cout << "\n🏠──── CÚSPIDES DE CASAS ────🏠\n";
        for (const auto& casa : casas) {
            cout << "🏠 Casa " << setw(2) << casa.numero << ": " 
                 << setw(12) << casa.signo << " (" 
                 << fixed << setprecision(2) << casa.longitude << "°)\n";
        }

        cout << "\n🪐──── POSICIONES PLANETARIAS ────🪐\n";
        string planetas_emoji[] = {"☉", "☽", "☿", "♀", "♂", "♃", "♄", "♅", "♆", "♇"};
        int emoji_index = 0;
        
        for (const auto& body : planetas) {
            ZodiacInfo info = get_zodiac_info(body.longitude);
            double grado_en_signo = fmod(body.longitude, 30.0);
            
            string emoji = (emoji_index < 10) ? planetas_emoji[emoji_index] : "🌟";
            cout << emoji << " " << setw(10) << body.name << ": " 
                 << setw(12) << info.sign_name << " " 
                 << fixed << setprecision(2) << grado_en_signo << "°\n";
            emoji_index++;
        }
        
    } catch (const exception& e) {
        cout << "❌ Error calculando carta astral: " << e.what() << endl;
    }
}

void mostrar_menu() {
    cout << "\n✨═══════════════════════════════════════════════✨\n";
    cout << "🌟    SISTEMA INTEGRADO DE ASTROLOGÍA Y VIDA    🌟\n";
    cout << "✨═══════════════════════════════════════════════✨\n";
    cout << "1️⃣  Calcular esperanza de vida y carta astral\n";
    cout << "2️⃣  Solo carta astral\n";
    cout << "3️⃣  Solo esperanza de vida\n";
    cout << "4️⃣  Análisis detallado del ascendente\n";
    cout << "5️⃣  🎨 Galería de signos zodiacales\n";  // ← Nueva opción
    cout << "6️⃣  Salir\n";
    cout << "✨═══════════════════════════════════════════════✨\n";
}

void procesar_galeria_signos() {
    cout << "\n🎨 Entrando a la galería de signos zodiacales...\n";
    ArteSignos::mostrar_galeria_signos();
}

void procesar_opcion_completa() {
    try {
        int dia, mes, anio;
        string sexo;
        
        cout << "\n🌟──── DATOS DE NACIMIENTO ────🌟\n";
        cout << "📅 Día de nacimiento (1-31): ";
        cin >> dia;
        cout << "📅 Mes de nacimiento (1-12): ";
        cin >> mes;
        cout << "📅 Año de nacimiento (ej: 1995): ";
        cin >> anio;
        
        if (!validar_fecha(anio, mes, dia)) {
            cout << "❌ Fecha inválida. Intenta nuevamente.\n";
            return;
        }
        
        cout << "👤 Sexo (Hombre/Mujer): ";
        cin >> sexo;

        // Obtener hora de nacimiento
        double hora_nacimiento = obtener_hora_nacimiento();
        
        // Obtener coordenadas
        double lat, lon;
        obtener_coordenadas(lat, lon);

        // Calcular edad actual
        time_t t = time(0);
        tm* now = localtime(&t);
        int current_year = now->tm_year + 1900;
        int edad = current_year - anio;

        // Calcular esperanza de vida
        int esperanza = calcular_esperanza_vida(sexo);
        int restante = max(esperanza - edad, 0);
        
        // Crear objeto DateTime
        int tz = -5; // Huso horario de Colombia
        DateTime dt(anio, mes, dia, hora_nacimiento, tz);

        // Obtener signos
        string signo_solar = calcular_signo_solar(dt);
        string ascendente = calcular_ascendente(dt, lat, lon);
        string frase = frases_por_signo.count(signo_solar) ? 
                      frases_por_signo[signo_solar] : 
                      "✨ Tu signo es único y especial.";

        // Mostrar resultados de vida con mejor formato
        cout << "\n💫═══════════════════════════════════════════💫\n";
        cout << "⏰        RESULTADOS DE ESPERANZA DE VIDA       ⏰\n";
        cout << "💫═══════════════════════════════════════════💫\n";
        cout << "👤 Edad actual: " << BLUE << edad << RESET << " años\n";
        cout << "☀️ " << BOLD << CYAN << "Signo zodiacal (Sol): " << RESET << BG_BLUE << WHITE << signo_solar << RESET << "\n";
        cout << "🔮 " << BOLD << YELLOW << "Ascendente: " << RESET << BG_MAGENTA << WHITE << ascendente << RESET << "\n";
        cout << "📊 Esperanza de vida total: " << GREEN << esperanza << RESET << " años\n";
        cout << "⏳ Vida restante estimada: " << RED << restante << RESET << " años\n";
        cout << "💖 Frase motivacional: " << frase << "\n";

        // Mostrar arte del signo con animación
        ArteSignos::mostrar_arte_animado(signo_solar);

        // Animación de cuenta regresiva
        cout << "\n⏳ Contando tu vida restante...\n";
        contar_vida_restante(min(restante, 5)); // Máximo 5 para no ser muy lenta

        // Mostrar gráficos
        mostrar_grafico_barras(edad, esperanza);
        mostrar_grafico_pastel(edad, restante);

        // Mostrar información astrológica completa
        mostrar_resultados_astrologicos(dt, lat, lon);

    } catch (const exception& e) {
        cout << "❌ Error: " << e.what() << endl;
    } catch (...) {
        cout << "❌ Error: entrada inválida.\n";
    }
}

void procesar_solo_astrologia() {
    try {
        int dia, mes, anio;
        
        cout << "\n🌟──── DATOS PARA CARTA ASTRAL ────🌟\n";
        cout << "📅 Día de nacimiento (1-31): ";
        cin >> dia;
        cout << "📅 Mes de nacimiento (1-12): ";
        cin >> mes;
        cout << "📅 Año de nacimiento (ej: 1995): ";
        cin >> anio;
        
        if (!validar_fecha(anio, mes, dia)) {
            cout << "❌ Fecha inválida. Intenta nuevamente.\n";
            return;
        }
        
        double hora_nacimiento = obtener_hora_nacimiento();
        
        double lat, lon;
        obtener_coordenadas(lat, lon);
        
        int tz = -5;
        DateTime dt(anio, mes, dia, hora_nacimiento, tz);
        
        mostrar_resultados_astrologicos(dt, lat, lon);
        
    } catch (...) {
        cout << "❌ Error procesando datos astrológicos.\n";
    }
}

void procesar_solo_esperanza() {
    try {
        int anio;
        string sexo;
        
        cout << "\n⏰──── CÁLCULO DE ESPERANZA DE VIDA ────⏰\n";
        cout << "📅 Año de nacimiento: ";
        cin >> anio;
        cout << "👤 Sexo (Hombre/Mujer): ";
        cin >> sexo;
        
        time_t t = time(0);
        tm* now = localtime(&t);
        int current_year = now->tm_year + 1900;
        int edad = current_year - anio;
        
        int esperanza = calcular_esperanza_vida(sexo);
        int restante = max(esperanza - edad, 0);
        
        cout << "\n👤 Edad actual: " << edad << " años\n";
        cout << "📊 Esperanza de vida total: " << GREEN << esperanza << RESET << " años\n";
        cout << "⏳ Vida restante estimada: " << RED << restante << RESET << " años\n";
        
        mostrar_grafico_barras(edad, esperanza);
        mostrar_grafico_pastel(edad, restante);
        
    } catch (...) {
        cout << "❌ Error procesando esperanza de vida.\n";
    }
}

void ejecutar_aplicacion() {
    srand(time(0)); // Inicializar semilla para números aleatorios
    
    cout << "🌟 ¡Bienvenido al Sistema de Astrología y Esperanza de Vida! 🌟\n";
    
    while (true) {
        mostrar_menu();
        string opcion;
        cout << "✨ Elige una opción (1-6): ";
        cin >> opcion;


        // Añadir retraso visual antes de ejecutar la opción
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        // Limpiar pantalla antes de mostrar la siguiente acción
        system("cls");

        if (opcion == "1") {
            procesar_opcion_completa();
        } else if (opcion == "2") {
            procesar_solo_astrologia();
        } else if (opcion == "3") {
            procesar_solo_esperanza();
        } else if (opcion == "4") {
            ejecutar_analisis_ascendente();
        } else if (opcion == "5") {  
            procesar_galeria_signos();
        } else if (opcion == "6") {
            cout << "🌟 ¡Gracias por usar el sistema! Que tengas un buen día. ✨\n";
            break;
        } else {
            cout << "❌ Opción no válida. Elige entre 1 y 6.\n";
        }
        
        cout << "\n⏸️ Presiona Enter para continuar...";
        cin.ignore();
        cin.get();
    }
}

int main() {
    system("chcp 65001");
    system("color 0F");
    try {
        ejecutar_aplicacion();
    } catch (const exception& e) {
        cout << "💥 Error fatal: " << e.what() << endl;
        return 1;
    }
    return 0;
}