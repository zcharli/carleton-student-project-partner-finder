#ifndef IMAPPABLE_H
#define IMAPPABLE_H

#include <QJsonObject>

/*!
 * \brief The IMappable class used ot serialize the inheriting object
 */

class IMappable
{
public:

    /*!
     *       @param: empty Json Object: QJsonObject&
     *        @desc: serializes the object implementing into JSON
     *      @return: objectInJSON: QJsonObject&
     */
    virtual bool serializeJSONForSave(QJsonObject&) = 0;

    /*!
     *       @param: objectToDeSerialize: QJsonObject&
     *        @desc: deserializes the the JSON object to create the object back
     *      @return: success or failure: bool
     */
    virtual bool deserializeJSONFromRetrieve(const QJsonObject&) = 0;

};

#endif // IMAPPABLE_H
