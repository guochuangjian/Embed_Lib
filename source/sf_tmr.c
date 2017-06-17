#include "stdio.h"
#include "sf_tmr.h"
//#define SF_TMR_DEBUG
/*****************************************************************************
 * 临界保护
 *****************************************************************************/
void spinlock_lock()
{
	//上锁
}

void spinlock_unlock()
{
	//解锁
}
/*****************************************************************************/
static struct list_head __g_tmr_list;

void sf_tmr_lib_init()
{
	INIT_LIST_HEAD(&__g_tmr_list);
}

void sf_tmr_tick_handle()
{
	spinlock_lock();

	if (!list_empty(&__g_tmr_list)) {
		sf_timer_t *p_cur_tmr  = list_entry(__g_tmr_list.next, sf_timer_t, node);
		sf_timer_t *p_tmp_tmr  = NULL;

		if (p_cur_tmr->tick) {
			p_cur_tmr->tick--;
		}

		list_for_each_entry_safe(p_cur_tmr, p_tmp_tmr, &__g_tmr_list, node) {
			if (p_cur_tmr->tick) {
				break;
			}

			list_del(&p_cur_tmr->node);
			spinlock_unlock();
			p_cur_tmr->timeout_cb(p_cur_tmr->p_arg);
			spinlock_lock();
		}
	}

	spinlock_unlock();
}

void sf_timer_init(sf_timer_t        *p_timer,
				   timeout_callback_t timeout_cb,
				   void              *p_arg)
{
	p_timer->timeout_cb = timeout_cb;
	p_timer->p_arg      = p_arg;
	INIT_LIST_HEAD(&p_timer->node);
}

static void __timer_add (sf_timer_t *p_new_tmr, uint32_t tick)
{
	sf_timer_t *p_cur_tmr = NULL;

	list_for_each_entry(p_cur_tmr, &__g_tmr_list, node) {
		if (tick > p_cur_tmr->tick) {
			tick -= p_cur_tmr->tick;
		} else {
			break;
		}
	}

	p_new_tmr->tick = tick;
	list_add_tail(&p_new_tmr->node, &p_cur_tmr->node);

	if (&p_cur_tmr->node != &__g_tmr_list) {
		p_cur_tmr->tick -= tick;
	}

#ifdef SF_TMR_DEBUG
	{
		sf_timer_t *p_cur_tmr = NULL;
		uint32_t    tick = 0;
		printf("insert tmr\n");
		list_for_each_entry(p_cur_tmr, &__g_tmr_list, node) {
			tick += p_cur_tmr->tick;
			printf("tick: %d, remain: %d\n", tick, p_cur_tmr->tick);
			fflush(stdout);
		}
	}
#endif
}

static void __timer_remove (sf_timer_t *p_rm_tmr)
{
	spinlock_lock();

	if (list_empty(&p_rm_tmr->node)) {
		spinlock_unlock();
		return;
	}

	if (p_rm_tmr->node.next != &__g_tmr_list) {
		sf_timer_t *p_next_tmr = list_entry(p_rm_tmr->node.next, sf_timer_t, node);

		p_next_tmr->tick += p_rm_tmr->tick;
	}

	list_del(&p_rm_tmr->node);

	spinlock_unlock();

#ifdef SF_TMR_DEBUG
	{
		uint32_t tick = 0;
		sf_timer_t *p_cur_tmr  = NULL;
		printf("remove timer\n");
		list_for_each_entry(p_cur_tmr, &__g_tmr_list, node) {
			tick += p_cur_tmr->tick;
			printf("tick: %d, remain: %d\n", tick, p_cur_tmr->tick);
			fflush(stdout);
		}
	}
#endif
}

int sf_timer_start(sf_timer_t *p_timer, uint32_t tick)
{
	if (p_timer == NULL) {
		return -1;
	}

	spinlock_lock();
	__timer_remove(p_timer);
	__timer_add(p_timer, tick);
	spinlock_unlock();

	return 0;
}

int sf_timer_stop(sf_timer_t *p_timer)
{
	if (p_timer == NULL) {
		return -1;
	}
	spinlock_lock();
	__timer_remove(p_timer);
	spinlock_unlock();
	return 0;
}

