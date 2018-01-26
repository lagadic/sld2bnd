/************************************************************************

 TITLE		: reduce.c

 DESCRIPTION	: Le module "reduce.c" contient les procedures de gestion
      de reduction d'une surface polygonale "Bound" par suppression
      de points, d'aretes et de faces.

 Avant usage, faire preceder les procedures d'un appel a "open_reduce".
 Apres usage, faire suivre   les procedures d'un appel a "close_reduce".

 VERSION	: 1.003

 ABSTRACT	:

 open_reduce		Ouvre le mode "reduce".
 close_reduce		Ferme le mode "reduce".

 Bound_to_Edge		Construit le tableau des aretes d'une surface.
 Bound_to_Node		Construit le tableau des noeuds d'une surface.
 Bound_to_Vecteur	Construit le tableau des normales d'une surface.
 concat_Vertex		Concatene deux sommets relies par une arete.
 free_Node		Libere un tableau de noeuds.
 malloc_Node		Alloue et initialise un tableau de noeuds.
 get_min_Node		Retourne le noeud minimale d'un tableau de noeuds.
 add_Edge_to_Node	Ajoute une arete incidente a un noeud.
 add_Vertex_to_Node	Ajoute un sommet incident a un noeud.
 sub_Vertex_to_Node	Retire un sommet incident a un noeud.
 find_Incident		Recherche un sommet incident sur un noeud.
 mark_Edge_point	Marque les points des aretes significatives.
 reduce_Bound_Edge	Reduit une surface par elimination des aretes.
 reduce_Bound_Vertex	Reduit une surface par elimination des sommets.
 reduce_Bound_Point3f	Reduit une surface par elimination des points.
 reduce_Point3f		Reduit un tableau de points 3D.

 ENVIRONMENT	: Compilation	- NONE
      Link 		- NONE
      Execution	-
      "open_reduce".
      "close_reduce".

 AUTHOR		: Jean-Luc CORRE		CREATION DATE	: 25/09/89

 MODIFIED BY	:

 1.001 - 25/09/89 Original.
 1.002 - 24/10/89 Ajout de "reduce_Point3f".
 1.003 - 17/11/89 Ajout des procedures "..._Edge_...".
 1.004 - 25/01/94 nettoyage option et include (BA)

*************************************************************************/


#include <bound.h>

typedef	struct	{
  float	d;	/* distance entre les sommets	*/
  Index	f;	/* numero de la face incidente 	*/
  Index	v;	/* numero du sommet incident	*/
} Incident;

typedef	struct	{
  Index		nbr;	/* nombre de sommets incidents	*/
  Incident	*ptr;	/* pointeur sur le tableau	*/
} Incident_list;

typedef	struct	{
  Incident_list	incident;	/* liste des sommets incidents	*/
  Incident	min;		/* sommet incident minimum	*/
  float		sumd;		/* somme distances des sommets	*/
} Node;

static	void		Bound_to_Edge ();
static	void		Bound_to_Node ();
static	void		Bound_to_Vecteur ();
static	void		concat_Vertex ();
static	Node*		get_min_Node ();
static	void		free_Node ();
static	Node*		malloc_Node ();
static	int		add_Edge_to_Node ();
static	int		add_Vertex_to_Node ();
static	int		sub_Vertex_to_Node ();
static	Incident*	find_Incident ();
static	void		mark_Edge_point ();
static	int		reduce_Point3f ();


/*
 * Variables utilisees par la reduction :
 *
 * FACE_LIST	:
 * Liste de faces de travail pour la reduction.
 * Sa taille est definie par les macros "FACE_NBR" de "bound.h".
 *
 * REDUCE	:
 * Surface resultat apres la reduction.
 * La surface est adaptee pour la reception de tous les types de surfaces.
 * Sa taille est definie par les macros "..._NBR" de "bound.h".
 *
 * FACE_NBR	: son nombre de faces
 * POINT_NBR	: son nombre de points
 * VECTOR_NBR	: son monbre de vecteurs
 * VERTEX_NBR	: son nombre de sommets par face.
 *
 * La surface recoit un  a un  les points reduits.
 * La surface recoit une a une les faces reduites.
 *
 * RENAME	:
 * Tableau de renommage des points durant la reduction.
 * RENAME[I] est l'indice du point I apres reduction.
 *
 * VECTOR	:
 * Tableau de normales au faces de taille FACE_NBR.
 */
static	Face_list	face_list;	/* liste de faces	*/
static	Bound		reduce;		/* surface reduire	*/
static	int		*rename_local;	/* tableau de renommage	*/
static	Vecteur		*vector;	/* tableau de normales	*/


/*
 * La procedure "open_reduce" alloue et initialise les variables utilisees
 * par le mode "reduce".
 */
open_reduce ()
{
  static	char	proc_name[] = "open_reduce";

  /* alloue la liste de faces de travail	*/
  if ((face_list.ptr = (Face *) malloc (FACE_NBR * sizeof (Face))) == NULL
  ||  (face_list.ptr[0].vertex.ptr =
     (Index *) malloc (FACE_NBR * VERTEX_NBR * sizeof (Index))) == NULL) {
    perror (proc_name);
    exit (1);
  }

  /* alloue la surface de travail	*/
  malloc_huge_Bound (&reduce);

  /* alloue les tableaux	*/
  if ((rename_local = (int *) malloc (POINT_NBR * sizeof (int))) == NULL
  ||  (vector = (Vecteur *) malloc (FACE_NBR * sizeof (Vecteur))) == NULL) {
    perror (proc_name);
    exit (1);
  }
}

/*
 * La procedure "close_reduce" libere les variables utilisees par
 * le mode "reduce".
 */
void close_reduce ()
{
  free ((char *) face_list.ptr[0].vertex.ptr);
  free ((char *) face_list.ptr);
  free_huge_Bound (&reduce);
  free ((int *) rename_local);
  free ((int *) vector);
}

/*
 * La procedure "Bound_to_Edge" construit un tableau d'aretes a partir d'une
 * surface plolygonale plane. Les proprietes d'un noeud sont les suivantes :
 * - il existe un noeud par point sommet de la surface
 * - un noeud contient la liste des sommets des aretes incidentes au noeud
 * - un noeud contient la liste des faces des aretes incidentes au noeud
 * - le champ "d" du noeud n'est pas utilise.
 *
 * Entree :
 * bp		Surface polygonale de reference.
 * Entree/Sortie :
 * np		Tableau de noeuds a construire.
 */
static	void
Bound_to_Edge (bp, np)
Bound		*bp;
register Node	*np;
{
  register Face		*fp   = bp->face.ptr;
  register Face		*fend = fp + bp->face.nbr;
  register Index		fi = 0;	/* numero de la face	*/

  for (; fp < fend; fp++, fi++) {
    register Index	*vp   = fp->vertex.ptr;
    register Index	*vend = vp + fp->vertex.nbr;
    register Index	*vs   = vend - 1;

    for (; vp < vend; vp++) {
      if (*vs == *vp)	/* arete nulle	*/
        continue;
      add_Edge_to_Node (&np[*vs], *vp, fi);
      vs = vp;
    }
  }
}

/*
 * La procedure "Bound_to_Node" construit un tableau de noeuds a partir d'une
 * surface plolygonale plane. Les proprietes du noeud sont les suivantes :
 * - il existe un noeud par point sommet de la surface
 * - un noeud contient la liste des sommets incidents au noeud
 * - un noeud contient la distance des sommets incidents au sommet du noeud
 * - l'ensemble des noeuds possede une relation d'ordre sur la distance
 *   minimale du sommet du noeud a un sommet incident.
 * - le champ "f" du noeud n'est pas utilise.
 *
 * Entree :
 * bp		Surface polygonale de reference.
 * Entree/Sortie :
 * np		Tableau de noeuds a construire.
 */
static	void
Bound_to_Node (bp, np)
Bound		*bp;
register Node	*np;
{
  register Face		*fp   = bp->face.ptr;
  register Face		*fend = fp + bp->face.nbr;
  register Point3f	*pptr = bp->point.ptr;

  for (; fp < fend; fp++) {
    register Index	*vp   = fp->vertex.ptr;
    register Index	*vend = vp + fp->vertex.nbr;
    register Index	*vs   = vend - 1;

    Point3f		*ps   = pptr + *vs;
    Point3f		*pp;

    for (; vp < vend; vp++) {
      float	x, y, z, d;

      if (*vs == *vp)	/* arete nulle	*/
        continue;
      pp = pptr + *vp;
      x = pp->x - ps->x;
      y = pp->y - ps->y;
      z = pp->z - ps->z;
      d = (x * x) + (y * y) + (z * z);
      add_Vertex_to_Node (&np[*vs], *vp, d);
      add_Vertex_to_Node (&np[*vp], *vs, d);
      vs = vp;
      ps = pp;
    }
  }
}

/*
 * La procedure "Bound_to_Vecteur" construit un tableau de normales a partir
 * d'une surface plolygonale plane.
 * Algorithme de Martin Newell :
 * Soit le polygone :
 *	- de n sommets "i" : 1 <= i <= n.
 *	- appartenant au plan definie par : a * x + b * y + c * z + d = 0
 * Avec j = 1 si i = n, i + 1 sinon, on a :
 *	a = Z (yi - yj)(zi + zj)
 *	b = Z (zi - zj)(xi + xj)
 *	c = Z (xi - xj)(yi + yj)
 * Entree :
 * bp		Surface a initialiser.
 * Entree/Sortie :
 * vptr		Tableau de normales a initialiser.
 */
static	void
Bound_to_Vecteur (bp, vptr)
Bound	*bp;
Vecteur	*vptr;
{
  Face		*fp   = bp->face.ptr;
  Face		*fend = fp + bp->face.nbr;
  Point3f		*pp   = bp->point.ptr;

  for (; fp < fend; fp++, vptr++) {
    register Index		*vp   = fp->vertex.ptr;
    register Index		*vend = vp + fp->vertex.nbr;
    register Point3f 	*pi   = pp + *(vend - 1);
    register float		x = 0.0;
    register float		y = 0.0;
    register float		z = 0.0;
    register float		denom;

    for (; vp < vend; vp++) {
      register Point3f	*pj = pp + *vp;

      x += (pi->y - pj->y) * (pi->z + pj->z);
      y += (pi->z - pj->z) * (pi->x + pj->x);
      z += (pi->x - pj->x) * (pi->y + pj->y);
      pi = pj;
    }
    if (denom = (float) sqrt ((double) (x * x + y * y + z * z))) {
      SET_COORD3 (*vptr,x/denom,y/denom,z/denom);
    }
    else {
      SET_COORD3 (*vptr,x,y,z);
    }
  }
}

/*
 * La procedure "concat_Vertex" concatene deux sommets relies par une arete.
 * La suppression s'effectue par translation du second sommet vers le premier.
 * Entree :
 * nptr		Tableau des noeuds de la surface.
 * pptr		Tableau des points de la surface.
 * vb		Sommet a la base de l'arete.
 * vt		Sommet a supprimer par translation.
 */
static	void
concat_Vertex (nptr, pptr, vb, vt)
register Node		*nptr;
register Point3f	*pptr;
Index			vb, vt;
{
  register Node	*nb = nptr + vb;	/* noeud de base	*/
  register Node	*nt = nptr + vt;	/* noeud a translater	*/

  register Incident	*ip   = nt->incident.ptr;
  register Incident	*iend = ip + nt->incident.nbr;

  /* supprime l'arete entre les deux sommets	*/
  sub_Vertex_to_Node (nb, vt);

  /* pour toutes les aretes incidentes a l'arete (vb,vt)	*/
  for (; ip < iend; ip++) {
    float	x, y, z, d;

    /* supprime le sommet translate des sommets incidents	*/
    sub_Vertex_to_Node (nptr + ip->v, vt);

    if (ip->v == vb)	/* arete non valide	*/
      continue;

    /* calcule la nouvelle arete generee par la translation	*/

    x = pptr[ip->v].x - pptr[vb].x;
    y = pptr[ip->v].y - pptr[vb].y;
    z = pptr[ip->v].z - pptr[vb].z;
    d = (x * x) + (y * y) + (z * z);
    /* ajoute l'arete au noeud de base	*/
    add_Vertex_to_Node (nb, ip->v, d);
    /* ajoute l'arete au noeud connexe	*/
    add_Vertex_to_Node (&nptr[ip->v], vb, d);
  }
  free ((char *) nt->incident.ptr);
  nt->incident.nbr = 0;
  nt->incident.ptr = NULL;
}

/*
 * La procedure "free_Node" libere un tableau de noeuds.
 * Entree :
 * nptr		Tableau de noeuds a liberer.
 * size		Taille du tableau de noeuds a liberer.
 */
static	void
free_Node (nptr, size)
Node	*nptr;
int	size;
{
  register Node	*np   = nptr;
  register Node	*nend = np + size;

  for (; np < nend; np++) {
    if (np->incident.nbr > 0) {
      free ((char *) np->incident.ptr);
      np->incident.nbr = 0;
      np->incident.ptr = NULL;
    }
  }
  free ((char *) nptr);
}

/*
 * La procedure "get_min_Node" retourne le noeud minimale d'un tableau.
 * Un noeud est minimale s'il possede la plus petite distance entre
 * le sommet du noeud et un sommet incident. En cas d'egalite avec un autre
 * noeud, le noeud minimale est celui qui possede la somme des distances
 * des sommets incidents la plus petite.
 * Entree :
 * np		Tableau de noeuds.
 * size		Taille  du tableau de noeuds.
 * Sortie :
 *		Pointeur du noeud minimale.
 *		NULL si le tableau ne possede pas de noeud minimale.
 */
static	Node	*
get_min_Node (np, size)
register Node	*np;
int		size;
{
  register Node	*min  = NULL;
  register Node	*nend = np + size;

  for (; np < nend; np++) {
    if (np->incident.nbr > 0) {
      min = np;
      break;
    }
  }
  for (np++; np < nend; np++) {
    if (np->incident.nbr == 0 || np->min.d > min->min.d)
      continue;
    if (np->min.d < min->min.d || np->sumd < min->sumd)
      min = np;
  }
  return (min);
}

/*
 * La procedure "malloc_Node" alloue et initialise un tableau de noeuds.
 * Entree :
 * size		Nombre du tableau de noeuds a allouer.
 * Sortie :
 *		Pointeur sur le premier element du tableau.
 *		NULL en cas d'erreur.
 */
static	Node*
malloc_Node (size)
int	size;
{
  static	char	proc_name[] = "malloc_Node";

  register Node	*nptr, *np, *nend;

  if ((nptr = (Node *) malloc (size * sizeof (Node))) == NULL) {
    perror (proc_name);
    return (NULL);
  }
  np   = nptr;
  nend = np + size;
  for (; np < nend; np++) {
    np->incident.nbr = 0;
    np->incident.ptr = NULL;
  }
  return (nptr);
}

/*
 * La procedure "add_Edge_to_Node" ajoute une arete incidente a un noeud.
 * Les champs "min" et "d" du noeud ne sont pas utilises.
 * Entree :
 * np		Noeud auquel on ajoute l'arete incidente.
 * v		Sommet de l'arete incidente a ajouter.
 * f		Face qui contient l'arete incidente a jouter.
 * Sortie :
 *		1 si l'arete incidente est effectivement ajoute.
 *		0 sinon.
 */
static	int
add_Edge_to_Node (np, v, f)
register Node	*np;
register Index	v;
Index		f;
{
  static	char	proc_name[] = "add_Edge_to_Node";

  register Incident	*ip   = np->incident.ptr;
  register Incident	*iend = ip + np->incident.nbr;

  for (; ip < iend; ip++) {
    if (ip->v == v)		/* sommet existant	*/
      return (0);
  }

  /*
   * Alloue ou realloue la liste des sommets incidents.
   */
  if (np->incident.nbr == 0) {
    if ((np->incident.ptr = (Incident *) malloc (sizeof (Incident)))
       == NULL) {
      perror (proc_name);
      exit (1);
    }
  }
  else {
    if ((np->incident.ptr = (Incident *) realloc (np->incident.ptr,
        (np->incident.nbr + 1) * sizeof (Incident))) == NULL) {
      perror (proc_name);
      exit (1);
    }
  }
  /*
   * Ajoute le sommet incident et met a jour les articles du noeud.
   */
  ip    = np->incident.ptr + np->incident.nbr++;
  ip->v = v;
  ip->f = f;
  return (1);
}

/*
 * La procedure "add_Vertex_to_Node" ajoute un sommet incident a un noeud.
 * Le champ "f" du noeud n'est pas utilise.
 * Entree :
 * np		Noeud auquel on ajoute le sommet incident.
 * v		Sommet incident a ajouter.
 * d		Distance de la connection (sommet incident, sommet au noeud).
 * Sortie :
 *		1 si le sommet incident est effectivement ajoute.
 *		0 sinon.
 */
static	int
add_Vertex_to_Node (np, v, d)
register Node	*np;
register Index	v;
float		d;
{
  static	char	proc_name[] = "add_Vertex_to_Node";

  register Incident	*ip   = np->incident.ptr;
  register Incident	*iend = ip + np->incident.nbr;

  for (; ip < iend; ip++) {
    if (ip->v == v)		/* sommet existant	*/
      return (0);
  }

  /*
   * Alloue ou realloue la liste des sommets incidents.
   */
  if (np->incident.nbr == 0) {
    if ((np->incident.ptr = (Incident *) malloc (sizeof (Incident)))
       == NULL) {
      perror (proc_name);
      exit (1);
    }
    np->min.v = v;	/* initialisation du noeud	*/
    np->min.d = d;
    np->sumd  = 0.0;
  }
  else {
    if ((np->incident.ptr = (Incident *) realloc (np->incident.ptr,
        (np->incident.nbr + 1) * sizeof (Incident))) == NULL) {
      perror (proc_name);
      exit (1);
    }
  }
  /*
   * Ajoute le sommet incident et met a jour les articles du noeud.
   */
  ip    = np->incident.ptr + np->incident.nbr++;
  ip->v = v;
  ip->d = d;
  if (d < np->min.d)	/* mise a jour		*/
    np->min = *ip;
  np->sumd += d;
  return (1);
}

/*
 * La procedure "sub_Vertex_to_Node" retire un sommet incident a un noeud.
 * La procedure verifie que le sommet incident est different du sommet au noeud
 * et que le sommet a retirer existe bien.
 * Entree :
 * np		Noeud auquel on retire le sommet incident.
 * v		Sommet incident a retirer.
 * Sortie :
 *		1 si le sommet incident est effectivement retire.
 *		0 sinon.
 */
static	int
sub_Vertex_to_Node (np, v)
register Node	*np;
register Index	v;
{
  register Incident	*ip   = np->incident.ptr;
  register Incident	*iend = ip + np->incident.nbr;

  for (; ip < iend; ip++) {	/* recherche le sommet incident	*/
    if (ip->v == v)		/* le sommet incident existe	*/
      break;
  }
  if (ip >= iend)			/* sommet incident inexistante	*/
    return (0);

  if (--np->incident.nbr <= 0) {	/* liste vide a liberer		*/
    free ((char *) np->incident.ptr);
    np->incident.ptr = NULL;
    return (1);
  }

  for (ip++; ip < iend; ip++)	/* ecrase le sommet incident	*/
    *(ip-1) = *ip;

  /* pas de reallocation de la liste a une taille inferieure	*/

  ip = np->incident.ptr;
  iend--;				/* un sommet en moins	*/
  np->min  = *ip;			/* met a jour le noeud	*/
  np->sumd = ip->d;
  for (ip++; ip < iend; ip++) {
    if (ip->d < np->min.d)
      np->min = *ip;
    np->sumd += ip->d;
  }
  return (1);
}

/*
 * La procedure "find_Incident" recherche un sommet incident dans la liste
 * des sommets incidents d'un noeud.
 * Entree :
 * np		Noeud ou s'effectue la recherche.
 * v		Numero du sommet incident a rechercher.
 * Sortie :
 *		Pointeur du sommet incident s'il existe,
 *		NULL sinon.
 */
static	Incident*
find_Incident (np, v)
Node		*np;
register Index	v;
{
  register Incident	*ip   = np->incident.ptr;
  register Incident	*iend = ip + np->incident.nbr;

  for (; ip < iend; ip++) {
    if (ip->v == v)
      return (ip);
  }
  return (NULL);
}

/*
 * La procedure "mark_Edge_point" marque les points des aretes siginificatives.
 * Une arete est significative si :
 * - elle appartient a la silouhette de la surface,
 *   c'est-a-dire si elle appartient a une seule face.
 * - elle appartient a deux faces dont l'angle entre les normales
 *   est superieur a un angle seuil.
 * Un compteur de meme indice est associe a chaque point.
 * Un compteur strictement positif indique que le point correspondant (de meme
 * indice) appartient a une arete significative.
 * Entree :
 * nptr		Tableau de noeuds de la surface.
 * size		Taille du tableau de noeuds.
 * vptr		Tableau des normales aux faces de la surface.
 * cptr		Tableau des compteurs.
 * angle	Angle d'ouverture minimale en degres entre les normales
 *		des faces pour rendre une arete significative
 */
static	void
mark_Edge_point (nptr, size, vptr, cptr, angle)
Node	*nptr;
int	size;
Vecteur	*vptr;
int	*cptr;
float	angle;
{
  register int	i;
  float		cosa = (float) cos ((double) angle * M_PI / 180.0);

  for (i = 0; i < size; cptr[i++] = 0);

  for (i = 0; i < size; i++) {	/* parcourt les noeuds	*/
    register Node		*np   = &nptr[i];
    register Incident	*ip   = np->incident.ptr;
    register Incident	*iend = ip + np->incident.nbr;

    for (; ip < iend; ip++) {
      Incident	*iptr;

      if (ip->v > i)
        continue;	/* arete deja traitee	*/
      /*
       * Recherche si l'arete est partage par une autre face
       * ou si l'angle forme par les deux faces partageant
       * l'arete est superieur a un seuil.
       */
      if ((iptr =find_Incident(&nptr[ip->v],(Index)i)) == NULL
      || DOT_PRODUCT(vptr[ip->f],vptr[iptr->f]) > cosa) {
        /* marque les points sommets de l'arete	*/
        cptr[i]++;
        cptr[ip->v]++;
      }
    }
  }
}

/*
 * La procedure "reduce_Bound_Edge" reduit une surface polygonale par
 * elimination des aretes dont la taille est inferieure a une distance seuil.
 * Les faces devenues non valides par l'elimination des aretes sont elles meme
 * eliminees.
 * Entree :
 * bp		Surface polygonale a reduire.
 * d		Distance maximale de concatenation des points.
 * angle	Angle minimal en degres entre les normales de deux faces
 *		pour rendre l'arete commune sigificative.
 * Sortie
 *		Pointeur sur la surface reduite resultat.
 *		NULL si la surface reduite est vide.
 */
Bound*
reduce_Bound_Edge (bp, d, angle)
Bound	*bp;
float	d, angle;
{
  static	char	proc_name[] = "reduce_Bound_Edge";

  register Node	*nptr;
  register int	point_in  = (int) bp->point.nbr;

  if ((nptr = malloc_Node (point_in)) == NULL) {
    perror (proc_name);
    exit (1);
  }

  Bound_to_Edge (bp, nptr);	/* construit les aretes		*/
  Bound_to_Vecteur (bp, vector);	/* construit les normales	*/
  mark_Edge_point (nptr, point_in, vector, rename_local, angle);
  free_Node (nptr, point_in);

  /* reduit les points de la surface	*/
  if ((reduce.point.nbr = (Index) reduce_Point3f (bp->point.ptr,
      (int) bp->point.nbr, d, TRUE, rename_local, reduce.point.ptr)) < 3)
    return (NULL);

  /* renomme les sommets des faces	*/
  face_list.nbr = (Index) copy_huge_Face (bp->face.ptr,
    face_list.ptr, (int) bp->face.nbr);
  rename_Face_vertex (face_list.ptr, (int) face_list.nbr, rename_local);

  /* supprime les faces non valides	*/
  if ((reduce.face.nbr = (Index) compress_huge_Face (face_list.ptr,
      (int) face_list.nbr, reduce.face.ptr)) == 0)
    return (NULL);
  return (&reduce);
}

/*
 * La procedure "reduce_Bound_Point3f" reduit une surface en concatenant
 * les points dont la distance est inferieure a une distance seuil.
 * Entree :
 * bp		Surface a reduire.
 * d		Distance maximale de concatenation des points.
 * Sortie
 *		Pointeur sur la surface reduite resultat.
 *		NULL si la surface reduite est vide.
 */
Bound	*
reduce_Bound_Point3f (bp, d)
Bound	*bp;
float	d;
{
  /* reduit les points de la surface	*/
  if ((reduce.point.nbr = (Index) reduce_Point3f (bp->point.ptr,
      (int) bp->point.nbr, d, FALSE, rename_local, reduce.point.ptr)) < 3)
    return (NULL);

  /* renomme les sommets des faces	*/
  face_list.nbr = (Index) copy_huge_Face (bp->face.ptr,
    face_list.ptr, (int) bp->face.nbr);
  rename_Face_vertex (face_list.ptr, (int) face_list.nbr, rename_local);

  /* supprime les faces non valides	*/
  if ((reduce.face.nbr = (Index) compress_huge_Face (face_list.ptr,
      (int) face_list.nbr, reduce.face.ptr)) == 0)
    return (NULL);
  return (&reduce);
}

/*
 * La procedure "reduce_Bound_Vertex" reduit une surface polygonale par
 * elimination des sommets. Les faces devenues non valides par l'elimination des
 * sommets sont elles meme eliminees.
 * Entree :
 * bp		Surface polygonale a reduire.
 * precent	Pourcentage de reduction du nombre de points de la surface.
 * Sortie
 *		Pointeur sur la surface reduite resultat.
 *		NULL si la surface reduite est vide.
 */
Bound*
reduce_Bound_Vertex (bp, percent)
Bound	*bp;
float	percent;
{
  static	char	proc_name[] = "reduce_Bound_Vertex";

  register Node	*nptr;
  register int	point_in  = (int) bp->point.nbr;
  register int	point_out;
  register int	i;

  if ((nptr = malloc_Node (point_in)) == NULL) {
    perror (proc_name);
    exit (1);
  }

  /* initialisation des noms par les indices des points	*/

  for (i = 0; i < point_in ; i++)
    rename_local[i] = i;
  Bound_to_Node (bp, nptr);	/* construit les noeuds	*/

  point_out = (int) (((float) point_in * (100.0-percent)) / 100.0);
  for (i = point_in; i > point_out; i--) {
    Node	*np;

    if ((np = get_min_Node (nptr, point_in)) == NULL)
      break;
    rename_local[np->min.v] = np - nptr;	/* renommage	*/
    concat_Vertex (nptr, bp->point.ptr,(Index)(np-nptr),np->min.v);
  }
  free_Node (nptr, point_in);

  /* recherche de nom de point stable : i == rename_local[i]	*/

  for (i = 0; i < point_in; i++) {
    register int	index = i;
    register int	name  = rename_local[index];

    for (; index != name; name = rename_local[index = name]);
    rename_local[i] = name;
  }

  /* renomme les sommets des faces	*/
  face_list.nbr = (Index) copy_huge_Face (bp->face.ptr,
    face_list.ptr, (int) bp->face.nbr);
  rename_Face_vertex (face_list.ptr, (int) face_list.nbr, rename_local);

  /* supprime les faces non valides	*/
  if ((reduce.face.nbr = (Index) compress_huge_Face (face_list.ptr,
      (int) face_list.nbr, reduce.face.ptr)) == 0)
    return (NULL);

  /* concatene les points valides		*/
  mark_Face_point (reduce.face.ptr,(int)reduce.face.nbr,rename_local,point_in);
  if ((reduce.point.nbr = (Index)compress_Point3f(bp->point.ptr, point_in,
    rename_local, reduce.point.ptr)) == 0)
    return (NULL);
  rename_Face_vertex (reduce.face.ptr, (int) reduce.face.nbr, rename_local);
  return (&reduce);
}

/*
 * La procedure "reduce_Point3f" reduit un tableau de points 3D en concatenant
 * les points dont la distance est inferieure a un seuil.
 * Apres concatenation, le tableau des marques contient les nouveaux indices
 * des points dans le tableau en sortie.
 * Entree :
 * from		Tableau de points 3D a concatener.
 * size		Taille du tableau de points 3D.
 * d		Distance maximale de concatenation des points.
 * idem		Booleen indiquant s'il existe des points a recopier tels quels.
 * Entree/Sortie :
 * ip		Tableau des nouveaux indices des points.
 * to		Tableau de points 3D apres concatenation
 * Sortie :
 *		Taille du tableau de points 3D apres concatenation.
 */
static	int
reduce_Point3f (from, size, d, idem, ip, to)
register Point3f	*from;
int			size;
register float		d;
int			idem;
register int		*ip;
register Point3f	*to;
{
  register Point3f	*fend   = from + size;
  register Point3f	*tobase = to;	/* base du tableau	*/

  d *= d;	/* supprime l'emploi de la racine carre	*/

  if (size <= 0)
    return (0);		/* tableau resultat vide	*/

  /* initialise le point germe	*/

  *ip++ = to - tobase;	/* reindicage du point	*/
  *to++ = *from++;	/* recopie du point	*/

  for (; from < fend; from++, ip++) {
    register Point3f	*tp;

    if (idem && *ip) {
      *ip   = to - tobase;	/* reindicage du point	*/
      *to++ = *from;		/* recopie du point	*/
      continue;
    }

    /* recherche un point semblable dans [tobase,to[	*/
    for (tp = tobase; tp < to; tp++) {
      float	x = from->x - tp->x;
      float	y = from->y - tp->y;
      float	z = from->z - tp->z;

      if ((x * x) + (y * y) + (z * z) < d)
        break;	/* points suffisamment proches	*/
    }

    if (tp < to)	/* point trouve		*/
      *ip = tp - tobase; 	/* concatenation	*/
    else {		/* point non trouve	*/
      *ip   = to - tobase;	/* reindicage du point	*/
      *to++ = *from;		/* recopie du point	*/
    }
  }
  return (to - tobase);		/* nombre de points	*/
}

