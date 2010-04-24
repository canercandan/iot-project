#ifndef WINDOWGEOMETRY_H_
#define WINDOWGEOMETRY_H_

/*! \class BasicWindowInfo
 * \brief Class regroupant toutes les informations basiques communes a toutes fenetres affiches a l ecran
 */
class WindowGeometry
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe BasicWindowInfo
     *
     */
    WindowGeometry(short int x = 0, short int y = 0, short int width = 0, short int height = 0);

public:
    short int _x; /*!< Position absolue sur l'axe des abscisses du coint haut gauche de la fenetre */
    short int _y; /*!< Position absolue sur l'axe des ordonnes du coint haut gauche de la fenetre */
    short int _width; /*!< Largeur de la fenetre */
    short int _height; /*!< Hauteur de la fenetre */
};

#endif // WINDOWGEOMETRY_H_
