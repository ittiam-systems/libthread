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

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/
#include <string.h>
#include <stdint.h>

#include "ithread.h"
#include <sys/types.h>

#ifndef WINDOWS
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <unistd.h>
#endif

#ifdef MACOS
#include <dispatch/dispatch.h>
#endif

#ifdef WINDOWS
#include <windows.h>

#define SEM_MAX_COUNT 100
#define SEM_INCREMENT_COUNT 1

uint32_t ithread_get_handle_size(void)
{
  return (sizeof(HANDLE));
}

uint32_t ithread_get_mutex_lock_size(void)
{
  return (sizeof(HANDLE));
}

int32_t ithread_create(void *thread_handle, void *attribute, ThreadFxn strt, void *argument)
{
  HANDLE *ppv_thread_handle;
  HANDLE  thread_handle_value;

  UNUSED(attribute);

  if (0 == thread_handle)
    return -1;

  ppv_thread_handle   = (HANDLE *) thread_handle;
  thread_handle_value = (void *) CreateThread(NULL,                          /* Attributes      */
                                              1024 * 128,                    /* Stack i4_size      */
                                              (LPTHREAD_START_ROUTINE) strt, /* Thread function */
                                              argument,                      /* Parameters      */
                                              0,                             /* Creation flags  */
                                              NULL);                         /* Thread ID       */
  *ppv_thread_handle  = (HANDLE) thread_handle_value;

  return 0;
}

int32_t ithread_join(void *thread_handle, void **val_ptr)
{
  HANDLE *ppv_thread_handle;
  HANDLE  thread_handle_value;

  UNUSED(val_ptr);

  if (0 == thread_handle)
    return -1;

  ppv_thread_handle   = (HANDLE *) thread_handle;
  thread_handle_value = *ppv_thread_handle;

  if (WAIT_OBJECT_0 == WaitForSingleObject(thread_handle_value, INFINITE))
  {
    CloseHandle(thread_handle_value);
  }

  return 0;
}

void ithread_exit(void *thread_handle)
{
  HANDLE *ppv_thread_handle;
  HANDLE  thread_handle_value;
  DWORD   thread_exit_code;

  if (0 == thread_handle)
    return;

  ppv_thread_handle   = (HANDLE *) thread_handle;
  thread_handle_value = *ppv_thread_handle;
  /* Get exit code for thread. If the return value is 0, means thread is busy */
  if (0 != GetExitCodeThread(thread_handle_value, &thread_exit_code))
  {
    TerminateThread(thread_handle_value, thread_exit_code);
  }

  return;
}

int32_t ithread_get_mutex_struct_size(void)
{
  return (sizeof(HANDLE));
}

int32_t ithread_mutex_init(void *mutex)
{
  HANDLE *ppv_mutex_handle;
  HANDLE  mutex_handle_value;

  if (0 == mutex)
    return -1;

  ppv_mutex_handle   = (HANDLE *) mutex;
  mutex_handle_value = CreateSemaphore(NULL, 1, 1, NULL);
  *ppv_mutex_handle  = mutex_handle_value;
  return 0;
}

int32_t ithread_mutex_destroy(void *mutex)
{
  HANDLE *ppv_mutex_handle;
  HANDLE  mutex_handle_value;

  if (0 == mutex)
    return -1;

  ppv_mutex_handle   = (HANDLE *) mutex;
  mutex_handle_value = *ppv_mutex_handle;
  CloseHandle(mutex_handle_value);
  return 0;
}

int32_t ithread_mutex_lock(void *mutex)
{
  HANDLE *ppv_mutex_handle;
  HANDLE  mutex_handle_value;
  DWORD   result = 0;

  if (0 == mutex)
    return -1;

  ppv_mutex_handle   = (HANDLE *) mutex;
  mutex_handle_value = *ppv_mutex_handle;
  result             = WaitForSingleObject(mutex_handle_value, INFINITE);

  if (WAIT_OBJECT_0 == result)
    return 0;

  return 1;
}

int32_t ithread_mutex_unlock(void *mutex)
{
  HANDLE *ppv_mutex_handle;
  HANDLE  mutex_handle_value;
  DWORD   result = 0;

  if (0 == mutex)
    return -1;

  ppv_mutex_handle   = (HANDLE *) mutex;
  mutex_handle_value = *ppv_mutex_handle;
  result             = ReleaseSemaphore(mutex_handle_value, 1, NULL);

  if (0 == result)
    return -1;

  return 0;
}

void ithread_yield(void) {}

void ithread_usleep(uint32_t u4_time_us)
{
  uint32_t u4_time_ms = u4_time_us / 1000;
  Sleep(u4_time_ms);
}

void ithread_msleep(uint32_t u4_time_ms)
{
  Sleep(u4_time_ms);
}

void ithread_sleep(uint32_t u4_time)
{
  uint32_t u4_time_ms = u4_time * 1000;
  Sleep(u4_time_ms);
}

uint32_t ithread_get_sem_struct_size(void)
{
  return (sizeof(HANDLE));
}

int32_t ithread_sem_init(void *sem, int32_t pshared, uint32_t value)
{
  HANDLE *sem_handle = (HANDLE *) sem;
  HANDLE  sem_handle_value;

  UNUSED(pshared);

  if (0 == sem)
    return -1;

  sem_handle_value = CreateSemaphore(NULL,          /* Security Attribute*/
                                     value,         /* Initial count     */
                                     SEM_MAX_COUNT, /* Max value         */
                                     NULL);         /* Name, not used    */
  *sem_handle      = sem_handle_value;
  return 0;
}

int32_t ithread_sem_post(void *sem)
{
  HANDLE *sem_handle = (HANDLE *) sem;
  HANDLE  sem_handle_value;

  if (0 == sem)
    return -1;

  sem_handle_value = *sem_handle;

  /* Post on Semaphore by releasing the lock on mutex */
  if (ReleaseSemaphore(sem_handle_value, SEM_INCREMENT_COUNT, NULL))
    return 0;

  return -1;
}

int32_t ithread_sem_wait(void *sem)
{
  DWORD   result     = 0;
  HANDLE *sem_handle = (HANDLE *) sem;
  HANDLE  sem_handle_value;

  if (0 == sem)
    return -1;

  sem_handle_value = *sem_handle;

  /* Wait on Semaphore object infinitly */
  result = WaitForSingleObject(sem_handle_value, INFINITE);

  /* If lock on semaphore is acquired, return SUCCESS */
  if (WAIT_OBJECT_0 == result)
    return 0;

  /* If call timeouts, return FAILURE */
  if (WAIT_TIMEOUT == result)
    return -1;

  return 0;
}

int32_t ithread_sem_destroy(void *sem)
{
  HANDLE *sem_handle = (HANDLE *) sem;
  HANDLE  sem_handle_value;

  if (0 == sem)
    return -1;

  sem_handle_value = *sem_handle;

  if (FALSE == CloseHandle(sem_handle_value))
  {
    return -1;
  }
  return 0;
}

int32_t ithread_set_affinity(int32_t core_id)
{
  UNUSED(core_id);

  return 1;
}

void ithread_set_name(char *pc_thread_name)
{
  UNUSED(pc_thread_name);

  return;
}

#else

uint32_t ithread_get_handle_size(void)
{
  return sizeof(pthread_t);
}

uint32_t ithread_get_mutex_lock_size(void)
{
  return sizeof(pthread_mutex_t);
}

int32_t ithread_create(void *thread_handle, void *attribute, ThreadFxn strt, void *argument)
{
  UNUSED(attribute);
  return pthread_create((pthread_t *) thread_handle, NULL, strt, argument);
}

int32_t ithread_join(void *thread_handle, void **val_ptr)
{
  pthread_t *pthread_handle = (pthread_t *) thread_handle;
  UNUSED(val_ptr);
  return pthread_join(*pthread_handle, NULL);
}

void ithread_exit(void *val_ptr)
{
  pthread_exit(val_ptr);
}

int32_t ithread_get_mutex_struct_size(void)
{
  return (sizeof(pthread_mutex_t));
}
int32_t ithread_mutex_init(void *mutex)
{
  return pthread_mutex_init((pthread_mutex_t *) mutex, NULL);
}

int32_t ithread_mutex_destroy(void *mutex)
{
  return pthread_mutex_destroy((pthread_mutex_t *) mutex);
}

int32_t ithread_mutex_lock(void *mutex)
{
  return pthread_mutex_lock((pthread_mutex_t *) mutex);
}

int32_t ithread_mutex_unlock(void *mutex)
{
  return pthread_mutex_unlock((pthread_mutex_t *) mutex);
}

void ithread_yield(void)
{
  sched_yield();
}

void ithread_sleep(uint32_t u4_time)
{
  usleep(u4_time * 1000 * 1000);
}

void ithread_msleep(uint32_t u4_time_ms)
{
  usleep(u4_time_ms * 1000);
}

void ithread_usleep(uint32_t u4_time_us)
{
  usleep(u4_time_us);
}
#ifdef MACOS
typedef struct  {
    dispatch_semaphore_t    disp_sem;
}mac_sem;

uint32_t ithread_get_sem_struct_size(void)
{
  return (sizeof(mac_sem));
}

int32_t ithread_sem_init(void *sem, int32_t pshared, uint32_t value)
{
	mac_sem *mac_sem = sem;
        UNUSED(pshared);
	
	dispatch_semaphore_t *dispatch_sem = &mac_sem->disp_sem;

    *dispatch_sem = dispatch_semaphore_create(value);
    return 1;
}

int32_t ithread_sem_post(void *sem)
{
	mac_sem *mac_sem = sem;
	
	dispatch_semaphore_signal(mac_sem->disp_sem);
    return 1;
}

int32_t ithread_sem_wait(void *sem)
{
	mac_sem *mac_sem = sem;
	
	dispatch_semaphore_wait(mac_sem->disp_sem, DISPATCH_TIME_FOREVER);
  return 1;
}

int32_t ithread_sem_destroy(void *sem)
{
	mac_sem *mac_sem = sem;
        //UNUSED(sem);
	
	dispatch_release(mac_sem->disp_sem);
  return 1;
}

#else //LINUX
uint32_t ithread_get_sem_struct_size(void)
{
  return (sizeof(sem_t));
}

int32_t ithread_sem_init(void *sem, int32_t pshared, uint32_t value)
{
  return sem_init((sem_t *) sem, pshared, value);
}

int32_t ithread_sem_post(void *sem)
{
  return sem_post((sem_t *) sem);
}

int32_t ithread_sem_wait(void *sem)
{
  return sem_wait((sem_t *) sem);
}

int32_t ithread_sem_destroy(void *sem)
{
  return sem_destroy((sem_t *) sem);
}
#endif //end of Linux

void ithread_set_name(char *pc_thread_name)
{

#ifndef WIN32
#ifndef QNX
#ifndef IOS
  UNUSED(pc_thread_name);
#endif
#endif
#endif
}
int32_t ithread_set_affinity(int32_t core_id)
{
#ifdef PTHREAD_AFFINITY
  cpu_set_t cpuset;
  int       num_cores  = sysconf(_SC_NPROCESSORS_ONLN);
  pthread_t cur_thread = pthread_self();

  if (core_id >= num_cores)
    return -1;

  CPU_ZERO(&cpuset);
  CPU_SET(core_id, &cpuset);

  return pthread_setaffinity_np(cur_thread, sizeof(cpu_set_t), &cpuset);

#elif SYSCALL_AFFINITY
  int32_t i4_sys_res;
  UNUSED(core_id);

  pid_t pid = gettid();

  i4_sys_res = syscall(__NR_sched_setaffinity, pid, sizeof(i4_mask), &i4_mask);
  if (i4_sys_res)
  {
    return -1;
  }
#else
  UNUSED(core_id);
#endif
  return 1;
}
#endif
