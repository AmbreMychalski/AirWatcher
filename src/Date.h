/*************************************************************************
                           Date  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Date> (fichier Date.h) ----------------
#if ! defined ( DATE_H )
#define DATE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Date>
//
//
//------------------------------------------------------------------------

class Date
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int getYear () const
    {
        return year;
    }
    
    int getMonth () const
    {
        return month;
    }
    
    int getDay () const
    {
        return day;
    }
    
    int getHour () const
    {
        return hour;
    }
    
    int getMinute () const
    {
        return minute;
    }
    
    int getSecond () const
    {
        return second;
    }


//------------------------------------------------- Surcharge d'opérateurs
    bool operator == ( const Date & date );
    bool operator < ( const Date & date );
    bool operator <= ( const Date & date );
    bool operator != ( const Date & date );
    bool operator > ( const Date & date );
    bool operator >= ( const Date & date );

//-------------------------------------------- Constructeurs - destructeur

    Date ( int y, int M, int d, int h, int m, int s ):
    year(y), month(M), day(d), hour(h), minute(m), second(s)
    {
#ifdef MAP
    cout << "Appel au constructeur de <Date>" << endl;
#endif
    }
    
    Date ()
    {
#ifdef MAP
    cout << "Appel au constructeur de <Date>" << endl;
#endif
    }

    virtual ~Date ( )
    {
#ifdef MAP
    cout << "Appel au destructeur de <Date>" << endl;
#endif
    }

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int year;
    int month;
	int day;
    int hour;
    int minute;
    int second;
};

//-------------------------------- Autres définitions dépendantes de <Date>

#endif // DATE_H

