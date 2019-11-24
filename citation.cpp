#include "citation.h"

Citation::Citation(QString texte, QString auteur)
    :m_Texte(texte), m_Auteur(auteur)
{}

QVector<Citation> Citation::CITATIONS = {
    Citation("La tombe du martyr est la clef de voûte de l'Imperium", "Liber Imperialis"),
    Citation("Savoir sa place est d'un grand confort, y exceller est le plus grand réconfort, et la satisfaction d'un maître est la plus grande récompense.", "Codex Administratum Edition XXIIVC"),
    Citation("Nous déterminons le coupable. Nous fixons la punition.", "Lex Imperialis"),
    Citation("Vous ne pouvez comprendre les mystères de l'univers, vous ne devez que faire confiance à la vérité des ordres de l'empereur.",
        "Édits de la guilde des navigateurs de Calixis")
};
