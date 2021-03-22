// Project2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

int main()
{
    /*
    * Dieses Script soll dabei helfen, alte Plausibilitätsprotokolle zu archivieren.
    * 1. Das Programm fragt den Benutzer nach PL-Nummer des Protokolls.
    * 2. Der Benutzer legt das Protokoll in den Scanner.
    * 3. Das Bild wird gespeichert als PDF. Das PDF wird eindeutig benannt.
    * 4. Das Papierprotokoll wird geschreddert.

    */
    
    std::cout << "Hello World!\n";
    system("echo Test system call");
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
cls
@echo off
chcp 1252
REM Dieses Script soll dabei helfen, alte Plausibilitätsprotokolle zu archivieren.
REM 1. Das Programm fragt den Benutzer nach PL-Nummer des Protokolls.
REM 2. Der Benutzer legt das Protokoll in den Scanner.
REM 3. Das Bild wird gespeichert als PDF. Das PDF wird eindeutig benannt.
REM 4. Das Papierprotokoll wird geschreddert.
title Plausi archivieren

set naps_scan_profile="fi-7160 grau"
set pfad_zum_archiv=C:\Users\Apothekenadmin\Documents\Qsync\Rezeptur\Rezepturdokumentation\
set naps_scan_bin=C:\Program Files (x86)\NAPS2\NAPS2.Console.exe

set exif_tool_bin=C:\Users\Apothekenadmin\Documents\Qsync\Mitarbeiter persönlich\Mandelkow\Anwendungen\Abholerarchiv\exiftool.exe



:START
REM Leere Werte für die Variablen vorgeben:
set plausi_nummer=""
set abholer_datum=""
set abholer_name=""

echo[
echo Um das Programm abzubrechen bitte den Buchstaben N eingeben und mit ENTER bestätgen.
echo Um die Eingabe abzubrechen und neu zu starten bitte den Buchstaben X eingeben und mit ENTER bestätgen.
echo Bitte die Plausinummer eingeben und mit ENTER bestätigen
echo z.B. PL 2015 - 03


set /p plausi_nummer=

IF "N" == "%plausi_nummer%" (
    GOTO :END
)
IF "n" == "%plausi_nummer%" (
    GOTO :END
)
IF "x" == "%plausi_nummer%" (
    GOTO :START
)
IF "X" == "%plausi_nummer%" (
    GOTO :START
)







echo "Bitte das Plausibilitätsprotokoll %plausi_nummer% in den Scanner legen und Enter drücken!"
set /p es_geht_los=

set archiv_file_name=%pfad_zum_archiv%Plausibilitätsprüfungen\%plausi_nummer%.pdf
echo Die Datei wird abgelegt als:
echo %archiv_file_name%
REM Dokument scannen:
"%naps_scan_bin%" -o "%archiv_file_name%" --enableocr --profile %naps_scan_profile% --ocrlang "deu"
gpg --output "%archiv_file_name%".gpg --sign "%archiv_file_name%"
gpg --output "%archiv_file_name%".sig --detach-sig "%archiv_file_name%"

REM Sprache für OCR --ocrlang "eng" mit folgender Sprache:
REM ger (B) oder deu (T) laut http://www.loc.gov/standards/iso639-2/php/code_list.php

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
echo[
echo[
echo[
echo[


REM Auf neuen Vorgang oder Abbruch warten
REM echo "Wollen wir noch eine Plausi scannen? (J/N)"
REM set /p vorgang_wiederholen=
REM IF "J" == "%vorgang_wiederholen%" (
    GOTO :START
REM )

:END
echo "Auf Wiedersehen"
*/