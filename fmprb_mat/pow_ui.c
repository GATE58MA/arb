/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "fmprb_mat.h"

void
fmprb_mat_pow_ui(fmprb_mat_t B, const fmprb_mat_t A, ulong exp, long prec)
{
    long d = fmprb_mat_nrows(A);

    if (exp <= 2 || d <= 1)
    {
        if (exp == 0 || d == 0)
        {
            fmprb_mat_one(B);
        }
        else if (d == 1)
        {
            fmprb_pow_ui(fmprb_mat_entry(B, 0, 0),
                 fmprb_mat_entry(A, 0, 0), exp, prec);
        }
        else if (exp == 1)
        {
            fmprb_mat_set(B, A);
        }
        else if (exp == 2)
        {
            fmprb_mat_mul(B, A, A, prec);   /* todo: sqr */
        }
    }
    else
    {
        fmprb_mat_t T, U;
        long i;

        fmprb_mat_init(T, d, d);
        fmprb_mat_set(T, A);
        fmprb_mat_init(U, d, d);

        for (i = ((long) FLINT_BIT_COUNT(exp)) - 2; i >= 0; i--)
        {
            fmprb_mat_mul(U, T, T, prec);   /* todo: sqr */

            if (exp & (1L << i))
                fmprb_mat_mul(T, U, A, prec);
            else
                fmprb_mat_swap(T, U);
        }

        fmprb_mat_swap(B, T);
        fmprb_mat_clear(T);
        fmprb_mat_clear(U);
    }
}

