#ifndef CARACCMDT_H
#define CARACCMDT_H
#include "../destinLib/carac.h"

class EmplacementCmdt;

/**
 * @brief Carac qui contient un des commandements et affiche son contenu
 */
class CaracCmdt : public Carac
{
public:
    explicit CaracCmdt(EmplacementCmdt* emplacementCmdt, QWidget *parent = nullptr);

    EmplacementCmdt* m_EmplacementCmdt;
};

#endif // CARACCMDT_H
