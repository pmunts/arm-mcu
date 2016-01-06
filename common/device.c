/******************************************************************************/
/*                                                                            */
/*                 MCU independent Device Abstraction Layer                   */
/*                                                                            */
/******************************************************************************/

// $Id$

// Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <fcntl.h>
#include <string.h>

#include <cpu.h>

// Compile support for FreeRTOS

#ifdef FREERTOS
#include <FreeRTOS.h>
#include <task.h>
#endif

// Device subsystem data definitions

#ifndef MAX_DEVICES
#ifdef CONIO_STDIO
#define MAX_DEVICES		2
#else
#define MAX_DEVICES		16
#endif
#endif

typedef enum
{
  DEVICE_TYPE_UNUSED		= 0,
  DEVICE_TYPE_CHAR		= 1,
  DEVICE_TYPE_BLOCK		= 2,
  DEVICE_TYPE_DIRECTORY		= 3,
  DEVICE_TYPE_FILE		= 4,
} device_type_t;

// This is the device table

typedef struct
{
  char name[DEVICE_NAME_SIZE+1];
  device_type_t type;
  unsigned int subdevice;
  device_open_fn_t open;
  device_close_fn_t close;
  device_write_fn_t write;
  device_read_fn_t read;
  device_write_ready_fn_t write_ready;
  device_read_ready_fn_t read_ready;
  device_seek_fn_t seek;
  device_fcntl_fn_t fcntl;
  int isopen;
  int flags;	// From open()
  int mode;	// From open()
} device_t;

static device_t device_table[MAX_DEVICES];

/* Register a character device driver to the next available file descriptor */

int device_register_char(char *name,
                         unsigned int subdevice,
                         device_open_fn_t openfn,
                         device_close_fn_t closefn,
                         device_write_fn_t writefn,
                         device_read_fn_t readfn,
                         device_write_ready_fn_t write_readyfn,
                         device_read_ready_fn_t read_readyfn,
                         device_fcntl_fn_t fcntlfn)
{
  int namelen;
  int fd;

  errno_r = 0;

  // Check for invalid device name

  if (name == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Check for duplicate device name

  if (device_lookup(name) >= 0)
  {
    errno_r = EEXIST;
    return -1;
  }

  // Only store device name up to colon

  namelen = strcspn(name, ":");

  // Check device name length

  if (namelen > DEVICE_NAME_SIZE)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Search device table for an empty slot

  for (fd = 3; fd < MAX_DEVICES; fd++)
    if (device_table[fd].type == DEVICE_TYPE_UNUSED)
    {
      memset(&device_table[fd], 0, sizeof(device_t));
      strlcpy(device_table[fd].name, name, namelen+1);
      device_table[fd].type = DEVICE_TYPE_CHAR;
      device_table[fd].subdevice = subdevice;
      device_table[fd].open = openfn;
      device_table[fd].close = closefn;
      device_table[fd].write = writefn;
      device_table[fd].read = readfn;
      device_table[fd].write_ready = write_readyfn;
      device_table[fd].read_ready = read_readyfn;
      device_table[fd].fcntl = fcntlfn;

      return fd;
    }

  errno_r = ENOMEM;
  return -1;
}

/* Register a character device driver to a specific file descripter */

int device_register_char_fd(int fd,
                            unsigned int subdevice,
                            device_write_fn_t writefn,
                            device_read_fn_t readfn,
                            device_write_ready_fn_t write_readyfn,
                            device_read_ready_fn_t read_readyfn,
                            device_fcntl_fn_t fcntlfn)
{
  errno_r = 0;

  // Check invalid file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  // Check for file descriptor in use

  if (device_table[fd].type != DEVICE_TYPE_UNUSED)
  {
    errno_r = EEXIST;
    return -1;
  }

  memset(&device_table[fd], 0, sizeof(device_t));
  device_table[fd].type = DEVICE_TYPE_CHAR;
  device_table[fd].subdevice = subdevice;
  device_table[fd].write = writefn;
  device_table[fd].read = readfn;
  device_table[fd].write_ready = write_readyfn;
  device_table[fd].read_ready = read_readyfn;
  device_table[fd].fcntl = fcntlfn;
  device_table[fd].isopen = true;

  if ((readfn != NULL) && (writefn != NULL))
    device_table[fd].flags = O_RDWR;
  else if (readfn == NULL)
    device_table[fd].flags = O_WRONLY;
  else if (writefn == NULL)
    device_table[fd].flags = O_RDONLY;

  return 0;
}

/* Register a block device driver to the next available file descriptor */

int device_register_block(char *name,
                          device_open_fn_t openfn,
                          device_close_fn_t closefn,
                          device_write_fn_t writefn,
                          device_read_fn_t readfn,
                          device_seek_fn_t seekfn,
                          device_fcntl_fn_t fcntlfn)
{
  int namelen;
  int fd;

  errno_r = 0;

  // Check for invalid device name

  if (name == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Check for duplicate device name

  if (device_lookup(name) >= 0)
  {
    errno_r = EEXIST;
    return -1;
  }

  // Only store device name up to colon

  namelen = strcspn(name, ":");

  // Check device name length

  if (namelen > DEVICE_NAME_SIZE)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Search device table for an empty slot

  for (fd = 3; fd < MAX_DEVICES; fd++)
    if (device_table[fd].type == DEVICE_TYPE_UNUSED)
    {
      memset(&device_table[fd], 0, sizeof(device_t));
      strlcpy(device_table[fd].name, name, namelen+1);
      device_table[fd].type = DEVICE_TYPE_BLOCK;
      device_table[fd].open = openfn;
      device_table[fd].close = closefn;
      device_table[fd].write = writefn;
      device_table[fd].read = readfn;
      device_table[fd].seek = seekfn;
      device_table[fd].fcntl = fcntlfn;

      return fd;
    }

  errno_r = ENOMEM;
  return -1;
}

/* Unregister a device driver */

int device_unregister(int fd)
{
  errno_r = 0;

  // Validate the file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  memset(&device_table[fd], 0, sizeof(device_t));
  return 0;
}

/* Lookup a device */

int device_lookup(char *name)
{
  int namelen;
  int fd;

  errno_r = 0;

  // Check for invalid device name

  if (name == NULL)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Only compare before colon character

  namelen = strcspn(name, ":");

  // Check device name length

  if (namelen > DEVICE_NAME_SIZE)
  {
    errno_r = EINVAL;
    return -1;
  }

  for (fd = 0; fd < MAX_DEVICES; fd++)
    if (!strncasecmp(device_table[fd].name, name, namelen))
      return fd;

  // No matching device was found

  errno_r = ENODEV;
  return -1;
}

/* Open a device */

int device_open(char *name, int flags, int mode)
{
  int fd;

  errno_r = 0;

  // Look up the device

  fd = device_lookup(name);
  if (fd < 0)
  {
    return fd;
  }

  // Check for already open

  if (device_table[fd].isopen)
  {
    errno_r = EBUSY;
    return -1;
  }

  // Validate parameters

  if ((flags & O_ACCMODE) == O_ACCMODE)
  {
    errno_r = EINVAL;
    return -1;
  }

  // Save open flag

  device_table[fd].isopen = true;

  // Save the flags

  device_table[fd].flags = flags;

  // Save the mode

  device_table[fd].mode = mode;

  // Initialize the device

  if (device_table[fd].open != NULL)
    if (device_table[fd].open(name, &device_table[fd].subdevice))
      return -1;

  return fd;
}

/* Close a device */

int device_close(int fd)
{
  errno_r = 0;

  // Validate the file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EBADF;
    return -1;
  }

  // We are not allowed to close a device created with device_register_char_fd()

  if (device_table[fd].name[0] == 0)
  {
    errno_r = EIO;
    return -1;
  }

  device_table[fd].subdevice = 0;
  device_table[fd].isopen = false;
  device_table[fd].flags = 0;
  device_table[fd].mode = 0;

  if (device_table[fd].close != NULL)
    if (device_table[fd].close(fd))
      return -1;

  return 0;
}

/* Return true if the device has received data available */

int device_ready_read(int fd)
{
  errno_r = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].read_ready == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_WRONLY)
  {
    errno_r = EBADF;
    return -1;
  }

  return device_table[fd].read_ready(device_table[fd].subdevice);
}

/* Return true if the device is ready to accept transmit data */

int device_ready_write(int fd)
{
  errno_r = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].write_ready == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_RDONLY)
  {
    errno_r = EBADF;
    return -1;
  }

  return device_table[fd].write_ready(device_table[fd].subdevice);
}

/* Read uncooked input from a device (whatever is available) */

int device_read_raw(int fd, char *s, unsigned int count)
{
  errno_r = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].read == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_WRONLY)
  {
    errno_r = EBADF;
    return -1;
  }

  return device_table[fd].read(device_table[fd].subdevice, s, count);
}

/* Read cooked input from a device */

int device_read_cooked(int fd, char *s, unsigned int count)
{
  device_t *d;
  char *p;
  char c;
  int status;

  errno_r = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  d = &device_table[fd];

  if (d->type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (d->read == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_WRONLY)
  {
    errno_r = EBADF;
    return -1;
  }

// Handle cooked character device input here

  for (p = s; p < s + count - 1;)
  {
    if (d->read_ready != NULL)
    {
      do
      {
#ifdef FREERTOS
        if (xTaskGetCurrentTaskHandle() != NULL)
          taskYIELD();
#endif
      }
      while ((status = d->read_ready(d->subdevice)) == 0);
      if (status < 0) return status;
    }

    status = d->read(d->subdevice, &c, 1);
    if (status < 0) return status;
    if (status == 0) continue;

    switch (c)
    {
      case '\r' :
      case '\n' :
        if (fd > 0)
          device_write_raw(fd, (char *) "\r\n", 2);
        else
          device_write_raw(1, (char *) "\r\n", 2);

        *p++ = '\n';
        *p = 0;
        return p - s;

      case '\b' :
      case 127 :
        if (p > s)
        {
          *p-- = 0;

          if (fd > 0)
            device_write_raw(fd, (char *) "\b \b", 3);
          else
            device_write_raw(1, (char *) "\b \b", 3);
        }
        break;

      default :
        if (fd > 0)
          device_write_raw(fd, &c, 1);
        else
          device_write_raw(1, &c, 1);

        *p++ = c;
        break;
    }
  }

  *p = 0;
  return p - s;
}

/* Read input from a device */

int device_read(int fd, char *s, unsigned int count)
{
  errno_r = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].read == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_WRONLY)
  {
    errno_r = EBADF;
    return -1;
  }

  if ((device_table[fd].type != DEVICE_TYPE_CHAR) ||
      (device_table[fd].flags & O_BINARY))
    return device_read_raw(fd, s, count);
  else
    return device_read_cooked(fd, s, count);
}

/* Read a single unbuffered, unechoed character from a device */

int device_getc(int fd)
{
  int status;
  char c;

  errno_r = 0;

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].read == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_WRONLY)
  {
    errno_r = EBADF;
    return -1;
  }

  if (device_table[fd].read_ready != NULL)
  {
    do
    {
#ifdef FREERTOS
      if (xTaskGetCurrentTaskHandle() != NULL)
        taskYIELD();
#endif
    }
    while ((status = device_table[fd].read_ready(device_table[fd].subdevice)) == 0);
    if (status < 0) return status;
  }

  status = device_table[fd].read(device_table[fd].subdevice, &c, 1);
  if (status < 0) return status;

  return c;
}

/* Write uncooked output to a device */

int device_write_raw(int fd, char *s, unsigned int count)
{
  int status;
  unsigned int i;

  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_RDONLY)
  {
    errno_r = EBADF;
    return -1;
  }

// Dispatch raw data to device driver.  Keep trying if less than the whole
// buffer is transferred.

  for (i = 0; i < count;)
  {
    if (device_table[fd].write_ready != NULL)
    {
      do
      {
#ifdef FREERTOS
        if (xTaskGetCurrentTaskHandle() != NULL) taskYIELD();
#endif
      }
      while ((status = device_table[fd].write_ready(device_table[fd].subdevice)) == 0);
      if (status < 0) return status;
    }

    status = device_table[fd].write(device_table[fd].subdevice, s, count - i);
    if (status < 0) return status;
    if (status == 0) continue;

    s += status;
    i += status;
  }

  return count;
}

/* Write cooked (CR before LF) output to a device */

int device_write_cooked(int fd, char *s, unsigned int count)
{
  int len;
  unsigned int i;
  char *p;

  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_RDONLY)
  {
    errno_r = EBADF;
    return -1;
  }

// Handle cooked character device output here

  for (i = 0; i < count;)
  {
    p = (char *) memchr((void *) s, '\n', count - i);

    if (p == NULL)
    {
      len = device_write_raw(fd, s, count - i);	// Write everything
      if (len < 0) return len;

      i += len;
      s += len;
    }
    else
    {
      len = device_write_raw(fd, s, p - s);	// Write everything up to LF
      if (len < 0) return len;

      i += len;
      s += len;

      len = device_write_raw(fd, (char *) "\r\n", 2);	// Write CR/LF
      if (len < 0) return len;

      i++;
      s++;
    }
  }

  return count;
}

/* Write to a device */

int device_write(int fd, char *s, unsigned int count)
{
  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  if ((device_table[fd].flags & O_ACCMODE) == O_RDONLY)
  {
    errno_r = EBADF;
    return -1;
  }

  if ((device_table[fd].type != DEVICE_TYPE_CHAR) ||
      (device_table[fd].flags & O_BINARY))
    return device_write_raw(fd, s, count);
  else
    return device_write_cooked(fd, s, count);
}

/* Write a single character to a device */

int device_putc(int fd, char c)
{
  return device_write(fd, &c, 1);
}

/* Is this file descriptor a character device? */

int device_isatty(int fd)
{
  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  return (device_table[fd].type == DEVICE_TYPE_CHAR);
}

/* Return file information */

int device_stat(int fd, struct stat *st)
{
  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  memset(st, 0, sizeof(struct stat));

  switch (device_table[fd].type)
  {
    case DEVICE_TYPE_CHAR :
      st->st_mode = S_IFCHR;
      break;

    case DEVICE_TYPE_BLOCK :
      st->st_mode = S_IFBLK;
      break;

    case DEVICE_TYPE_DIRECTORY :
      st->st_mode = S_IFDIR;
      break;

    case DEVICE_TYPE_FILE :
      st->st_mode = S_IFREG;
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

  return 0;
}

/* Seek to position in file */

off_t device_seek(int fd, off_t pos, int whence)
{
  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_CHAR)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }

  if (device_table[fd].seek == NULL)
  {
    errno_r = EIO;
    return -1;
  }

  return device_table[fd].seek(device_table[fd].subdevice, pos, whence);
}

int device_fcntl(int fd, int cmd, ...)
{
  va_list args;

  errno_r = 0;

// Validate file descriptor

  if ((fd < 0) || (fd >= MAX_DEVICES))
  {
    errno_r = EINVAL;
    return -1;
  }

  if (device_table[fd].type == DEVICE_TYPE_UNUSED)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (device_table[fd].type != DEVICE_TYPE_CHAR)
  {
    errno_r = EINVAL;
    return -1;
  }

  if (!device_table[fd].isopen)
  {
    errno_r = EIO;
    return -1;
  }


// Perform operation

  switch (cmd)
  {
    case F_GETFL :
      return device_table[fd].flags;

    case F_SETFL :
      va_start(args, cmd);
      device_table[fd].flags = va_arg(args, int);
      va_end(args);
      return 0;

    default :
      if (device_table[fd].fcntl != NULL)
      {
        va_start(args, cmd);
        int result = device_table[fd].fcntl(device_table[fd].subdevice, cmd, args);
        va_end(args);
        return result;
      }
      else
      {
        errno_r = EINVAL;
        return -1;
      }
  }
}

// The following syscall service functions are aliased to device_xxxx()
// functions defined above

int _open(const char *path, int flags, mode_t mode) __attribute__((alias("device_open")));

int _close(int fd) __attribute__((alias("device_close")));

ssize_t _read(int fd, void *dst, size_t size) __attribute__((alias("device_read")));

ssize_t _write(int fd, const void *src, size_t size) __attribute__((alias("device_write")));

int _fstat(int fd, struct stat *st) __attribute__((alias("device_stat")));

int _isatty(int fd) __attribute__((alias("device_isatty")));

off_t _lseek(int fd, off_t pos, int whence) __attribute__((alias("device_seek")));

int fcntl(int fd, int cmd, ...) __attribute__((alias("device_fcntl")));
