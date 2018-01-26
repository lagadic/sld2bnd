#include "my.h"
#include "arit.h"
#include "bound.h"

scale(bp, l1,l2,l3)
Bound *bp;
float l1,l2,l3;
{
	Point3f_list   		*lp = &bp->point;
	register Point3f	*pp;	/* point courant	*/
	register Point3f	*pend;	/* borne de "pp"	*/

	pp   = lp->ptr;		
	pend = pp + lp->nbr;
	for (; pp < pend; pp++) pp->x *= l1, pp->y*= l2, pp->z*= l3;
}

move_bound(bp, m)
Bound *bp;
Matrice	m;
{
        register Point3f        *pp   = bp->point.ptr;
	register Point3f        *pend = pp + bp->point.nbr;
	register float          x, y, z, w;

	for (; pp < pend; pp++) 
	{
	        x = pp->x;
	        y = pp->y;
	        z = pp->z;

	        w = COORD3_COL(x,y,z,m,3);
	        if (w >= 0.0) 
	        {
			if (w <   M_EPSILON) w =   M_EPSILON;
	        }
	        else 
	        {
			if (w > - M_EPSILON) w = - M_EPSILON;
	        }
	        pp->x = COORD3_COL(x,y,z,m,0) / w;
	        pp->y = COORD3_COL(x,y,z,m,1) / w;
	        pp->z = COORD3_COL(x,y,z,m,2) / w;
	}
}
