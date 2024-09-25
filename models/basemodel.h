#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QDateTime>
#include <QRandomGenerator>

class BaseModel {
public:
    qint64 id;
    QDateTime createdAt;
    QDateTime updatedAt;
    qint64 generateId();
    bool fromDb = false;

    BaseModel(const qint64 id);
    BaseModel();
    virtual ~BaseModel();
};

#endif // BASEMODEL_H
