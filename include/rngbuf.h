/*
 *  \brief RingBufferʵ��
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

typedef uint16_t rb_size_t; /* �û�������������  */

typedef struct rngbuf {
    rb_size_t in;
    rb_size_t out;
	char     *p_buf;
	rb_size_t size;
} rngbuf_t;

/**
 * \brief ��ʼ�����λ���
 *
 * \param p_rb   : ��ʼ���Ļ��λ�����
 * \param p_buf  : ������
 * \param size   : ��������С; �ر�ע��:ϵͳ����һ���ֽڣ�ʵ�ʿ��ô�СΪ size - 1
 */
void rngbuf_init(rngbuf_t *p_rb, char *p_buf, rb_size_t size);

/**
 * \brief ������ݵ�������
 * \attetion rngbuf_put��rngbuf_get���̶߳�д��ȫ���˴���д��ȫΪ�� �߳�1����rngbuf_get,
 *           �߳�2����rngbuf_put�ò���Ϊ�̰߳�ȫ
 *
 * \param p_rb  : �����Ļ��λ�����
 * \param p_buf : ��ŵ����ݻ�����
 * \param size  : ��������ֽ���
 *
 * \return ʵ�ʴ���ֽ���
 */
rb_size_t rngbuf_put(rngbuf_t *p_rb, char *p_buf, rb_size_t len);

/**
 * \brief ��ȡ���ݵ�������
 * \attetion rngbuf_put��rngbuf_get���̶߳�д��ȫ���˴���д��ȫΪ�� �߳�1����rngbuf_get,
 *           �߳�2����rngbuf_put�ò���Ϊ�̰߳�ȫ
 * \param p_rb  : �����Ļ��λ�����
 * \param p_buf : ��ȡ�����ݻ�����
 * \param size  : ��ȡ�����ֽ���
 *
 * \return ʵ�ʻ�ȡ�ֽ���
 */
rb_size_t rngbuf_get(rngbuf_t *p_rb, char *p_buf, rb_size_t len);

/**
 * \brief д��һ���ֽ�
 *
 * \param p_rb  : �����Ļ��λ�����
 * \param ch    : д����ֽ�
 *
 * \retval 1 : д��һ���ֽ�
 * \retval 0 : ����������д��0���ֽ�
 */
rb_size_t rngbuf_putchar(rngbuf_t *p_rb, char ch);

/**
 * \brief ��ȡһ���ֽ�
 *
 * \param p_rb  : �����Ļ��λ�����
 * \param *p_ch : ��ȡ���ֽڻ���
 *
 * \retval 1 : ��ȡһ���ֽ�
 * \retval 0 : �������գ���ȡ0���ֽ�
 */
rb_size_t rngbuf_getchar(rngbuf_t *p_rb, char *p_ch);

/**
 * \brief ǿ�����λ�����д�����ݣ��������д�볤��Ϊsize - 1
 *
 * \param p_rb  : �����Ļ��λ�����
 * \param p_buf : д������ݻ�����
 * \param len   : д���ֽ���
 *
 * \return ʵ��д���ֽ���
 */
rb_size_t rngbuf_put_force(rngbuf_t *p_rb, char *p_buf, rb_size_t len);

/**
 * \brief ǿ�����λ�����д��һ���ֽ�
 *
 * \param p_rb  : �����Ļ��λ�����
 * \param ch    : д���ֽ�
 *
 */
void rngbuf_putchar_force(rngbuf_t *p_rb, char ch);

/**
 * \brief ��ȡ���λ�������ʹ�õ��ֽ���
 *
 * \param p_rb  : �����Ļ��λ�����
 *
 * \return ���λ�������ʹ���ֽ���
 */
uint16_t rngbuf_nbytes_get(rngbuf_t *p_rb);

/**
 * \brief ��ջ��λ�����
 *
 * \param p_rb  : �����Ļ��λ�����
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
