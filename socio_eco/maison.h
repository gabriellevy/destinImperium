#ifndef MAISON_H
#define MAISON_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;


class Maison
{
    QString m_Id;
public:
    Maison(QString id);

    QString GetImageAleatoire();


    // valeurs statiques
    static QString AssignerMaison(QString classeSociale, QString typeMonde);
    // caracs :
    static QString C_MAISON;
    // maisons "pauvres" et "moyennes"
    static QString VANSAAR;
    static QString ORLOCK;
    static QString GOLIATH;
    static QString ESHER;
    static QString DELAQUE;
    static QString CAWDOR;

    // maisons influentes et maîtres

};

#endif // MAISON_H