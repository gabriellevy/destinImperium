#include "age.h"
#include "ui_carac.h"
#include "../destinLib/abs/univers.h"
#include <QDebug>
#include "../destinLib/gestionnairecarac.h"
#include "genviehumain.h"

Age::Age(int ageMois)
    :Carac(GenVieHumain::AGE, GenVieHumain::AGE, QString::number(ageMois),
           "", "", MODE_AFFICHAGE::ma_Texte,
           nullptr, "", "")
{

}

bool Age::AfficherValeur()
{
    if ( m_DataCarac.AUneValeur() )
    {
        ui->labelValeur->show();
        ui->labelValeur->setFont( *Univers::BASE_FONT);
        int ageMois = m_DataCarac.GetValeur().toInt();
        int ageAnnee = ageMois/12;
        ageMois = (ageMois % 12);
        QString ageStr = QString::number(ageAnnee) + " ans " +
                (ageMois> 0 ? (QString::number(ageMois) + " mois"):"");
        ui->labelValeur->setText(ageStr);
        ui->labelValeur->setToolTip(this->GetCaracDescription());
        return true;
    }
}
