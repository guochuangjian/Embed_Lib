#ifndef SF_TMR_H_
#define SF_TMR_H_

#ifdef __cplusplus
extern "C" {
#endif
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

void sf_tmr_lib_init();
void sf_tmr_tick_handle();
void sf_timer_init(sf_timer_t        *p_timer,
				   timeout_callback_t timeout_cb,
				   void              *p_arg);
int sf_timer_start(sf_timer_t *p_timer, uint32_t tick);
int sf_timer_stop(sf_timer_t *p_timer);

#ifdef __cplusplus
}
#endif

#endif /* SF_TMR_H_ */
