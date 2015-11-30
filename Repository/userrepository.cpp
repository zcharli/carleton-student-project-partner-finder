#include "userrepository.h"

#include "DataAccessLayer/qualification.h"
#include "DataAccessLayer/mapconfigs.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringBuilder>
#include <QVector>

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

int UserRepository::userCreatedPPP(QJsonObject& pppJSON, int userId)
{
    //QJsonObject userJSON = user[USER_KEY].toObject();
    //QJsonObject pppJSON = user[PPP_KEY].toObject();
    QJsonArray qualificationArrayJSON = pppJSON[QUALIFICATIONS_KEY].toArray();
    qDebug() << qualificationArrayJSON.size();
    QSqlQuery insertPPP(this->db);


    //Qualification::TechnicalScoreForStudentUser(static_cast<StudentUser&>(user), personalScore, teamMateScore);
    insertPPP.prepare("INSERT INTO ppp (personal_tech_score, we_bs, teammate_tech_score) VALUES (:personal_tech_score, :we_bs, :teammate_tech_score)");
    insertPPP.bindValue(":personal_tech_score", pppJSON[PPP_personalTechnicalScore].toInt());
    insertPPP.bindValue(":we_bs", pppJSON[PPP_workEthic].toInt());
    insertPPP.bindValue(":teammate_tech_score", pppJSON[PPP_teammateTechnicalScore].toInt());
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
    pppJSON[PPP_pppID] = pppID;
    //user[STUDENT_pppIDForFetch] = pppJSON;

    QString qualificationQuery;
    int i;
    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
        qualificationQuery = QString("Insert into ppp_qualifications (qualification_id,ppp_id,value) values (%1,%2,%3);").
                arg(QString::number(i+1),QString::number(pppID),QString::number(qualificationArrayJSON[i].toObject()[QUALIFICATION_value].toInt()));
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
            arg(QString::number(pppID),QString::number(userId));

    QSqlQuery insertQualifications(this->db);
    insertQualifications.prepare(qualificationQuery);
    if(!insertQualifications.exec())
    {
        qDebug() << "insertQualifications error:  "<< insertQualifications.lastError();
        qDebug() << qualificationQuery;
        return insertQualifications.lastError().number();
    }

    return 0;
}

int UserRepository::fetchPPPForUser(QJsonObject& user, int pppId, bool full)
{
    QJsonObject pppJSON;


    // This join will ensure we only return PPP qualifications if the user has a PPP
    // This also helps ensure that after a student deletes their profile, then nothing will return
    if(full)
    {
        QJsonArray qualificationArrayJSON;
        QString fetchQuery = "Select * from ppp_qualifications p join users u on u.ppp_id = p.ppp_id where p.ppp_id = :pppid";
        QSqlQuery fetchPPP(this->db);
        fetchPPP.prepare(fetchQuery);
        fetchPPP.bindValue(":pppid",pppId);
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
                QJsonObject qualification;
                // Qualification returned will be copied to the PPP
                qualification[QUALIFICATION_type] = fetchPPP.value(0).toInt() - 1;
                qualification[QUALIFICATION_value] = fetchPPP.value(2).toInt();

                qualificationArrayJSON.append(qualification);
            }
            user[STUDENT_pppIDForFetch] = pppId;
        }
        else
        {
            qDebug() << "fetchPPPForUser error:  "<< fetchPPP.lastError();
            qDebug() << fetchQuery;
            return fetchPPP.lastError().number();
        }
        //success
        pppJSON[QUALIFICATIONS_KEY] = qualificationArrayJSON;
    }

    QString fetchPPPProxyQuery = "select we_bs, teammate_tech_score, personal_tech_score from ppp where ppp_id=:pppid";
    QSqlQuery fetchPPPProxy(this->db);
    fetchPPPProxy.prepare(fetchPPPProxyQuery);
    fetchPPPProxy.bindValue(":pppid",pppId);
    if(fetchPPPProxy.exec())
    {
        if(fetchPPPProxy.next())
        {
            // Indexes
            //  0 -> web_bs
            //  1 -> teammate_tech_score
            //  2 -> personal_tech_score

            char workEthic = (char)fetchPPPProxy.value(0).toInt();
            int teamScore = fetchPPPProxy.value(1).toInt();
            int personalScore = fetchPPPProxy.value(2).toInt();

            pppJSON[PPP_personalTechnicalScore] = personalScore;
            pppJSON[PPP_teammateTechnicalScore] = teamScore;
            pppJSON[PPP_workEthic] = workEthic;
        }
    }
    else
    {
        qDebug() << "fetchPPPProxy error:  "<< fetchPPPProxy.lastError();
        return fetchPPPProxy.lastError().number();
    }

    pppJSON[PPP_pppID] = pppId;
    user[PPP_KEY] = pppJSON;

    return 0;
}

int UserRepository::userUpdatedPPP(QJsonObject& pppJSON)
{
    if(!pppJSON.contains(QUALIFICATIONS_KEY))
    {
        return -1;
    }
    QJsonArray qualificationArrayJSON = pppJSON[QUALIFICATIONS_KEY].toArray();
    QString massUpdateQuery;
    QSqlQuery updatePPPQuery(this->db);
    int i;
    for(i=0;i<NUMBER_OF_QUALIFICATIONS;++i)
    {
        massUpdateQuery = QString("Update ppp_qualifications set value=%1 where ppp_id=%2 and qualification_id=%3;").arg(
                    QString::number(qualificationArrayJSON[i].toObject()[QUALIFICATION_value].toInt()), QString::number(pppJSON[PPP_pppID].toInt()),
                    QString::number(qualificationArrayJSON[i].toObject()[QUALIFICATION_type].toInt() + 1));
        updatePPPQuery.prepare(massUpdateQuery);

        if(!updatePPPQuery.exec())
        {
            qDebug() << "userUpdatedPPP error:  "<< updatePPPQuery.lastError();
            return updatePPPQuery.lastError().number();
        }
    }

    QString updatePPPScore = "update ppp set we_bs=:wb,teammate_tech_score=:ts,personal_tech_score=:ps where ppp_id=:pppid";
    QSqlQuery updatePPPScoreQuery(this->db);
    updatePPPScoreQuery.prepare(updatePPPScore);
    updatePPPScoreQuery.bindValue(":pppid",pppJSON[PPP_pppID].toInt());
    updatePPPScoreQuery.bindValue(":wb", pppJSON[PPP_workEthic].toInt());
    updatePPPScoreQuery.bindValue(":ts", pppJSON[PPP_teammateTechnicalScore].toInt());
    updatePPPScoreQuery.bindValue(":ps", pppJSON[PPP_personalTechnicalScore].toInt());
    if(!updatePPPScoreQuery.exec())
    {
        qDebug() << "fetchPPPProxy error:  "<< updatePPPScoreQuery.lastError();
        return updatePPPScoreQuery.lastError().number();
    }

    // Successful
    return 0;
}

int UserRepository::userDeletedPPP(int userId)
{
    // Deleting a PPP is the same as deleting the association of a ppp to user
    // This method of deletion can enable a user to get his PPP back.
    // However once deleted, he can create a new PPP
    QString removePPPfromUserQueryStr = "Update users set ppp_id=0 where user_id=:id";
    QSqlQuery deleteQuery(this->db);
    deleteQuery.bindValue(":id", userId);
    deleteQuery.prepare(removePPPfromUserQueryStr);

    if(!deleteQuery.exec())
    {
        qDebug() << "userDeletedPPP error:  " << this->db.lastError();
        return deleteQuery.lastError().number();
    }

    //successful
    return 0;
}

int UserRepository::retrieveUserWithUsername(QJsonObject& user, QString& username, int type)
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

            user[USER_id] = id;
            user[USER_firstName] = fname;
            user[USER_lastName] = lname;
            user[USER_userName] = username;
            user[USER_userType] = type;

            // Going to get PPP only when needed so we won't populate that now.
            if(loginQuery.value(4).toInt() == Student)
            {
                //set the pppIDForFetch for the StudentUser
                user[STUDENT_pppIDForFetch] = loginQuery.value(5).toInt();
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

int UserRepository::createUser(QJsonObject& user)
{
    // Inserts a row in users table
    QString createUserQueryStr = "Insert into users (username,fname,lname,type) values (:u,:f,:l,:t)";
    QSqlQuery createQuery(this->db);
    if(this->db.isOpen())
    {
        createQuery.prepare(createUserQueryStr);
        createQuery.bindValue(":u",user[USER_userName].toString());
        createQuery.bindValue(":f",user[USER_firstName].toString());
        createQuery.bindValue(":l", user[USER_lastName].toString());
        createQuery.bindValue(":t", user[USER_userType].toInt());

        if(!createQuery.exec())
        {
            qDebug() << "createUser error:  " << this->db.lastError();
            return createQuery.lastError().number();
        } else // successful
        {
            int userId = 0;
            QSqlQuery getLastUser(this->db);
            getLastUser.prepare("Select max(user_id) from users");
            if(getLastUser.exec())
            {
                if(getLastUser.next())
                {
                    userId = getLastUser.value(0).toInt();
                    user["id"] = userId;
                }
            }
            else
            {
                qDebug() << "getProjectID error:  "<< getLastUser.lastError();
                return getLastUser.lastError().number();
            }

            return 0;
        }

    }

    return -1;
}
