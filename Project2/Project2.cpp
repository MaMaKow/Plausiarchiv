// Project2.cpp : Diese Datei enth�lt die Funktion "main". Hier beginnt und endet die Ausf�hrung des Programms.
//

#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>      // std::stringstream
#include <fstream>


/*
title Plausi archivieren



echo "Bitte die Herstellungsanweisung %plausi_nummer% in den Scanner legen und Enter dr�cken!"
set /p es_geht_los=
set archiv_file_name=%pfad_zum_archiv%Herstellungsanweisungen\%plausi_nummer%.pdf
echo Die Datei wird abgelegt als:
echo %archiv_file_name%
REM Dokument scannen:
"%naps_scan_bin%" -o "%archiv_file_name%" --enableocr --profile %naps_scan_profile% --ocrlang "deu"
gpg --output "%archiv_file_name%".gpg --sign "%archiv_file_name%"
gpg --output "%archiv_file_name%".sig --detach-sig "%archiv_file_name%"

REM Erst mal anzeigen und gucken, wies es aussieht:
REM "C:\Program Files (x86)\Adobe\Acrobat Reader DC\Reader\AcroRd32.exe"  %archiv_file_name%

REM Benutzer �ber den Erfolg informieren
IF exist "%archiv_file_name%" (
    echo Die Datei wurde erfolgreich erstellt. Das Papier kann geschreddert werden.
) ELSE (
    echo Scheinbar gab es einen Fehler. Die Datei wurde nicht erstellt.
)

REM Auf neuen Vorgang oder Abbruch warten
REM echo "Wollen wir noch eine Plausi scannen? (J/N)"
REM set /p vorgang_wiederholen=
REM IF "J" == "%vorgang_wiederholen%" (
    GOTO :START
REM )

:END
echo "Auf Wiedersehen"
*/

bool fileExists(const std::string& fileName) {

    std::ifstream ifile;
    ifile.open(fileName);
    if (ifile) {
        std::cout << "file exists";
        return true;
    }
    else {
        std::cout << "file doesn't exist";
        return false;
    }
}
/*
bool fileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
*/
void executeSystem(std::string pathOfCommand, std::string stringOfArguments) {
    // system entfernt Anf�hrungszeichen "" unter verschiedenen Bedingungen.
    //https://stackoverflow.com/a/55652942/2323627
    std::stringstream stringStream;

    // some code to set values for paths
    //stringStream << "\"cmd /S /C @echo off & ";                             // command opening quote
    stringStream << "\"cmd /S /C @echo off & chcp 1252 & ";                             // command opening quote
    stringStream << "\"" << pathOfCommand << "\" "; // Quoted binary (could have spaces)
    stringStream << stringOfArguments;  // Quoted input (could have spaces)
    stringStream << "\"";                             // command closing quote
    system(stringStream.str().c_str());             // Execute the command

}


void pdfSignieren(std::string archiv_file_name) {
    std::string gpg_sign_command;
    std::string gpg_encrypt_command;
    /*
     * Signieren und verschl�sseln:
     * Die Datei mit der Endung .sig enth�lt lediglich die Signatur. Sie braucht immer das vorhandene PDF und kann es dann best�tigen.
     * Die Datei mit der Endung .gpg enth�lt das verschl�sselte PDF und die Signatur. Die Datei kann eigenst�ndig verwendet werden.
     */
    gpg_sign_command = "gpg --output " + archiv_file_name + ".gpg --sign " + archiv_file_name;
    system(gpg_sign_command.c_str());
    gpg_encrypt_command = "gpg --output " + archiv_file_name + ".sig --detach-sig " + archiv_file_name;
    system(gpg_encrypt_command.c_str());
}

void pdfScannen(std::string archiv_file_name) {
    std::string naps_scan_bin = "C:\\Program Files (x86)\\NAPS2\\NAPS2.Console.exe";
    std::string naps_scan_profile = "fi-7160_grau";
    /*
     * Dokument scannen:
     * Sprache f�r OCR --ocrlang "eng" mit folgender Sprache:
     * ger (B) oder deu (T) laut http://www.loc.gov/standards/iso639-2/php/code_list.php
     */
    std::string naps_scan_argument;
    naps_scan_argument = " -o " + archiv_file_name + " --enableocr --profile " + naps_scan_profile + " --ocrlang deu";
    executeSystem(naps_scan_bin, naps_scan_argument);
}

int main()
{
    /*
     * Dieses Script soll dabei helfen, alte Plausibilit�tsprotokolle zu archivieren.
     * 1. Das Programm fragt den Benutzer nach PL-Nummer des Protokolls.
     * 2. Der Benutzer legt das Protokoll in den Scanner.
     * 3. Das Bild wird gespeichert als PDF. Das PDF wird eindeutig benannt.
     * 4. Das Papierprotokoll wird geschreddert.
     */

    SetConsoleOutputCP(1252); // f�r Umlaut-Ausgabe
    SetConsoleCP(1252); // f�r Umlaut-Eingabe
    std::string plausi_nummer;
    std::string archiv_file_name;

    std::string pfad_zum_archiv = "C:\\Users\\Apothekenadmin\\Documents\\Qsync\\Rezeptur\\Rezepturdokumentation\\";
    std::string exif_tool_bin = "C:\\Users\\Apothekenadmin\\Documents\\Qsync\\Mitarbeiter pers�nlich\\Mandelkow\\Anwendungen\\Abholerarchiv\\exiftool.exe";

    //while (plausi_nummer != "n" and plausi_nummer != "N")
    {


        std::cout << std::endl;
        std::cout << "Bitte die Plausinummer eingeben und mit ENTER best�tigen" << std::endl;
        std::cout << "z.B. PL 2015 - 03" << std::endl;
        std::getline(std::cin, plausi_nummer);

        archiv_file_name = "\"" + pfad_zum_archiv + "Plausibilit�tspr�fungen\\" + plausi_nummer + ".pdf\"";
        std::cout << "Die Datei wird abgelegt als :" << std::endl;
        std::cout << archiv_file_name << std::endl;

        std::cout << "Bitte das Plausibilit�tsprotokoll " + plausi_nummer + " in den Scanner legen und Enter dr�cken!" << std::endl;
        std::cin.get();

        if (fileExists(archiv_file_name)) {
            std::cout << "The files already exists!";
        }
        else
        {
            std::cout << "The files do not exist yet.";
        }
        return 0;
        //pdfScannen(archiv_file_name);
        //pdfSignieren(archiv_file_name);

        /*
         * Und jetzt kommt die Herstellungsanweisung:
         * Da folgen die selben Befehle noch einmal.
         */
        std::cout << "Bitte die Herstellungsanweisung " + plausi_nummer + " in den Scanner legen und Enter dr�cken!" << std::endl;
        std::cin.get();


        archiv_file_name = "\"" + pfad_zum_archiv + "Herstellungsanweisungen\\" + plausi_nummer + ".pdf\"";
        std::cout << "Die Datei wird abgelegt als :" << std::endl;
        std::cout << archiv_file_name << std::endl;

        //pdfScannen(archiv_file_name);
        //pdfSignieren(archiv_file_name);
    }
}

// Programm ausf�hren: STRG+F5 oder Men�eintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Men� "Debuggen starten"

// Tipps f�r den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzuf�gen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzuf�gen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzuf�gen", um dem Projekt vorhandene Codedateien hinzuzuf�gen.
//   6. Um dieses Projekt sp�ter erneut zu �ffnen, wechseln Sie zu "Datei" > "�ffnen" > "Projekt", und w�hlen Sie die SLN-Datei aus.
