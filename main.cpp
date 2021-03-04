#include "Painter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef QT_DEBUG
    qSetMessagePattern("[%{time hh:mm:ss.zzz}]%{file} %{if-debug}%{endif}%{if-warning}W%{endif}"
                       "%{if-critical}C%{endif}%{if-fatal}F%{endif}"
                       "%{file}:%{line}\n"
"                                     ---->%{message}\r");
#endif
    QApplication a(argc, argv);
    Painter w;
    //    QString fileName = fileNName;
    //    w.setWindowTitle(fileName);
    w.show();
    return a.exec();
}
