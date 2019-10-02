#include "utils.h"

//TODO: crossplatform delete file
#include "Windows.h"
#include "shellapi.h"

#include <QDebug>
#include <QUuid>
#include <QFile>
#include <QDir>


Utils::Utils()
{
}

Utils::~Utils()
{
}

QString Utils::uniqueDatabaseName()
{
    QString uuid = QUuid::createUuid().toString();
    uuid = uuid.mid(1, uuid.length() - 2);
    return uuid + ".sqlite";
}

void Utils::deleteFile(const QString &filename)
{
    QFileInfo fileinfo(filename);
    if( !fileinfo.exists() ) return;
        //throw OdtCore::Exception( "File doesnt exists, cant move to trash" );

    WCHAR from[ MAX_PATH ];
    memset( from, 0, sizeof( from ));
    int l = fileinfo.absoluteFilePath().toWCharArray( from );
    Q_ASSERT( 0 <= l && l < MAX_PATH );
    from[ l ] = '\0';
    SHFILEOPSTRUCT fileop;
    memset( &fileop, 0, sizeof( fileop ) );
    fileop.wFunc = FO_DELETE;
    fileop.pFrom = from;
    fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
    int rv = SHFileOperation( &fileop );
    if( 0 != rv )
    {
        qDebug() << rv << QString::number( rv ).toInt( nullptr, 8 );
        return;
        //throw OdtCore::Exception( "move to trash failed" );
    }
    // TODO: delete in thrashbin on Linux
}


QFileInfo Utils::replaceFile(const QString &path, const QString &newPath)
{
    QDir pathToFolder = QFileInfo(newPath).absoluteDir();

    if(!pathToFolder.exists())
    {
        QDir().mkpath(pathToFolder.path());
        pathToFolder.mkdir(pathToFolder.path());
    }

    QFileInfo fileInfo(newPath);
    fileInfo.baseName();
    fileInfo.completeSuffix();

    auto currentNewPath = newPath;
    int i = 1;
    while(QFile::exists(currentNewPath))
    {
        currentNewPath = pathToFolder.filePath(
                    fileInfo.baseName() +
                    QString(" (%1).").arg(i) +
                    fileInfo.completeSuffix());
    }

    QFile::copy(path, currentNewPath);

    return QFileInfo(currentNewPath);
}
