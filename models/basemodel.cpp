#include "basemodel.h"

BaseModel::BaseModel()
        : id(generateId()),
          createdAt(QDateTime::currentDateTime()),
          updatedAt(QDateTime::currentDateTime()) {}


BaseModel::BaseModel(const qint64 id)
    : id(id),
    createdAt(QDateTime::currentDateTime()),
    updatedAt(QDateTime::currentDateTime()) {}

BaseModel::~BaseModel() {}

qint64 BaseModel::generateId() {
    return static_cast<qint64>(QRandomGenerator::global()->generate64() & 0xFFFFFFFFFFFF);
}
