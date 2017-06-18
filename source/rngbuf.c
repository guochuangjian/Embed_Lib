
#include "stdio.h"
#include "emdef.h"
#include "rngbuf.h"

void rngbuf_init(rngbuf_t *p_rb, char *p_buf, rb_size_t size)
{
    p_rb->in    = 0;
    p_rb->out   = 0;
    p_rb->p_buf = p_buf;
    p_rb->size  = size;
}

rb_size_t rngbuf_put(rngbuf_t *p_rb, char *p_buf, rb_size_t len)
{
    rb_size_t out      = p_rb->out; //保证多线程操作时，读写可同步操作。
    rb_size_t putbytes = 0;

    if (out > p_rb->in) {
        putbytes = min(out - p_rb->in - 1, len);

        memcpy(&p_rb->p_buf[p_rb->in], p_buf, putbytes);

        p_rb->in += putbytes;

    } else if (out == 0) {
        putbytes = min(p_rb->size - p_rb->in - 1 , len);
        memcpy(&p_rb->p_buf[p_rb->in], p_buf, putbytes);
        p_rb->in += putbytes;
    } else {
        putbytes = min(p_rb->size - p_rb->in, len);

        memcpy(&p_rb->p_buf[p_rb->in], p_buf, putbytes);
        p_rb->in += putbytes;

        if (p_rb->in == p_rb->size) {
            rb_size_t tmp = min(len - putbytes, out - 1);

            memcpy(&p_rb->p_buf[0], &p_buf[putbytes], tmp);

            p_rb->in  = tmp;
            putbytes += tmp;
        }
    }

    return putbytes;
}

rb_size_t rngbuf_get(rngbuf_t *p_rb, char *p_buf, rb_size_t len)
{
    rb_size_t in        = p_rb->in; //保证多线程操作时，读写可同步操作。
    rb_size_t out_bytes = 0;

    if (in >= p_rb->out) {
        out_bytes = min(in - p_rb->out, len);

        memcpy(p_buf, &p_rb->p_buf[p_rb->out], out_bytes);

        p_rb->out += out_bytes;
    } else {
        out_bytes = min(p_rb->size - p_rb->out, len);

        memcpy(p_buf, &p_rb->p_buf[p_rb->out], out_bytes);
        p_rb->out += out_bytes;

        if (p_rb->size == p_rb->out) {
            rb_size_t remain = min(len - out_bytes, in);

            memcpy(&p_buf[out_bytes], &p_rb->p_buf[0], remain);

            p_rb->out  = remain;
            out_bytes += remain;
        }
    }

    return out_bytes;
}

rb_size_t rngbuf_putchar(rngbuf_t *p_rb, char ch)
{
    if (rngbuf_nbytes_get(p_rb) == (p_rb->size - 1)) {
        return 0;
    }


    if (p_rb->out > p_rb->in && p_rb->out )

    p_rb->p_buf[p_rb->in] = ch;
    if (p_rb->in == p_rb->size) {
        p_rb->in = 0;
    } else {
        p_rb->in++;
    }

    return 1;
}

rb_size_t rngbuf_getchar(rngbuf_t *p_rb, char *p_ch)
{
    if (p_rb->in == p_rb->out) {
        return 0;
    }

    p_rb->p_buf[p_rb->out] = *p_ch;

    if (p_rb->out == p_rb->size) {
        p_rb->out = 0;
    } else {
        p_rb->out++;
    }

    return 1;
}

rb_size_t rngbuf_put_force(rngbuf_t *p_rb, char *p_buf, rb_size_t len)
{
    rb_size_t spcae     = p_rb->size - rngbuf_nbytes_get(p_rb) - 1;
    rb_size_t putbytes  = min(p_rb->size - 1, len);
    rb_size_t cur_space = min(putbytes, p_rb->size - p_rb->in);

    memcpy(&p_rb->p_buf[p_rb->in], p_buf, cur_space);
    p_rb->in += cur_space;

    if (p_rb->in == p_rb->size) {
        rb_size_t remain_size = putbytes - cur_space;

        memcpy(&p_rb->p_buf[0], &p_buf[cur_space], remain_size);
        p_rb->in = remain_size;
    }

    if (putbytes > spcae) {
        if (p_rb->in == p_rb->size) {
            p_rb->out = 1;
        } else {
            p_rb->out = p_rb->in + 1;
        }
    }

    return putbytes;
}

void rngbuf_putchar_force(rngbuf_t *p_rb, char ch)
{
    uint8_t is_full = ((p_rb->size - rngbuf_nbytes_get(p_rb)) == 1) ? 1 : 0;

    p_rb->p_buf[p_rb->in] = ch;

    if (p_rb->in == p_rb->size) {
        p_rb->in = 0;
    } else {
        p_rb->in++;
    }

    if (is_full) {
        if (p_rb->in == p_rb->size) {
            p_rb->out = 0;
        } else {
            p_rb->out = p_rb->in + 1;
        }
    }
}

uint16_t rngbuf_nbytes_get(rngbuf_t *p_rb)
{
    return p_rb->in < p_rb->out ? (p_rb->size - p_rb->out + p_rb->in) :
                                  (p_rb->in - p_rb->out);
}
