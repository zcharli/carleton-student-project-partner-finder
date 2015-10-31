#include "userrepository.h"
#include "Models/user.h"
#include "Models/studentuser.h"
#include "Models/projectpartnerprofile.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringBuilder>
#include <QVector>
#include "Models/qualification.h"
#include "QDebug"
#include <QSqlError>

/*!
 * \brief UserRepository::UserRepository
 * \param db
 * \note  Sql Returns 0 if successful, 1 to 4 if error (defined in QSqlError)
 */

UserRepository::UserRepository(QSqlDatabase& db)
{
  this->db = db;
}

UserRepository::~UserRepository() {}

int UserRepository::userCreatedPPP(User &user, ProjectPartnerProfile& ppp)
{
    QSqlQuery insertPPP(this->db);

    float personalScore = 0;
    float teamMateScore = 0;
    Qualification::TechnicalScoreForStudentUser(static_cast<StudentUser&>(user), personalScore, teamMateScore);
    insertPPP.prepare("INSERT INTO ppp (personal_tech_score, we_bs, teammate_tech_score) VALUES (:personal_tech_score, :we_bs, :teammate_tech_score)");
    insertPPP.bindValue(":personal_tech_score", personalScore);
    insertPPP.bindValue(":we_bs", ppp.getQualification(userWorkEthic).getValue());
    insertPPP.bindValue(":teammate_tech_score", teamMateScore);
    if(!insertPPP.exec())
    {
        qDebug() << "userCreatedPPP error:  "<< insertPPP.lastError();
        return insertPPP.lastError().number();
    }

    int pppID = 0;
    QSqlQuery getPPPId(this->db);
    getPPPId.prepare("SELECT max(ppp_id) FROM ppp;");
    if(getPPPId.exec())
    {
        if(getPPPId.next())
        {
            pppID = getPPPId.value(0).toInt();
        }
    }
    if(pppID == 0)
    {
        qDebug() << "Unsuccessfully retrived last PPP id inserted!"<< getPPPId.lastError();
        return getPPPId.lastError().number();
    }

    // Set the PPP since its been created
    ppp.setPPPID(pppID);

    // Now start the big transaction to save Qualifications
    //  Proper way to do this!!!!!
    /*QString qualificationQuery;
    int i;
    qualificationQuery += "begin transaction;";
    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
        //  have to convert args to string first!!
        qualificationQuery += QString("Insert into ppp_qualifications (qualification_id,ppp_id,value) values (%1,%2,%3);").
                arg(QString::number(i),QString::number(pppID),QString::number(ppp.getQualification(i).getValue()));
    }
    qualificationQuery += QString("Update users set ppp_id=%1 where user_id=%2;").
            arg(QString::number(pppID),QString::number(user.getUserId()));
    qualificationQuery += "commit;";

    QSqlQuery insertQualifications(this->db);
    insertQualifications.prepare(qualificationQuery);
    if(!insertQualifications.exec())
    {
        qDebug() << "insertQualifications error:  "<< insertQualifications.lastError();
        qDebug() << qualificationQuery;
        return insertQualifications.lastError().number();
    }*/


    //  Bad but woks! ######################################
    QString qualificationQuery;
    int i;
    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
        qualificationQuery = QString("Insert into ppp_qualifications (qualification_id,ppp_id,value) values (%1,%2,%3);").
                arg(QString::number(i),QString::number(pppID),QString::number(ppp.getQualification(i).getValue()));
                QSqlQuery insertQualifications(this->db);
                insertQualifications.prepare(qualificationQuery);
                if(!insertQualifications.exec())
                {
                    qDebug() << "insertQualifications error:  "<< insertQualifications.lastError();
                    qDebug() << qualificationQuery;
                    return insertQualifications.lastError().number();
                }
    }
    qualificationQuery = QString("Update users set ppp_id=%1 where user_id=%2;").
            arg(QString::number(pppID),QString::number(user.getUserId()));

    QSqlQuery insertQualifications(this->db);
    insertQualifications.prepare(qualificationQuery);
    if(!insertQualifications.exec())
    {
        qDebug() << "insertQualifications error:  "<< insertQualifications.lastError();
        qDebug() << qualificationQuery;
        return insertQualifications.lastError().number();
    }
    //#######################################################

    //success;
    return 0;
}

int UserRepository::fetchPPPForUser(User &user, ProjectPartnerProfile& ppp)
{
    // This join will ensure we only return PPP qualifications if the user has a PPP
    // This also helps ensure that after a student deletes their profile, then nothing will return
    StudentUser& student= static_cast<StudentUser&>(user);
    QString fetchQuery = "Select * from ppp_qualifications p join users u on u.ppp_id = p.ppp_id where p.ppp_id = " + QString::number(student.getFetchIDForPPP());
    QSqlQuery fetchPPP(this->db);
    fetchPPP.prepare(fetchQuery);
    //fetchPPP.bindValue(":id", (static_cast<StudentUser&>(user)).getFetchIDForPPP());
    // Execute this fetch and populate the ppp's qualifications
    if(fetchPPP.exec())
    {
        while(fetchPPP.next())
        {
            // Indexes
            //  0 -> qualification_id (also qualification type)
            //  1 -> ppp_id
            //  2 -> value (int)

            // Qualification returned will be copied to the PPP
            Qualification returnedQualification((QualificationType)fetchPPP.value(0).toInt(),fetchPPP.value(2).toInt());
            ppp.changeQualification(returnedQualification);
        }
        ppp.setPPPID(student.getFetchIDForPPP());

    }
    else
    {
        qDebug() << "fetchPPPForUser error:  "<< fetchPPP.lastError();
        qDebug() << fetchQuery;
        return fetchPPP.lastError().number();
    }
    //success
    return 0;
}

int UserRepository::userUpdatedPPP(User &user, ProjectPartnerProfile &ppp)
{
    /*  Correct Way to do this but not working for some reason
     *  Best bet is to loop over every insert -> This is slower
     *
    // Create a big transaction to speed up the query
    // We update all qualification whether or not they changed
    QString massUpdateQuery = "begin transaction;";
    QSqlQuery updatePPPQuery(this->db);
    int i;
    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
        massUpdateQuery += QString("Update ppp_qualifications set value=%1 where ppp_id=%2 and qualification_id=%3;").arg(
                    QString::number(ppp.getQualification(i).getValue()), QString::number(ppp.getPPPID()), QString::number(ppp.getQualification(i).getType()));
    }
    massUpdateQuery += "commit;";

    updatePPPQuery.prepare(massUpdateQuery);
    if(!updatePPPQuery.exec())
    {
        qDebug() << "userUpdatedPPP error:  "<< updatePPPQuery.lastError();
        return updatePPPQuery.lastError().number();
    }
    // Successful
    return 0;*/

    //  BAD!!!!! BUT WORKS ##########################################
    QString massUpdateQuery;
    QSqlQuery updatePPPQuery(this->db);
    int i;
    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
        massUpdateQuery = QString("Update ppp_qualifications set value=%1 where ppp_id=%2 and qualification_id=%3;").arg(
                    QString::number(ppp.getQualification(i).getValue()), QString::number(ppp.getPPPID()), QString::number(ppp.getQualification(i).getType()));
        updatePPPQuery.prepare(massUpdateQuery);

        if(!updatePPPQuery.exec())
        {
            qDebug() << "userUpdatedPPP error:  "<< updatePPPQuery.lastError();
            return updatePPPQuery.lastError().number();
        }
    }

    // Successful
    return 0;
    //##########################################
}

int UserRepository::userDeletedPPP(User &user, ProjectPartnerProfile &ppp)
{
    // Deleting a PPP is the same as deleting the association of a ppp to user
    // This method of deletion can enable a user to get his PPP back.
    // However once deleted, he can create a new PPP
    QString removePPPfromUserQueryStr = "Update users set ppp_id=0 where user_id=:id";
    QSqlQuery deleteQuery(this->db);
    deleteQuery.bindValue(":id", user.getUserId());
    deleteQuery.prepare(removePPPfromUserQueryStr);

    if(!deleteQuery.exec())
    {
        qDebug() << "userDeletedPPP error:  " << this->db.lastError();
        return deleteQuery.lastError().number();
    }

    //successful
    return 0;
}

int UserRepository::retrieveUserWithUsername(QString& username, User& user, int type)
{
    // Will retrive User and all it's PPP
    QString checkUsernameQueryStr = "Select * from users where type=:type and username=:usrnm";
    QSqlQuery loginQuery(this->db);
    loginQuery.prepare(checkUsernameQueryStr);
    loginQuery.bindValue(":type",type);
    loginQuery.bindValue(":usrnm", username);

    if(loginQuery.exec())
    {
        if(loginQuery.next())
        {
            // Indexes
            //  0 -> user_id
            //  1 -> username
            //  2 -> fname
            //  3 -> lname
            //  4 -> type (admin/student)
            //  5 -> ppp_id
            int id = loginQuery.value(0).toInt();
            QString fname = QString(loginQuery.value(2).toString());
            QString lname = QString(loginQuery.value(3).toString());

            user.setUserId(id);
            user.setFirstName(fname);
            user.setLastName(lname);
            user.setUserName(username);

           // Going to get PPP only when needed so we won't populate that now.
           if(loginQuery.value(4).toInt() == Student)
           {
              //set the pppIDForFetch for the StudentUser
              static_cast<StudentUser&>(user).setFetchIDForPPP(loginQuery.value(5).toInt());
           }
        }
        else
        {
            qDebug() << "No user found with that username";
            return -1; // No user found
        }
    }
    else
    {
        qDebug() << "retrieveUserWithUsername error:  " << this->db.lastError();
    }
    return 0;
}

int UserRepository::createUser(User& user)
{
    // Inserts a row in users table
    QString createUserQueryStr = "Insert into users (username,fname,lname,type) values (:u,:f,:l,:t)";
    QSqlQuery createQuery(this->db);
    if(this->db.isOpen())
    {
        createQuery.prepare(createUserQueryStr);
        createQuery.bindValue(":u",user.getUserName());
        createQuery.bindValue(":f",user.getFirstName());
        createQuery.bindValue(":l", user.getLastName());
        createQuery.bindValue(":t", (int)user.getUserType());
        if(!createQuery.exec())
        {
            qDebug() << "createUser error:  " << this->db.lastError();
            return createQuery.lastError().number();
        } else // successful
        {
            return 0;
        }

    }
    return -1;
}
