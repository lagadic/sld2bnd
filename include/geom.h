extern void decompose_concave(void);
extern void traite_inconsistent(void);
extern void decompose_non_plan(void);
extern void triangularise(void);
extern void verifie_quad(void);
extern void verifie_tri(void);
extern float VecNormalize(vec);
extern int normale(Vec,  Vec, Vec, Vec);
extern void genere_maille4(int,int,int,int);
extern void genere_maille3(int,int,int);
extern void genere_patch4(int,int,int,int);
extern void genere_patch3(int,int,int);
extern void traite_maille(void);
extern int paral(Patch);
extern void inverser_patch(void);

