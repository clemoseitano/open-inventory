#include "product.h"

QString Product::toString() const {
    return name + " - " + code + ", " + QString::number(quantity) + " available";
}
