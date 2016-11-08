// Copyright (C)2016, Philip Munts, President, Munts AM Corp.
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

#include <assert.h>
#include <uthash.h>

#include "common.h"

typedef struct
{
  int number;
  command_handler_t handler;
  UT_hash_handle hh;
} CommandElement_t;

static CommandElement_t *CommandTable = NULL;

// Add a command handler.

void AddCommand(uint16_t number, command_handler_t handler)
{
  CommandElement_t *ce;

  ce = malloc(sizeof(CommandElement_t));
  assert(ce != NULL);

  ce->number = number;
  ce->handler = handler;

  HASH_ADD_INT(CommandTable, number, ce);
}

// Lookup command handler.  Return *handler=NULL if not found.

void LookupCommand(uint16_t number, command_handler_t *handler)
{
  int key = number;
  CommandElement_t *item;

  HASH_FIND_INT(CommandTable, &key, item);

  if (item == NULL)
    *handler = NULL;
  else
    *handler = item->handler;
}
