#include "cdatabaseadapter.h"

CDatabaseAdapter::CDatabaseAdapter()
{
    _db = CDatabase();
    _filename = filename;
}

CDatabaseAdapter::~CDatabaseAdapter()
{

}

QList<CBook> CDatabaseAdapter::books()
{
    return QList<CBook>();
}