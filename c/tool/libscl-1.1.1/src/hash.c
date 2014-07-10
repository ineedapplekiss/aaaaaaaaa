/*
 * This file is part of the SCL software.
 * The license which this software falls under is as follows:
 *
 * Copyright (C) 2004-2010 Douglas Jerome <douglas@backstep.org>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


/* *****************************************************************************

FILE NAME

	$RCSfile: hash.c,v $
	$Revision: 1.9 $
	$Date: 2010/04/14 02:52:39 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Hash Container Implementation

	Many of the hash functions depends upon:
	1. SCL_ALLOCATOR() setting allocated memory to binary 0,
	2. SCL_ALLOCATOR() returning NULL if memory allocation fails and
	3. NULL being equal to binary 0.

CHANGE LOG

	13apr10	drj	Fixed bug in the rebuild() function.

	04apr10	drj	Added callback context pointer to hash_foreach().

	31mar10	drj	Fixed a warning in private function md() that was
			generated by either a newer GCC or 64-bit systems, or
			both.

	06jun06	drj	Miscellaneous format finessing.

	16dec04	drj	hash_insert() returns SCL_DUPKEY for duplicate keys.

	10dec04	drj	Added hash_key_get().

	26nov04	drj	Changed hash_update() to hash_replace().

	16nov04	drj	File generation.

***************************************************************************** */


/* ************************************************************************* */
/*                                                                           */
/*      F e a t u r e   S w i t c h e s                                      */
/*                                                                           */
/* ************************************************************************* */

/*
 * Select these feature by moving them from the `if UNDEF' into the `else'
 * section.
 */
#ifdef	UNDEF
#   define	_BSD_SOURCE	1	/* 4.3+bsd subsystems           */
#   define	_POSIX_SOURCE	1	/* posix.1                      */
#   define	_POSIX_C_SOURCE	199309L	/* posix.1 and posix.4          */
#   define	_POSIX_C_SOURCE	199506L	/* posix.1 and posix.4 and MORE */
#else
#   define	_POSIX_C_SOURCE	200112L	/* posix.1 and posix.4 and MORE */
#   undef	_REENTRANT
#   define	_REENTRANT		/* thread-safe for glibc        */
#endif


/* ************************************************************************* */
/*                                                                           */
/*      I n c l u d e d   F i l e s                                          */
/*                                                                           */
/* ************************************************************************* */

/*
 * OS Specific Header Files
 */
#ifdef	WIN32
#   include	"stdafx.h"
#endif

/*
 * Standard C (ANSI) Header Files
 */
#include	<string.h>

/*
 * Posix Header Files
 */
#ifdef	_unix
#   include	<unistd.h> /* always first amongst POSIX header files */
#endif

/*
 * Project Specific Header Files
 */
#include	"SCL_hash.h"


/* ************************************************************************* */
/*                                                                           */
/*      C o n s t a n t s                                                    */
/*                                                                           */
/* ************************************************************************* */

#define   PRED(x)   ((x)->pred)
#define   SUCC(x)   ((x)->succ)

#define   COSMOLOGICAL_CONSTANT   (7)


/* ************************************************************************* */
/*                                                                           */
/*      E x t e r n a l   R e f e r e n c e s                                */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      D a t a   T y p e s   a n d   S t r u c t u r e s                    */
/*                                                                           */
/* ************************************************************************* */

typedef struct S_node_t     S_node_t;
typedef struct S_SCL_hash_t S_SCL_hash_t;

struct S_node_t
   {
   S_node_t*   pred;
   S_node_t*   succ;
   SCL_hash_t  hash;
   long        index;
   const char* key;
   const void* data;
   };

struct S_SCL_hash_t
   {
   S_node_t** table;
   SCL_mdfn_t mdfn;
   size_t     count;
   size_t     size;
   size_t     bmod;
   };


/* ************************************************************************* */
/*                                                                           */
/*      P u b l i c   G l o b a l   V a r i a b l e s                        */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      P r i v a t e   G l o b a l   V a r i a b l e s                      */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (Locally Used Functions)             */
/*                                                                           */
/* ************************************************************************* */


/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

static uint32_t md (const char* k, size_t l);
static __inline__ long hashfn(SCL_hash_t a_hash,const char* a_key,size_t a_len);
static __inline__ void insert (S_node_t** const a_list, S_node_t* const a_node);
static __inline__ S_node_t* find (S_node_t** const a_list, const char* a_key);
static __inline__ int rebuild (S_SCL_hash_t* a_hash);


/*****************************************************************************
 * Private Function md
 *****************************************************************************/

static uint32_t md (const char* a_keyptr, size_t a_keylen)
   {
   register const unsigned char* p = (const unsigned char*)a_keyptr;
   register size_t len = a_keylen;
   register uint32_t v = 0;
   register uint32_t g;

   while (len > 0)
      {
      v = (v << 4) + (uint32_t)(*p++ * (unsigned char)17);
      if ((g = v & 0xF0000000))
         {
         v = v ^ (g >> 24);
         v = v ^ g;
         }
      len -= 1;
      }

   return v;
   }


/*****************************************************************************
 * Private Function hashfn
 *****************************************************************************/

static __inline__ long hashfn (SCL_hash_t a_hash,const char*a_key,size_t a_len)
   {
   register uint32_t v;

   v = (*a_hash->mdfn) (a_key, a_len);
   v = v & a_hash->bmod;

   return (long)v;
   }


/*****************************************************************************
 * Private Function insert
 *****************************************************************************/

static __inline__ void insert (S_node_t** const a_list, S_node_t* const a_node)
   {
   register S_node_t* const node = a_node;
   register S_node_t* const head = *a_list;

   if (head != NULL)
      {
      PRED(head) = node;
      SUCC(node) = head;
      }
   else
      {
      SUCC(node) = NULL;
      }
   PRED(node) = NULL;
   *a_list = node;

   return;
   }


/*****************************************************************************
 * Private Function find
 *****************************************************************************/

static __inline__ S_node_t* find (S_node_t** const a_list, const char* a_key)
   {
   register const S_node_t* node = *a_list;

   while (node != NULL)
      {
      if (strcmp(node->key,a_key) == 0) break;
      node = SUCC(node);
      }

   return (S_node_t*)node;
   }


/*****************************************************************************
 * Private Function rebuild
 *****************************************************************************/

static __inline__ int rebuild (S_SCL_hash_t* a_hash)
   {
   register S_SCL_hash_t* const hash = a_hash;

   register size_t size = hash->size << 2;
   register size_t bmod = size - 1;

   register S_node_t* node;
   register S_node_t* next;
   register long index;

   register int i;

   S_node_t** nodes = SCL_ALLOCATOR (size * sizeof(S_node_t*));
   if (nodes == NULL) return SCL_NOMEM;

   hash->bmod = bmod; /* Set this here so the new indexes generated below  */
                      /* are in the reference frame of the new hash table. */
                      /* Bug fix reported by <chenzunfeng@qq.com>          */

   for (i=hash->size-1 ; i>=0 ; i--)
      {
      node = hash->table[i];
      while (node != NULL)
         {
         next = SUCC(node);
         index = hashfn (hash, node->key, strlen(node->key));
         node->index = index;
         (void)insert (&nodes[index], node);
         node = next;
         }
      }

   SCL_DEALLOCATOR ((void*)hash->table);

   hash->table = nodes;
   hash->size = size;

   return SCL_OK;
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/*****************************************************************************
 * Public Function hash_new
 *****************************************************************************/

#define	BITS_IN_LONG	(sizeof(long)*8)
#define	BITS_IN_SIZE	(2)

SCL_hash_t (hash_new) (SCL_mdfn_t a_mdfn)
   {
   S_SCL_hash_t* const hash = SCL_ALLOCATOR (sizeof(S_SCL_hash_t));
   S_node_t** const nodes = SCL_ALLOCATOR ((1<<BITS_IN_SIZE)*sizeof(S_node_t*));

   if ((hash == NULL) || (nodes == NULL))
      {
      if (hash != NULL) SCL_DEALLOCATOR (hash);
      if (nodes != NULL) SCL_DEALLOCATOR (nodes);
      return NULL;
      }

   hash->mdfn = a_mdfn != NULL ? a_mdfn : md;
   hash->table = nodes;
   hash->size = 1 << BITS_IN_SIZE;
   hash->bmod = hash->size - 1;

   return hash;
   }

#undef	BITS_IN_LONG
#undef	BITS_IN_SIZE


/*****************************************************************************
 * Public Function hash_del
 *****************************************************************************/

void (hash_del) (SCL_hash_t a_hash)
   {
   S_SCL_hash_t* const hash = a_hash;

   size_t size = hash->size;
   S_node_t** table = hash->table;

   S_node_t* node1;
   S_node_t* node2;

   while (size-- > 0)
      {
      node1 = *table++;
      while (node1 != NULL)
         {
         node2 = SUCC(node1);
         SCL_DEALLOCATOR ((void*)node1);
         node1 = node2;
         }
      }

   SCL_DEALLOCATOR (hash->table);
   SCL_DEALLOCATOR (hash);

   return;
   }


/*****************************************************************************
 * Public Function hash_erase
 *****************************************************************************/

void (hash_erase) (SCL_hash_t a_hash)
   {
   S_SCL_hash_t* const hash = a_hash;

   size_t size = hash->size;
   S_node_t** table = hash->table;

   const S_node_t* node1;
   const S_node_t* node2;

   while (size-- > 0)
      {
      node1 = *table;
      while (node1 != NULL)
         {
         node2 = SUCC(node1);
         SCL_DEALLOCATOR ((void*)node1);
         node1 = node2;
         }
      *table++ = NULL;
      }

   hash->count = 0;

   return;
   }


/*****************************************************************************
 * Public Function hash_size
 *****************************************************************************/

size_t (hash_size) (SCL_hash_t a_hash)
   {
   return a_hash->size;
   }


/*****************************************************************************
 * Public Function hash_count
 *****************************************************************************/

size_t (hash_count) (SCL_hash_t a_hash)
   {
   return a_hash->count;
   }


/*****************************************************************************
 * Public Function hash_insert
 *****************************************************************************/

int (hash_insert) (SCL_hash_t a_hash, const char* a_key, const void* a_data)
   {
   S_SCL_hash_t* const hash = a_hash;
   const long index = hashfn (hash, a_key, strlen(a_key));
   S_node_t* node;

   node = find (&hash->table[index], a_key);
   if (node != NULL) return SCL_DUPKEY;

   node = SCL_ALLOCATOR (sizeof(S_node_t));
   if (node == NULL) return SCL_NOMEM;

   node->hash = hash;
   node->index = index;
   node->key = a_key;
   node->data = a_data;

   (void)insert (&hash->table[index], node);

   hash->count += 1;

   if (hash->count > COSMOLOGICAL_CONSTANT * hash->size)
      {
      (void)rebuild (hash);
      }

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function hash_replace
 *****************************************************************************/

int (hash_replace) (SCL_hash_t a_hash, const char* a_key, const void* a_data)
   {
   S_SCL_hash_t* const hash = a_hash;
   const long index = hashfn (hash, a_key, strlen(a_key));
   S_node_t* node = find (&hash->table[index], a_key);

   if (node != NULL)
      {
      node->data = a_data;
      return SCL_OK;
      }

   node = SCL_ALLOCATOR (sizeof(S_node_t));
   if (node == NULL) return SCL_NOMEM;

   node->hash = hash;
   node->index = index;
   node->key = a_key;
   node->data = a_data;

   (void)insert (&hash->table[index], node);

   hash->count += 1;

   if (hash->count > COSMOLOGICAL_CONSTANT * hash->size)
      {
      (void)rebuild (hash);
      }

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function hash_remove
 *****************************************************************************/

void* (hash_remove) (SCL_hash_t a_hash, const char* a_key)
   {
   S_SCL_hash_t* const hash = a_hash;
   const long index = hashfn ((SCL_hash_t)hash, a_key, strlen(a_key));
   S_node_t* const node = find (&hash->table[index], a_key);

   const void* data;

   if (node == NULL) return NULL;

   if (SUCC(node) != NULL) PRED(SUCC(node)) = PRED(node);
   if (PRED(node) != NULL) SUCC(PRED(node)) = SUCC(node);
   else hash->table[index] = SUCC(node);

   data = node->data;

   SCL_DEALLOCATOR ((void*)node);
   hash->count -= 1;

   return (void*)data;
   }


/*****************************************************************************
 * Public Function hash_access
 *****************************************************************************/

void* (hash_access) (SCL_hash_t a_hash, const char* a_key)
   {
   const long index = hashfn (a_hash, a_key, strlen(a_key));
   const S_node_t* const node = find (&a_hash->table[index], a_key);
   return node != NULL ? (void*)node->data : NULL;
   }


/*****************************************************************************
 * Public Function hash_at
 *****************************************************************************/

SCL_iterator_t (hash_at) (SCL_hash_t a_hash, const char* a_key)
   {
   const long index = hashfn (a_hash, a_key, strlen(a_key));
   return (SCL_iterator_t) find (&a_hash->table[index], a_key);
   }


/*****************************************************************************
 * Public Function hash_begin
 *****************************************************************************/

SCL_iterator_t (hash_begin) (SCL_hash_t a_hash)
   {
   const S_node_t* node = NULL;
   size_t index = a_hash->size;
   const S_node_t** table = (const S_node_t**)a_hash->table;

   while ((node == NULL) && (index-- > 0))
      {
      node = *table++;
      }

   return (SCL_iterator_t)node;
   }


/*****************************************************************************
 * Public Function hash_end
 *****************************************************************************/

SCL_iterator_t (hash_end) (SCL_hash_t a_hash)
   {
   const S_node_t* node = NULL;
   size_t index = a_hash->size;
   const S_node_t** table = (const S_node_t**)&a_hash->table[index];

   while ((node == NULL) && (index-- > 0))
      {
      node = *--table;
      }
   if (node != NULL) while (SUCC(node) != NULL) node = SUCC(node);

   return (SCL_iterator_t)node;
   }


/*****************************************************************************
 * Public Function hash_next
 *****************************************************************************/

SCL_iterator_t (hash_next) (SCL_iterator_t a_iterator)
   {
   const S_node_t* node = a_iterator;
   size_t index = node->index;
   const size_t size = node->hash->size;
   const S_node_t** table = (const S_node_t**)&node->hash->table[index];

   node = SUCC(node);
   while ((node == NULL) && (++index < size))
      {
      node = *++table;
      }

   return (SCL_iterator_t)node;
   }


/*****************************************************************************
 * Public Function hash_prev
 *****************************************************************************/

SCL_iterator_t (hash_prev) (SCL_iterator_t a_iterator)
   {
   const S_node_t* node = a_iterator;
   size_t index = node->index;
   const S_node_t** table = (const S_node_t**)&node->hash->table[index];

   node = PRED(node);
   if (node != NULL) return (SCL_iterator_t)node;
   while ((node == NULL) && (index-- > 0))
      {
      node = *--table;
      }
   if (node != NULL) while (SUCC(node) != NULL) node = SUCC(node);

   return (SCL_iterator_t)node;
   }


/*****************************************************************************
 * Public Function hash_data_set
 *****************************************************************************/

void (hash_data_set) (SCL_iterator_t a_iterator, const void* a_data)
   {
   ((S_node_t*)a_iterator)->data = a_data;
   }


/*****************************************************************************
 * Public Function hash_data_get
 *****************************************************************************/

void* (hash_data_get) (SCL_iterator_t a_iterator)
   {
   return (void*)((S_node_t*)a_iterator)->data;
   }


/*****************************************************************************
 * Public Function hash_key_get
 *****************************************************************************/

const char* (hash_key_get) (SCL_iterator_t a_iterator)
   {
   return ((S_node_t*)a_iterator)->key;
   }


/*****************************************************************************
 * Public Function hash_foreach
 *****************************************************************************/

void (hash_foreach) (SCL_hash_t a_hash, SCL_cbfn_t a_func, void* a_context)
   {
   const S_node_t* node;
   const size_t size = a_hash->size;
   const S_node_t** table = (const S_node_t**)a_hash->table;
   size_t i;
   int stat;

   for (i=0 ; i<size ; i++)
      {
      node = *table++;
      while (node != NULL)
         {
         stat = (*a_func) (
                          node->key,
                          (long)node->index,
                          (void*)node->data,
                          a_context
                          );
         if (stat != SCL_NOTFOUND) return;
         node = SUCC(node);
         }
      }

   return;
   }


/* end of file */