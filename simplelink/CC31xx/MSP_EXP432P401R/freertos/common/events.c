#include <errno.h>
#include <string.h>

#include <console.h>
#include <events.h>

// Print error message if DEBUG is defined

#ifdef DEBUG
#define EVENTERRMSG(msg) { puts("ERROR: "); puts(msg); puts("\r\n"); }
#else
#define EVENTERRMSG(msg)
#endif

// General purpose error checking macro

#define FAILIF(cond, msg, err) if (cond) { EVENTERRMSG(msg); return err; }

// Send an event message

int event_enqueue(const QueueHandle_t queue, const uint32_t code,
  const void * const payload, const size_t length, const unsigned timeoutms)
{
  // Validate parameters

  FAILIF(queue == NULL, "queue is NULL", EINVAL);
  FAILIF((payload == NULL) && (length != 0), "payload and length are inconsistent", EINVAL);
  FAILIF((payload != NULL) && (length == 0), "payload and length are inconsistent", EINVAL);
  FAILIF(length > MAX_PAYLOAD_SIZE, "payload greater than MAX_PAYLOAD_SIZE", EINVAL);
  
  // Build the event message

  event_msg_t event = { code };

  if (payload != NULL)
    memcpy(event.payload, payload, length);

  // Send the event message

  FAILIF(xQueueSend(queue, &event, pdMS_TO_TICKS(timeoutms)) != pdPASS, "xQueueSend() failed", EAGAIN);

  return 0;
}

// Send an event message from an interrupt service routine

int event_enqueue_isr(const QueueHandle_t queue, const uint32_t code,
  const void * const payload, const size_t length)
{
  // Validate parameters

  if (queue == NULL) return EINVAL;
  if ((payload == NULL) && (length != 0)) return EINVAL;
  if ((payload != NULL) && (length == 0)) return EINVAL;
  if (length > MAX_PAYLOAD_SIZE) return EINVAL;
  
  // Build the event message

  event_msg_t event = { code };

  if (payload != NULL)
    memcpy(event.payload, payload, length);

  // Send the event message

  if (!xQueueSendFromISR(queue, &event, NULL)) return EAGAIN;

  return 0;
}

// Dispatch to an event handler

int event_dispatch(const event_handler_t * const EventHandlers,
  const unsigned num_handlers, const event_msg_t * const event)
{
  // Validate parameters

  FAILIF(event->code >= num_handlers, "Unrecognized event code", EINVAL);

  // Dispatch event to its handler

  return EventHandlers[event->code](event);
}
