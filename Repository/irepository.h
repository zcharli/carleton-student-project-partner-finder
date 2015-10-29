#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <QVector>

template<class TEntity>
class IRepository
{
public:
    //virtual ~IRepository();

    /*!
     *       @param: objectToSave: TEntity&
     *        @desc: saves the type TEntity to database,
     *               when TEntity.id is 0 or null:
     *                   insert -> returns ID of the new row
     *                   else update
     *      @return: saveSuccessful: int
     */
    virtual unsigned int save(const TEntity&) = 0;

    /*!
     *       @param: idToDelete: int
     *        @desc: deletes the type TEntity to database
     *      @return: success or failure: int
     */
    virtual unsigned int deleteFromRepo(const int) = 0;

    /*!
     *       @param: idToFetch: int
     *        @desc: fetchs the type TEntity to database
     *      @return: entityObject: TEntity&
     */
    virtual TEntity& fetchById(const int) = 0;

    /*!
     *       @param: idToFetch (optional): int
     *        @desc: fetchs all type TEntity to database
     *      @return: entityObject: QVector<TEntity*>&
     */
    virtual QVector<TEntity*>& fetchAll(const int=0) = 0;
};

#endif // IREPOSITORY_H
