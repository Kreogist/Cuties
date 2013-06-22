#ifndef GDB_H
#define GDB_H

#include <QProcess>

class gdb : public QProcess
{
    Q_OBJECT
public:
    explicit gdb(QObject *parent = 0);

    void setGDBPath(const QString& path);
    bool checkGDBPath();

    void runGDB(const QString& filePath);
    void watchVariable(const QString& var);

    
signals:
    
public slots:

private:
    static QString gdbPath;
    
};

#endif // GDB_H
