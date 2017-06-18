/*
 *  \brief RingBuffer实现
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
#ifndef __RNGBUF_H_
#define __RNGBUF_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "string.h"

typedef uint16_t rb_size_t; /* 用户定义数据类型  */

typedef struct rngbuf {
    rb_size_t in;
    rb_size_t out;
	char     *p_buf;
	rb_size_t size;
} rngbuf_t;

/**
 * \brief 初始化环形缓冲
 *
 * \param p_rb   : 初始化的环形缓冲区
 * \param p_buf  : 缓冲区
 * \param size   : 缓冲区大小; 特别注意:系统保留一个字节，实际可用大小为 size - 1
 */
void rngbuf_init(rngbuf_t *p_rb, char *p_buf, rb_size_t size);

/**
 * \brief 存放数据到缓冲区
 * \attetion rngbuf_put与rngbuf_get多线程读写安全，此处读写安全为： 线程1调用rngbuf_get,
 *           线程2调用rngbuf_put该操作为线程安全
 *
 * \param p_rb  : 操作的环形缓冲区
 * \param p_buf : 存放的数据缓冲区
 * \param size  : 存放数据字节数
 *
 * \return 实际存放字节数
 */
rb_size_t rngbuf_put(rngbuf_t *p_rb, char *p_buf, rb_size_t len);

/**
 * \brief 获取数据到缓冲区
 * \attetion rngbuf_put与rngbuf_get多线程读写安全，此处读写安全为： 线程1调用rngbuf_get,
 *           线程2调用rngbuf_put该操作为线程安全
 * \param p_rb  : 操作的环形缓冲区
 * \param p_buf : 获取的数据缓冲区
 * \param size  : 获取数据字节数
 *
 * \return 实际获取字节数
 */
rb_size_t rngbuf_get(rngbuf_t *p_rb, char *p_buf, rb_size_t len);

/**
 * \brief 写入一个字节
 *
 * \param p_rb  : 操作的环形缓冲区
 * \param ch    : 写入的字节
 *
 * \retval 1 : 写入一个字节
 * \retval 0 : 缓冲区满，写入0个字节
 */
rb_size_t rngbuf_putchar(rngbuf_t *p_rb, char ch);

/**
 * \brief 读取一个字节
 *
 * \param p_rb  : 操作的环形缓冲区
 * \param *p_ch : 读取的字节缓冲
 *
 * \retval 1 : 读取一个字节
 * \retval 0 : 缓冲区空，读取0个字节
 */
rb_size_t rngbuf_getchar(rngbuf_t *p_rb, char *p_ch);

/**
 * \brief 强制向环形缓冲区写入数据，最大允许写入长度为size - 1
 *
 * \param p_rb  : 操作的环形缓冲区
 * \param p_buf : 写入的数据缓冲区
 * \param len   : 写入字节数
 *
 * \return 实际写入字节数
 */
rb_size_t rngbuf_put_force(rngbuf_t *p_rb, char *p_buf, rb_size_t len);

/**
 * \brief 强制向环形缓冲区写入一个字节
 *
 * \param p_rb  : 操作的环形缓冲区
 * \param ch    : 写入字节
 *
 */
void rngbuf_putchar_force(rngbuf_t *p_rb, char ch);

/**
 * \brief 获取环形缓冲区已使用的字节数
 *
 * \param p_rb  : 操作的环形缓冲区
 *
 * \return 环形缓冲区已使用字节数
 */
uint16_t rngbuf_nbytes_get(rngbuf_t *p_rb);

/**
 * \brief 清空环形缓冲区
 *
 * \param p_rb  : 操作的环形缓冲区
 */
inline void rngbuf_flush(rngbuf_t *p_rb)
{
    p_rb->in  = 0;
    p_rb->out = 0;
}

#ifdef __cplusplus
}
#endif

#endif
