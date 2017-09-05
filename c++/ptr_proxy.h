//
// Created by Pure on 17/9/5.
//

#ifndef TEST_CODE_PTR_PROXY_H
#define TEST_CODE_PTR_PROXY_H

#include <stdio.h>
#include <stdint.h>
#include <vector>

using namespace std;

template<typename T>
class ptr_proxy {

public:
    ptr_proxy(const T *pobj = NULL) : m_ppobj(NULL), m_pcount(NULL) {
        if (pobj == NULL) {
            return;
        }
        init(pobj);
    }

    ptr_proxy(const ptr_proxy &rhs) {
        m_ppobj = rhs.m_ppobj;
        m_pcount = rhs.m_pcount;
        add_count();
    }

    virtual ~ptr_proxy() {
        dec_count();
    }

    void set2null() {
        if (m_ppobj) {
            *m_ppobj = NULL;
        }
    }

    ptr_proxy &operator=(const ptr_proxy &rhs) {
        if (m_ppobj == rhs.m_ppobj) {
            return *this;
        }

        dec_count();
        m_ppobj = rhs.m_ppobj;
        m_pcount = rhs.m_pcount;
        add_count();

        return *this;
    }

    ptr_proxy &operator=(const T *pobj) {
        if (m_ppobj && *m_ppobj == pobj) {
            return *this;
        }

        dec_count();
        init(pobj);

        return *this;
    }

    T *origin_ptr() {
        if (m_ppobj) {
            return *m_ppobj;
        } else {
            return NULL;
        }
    }

    T *operator*() {
        return origin_ptr();
    };

    int count() const {
        if (m_pcount) {
            return *m_pcount;
        } else {
            return 0;
        }
    }

    bool is_null() {
        if (m_ppobj == NULL) {
            return true;
        }

        if ((*m_ppobj) == NULL) {
            return true;
        }

        return false;
    }

protected:
    void init(const T *pobj) {
        m_ppobj = new(T *)();
        *m_ppobj = (T *) pobj;
        m_pcount = new int();
        *m_pcount = 1;
    }

    void add_count() {
        if (m_pcount == NULL) {
            return;
        }
        (*m_pcount)++;
    }

    void dec_count() {
        if (m_pcount == NULL || m_ppobj == NULL) {
            return;
        }

        (*m_pcount)--;
        if (*m_pcount <= 0) {
            if (m_ppobj != NULL) {
                delete m_ppobj;
                m_ppobj = NULL;
            }

            if (m_pcount != NULL) {
                delete m_pcount;
                m_pcount = NULL;
            }
        }
    }

protected:
    T **m_ppobj;
    int *m_pcount;

};

template<typename T>
class IPtrProxy {
public:
    IPtrProxy() {
        m_ptr_proxy = (T *) this;
    }

    virtual ~IPtrProxy() {
        m_ptr_proxy.set2null();
    }

    ptr_proxy<T> &get_ptr_proxy() {
        return m_ptr_proxy;
    }

protected:
    ptr_proxy<T> m_ptr_proxy;
};

#endif //TEST_CODE_PTR_PROXY_H
