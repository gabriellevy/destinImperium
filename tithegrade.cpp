#include "tithegrade.h"

TitheGrade::TitheGrade(e_TitheGrade TitheGrade, e_ProductionGrade ProductionGrade)
    :m_TitheGrade(TitheGrade), m_ProductionGrade(ProductionGrade)
{}

QString TitheGrade::GetIntitule()
{
    QString texte = "";
    switch (m_TitheGrade) {
    case AptusNon : texte += "Aptus Non"; break;
    case Exactis_Tertius : texte += "Exactis Tertius"; break;

    }

    if ( m_ProductionGrade != Inconnu)
    {

        texte += "(Grade de production : ";

        switch (m_ProductionGrade) {
        case I_Maximus      : texte += "I-Maximus"; break;
        case I_Extremis     : texte += "I-Extremis"; break;
        case I_Prima        : texte += "I-Prima"; break;
        case I_Secundi      : texte += "I-Secundi"; break;
        case I_Tertius      : texte += "I-Tertius"; break;
        case II_Maximus     : texte += "II-Maximus"; break;
        case II_Extremis    : texte += "II-Extremis"; break;
        case II_Prima       : texte += "II-Prima"; break;
        case II_Secundi     : texte += "II-Secundi"; break;
        case II_Tertius     : texte += "II-Tertius"; break;
        case III_Maximus    : texte += "III-Maximus"; break;
        case III_Extremis   : texte += "III-Extremis"; break;
        case III_Prima      : texte += "III-Prima"; break;
        case III_Secundi    : texte += "III-Secundi"; break;
        case III_Tertius    : texte += "III-Tertius"; break;
        case IV_Maximus     : texte += "IV-Maximus"; break;
        case IV_Extremis    : texte += "IV-Extremis"; break;
        case IV_Prima       : texte += "IV-Prima"; break;
        case IV_Secundi     : texte += "IV-Secundi"; break;
        case IV_Tertius     : texte += "IV-Tertius"; break;
        default             : texte += "Aucun"; break;
        }

        texte += ")";
    }
    return texte;
}
