/* Library for getting virtual memory informations

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef _VMINFO_H_
#define _VMINFO_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /* Get memory page size */
  long get_vmem_pagesize (void);

  struct proc_vmem;

  /* Allocates space for a new vmem object.
   * Returns 0 if all went ok. Errors are returned as negative values.  */
  int proc_vmem_new (struct proc_vmem **vmem);

  /* Fill the proc_vmem structure pointed with the values found in the
   * proc filesystem.  */
  void proc_vmem_read (struct proc_vmem *vmem);

  /* Drop a reference of the virtual memory library context. If the refcount
   * of reaches zero, the resources of the context will be released.  */
  struct proc_vmem *proc_vmem_unref (struct proc_vmem *vmem);

  /* Accessing the values from proc_vmem */

  unsigned long proc_vmem_get_pgalloc (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgfault (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgfree (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgmajfault (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgpgin (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgpgout (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgrefill (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pgscan (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pswpin (struct proc_vmem *vmem);
  unsigned long proc_vmem_get_pswpout (struct proc_vmem *vmem);

#ifdef __cplusplus
}
#endif

#endif				/* _VMINFO_H_ */
