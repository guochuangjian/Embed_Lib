/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-17     zoe      first version.
 */
#ifndef __EMDEF_H_
#define __EMDEF_H_

#include "stdio.h"

/*
 * Return the max value
 */
#ifndef min
#define min(a, b)  (((a) > (b)) ? (b) : (a))
#endif

/*
 * Return the min value
 */
#ifndef max
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

/*
 * Return the most contiguous size aligned at specified width. EM_ALIGN_UP(13, 4)
 * would return 16.
 */
#define EM_ALIGN_UP(size, align)    ((size) + ((align) - 1) & ~((align) - 1))

/*
 * Return the down number of aligned at specified width. EM_ALIGN_DOWN(13, 4)
 * would return 12.
 */
#define EM_ALIGN_DOWN(size, align)  ((size) & ~((align) - 1))

#endif  /* __EMDEF_H_ */
