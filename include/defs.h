typedef enum
{
    false, true
}               Booleen;

/*------------------------------------------------------------------------
  Table des segments
  	C'est un tableau qui contient les renseignements suivants
  	pour chaque segment:
  	. coordonnees des extremites
  	. longueur du segment
  	. cosinus et sinus du vecteur directeur
------------------------------------------------------------------------*/

typedef struct
{
    float           xdeb, ydeb;
    float           xfin, yfin;
    float           longueur;
    Booleen         affiche;			/* Marqueur de segment affiche */
}               Seg;

