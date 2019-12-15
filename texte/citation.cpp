#include "citation.h"

Citation::Citation(QString texte, QString auteur)
    :m_Texte(texte), m_Auteur(auteur)
{}

QVector<Citation> Citation::CITATIONS = {
    Citation("La tombe du martyr est la clef de voûte de l'Imperium", "Liber Imperialis"),
    Citation("Savoir sa place est d'un grand confort, y exceller est le plus grand réconfort, et la satisfaction d'un maître est la plus grande récompense.", "Codex Administratum Edition XXIIVC"),
    Citation("Nous déterminons le coupable. Nous fixons la punition.", "Lex Imperialis"),
    Citation("Vous ne pouvez comprendre les mystères de l'univers, vous ne devez que faire confiance à la vérité des ordres de l'empereur.",
        "Édits de la guilde des navigateurs de Calixis"),
    Citation("Vous avez été accusé, au nom de l'empereur, du crime de piraterie. Vous avez le droit de confesser vos crimes et de chercher l'absolution pour vos péchés. Les demandes de clémence ne seront pas entendues.",
        "Maître châtisseur Grigor Cardainn"),
    Citation("Si l'Adeptus Astartes est la colère de l'empereur, la garde impériale son marteau, alors la sainte marine est son puissant bouclier",
        "Cardinal Kregory Hestor"),
    Citation("Je suis Tzeentch et tu es le pantin qui danse sur ma musique...",
        "Extrait du livre de Tzeentch")
};
