#include "sale.h"

QString Sale::toString() const {
    return productId + " sold to " + customerName;
}
