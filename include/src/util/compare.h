/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */



#ifndef UTIL_COMPARE_H
#define UTIL_COMPARE_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Equality file descriptors
static inline
bool eq_fd(const void* key1, const void* key2 )
{
  assert(key1 != NULL);
  assert(key2 != NULL);

  int* fd1 = (int*)key1;
  int* fd2 = (int*)key2;

  assert(*fd1 > -1);
  assert(*fd2 > -1);

  return *fd1 == *fd2;
}

// Comparation file descriptors
static inline 
int cmp_fd(void const* fd_v1, void const* fd_v2)
{
  assert(fd_v1 != NULL);
  assert(fd_v2 != NULL);
  int* fd1 = (int*)fd_v1;
  int* fd2 = (int*)fd_v2;

  assert(*fd1 > -1 && "File descriptors must be larger than zero");
  assert(*fd2 > -1 && "File descriptors must be larger than zero");

  if(*fd1 < *fd2) return 1;
  if(*fd1 == *fd2) return 0;
  return -1;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Equality file descriptors
static inline
bool eq_int(const void* key1, const void* key2 )
{
  assert(key1 != NULL);
  assert(key2 != NULL);

  int* m0 = (int*)key1;
  int* m1 = (int*)key2;

  return *m0 == *m1;
}

// Comparation file descriptors
static inline 
int cmp_int(void const* key1, void const* key2)
{
  assert(key1 != NULL);
  assert(key2 != NULL);
  int* m0 = (int*)key1;
  int* m1 = (int*)key2;

  assert(*m0 > -1 && "File descriptors must be larger than zero");
  assert(*m1 > -1 && "File descriptors must be larger than zero");

  if(*m0 < *m1) return 1;
  if(*m0 == *m1) return 0;
  return -1;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Equality uint32_t 
static inline
bool eq_uint32(const void* key1, const void* key2 )
{
  assert(key1 != NULL);
  assert(key2 != NULL);

  uint32_t* m0 = (uint32_t*)key1;
  uint32_t* m1 = (uint32_t*)key2;

  return *m0 == *m1;
}

// Comparation file descriptors
static inline 
int cmp_uint32(void const* key1, void const* key2)
{
  assert(key1 != NULL);
  assert(key2 != NULL);
  uint32_t* m0 = (uint32_t*)key1;
  uint32_t* m1 = (uint32_t*)key2;

  if(*m0 < *m1) return 1;
  if(*m0 == *m1) return 0;
  return -1;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////





static inline
bool eq_ran_func_id(const void* value, const void* key)
{
  uint16_t* ran_func_id1 = (uint16_t*)value;
  uint16_t* ran_func_id2 = (uint16_t*)key;
  assert(ran_func_id1 != NULL);
  assert(ran_func_id2 != NULL);

  return *ran_func_id1 == *ran_func_id2;
}

// Comparing RAN Function IDs
static inline
int cmp_ran_func_id(const void* a_v, const void* b_v)
{
  assert(a_v != NULL);
  assert(b_v != NULL);

  uint16_t* a = (uint16_t*)a_v;
  uint16_t* b = (uint16_t*)b_v;

  if(*a < *b) return 1;
  if(*a == *b) return 0;
  return -1; 
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

static inline
bool cmp_str(const void* a, const void* b)
{
  char* a_str = *(char**)(a);
  char* b_str = *(char**)(b);

  int const ret = strcmp(a_str, b_str);
  return ret == 0;
}

// Equality file descriptors
static inline
bool eq_fd_ind_ev(const void* key1, const void* key2 )
{
  assert(key1 != NULL);
  assert(key2 != NULL);

  int* fd1 = (int*)key1;
  int* fd2 = (int*)key2;

  return *fd1 == *fd2;
}

// Comparation file descriptors
static inline 
int cmp_fd_ind_ev(void const* fd_v1, void const* fd_v2)
{
  assert(fd_v1 != NULL);
  assert(fd_v2 != NULL);
  int* fd1 = (int*)fd_v1;
  int* fd2 = (int*)fd_v2;

  if(*fd1 < *fd2) return 1;
  if(*fd1 == *fd2) return 0;
  return -1;
}

#endif

