// Project2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>      // std::stringstream

int main()
{
    /*
    * Dieses Script soll dabei helfen, alte Plausibilitätsprotokolle zu archivieren.
    * 1. Das Programm fragt den Benutzer nach PL-Nummer des Protokolls.
    * 2. Der Benutzer legt das Protokoll in den Scanner.
    * 3. Das Bild wird gespeichert als PDF. Das PDF wird eindeutig benannt.
    * 4. Das Papierprotokoll wird geschreddert.

    */

    SetConsoleOutputCP(1252); // für Umlaut-Ausgabe
    SetConsoleCP(1252); // für Umlaut-Eingabe
    system("chcp 1252");
    std::string plausi_nummer;
    std::string abholer_datum;
    std::string abholer_name;
    std::string archiv_file_name;
    std::string void_var; // Diese Variable soll eigentlich gar nichts bedeuten.

    void executeSystem(std::string, std::string);
    void pdfScannen(std::string);
    void pdfSignieren(std::string);


    std::cout << "Hello World!" << std::endl;
    system("echo Test system call");




    std::string pfad_zum_archiv = "C:\\Users\\Apothekenadmin\\Documents\\Qsync\\Rezeptur\\Rezepturdokumentation\\";

    std::string exif_tool_bin = "C:\\Users\\Apothekenadmin\\Documents\\Qsync\\Mitarbeiter persönlich\\Mandelkow\\Anwendungen\\Abholerarchiv\\exiftool.exe";



    //while (plausi_nummer != "n" and plausi_nummer != "N")
    {


        std::cout << std::endl;
        //std::cout << "Um das Programm abzubrechen bitte den Buchstaben N eingeben und mit ENTER bestätgen." << std::endl;
        std::cout << "Bitte die Plausinummer eingeben und mit ENTER bestätigen" << std::endl;
        //std::cout << "z.B. PL 2015 - 03" << std::endl;

        //std::cin >> plausi_nummer;
        plausi_nummer = "PL 1985 - 50";

        //std::cout << "Bitte das Plausibilitätsprotokoll " + plausi_nummer + " in den Scanner legen und Enter drücken!" << std::endl;
        //std::cin >> void_var; // Wir brauchen diesen Input nicht als Variable speichern.
        //std::cin.ignore();

        archiv_file_name = pfad_zum_archiv + "Plausibilitätsprüfungen\\" + plausi_nummer + ".pdf";
        //std::cout << "Die Datei wird abgelegt als :" << std::endl;
        //std::cout << archiv_file_name << std::endl;

        pdfScannen(archiv_file_name);
        //pdfSignieren(archiv_file_name);
    }
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.

/*
title Plausi archivieren



echo "Bitte die Herstellungsanweisung %plausi_nummer% in den Scanner legen und Enter drücken!"
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

REM Benutzer über den Erfolg informieren
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


void executeSystem(std::string pathOfCommand, std::string stringOfArguments) {
    // system entfernt Anführungszeichen "" unter verschiedenen Bedingungen.
    //https://stackoverflow.com/a/55652942/2323627
    std::stringstream stringStream;

    // some code to set values for paths
    stringStream << "\"cmd /S /C @echo on & echo hello world & @echo on & echo hello world & ";                             // command opening quote
    stringStream << "\"" << pathOfCommand << "\" "; // Quoted binary (could have spaces)
    stringStream << "\"" << stringOfArguments << "\"";  // Quoted input (could have spaces)
    stringStream << "\"";                             // command closing quote
    system(stringStream.str().c_str());             // Execute the command
}


void pdfSignieren(std::string archiv_file_name) {
    std::string gpg_sign_command;
    std::string gpg_encrypt_command;
    /*
     * Signieren und verschlüsseln:
     * Die Datei mit der Endung .sig enthält lediglich die Signatur. Sie braucht immer das vorhandene PDF und kann es dann bestätigen.
     * Die Datei mit der Endung .gpg enthält das verschlüsselte PDF und die Signatur. Die Datei kann eigenständig verwendet werden.
     */
    gpg_sign_command = "gpg --output " + archiv_file_name + ".gpg --sign " + archiv_file_name;
    //system(gpg_sign_command.c_str());
    gpg_encrypt_command = "gpg --output " + archiv_file_name + ".sig --detach-sig " + archiv_file_name;
    //system(gpg_encrypt_command.c_str());
}

void pdfScannen(std::string archiv_file_name) {
    std::string naps_scan_bin = "C:\\Program Files (x86)\\NAPS2\\NAPS2.Console.exe";
    std::string naps_scan_profile = "\"fi-7160 grau\"";
    /*
     * Dokument scannen:
     * Sprache für OCR --ocrlang "eng" mit folgender Sprache:
     * ger (B) oder deu (T) laut http://www.loc.gov/standards/iso639-2/php/code_list.php
     */
    std::string naps_scan_command;
    naps_scan_command = naps_scan_bin  + " -o " + '"' + archiv_file_name + '"' + " --enableocr --profile " + naps_scan_profile + " --ocrlang \"deu\"";
    std::string naps_scan_argument;
    naps_scan_argument = " -o " + '"' + archiv_file_name + '"' + " --enableocr --profile " + naps_scan_profile + " --ocrlang \"deu\"";
    //std::cout << naps_scan_command << std::endl;
    //std::cout << std::endl;
    executeSystem(naps_scan_bin, naps_scan_argument);
    //std::cout << std::endl;
}

