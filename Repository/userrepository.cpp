#include "userrepository.h"
#include "Models/user.h"
#include "Models/projectpartnerprofile.h"
#include "Models/qualification.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringBuilder>
#include "Models/qualification.h"
#include "QDebug"

UserRepository::UserRepository(QSqlDatabase& db)
{
  this->db = db;
}

UserRepository::~UserRepository() {}

int UserRepository::userCreatedPPP(User &user, ProjectPartnerProfile& ppp)
{
    /*QSqlQuery insertPPP(this->db);
    // "SELECT last_insert_rowid();"
    //QVector<Qualification> qualifications = ppp.getQualifications();
    //  My mod

    // We need to add teammate and personal tech score here
    insertPPP.prepare("INSERT INTO ppp (we_bs,user_id) VALUES (:we_bs,:user_id)");
    insertPPP.bindValue(":we_bs", qualifications[userWorkEthic].value);
    insertPPP.bindValue(":user_id", user.getUserId());
    if(!insertPPP.exec())
    {
        qDebug() << "userCreatedPPP error:  ";// << this->db.lastError();
    }

    int pppID = 0;
    QSqlQuery getPPPId(this->db);
    getPPPId.prepare("SELECT last_insert_rowid()");
    if(getPPPId.exec())
    {
        if(getPPPId.next())
        {
            pppID = getPPPId.value(0).toInt();
        }
    }
    if(pppID == 0)
    {
        qDebug() << "Unsuccessfully retrived last PPP id inserted!";// << this->db.lastError();
    }

    // Set the PPP since its been created
    ppp.setPPPID(pppID);

    // Now start the big transaction to save Qualifications
    QString qualificationQuery;
    int i;
    qualificationQuery += "start transactions;";
    for(i=0;i<qualifications.size();++i)
    {
        qualificationQuery += QString("Insert into ppp_qualifications (qualification_id,ppp_id,value) values (%d,%d,%d);").arg(
                    i, pppID, qualifications[i].value);
    }
    qualificationQuery += QString("Update users set ppp_id=%d where user_id=%d;").arg(pppID,user.getUserId());
    qualificationQuery += "commit;";
    QSqlQuery insertQualifications(qualificationQuery);
    if(!insertQualifications.exec())
    {
        qDebug() << "insertQualifications error:  ";// << this->db.lastError();
    }

*/
    return 0;
}

int UserRepository::fetchPPPForUser(User &user, ProjectPartnerProfile& ppp)
{
    QString fetchQuery = QString("Select * from ppp_qualifications where ppp_id=%d").arg(ppp.getPPPID());
    QSqlQuery fetchPPP(fetchQuery);
    // Execute this fetch and populate the ppp's qualifications
    if(fetchPPP.exec())
    {
        while(fetchPPP.next())
        {
            // Indexes
            //  0 -> qualification_id
            //  1 -> ppp_id
            //  2 -> value (int)
            //Qualification qu
            //pppID = fetchPPP.value(0).toInt();
        }
    }
    return 0;
}

int UserRepository::userUpdatedPPP(User &user, ProjectPartnerProfile &ppp)
{
    //TODO:
    return 0;
}

int UserRepository::userDeletedPPP(User &user, ProjectPartnerProfile &ppp)
{
    //TODO:
    return 0;
}

int UserRepository::retrieveUserWithUsername(QString& username, User& user)
{
  //TODO:
  return 0;
}

int UserRepository::createUser(User& user)
{
  //TODO:
  return 0;
}
