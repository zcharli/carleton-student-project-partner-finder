#ifndef USER_H
#define USER_H

#include <QString>
#include "Models/project.h"

enum UserType {
    Administrator = 0,
    Student = 1
};

class User
{
public:
  User(QString&, QString&, QString&, int);
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
   void setFirstName(QString&);

   /*!
    *       @param: newLastName: QString&
    *        @desc: sets the User's LastName
    *      @return: void
    */
   void setLastName(QString&);

   /*!
    *       @param: newUserName: QString&
    *        @desc: sets the User's UseraName
    *      @return: void
    */
   void setUserName(QString&);

   /*!
    *       @param: id: int
    *        @desc: sets the user's id
    *      @return: void
    */
   void setUserId(int);

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
    *       @param: projectToAdd: Project*
    *        @desc: adds the given project to the list of projects assocaited to the User
    *      @return: void
    */
   void addProjectToUser(Project*);

   /*!
    *       @param: projectToRemove: Project*
    *        @desc: removes the given project from the list of projects associated to the user
    *               (if the project is contained in the list). Does nothing otherwise
    *      @return: void
    */
   void removeProjectFromUser(Project*);

   /*!
    *       @param: none
    *        @desc: returns the list of projects that are associated to this user
    *      @return: myProjects: QVection<Project *>
    */
   QVector<Project*>& getProjectsAssociated();

   /*!
    *       @param: bool
    *        @desc: checks if the project ID is inside the list
    *      @return: project: Project*
    */
   bool containsProject(Project*);

protected:
   QString firstName;
   QString lastName;
   QString userName;
   UserType userType;
   QVector<Project*> myProjects;
   //Needed when quering database
   int id;
};

#endif // USER_H
