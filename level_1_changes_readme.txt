, Red   = FOREGROUND_GREEN
--> eliras

, Red   = BACKGROUND_GREEN
--> eliras

Console::MoveCursor( const uint16_ht pX, const uint16_ht pY )
--> SHORT vs uint16_ht

Error Console::PutString() printf( pFmt, args );
--> vprintf

Error Console::Clear()
--> local valtozo elnevezesek nem kovetkezetesek (mashol is van ra pelda, pl. main())

Error Console::MoveCursor() if ( lResult == TRUE )  (es a tobbi WINAPI fuggveny hibakezeles)
--> typedef int BOOL; #define TRUE  1;  SetConsoleCursorPosition: If the function succeeds, the return value is nonzero.
--> hibakezelo ag legyen a fuggveny menete soran, az jobb megoldas

ENUM_FLAG( IOutput::ForeColor ); ENUM_FLAG( IOutput::BackColor );
--> felesleges, nem is hasznaljuk

enumflag.h  #pragma once 2x
--> egyik felesleges, de egyebkent az egesz file az (ld. ENUM_FLAG felesleges)

class Error, inline operator bool() const;
--> explicit inline operator bool() const; (ne mehessen ra implicit konverzio, igy akar int-re is konvertalodhatna)

int32_ht Error::GetCode() const
--> inline int32_ht Error::GetCode() const  (kulonben linker error)

class Error: int32_ht m_Code;
--> ez a class ugyis immutable, igy akkor mar tisztabb, ha az m_Code is const:  const int32_ht m_Code;

int main( int argc, char** argv )
--> warning elkerulese: int main( int /*argc*/, char** /*argv*/ )

int main( int argc, char** argv ) getchar();
--> csak ENTER-re lep ki a program, a tobbi karaktert csak kiirja a konzol, ez inkabb tunik hibanak, mint szandekos mukodesnek
--> helyette pl: _getch(); (#include <conio.h> kell hozza), nem C++ standard, igy a portability-vel lehetnek gondok _getch() hasznalatanal, de Win alatt mukodik)

--------------------------------------------------------------------------
Ezek inkabb hianyossagok, mint hibak:

class Drawer, static const CoordList kCoords;
--> megteveszto valtozo elnevezes

SetConsoleCursorPosition()
--> ::SetConsoleCursorPosition() WINAPI fuggvenyek global namespace-ban vannak, ez stilus kerdese is, szerintem egyszerubb igy olvasni a kodot

Error Console::PutString( const char* const pFmt, ... )
--> ASCII art eseten nem kellene ilyen nagyagyu a karakterek kipakolasahoz (csak azert, hogy ezzel mehessen az error kiirasa)
--> pl. a ::WriteConsoleOutputCharacter() WINAPI fuggvenyhivassal jobb lenne erre

homework.h
--> ide huzunk be mindent? fuggosegek...

homework.h #include <stdio.h> #include <stdlib.h> #include <string.h> #include <assert.h>
--> depricated headers

a program atallitja a console-ban a text szint es a hatterszint, es programbol valo kilepes utan is ugy marad
--> vissza lehetne allitani (ld. Level2)

villog a kurzor az rajzolas vegen
--> le lehetne kapcsolni es persze kilepeskor vissza kell kapcsolni (ld. Level2)
