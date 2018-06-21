#include "utils.h"


Utils::Utils()
{
}

QString Utils::UniqueDatabaseName()
{
    QString uuid = QUuid::createUuid().toString();
    uuid = uuid.mid(1, uuid.length() - 2);
    return uuid + ".sqlite";
}
