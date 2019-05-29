#ifndef _EVENTS_H_
#define _EVENTS_H_

#ifndef MAX_PAYLOAD_SIZE
#define MAX_PAYLOAD_SIZE 64
#endif

// Type declarations

typedef struct
{
  uint32_t code;
  uint8_t payload[MAX_PAYLOAD_SIZE];
} event_msg_t;

typedef int (*event_handler_t)(const event_msg_t * const event);

// Functions

extern int event_enqueue(const QueueHandle_t queue, const uint32_t code,
  const void * const payload, const size_t length, const unsigned timeoutms);

extern int event_enqueue_isr(const QueueHandle_t queue, const uint32_t code,
  const void * const payload, const size_t length);

extern int event_dispatch(const event_handler_t *EventHandlers,
  const unsigned max_handlers, const event_msg_t * const event);

#endif
