#ifndef CITATION_H
#define CITATION_H

#include <QString>
#include <QVector>

class Citation
{
public:
    Citation(QString texte, QString auteur);

    QString m_Texte;
    QString m_Auteur;

    static QVector<Citation> CITATIONS;
};

#endif // CITATION_H
