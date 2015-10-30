#ifndef USER_H
#define USER_H

#include <QString>

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


protected:
   QString firstName;
   QString lastName;
   QString userName;
   UserType userType;

   //Needed when quering database
   int id;
};

#endif // USER_H
