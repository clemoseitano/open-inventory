#include "userlocation.h"

QString UserLocation::toString() const {
    return name + " at " + address;
}
