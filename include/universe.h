/*________________________________________________________________________

 	Fichier		: universe.h

Fichier de macros et de types d'un univers 3D.
  
 	Contenu		:

Macros de primitives solides.
Macros de primitives facettes.
Types  de primitives solides.
Types  de primitives facettes.
 
	Auteur		: Jean-Luc CORRE
	Cree le		: 27/03/87
	Modifie le	: 30/03/87
 
	Modification	:

Ajout de "Bouding_box".
 
	Renseignement	: Jean-Luc CORRE,	IRISA
						INRIA
						Campus de Beaulieu
						35042 RENNES Cedex
 
________________________________________________________________________*/
 

/*
 * Macros de primitives solides.
 */
#define	SOLID_SPHERE	0
#define	SOLID_PARALL	1
#define SOLID_CONE	2
#define	SOLID_CYLIND	3
#define SOLID_NBR	4

/*
 * Macros de l'univers.
 */	
#define	UNIVERSE	0
#define	WORLD		1
#define	CLUSTER		2
#define	OBJECT		3

/*
 * Types de transformation.
 */
typedef	struct	{
	float		xmin, xmax;	/* boite englobante	*/
	float		ymin, ymax;
	float		zmin, zmax;
} Bounding_box;

typedef	struct	{
	short		rx, ry, rz;	/* rotation en degres	*/
} Rotate;

typedef	struct	{
	float		sx, sy, sz;	/* homotetie sur X Y Z	*/
} Scale;

typedef	struct	{
	float		tx, ty, tz;	/* translation sur X Y Z*/
} Translate;

typedef	struct	{
	Bounding_box	box;		/* boite englobante	*/
	Matrice		lsm;		/* passage Local->Scene	*/
	Rotate		rotate;		/* rotation		*/
	Scale		scale;		/* homotetie		*/
	Translate	translate;	/* translation		*/
} Transform;

/*
 * Types de primitives solides.
 */
typedef	struct	{
	float		tx,ty,tz;	/* distances sur X Y Z	*/
} Solid_cube;

typedef	struct	{
	float		radius;		/* rayon		*/
} Solid_sphere;

typedef	union	{
	Solid_cube	cube;
	Solid_sphere	sphere;
} Solid_primitive;

typedef	struct	{
	Type		type;		/* type de la primitive	*/
	Solid_primitive	geometry;	/* geometrie		*/
} Solid_geometry;

/*
 * Types de primitives decrites par facettes polygonales.
 */
typedef	struct	{
	Index		v1, v2;		/* extremites		*/
	Index		f1, f2;		/* facettes		*/
} Edge;

typedef	struct	{
	Index		nbr;		/* nombre d'aretes	*/
	Edge		*ptr;		/* liste  dynamique	*/
} Edge_list;
 
typedef	struct	{
	Index		nbr;		/* nombre de sommets	*/
	Index		*ptr;		/* liste  dynamique	*/
} Polygon_list;

typedef	struct	{
	Index		nbr;		/* nombre de points	*/
	Point3f		*ptr;		/* liste  dynamique	*/
} Point_list;

typedef	struct	{
	Polygon_list	edge;		/* liste d'aretes	*/
	Polygon_list	vertex;		/* liste de sommets	*/
} Facet;

typedef	struct	{
	Index		nbr;		/* nombre de facettes	*/
	Facet		*ptr;		/* liste  dynamique	*/
} Facet_list;

typedef	struct	{
	Facet_list	facet;		/* liste de facettes	*/
	Edge_list	edge;		/* liste d'aretes	*/
	Point_list	point;		/* liste de points	*/
} Poly_geometry;

/*
 * Types de l'arbre.
 */
typedef	union	{
	Poly_geometry	poly;
	Solid_geometry	solid;
} Geometry;

typedef	struct	{
	unsigned	is_usable : 1;	/* utilisable		*/
	unsigned	is_1 : 1;	/* utilisation future	*/
	unsigned	is_2 : 1;
	unsigned	is_3 : 1;
	unsigned	is_4 : 1;
	unsigned	is_5 : 1;
	unsigned	is_6 : 1;
	unsigned	is_7 : 1;
} Node_flags;

typedef	struct	{
	char		*name;		/* nom			*/
	Node_flags	flags;		/* drapeaux d'etats	*/
	Transform	transform;	/* positionnement	*/
	Type		type;		/* type du noeud	*/	
} Node_data;

typedef	struct	tree_node {
	Node_data	 data;		/* information du noeud	*/
	struct tree_node *daddy;	/* noeud pere		*/
	struct tree_node **child;	/* liste de noeuds fils	*/
	Index		 childnbr;	/* nombre de noeuds fils*/
} Node;

typedef	struct	{
	Node		*root;		/* racine de l'arbre	*/
	Node		*node;		/* noeud courant	*/
} Tree;

