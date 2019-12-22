#ifndef JOURAPRESJOUR_H
#define JOURAPRESJOUR_H

#include <QString>
#include <QVector>
#include <QPair>

// affichage de texte (phrase donc) mais aussi potetntiellement d'une image
struct Phrase {
    Phrase(QString texte, QString img = ""):m_Texte(" - " + texte), m_CheminImg(img) {

    }
    QString m_Texte;
    QString m_CheminImg = "";
};

/**
 * @brief Génération des textes/images à afficher quand il n'arrive rien au joueur, et ce en fonction de son état actuel
 * (socio économique, métier, planète...)
 */
class JourApresJour
{
    void RafraichirPhrasesSelonPlanete(QString typePlanete, QString classeSociale, QString metier);
    void RafraichirPhrasesSelonMetier(QString typePlanete, QString classeSociale, QString metier);
public:
    JourApresJour();
    static QVector<Phrase> PHRASES;

    void RafraichirPhrases();

    static Phrase ExtrairePhrase();

};

#endif // JOURAPRESJOUR_H
