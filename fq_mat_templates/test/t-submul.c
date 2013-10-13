/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 Mike Hansen

******************************************************************************/


#ifdef T

#include "templates.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
main(void)
{
    slong i;
    flint_rand_t state;
    flint_randinit(state);

    printf("submul....");
    fflush(stdout);

    for (i = 0; i < 20; i++)
    {
        TEMPLATE(T, ctx_t) ctx;
        TEMPLATE(T, mat_t) A, B, C, D, T, E;

        slong m, k, n;

        TEMPLATE(T, ctx_randtest)(ctx, state);

        m = n_randint(state, 100);
        k = n_randint(state, 100);
        n = n_randint(state, 100);

        TEMPLATE(T, mat_init)(A, m, k, ctx);
        TEMPLATE(T, mat_init)(B, k, n, ctx);
        TEMPLATE(T, mat_init)(C, m, n, ctx);
        TEMPLATE(T, mat_init)(D, m, n, ctx);
        TEMPLATE(T, mat_init)(T, m, n, ctx);
        TEMPLATE(T, mat_init)(E, m, n, ctx);

        TEMPLATE(T, mat_randtest)(A, state, ctx);
        TEMPLATE(T, mat_randtest)(B, state, ctx);
        TEMPLATE(T, mat_randtest)(C, state, ctx);

        TEMPLATE(T, mat_submul)(D, C, A, B, ctx);

        TEMPLATE(T, mat_mul)(T, A, B, ctx);
        TEMPLATE(T, mat_sub)(E, C, T, ctx);

        if (!TEMPLATE(T, mat_equal)(D, E))
        {
            printf("FAIL: results not equal\n");
            TEMPLATE(T, mat_print_pretty)(A, ctx);
            TEMPLATE(T, mat_print_pretty)(B, ctx);
            TEMPLATE(T, mat_print_pretty)(C, ctx);
            TEMPLATE(T, mat_print_pretty)(D, ctx);
            TEMPLATE(T, mat_print_pretty)(E, ctx);
            abort();
        }

        /* Check aliasing */
        TEMPLATE(T, mat_submul)(C, C, A, B, ctx);

        if (!TEMPLATE(T, mat_equal)(C, E))
        {
            printf("FAIL: results not equal (aliasing)\n");
            TEMPLATE(T, mat_print_pretty)(A, ctx);
            TEMPLATE(T, mat_print_pretty)(B, ctx);
            TEMPLATE(T, mat_print_pretty)(C, ctx);
            TEMPLATE(T, mat_print_pretty)(D, ctx);
            TEMPLATE(T, mat_print_pretty)(E, ctx);
            abort();
        }

        TEMPLATE(T, mat_clear)(A);
        TEMPLATE(T, mat_clear)(B);
        TEMPLATE(T, mat_clear)(C);
        TEMPLATE(T, mat_clear)(D);
        TEMPLATE(T, mat_clear)(E);
        TEMPLATE(T, mat_clear)(T);

        TEMPLATE(T, ctx_clear)(ctx);
    }

    flint_randclear(state);

    printf("PASS\n");
    return 0;
}


#endif