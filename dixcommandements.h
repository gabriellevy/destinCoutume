#ifndef DIXCOMMANDEMENTS_H
#define DIXCOMMANDEMENTS_H

#include <QWidget>
#include "../destinLib/histoire.h"

class DixCommandements : public Histoire
{
    Q_OBJECT

public:
    DixCommandements(QWidget *parent = nullptr);

    virtual void GenererHistoire();

    virtual void GenererThemes();

private:
    void GenererEvtsAccueil();
    virtual void GenererPersos();
};

#endif // DIXCOMMANDEMENTS_H
