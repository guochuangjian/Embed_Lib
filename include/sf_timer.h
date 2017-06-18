/*
 *  \brief 软件定时器实现
 *
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
#ifndef __SF_TIMER_H_
#define __SF_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "emdef.h"
#include "list.h"
/*****************************************************************************/
typedef void (*timeout_callback_t) (void *p_arg);
struct sf_timer;
typedef struct sf_timer {
	uint32_t           tick;
	timeout_callback_t timeout_cb;
	void              *p_arg;
	struct list_head   node;
} sf_timer_t;

void sf_timer_lib_init();
void sf_timer_tick_handle();
void sf_timer_init(sf_timer_t        *p_timer,
				   timeout_callback_t timeout_cb,
				   void              *p_arg);
int sf_timer_start(sf_timer_t *p_timer, uint32_t tick);
int sf_timer_stop(sf_timer_t *p_timer);

#ifdef __cplusplus
}
#endif

#endif /* __SF_TIMER_H_ */
