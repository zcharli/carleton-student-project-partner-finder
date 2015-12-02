#ifndef USER_H
#define USER_H

#include "project.h"
#include "imappable.h"

#include <QString>

enum UserType {
    Administrator = 0,
    Student = 1
};

class User : private IMappable
{
public:
  User(QString, QString, QString);
  User();
  virtual ~User();

    //accessor Functions
    //getters
    /*!
   *       @param: none
   *        @desc: get the User's Firstname
   *      @return: firstName: QString&
   */
    QString& getFirstName();

    /*!
    *       @param: none
    *        @desc: get the User's LastName
    *      @return: lastName: QString&
    */
    QString& getLastName();

    /*!
    *       @param: none
    *        @desc: get the User's UserName
    *      @return: userName: QString&
    */
    QString& getUserName();

    //setters
    /*!
    *       @param: newFirstName: QString&
    *        @desc: sets the User's Firstname
    *      @return: void
    */
    void setFirstName(QString);

    /*!
    *       @param: newLastName: QString&
    *        @desc: sets the User's LastName
    *      @return: void
    */
    void setLastName(QString);

    /*!
    *       @param: newUserName: QString&
    *        @desc: sets the User's UseraName
    *      @return: void
    */
    void setUserName(QString);

    /*!
    *       @param: id: int
    *        @desc: sets the user's id
    *      @return: void
    */
    void setUserId(int);

    /*!
    *       @param: none
    *        @desc: returns the firstname lastname (username)
    *      @return: QString
    */
    QString getUsernameIdentifer();

    /*!
    *       @param: none
    *        @desc: gets the user's id
    *      @return: id: int
    */
    int getUserId();

    /*!
    *       @param: none
    *        @desc: gets the user's id's type
    *      @return: userType: int / UserType
    */
    UserType getUserType();

    /*!
    *       @param: none
    *        @desc: gets the user's id's type
    *      @return: userType: int / UserType
    */
    void setUserType(UserType);

    /*!
    *       @param: none
    *        @desc: get the number of projects this user is associated with
    *      @return: number of projects created: int
    */
    int getNumberOfProjectsAssociated();

    /*!
    *       @param: IDofProjectToAdd: int
    *        @desc: adds the given project to the list of projects assocaited to the User
    *      @return: void
    */
    void addProjectToUser(int);

    /*!
    *       @param: IdofProjectToRemove: int
    *        @desc: removes the given project from the list of projects associated to the user
    *               (if the project is contained in the list). Does nothing otherwise
    *      @return: void
    */
    void removeProjectFromUser(int);

    /*!
    *       @param: none
    *        @desc: returns the list of projects that are associated to this user
    *      @return: myProjects: QVection<Project *>
    */
    QSet<int>& getProjectsAssociated();

    /*!
    *       @param: projectToCheck
    *        @desc: checks if the project ID is inside the list
    *      @return: project: bool
    */
    bool containsProject(Project&);

    /*!
    *       @param: empty Json Object: QJsonObject&
    *        @desc: serializes the object implementing into JSON
    *      @return: success or failure: bool
    */
    virtual bool serializeJSONForSave(QJsonObject&) = 0;

    /*!
    *       @param: objectToDeSerialize: QJsonObject&
    *        @desc: deserializes the the JSON object to create the object back
    *      @return: success or failure: bool
    */
    virtual bool deserializeJSONFromRetrieve(const QJsonObject&) = 0;


protected:
    QString firstName;
    QString lastName;
    QString userName;
    UserType userType;
    QSet<int> myProjects; //keep only the ids of the projects
    //Needed when quering database
    int id;
};

#endif // USER_H
