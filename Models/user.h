#ifndef USER_H
#define USER_H

#include <QString>

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

protected:
   QString firstName;
   QString lastName;
   QString userName;

   //Needed when quering database
   int id;
};

#endif // USER_H
