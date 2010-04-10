#ifndef ICOMMUNICATIONGRAPHICALSERVER_H_
#define ICOMMUNICATIONGRAPHICALSERVER_H_

#include <list>

#include "Window.h"

/**
 * \interface ICommunicationGraphicalServer
 * \brief Interface pour la communication avec les serveurs graphiques
 * Cette interface doit etre implementer pour tout les serveurs graphiques existants.
 * Elle permet la communication avec le serveur graphique pour recuperer des informations sur les fenetres ou sur generer des evenements souris.
 */

class ICommunicationGraphicalServer {
public:

    /**
     * \brief Destructeur
     */
    virtual ~ICommunicationGraphicalServer() {
    }

    /**
     * \brief Permet de recuperer la liste de toutes les fenetres affichees a l'ecran.
     * \param windows [out] la liste de toutes les fenetres affichees a l'ecran, cette liste est vide a l'entree.
     * \return Vrai en cas de succes, faux en cas d'erreur
     */
    virtual bool getWindows(std::list<Ceg::Window> & windows) = 0;

    /**
     * \brief Permet de recuperer la fenetre possedant le focus
     * \param windows [out] la liste de toutes les fenetres affichees a l'ecran, cette liste est vide a l'entree.
     * \return Vrai en cas de succes, faux en cas d'erreur
     */

    virtual bool getFocusedWindow(Ceg::Window & focusedWindow) = 0;

    virtual bool setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow) = 0;

    virtual bool refreshWindowInfo(Ceg::Window &) = 0;

    virtual bool generateClickEvent(short int x, short int y) = 0;
};

#endif // ICOMMUNICATIONGRAPHICALSERVER_H_
