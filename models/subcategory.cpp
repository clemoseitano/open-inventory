#include "subcategory.h"

QString SubCategory::toString() const {
    return name + " in " + QString::number(categoryId);
}
