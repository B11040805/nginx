
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

// 动态数组 动态在可以扩展数组大小
// 分配在联系的内存上，查询速度快
typedef struct {
    void        *elts; // 指向数组的首地址
    ngx_uint_t   nelts; // 数组中已经使用的元素个数
    size_t       size; // 每个元素占用的内存大小
    ngx_uint_t   nalloc; // 数组的总大小
    ngx_pool_t  *pool; //内存池对象
} ngx_array_t;


ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);
void ngx_array_destroy(ngx_array_t *a);
void *ngx_array_push(ngx_array_t *a);
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);


static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0; // 初始化
    array->size = size; // 多大的数组
    array->nalloc = n;
    array->pool = pool;

    array->elts = ngx_palloc(pool, n * size);
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
