#include "factorizations.h"

SEXP LU_validate(SEXP obj)
{
    return ScalarLogical(1);
}

SEXP BunchKaufman_validate(SEXP obj)
{
    return ScalarLogical(1);
}

SEXP pBunchKaufman_validate(SEXP obj)
{
    return ScalarLogical(1);
}

SEXP Cholesky_validate(SEXP obj)
{
    return ScalarLogical(1);
}

SEXP pCholesky_validate(SEXP obj)
{
    return ScalarLogical(1);
}

SEXP SVD_validate(SEXP obj)
{
    return ScalarLogical(1);
}

SEXP LU_expand(SEXP x)
{
    char *nms[] = {"L", "U", "P", ""};
    SEXP L, U, P, val = PROTECT(Matrix_make_named(VECSXP, nms)),
	lux = GET_SLOT(x, Matrix_xSym),
	dd = GET_SLOT(x, Matrix_DimSym);
    int *perm, *pivot = INTEGER(GET_SLOT(x, Matrix_permSym)),
	i, n = INTEGER(dd)[0];

    SET_VECTOR_ELT(val, 0, NEW_OBJECT(MAKE_CLASS("dtrMatrix")));
    L = VECTOR_ELT(val, 0);
    SET_VECTOR_ELT(val, 1, NEW_OBJECT(MAKE_CLASS("dtrMatrix")));
    U = VECTOR_ELT(val, 1);
    SET_VECTOR_ELT(val, 2, NEW_OBJECT(MAKE_CLASS("pMatrix")));
    P = VECTOR_ELT(val, 2);
    SET_SLOT(L, Matrix_xSym, duplicate(lux));
    SET_SLOT(L, Matrix_DimSym, duplicate(dd));
    SET_SLOT(L, Matrix_uploSym, mkString("L"));
    SET_SLOT(L, Matrix_diagSym, mkString("U"));
    make_array_triangular(REAL(GET_SLOT(L, Matrix_xSym)), L);
    SET_SLOT(U, Matrix_xSym, duplicate(lux));
    SET_SLOT(U, Matrix_DimSym, duplicate(dd));
    SET_SLOT(U, Matrix_uploSym, mkString("U"));
    SET_SLOT(U, Matrix_diagSym, mkString("N"));
    make_array_triangular(REAL(GET_SLOT(U, Matrix_xSym)), U);
    SET_SLOT(P, Matrix_DimSym, duplicate(dd));
    perm = INTEGER(ALLOC_SLOT(P, Matrix_permSym, INTSXP, n));
    for (i = 0; i < n; i++) perm[i] = i + 1;
    for (i = 0; i < n; i++) {
	int newpos = pivot[i] - 1;
	if (newpos != i) {
	    int tmp = perm[i];

	    perm[i] = newpos + 1;
	    perm[newpos] = tmp;
	}
    }
    UNPROTECT(1);
    return val;
}
