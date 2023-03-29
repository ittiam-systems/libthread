/* 	Copyright (c) [2020]-[2023] Ittiam Systems Pvt. Ltd.
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted (subject to the limitations in the
   disclaimer below) provided that the following conditions are met:
   •	Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   •	Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   •	None of the names of Ittiam Systems Pvt. Ltd., its affiliates,
   investors, business partners, nor the names of its contributors may be
   used to endorse or promote products derived from this software without
   specific prior written permission.

   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED
   BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
   BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   NOTWITHSTANDING ANYTHING TO THE CONTRARY, THIS DOES NOT GRANT ANY
   EXPRESS OR IMPLIED LICENSES TO ANY PATENT CLAIMS OF ANY AFFILIATE
   (TO THE EXTENT NOT IN THE LEGAL ENTITY), INVESTOR, OR OTHER
   BUSINESS PARTNER OF ITTIAM. You may only use this software or
   modifications thereto for purposes that are authorized by
   appropriate patent licenses. You should seek legal advice based
   upon your implementation details.
---------------------------------------------------------------*/

#ifndef _ITHREAD_H_
#define _ITHREAD_H_

#include <stdint.h>

#define ITHREAD_UNUSED(x) ((void) x)

typedef void *(*ThreadFxn)(void *);

uint32_t ithread_get_handle_size(void);

uint32_t ithread_get_mutex_lock_size(void);

int32_t ithread_create(void *thread_handle, void *attribute, ThreadFxn strt, void *argument);

void ithread_exit(void *val_ptr);

int32_t ithread_join(void *thread_id, void **val_ptr);

int32_t ithread_get_mutex_struct_size(void);

int32_t ithread_mutex_init(void *mutex);

int32_t ithread_mutex_destroy(void *mutex);

int32_t ithread_mutex_lock(void *mutex);

int32_t ithread_mutex_unlock(void *mutex);

void ithread_yield(void);

void ithread_sleep(uint32_t u4_time);

void ithread_msleep(uint32_t u4_time_ms);

void ithread_usleep(uint32_t u4_time_us);

uint32_t ithread_get_sem_struct_size(void);

int32_t ithread_sem_init(void *sem, int32_t pshared, uint32_t value);

int32_t ithread_sem_post(void *sem);

int32_t ithread_sem_wait(void *sem);

int32_t ithread_sem_destroy(void *sem);

int32_t ithread_set_affinity(int32_t core_id);

void ithread_set_name(char *pc_thread_name);

#endif /* _ITHREAD_H_ */
