#include <stdint.h>
#include <stdio.h>

#include <cpu.h>

#include "uthash.h"

typedef struct
{
  int key;
  uint8_t *data;
  UT_hash_handle hh;
} hash_element_t;

hash_element_t *HashTable = NULL;

void AddElement(int key, uint8_t *item)
{
  hash_element_t *s = malloc(sizeof(hash_element_t));
  if (s == NULL) return;

  s->key = key;
  s->data = item;
  HASH_ADD_INT(HashTable, key, s);
}

int main(void)
{
  int i;
  hash_element_t *p;

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio(CONSOLE_PORT);

  printf("\033[H\033[2J%s Hash Library Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  printf("CPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

  // Added items to the hash table

  for (i = 0; i < 100; i++)
  { 
    AddElement(i, (uint8_t *) (0x10000000 + i));
  }

  // Retrieve items from the hash table

  for (i = 0; i < 100; i++)
  {
    HASH_FIND_INT(HashTable, &i, p);
    printf("%04X %08X\n", p->key, (unsigned) p->data);
  }

  exit(0);
}
